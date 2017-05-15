#include <Arduino.h>
#include <EEPROM.h>

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
      switch (GetState()) {
        case LOW:
          digitalWrite(GetPin(), HIGH);
          break;
        case HIGH:
          digitalWrite(GetPin(), LOW);
          break;
      }
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
  public:
    PinController(int eeAddr, int pin) {
      init(eeAddr, pin);
    }

    // Obtiene el estado del rele leyendolo de la memoria EEPROM
    int GetState() {
      return readFromEEPROM();
    }
    // Establece el estado del rele y lo guarda en la memoria EEPROM
    void SetState(int state) {
      writeToEEPROM(state);
    }
    // Te devuleve el pin que tiene dicho objeto
    int GetPin() {
      return this->pin;
    }
    // Enciende el rele y establece el estado a HIGH
    void On() {
      digitalWrite(GetPin(), LOW);
      SetState(HIGH);
    }
    // Apaga el rele y establece el estado a LOW
    void Off() {
      digitalWrite(GetPin(), HIGH);
      SetState(LOW);
    }
    // Cambia el estado del rele desde el que se ha establecido en memoria
    void Toggle() {
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
};
