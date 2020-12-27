#include "include/application.h"

void printDocumentMenu() {
    std::cout << std::endl << "[1] - Create document" << std::endl;
    std::cout << "[2] - Connect document" << std::endl << std::endl;
}

void printMainMenu() {

    std::cout << std::endl << "[1] - Current text" << std::endl;
    std::cout << "[2] - Send changes" << std::endl;
    std::cout << "[0] - Exit" << std::endl << std::endl;
}

int main(int argc, const char * argv[]) {
    int editorId = 0;
    int docId = 0;
    std::cout << "\nInput editorId: ";
    std::cin >> editorId;

    std::shared_ptr<Application> app(new Application(editorId));

    while(1) {
        printDocumentMenu();

        char inputedChoice;
        std::cin >> inputedChoice;

        if (inputedChoice == '1') {
            std::string documentName;
            std::cout << "\nInput document name: ";
            std::cin >> documentName;
            app->createDocument(documentName);
        } else if (inputedChoice == '2') {
            break;
        } else {
            std::cout << "Error input" << std::endl;
        }
    }

    std::cout << "\nInput docId: ";
    std::cin >> docId;
    app->setDocId(docId);

    auto err = app->connect();
    while(err) {
        printMainMenu();

        char inputedChoice;
        std::cin >> inputedChoice;

        switch (inputedChoice) {
            case '1': {
                app->getTextDocument();
                break;
            }
            case '2': {
                int pos = 0;
                app->getTextDocument();
                std::cout << "Enter position of cursor: ";
                std::cin >> pos ;
                std::cout << "\n";

                std::string line;
                std::cout << "Enter value: ";
                std::cin >> line;
                std::cout << "\n";

                if (line == "0") {
                    err = false;
                }
                std::string operation = std::to_string(pos) + "," + line + ",";
                if (line[0] == '-') {
                    operation += std::to_string(app->getSizeDoc() - pos + std::stoi(line));
                } else {
                    operation += std::to_string(app->getSizeDoc() - pos);
                }
                app->update(pos, operation);
                break;
            }
            default:
                err = false;
                break;
        }
    }

    std::cout << "Hello, world!" << std::endl;

    return 0;
}
