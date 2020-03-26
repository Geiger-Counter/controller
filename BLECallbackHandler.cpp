#include "BLECallbackHandler.h"

BLECallbackHandler::BLECallbackHandler()
{
    connected = false;
}

BLECallbackHandler::~BLECallbackHandler() {};

void BLECallbackHandler::onConnect(BLEServer* server) {
    connected = true;
};

void BLECallbackHandler::onDisconnect(BLEServer* server) {
    connected = false;
}

bool BLECallbackHandler::isConnected() {
    return connected;
}

