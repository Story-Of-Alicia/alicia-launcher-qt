#ifndef LAUNCHER_MASTERWINDOW_HPP
#define LAUNCHER_MASTERWINDOW_HPP

#include "ui_MasterFrame.h"
#include "ui_LoginWidget.h"
#include "ui_MenuWidget.h"

#include <QMouseEvent>

namespace Ui {
    class MasterWidget final : public QWidget {
        Q_OBJECT
        public:
        explicit MasterWidget(QWidget *parent = nullptr);
        private slots:
            void handle_btn_exit();
            void handle_btn_launch();
            void handle_login();

    private:
        QFrame *master_frame = new QFrame(this);
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