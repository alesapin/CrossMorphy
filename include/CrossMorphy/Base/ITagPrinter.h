#ifndef ITAGPRINTER_H_
#define ITAGPRINTER_H_
#include "MorphChars.h"
#include <vector>
#include <string>
namespace base {
    class ITagPrinter {
    public:
        virtual std::vector<std::string> toStringVector(Tag t) const = 0;
        virtual std::string toString(Tag t) const = 0;
    };
}
#endif //ITAGPRINTER_H
