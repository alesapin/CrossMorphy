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
                // case SpeechPart::SHRT_ADJ:
                //   return "SHRT_ADJ";
            case SpeechPart::PARTICIPLE:
                return "PARTICIPLE";
            case SpeechPart::PRON:
                return "PRON";
            case SpeechPart::PREP:
                return "PREP";
            case SpeechPart::UNI:
                return "UNI";
            case SpeechPart::PARTICLE:
                return "PARTICLE";
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
            // } else if(name == "SHRT_ADJ"){
            //   return SpeechPart::SHRT_ADJ;
        } else if (name == "PARTICLE") {
            return SpeechPart::PARTICIPLE;
        } else if (name == "PRON") {
            return SpeechPart::PRON;
        } else if (name == "PREP") {
            return SpeechPart::PREP;
        } else if (name == "UNI") {
            return SpeechPart::UNI;
        } else if (name == "PARTICLE") {
            return SpeechPart::PARTICLE;
        } else {
            return SpeechPart::UNKNOWN;
        }
    }

    SpeechPart operator++(SpeechPart &val) {
        typedef typename std::underlying_type<SpeechPart>::type underlying;
        return val = static_cast<SpeechPart>(static_cast<underlying>(val) + 1);
    }

    Tag operator++(Tag &val) {
        typedef typename std::underlying_type<Tag>::type underlying;
        return val = static_cast<Tag>(static_cast<underlying>(val) << 1);
    }

    std::size_t toInt(Tag t) {
        typedef typename std::underlying_type<Tag>::type underlying;
        underlying val = static_cast<underlying>(t);
        std::size_t result = 0;
        while (val > 1) {
            val >>= 1;
            result++;
        }
        return result;
    }

    Tag fromInt(std::size_t val) {
        typedef typename std::underlying_type<Tag>::type underlying;
        return static_cast<Tag>(static_cast<underlying>(1 << val));
    }

}
