#include "ProgressDialog.hpp"

#include <QGraphicsBlurEffect>
#include <QtConcurrent>

ProgressDialog::ProgressDialog(QWidget * parent) : QDialog(parent)
{
  _ui_progressWidget.setupUi(this);
  this->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
  blur = new QGraphicsBlurEffect(this);
  blur->setBlurRadius(3);
  blur->setEnabled(false);
}

void ProgressDialog::begin(QWidget * blur_target, QString const & title)
{
  auto geometry = dynamic_cast<QWidget*>(parent())->geometry();
  this->move(geometry.width() / 2 - this->geometry().width() / 2, geometry.height() / 2 - this->geometry().height() / 2);
  this->blur_target = blur_target;

  blur->setEnabled(true);
  blur_target->setGraphicsEffect(this->blur);
  blur_target->setDisabled(true);
  setVisible(true);

  _ui_progressWidget.l_title->setText(title);
  _ui_progressWidget.l_status->setText("0%");
  _ui_progressWidget.pb_primary->setValue(0);
  _ui_progressWidget.pb_secondary->setValue(0);
}
void ProgressDialog::end()
{
  setVisible(false);
  blur->setBlurHints(QGraphicsBlurEffect::PerformanceHint);
  blur->setEnabled(false);
  blur_target->setDisabled(false);
}

void ProgressDialog::updateSecondary(const int& progress, QString const& text) const
{
  _ui_progressWidget.l_title->setText(text);
  auto animation = new QPropertyAnimation(_ui_progressWidget.pb_secondary, "value");
  animation->setDuration(100);
  animation->setStartValue(_ui_progressWidget.pb_secondary->value());
  animation->setEndValue(progress);
  animation->setEasingCurve(QEasingCurve::Linear);
  animation->start(QAbstractAnimation::DeleteWhenStopped);
}


void ProgressDialog::updatePrimary(const int& progress) const
{
  _ui_progressWidget.l_status->setText(QString("%1%").arg(progress));
  auto animation = new QPropertyAnimation(_ui_progressWidget.pb_primary, "value");
  animation->setDuration(100);
  animation->setStartValue(_ui_progressWidget.pb_primary->value());
  animation->setEndValue(progress);
  animation->setEasingCurve(QEasingCurve::Linear);
  animation->start(QAbstractAnimation::DeleteWhenStopped);
}
