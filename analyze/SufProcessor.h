#ifndef SUF_PROCESSOR_H_
#define SUF_PROCESSOR_H_

#include <map>
#include <stdexcept>
#include <set>

#include "SufCollection.h"
#include "../base/MorphChars.h"
#include "../base/MorphClass.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <memory>

namespace analyze {

    struct WordForm {
        std::string form;
        base::MorphClass cls;

        std::string getForm() const {
            return form;
        }

        base::MorphClass getClass() const {
            return cls;
        }
    };
    typedef std::vector<WordForm> Lexeme;

    class SufProcessor {
    private:
        static const std::string NOUN;
        static const std::string VERB;
        static const std::string ADJ;
        static const std::string SHRTADJ;
        static const std::string PRON;
        static const std::string LOC_NOUNS;
        static const std::string SING_PLUR_NOUNS;
        std::map<std::string, std::shared_ptr<SufCollection>> suffixes;
        std::set<std::string> locativeNouns;
        std::vector<WordForm> getAllShortFormsByFullForm(const std::string &normalForm,
                                                         const base::MorphClass &cls) const;

    public:
        SufProcessor() { };

        SufProcessor(const SufProcessor &o) {
            suffixes = o.suffixes;
            locativeNouns = o.locativeNouns;
        }
        SufProcessor&operator=(const SufProcessor& o){
            suffixes = o.suffixes;
            locativeNouns = o.locativeNouns;
            return *this;
        }
        std::string getSuffix(const base::MorphClass &cls) const;

        std::string getSuffix(base::SpeechPart sp, std::size_t classNum, std::size_t pos = 0,
                              std::size_t shrtPos = base::MorphClass::UNKNOWN_POS) const;

        std::string getStemByNormalForm(const std::string &normalForm, const base::MorphClass &cls) const;

        std::string getStemByForm(const std::string &form, const base::MorphClass &cls) const;

        std::string getNormalFromByForm(const std::string &form, const base::MorphClass& cls) const;

        std::vector<std::string> getAllFormsByStem(const std::string &stem, const base::MorphClass &cls) const;

        Lexeme getAllFormsByDictForm(const std::string &normalForm, const base::MorphClass &cls) const;

        std::size_t getNumberOfForms(const base::MorphClass& cls, const std::string& form = "") const;
        bool isLocativeNoun(const std::string& noun) const;
        static void loadSufProcessor(const std::string &filepath, SufProcessor &prc);
    };
}
#endif //SUF_PROCESSOR_H_
