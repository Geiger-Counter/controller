#include <stdio.h>
#include "./../src/LinkedList.h"

using namespace std;

int first_index_for_timespan(LinkedList<long>* elements, int seconds);
int calculate_cpm_approach(LinkedList<long>* elements);
int calculate_cpm_last_minute(LinkedList<long>* elements, int index);

int main() {
    LinkedList<long> detections = LinkedList<long>();
    detections.add(0);
    detections.add(1000);
    detections.add(3000);
    detections.add(7000);
    detections.add(8000);

    int entry_f = first_index_for_timespan(&detections, 60);
    printf("Entry under minute: %d\n", entry_f);
    int cpm_f = calculate_cpm_approach(&detections);
    printf("CPM: %d\n", cpm_f);

    detections.add(20000);
    detections.add(30000);
    detections.add(70000);
    detections.add(80000);
    int entry_n = first_index_for_timespan(&detections, 60);
    printf("Entry more than minute: %d - Is: %ld\n", entry_n, detections.get(entry_n));
    int cpm_n = calculate_cpm_last_minute(&detections, entry_n);
    printf("CPM: %d\n", cpm_n);
    return 0;
}

int calculate_cpm_approach(LinkedList<long>* elements) {
    long timediff = elements->get(elements->size() - 1) - elements->get(0);
    printf("Timediff: %ld\n", timediff);
    double factor = 60000 / timediff;
    printf("Factor: %f\n", factor);
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