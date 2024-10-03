#include "window.hpp"

#include <format>
#include <QFontDatabase>
#include <QWidget>

#include "launcher.hpp"
#include <QFile>

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

  networkManager = new QNetworkAccessManager(this);

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

  connect(this, SIGNAL(login_finished()), this, SLOT(cb_logged()));

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
  this->_loginWidgetUI.btn_login->setDisabled(true);

  launcher::authenticate_async(
    this->_loginWidgetUI.input_username->text().toStdString(),
    this->_loginWidgetUI.input_password->text().toStdString(),
    [this]() -> void {
      QMetaObject::invokeMethod(this, [this]() {
          QNetworkRequest request(QUrl("http://localhost:3000/player/1"));
          QNetworkReply *reply = networkManager->get(request);

          connect(reply, SIGNAL(finished()), this, SLOT(handle_authenticate()));

          currentReply = reply;
                
      }, Qt::QueuedConnection);
    }
  );
}

void Window::handle_info()
{
  //TODO: implement info
}

void Window::cb_logged()
{
  this->_masterFrameUI.menu_widget->show();
  this->_masterFrameUI.login_widget->hide();
  this->_loginWidgetUI.btn_login->setDisabled(false);
}

void Window::handle_authenticate()
{
  if (!currentReply)
    return;

  if (currentReply->error()) 
  {
    qDebug() << "Error:" << currentReply->errorString();
    this->_loginWidgetUI.btn_login->setDisabled(false);
  } 
  else 
  {
    QByteArray response = currentReply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
    QJsonObject jsonObj = jsonDoc.object();

    qDebug() << "player data:";
    qDebug().noquote() << QJsonDocument(jsonObj).toJson(QJsonDocument::Indented);

    qDebug() << "nickname:" << jsonObj["nickName"].toString();
    qDebug() << "level:" << jsonObj["level"].toInt();

    emit login_finished();
  }
    
  currentReply->deleteLater();
  currentReply = nullptr;
}

}



/*
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

*/
