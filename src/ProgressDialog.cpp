#include "ProgressDialog.hpp"

#include <QGraphicsBlurEffect>

ProgressDialog::ProgressDialog(QWidget * parent) : QDialog(parent)
{
  _ui_progressWidget.setupUi(this);
  this->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
  blur = new QGraphicsBlurEffect(this);
  blur->setBlurRadius(3);
  blur->setEnabled(false);
}

void ProgressDialog::begin(QWidget * blur_target)
{
  auto geometry = dynamic_cast<QWidget*>(parent())->geometry();
  this->move(geometry.width() / 2 - this->geometry().width() / 2, geometry.height() / 2 - this->geometry().height() / 2);

  this->blur_target = blur_target;

  blur->setEnabled(true);
  blur_target->setGraphicsEffect(this->blur);
  blur_target->setDisabled(true);

  setVisible(true);
}
void ProgressDialog::end()
{
  setVisible(false);
  blur->setEnabled(false);
  blur_target->setDisabled(false);
}

void ProgressDialog::update(const int &progress, QString const& text)
{
  if (progress == 100)
  {
    end();
  }
  _ui_progressWidget.l_title->setText(text);
  _ui_progressWidget.l_status->setText(QString("%1%").arg(progress));
  _ui_progressWidget.progressBar->setValue(progress);
}
