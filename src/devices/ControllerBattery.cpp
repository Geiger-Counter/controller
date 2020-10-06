#include "ControllerBattery.h"

ControllerBattery::ControllerBattery() {
    loading = false;
}

ControllerBattery::~ControllerBattery() {}

float ControllerBattery::get_percentage() {
    return 100.0;
}

bool ControllerBattery::is_loading() {
    return loading;
}