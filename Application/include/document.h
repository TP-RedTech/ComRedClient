#ifndef COMREDCLIENT_DOCUMENT_H
#define COMREDCLIENT_DOCUMENT_H

#include "header.h"

class Document {
public:
    Document() {}

    void updateText(std::string operations);

    const std::string &getText();

    void setText(std::string newValue);

private:
    std::string text;
};

#endif //COMREDCLIENT_DOCUMENT_H
