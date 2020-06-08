#ifndef GEIGERCOUNTER_SERVICE_CALLBACK_HANDLER_H
#define GEIGERCOUNTER_SERVICE_CALLBACK_HANDLER_H

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

class ServiceCallbackHandler : public BLEServerCallbacks
{

public:

    ServiceCallbackHandler();
    ~ServiceCallbackHandler();
    void onConnect(BLEServer* server);
    void onDisconnect(BLEServer* server);
    bool isConnected();

private:

    bool connected;

};

#endif
