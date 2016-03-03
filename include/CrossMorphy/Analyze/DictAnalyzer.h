#ifndef _DICTANALYZER_H_
#define _DICTANALYZER_H_
#include "DAWG/Dictionary.h"
#include "SufProcessor.h"
#include "Base/MorphClassContainer.h"
#include "IAnalyzer.h"
#include <memory>
namespace analyze {
    typedef dawg::Dictionary<base::MorphClassContainer> MainDict;
    class DictAnalyzer : public IAnalyzer {
    private:
        std::shared_ptr<MainDict> dict;
    public:
        DictAnalyzer(std::shared_ptr<MainDict> d,const SufProcessor& proc): IAnalyzer(proc), dict(d) {}
        virtual std::vector<Parsed> analyze(const std::string& wordForm) const override;
        virtual std::vector<Parsed> inflect(const std::string& wordForm,base::Tag t) const override;
    };
}


#endif //CROSSMORPHY_DICTANALYZER_H
