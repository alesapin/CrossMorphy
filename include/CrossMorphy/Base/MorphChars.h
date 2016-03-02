#ifndef MORPH_CHARS_H_
#define MORPH_CHARS_H_
#include <cstdint>
#include <type_traits>
#include <string>
namespace base {
enum class SpeechPart : uint16_t {
  UNKNOWN = 0, NOUN = 1, VERB = 2,ADJ = 3, ADV = 4, PARTICIPLE = 5, PRON = 6, PREP = 7, UNI = 8, PARTICLE = 9, SPEECH_PART_STOP, SPEECH_PART_START = NOUN
};
enum class Tag : uint64_t {
  UNDEF = 0x01,
  MASC = 0x02,
  FEM = 0x04,
  NEUT = 0x08,
  OVERALL = 0x10,
  GENDER_START = MASC,
  GENDER_STOP = 0x20,
  SG = 0x40,
  PL = 0x80,
  NUMBER_START = SG,
  NUMBER_STOP = 0x100,
  NOM = 0x200,
  GEN = 0x400,
  DAT = 0x800,
  ACC = 0x1000,
  INS = 0x2000,
  PRE = 0x4000,
  PAR = 0x8000,
  LOC = 0x10000,
  CASE_STOP = 0x20000,
  CASE_START = NOM,
  INDC = 0x40000,
  IMPR = 0x80000,
  MOOD_START = INDC,
  MOOD_END = 0x100000,
  FP = 0x200000,
  SP = 0x400000,
  TP = 0x800000,
  PERSON_START = FP,
  PERSON_END = 0x1000000,
  PAST = 0x2000000,
  NPAST = 0x4000000,
  TIME_START = PAST,
  TIME_END = 0x80000000,
  INF = 0x10000000,
  SHRT = 0x20000000,
  SPECIAL_START = INF,
  SPECIAL_END = 0x40000000,
};
Tag operator++ (Tag& val);
std::size_t toInt(Tag t);
Tag fromInt(std::size_t val);
SpeechPart operator++ (SpeechPart& val);
std::string toString(SpeechPart p);
SpeechPart fromString(const std::string& name);
}
#endif //MORPH_CHARS_H_
