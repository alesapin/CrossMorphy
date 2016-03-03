#ifndef _MORPH_CLASS_CONTAINER_H_
#define _MORPH_CLASS_CONTAINER_H_

#include "DAWG/ISerializable.h"
#include "MorphClass.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <string>

namespace base {
    class MorphClassContainer : public dawg::ISerializable {
        friend class std::hash<MorphClassContainer>;

    private:
        MorphClass *data;
        std::size_t sz;
        std::size_t cps;
        double amortConst;
        static const double DEFAULT_AMORT_CONST;

        void recapacity(std::size_t size);
        int trunc(double val) { return (int)(val+0.5);}
    public:
        explicit MorphClassContainer(std::size_t s);

        MorphClassContainer();

        MorphClassContainer(const MorphClassContainer &o);

        MorphClassContainer &operator=(const MorphClassContainer &o);

        MorphClass &operator[](std::size_t n);

        const MorphClass &operator[](std::size_t n) const;

        std::size_t size() const { return sz; }

        void append(const MorphClass &m);

        MorphClass pop();

        MorphClass& last();

        void resize(std::size_t size);

        void clear();

        std::size_t capacity() const { return cps; }

        bool operator==(const MorphClassContainer &o) const;

        bool operator!=(const MorphClassContainer &o) const { return !(*this == o); }

        virtual bool serialize(std::ostream &os) const;

        virtual bool deserialize(std::istream &is);

        virtual ~MorphClassContainer();
    };
}
namespace std {
    template<>
    class hash<base::MorphClassContainer> {
    public:
        std::size_t operator()(const base::MorphClassContainer &o) const {
            int h1 = 0;
            int i = 0;
            while (i < o.size()) {
                h1 += (71 * h1 + std::hash<base::MorphClass>()(o.data[i])) % 378551;
                i++;
            }
            return h1;
        }
    };
}

#endif //CROSSMORPHY_MORPHCLASSCONTAINER_H
