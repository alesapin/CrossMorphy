#include "Analyze/DictAnalyzer.h"

namespace analyze {
    std::vector<Parsed> DictAnalyzer::analyze(const std::string &wordForm) const {
        std::vector<Parsed> result;
        try{
            base::MorphClassContainer vars =  dict->getValue(wordForm);
            for(int i = 0;i<vars.size();++i){
                std::string normalForm = sufProc.getNormalFromByForm(wordForm,vars[i]);
                Parsed prs = {wordForm,normalForm,vars[i].getSpeechPart(),base::Tag::FEM};
                result.push_back(prs);
            }
        } catch (dawg::NoSuchKeyException e){
            return result;
        }
        return result;
    }
    std::vector<Parsed> DictAnalyzer::inflect(const std::string& wordForm,base::Tag t) const {
        std::vector<Parsed> result;
        return result;
    }
}