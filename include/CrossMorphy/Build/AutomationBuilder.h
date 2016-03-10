#ifndef AUTOMATIONBUILDER_H_
#define AUTOMATIONBUILDER_H_

#include "DAWG/Dictionary.h"
#include "DAWG/BuildFactory.h"
#include "Base/MorphClassContainer.h"
#include "Analyze/SufProcessor.h"
#include <map>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include "Analyze/NounPairs.h"
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>
/**
 * Namespace contains all clases linked with
 * dictionary building from text files on disk.
 */
namespace build {
    typedef  std::map<std::string, base::MorphClassContainer> UnpackDict;
    /**
     * Can build main dict and nounpairs dict
     */
    class AutomationBuilder {
    private:
        analyze::SufProcessor sufProc;

        void dropToFact(const UnpackDict &form,
                        dawg::BuildFactory<base::MorphClassContainer> &fact,
                        std::unordered_map<base::MorphClassContainer, std::size_t> &indexer);

        void saveToMap(const analyze::Lexeme &form,
                       UnpackDict &fact);

        analyze::WordForm dictParser(const std::string &line);

        std::string getCommonPrefix(const std::string &s1,const std::string &s2);

    public:
        explicit AutomationBuilder(const analyze::SufProcessor &prc) : sufProc(prc) { }

        std::shared_ptr<dawg::Dictionary<base::MorphClassContainer>> buildMainDictFromText(
                const std::string &textFileName);

        std::shared_ptr<dawg::Dictionary<analyze::NounSuffix>> buildNounPairsFromText(const std::string &textFileName);
    };
}

#endif //AUTOMATIONBUILDER_H_
