#ifndef BOUNDARY_CONDTIONS_H
#define BOUNDARY_CONDTIONS_H


class Boundary_condtions
{
public:

    // boundary types
    enum type { fixed_value, calculated };

    // constructors
    Boundary_condtions() = delete;

    Boundary_condtions(const type &xm, const double &xmv,
                       const type &xp, const double&xpv):
        x_m_boundary_(xm), x_m_value_(xmv),
        x_p_boundary_(xp), x_p_value_(xpv) {    }

    // methods
    type &x_m_bc() { return x_m_boundary_; }

    double &x_m_bc_v() { return x_m_value_; }

    type &x_p_bc() { return x_p_boundary_; }

    double &x_p_bc_v() { return x_p_value_; }

    // const methods
    const type &x_m_bc() const { return x_m_boundary_; }

    const double &x_m_bc_v() const { return x_m_value_; }

    const type &x_p_bc() const { return x_p_boundary_; }

    const double &x_p_bc_v() const { return x_p_value_; }

private:

    // members
    type x_m_boundary_;

    double x_m_value_;

    type x_p_boundary_;

    double x_p_value_;
};

#endif // BOUNDARY_CONDTIONS_H
