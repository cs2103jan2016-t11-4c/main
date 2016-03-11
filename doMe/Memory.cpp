#include "Memory.h"

const string Memory::MESSAGE_VOID_STRING = "";
const string Memory::DEFAULT_TEXT_FILE_NAME = "doMe.txt";
const string Memory::LIST_DIVIDER = "__________";

Memory::Memory(void) {
    _settings = new Settings();
    _storage = new Storage();
}

Memory::~Memory(void) {
    delete _settings;
    delete _storage;
}



