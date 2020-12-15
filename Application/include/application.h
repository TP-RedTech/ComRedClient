#include "header.h"

#include "document.h"
#include "../../HTTPClient/include/client.h"

class Application {
public:
    Application(int editorId, int docId) : editorId(editorId), docId(docId) {
        doc = std::shared_ptr<Document>(new Document());
        client = std::shared_ptr<Client>(new Client());
    }

    void connect();

    void update(int cursorPos, std::string operations);

private:
    int editorId;
    int docId;
    std::shared_ptr<Document> doc;
    std::shared_ptr<Client> client;
};
