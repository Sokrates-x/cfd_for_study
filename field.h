#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include "unit.h"

template <typename T>
class Field : public std::vector<T>
{
public:

    // constructors
    Field() = default;

    Field(const Unit &u) : std::vector<T>(), unit_(u) { }

    Field(typename std::vector<T>::size_type sz, const T &t, const Unit &u) :
        std::vector<T>(sz, t), unit_(u) {   }

    //methods
    Unit &unit() { return unit_; }

    //const methods
    const Unit &unit() const { return unit_; }


private:

    //members
    Unit unit_;
};

#endif // FIELD_H
