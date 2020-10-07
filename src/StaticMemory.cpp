#include "StaticMemory.h"

bool StaticMemory::setup() 
{
    EEPROM.begin(512);
    return true;
}

void StaticMemory::define() {
    EEPROM.write(0, 1);
    save();
}

void StaticMemory::undefine() {
    EEPROM.write(0, 0);
    save();
}

bool StaticMemory::is_defined() {
    uint8_t defined = EEPROM.read(0);
    return defined == 1;
}

bool StaticMemory::write(MemoryRegister reg, String data)
{
    clear(reg);
    int length = data.length();
    if(length > REGISTER_SIZE) {
        return false;
    }
    byte* converted = (byte*) malloc(REGISTER_SIZE * sizeof(byte));
    for(int i = 0; i < REGISTER_SIZE; i++) {
        if(i < length) {
            EEPROM.write(i + reg, (byte)data.charAt(i));
        } else {
            EEPROM.write(i + reg, (byte)'\0');
        }
    }
    define();
    return true;
}

char* StaticMemory::read(MemoryRegister reg)
{
    char* tmp = (char*) malloc(REGISTER_SIZE * sizeof(char));
    if(!is_defined()) {
        tmp = "-1";
    } else {
        char* tmp = new char[REGISTER_SIZE];
        for(int i = 0; i < REGISTER_SIZE; i++) {
            int read = (int) EEPROM.read(i + reg);
            if(read == 255 || read == 0) {
                tmp[i] = '\0';
                break;
            }
            Serial.println(read);
            tmp[i] = (char) read;
        }
    }
    return tmp;
}

bool StaticMemory::save()
{
    return EEPROM.commit();
}

void StaticMemory::clear(int max = 130)
{
    for(int i = 0; i < max; i++) {
        EEPROM.write(i, 0);
    }
    undefine(); 
}