/********************************************************************************
** Form generated from reading UI file 'MasterFrame.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MASTERFRAME_H
#define UI_MASTERFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MasterFrame
{
public:
    QPushButton *btn_exit;
    QLabel *l_corrupted;
    QPushButton *btn_settings;
    QLabel *l_troubleshoot;
    QLabel *l_support;
    QWidget *launcher_widget;
    QPushButton *alicia1;
    QPushButton *alicia2;
    QPushButton *btn_repair;
    QPushButton *btn_minimize;
    QPushButton *btn_ticket;
    QWidget *login_widget;
    QLabel *l_issues;

    void setupUi(QFrame *MasterFrame)
    {
        if (MasterFrame->objectName().isEmpty())
            MasterFrame->setObjectName("MasterFrame");
        MasterFrame->resize(1400, 850);
        MasterFrame->setStyleSheet(QString::fromUtf8("QFrame#MasterFrame {\n"
"	background-image: url(\":/img/bg.png\");\n"
"}\n"
"\n"
"QPushButton {\n"
"	background: transparent;\n"
"}\n"
"\n"
"QPushButton#btn_exit {\n"
"    border-image: url(:/img/btn/close.png);\n"
"    background-repeat: no-repeat;\n"
"}\n"
"\n"
"QPushButton#btn_exit:hover {\n"
"    border-image: url(:/img/btn/close_hover.png);\n"
"    background-repeat: no-repeat;\n"
"}\n"
"\n"
"QPushButton#btn_exit:pressed  {\n"
"    border-image: url(:/img/btn/close_pressed.png);\n"
"    background-repeat: no-repeat;\n"
"}\n"
"\n"
"QPushButton#btn_minimize {\n"
"    border-image: url(:/img/btn/minimize.png);\n"
"    background-repeat: no-repeat;\n"
"}\n"
"\n"
"QPushButton#btn_minimize:hover {\n"
"    border-image: url(:/img/btn/minimize_hover.png);\n"
"    background-repeat: no-repeat;\n"
"}\n"
"\n"
"QPushButton#btn_minimize:pressed  {\n"
"    border-image: url(:/img/btn/minimize_pressed.png);\n"
"    background-repeat: no-repeat;\n"
"}\n"
"\n"
"QPushButton#btn_settings {\n"
"    border-image: url(:/img/bt"
                        "n/settings.png);\n"
"    background-repeat: no-repeat;\n"
"}\n"
"QPushButton#btn_settings:hover {\n"
"    border-image: url(:/img/btn/settings_hover.png);\n"
"    background-repeat: no-repeat;\n"
"}\n"
"QPushButton#btn_settings:pressed  {\n"
"    border-image: url(:/img/btn/settings_pressed.png);\n"
"    background-repeat: no-repeat;\n"
"}\n"
"\n"
"QCheckBox {\n"
"	color: #392518;\n"
"}\n"
"\n"
"\n"
"QLabel {\n"
"	color: #4F1717;\n"
"}\n"
"\n"
"QLabel#l_story_awaits {\n"
"	color: #453327;\n"
"}\n"
"\n"
"QLabel#l_sign_up {\n"
"	color: #FF441C;\n"
"}\n"
"\n"
"\n"
"QLineEdit {\n"
"	border-radius: 3px;\n"
"	padding: 0px 25px;\n"
"}\n"
"\n"
"QWidget#MenuWidget {\n"
"	background-image: url(\":img/menu.png\");\n"
"	background-repeat: no-repeat;\n"
"}\n"
""));
        MasterFrame->setFrameShape(QFrame::Shape::StyledPanel);
        MasterFrame->setFrameShadow(QFrame::Shadow::Raised);
        btn_exit = new QPushButton(MasterFrame);
        btn_exit->setObjectName("btn_exit");
        btn_exit->setGeometry(QRect(1318, 41, 36, 36));
        btn_exit->setAutoFillBackground(false);
        btn_exit->setText(QString::fromUtf8(""));
        btn_exit->setIconSize(QSize(26, 26));
        btn_exit->setFlat(true);
        l_corrupted = new QLabel(MasterFrame);
        l_corrupted->setObjectName("l_corrupted");
        l_corrupted->setGeometry(QRect(765, 593, 141, 16));
        QFont font;
        font.setFamilies({QString::fromUtf8("NanumGothic")});
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        l_corrupted->setFont(font);
        btn_settings = new QPushButton(MasterFrame);
        btn_settings->setObjectName("btn_settings");
        btn_settings->setGeometry(QRect(85, 742, 48, 48));
        btn_settings->setText(QString::fromUtf8(""));
        btn_settings->setIconSize(QSize(72, 51));
        btn_settings->setFlat(true);
        l_troubleshoot = new QLabel(MasterFrame);
        l_troubleshoot->setObjectName("l_troubleshoot");
        l_troubleshoot->setGeometry(QRect(765, 569, 171, 21));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("EurostileBla")});
        font1.setPointSize(14);
        font1.setWeight(QFont::Black);
        l_troubleshoot->setFont(font1);
        l_troubleshoot->setText(QString::fromUtf8("TROUBLESHOOT"));
        l_support = new QLabel(MasterFrame);
        l_support->setObjectName("l_support");
        l_support->setGeometry(QRect(1021, 569, 171, 21));
        l_support->setFont(font1);
        l_support->setText(QString::fromUtf8("SUPPORT"));
        launcher_widget = new QWidget(MasterFrame);
        launcher_widget->setObjectName("launcher_widget");
        launcher_widget->setEnabled(true);
        launcher_widget->setGeometry(QRect(724, 245, 496, 272));
        alicia1 = new QPushButton(MasterFrame);
        alicia1->setObjectName("alicia1");
        alicia1->setEnabled(true);
        alicia1->setGeometry(QRect(60, 500, 102, 105));
        alicia1->setText(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/tmp/game_selected_1.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        alicia1->setIcon(icon);
        alicia1->setIconSize(QSize(102, 105));
        alicia1->setFlat(true);
        alicia2 = new QPushButton(MasterFrame);
        alicia2->setObjectName("alicia2");
        alicia2->setEnabled(true);
        alicia2->setGeometry(QRect(60, 620, 102, 105));
        alicia2->setText(QString::fromUtf8(""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/game_select_locked.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        alicia2->setIcon(icon1);
        alicia2->setIconSize(QSize(102, 105));
        alicia2->setFlat(true);
        btn_repair = new QPushButton(MasterFrame);
        btn_repair->setObjectName("btn_repair");
        btn_repair->setGeometry(QRect(765, 623, 160, 32));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/btn/repair.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_repair->setIcon(icon2);
        btn_repair->setIconSize(QSize(160, 32));
        btn_minimize = new QPushButton(MasterFrame);
        btn_minimize->setObjectName("btn_minimize");
        btn_minimize->setGeometry(QRect(1268, 41, 36, 36));
        btn_minimize->setText(QString::fromUtf8(""));
        btn_minimize->setIconSize(QSize(26, 26));
        btn_minimize->setFlat(true);
        btn_ticket = new QPushButton(MasterFrame);
        btn_ticket->setObjectName("btn_ticket");
        btn_ticket->setGeometry(QRect(1021, 623, 160, 32));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/btn/ticket.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_ticket->setIcon(icon3);
        btn_ticket->setIconSize(QSize(160, 32));
        login_widget = new QWidget(MasterFrame);
        login_widget->setObjectName("login_widget");
        login_widget->setEnabled(true);
        login_widget->setGeometry(QRect(725, 245, 496, 272));
        l_issues = new QLabel(MasterFrame);
        l_issues->setObjectName("l_issues");
        l_issues->setGeometry(QRect(1021, 593, 141, 16));
        l_issues->setFont(font);

        retranslateUi(MasterFrame);

        QMetaObject::connectSlotsByName(MasterFrame);
    } // setupUi

    void retranslateUi(QFrame *MasterFrame)
    {
        MasterFrame->setWindowTitle(QCoreApplication::translate("MasterFrame", "Frame", nullptr));
        l_corrupted->setText(QCoreApplication::translate("MasterFrame", "Corrupted files?", nullptr));
        btn_repair->setText(QString());
        btn_ticket->setText(QString());
        l_issues->setText(QCoreApplication::translate("MasterFrame", "Ran into issues?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MasterFrame: public Ui_MasterFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MASTERFRAME_H
