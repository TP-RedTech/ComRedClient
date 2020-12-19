#include "../include/application.h"

void Application::connect() {
    auto res = client->connect(editorId, docId);
    std::cout << "Connected" << std::endl;
    std::cout << "connect() res: " << res.second << std::endl << std::endl;
    printText();
}

void Application::update(int cursorPos, std::string operations) {
    auto res = client->update(editorId, docId, cursorPos, operations);
    doc->updateText(res.second);
    std::cout << "Updated" << std::endl;
    if (res.first == ClientErrors::success) {
        std::cout << "success" << std::endl;
    }
    std::cout << "update() res: " << res.second << std::endl << std::endl;
    printText();
}
