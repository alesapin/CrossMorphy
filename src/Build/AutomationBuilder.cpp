#include "Build/AutomationBuilder.h"

namespace build {
    void AutomationBuilder::saveToMap(const analyze::Lexeme &form,
                                      std::map<std::string, base::MorphClassContainer> &fact) {
        for (int i = 0; i < form.size(); ++i) {
            if (fact.find(form[i].getForm()) == fact.end()) {
                base::MorphClassContainer lst;
                lst.append(form[i].getClass());
                fact[form[i].getForm()] = lst;
            } else {
                fact[form[i].getForm()].append(form[i].getClass());
            }
        }
    }

    void AutomationBuilder::dropToFact(const UnpackDict &mp,
                                       dawg::BuildFactory<base::MorphClassContainer> &fact,
                                       std::unordered_map<base::MorphClassContainer, std::size_t> &indexer) {
        for (auto itr = mp.begin(); itr != mp.end(); ++itr) {
            auto cur = indexer.find(itr->second);
            if (cur != indexer.end()) {
                if (!fact.addLink(itr->first, cur->second)) {
                    std::cerr << "Link not created:" << itr->first << "\n";
                }
            } else {
                std::size_t ind = fact.insert(itr->first, itr->second);
                if (ind != -1) {
                    indexer[itr->second] = ind;
                } else {
                    std::cerr << "Not inserted:" << itr->first << "\n";
                }
            }
        }
    }

    std::shared_ptr<dawg::Dictionary<base::MorphClassContainer>> AutomationBuilder::buildMainDictFromText(
            const std::string &textFileName
    ) {
        std::ifstream ifs(textFileName, std::ifstream::in);
        UnpackDict mp;
        dawg::BuildFactory<base::MorphClassContainer> factory;
        std::unordered_map<base::MorphClassContainer, std::size_t> indexer;
        std::string str;
        while (std::getline(ifs, str)) {
            analyze::WordForm w = dictParser(str);
            analyze::Lexeme result = sufProc.getAllFormsByDictForm(w.getForm(), w.getClass());
            saveToMap(result, mp);

        }
        dropToFact(mp, factory, indexer);
        ifs.close();
        return factory.build();
    }

    analyze::WordForm AutomationBuilder::dictParser(const std::string &line) {
        std::stringstream ss;
        std::string word;
        int sp, gen, num;
        std::size_t cls;
        ss << line;
        ss >> sp;
        ss >> cls;
        ss >> num;
        ss >> gen;
        ss >> word;
        base::SpeechPart spechPart = (base::SpeechPart) sp;
        if (spechPart == base::SpeechPart::VERB) {
            cls -= 1;
        }
        base::MorphClass cur(spechPart, cls);

        if (spechPart == base::SpeechPart::NOUN) {
            cur.setGender((base::Tag) (1 << gen));
            cur.setNumber((base::Tag) (0x20 << num));
        } else if (spechPart == base::SpeechPart::ADJ) {
            cur.setShortAdjPos(gen - 1);
        }
        return {word, cur};
    }

//    std::map<std::string, base::MorphClassContainer> AutomationBuilder::removeFormsByPrefix(
//            std::map<std::string, base::MorphClassContainer> &form, const std::string &letter, bool eq) {
//        std::map<std::string, base::MorphClassContainer> result;
//        for (auto itr = form.begin(); itr != form.end();) {
//            if ((eq && itr->first.find(letter) == 0) || (!eq && itr->first.find(letter) != 0)) {
//                result[itr->first] = itr->second;
//                form.erase(itr++);
//            } else {
//                ++itr;
//            }
//        }
//        return result;
//    };


}
