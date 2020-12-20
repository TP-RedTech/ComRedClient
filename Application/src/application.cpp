#include "../include/application.h"

void Application::connect() {
    auto res = client->connect(editorId, docId);

	if (res.first == ClientErrors::success) {
		std::cout << "success connect" << std::endl;
	} else {
		std::cout << "failure" << std::endl;
	}

    std::cout << "connect() res: " << res.second << std::endl << std::endl;
    //printText();
}

void Application::update(int cursorPos, std::string operations) {
    auto res = client->update(editorId, docId, cursorPos, operations);
    //doc->updateText(res.second);
    if (res.first == ClientErrors::success) {
        std::cout << "success update " << std::endl;
    } else {
		std::cout << "failure" << std::endl;
	}

    std::cout << "update() res: " << res.second << std::endl << std::endl;
    //printText();
}

void Application::createDocument(std::string documentName) {
    auto res = client->create(editorId, documentName);
    if (res.first == ClientErrors::success) {
    	std::cout << "created document with name: " << documentName << " and Id: " << res.second << std::endl;
    } else {
    	std::cout << "failure" << std::endl;
    }
}

void Application::saveDocument() {
    // TODO:- client->saveDocument(docId);
}

void Application::printText() {
	std::cout << std::endl << doc->getText() << std::endl;
}

void Application::getTextDocument() {
	auto res = client->getTextDocument(docId);

	if (res.first == ClientErrors::success) {
		std::cout << "success" << std::endl;
		doc->setText(res.second);
	} else {
		std::cout << "failure" << std::endl;
	}
};
