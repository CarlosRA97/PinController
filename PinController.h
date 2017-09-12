#include <Arduino.h>
#include <EEPROM.h>

#ifndef PINCONTROLLER_H
#define PINCONTROLLER_H

class PinController {
  private:
    int pin;
    int state;
    int eeAddress;

    void init(int address, int pin) {
      #ifdef ESP8266
      EEPROM.begin(8);
      #endif
      setPin(pin);
      seteeAddr(address);
      pinMode(GetPin(), OUTPUT);
      dWrite();
    }
    void seteeAddr(int addr) {
      this->eeAddress = addr;
    }
    void writeToEEPROM(int state) {
        EEPROM.write(geteeAddr(), state);
        #ifdef ESP8266
        EEPROM.commit();
        #endif
    }
    int readFromEEPROM() {
        return EEPROM.read(geteeAddr());
    }
    int geteeAddr() {
      return this->eeAddress;
    }
    void setPin(int p) {
      this->pin = p;
    }
    void dWrite() {
      digitalWrite(GetPin(), GetState());
    }
  public:
    PinController(int eeAddr, int pin);

    int GetState();           // Obtiene el estado del pin leyendolo de la memoria EEPROM    
    void SetState(int state); // Establece el estado del pin y lo guarda en la memoria EEPROM
    int GetPin();             // Te devuleve el pin que tiene dicho objeto
    void On();                // Enciende el pin y establece el estado a HIGH
    void Off();               // Apaga el pin y establece el estado a LOW 
    void Toggle();            // Cambia el estado del pin desde el que se ha establecido en memoria
    
};

#endif