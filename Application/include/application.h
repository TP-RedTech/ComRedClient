#include "header.h"

#include "document.h"
#include "../../HTTPClient/include/httpClient.h"

using namespace client;

class Application {
public:
    Application(int editorId, int docId) : editorId(editorId), docId(docId),
                                           doc(new Document()), client(new client::Client("127.0.0.1", "5555")) { }

    void connect();

    void update(int cursorPos, std::string operations);

private:
    int editorId;
    int docId;
    std::shared_ptr<Document> doc;
    std::shared_ptr<client::Client> client;

    void printText() {
        std::cout << std::endl << doc->getText() << std::endl;
    }
};
