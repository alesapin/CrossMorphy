#ifndef ITAGPRINTER_H_
#define ITAGPRINTER_H_
#include "MorphChars.h"
#include <vector>
#include <string>
namespace base {
    /**
     * Interface for all classes, that could print tags.
     */
    class ITagPrinter {
    public:
        /**
         * Return vector string repsentation of tag
         */
        virtual std::vector<std::string> toStringVector(Tag t) const = 0;
        /**
         * Return string represantation of tag
         */
        virtual std::string toString(Tag t) const = 0;
    };
}
#endif //ITAGPRINTER_H
