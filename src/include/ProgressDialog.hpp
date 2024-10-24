#ifndef PROGRESSDIALOG_HPP
#define PROGRESSDIALOG_HPP

#include <QDialog>

#include "ui_ProgressWidget.h"

#include <QGraphicsBlurEffect>

class ProgressDialog : public QDialog {
  Q_OBJECT
public:
  explicit ProgressDialog(QWidget *parent = nullptr);

  void begin(QWidget * blur_target);
  void end();
  void update(const int &progress, QString const& text);

private:
  Ui::ProgressWidget _ui_progressWidget = Ui::ProgressWidget();
  QGraphicsBlurEffect *blur = nullptr;
  QWidget * blur_target = nullptr;
};

#endif // PROGRESSDIALOG_HPP