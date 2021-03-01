#ifndef MESH_H
#define MESH_H

#include <cstddef>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <memory>

#include "node.h"

class Mesh
{
public:

    Mesh() = delete;

    Mesh(const std::vector<std::shared_ptr<Node> >::size_type &dx);

    // method
    double &l_x() { return length_x_; }

    static double &d_x() { return delta_x_; }

    size_t &n_x() { return node_x_; }

    std::vector<std::shared_ptr<Node> > &vec_node_p() {
        return vec_node_pointer_;
    }

    // const method
    const double &l_x() const { return length_x_; }

    const size_t &n_x() const { return node_x_; }

    const std::vector<std::shared_ptr<Node> > &vec_node_p() const {
        return vec_node_pointer_;
    }

private:

    static double delta_x_;

    size_t node_x_ = 2;

    double length_x_ = 0.0;

    std::vector<std::shared_ptr<Node> > vec_node_pointer_;
};

#endif // MESH_H
