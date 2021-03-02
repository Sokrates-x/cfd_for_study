#include "equation.h"

Equation::Equation(const Mesh &m, const Boundary_condtions &bc, Fluid &f,
    Fluid &f_old, const double &r, Time &t) :mesh_(m), boundary_conditons_(bc),
    fluid_(f), fluid_old_(f_old), relax_factor_(r), time_(t) {

    y_ = std::vector<double>(mesh_.n_x(), 0.0);
    A_ = std::vector<std::vector<double> >(mesh_.n_x(), y_);

}

void Equation::solve(){
    //
    double A_xx = 0.0;

    // initailize
    auto x_iter = x_.begin();
    auto A_iter = A_.cbegin();
    auto y_iter = y_.cbegin();
    auto xx_iter = x_.begin();

    while(x_iter != x_.end() && y_iter != y_.cend() && A_iter != A_.cend()){

        *x_iter = *y_iter;

        xx_iter = x_.begin();

        while(xx_iter != x_.end()){

            std::vector<double>::difference_type diff = xx_iter - x_.begin();

            if(diff == (x_iter - x_.begin())){
                A_xx = *((*A_iter).begin() + diff);
            }
            else{
                *x_iter -= *((*A_iter).begin() + diff)*(*xx_iter);
            }
            ++xx_iter;
        }

        *x_iter /= A_xx;
        ++A_iter;
        ++x_iter;
        ++y_iter;
    }

}

void Equation::correct(Field<double>::iterator begin, Field<double>::iterator end){

    if(time_.time_changed()){

        *(fluid_old_.P()) = *(fluid_.P());
        *(fluid_old_.rho()) = *(fluid_.rho());
        *(fluid_old_.T()) = *(fluid_.T());
        *(fluid_old_.u()) = *(fluid_.u());

        time_.time_changed() = false;
    }

    auto iter_x = x_.begin();
    auto iter_f = begin;

    double redsidues = 0.0;

    max_residues_ = 0.0;

    while (iter_x != x_.end() && iter_f != end) {

        redsidues = fabs(*iter_f - *iter_x);

        max_residues_ = max_residues_ > redsidues ? max_residues_ : redsidues;

        *iter_f *= (1.0 - relax_factor_);

        *iter_f += *iter_x*relax_factor_;

        *iter_x = *iter_f;

        ++iter_f;
        ++iter_x;
    }
}
