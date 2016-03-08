#ifndef MORPHANALYZER_H_
#define MORPHANALYZER_H_
#include <vector>
#include "Analyze/IAnalyzer.h"
#include "Config.h"
#include "Analyze/DictAnalyzer.h"
#include "Analyze/SufProcessor.h"
#include "Analyze/DictAnalyzer.h"
#include "Analyze/NounPairs.h"
#include "BinaryFileException.h"
#include <boost/locale.hpp>
#include <boost/algorithm/string.hpp>
namespace xmorph {
    using analyze::Parsed;
    class MorphAnalyzer {
    private:
        std::locale ruUtf8Locale;
        std::vector<std::shared_ptr<analyze::IAnalyzer>> analyzers;
        std::string prepareWord(const std::string word) const;
    public:
        MorphAnalyzer(){
            ruUtf8Locale = boost::locale::generator().generate("ru_RU.UTF8");
        };
        std::vector<Parsed> analyze(const std::string& word) const;
        static void load(MorphAnalyzer& ma,const Config& conf = DEFAULT_CONFIG);
    };
}

#endif //CROSSMORPHY_MORPHANALYZER_H
