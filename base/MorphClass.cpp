#include "MorphClass.h"
#include <iostream>
#include <iomanip>

namespace base {
    const uint8_t MorphClass::UNKNOWN_POS = UCHAR_MAX;

    SpeechPart MorphClass::getSpeechPart() const {
        return (SpeechPart) sp;
    }

    uint16_t MorphClass::getClassNumber() const {
        return classNum;
    }

    void MorphClass::setSpeechPart(SpeechPart p) {
        sp = (uint8_t) p;
    }

    void MorphClass::setClassNumber(uint16_t val) {
        classNum = val;
    }

    MorphClass::MorphClass(SpeechPart p, uint16_t cl, uint8_t ps) {
        setSpeechPart(p);
        setClassNumber(cl);
        setPosition(ps);
        if (p != SpeechPart::ADJ) {
            special = 0;
        } else {
            special = UNKNOWN_POS;
        }
    }

    bool MorphClass::operator==(const MorphClass &o) {
        return classNum == o.classNum && sp == o.sp;
    }

    Tag MorphClass::getGender() const {
        return fromInt((special & 0x0F));
    }

    Tag MorphClass::getNumber() const {
        return fromInt(special >> 4);
    }

    void MorphClass::setGender(Tag g) {
        uint8_t intVal = (uint8_t) toInt(g);
        special = (special & 0xF0) | intVal;
    }

    void MorphClass::setNumber(Tag n) {
        uint8_t intVal = (uint8_t) toInt(n);
        special |= (intVal << 4);
    }

    uint8_t MorphClass::getPosition() const {
        return pos;
    }

    void MorphClass::setPosition(uint8_t p) {
        pos = p;
    }

    MorphClass::MorphClass(const MorphClass &o) {
        sp = o.sp;
        special = o.special;
        pos = o.pos;
        classNum = o.classNum;
    }

    MorphClass &MorphClass::operator=(const MorphClass &o) {
        sp = o.sp;
        special = o.special;
        pos = o.pos;
        classNum = o.classNum;
        return *this;
    }

    uint8_t MorphClass::getShortAdjPos() const {
        return special;
    }

    void MorphClass::setShortAdjPos(uint8_t val) {
        special = val;
    }

}
