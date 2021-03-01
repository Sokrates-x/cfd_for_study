#ifndef FLUID_H
#define FLUID_H

#include <cmath>
#include <iostream>
#include <memory>

#include "constant.h"
#include "initial_tags.h"
#include "field.h"

//class Initial_conditons;

class Fluid
{
public:

    // constructor
    Fluid() = default;

    // access and change
    std::shared_ptr<Field<double> > &P() { return pressure_field_; }

    std::shared_ptr<Field<double> > &T() { return temperature_field_; }

    std::shared_ptr<Field<double> > &rho() { return density_field_; }

    std::shared_ptr<Field<double> > &u() { return velocity_field_x_; }

    static double &M() { return molar_mass_; }

    // correct
    void correct();

    void correct(p_t_tag);

    void correct(p_rho_tag);

    void correct(t_rho_tag);

    // const methods
    const std::shared_ptr<Field<double> > &P() const { return pressure_field_; }

    const std::shared_ptr<Field<double> > &T() const { return temperature_field_; }

    const std::shared_ptr<Field<double> > &rho() const  { return density_field_; }

    const std::shared_ptr<Field<double> > &u() const { return velocity_field_x_; }

private:

    // molar mass kg/mol
    static double molar_mass_;

    // fluid pressure Pa
    std::shared_ptr<Field<double> > pressure_field_;

    // fluid temperature K
    std::shared_ptr<Field<double> > temperature_field_;

    // dynamic viscosity  N/s/m2
    //std::shared_ptr<Field<double> > viscosity_field_;

    // fluid density kg/m3
    std::shared_ptr<Field<double> > density_field_;

    // fluid velocity in x direction
    std::shared_ptr<Field<double> > velocity_field_x_;

};

#endif // FLUID_H
