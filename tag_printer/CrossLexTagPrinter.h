#ifndef CROSSLEXTAGPRINTER_H_
#define CROSSLEXTAGPRINTER_H_

#include "../base/ITagPrinter.h"
#include <boost/algorithm/string/join.hpp>
/**
 * Cross lexica tags printer.
 * Have to be moved in anyone namespace
 */
class CrossLexTagPrinter : public base::ITagPrinter {
    static const std::size_t CASE_SIZE = 8;
    static const std::string CASE[CASE_SIZE];
    static const std::size_t NUMBER_SIZE = 2;
    static const std::string NUMBER[NUMBER_SIZE];
    static const std::size_t GEN_SIZE = 4;
    static const std::string GEN[GEN_SIZE];
    static const std::size_t MOOD_SIZE = 2;
    static const std::string MOOD[MOOD_SIZE];
    static const std::size_t PERSON_SIZE = 3;
    static const std::string PERSON[PERSON_SIZE];
    static const std::size_t TIME_SIZE = 2;
    static const std::string TIME[TIME_SIZE];
public:
    virtual std::vector<std::string> toStringVector(base::Tag t) const override;

    virtual std::string toString(base::Tag t) const override;

};

#endif //CROSSLEXTAGPRINTER_H_
