#ifndef LAUNCHER_MASTERWINDOW_HPP
#define LAUNCHER_MASTERWINDOW_HPP

#include "ui_MasterFrame.h"
#include "ui_LoginWidget.h"
#include "ui_MenuWidget.h"

#include <QMouseEvent>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

using namespace Ui;

namespace ui {
    int start(int argc, char *argv[]);

    class Window final : public QWidget {
        Q_OBJECT
        public:
        explicit Window(QWidget *parent = nullptr);
        private slots:
            void handle_exit();
            void handle_launch();
            void handle_login();
            void handle_authenticate();
            void handle_logout();
            void handle_info();
            void handle_repair();
            void handle_ticket();
            void handle_minimize();
            void handle_settings();
            void cb_logged();
        signals:
            void login_finished();

    private:
        QFrame *master_frame = new QFrame(this);
        QNetworkAccessManager *networkManager;
        QNetworkReply* currentReply = nullptr;
        MasterFrame _masterFrameUI{};
        LoginWidget _loginWidgetUI{};
        MenuWidget _menuWidgetUI{};
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        QPoint _mouseEventPos;
        bool   _windowDragActive = false;
    };
}


#endif // LAUNCHER_MASTERWINDOW_HPP