#ifndef IANALYZER_H_
#define IANALYZER_H_
#include "Parsed.h"
#include "SufProcessor.h"
#include <vector>
namespace analyze {
    class IAnalyzer {
    protected:
        SufProcessor sufProc;
    public:
        explicit IAnalyzer(const SufProcessor& suf): sufProc(suf){ }
        virtual std::vector<Parsed> analyze(const std::string& wordForm) const = 0;
        virtual std::vector<Parsed> inflect(const std::string& wordForm,base::Tag t) const = 0;
    };
}
#endif //IANALYZER_H_
