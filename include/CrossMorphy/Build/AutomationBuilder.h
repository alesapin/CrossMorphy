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
#include <fstream>
#include <sstream>

namespace build {
    typedef  std::map<std::string, base::MorphClassContainer> UnpackDict;
    class AutomationBuilder {
    private:
        analyze::SufProcessor sufProc;

        void dropToFact(const UnpackDict &form,
                        dawg::BuildFactory<base::MorphClassContainer> &fact,
                        std::unordered_map<base::MorphClassContainer, std::size_t> &indexer);

        void saveToMap(const analyze::Lexeme &form,
                       UnpackDict &fact);

        analyze::WordForm dictParser(const std::string &line);


    public:
        explicit AutomationBuilder(const analyze::SufProcessor &prc) : sufProc(prc) { }

        std::shared_ptr<dawg::Dictionary<base::MorphClassContainer>> buildMainDictFromText(
                const std::string &textFileName);
    };
}

#endif //AUTOMATIONBUILDER_H_
