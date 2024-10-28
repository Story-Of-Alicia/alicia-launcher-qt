#ifndef PROGRESSDIALOG_HPP
#define PROGRESSDIALOG_HPP

#include <QDialog>

#include "ui_ProgressWidget.h"

#include <QGraphicsBlurEffect>

class ProgressDialog : public QDialog {
  Q_OBJECT
public:
  explicit ProgressDialog(QWidget *parent = nullptr);

  Ui::ProgressWidget _ui_progressWidget = Ui::ProgressWidget();

  void begin(QWidget * blur_target, QString const & title);
  void end();
  void updatePrimary(const int &progress) const;
  void updateSecondary(const int &progress, QString const& text) const;

private:
  QGraphicsBlurEffect *blur = nullptr;
  QWidget * blur_target = nullptr;

  std::atomic_bool _shouldRun = false;
  std::atomic_int _primaryProgress = 0;
  std::atomic_int _secondaryProgress = 0;
};

#endif // PROGRESSDIALOG_HPP