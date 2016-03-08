#include "Analyze/NounPairs.h"
namespace analyze {
    std::string NounPairs::getSingularForm(const std::string& pluralForm) const {
        try{
            NounSuffix s = dict->getValue(pluralForm);
            return pluralForm.substr(0,s.sufPos) + s.suf;
        } catch (dawg::NoSuchKeyException e){
            return pluralForm;
        }
    }
    std::string NounPairs::getPluralForm(const std::string& singularForm) const {
        try{
            NounSuffix s = dict->getValue(singularForm);
            return singularForm.substr(0,s.sufPos) + s.suf;
        } catch (dawg::NoSuchKeyException e){
            return singularForm;
        }
    }
    bool NounSuffix::serialize(std::ostream &os) const {
        if (!os.write((const char *) (&sufPos), sizeof(std::size_t))) return false;
        std::size_t strLen = suf.length();
        if (!os.write((const char *) (&strLen), sizeof(std::size_t))) return false;
        if (!os.write((const char *) (&suf[0]), suf.size())) return false;
        return true;
    }
    bool NounSuffix::deserialize(std::istream &is) {
        if (!is.read((char *) (&sufPos), sizeof(std::size_t))) return false;
        std::size_t strLen;
        if (!is.read((char *) (&strLen), sizeof(std::size_t))) return false;
        suf.resize(strLen);
        if (!is.read((char *) (&suf[0]), strLen)) return false;
        return true;
    }
}