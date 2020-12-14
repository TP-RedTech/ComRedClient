#ifndef COMREDCLIENT_DOCUMENT_H
#define COMREDCLIENT_DOCUMENT_H

class Document {
public:
    Document() {}

    void applyChanges(std::string operations);
    const std::string &getText() {
        return text;
    }
private:
    std::string text;
};

#endif //COMREDCLIENT_DOCUMENT_H
