#include "PinController.h"


PinController::PinController(int eeAddr, int pin) {
    init(eeAddr, pin);
}

// Obtiene el estado del rele leyendolo de la memoria EEPROM
int PinController::GetState() {
    return readFromEEPROM();
}
// Establece el estado del rele y lo guarda en la memoria EEPROM
void PinController::SetState(int state) {
    writeToEEPROM(state);
}
// Te devuleve el pin que tiene dicho objeto
int PinController::GetPin() {
    return this->pin;
}
// Enciende el rele y establece el estado a HIGH
void PinController::On() {
    SetState(HIGH);
    dWrite();
}
// Apaga el rele y establece el estado a LOW
void PinController::Off() {
    SetState(LOW);
    dWrite();
}

// Cambia el estado del rele desde el que se ha establecido en memoria
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
