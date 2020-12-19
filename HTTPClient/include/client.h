#ifndef HTTPCLIENT_INCLUDE_CLIENT_H
#define HTTPCLIENT_INCLUDE_CLIENT_H

#include <string>
#include <utility>
#include <memory>

namespace client {
enum class ClientErrors {
    success,
    failure
};

using ClientOut = std::pair<ClientErrors, std::string>;

class Client {
public:
    ClientOut connect(int editorId, int docId);
    ClientOut update(int editorId, int docId, int cursorPos, std::string operations);
    ClientOut deleteDoc(int editorId, int docId);
};
}

class Document {
public:
    void applyChanges(std::string operations);
    const std::string &text() {
        return text;
    }
private:
    std::string text;
};

class Application {
public:
    Application(int editorId, int docId) : myId(editorId), docId(docId) {}
    
    void connect() {
        client.connect(1, 1);
        std::cout << "Connected" << std::endl;
    }
    
    void update(int cPos, std::string operations) {
        auto res = client->update(myId, docId, cPos, operations);
        doc->applyChanges(res.second);
        std::cout << doc->text() << endl;
    }
    
private:
    std::shared_ptr<Document> doc;
    int docId;
    int myId;
    std::shared_ptr<Client> client;
};
#endif
