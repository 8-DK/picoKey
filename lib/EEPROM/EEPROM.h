#ifndef __EEPROM__
#define __EEPROM__

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <hardware/sync.h>
#include <stack>
#include <map>
// Support nested IRQ disable/re-enable
static std::stack<uint32_t> _irqStack[2];

extern "C" void interrupts() {
    if (_irqStack[get_core_num()].empty()) {
        // ERROR
        return;
    }
    auto oldIrqs = _irqStack[get_core_num()].top();
    _irqStack[get_core_num()].pop();
    restore_interrupts(oldIrqs);
}

extern "C" void noInterrupts() {
    _irqStack[get_core_num()].push(save_and_disable_interrupts());
}

class EEPROMClass {
public:
    EEPROMClass(void);

    void begin(size_t size);
    uint8_t read(int const address);
    void write(int const address, uint8_t const val);
    bool commit();
    bool end();

    uint8_t * getDataPtr();
    uint8_t const * getConstDataPtr() const;

    template<typename T>
    T &get(int const address, T &t) {
        if (address < 0 || address + sizeof(T) > _size) {
            return t;
        }

        memcpy((uint8_t*) &t, _data + address, sizeof(T));
        return t;
    }

    template<typename T>
    const T &put(int const address, const T &t) {
        if (address < 0 || address + sizeof(T) > _size) {
            return t;
        }
        if (memcmp(_data + address, (const uint8_t*)&t, sizeof(T)) != 0) {
            _dirty = true;
            memcpy(_data + address, (const uint8_t*)&t, sizeof(T));
        }

        return t;
    }

    size_t length() {
        return _size;
    }

    uint8_t& operator[](int const address) {
        return getDataPtr()[address];
    }
    uint8_t const & operator[](int const address) const {
        return getConstDataPtr()[address];
    }

protected:
    uint8_t* _sector;
    uint8_t* _data = nullptr;
    size_t _size = 0;
    bool _dirty = false;
};

extern EEPROMClass EEPROM;

#endif
