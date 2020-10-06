#ifndef GEIGERCOUNTER_CALCULATOR_H
#define GEIGERCOUNTER_CALCULATOR_H

#include "LinkedList.h"

int first_index_for_timespan(LinkedList<long>* elements, int seconds);
int calculate_cpm_approach(LinkedList<long>* elements);
int calculate_cpm_last_minute(LinkedList<long>* elements, int index);
int calculate_cpm(LinkedList<long>* elements);
float calculate_msvh(int cpm);

#endif