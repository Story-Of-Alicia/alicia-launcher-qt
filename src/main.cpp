#include "MasterWidget.hpp"

#include "launcher.hpp"

int main(int argc, char** argv) {
    QApplication application(argc, argv);

    Ui::MasterWidget window{};
    window.show();

    return QApplication::exec();
}


