#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<array>

#include "unit.h"
#include "fluid.h"
#include "mesh.h"
#include "time_cfd.h"
#include "node.h"
#include "boundary_condtions.h"
#include "field.h"
#include "initial_tags.h"
#include "u_equation.h"
#include "rho_equation.h"

int main()
{

    Mesh::d_x() = 1.0;
    const Mesh mesh(101);

    // Initailize

    // m/s
    Unit unit_u(0, 0, 1, -1, 0);
    auto u = std::make_shared<Field<double> >(mesh.n_x(), 0.0, unit_u);
    auto u_old = std::make_shared<Field<double> >(mesh.n_x(), 0.0, unit_u);

    // Pa N/m2 kg/m/s
    Unit unit_P(0, 1, -1, -1, 0);
    auto P = std::make_shared<Field<double> >(mesh.n_x(), 101325.0, unit_P);
    auto P_old = std::make_shared<Field<double> >(mesh.n_x(), 101325.0, unit_P);

    // K
    Unit unit_T(1, 0, 0, 0, 0);
    auto T = std::make_shared<Field<double> >(mesh.n_x(), 293.15, unit_T);
    auto T_old = std::make_shared<Field<double> >(mesh.n_x(), 293.15, unit_T);

    // kg/m3
    Unit unit_rho(0, 1, -3, 0, 0);
    auto rho = std::make_shared<Field<double> >(mesh.n_x(), 0.0, unit_rho);
    auto rho_old = std::make_shared<Field<double> >(mesh.n_x(), 0.0, unit_rho);

    Fluid::M() = 2.801e-2;

    Fluid f, f_old;

    f.P() = P;
    f.T() = T;
    f.rho() = rho;
    f.u() = u;

    f.correct(p_t_tag());

    f_old.P() = P_old;
    f_old.T() = T_old;
    f_old.rho() = rho_old;
    f_old.u() = u_old;

    f_old.correct(p_t_tag());

    Time time(1001, 10.0);

    std::cout << time.total_t() << " " << time.d_t() << " " << time.n_t() << std::endl;

    Boundary_condtions bc_u(Boundary_condtions::type::calculated,
                            0.0, Boundary_condtions::type::fixed_value, 0.0);

    Boundary_condtions bc_rho(Boundary_condtions::type::fixed_value,
                              1.3, Boundary_condtions::type::calculated, 0.0);

    Rho_equation rho_eqn(mesh, bc_rho, f, f_old, 0.3, time);

    U_equation u_eqn(mesh, bc_u, f, f_old, 0.3, time);

    while(!time.end_time()){

        std::cout << "Time steps:" << time.now_step() << " Time:" << time.now() << std::endl;

        do {

            rho_eqn.solve();

            u_eqn.solve();

        } while (rho_eqn.residues() > 1e-8 || u_eqn.residues() > 1e-8);

        ++time;
    }

    return 0;
}
