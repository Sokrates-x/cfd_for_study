#include "u_equation.h"

U_equation::U_equation(const Mesh &m, const Boundary_condtions &bc, Fluid &f,
    Fluid &f_old, const double &r, Time &t) : Equation(m, bc, f, f_old, r, t) {

    for(auto m : *(fluid_.u())){

        x_.push_back(m);

    }

    calc_A_y();
}

void U_equation::calc_A_y(){

    auto iter_n = mesh_.vec_node_p().begin();

    auto iter_A = A_.begin();
    auto iter_y = y_.begin();

    double rho_n_now = 0.0, rho_p_now = 0.0, rho_m_now = 0.0;
    double rho_n_old = 0.0, rho_p_old = 0.0, rho_m_old = 0.0;

    double p_n_now = 0.0, p_p_now = 0.0, p_m_now = 0.0;

    double u_n_now = 0.0, u_p_now = 0.0, u_m_now = 0.0;
    double u_n_old = 0.0, u_p_old = 0.0, u_m_old = 0.0;

    const double dx = Mesh::d_x(), dt = time_.d_t();

    double A_t_p = 0.0, A_u_p = 0.0;
    double A_t_m = 0.0, A_u_m = 0.0;
    double A_t_n = 0.0, A_u_n = 0.0;

    std::vector<std::shared_ptr<Node> >::difference_type n_x_diff;
    std::vector<std::shared_ptr<Node> >::difference_type p_x_diff;
    std::vector<std::shared_ptr<Node> >::difference_type m_x_diff;

    while(iter_A != A_.end() && iter_y != y_.end() && iter_n != mesh_.vec_node_p().end()){

        n_x_diff = (*iter_n)->x_n_diff();

        rho_n_now = *(fluid_.rho()->cbegin() + n_x_diff);
        u_n_now = *(fluid_.u()->cbegin() + n_x_diff);
        p_n_now = *(fluid_.P()->cbegin() + n_x_diff);

        rho_n_old = *(fluid_old_.rho()->cbegin() + n_x_diff);
        u_n_old = *(fluid_old_.u()->cbegin() + n_x_diff);

        // boundary
        if((*iter_n)->m_x_boundary()){

            p_x_diff = (*iter_n)->x_p_diff();

            rho_p_now = *(fluid_.rho()->cbegin() + p_x_diff);
            u_p_now = *(fluid_.u()->cbegin() + p_x_diff);
            p_p_now = *(fluid_.P()->cbegin() + p_x_diff);

            rho_p_old = *(fluid_old_.rho()->cbegin() + p_x_diff);
            u_p_old = *(fluid_old_.u()->cbegin() + p_x_diff);

            switch (boundary_conditons_.x_m_bc()) {

            case Boundary_condtions::type::calculated :

                A_t_n = (rho_n_now*3/4 + rho_p_now/4)*dx/dt*3/8;
                A_u_n = ((u_p_now >= -u_n_now) ? (u_p_now + u_n_now)*(rho_n_now + rho_p_now)/4 : 0)
                        - rho_n_now*u_n_now;

                *((*iter_A).begin() + n_x_diff) = A_t_n + A_u_n;

                A_t_p = (rho_n_now*3/4 + rho_p_now/4)*dx/dt/8;
                A_u_p = ((u_p_now < -u_n_now) ? (u_p_now + u_n_now)*(rho_n_now + rho_p_now)/4 : 0);

                *((*iter_A).begin() + p_x_diff) = A_t_p + A_u_p;

                *iter_y = (p_n_now - p_p_now)/2 + (rho_n_old*3/4 + rho_p_old/4)*(u_n_old*3/4 + u_p_old/4)*dx/dt/2;

                break;

            case Boundary_condtions::type::fixed_value :

                *((*iter_A).begin() + n_x_diff) = 1.0;

                *iter_y = boundary_conditons_.x_m_bc_v();

                break;

            default:

                std::cerr << "Undefine boundary type." << std::endl;
                break;
            }

        }else if((*iter_n)->p_x_boundary()){

            m_x_diff = (*iter_n)->x_m_diff();

            rho_m_now = *(fluid_.rho()->cbegin() + m_x_diff);
            u_m_now = *(fluid_.u()->cbegin() + m_x_diff);
            p_m_now = *(fluid_.P()->cbegin() + m_x_diff);

            rho_m_old = *(fluid_old_.rho()->cbegin() + m_x_diff);
            u_m_old = *(fluid_old_.u()->cbegin() + m_x_diff);

            switch (boundary_conditons_.x_p_bc()) {

            case Boundary_condtions::type::calculated :

                A_t_n = (rho_n_now*3/4 + rho_m_now/4)*dx/dt*3/8;
                A_u_n = ((u_m_now <= -u_n_now) ? -(u_m_now + u_n_now)*(rho_n_now + rho_m_now)/4 : 0)
                        + rho_n_now*u_n_now;

                *((*iter_A).begin() + n_x_diff) = A_t_n + A_u_n;

                A_t_m = (rho_n_now*3/4 + rho_m_now/4)*dx/dt/8;
                A_u_m = ((u_m_now > -u_n_now) ? -(u_m_now + u_n_now)*(rho_n_now + rho_m_now)/4 : 0);

                *((*iter_A).begin() + m_x_diff) = A_t_m + A_u_m;

                *iter_y = (p_m_now - p_n_now)/2 + (rho_n_old*3/4 + rho_m_old/4)*(u_n_old*3/4 + u_m_old/4)*dx/dt/2;

                break;

            case Boundary_condtions::type::fixed_value :

                *((*iter_A).begin() + n_x_diff) = 1.0;

                *iter_y = boundary_conditons_.x_p_bc_v();

                break;

            default:

                std::cerr << "Undefine boundary type." << std::endl;
                break;
            }
        }else{

            p_x_diff = (*iter_n)->x_p_diff();

            rho_p_now = *(fluid_.rho()->cbegin() + p_x_diff);
            u_p_now = *(fluid_.u()->cbegin() + p_x_diff);
            p_p_now = *(fluid_.P()->cbegin() + p_x_diff);

            m_x_diff = (*iter_n)->x_m_diff();

            rho_m_now = *(fluid_.rho()->cbegin() + m_x_diff);
            u_m_now = *(fluid_.u()->cbegin() + m_x_diff);
            p_m_now = *(fluid_.P()->cbegin() + m_x_diff);

            // internal points

            A_t_n = rho_n_now*dx/dt;

            A_u_n = ((u_n_now >= -u_p_now) ? ((u_p_now + u_n_now)*(rho_p_now + rho_n_now)/4) : 0)
                    - ((u_m_now <= -u_n_now) ? ((u_m_now + u_n_now)*(rho_m_now + rho_n_now)/4) : 0);

            *((*iter_A).begin() + n_x_diff) = A_t_n + A_u_n;

            A_t_m = 0.0;

            A_u_m = -((u_m_now > -u_n_now) ? ((u_m_now + u_n_now)*(rho_m_now + rho_n_now)/4) : 0);

            *((*iter_A).begin() + m_x_diff) = A_t_m + A_u_m;

            A_t_p = 0.0;

            A_u_p = ((u_n_now < -u_p_now) ? ((u_p_now + u_n_now)*(rho_p_now + rho_n_now)/4) : 0);

            *((*iter_A).begin() + p_x_diff) = A_t_p + A_u_p;

            *iter_y = (p_m_now - p_p_now)/2 + rho_n_old*u_n_old*dx/dt;
        }

        ++iter_n;
        ++iter_A;
        ++iter_y;
    }
}

void U_equation::correct(){

    Equation::correct(fluid_.u()->begin(), fluid_.u()->end());

}


void U_equation::solve(){

    calc_A_y();

    Equation::solve();

    correct();
}
