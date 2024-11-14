#ifndef PROGRESSDIALOG_HPP
#define PROGRESSDIALOG_HPP
#include "Launcher.hpp"
#include "ui_ProgressWidget.h"

#include <QDialog>
#include <QGraphicsBlurEffect>

class ProgressDialog : public QDialog {
  Q_OBJECT
public:
  explicit ProgressDialog(QWidget *parent = nullptr);

  Ui::ProgressWidget _ui_progressWidget = Ui::ProgressWidget();

  void begin(QWidget * blur_target, launcher::Launcher * launcher);
  void end();

private slots:
  void updateProgress();

private:
  QGraphicsBlurEffect *_blur = nullptr;
  QWidget * _target = nullptr;
  launcher::Launcher * _launcher = nullptr;
  QTimer * _timer = nullptr;
};

#endif // PROGRESSDIALOG_HPP