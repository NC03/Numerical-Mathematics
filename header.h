#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <fstream>

using namespace std;

struct State
{
    vector<double> vars;
};
typedef function<double(State)> DifferentialEquation;
struct DiffEqs
{
    // vector<DifferentialEquation> differentialEquations;
    vector<function<double(State)>> differentialEquations;
    State apply(State conditions)
    {
        int idx = 0;
        State out;
        for (function<double(State)> diffEq : differentialEquations)
        {
            out.vars.push_back(diffEq(conditions));
        }
        return out;
    }
};

double func(double x);
double lram(double (*f)(double), double a, double b, const int n = 200);
double rram(double (*f)(double), double a, double b, const int n = 200);
double mram(double (*f)(double), double a, double b, const int n = 200);
double trap(double (*f)(double), double a, double b, const int n = 200);
double simpson(double (*f)(double), double a, double b, const int n = 200);
double integrate(double (*f)(double), double a, double b);
double differentiate(double (*f)(double), double x, double dx = 1e-2);
double integrate(function<double(double)> func, double a, double b, const int n = 400);
double sol(double x);
State operator*(State a, double b);
State operator*(double a, State b);
State operator+(State a, State b);
State next(State initial, DiffEqs eqs, double h = 0.5);
State euler(State initial, DiffEqs eqs, double h = 0.5);