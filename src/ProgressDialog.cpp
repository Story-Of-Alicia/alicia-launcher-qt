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
  _ui_progressWidget.l_status->setText("");
  _ui_progressWidget.pb_primary->setValue(0);
  _ui_progressWidget.pb_secondary->setValue(0);

  if (_timer == nullptr)
  {
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateProgress()));

  }
  _timer->start(100);
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
  if (_launcher->isUpdatePaused())
  {
    return;
  }

  if (_launcher->progressTotal() == 100)
  {
    _ui_progressWidget.l_title->setText("FINISHED");
  } else
  {
    if(_launcher->state() == launcher::State::DOWNLOADING)
    {
      _ui_progressWidget.l_title->setText(QString("DOWNLOADING (%1 left)").arg(_launcher->countToDownload()));
    } else
    {
      _ui_progressWidget.l_title->setText(QString("PATCHING (%1 left)").arg(_launcher->countToPatch()));
    }
  }

  _ui_progressWidget.l_status->setText("DOPICE");

  //TODO: when progress == 0 animate going back to zero after a while
  auto primary_forward = new QPropertyAnimation(_ui_progressWidget.pb_primary, "value");
  primary_forward->setDuration(100);
  primary_forward->setStartValue(_ui_progressWidget.pb_primary->value());
  primary_forward->setEndValue(_launcher->progressTotal());
  primary_forward->setEasingCurve(QEasingCurve::Linear);
  primary_forward->start(QAbstractAnimation::DeleteWhenStopped);

  auto secondary_forward = new QPropertyAnimation(_ui_progressWidget.pb_secondary, "value");
  secondary_forward->setDuration(100);
  secondary_forward->setStartValue(_ui_progressWidget.pb_secondary->value());
  secondary_forward->setEndValue(_launcher->progress());
  secondary_forward->setEasingCurve(QEasingCurve::Linear);
  secondary_forward->start(QAbstractAnimation::DeleteWhenStopped);
}

