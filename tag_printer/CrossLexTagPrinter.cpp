#include "CrossLexTagPrinter.h"

const std::string CrossLexTagPrinter::CASE[CASE_SIZE] = {
        "nom", "gen", "dat", "acc", "ins", "pre", "par", "loc"
};
const std::string CrossLexTagPrinter::NUMBER[NUMBER_SIZE] = {
        "sg", "pl"
};
const std::string CrossLexTagPrinter::GEN[GEN_SIZE] = {
        "masc", "fem", "neut", "overall"
};
const std::string CrossLexTagPrinter::MOOD[MOOD_SIZE] = {
        "indc", "imper"
};
const std::string CrossLexTagPrinter::PERSON[PERSON_SIZE] = {
        "1p", "2p", "3p"
};
const std::string CrossLexTagPrinter::TIME[TIME_SIZE] = {
        "past", "npast"
};

std::vector<std::string> CrossLexTagPrinter::toStringVector(base::Tag tag) const {
    std::vector<std::string> result;
    int i = 0;
    if (static_cast<bool>(tag & base::Tag::SHRT)) {
        result.push_back("shrt");
    }
    for (base::Tag t = base::Tag::CASE_START; t != base::Tag::CASE_STOP; ++t, ++i) {
//        std::cerr<<"Case:"<<i<<"\n";
        if (static_cast<bool>(tag & t)) {
            result.push_back(CASE[i]);
        }
    }
    i = 0;
    for (base::Tag t = base::Tag::GENDER_START; t != base::Tag::GENDER_STOP; ++t, ++i) {
//        std::cerr<<"Gen:"<<i<<"\n";

        if (static_cast<bool>(tag & t)) {
            result.push_back(GEN[i]);
        }
    }
    i = 0;
    for (base::Tag t = base::Tag::NUMBER_START; t != base::Tag::NUMBER_STOP; ++t, ++i) {
//        std::cerr<<"Num:"<<i<<"\n";

        if (static_cast<bool>(tag & t)) {
            result.push_back(NUMBER[i]);
        }
    }
    if (static_cast<bool>(tag & base::Tag::INF)) {
        result.push_back("inf");
    }
    i = 0;
    for (base::Tag t = base::Tag::MOOD_START; t != base::Tag::MOOD_STOP; ++t, ++i) {
//        std::cerr<<"Mood:"<<i<<"\n";

        if (static_cast<bool>(tag & t)) {
            result.push_back(MOOD[i]);
        }
    }
    i = 0;
    for (base::Tag t = base::Tag::PERSON_START; t != base::Tag::PERSON_STOP; ++t, ++i) {
//        std::cerr<<"Person:"<<i<<"\n";

        if (static_cast<bool>(tag & t)) {
            result.push_back(PERSON[i]);
        }
    }
    i = 0;
    for (base::Tag t = base::Tag::TIME_START; t != base::Tag::TIME_STOP; ++t, ++i) {
//        std::cerr<<"Time:"<<i<<"\n";

        if (static_cast<bool>(tag & t)) {
            result.push_back(TIME[i]);
        }
    }
    return result;
}

std::string CrossLexTagPrinter::toString(base::Tag t) const {
    return boost::algorithm::join(toStringVector(t), " ");
}
