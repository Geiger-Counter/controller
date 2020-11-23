#include "IntervalHandler.h"

LinkedList<struct Interval*>* IntervalHandler::intervals = new LinkedList<struct Interval*>();

IntervalHandler::IntervalHandler() {}

IntervalHandler::~IntervalHandler() {}

int IntervalHandler::add(int _interval, int _times, void (*_callback)(int)) {
    struct Interval* _n_interval = (struct Interval*)malloc(sizeof(struct Interval));
    _n_interval->id = get_last_id() + 1;
    _n_interval->interval = _interval;
    _n_interval->times = _times;
    _n_interval->on = true;
    _n_interval->timestamp = 0;
    _n_interval->callback = _callback;
    intervals->add(_n_interval);
    return _n_interval->id;
}

void IntervalHandler::remove(int id) {
    intervals->remove(id);
}

void IntervalHandler::loop() {
    unsigned long now = millis();
    for(int i = 0; i < intervals->size(); i++) {
        struct Interval* interval = intervals->get(i);
        if(interval->on) {
            if((now - interval->timestamp) > interval->interval) {
                if(interval->times > 0) {
                    interval->times--;
                }
                interval->callback(interval->times);
            }
        }
    }
}

int IntervalHandler::get_last_id() {
    int id = 0;
    int i = intervals->size() - 1;
    while(i >= 0) {
        if(intervals->get(i)->id > 0) {
            id = intervals->get(i)->id;
        }
        i--;
    }
    return id;
}