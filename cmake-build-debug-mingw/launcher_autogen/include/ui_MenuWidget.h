/********************************************************************************
** Form generated from reading UI file 'MenuWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUWIDGET_H
#define UI_MENUWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuWidget
{
public:
    QPushButton *btn_logout;
    QLabel *l_last_login;
    QLabel *l_guild;
    QLabel *l_level;
    QLabel *l_player;
    QPushButton *btn_info;
    QLabel *l_last_login_d;
    QLabel *l_player_d;
    QLabel *l_level_d;
    QLabel *l_guild_d;
    QLabel *label;
    QLabel *l_username_d;

    void setupUi(QWidget *MenuWidget)
    {
        if (MenuWidget->objectName().isEmpty())
            MenuWidget->setObjectName("MenuWidget");
        MenuWidget->resize(545, 331);
        MenuWidget->setStyleSheet(QString::fromUtf8("QWidget#MenuWidget {\n"
"	background-image: url(\":tmp/MENU_preview.png\");\n"
"	background-repeat: no-repeat;\n"
"}"));
        btn_logout = new QPushButton(MenuWidget);
        btn_logout->setObjectName("btn_logout");
        btn_logout->setGeometry(QRect(40, 204, 116, 36));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/btn/logout.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_logout->setIcon(icon);
        btn_logout->setIconSize(QSize(116, 364));
        l_last_login = new QLabel(MenuWidget);
        l_last_login->setObjectName("l_last_login");
        l_last_login->setGeometry(QRect(215, 209, 171, 21));
        QFont font;
        font.setFamilies({QString::fromUtf8("NanumGothic")});
        font.setPointSize(11);
        font.setBold(true);
        l_last_login->setFont(font);
        l_guild = new QLabel(MenuWidget);
        l_guild->setObjectName("l_guild");
        l_guild->setGeometry(QRect(213, 160, 49, 16));
        l_guild->setFont(font);
        l_level = new QLabel(MenuWidget);
        l_level->setObjectName("l_level");
        l_level->setGeometry(QRect(217, 132, 49, 16));
        l_level->setFont(font);
        l_player = new QLabel(MenuWidget);
        l_player->setObjectName("l_player");
        l_player->setGeometry(QRect(209, 103, 49, 16));
        l_player->setFont(font);
        btn_info = new QPushButton(MenuWidget);
        btn_info->setObjectName("btn_info");
        btn_info->setGeometry(QRect(376, 43, 100, 37));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/btn/info.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_info->setIcon(icon1);
        btn_info->setIconSize(QSize(100, 37));
        l_last_login_d = new QLabel(MenuWidget);
        l_last_login_d->setObjectName("l_last_login_d");
        l_last_login_d->setGeometry(QRect(288, 212, 141, 16));
        l_last_login_d->setFont(font);
        l_player_d = new QLabel(MenuWidget);
        l_player_d->setObjectName("l_player_d");
        l_player_d->setGeometry(QRect(267, 104, 49, 16));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("EurostileBla")});
        font1.setPointSize(13);
        font1.setBold(true);
        l_player_d->setFont(font1);
        l_level_d = new QLabel(MenuWidget);
        l_level_d->setObjectName("l_level_d");
        l_level_d->setGeometry(QRect(266, 132, 49, 16));
        l_level_d->setFont(font1);
        l_guild_d = new QLabel(MenuWidget);
        l_guild_d->setObjectName("l_guild_d");
        l_guild_d->setGeometry(QRect(267, 161, 151, 16));
        l_guild_d->setFont(font1);
        label = new QLabel(MenuWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(48, 45, 111, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("NanumGothic")});
        font2.setPointSize(18);
        font2.setBold(true);
        label->setFont(font2);
        l_username_d = new QLabel(MenuWidget);
        l_username_d->setObjectName("l_username_d");
        l_username_d->setGeometry(QRect(160, 50, 49, 21));

        retranslateUi(MenuWidget);

        QMetaObject::connectSlotsByName(MenuWidget);
    } // setupUi

    void retranslateUi(QWidget *MenuWidget)
    {
        MenuWidget->setWindowTitle(QCoreApplication::translate("MenuWidget", "Form", nullptr));
        btn_logout->setText(QString());
        l_last_login->setText(QCoreApplication::translate("MenuWidget", "last login", nullptr));
        l_guild->setText(QCoreApplication::translate("MenuWidget", "Guild", nullptr));
        l_level->setText(QCoreApplication::translate("MenuWidget", "Level", nullptr));
        l_player->setText(QCoreApplication::translate("MenuWidget", "Player", nullptr));
        btn_info->setText(QString());
        l_last_login_d->setText(QCoreApplication::translate("MenuWidget", "12-09-24  10:49 PM", nullptr));
        l_player_d->setText(QCoreApplication::translate("MenuWidget", "Alicia", nullptr));
        l_level_d->setText(QCoreApplication::translate("MenuWidget", "1", nullptr));
        l_guild_d->setText(QCoreApplication::translate("MenuWidget", "Not joined yet", nullptr));
        label->setText(QCoreApplication::translate("MenuWidget", "Welcome,", nullptr));
        l_username_d->setText(QCoreApplication::translate("MenuWidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MenuWidget: public Ui_MenuWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUWIDGET_H
