#include "PID.h"

#include <cmath>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {

    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;

    p_error = 0;
    i_error = 0;
    d_error = 0;

    d_kd = Kd * 0.001;
    d_ki = Ki * 0.001;
    d_kp = Kp * 0.001;

    // file to record CTE
    fout=ofstream("testout6.csv");


}

void PID::UpdateError(double cte) {

    d_error = cte - p_error;
    p_error = cte;
    i_error += cte;

    fout << cte <<endl;

    double dp_sum = fabs(d_kd) + fabs(d_ki) + fabs(d_kp);


    if ((dp_sum > 1e-5) && twiddle) {

        if (iteration % 3 == 0) {

            UpdateP(cte, d_kp, Kp);
        } else if (iteration % 3 == 1) {

            UpdateP(cte, d_ki, Ki);
        } else if (iteration % 3 == 2) {

            UpdateP(cte, d_kd, Kd);
        }

    }

    iteration++;

}

double PID::TotalError() {

    return -Kp * p_error - Ki * i_error - Kd * d_error;
}

void PID::UpdateP(double cte, double &dp, double &p) {

    // Twiddle algorithms to update the PID values
    if (dp > 0) {

        if (fabs(cte) < best_error) {

            best_error = fabs(cte);
            dp *= 1.1;
            p += dp;

        } else {
            dp = -dp;
            p += 2 * dp;
        }
    } else if (dp < 0) {

        if (fabs(cte) < best_error) {

            best_error = fabs(cte);
            dp *= 1.1;
            p += dp;

        } else {

            p -= dp;
            dp *= -0.9;
            p += dp;
        }
    }

}

