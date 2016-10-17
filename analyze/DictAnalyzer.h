#ifndef _DICTANALYZER_H_
#define _DICTANALYZER_H_

#include "../DAWG/Dictionary.h"
#include "SufProcessor.h"
#include "../base/MorphClassContainer.h"
#include "IAnalyzer.h"
#include "../analyze/NounPairs.h"
#include <memory>
#include "../base/TagConverter.h"

namespace analyze {
    typedef dawg::Dictionary<base::MorphClassContainer> MainDict;
    class DictAnalyzer : public IAnalyzer {
    private:
        std::shared_ptr<MainDict> dict;
        analyze::NounPairs np;
    public:
        DictAnalyzer(std::shared_ptr<MainDict> d,const NounPairs& p, const SufProcessor &proc) : IAnalyzer(proc), dict(d), np(p)  { }

        virtual std::vector<Parsed> analyze(const std::string &wordForm) const override;

        virtual std::vector<Parsed> inflect(const std::string &wordForm, base::Tag t) const override;
    };
}


#endif //CROSSMORPHY_DICTANALYZER_H
