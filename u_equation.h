#ifndef U_EQUATION_H
#define U_EQUATION_H

#include "equation.h"
#include "time_cfd.h"

class U_equation : public Equation
{
public:

    // constructor
    U_equation() = delete;

    U_equation(const Mesh &, const Boundary_condtions &, Fluid &, Fluid &, const double &, Time &);


    void solve();

private:

    // private methods
    void calc_A_y();

    void correct();

};

#endif // U_EQUATION_H
