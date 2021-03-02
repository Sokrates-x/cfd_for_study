#ifndef RHO_EQUATION_H
#define RHO_EQUATION_H

#include "equation.h"

class Rho_equation : public Equation
{
public:

    Rho_equation() = delete;

    Rho_equation(const Mesh &, const Boundary_condtions &, Fluid &, Fluid &, const double &, Time &);

    // public method
    void solve();

private:

    // private methods
    void calc_A_y();

    void correct();

};

#endif // RHO_EQUATION_H
