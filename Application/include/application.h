#include "header.h"

#include "document.h"
#include "../../HTTPClient/include/client.h"

class Application {
public:
    Application(int editorId, int docId) : myId(editorId), docId(docId) {
        doc = std::shared_ptr<Document>(new Document());
        client = std::shared_ptr<Client>(new Client());
    }

    void connect() {
        //client.connect(1, 1);
        std::cout << "Connected" << std::endl;
    }

    void update(int cPos, std::string operations) {
        //auto res = client->update(myId, docId, cPos, operations);
        doc->applyChanges(operations);
        std::cout << doc->getText() << std::endl;
    }

private:
    std::shared_ptr<Document> doc;
    int docId;
    int myId;
    std::shared_ptr<Client> client;
};