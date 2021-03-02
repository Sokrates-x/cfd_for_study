#ifndef EQUATION_H
#define EQUATION_H

#include <vector>

#include "mesh.h"
#include "boundary_conditions.h"
#include "time_cfd.h"
#include "fluid.h"

class Equation
{
public:

    // constructors
    Equation(const Mesh &, const Boundary_condtions &, Fluid &, Fluid &, const double &, Time &);

    void solve();

    const double &residues() const { return max_residues_; }

protected:

    // methods
    virtual void calc_A_y() = 0;

    void correct(Field<double>::iterator, Field<double>::iterator);

    // protected members
    std::vector<std::vector<double> > A_;

    std::vector<double> x_;

    std::vector<double> y_;

    const Mesh &mesh_;

    const Boundary_condtions &boundary_conditons_;

    Fluid &fluid_;

    Fluid &fluid_old_;

    double relax_factor_;

    double max_residues_;

    Time &time_;

};

#endif // EQUATION_H
