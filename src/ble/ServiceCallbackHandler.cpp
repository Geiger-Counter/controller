#include "ServiceCallbackHandler.h"

ServiceCallbackHandler::ServiceCallbackHandler() {
    connected = false;
}

ServiceCallbackHandler::~ServiceCallbackHandler() {};

void ServiceCallbackHandler::onConnect(BLEServer* server) {
    connected = true;
};

void ServiceCallbackHandler::onDisconnect(BLEServer* server) {
    connected = false;
}

bool ServiceCallbackHandler::isConnected() {
    return connected;
}

