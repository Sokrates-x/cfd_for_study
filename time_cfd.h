#ifndef TIME_CONTROL_H
#define TIME_CONTROL_H

#include <cstddef>
#include <cmath>

class Time
{
public:

    // constructors
    Time() = delete;

    Time(const size_t &ts, const double &tt) : time_steps_(ts), delta_time_(tt/(ts - 1)),
        total_time_(tt) {    }

    // opreators

    Time &operator++(){
        now_time_ += delta_time_;
        ++now_step_;
        time_changed_ = true;
        return *this;
    }


    // methods
    double &d_t() { return delta_time_; }

    double &total_t() { return total_time_; }

    size_t &n_t() { return time_steps_; }

    double &now() { return now_time_; }

    size_t &w_intervel() { return write_intervel_; }

    bool &time_changed() { return time_changed_; }

    // const methods

    const double &d_t() const {return delta_time_; }

    const double &total_t() const { return total_time_; }

    const size_t &n_t() const { return time_steps_; }

    bool write_time() {

        if(end_time()){

            return true;
        }
        if(now_step_%write_intervel_){

            return false;
        }
        return true;
    }

    bool end_time() { return now_step_ == time_steps_; }

    const double &now() const { return now_time_; }

    const size_t &w_intervel() const { return write_intervel_; }

    const size_t &now_step() const { return now_step_; }

    const bool &time_changed() const { return time_changed_; }

private:

    //members
    size_t time_steps_ = 1;

    double delta_time_ = 0.0;

    size_t write_intervel_ = 1;

    double now_time_ = 0.0;

    double total_time_ = 0.0;

    size_t now_step_ = 0;

    bool time_changed_ = false;
};


#endif // TIME_CONTROL_H
