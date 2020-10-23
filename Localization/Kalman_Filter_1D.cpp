//Localization Module
// Implementation and Visualization of a 1-D Kalman Filter

#include <iostream>
#include <math.h>
#include <tuple>
#include "matplotlibcpp.h"

using namespace std;

double new_mean, new_var;

tuple<double, double> measurement_update(double mean1, double var1, double mean2, double var2)
{
    new_mean = (var2 * mean1 + var1 * mean2) / (var1 + var2);
    new_var = 1 / (1 / var1 + 1 / var2);
    return make_tuple(new_mean, new_var);
}

tuple<double, double> state_prediction(double mean1, double var1, double mean2, double var2)
{
    new_mean = mean1 + mean2;
    new_var = var1 + var2;
    return make_tuple(new_mean, new_var);
}

int main()
{
    //Measurements and measurement variance
    double measurements[5] = { 5, 6, 7, 9, 10 };
    double measurement_sig = 4;
    
    //Motions and motion variance
    double motion[5] = { 1, 1, 2, 1, 1 };
    double motion_sig = 2;
    
    //Initial state
    double mu = 0;
    double sig = 5;
    //Visualization
    matplotlibcpp::figure(1);
    matplotlibcpp::title("Actual Motion vs Prediction");
    matplotlibcpp::legend();

  

vector<double> mu_vector;
vector<double> sig_vector;
vector<double> mu_vector1;
vector<double> sig_vector1;
vector<double> mu_motion{ 5, 6, 7, 9, 10 };
vector<double> sig_motion{2,2,2,2,2};
mu_motion.push_back(0);
sig_motion.push_back(0);


mu_vector1.push_back(mu);
sig_vector1.push_back(sig);

    for (int i = 0; i < sizeof(measurements)/sizeof(measurements[i]); i++) {
        
        tie(mu, sig) = measurement_update(mu, sig, measurements[i], measurement_sig);
        printf("update:  [%f, %f]\n", mu, sig);
        
        //mu_vector.push_back(mu);
        //sig_vector.push_back(sig);
        
        
        tie(mu, sig) = state_prediction(mu, sig, motion[i], motion_sig);
        printf("predict: [%f, %f]\n", mu, sig);
        
        mu_vector1.push_back(mu);
        sig_vector1.push_back(sig);
        
        matplotlibcpp::named_plot("State Prediction",mu_vector1,sig_vector1);
        matplotlibcpp::named_plot("Motion",mu_motion,sig_motion);

        
        
    }
    matplotlibcpp::show();
        matplotlibcpp::pause(0.001);
    //matplotlibcpp::show();
    return 0;
}
// Compile Flags g++ -I /usr/include/python2.7 Kalman1D.cpp -lpython2.7 
