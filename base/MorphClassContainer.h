#ifndef _MORPH_CLASS_CONTAINER_H_
#define _MORPH_CLASS_CONTAINER_H_

#include "../DAWG/ISerializable.h"
#include "MorphClass.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <string>

namespace base {
    /**
     * Class repsents dynamic array for storing MorphClasses.
     * May by changed to set.
     */
    class MorphClassContainer : public dawg::ISerializable {
        friend class std::hash<MorphClassContainer>;

    private:
        MorphClass *data;///data, stored in container
        std::size_t sz; ///size
        std::size_t cps; ///capacity
        double amortConst; ///Amortization const
        static const double DEFAULT_AMORT_CONST; ///Default amortization const
        /**
         * Change capacity to size.
         */
        void recapacity(std::size_t size);
        /**
         * Round val to int.
         */
        int trunc(double val) { return (int)(val+0.5);}
    public:
        /**
         * Construct container for s elements.
         */
        explicit MorphClassContainer(std::size_t s);
        /**
         * Construct empty container.
         */
        MorphClassContainer();

        MorphClassContainer(const MorphClassContainer &o);

        MorphClassContainer &operator=(const MorphClassContainer &o);
        /**
         * Get element by index. No border check.
         */
        MorphClass &operator[](std::size_t n);

        const MorphClass &operator[](std::size_t n) const;

        std::size_t size() const { return sz; }
        /**
         * Add elemnt to end of container.
         */
        void append(const MorphClass &m);
        /**
         * Pop element from end of container.
         */
        MorphClass pop();
        /**
         * Get last element of container.
         */
        MorphClass& last();
        /**
         * Resizes container to required size.
         */
        void resize(std::size_t size);
        /**
         * Clear container.
         */
        void clear();
        /**
         * Returns capacity of array.
         */
        std::size_t capacity() const { return cps; }
        /**
         * Checks equality of this and o container. O(n) complexity.
         */
        bool operator==(const MorphClassContainer &o) const;

        bool operator!=(const MorphClassContainer &o) const { return !(*this == o); }
        /**
         * Serialize container to byte stream.
         */
        virtual bool serialize(std::ostream &os) const;
        /**
         * Deserialize container from byte stream.
         */
        virtual bool deserialize(std::istream &is);
        /**
         * Virtual destructor.
         */
        virtual ~MorphClassContainer();
    };
}
namespace std {
    /**
     * Specializing hash template, to be able to store
     * MorphClassContainer in unordered_ containers.
     */
    template<>
    class hash<base::MorphClassContainer> {
    public:
        std::size_t operator()(const base::MorphClassContainer &o) const {
            int h1 = 0;
            std::size_t i = 0;
            while (i < o.size()) {
                h1 += (71 * h1 + std::hash<base::MorphClass>()(o.data[i])) % 378551;
                i++;
            }
            return h1;
        }
    };
}

#endif //CROSSMORPHY_MORPHCLASSCONTAINER_H
