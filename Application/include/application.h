#include "header.h"

#include "document.h"
#include "../../HTTPClient/include/client.h"

using namespace client;

class Application {
public:
    Application(int editorId, int docId) : editorId(editorId), docId(docId),
                                           doc(new Document()), client(new client::Client("127.0.0.1", "5555")) { }

    Application(int editorId) : editorId(editorId), doc(new Document()), client(new client::Client("127.0.0.1", "5555")) { }

    bool connect();

    void disconnect();

    void update(int cursorPos, std::string operations);

    ClientOut createDocument(std::string documentName);

    void setDocId(const int& newDocId);

    ClientOut getTextDocument();

    size_t getSizeDoc() const;

private:
    int editorId;
    int docId;
    std::shared_ptr<Document> doc;
    std::shared_ptr<client::Client> client;

    void printText();

};
