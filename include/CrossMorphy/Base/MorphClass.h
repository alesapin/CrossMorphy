#ifndef MORPH_CLASS_H_
#define MORPH_CLASS_H_
#include "MorphChars.h"
#include <climits>
namespace base {
class MorphClass {
private:
  uint8_t sp; //speechpart_byte
  uint16_t classNum; // class number repr;
  uint8_t special; //Gender 0x0F and Number 0xF0 for NOUNS
  uint8_t pos; //position in morphclass
public:
  MorphClass(SpeechPart p,uint16_t cl,uint8_t ps = UNKNOWN_POS);
  MorphClass() = default;
  MorphClass(const MorphClass& o);
  MorphClass& operator=(const MorphClass& m);
  bool operator==(const MorphClass& o);
  bool operator!=(const MorphClass& o){return !(*this == o);}
  SpeechPart getSpeechPart() const;
  uint16_t getClassNumber() const;
  Tag getGender() const;
  Tag getNumber() const;
  uint8_t getPosition() const;
  uint8_t getShortAdjPos() const;
  void setPosition(uint8_t pos);
  void setSpeechPart(SpeechPart p);
  void setClassNumber(uint16_t val);
  void setShortAdjPos(uint8_t val);
  void setGender(Tag g);
  void setNumber(Tag n);
  static const uint8_t UNKNOWN_POS;
};
}
#endif //MORPH_CLASS_H_
