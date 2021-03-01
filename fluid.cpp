#include "fluid.h"

double Fluid::molar_mass_;


void Fluid::correct(p_t_tag){

    auto iter_p = pressure_field_->cbegin();
    auto iter_t = temperature_field_->cbegin();
    auto iter_rho = density_field_->begin();

    while (iter_p != pressure_field_->cend() && iter_t != temperature_field_->cend() &&
           iter_rho != density_field_->end()) {

        *iter_rho = (*iter_p)/(*iter_t)*molar_mass_/gas_constant;

        ++iter_p;
        ++iter_rho;
        ++iter_t;
    }
}

void Fluid::correct(p_rho_tag){

    auto iter_p = pressure_field_->cbegin();
    auto iter_t = temperature_field_->begin();
    auto iter_rho = density_field_->cbegin();

    while (iter_p != pressure_field_->cend() && iter_t != temperature_field_->end() &&
           iter_rho != density_field_->cend()) {

        *iter_t = (*iter_p)/(*iter_rho)*molar_mass_/gas_constant;

        ++iter_p;
        ++iter_rho;
        ++iter_t;
    }
}

void Fluid::correct(t_rho_tag){

    auto iter_p = pressure_field_->begin();
    auto iter_t = temperature_field_->cbegin();
    auto iter_rho = density_field_->cbegin();

    while (iter_p != pressure_field_->end() && iter_t != temperature_field_->cend() &&
           iter_rho != density_field_->cend()) {

        *iter_p = (*iter_rho)*(*iter_t)/molar_mass_*gas_constant;

        ++iter_p;
        ++iter_rho;
        ++iter_t;
    }
}

void Fluid::correct(){

    auto iter_p = pressure_field_->begin();
    auto iter_t = temperature_field_->begin();
    auto iter_rho = density_field_->begin();

    double r;

    while (iter_p != pressure_field_->end() && iter_t != temperature_field_->end() &&
           iter_rho != density_field_->end()) {

        r = std::pow((*iter_p)/(*iter_rho)/(*iter_t)/gas_constant*molar_mass_, 1.0/3.0);

        *iter_p = *iter_p/r;
        *iter_t = *iter_t*r;
        *iter_rho = *iter_rho*r;

        ++iter_p;
        ++iter_rho;
        ++iter_t;
    }


}

