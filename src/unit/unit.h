#ifndef UNIT_H
#define UNIT_H

class Unit
{
public:
    // constructor
    Unit(const int &K = 0, const int &kg = 0, const int &m = 0,
         const int &s = 0, const int &mole = 0) : K_(K), kg_(kg),
        m_(m), s_(s), mole_(mole) {    }

    // methods
    int &K() { return K_; }

    int &kg() { return kg_; }

    int &m() { return m_; }

    int &s() { return s_; }

    int &mole() { return mole_; }

    // const methods
    const int &K() const { return K_; }

    const int &kg() const { return kg_; }

    const int &m() const { return m_; }

    const int &s() const { return s_; }

    const int &mole() const { return mole_; }

private:

    // members
    int K_;

    int kg_;

    int m_;

    int s_;

    int mole_;
};

#endif // UNIT_H
