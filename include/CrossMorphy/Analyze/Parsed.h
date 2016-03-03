#ifndef PARSED_H_
#define PARSED_H_
#include "Base/MorphChars.h"
#include <string>
namespace analyze {
    struct Parsed {
        std::string form;
        std::string normalForm;
        base::SpeechPart sp;
        base::Tag tag;
    };
}
#endif //PARSED_H_
