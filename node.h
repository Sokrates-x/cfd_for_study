#ifndef NODE_H
#define NODE_H

#include <memory>
#include <vector>

#include "fluid.h"

class Node
{
public:

    // constructor
    Node(const double &x, const std::vector<std::shared_ptr<Node> >::size_type &id) :
        coordinate_x_(x), id_(id) {   }

    // method
    std::shared_ptr<Node> &n_x_p() { return node_x_plus_; }

    std::shared_ptr<Node> &n_x_m() { return node_x_minus_; }

    double &x() { return coordinate_x_; }

    bool &m_x_boundary() { return x_minus_boundary_; }

    bool &p_x_boundary() { return x_plus_boundary_; }

    std::vector<std::shared_ptr<Node> >::size_type &id() { return id_; }

    std::vector<std::shared_ptr<Node> >::difference_type &x_p_diff() {
        return x_plus_diff_;
    }

    std::vector<std::shared_ptr<Node> >::difference_type &x_m_diff() {
        return x_minus_diff_;
    }

    std::vector<std::shared_ptr<Node> >::difference_type &x_n_diff() {
        return x_now_diff_;
    }

    // const methods
    const std::shared_ptr<Node> &n_x_p() const { return node_x_plus_; }

    const std::shared_ptr<Node> &n_x_m() const { return node_x_minus_; }

    const double &x() const { return coordinate_x_; }

    const bool &m_x_boundary() const { return x_minus_boundary_; }

    const bool &p_x_boundary() const { return x_plus_boundary_; }

    const std::vector<std::shared_ptr<Node> >::size_type &id() const {
        return id_;
    }

    const std::vector<std::shared_ptr<Node> >::difference_type &x_p_diff() const {
        return x_plus_diff_;
    }

    const std::vector<std::shared_ptr<Node> >::difference_type &x_m_diff() const {
        return x_minus_diff_;
    }

    const std::vector<std::shared_ptr<Node> >::difference_type &x_n_diff() const {
        return x_now_diff_;
    }

private:

    // members
    std::shared_ptr<Node> node_x_plus_ = nullptr;

    std::shared_ptr<Node> node_x_minus_ = nullptr;

    double coordinate_x_ = 0.0;

    bool x_minus_boundary_ = false;

    bool x_plus_boundary_ = false;

    std::vector<std::shared_ptr<Node> >::size_type id_ = 0;

    std::vector<std::shared_ptr<Node> >::difference_type x_plus_diff_ = 0;

    std::vector<std::shared_ptr<Node> >::difference_type x_minus_diff_ = 0;

    std::vector<std::shared_ptr<Node> >::difference_type x_now_diff_ = 0;

};

#endif // NODE_H
