#include "Analyze/DictAnalyzer.h"

namespace analyze {
    std::vector<Parsed> DictAnalyzer::analyze(const std::string &wordForm) const {
        std::vector<Parsed> result;
        CrossLexTagPrinter *t = new CrossLexTagPrinter();
        std::shared_ptr<CrossLexTagPrinter> pt(t);
        try {
            base::MorphClassContainer vars = dict->getValue(wordForm);
            for (std::size_t i = 0; i < vars.size(); ++i) {
                std::string normalForm = sufProc.getNormalFromByForm(wordForm, vars[i]);
                if(vars[i].getSpeechPart() == base::SpeechPart::NOUN && vars[i].getNumber() == base::Tag::PL) {
                    normalForm = np.getSingularForm(normalForm);
                }
                Parsed prs(wordForm, normalForm, vars[i].getSpeechPart(), base::convertClassToTag(vars[i]), pt);
                result.push_back(prs);
            }
        } catch (dawg::NoSuchKeyException e) {
            return result;
        }
        return result;
    }

    std::vector<Parsed> DictAnalyzer::inflect(const std::string &wordForm, base::Tag t) const {
        std::vector<Parsed> result;
        return result;
    }
}