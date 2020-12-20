#ifndef CLIENT_INCLUDE_CLIENT_H
#define CLIENT_INCLUDE_CLIENT_H

#include "httpClient.h"

namespace client {
enum class ClientErrors {
  success,
  failure
};

using ClientOut = std::pair<ClientErrors, std::string>;

class Client {
public:
  Client(std::string host, std::string port) : rs(host, port) {}

  ClientOut update(int editorId, int docId, int cursorPos, const std::string &operations);

  ClientOut connect(int editorId, int docId);

  ClientOut create(int editorId, const std::string &documentName);

  ClientOut getTextDocument(int docId);

private:
  ClientOut _getResponse(const std::string &target, std::string body);

private:
  RequestSender rs;
};
}

#endif
