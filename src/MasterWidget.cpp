#include "MasterWidget.hpp"

#include <format>
#include <QFontDatabase>
#include <QMessageBox>
#include <QWidget>

#include "launcher.hpp"
#include "util.hpp"
#include <QFile>

namespace Ui
{

MasterWidget::MasterWidget(QWidget* parent)
    : QWidget(parent)
{
  _masterFrameUI.setupUi(this->master_frame);

  _loginWidgetUI.setupUi(_masterFrameUI.login_widget);
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

void MasterWidget::mousePressEvent(QMouseEvent *event)
{
    _windowDragActive = true;
    _mouseEventPos = event->pos();
}

void MasterWidget::mouseReleaseEvent(QMouseEvent *event)
{
  _windowDragActive = false;
}

void MasterWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!_windowDragActive)
      return;

    move(event->globalPosition().toPoint() - _mouseEventPos);
}

void MasterWidget::handle_exit()
{
  QCoreApplication::quit();
}

void MasterWidget::handle_minimize()
{
  this->showMinimized();
}

void MasterWidget::handle_settings()
{
  //TODO: implement settings
}

void MasterWidget::handle_repair()
{
  //TODO: implement repair
}

void MasterWidget::handle_ticket()
{
  //TODO: implement ticket
}

void MasterWidget::handle_logout()
{
  this->_masterFrameUI.login_widget->show();
  this->_masterFrameUI.menu_widget->hide();
}

void MasterWidget::handle_login()
{
  this->_masterFrameUI.login_widget->hide();
  this->_masterFrameUI.menu_widget->show();
}

void MasterWidget::handle_info()
{
  //TODO: implement info
}

void MasterWidget::handle_launch()
{
  const std::string _webInfoId = "927628CA6D76A6E9162C56D4E3E6D6E3";

  const launcher::WebInfo _webInfoContent{
    .gameId = "Alicia",
    .memberNo = 0,
    .loginId = "<name>",
    .authKey = "<auth_key>",
    .installUrl = "<install_url>",
    .serverType = 0,
    .serverInfo = ":",
    .sex = launcher::WebInfo::Sex::MALE,
    .birthday = "",
    .wardNo = 0,
    .cityCode = 0,
    .zipCode = "",
    .pcBangNo = 0,
    .closeTime = "",
  };

  std::string _executableProgram = "Alicia.exe";
  std::string _workdir = R"(C:\Users\martin\AppData\Local\Gametree\Alicia)";
  std::string _executableArguments = "-GameID 0";

  try
  {
    launcher::WebInfoHost webInfoHost;
    webInfoHost.host(_webInfoId, _webInfoContent);
  }
  catch (const std::exception& e)
  {
    QMessageBox::critical(this, "Error", "Couldn't host the web info.");
    return;
  }

  STARTUPINFO startupInfo{.cb = sizeof(STARTUPINFO)};
  PROCESS_INFORMATION processInfo{};

  SetCurrentDirectory(util::win32_widen(_workdir).data());
  if (!CreateProcess(
        util::win32_widen(_executableProgram).data(),
        util::win32_widen(_executableArguments).data(),
        nullptr,
        nullptr,
        FALSE,
        0,
        nullptr,
        nullptr,
        &startupInfo,
        &processInfo))
  {
    if (GetLastError() == ERROR_ELEVATION_REQUIRED)
    {
      QMessageBox::critical(this, "Error", "Can't launch the game, elevation is required.");
    }
    else
    {
      QMessageBox::critical(this, "Error", "Can't launch the game, misc error.");
    }
  }
  else
  {
    WaitForSingleObject(processInfo.hProcess, INFINITE);

    DWORD exitCode = 0;
    GetExitCodeProcess(processInfo.hProcess, &exitCode);
    QMessageBox::information(this, "Info", std::format("Game exited with code {}.", exitCode).data());

    CloseHandle(&processInfo);
    exit(0);
  }
}
} // namespace Ui
