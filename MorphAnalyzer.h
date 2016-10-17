#ifndef MORPHANALYZER_H_
#define MORPHANALYZER_H_
#include <vector>
#include "analyze/IAnalyzer.h"
#include "Config.h"
#include "analyze/DictAnalyzer.h"
#include "analyze/SufProcessor.h"
#include "analyze/DictAnalyzer.h"
#include "analyze/NounPairs.h"
#include "BinaryFileException.h"
#include <boost/locale.hpp>
#include <boost/algorithm/string.hpp>

/// User api namespace
namespace xmorph {
    using analyze::Parsed;
    /**
     * Contains all analyzers, and repsents
     * morphological analyzer.
     */
    class MorphAnalyzer {
    private:
        ///Russian UTF8 locale
        std::locale ruUtf8Locale;
        ///Pointers to analyzers
        std::vector<std::shared_ptr<analyze::IAnalyzer>> analyzers;
        /**
         * Delete different garbage from word, set to lower case
         *
         */
        std::string prepareWord(const std::string word) const;
    public:
        /**
         * Constructor
         */
        MorphAnalyzer(){
            ruUtf8Locale = boost::locale::generator().generate("ru_RU.UTF8");
        };
        /**
         * Analyze word and get parsed results.
         */
        std::vector<Parsed> analyze(const std::string& word) const;
        /**
         * Load morph analyzer from paths in config.
         */
        static void load(MorphAnalyzer& ma,const Config& conf = DEFAULT_CONFIG);
    };
}
#endif //MORPHANALYZER_H_
