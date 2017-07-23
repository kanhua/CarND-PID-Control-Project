#ifndef PID_H
#define PID_H

#include <limits>
#include <fstream>


using namespace std;

class PID {
public:
    /*
    * Errors
    */
    double p_error;
    double i_error;
    double d_error;

    /*
    * Coefficients
    */
    double Kp;
    double Ki;
    double Kd;

    /*
     * twiddle
     */
    bool twiddle=true;


    ofstream fout;

    /*
     * The best error
     */

    double best_error = std::numeric_limits<double>::infinity();

    /*
     * iteration
     */
    int iteration=0;

    /*
     * delta coefficients
     */
    double d_kp;
    double d_ki;
    double d_kd;


    /*
    * Constructor
    */
    PID();

    /*
    * Destructor.
    */
    virtual ~PID();

    /*
    * Initialize PID.
    */
    void Init(double Kp, double Ki, double Kd);

    /*
    * Update the PID error variables given cross track error.
    */
    void UpdateError(double cte);

    /*
    * Calculate the total PID error.
    */
    double TotalError();


    /*
     * Update the coefficients
     */
    void UpdateP(double cte, double &dp, double &p);

};

#endif /* PID_H */
