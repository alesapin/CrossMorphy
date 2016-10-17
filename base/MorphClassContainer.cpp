#include "MorphClassContainer.h"

namespace base {
    const double MorphClassContainer::DEFAULT_AMORT_CONST = 1.5;

    MorphClassContainer::MorphClassContainer(std::size_t s) : sz(s) {
        cps = s;
        data = new MorphClass[s];
        amortConst = DEFAULT_AMORT_CONST;
    }

    MorphClass &MorphClassContainer::operator[](std::size_t n) {
        return data[n];
    }

    const MorphClass &MorphClassContainer::operator[](std::size_t n) const {
        return data[n];
    }

    MorphClassContainer::~MorphClassContainer() {
        if (cps != 0) {
            delete[] data;
        }
    }

    bool MorphClassContainer::serialize(std::ostream &os) const {
        if (!os.write((const char *) (&sz), sizeof(std::size_t))) return false;
        if (!os.write((const char *) (&data[0]), sz * sizeof(MorphClass))) return false;
        return true;
    }

    bool MorphClassContainer::deserialize(std::istream &is) {
        if (!is.read((char *) (&sz), sizeof(std::size_t))) return false;
        cps = sz;
        MorphClass *newdata = new MorphClass[cps];
        if (!is.read((char *) (&newdata[0]), sizeof(MorphClass) * sz)) return false;
        delete[] data;
        data = newdata;
        return true;
    }

    MorphClassContainer::MorphClassContainer(const MorphClassContainer &o) {
        sz = o.sz;
        cps = o.cps;
        data = new MorphClass[cps];
        memcpy(data, o.data, sz * sizeof(MorphClass));
    }

    bool MorphClassContainer::operator==(const MorphClassContainer &o) const {
        if (sz != o.sz) return false;
        return static_cast<bool>(!memcmp(data, o.data, sz * sizeof(MorphClass)));
    }

    MorphClassContainer &MorphClassContainer::operator=(const MorphClassContainer &o) {
        if (o != *this) {
            sz = o.sz;
            delete[] data;
            cps = o.cps;
            data = new MorphClass[cps];
            memcpy(data, o.data, sz * sizeof(MorphClass));
        }
        return *this;
    }

    void MorphClassContainer::append(const MorphClass &m) {
        std::size_t currentSize = sz;
        if (currentSize == cps) {
            if (cps != 0) {
                recapacity(trunc(cps * amortConst));
            } else {
                recapacity(1);
            }
        }
        memcpy(&data[currentSize], &m, sizeof(MorphClass));
        sz++;
    }

    void MorphClassContainer::clear() {
        sz = 0;
        cps = 1;
        delete data;
        data = new MorphClass[1];
    }

    MorphClass MorphClassContainer::pop() {
        sz--;
        if (sz < cps / amortConst) {
            recapacity(trunc(cps / amortConst));
        }
        return this->operator[](sz);
    }

    void MorphClassContainer::resize(std::size_t size) {
        if (size == 0) {
            clear();
        } else {
            recapacity(trunc(size * amortConst));
            sz = size;
        }
    }

    void MorphClassContainer::recapacity(std::size_t sz) {
        std::size_t oldcps = cps;
        cps = sz;
        MorphClass *ndata = new MorphClass[cps];
        if (cps >= oldcps) {
            memcpy(ndata, data, oldcps * sizeof(MorphClass));
        } else {
            memcpy(ndata, data, cps * sizeof(MorphClass));
        }
        delete[] data;
        data = ndata;
    }

    MorphClassContainer::MorphClassContainer() : sz(0), amortConst(DEFAULT_AMORT_CONST) {
        cps = 1;
        data = new MorphClass[1];
    }

    MorphClass &MorphClassContainer::last() {
        if (sz > 0) {
            return data[sz - 1];
        }
    }

}
