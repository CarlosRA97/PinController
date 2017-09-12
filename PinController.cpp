#include "PinController.h"

PinController::PinController(int eeAddr, int pin) {
    init(eeAddr, pin);
}

int PinController::GetState() {
    return readFromEEPROM();
}

void PinController::SetState(int state) {
    writeToEEPROM(state);
}

int PinController::GetPin() {
    return this->pin;
}

void PinController::On() {
    SetState(HIGH);
    dWrite();
}

void PinController::Off() {
    SetState(LOW);
    dWrite();
}

void PinController::Toggle() {
    switch (GetState()) {
        case LOW:
            On();
            break;
        case HIGH:
            Off();
            break;
        default:
            break;
    }
}
