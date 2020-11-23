#ifndef GEIGERCOUNTER_CONTROLLER_INTERVAL_HANDLER_H
#define GEIGERCOUNTER_CONTROLLER_INTERVAL_HANDLER_H

#include <Arduino.h>
#include "./../LinkedList.h"

struct Interval {
    int id;
    int interval;
    int times;
    bool on;
    long timestamp;
    void (*callback)(int);
};

class IntervalHandler {

public:

    IntervalHandler();
    ~IntervalHandler();

    static int add(int interval, int times, void (*callback)(int));
    static void remove(int id);
    static void loop();

private:

    static LinkedList<struct Interval*>* intervals; 
    static int get_last_id();

};

#endif