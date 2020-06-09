#ifndef GEIGERCOUNTER_API_H
#define GEIGERCOUNTER_API_H

#include <Arduino.h>
#include <HTTPClient.h>
#include "./../Settings.h"
#include "./../LinkedList.h"

bool send_data(struct Settings* settings, LinkedList<long>* data);
String parse_json(const char* username, const char* token, LinkedList<long>* data);

#endif
