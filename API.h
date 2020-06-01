#ifndef _API_H
#define _API_H

#include <Arduino.h>
#include <HTTPClient.h>
#include "Settings.h"
#include "LinkedList.h"

bool send_data(struct Settings* settings, LinkedList<long> data);
char* parse_json(char* username, char* token, LinkedList<long> data);

#endif
