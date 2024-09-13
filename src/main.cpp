#include "MasterWindow.hpp"

#include "launcher.hpp"

int main(int argc, char** argv) {
    QApplication application(argc, argv);

    Ui::MasterWindow window{};
    window.show();

    return QApplication::exec();
}


