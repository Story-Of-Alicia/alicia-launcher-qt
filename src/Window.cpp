#include "window.hpp"

#include <cmath>
#include <QFontDatabase>
#include <QMouseEvent>
#include <QMovie>
#include <QPainter>
#include <QtConcurrent>
#include <QWidget>

#include "Launcher.hpp"

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
  this->_gameStartMovie = new QMovie(":/img/game_start_hover.gif");
  this->_gameStartMovie->start();
  this->_gameStartMovie->setPaused(true);

  _masterFrameUI.setupUi(this->_masterFrame);

  _masterFrameUI.l_game_start->setMovie(_gameStartMovie);

  _loginWidgetUI.setupUi(_masterFrameUI.login_widget);
  _loginWidgetUI.l_error->hide();

  _masterFrameUI.login_widget->show();

  _menuWidgetUI.setupUi(_masterFrameUI.menu_widget);
  _masterFrameUI.menu_widget->hide();

  connect(_masterFrameUI.btn_exit, SIGNAL(clicked()), this, SLOT(handle_exit()));
  connect(_masterFrameUI.btn_minimize, SIGNAL(clicked()), this, SLOT(handle_minimize()));
  connect(_masterFrameUI.btn_settings, SIGNAL(clicked()), this, SLOT(handle_settings()));

  connect(_masterFrameUI.btn_repair, SIGNAL(clicked()), this, SLOT(handle_repair()));
  connect(_masterFrameUI.btn_ticket, SIGNAL(clicked()), this, SLOT(handle_ticket()));

  connect(_loginWidgetUI.btn_login, SIGNAL(clicked()), this, SLOT(handle_login()));
  connect(_menuWidgetUI.btn_logout, SIGNAL(clicked()), this, SLOT(handle_logout()));

  connect(_menuWidgetUI.btn_info, SIGNAL(clicked()), this, SLOT(handle_info()));

  this->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
  this->setAttribute(Qt::WA_NoSystemBackground, true);
  this->setAttribute(Qt::WA_TranslucentBackground, true);


  // handle l_game_start_frame mouse tracking, because it sits at the top of Z-axis
  this->_masterFrameUI.l_game_start_frame->setMouseTracking(true);
  this->_masterFrameUI.l_game_start_frame->installEventFilter(this);

  // to be able to stop the animation cleanly at frame 0
  connect(this->_gameStartMovie, SIGNAL(frameChanged(int)), this, SLOT(handle_frame_changed(int)));
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
  if (object == this->_masterFrameUI.l_game_start_frame && (event->type() == QEvent::MouseMove))
  {
    // sqrt((x1 - x2)^2 + (y1 - y2)^2)
    // using "scene" coordinates (window coordinates)
    double distance = std::sqrt(
      std::pow(
        dynamic_cast<QMouseEvent*>(event)->scenePosition().x() -
          this->_masterFrameUI.l_game_start->geometry().center().x(),
        2) +
      std::pow(
        dynamic_cast<QMouseEvent*>(event)->scenePosition().y() -
          this->_masterFrameUI.l_game_start->geometry().center().y(),
        2));
    // game start button radius is 119 pixels
    if (distance <= 119)
    {
      this->_shouldAnimateGameStart = true;
      this->_gameStartMovie->start();
    }
    else
    {
      this->_shouldAnimateGameStart = false;
    }
  }

  return false;
}

void Window::handle_exit() { QCoreApplication::quit(); }

void Window::handle_minimize() { this->showMinimized(); }

void Window::handle_settings()
{
  // TODO: implement settings
}

void Window::handle_repair()
{
  // TODO: implement repair
}

void Window::handle_ticket()
{
  // TODO: implement ticket
}

void Window::handle_logout()
{
  this->_masterFrameUI.login_widget->show();
  this->_masterFrameUI.menu_widget->hide();
}

void Window::handle_launch()
{
  // TODO implement
}

void Window::handle_login()
{
  this->_loginWidgetUI.btn_login->setDisabled(true); // lock mutex (probably safe?)

  auto username = this->_loginWidgetUI.input_username->text().toStdString();
  auto password = this->_loginWidgetUI.input_password->text().toStdString();

  //authorization leaves the Qt Application thread, calls Qt functions trough QtConcurrent
  this->_loginThread = std::make_unique<std::thread>(
    [username, password, this]() -> void
    {
      try
      {
        launcher::authenticate(username, password);

        auto future = QtConcurrent::run(
          [this]()
          {
            this->_masterFrameUI.menu_widget->show();
            this->_masterFrameUI.login_widget->hide();
          });
      }
      catch (std::exception& e)
      {
        auto future = QtConcurrent::run([this]() { this->_loginWidgetUI.l_error->show(); });
      }

      // release "mutex"
      auto future =
        QtConcurrent::run([this]() { this->_loginWidgetUI.btn_login->setDisabled(false); });
    });

  this->_loginThread->detach();
}

void Window::handle_info()
{
  // TODO: implement info
}

void Window::handle_frame_changed(int frameNumber)
{
  if (!this->_shouldAnimateGameStart && frameNumber == 0)
  {
    this->_gameStartMovie->setPaused(true);
  }
}

} // namespace ui
