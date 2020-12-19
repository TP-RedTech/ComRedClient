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
        std::string line;
        std::cin >> line;
        if (line == "0") {
            break;
        }
        app->update(0, line);
    }


    std::cout << "Hello, world!" << std::endl;

    return 0;
}
