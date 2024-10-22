#ifndef LAUNCHER_MASTERWINDOW_HPP
#define LAUNCHER_MASTERWINDOW_HPP

#include "ui_LoginWidget.h"
#include "ui_MasterFrame.h"
#include "ui_MenuWidget.h"

#include <memory>
#include <thread>

#include <QMouseEvent>

using namespace Ui;

namespace ui
{
int start(int argc, char* argv[]);

class Window final : public QWidget
{
  Q_OBJECT
public:
  explicit Window(QWidget* parent = nullptr);
private slots:
  void handle_exit();
  void handle_launch();
  void handle_login();
  void handle_logout();
  void handle_info();
  void handle_repair();
  void handle_ticket();
  void handle_minimize();
  void handle_settings();
  void handle_frame_changed(int frameNumber);

private:
  std::unique_ptr<std::thread> _loginThread;
  QMovie* _gameStartMovie = nullptr;
  QFrame* _masterFrame = new QFrame(this);

  MasterFrame _masterFrameUI{};
  LoginWidget _loginWidgetUI{};
  MenuWidget _menuWidgetUI{};

  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  bool eventFilter(QObject* object, QEvent* event) override;

  QPoint _mouseEventPos;
  bool _windowDragActive = false;
  bool _shouldAnimateGameStart = false;
};
} // namespace ui

#endif // LAUNCHER_MASTERWINDOW_HPP
