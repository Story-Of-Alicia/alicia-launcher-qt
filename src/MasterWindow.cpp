#include "MasterWindow.hpp"

#include <QWidget>
#include <QMessageBox>

#include "launcher.hpp"
#include "util.hpp"

namespace Ui {
    MasterWindow::MasterWindow(QWidget *parent) : QWidget(parent) {
        _widget.setupUi(this);
        connect(_widget.pushButton, SIGNAL(clicked()), this, SLOT(launch()));
    }

    void MasterWindow::launch() {
        std::string _webInfoId = "927628CA6D76A6E9162C56D4E3E6D6E3";

        auto _webInfoContent = launcher::WebInfo{
            .gameId = "Alicia",
            .memberNo = 0,
            .loginId = "<name>",
            .authKey = "<auth_key>",
            .installUrl = "<install_url>",
            .serverType = 0,
            .serverInfo = ":",
            .sex = launcher::WebInfo::Sex::MALE,
            .birthday = "",
            .wardNo = 0,
            .cityCode = 0,
            .zipCode = "",
            .pcBangNo = 0,
            .closeTime = "",
        };

        std::string _executableProgram = "Alicia.exe";
        std::string _workdir = R"(C:\Users\martin\AppData\Local\Gametree\Alicia)";
        std::string _executableArguments = "-GameID 0";

        try {
            launcher::WebInfoHost webInfoHost;
            webInfoHost.host(_webInfoId, _webInfoContent);
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", "Couldn't host the web info.");
            return;
        }

        STARTUPINFO startupInfo{.cb = sizeof(STARTUPINFO)};
        PROCESS_INFORMATION processInfo{};

        SetCurrentDirectory(util::win32_widen(_workdir).data());
        if (!CreateProcess(
            util::win32_widen(_executableProgram).data(),
            util::win32_widen(_executableArguments).data(),
            nullptr,
            nullptr,
            FALSE,
            0,
            nullptr,
            nullptr,
            &startupInfo,
            &processInfo)) {
            if (GetLastError() == ERROR_ELEVATION_REQUIRED) {
                QMessageBox::critical(this, "Error", "Can't launch the game, elevation is required.");
            } else {
                QMessageBox::critical(this, "Error", "Can't launch the game, misc error.");
            }
            } else {
                CloseHandle(&processInfo);
                exit(0);
            }
    }
}
