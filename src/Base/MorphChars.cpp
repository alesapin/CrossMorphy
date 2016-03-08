#include "Base/MorphChars.h"

namespace base {

    std::string toString(SpeechPart p) {
        switch (p) {
            case SpeechPart::NOUN:
                return "NOUN";
            case SpeechPart::VERB:
                return "VERB";
            case SpeechPart::ADJ:
                return "ADJ";
            case SpeechPart::ADV:
                return "ADV";
            case SpeechPart::PARTICIPLE:
                return "PARTICIPLE";
            case SpeechPart::PRON:
                return "PRON";
            case SpeechPart::PREP:
                return "PREP";
            case SpeechPart::CONJ:
                return "CONJ";
            case SpeechPart::PARTICLE:
                return "PARTICLE";
            case SpeechPart::INTJ:
                return "INTJ";
            default:
                return "UNKNOWN";
        }
    }

    SpeechPart fromString(const std::string &name) {
        if (name == "NOUN") {
            return SpeechPart::NOUN;
        } else if (name == "VERB") {
            return SpeechPart::VERB;
        } else if (name == "ADJ") {
            return SpeechPart::ADJ;
        } else if (name == "ADV") {
            return SpeechPart::ADV;
        } else if (name == "PARTICLE") {
            return SpeechPart::PARTICIPLE;
        } else if (name == "PRON") {
            return SpeechPart::PRON;
        } else if (name == "PREP") {
            return SpeechPart::PREP;
        } else if (name == "CONJ") {
            return SpeechPart::CONJ;
        } else if (name == "PARTICLE") {
            return SpeechPart::PARTICLE;
        } else if (name == "INTJ") {
            return SpeechPart::INTJ;
        } else {
            return SpeechPart::UNKNOWN;
        }
    }




    typedef typename std::underlying_type<Tag>::type underlying;

    SpeechPart operator++(SpeechPart &val) {
        return val = static_cast<SpeechPart>(static_cast<underlying>(val) + 1);
    }

    Tag& operator++(Tag &val) {
        return val = static_cast<Tag>(static_cast<underlying>(val) << 1);
    }

    Tag operator&(Tag t1, Tag t2) {
        underlying v1 = static_cast<underlying>(t1);
        underlying v2 = static_cast<underlying>(t2);
        return static_cast<Tag>(v1 & v2);
    }
    Tag& operator|=(Tag& t1, Tag t2) {
        underlying v1 = static_cast<underlying>(t1);
        underlying v2 = static_cast<underlying>(t2);
        return t1 = static_cast<Tag>(v1 | v2);
    }
    Tag operator<<(Tag t,std::size_t bits){
        underlying v = static_cast<underlying>(t);
        return static_cast<Tag>(v << bits);
    }
    Tag operator>>(Tag t,std::size_t bits) {
        underlying v = static_cast<underlying>(t);
        return static_cast<Tag>(v >> bits);
    }
    Tag& operator&=(Tag& t1,Tag t2) {
        underlying v1 = static_cast<underlying>(t1);
        underlying v2 = static_cast<underlying>(t2);
        return t1 = static_cast<Tag>(v1 & v2);
    }

    std::size_t toInt(Tag t) {
        underlying val = static_cast<underlying>(t);
        std::size_t result = 0;
        while (val > 1) {
            val >>= 1;
            result++;
        }
        return result;
    }

    Tag fromInt(std::size_t val) {
        return static_cast<Tag>(static_cast<underlying>(1 << val));
    }
    Tag operator|(Tag t1, Tag t2) {
        underlying v1 = static_cast<underlying>(t1);
        underlying v2 = static_cast<underlying>(t2);
        return static_cast<Tag>(v1 | v2);
    }


}
