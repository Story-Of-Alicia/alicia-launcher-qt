#include "ProgressDialog.hpp"

#include "Launcher.hpp"

#include <QGraphicsBlurEffect>
#include <QtConcurrent>
#include <QTimer>

ProgressDialog::ProgressDialog(QWidget * parent) : QDialog(parent)
{
  _ui_progressWidget.setupUi(this);
  setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
}

void ProgressDialog::begin(QWidget * blur_target, launcher::Launcher * launcher)
{
  auto geometry = dynamic_cast<QWidget*>(parent())->geometry();
  this->move(geometry.width() / 2 - this->geometry().width() / 2, geometry.height() / 2 - this->geometry().height() / 2);
  this->_target = blur_target;
  this->_launcher = launcher;

  if(_blur == nullptr)
  {
    _blur = new QGraphicsBlurEffect(this);
    _blur->setBlurHints(QGraphicsBlurEffect::PerformanceHint);
    _blur->setBlurRadius(6);
  }

  _blur->setEnabled(true);
  blur_target->setGraphicsEffect(this->_blur);
  blur_target->setDisabled(true);
  setVisible(true);

  _ui_progressWidget.l_title->setText("");
  _ui_progressWidget.l_status->setText("0%");
  _ui_progressWidget.pb_primary->setValue(0);
  _ui_progressWidget.pb_secondary->setValue(0);

  _timer = new QTimer(this);
  connect(_timer, SIGNAL(timeout()), this, SLOT(updateProgress()));
  _timer->start(1000);
}

void ProgressDialog::end()
{
  setVisible(false);
  _blur->setEnabled(false);
  _target->setDisabled(false);
  _timer->stop();
}

void ProgressDialog::updateProgress()
{
  auto primary_animation = new QPropertyAnimation(_ui_progressWidget.pb_primary, "value");
  primary_animation->setDuration(900);
  primary_animation->setStartValue(_ui_progressWidget.pb_primary->value());
  primary_animation->setEndValue(_launcher->progressTotal());
  primary_animation->setEasingCurve(QEasingCurve::Linear);
  primary_animation->start(QAbstractAnimation::DeleteWhenStopped);

  auto secondary_animation = new QPropertyAnimation(_ui_progressWidget.pb_secondary, "value");
  secondary_animation->setDuration(900);
  secondary_animation->setStartValue(_ui_progressWidget.pb_secondary->value());
  secondary_animation->setEndValue(_launcher->progress());
  secondary_animation->setEasingCurve(QEasingCurve::Linear);
  secondary_animation->start(QAbstractAnimation::DeleteWhenStopped);
}

