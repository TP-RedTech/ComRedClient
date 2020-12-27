#include "../include/application.h"

bool Application::connect() {
    auto res = client->connect(editorId, docId);

    if (res.first == ClientErrors::success) {
        std::cout << "connect() res: " << res.second << std::endl << std::endl;
        return true;
    } else {
        std::cout << "failure connect" << std::endl;
        return false;
    }
}

void Application::disconnect() {
    auto res = client->disconnect(editorId, docId);
}

void Application::update(int cursorPos, std::string operations) {
    auto res = client->update(editorId, docId, cursorPos, operations);
    std::cout << "update(): " << res.second << std::endl << std::endl;
    if (res.first == ClientErrors::success) {
        this->getTextDocument();
    }
}

ClientOut Application::createDocument(std::string documentName) {
    auto res = client->create(editorId, documentName);
    if (res.first == ClientErrors::success) {
        std::cout << res.second << std::endl;
    } else {
        std::cout << res.second << std::endl;
    }
    return res;
}

void Application::printText() {
    std::cout << std::endl << doc->getText() << std::endl;
}

ClientOut Application::getTextDocument() {
    auto res = client->getTextDocument(docId);

    if (res.first == ClientErrors::success) {
        doc->setText(res.second);
        std::cout << "Current text: " << doc->getText() << std::endl;
        doc->setSize(doc->getText().size());
    } else {
        std::cout << res.second << std::endl;
    }

    return res;
}

void Application::setDocId(const int &newDocId) {
    docId = newDocId;
}

size_t Application::getSizeDoc() const {
    return doc->getSize();
}
