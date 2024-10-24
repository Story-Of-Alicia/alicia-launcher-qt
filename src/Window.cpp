#include "Window.hpp"
#include "Launcher.hpp"

#include <QDesktopServices>
#include <QMessageBox>
#include <QMouseEvent>
#include <QMovie>
#include <QPainter>
#include <QtConcurrent>
#include <QWidget>
#include <QGraphicsBlurEffect>

#include <cmath>

constexpr char const* const WEB_STORYOFALICIA_TICKET = "https://storyofalicia.com/ticket";

namespace ui
{

int start(int argc, char* argv[])
{
  QApplication application(argc, argv);

  Window window{};
  window.show();

  return QApplication::exec();
}

Window::Window(QWidget* parent)
    : QWidget(parent)
{
  _progressDialog->hide();
  _gameStartMovie = new QMovie(":/img/game_start_hover.gif");

  // to display frame 0, so the button is not empty
  _gameStartMovie->start();
  _gameStartMovie->setPaused(true);

  _masterFrameUI.setupUi(_master);

  _masterFrameUI.l_game_start->setMovie(_gameStartMovie);

  _loginWidgetUI.setupUi(_masterFrameUI.login_widget);
  _loginWidgetUI.l_error->hide();

  _masterFrameUI.login_widget->show();

  _menuWidgetUI.setupUi(_masterFrameUI.menu_widget);
  _masterFrameUI.menu_widget->hide();

  _masterFrameUI.l_frame->setAttribute(Qt::WA_TransparentForMouseEvents);
  _masterFrameUI.l_game_start_frame->setAttribute(Qt::WA_TransparentForMouseEvents);

  connect(_masterFrameUI.btn_exit, SIGNAL(clicked()), this, SLOT(handle_exit()));
  connect(_masterFrameUI.btn_minimize, SIGNAL(clicked()), this, SLOT(handle_minimize()));
  connect(_masterFrameUI.btn_settings, SIGNAL(clicked()), this, SLOT(handle_settings()));

  connect(_masterFrameUI.btn_repair, SIGNAL(clicked()), this, SLOT(handle_repair()));
  connect(_masterFrameUI.btn_ticket, SIGNAL(clicked()), this, SLOT(handle_ticket()));

  connect(_loginWidgetUI.btn_login, SIGNAL(clicked()), this, SLOT(handle_login()));
  connect(_menuWidgetUI.btn_logout, SIGNAL(clicked()), this, SLOT(handle_logout()));

  connect(_menuWidgetUI.btn_info, SIGNAL(clicked()), this, SLOT(handle_info()));

  setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
  setAttribute(Qt::WA_NoSystemBackground, true);
  setAttribute(Qt::WA_TranslucentBackground, true);

  // handle l_game_start mouse tracking
  _masterFrameUI.l_game_start->setMouseTracking(true);
  _masterFrameUI.l_game_start->installEventFilter(this);

  // to be able to stop the animation cleanly at frame 0
  connect(_gameStartMovie, SIGNAL(frameChanged(int)), this, SLOT(handle_frame_changed(int)));
}

void Window::mousePressEvent(QMouseEvent* event)
{
  _windowDragActive = true;
  _mouseEventPos = event->pos();
}

void Window::mouseReleaseEvent(QMouseEvent* event) { _windowDragActive = false; }

void Window::mouseMoveEvent(QMouseEvent* event)
{
  if (!_windowDragActive)
    return;

  move(event->globalPosition().toPoint() - _mouseEventPos);
}

bool Window::eventFilter(QObject* object, QEvent* event)
{
  // handling MouseButtonPress and MouseMove for _masterFrameUI.l_game_start
  if (
    object == _masterFrameUI.l_game_start && (event->type() == QEvent::MouseMove) ||
    (event->type() == QEvent::MouseButtonPress))
  {
    if (!dynamic_cast<QWidget*>(object)->isEnabled())
      return true;

    // sqrt((x1 - x2)^2 + (y1 - y2)^2)
    // using "scene" coordinates (window coordinates)
    double const distance = std::sqrt(
      std::pow(
        dynamic_cast<QMouseEvent*>(event)->scenePosition().x() -
          _masterFrameUI.l_game_start->geometry().center().x(),
        2) +
      std::pow(
        dynamic_cast<QMouseEvent*>(event)->scenePosition().y() -
          _masterFrameUI.l_game_start->geometry().center().y(),
        2));

    // game start button radius is 119 pixels
    if (distance <= 119)
    {
      if (event->type() == QEvent::MouseMove)
      {
        // playing animation when the mouse is within the button
        _shouldAnimateGameStart = true;
        _gameStartMovie->setPaused(false);
      }
      else if (
        event->type() == QEvent::MouseButtonPress &&
        dynamic_cast<QMouseEvent*>(event)->button() == Qt::LeftButton)
      {
        // stopping the animation so it doesn't get stuck replaying
        _shouldAnimateGameStart = false;
        // launching the game when the mouse is pressed within the button
        handle_launch();
      }
    }
    else
    {
      if (event->type() == QEvent::MouseMove)
      {
        // signal to stop the animation when the mouse leaves the button
        _shouldAnimateGameStart = false;
      }
    }
  }

  return false;
}

void Window::handle_exit() { QCoreApplication::quit(); }

void Window::handle_minimize() { showMinimized(); }

void Window::handle_settings()
{
  // TODO: implement settings
}

void Window::handle_repair()
{
  // todo: implement
}

void Window::handle_ticket() { QDesktopServices::openUrl(QString(WEB_STORYOFALICIA_TICKET)); }

void Window::handle_logout()
{
  _authenticated = false;
  _masterFrameUI.login_widget->show();
  _masterFrameUI.menu_widget->hide();
}

// maybe remove slot specifier
void Window::handle_launch()
{
  if (_workerRunning)
    return;

  if (!_authenticated)
    return;

  _workerRunning = true;
  _workerThread = std::make_unique<std::thread>(
    [this]
    {
      bool patched = false;
      if (const auto files = launcher::fileCheck(); !files.empty())
      {
        QMetaObject::invokeMethod(
          this,
          [this, files]()
          {
            QMessageBox box(this);
            box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            box.setIcon(QMessageBox::Icon::Critical);
            box.setText(QString("%1 files need patching. Patch them?").arg(files.size()));
            return box.exec() == QMessageBox::Yes;
          },
          Qt::BlockingQueuedConnection,
          qReturnArg(patched));
        // patched will be set to true, if user picked the yes option
        if (patched)
        {
          QMetaObject::invokeMethod(this, [this]
          {
            this->_progressDialog->begin(_masterFrameUI.content);
          }, Qt::QueuedConnection);
          try
          {
            launcher::fileUpdate(files, [this](const int progress) -> void
            {
              QMetaObject::invokeMethod(this, [this, progress]
              {
                this->_progressDialog->update(progress, "Patching");
              }, Qt::QueuedConnection);
            });

            QMetaObject::invokeMethod(this, [this]
              {
                this->_progressDialog->update(100, "Patching");
              }, Qt::QueuedConnection); // make the widget close itself
          }
          catch (const std::exception& e)
          {
            // TODO: log patching error
            patched = false;
          }
        }
      } else
      {
        patched = true; // all files have the correct checksum
      }

      // if the files were recently patched
      if (patched)
      {
        //QMetaObject::invokeMethod(this, [this] { this->hide(); }, Qt::QueuedConnection);
        if (launcher::launch(this->_profile))
        {
          //std::this_thread::sleep_for(std::chrono::seconds(5));
        }
        else
        {
          // TODO: log error
        }

        //QMetaObject::invokeMethod(this, [this] { handle_exit(); }, Qt::QueuedConnection);
      }

      this->_workerRunning = false;
    });
  _workerThread->detach();
}

void Window::handle_post_login()
{
  if (_authenticated)
  {
    _menuWidgetUI.l_username_d->setText(QString(_profile.username.data()));
    _menuWidgetUI.l_player_d->setText(QString(_profile.character_name.data()));

    _menuWidgetUI.l_level_d->setText(QString::number(_profile.level));
    _menuWidgetUI.l_guild_d->setText(QString(_profile.guild.data()));
    auto const date = QDateTime::fromSecsSinceEpoch(static_cast<qint64>(_profile.last_login));
    _menuWidgetUI.l_last_login_d->setText(date.toString("yy-MM-dd HH:mm:ss"));

    _masterFrameUI.menu_widget->show();
    _masterFrameUI.login_widget->hide();
  }
  else
  {
    _loginWidgetUI.l_error->setText("Authentication failed");
    _loginWidgetUI.l_error->show();
  }
  _masterFrameUI.login_widget->setDisabled(false);
}

void Window::handle_login()
{
  if (_workerRunning)
    return;

  _loginWidgetUI.l_error->hide();
  _masterFrameUI.login_widget->setDisabled(true);

  auto const username = _loginWidgetUI.input_username->text().toStdString();
  auto const password = _loginWidgetUI.input_password->text().toStdString();

  // lock mutex
  _workerRunning = true;
  // authorization leaves the Qt Application thread, calls Qt functions trough
  // QMetaObject::invokeMethod
  _workerThread = std::make_unique<std::thread>(
    [username, password, this]() -> void
    {
      try
      {
        this->_profile = launcher::authenticate(username, password);
        this->_authenticated = true;
        QMetaObject::invokeMethod(this, Window::handle_post_login, Qt::QueuedConnection);
      }
      catch (std::exception& e)
      {
        QMetaObject::invokeMethod(this, Window::handle_post_login, Qt::QueuedConnection);
      }

      // release mutex
      this->_workerRunning = false;
    });

  _workerThread->detach();
}

void Window::handle_info()
{
  // TODO: implement info
}

void Window::handle_frame_changed(int frameNumber)
{
  if (!_shouldAnimateGameStart && frameNumber == 0)
  {
    // stop the playback at frame 0, when _shouldAnimateGameStart is false
    _gameStartMovie->setPaused(true);
  }
}

} // namespace ui
