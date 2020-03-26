#ifndef BLECallbackHandler_H
#define BLECallbackHandler_H

#include <Arduino.h>
#include <BLEServer.h>

/**
 * BLECallbackHandler Class implements BLEServerCallbacks
 *
 * Callback Handler for BLEServer
 *
 * checks if device is connected to a client
 *
 */

class BLECallbackHandler : public BLEServerCallbacks
{

public:

    BLECallbackHandler();
    ~BLECallbackHandler();
    void onConnect(BLEServer* server);
    void onDisconnect(BLEServer* server);
    bool isConnected();

private:

    bool connected;

};

#endif
