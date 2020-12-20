#include "header.h"

#include "document.h"
#include "../../HTTPClient/include/client.h"

using namespace client;

class Application {
public:
    Application(int editorId, int docId) : editorId(editorId), docId(docId),
                                           doc(new Document()), client(new client::Client("127.0.0.1", "5555")) { }

	Application(int editorId) : editorId(editorId), doc(new Document()), client(new client::Client("127.0.0.1", "5555")) { }

    void connect();

    void update(int cursorPos, std::string operations);

    void saveDocument();

    void createDocument(std::string documentName);

private:
    int editorId;
    int docId;
    std::shared_ptr<Document> doc;
    std::shared_ptr<client::Client> client;

    // TODO: перенести нижние методы в public, как они будут готовы к использованию

    void printText();

    void getTextDocument();
};
