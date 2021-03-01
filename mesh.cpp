#include "mesh.h"

double Mesh::delta_x_ = 0.0;

Mesh::Mesh(const std::vector<std::shared_ptr<Node> >::size_type &nx)
    : node_x_(nx), length_x_(delta_x_*(nx - 1)) {

    for(std::vector<std::shared_ptr<Node> >::size_type i = 0; i < node_x_; ++i) {

        double x = delta_x_*i;

        if(x <= (length_x_ + 1e-20)){

            auto node = std::make_shared<Node>(x, i);

            if(fabs(x) < 1e-20){

                node->m_x_boundary() = true;
                node->n_x_m() = nullptr;
                node->x_m_diff() = node_x_;

            }else if(fabs(x - length_x_) < 1e-20){

                node->p_x_boundary() = true;
                node->n_x_p() = nullptr;
                node->x_p_diff() = node_x_;

            }

            vec_node_pointer_.push_back(node);

        }
    }

    std::vector<std::shared_ptr<Node> >::size_type temp;

    for(auto iter = vec_node_pointer_.begin(); iter!=vec_node_pointer_.end(); ++iter) {

        (*iter)->x_n_diff() = iter - vec_node_pointer_.begin();

        if(!(*iter)->m_x_boundary()){

            temp = (*iter)->id() - 1;

            auto iter_x_m = find_if(vec_node_pointer_.begin(),
                                    vec_node_pointer_.end(),
                                    [temp](std::shared_ptr<Node> &n)
            { return n->id()==temp; });

            if(iter_x_m != vec_node_pointer_.end()){

                (*iter)->n_x_m() = *iter_x_m;
                (*iter)->x_m_diff() = iter_x_m - vec_node_pointer_.begin();

            }else{

                std::cerr << "Sth. wrong with x minus boundary." << std::endl;

            }
        }

        if(!(*iter)->p_x_boundary()){

            temp = (*iter)->id() + 1;

            auto iter_x_p = find_if(vec_node_pointer_.begin(),
                                    vec_node_pointer_.end(),
                                    [temp](std::shared_ptr<Node> &n)
            { return n->id()==temp; });

            if(iter_x_p != vec_node_pointer_.end()){

                (*iter)->n_x_p() = *iter_x_p;
                (*iter)->x_p_diff() = iter_x_p - vec_node_pointer_.begin();

            }else{

                std::cerr << "Sth. wrong with x plus boundary." << std::endl;

            }
        }
    }
}
