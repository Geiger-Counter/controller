#ifndef API_H
#define API_H

#include <Arduino.h>
#include "Settings.h"
#include "LinkedList.h"

bool send_data(struct Settings* settings, LinkedList<long> data);

#endif
