#include "window.hpp"

#include <QFontDatabase>
#include <QWidget>
#include <QtConcurrent>

#include "launcher.hpp"
namespace ui
{

int start(int argc, char *argv[])
{
  QApplication application(argc, argv);

  Window window{};
  window.show();

  return QApplication::exec();
}

Window::Window(QWidget* parent)
    : QWidget(parent)
{
  _masterFrameUI.setupUi(this->master_frame);

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
}

void Window::mousePressEvent(QMouseEvent *event)
{
  _windowDragActive = true;
  _mouseEventPos = event->pos();
}

void Window::mouseReleaseEvent(QMouseEvent *event)
{
  _windowDragActive = false;
}

void Window::mouseMoveEvent(QMouseEvent *event)
{
  if (!_windowDragActive)
    return;

  move(event->globalPosition().toPoint() - _mouseEventPos);
}

void Window::handle_exit()
{
  QCoreApplication::quit();
}

void Window::handle_minimize()
{
  this->showMinimized();
}

void Window::handle_settings()
{
  //TODO: implement settings
}

void Window::handle_repair()
{
  //TODO: implement repair
}

void Window::handle_ticket()
{
  //TODO: implement ticket
}

void Window::handle_logout()
{
  this->_masterFrameUI.login_widget->show();
  this->_masterFrameUI.menu_widget->hide();
}

void Window::handle_launch()
{
 //TODO: implement launch
}

void Window::handle_login()
{
  this->_loginWidgetUI.btn_login->setDisabled(true); // probably a valid mutex?

  auto username = this->_loginWidgetUI.input_username->text().toStdString();
  auto password = this->_loginWidgetUI.input_password->text().toStdString();

  this->login_thread = std::make_unique<std::thread>([username, password, this]() -> void
  {
    try
    {
      launcher::authenticate(username, password);

      auto future = QtConcurrent::run([=]() {
        this->_masterFrameUI.menu_widget->show();
        this->_masterFrameUI.login_widget->hide();
      });

    } catch(std::exception &e)
    {
      auto future = QtConcurrent::run([=]() {
        this->_loginWidgetUI.l_error->show();
      });
    }

    auto future = QtConcurrent::run([=]() {
      this->_loginWidgetUI.btn_login->setDisabled(false);
    });
  });

  this->login_thread->detach();
}


void Window::handle_info()
{
  //TODO: implement info
}

}
