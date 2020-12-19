#include "include/application.h"

int main(int argc, const char * argv[]) {
    int editorId;
    int docId;
    std::cout << "\nInput editorId: ";
    std::cin >> editorId;

    std::cout << "\nInput docId: ";
    std::cin >> docId;

    std::shared_ptr<Application> app(new Application(editorId, docId));

    app->connect();
    while(1) {
        int pos = 0;
        std::cout << "Enter position of cursor: ";
        std::cin >> pos ;
        std::cout << "\n";

        std::string line;
        std::cout << "Enter text: ";
        std::cin >> line;
        std::cout << "\n";

        if (line == "0") {
            break;
        }
        app->update(pos, line);
    }


    std::cout << "Hello, world!" << std::endl;

    return 0;
}
