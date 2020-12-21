#ifndef COMREDCLIENT_DOCUMENT_H
#define COMREDCLIENT_DOCUMENT_H

#include "header.h"

class Document {
public:
    Document() {}

    void updateText(std::string operations);

    const std::string &getText();

    void setText(std::string newValue);

    size_t getSize() const;

    void setSize(const size_t& newSize);

private:
    std::string text;
    size_t size;
};

#endif //COMREDCLIENT_DOCUMENT_H
