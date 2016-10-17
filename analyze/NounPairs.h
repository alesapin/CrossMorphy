#ifndef NOUNPAIRS_H_
#define NOUNPAIRS_H_
#include "../DAWG/Dictionary.h"
#include "../DAWG/ISerializable.h"
#include <string>
#include <memory>
namespace analyze {
    struct NounSuffix : public dawg::ISerializable {
        NounSuffix(std::size_t pos,const std::string& s):sufPos(pos),suf(s){}
        NounSuffix():sufPos(0),suf(""){}
        std::size_t sufPos;
        std::string suf;
        virtual bool serialize(std::ostream &os) const;
        virtual bool deserialize(std::istream &is);

        bool operator==(const NounSuffix& o) const{
            return suf == o.suf && sufPos == o.sufPos;
        }
    };
    class NounPairs {
    private:
        std::shared_ptr<dawg::Dictionary<NounSuffix>> dict;
    public:
        explicit NounPairs(std::shared_ptr<dawg::Dictionary<NounSuffix>> d):dict(d){}
        std::string getSingularForm(const std::string& pluralForm) const;
        std::string getPluralForm(const std::string& singularForm) const;

    };
}
namespace std {
    template<>
    class hash<analyze::NounSuffix> {
    public:
        std::size_t operator()(const analyze::NounSuffix &o) const {
            int h1 = std::hash<std::string>()(o.suf);
            int h2 = std::hash<std::size_t>()(o.sufPos);
            return h1 ^ h2;
        }
    };
}
#endif //NOUNPAIRS_H_
