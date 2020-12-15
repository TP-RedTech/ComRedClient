#include "../include/document.h"

void Document::updateText(std::string operations) {
    text += operations;
}

const std::string& Document::getText() {
    return text;
}

void Document::setText(std::string newValue) {
    text = newValue;
}
