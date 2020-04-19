#include "StaticMemory.h"

bool StaticMemory::setup() 
{
    EEPROM.begin(512);
    return true;
}

bool StaticMemory::write(MemoryRegister reg, String data)
{
    clear(reg);
    int length = data.length();
    if(length > REGISTER_SIZE) {
        return false;
    }
    byte* converted = new byte[REGISTER_SIZE];
    for(int i = 0; i < REGISTER_SIZE; i++) {
        if(i < length) {
            EEPROM.write(i + reg, (byte)data.charAt(i));
        } else {
            EEPROM.write(i + reg, (byte)'\0');
        }
    }

    return true;
}

String StaticMemory::read(MemoryRegister reg)
{
    char* tmp = new char[REGISTER_SIZE];
    for(int i = 0; i < REGISTER_SIZE; i++) {
        int read = (int) EEPROM.read(i + reg);
        if(read == 255 || read == 0) {
            tmp[i] = '\0';
            break;
        }
        tmp[i] = (char) read;
    }
    return String(tmp);
}

bool StaticMemory::save()
{
    return EEPROM.commit();
}

void StaticMemory::clear(MemoryRegister reg)
{
    for(int i = reg; i < reg + REGISTER_SIZE; i++) {
        EEPROM.write(i, (byte)'\0');
    }
    save();    
}