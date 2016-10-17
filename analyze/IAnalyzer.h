#ifndef IANALYZER_H_
#define IANALYZER_H_
#include "Parsed.h"
#include "SufProcessor.h"
#include <vector>
/**
 * All interfaces and classes linked with
 * word analization placed here.
 */
namespace analyze {
    /**
     * @interface
     * Basic interface to all classes, provide morphological analysis
     */
    class IAnalyzer {
    protected:
        ///Suffix processor
        SufProcessor sufProc;
    public:
        /**
         * Constructor
         */
        explicit IAnalyzer(const SufProcessor& suf): sufProc(suf){ }
        /**
         * Analyze word and get parsed result
         */
        virtual std::vector<Parsed> analyze(const std::string& wordForm) const = 0;
        /**
         * Inflect word with tag
         */
        virtual std::vector<Parsed> inflect(const std::string& wordForm,base::Tag t) const = 0;
    };
}
#endif //IANALYZER_H_
