/********************************************************************************
** Form generated from reading UI file 'LoginWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWidget
{
public:
    QLabel *l_story_awaits;
    QPushButton *btn_login;
    QLabel *l_sign_up;
    QLineEdit *input_username;
    QCheckBox *check_remember;
    QLineEdit *input_password;

    void setupUi(QWidget *LoginWidget)
    {
        if (LoginWidget->objectName().isEmpty())
            LoginWidget->setObjectName("LoginWidget");
        LoginWidget->resize(664, 300);
        LoginWidget->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"	color: #392518;\n"
"}\n"
"QLabel#l_story_awaits {\n"
"	color: #453327;\n"
"}\n"
"\n"
"QLabel#l_sign_up {\n"
"	color: #FF441C;\n"
"}\n"
"\n"
"QLineEdit {\n"
"	border-radius: 3px;\n"
"	padding: 0px 25px;\n"
"}"));
        l_story_awaits = new QLabel(LoginWidget);
        l_story_awaits->setObjectName("l_story_awaits");
        l_story_awaits->setGeometry(QRect(260, 220, 140, 20));
        QFont font;
        font.setFamilies({QString::fromUtf8("NanumGothic")});
        font.setPointSize(13);
        font.setBold(true);
        font.setStyleStrategy(QFont::PreferAntialias);
        l_story_awaits->setFont(font);
        btn_login = new QPushButton(LoginWidget);
        btn_login->setObjectName("btn_login");
        btn_login->setGeometry(QRect(351, 40, 112, 111));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/btn/login.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_login->setIcon(icon);
        btn_login->setIconSize(QSize(112, 111));
        l_sign_up = new QLabel(LoginWidget);
        l_sign_up->setObjectName("l_sign_up");
        l_sign_up->setGeometry(QRect(402, 217, 63, 22));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("EurostileBla")});
        font1.setPointSize(13);
        font1.setBold(true);
        font1.setUnderline(true);
        l_sign_up->setFont(font1);
        input_username = new QLineEdit(LoginWidget);
        input_username->setObjectName("input_username");
        input_username->setGeometry(QRect(32, 40, 304, 48));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("EurostileBla")});
        font2.setPointSize(16);
        input_username->setFont(font2);
        check_remember = new QCheckBox(LoginWidget);
        check_remember->setObjectName("check_remember");
        check_remember->setGeometry(QRect(32, 184, 151, 20));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("NanumGothic")});
        font3.setPointSize(13);
        font3.setBold(true);
        check_remember->setFont(font3);
        check_remember->setChecked(true);
        input_password = new QLineEdit(LoginWidget);
        input_password->setObjectName("input_password");
        input_password->setGeometry(QRect(32, 104, 304, 48));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Eurostile")});
        font4.setPointSize(16);
        font4.setWeight(QFont::Black);
        input_password->setFont(font4);
        input_password->setEchoMode(QLineEdit::EchoMode::Password);

        retranslateUi(LoginWidget);

        QMetaObject::connectSlotsByName(LoginWidget);
    } // setupUi

    void retranslateUi(QWidget *LoginWidget)
    {
        LoginWidget->setWindowTitle(QCoreApplication::translate("LoginWidget", "Form", nullptr));
        l_story_awaits->setText(QCoreApplication::translate("LoginWidget", "Your Story awaits!", nullptr));
        btn_login->setText(QString());
        l_sign_up->setText(QCoreApplication::translate("LoginWidget", "Sign Up", nullptr));
        input_username->setText(QString());
        input_username->setPlaceholderText(QCoreApplication::translate("LoginWidget", "USERNAME", nullptr));
        check_remember->setText(QCoreApplication::translate("LoginWidget", "Remember me", nullptr));
        input_password->setPlaceholderText(QCoreApplication::translate("LoginWidget", "PASSWORD", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWidget: public Ui_LoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
