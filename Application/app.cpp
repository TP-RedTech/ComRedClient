#include "include/application.h"

void printMenu() {
    std::cout << std::endl << "[1] - Create document" << std::endl;
    std::cout << "[2] - Current text" << std::endl;
    std::cout << "[3] - Send changes" << std::endl;
    std::cout << "[0] - Exit" << std::endl << std::endl;
}

int main(int argc, const char * argv[]) {
    int editorId = 0;
    int docId = 0;
    std::cout << "\nInput editorId: ";
    std::cin >> editorId;

    std::shared_ptr<Application> app(new Application(editorId));

    std::cout << "\nInput docId: ";
    std::cin >> docId;
    app->setDocId(docId);

    bool err = app->connect();
    while(err) {
        printMenu();

        char inputedChoice;
        std::cin >> inputedChoice;

        switch (inputedChoice) {
            case '1': {
                std::string documentName;
                std::cout << "\nInput document name: ";
                std::cin >> documentName;
                app->createDocument(documentName);
                break;
            }
            case '2': {
                app->getTextDocument();
                break;
            }
            case '3': {
                int pos = 0;
                std::cout << "Enter position of cursor: ";
                std::cin >> pos ;
                std::cout << "\n";

                std::string line;
                std::cout << "Enter text: ";
                std::cin >> line;
                std::cout << "\n";

                if (line == "0") {
                    err = false;
                }
                app->update(pos, line);
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
