#ifndef LAUNCHER_MASTERWINDOW_HPP
#define LAUNCHER_MASTERWINDOW_HPP

#include "ui_MasterWindow.h"
namespace Ui {
    class MasterWindow final : public QWidget {
        Q_OBJECT
        public:
        explicit MasterWindow(QWidget *parent = nullptr);
        private slots:
            void launch();

    private:
        MasterWindowWidget _widget{};
    };
}


#endif // LAUNCHER_MASTERWINDOW_HPP