#include "include/application.h"

int main(int argc, const char * argv[]) {
    int editorId = 0;
    int docId = 0;
    std::cout << "\nInput editorId: ";
    std::cin >> editorId;

	std::shared_ptr<Application> app(new Application(editorId));

    std::string documentName;
	std::cout << "\nInput document name: ";
	std::cin >> documentName;
	app->createDocument(documentName);

	std::cout << "\nInput docId: ";
	std::cin >> docId;

    //std::shared_ptr<Application> app(new Application(editorId, docId));
	// TODO: при коннекте он хочет создать документ, даже если его не нужно создавать
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
