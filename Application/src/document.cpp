#include "../include/document.h"

void Document::updateText(std::string operations) {
    text += operations; // TODO: а надо ли нам обновлять, или можем просто весь текст новый получать и сетить его
}

const std::string& Document::getText() {
    return text;
}

void Document::setText(std::string newValue) {
    text = newValue;
}
