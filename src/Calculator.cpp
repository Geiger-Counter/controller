#include "Calculator.h"

int calculate_cpm_approach(LinkedList<long>* elements) {
    long timediff = elements->get(elements->size() - 1) - elements->get(0);
    if(timediff == 0) {
        return 0;
    }
    double factor = 60000 / timediff;
    return elements->size() * factor;
}

int calculate_cpm_last_minute(LinkedList<long>* elements, int index) {
    return elements->size() - index;
}

int first_index_for_timespan(LinkedList<long>* elements, int seconds) {
    long last_entry = elements->get(elements->size() - 1);
    long searched_timestamp = last_entry - (seconds * 1000);
    if(searched_timestamp < elements->get(0)) {
        return -1;
    }
    int i = elements->size() - 1;
    while(elements->get(i) > searched_timestamp) {
        i--;
    }
    return i;
}

int calculate_cpm(LinkedList<long>* elements) {
    int entry = first_index_for_timespan(elements, 60);
    if(entry < 0) {
        return calculate_cpm_approach(elements);
    } else {
        return calculate_cpm_last_minute(elements, entry);
    }
}

float calculate_msvh(int cpm) {
    return cpm/151.0;
}