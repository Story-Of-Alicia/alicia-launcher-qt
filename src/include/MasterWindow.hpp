#ifndef LAUNCHER_MASTERWINDOW_HPP
#define LAUNCHER_MASTERWINDOW_HPP

#include "ui_MasterWindow.h"

#include <QMouseEvent>

namespace Ui {
    class MasterWindow final : public QWidget {
        Q_OBJECT
        public:
        explicit MasterWindow(QWidget *parent = nullptr);
        private slots:
            void handle_btn_exit();
            void handle_btn_launch();

    private:
        MasterWindowWidget _widget{};
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        QPoint _mouseEventPos;
        bool   _windowDragActive = false;
    };
}


#endif // LAUNCHER_MASTERWINDOW_HPP