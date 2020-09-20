#include "header.h"

// int main(int argc, char *argv[])
// {
//     // double a = 0;
//     // double b = M_PI/2;
//     cout.precision(8);
//     cout.setf(ios::showpoint);
//     cout.setf(ios::fixed);
//     // double ans = sol(b) - sol(a);
//     // cout << "Left Rectangular Approximation Method: " << lram(func, a, b) << " " << abs(ans - lram(func, a, b)) << endl;
//     // cout << "Right Rectangular Approximation Method: " << rram(func, a, b) << " " << abs(ans - rram(func, a, b)) << endl;
//     // cout << "Midpoint Rectangular Approximation Method: " << mram(func, a, b) << " " << abs(ans - mram(func, a, b)) << endl;
//     // cout << "Trapezoidal Approximation Method: " << trap(func, a, b) << " " << abs(ans - trap(func, a, b)) << endl;
//     // cout << "Simpsons Approximation Method: " << simpson(func, a, b) << " " << abs(ans - simpson(func, a, b)) << endl;
//     // cout << "Simpsons Approximation Method n=400: " << simpson(func, a, b,400) << " " << abs(ans - simpson(func, a, b,400)) << endl;
//     // cout << "Answer: " << ans << endl;
//     // cout << simpson([](double x) -> double{
//     //     return x*x;
//     // },0,1,200);

    
//     return 0;
// }

double lram(double (*f)(double), double a, double b, const int n)
{
    double sum = 0;
    double dx = (b - a) / n;
    for (int i = 0; i < n; i++)
    {
        sum += f(a + dx * i) * dx;
    }
    return sum;
}
double rram(double (*f)(double), double a, double b, const int n)
{
    double sum = 0;
    double dx = (b - a) / n;
    for (int i = 0; i < n; i++)
    {
        sum += f(a + dx * (i + 1)) * dx;
    }
    return sum;
}
double mram(double (*f)(double), double a, double b, const int n)
{
    double sum = 0;
    double dx = (b - a) / n;
    for (int i = 0; i < n; i++)
    {
        sum += f(a + 0.5 * dx * (2 * i + 1)) * dx;
    }
    return sum;
}
double trap(double (*f)(double), double a, double b, const int n)
{
    double sum = 0;
    double dx = (b - a) / n;
    for (int i = 1; i < n; i++)
    {
        sum += 2 * f(a + i * dx);
    }
    sum += f(a) + f(b);
    return sum * 0.5 * dx;
}
double simpson(double (*f)(double), double a, double b, const int n)
{
    // 1    1 4 1
    // 2    1 4 2 4 1
    // 3    1 4 2 4 2 4 1

    double sum = 0;
    double dx = (b - a) / (2 * n);
    // sum += f(a) + f(b);
    for (int i = 0; i <= 2 * n; i++)
    {
        double x = a + dx * i;
        if (i == 0 || i == 2 * n)
        {
            // cout << 1;
            sum += f(x);
        }
        else if (i % 2 == 1)
        {
            // cout << 4;
            sum += 4 * f(x);
        }
        else
        {
            // cout << 2;
            sum += 2 * f(x);
        }
    }
    // for (int i = 0; i < n / 2; i++)
    // {
    //     sum += 4 * f(a + 2 * i * dx) + 2 * f(a + (2 * i + 1) * dx);
    // }
    // sum += 4 * f(a + 0.5 * n * dx);
    return (b - a) / 6 / n * sum;
}
double integrate(double (*f)(double), double a, double b)
{
    return simpson(f, a, b);
}
double differentiate(double (*f)(double), double x, double dx)
{
    double quotient = f(x + dx) - f(x - dx);
    return quotient / 2 / dx;
}
double integrate(function<double(double)> func, double a, double b, const int n)
{
    double sum = 0;
    double dx = (b - a) / (2 * n);
    for (int i = 0; i <= 2 * n; i++)
    {
        double x = a + dx * i;
        if (i == 0 || i == 2 * n)
        {
            sum += func(x);
        }
        else if (i % 2 == 1)
        {
            sum += 4 * func(x);
        }
        else
        {
            sum += 2 * func(x);
        }
    }
    return (b - a) / 6 / n * sum;
}
double sol(double x)
{
    return exp(x);
    // return 0.25 * pow(x, 4) + 4.0 / 3 * pow(x, 3) + 21.0 / 2 * pow(x, 2) - 55 * x;
}
double func(double x)
{
    double m = 0.015;
    double k = sqrt(m);
    return sqrt(1 - pow(k, 2) * pow(sin(x), 2));
    // return exp(x);
    // return pow(x, 3) + 4 * pow(x, 2) + 21 * x - 55;
}
State operator*(State a, double b)
{
    State out;
    for (double v : a.vars)
    {
        out.vars.push_back(v * b);
    }
    return out;
}
State operator*(double b, State a)
{
    return a * b;
}
State operator+(State a, State b)
{
    State out;
    for (int i = 0; i < a.vars.size(); i++)
    {
        out.vars.push_back(a.vars.at(i) + b.vars.at(i));
    }
    return out;
}
State next(State initial, DiffEqs eqs, double h)
{
    State a = eqs.apply(initial);
    State b = eqs.apply(initial + (h / 2) * a);
    State c = eqs.apply(initial + (h / 2) * b);
    State d = eqs.apply(initial + h * c);
    State next = initial + (h / 6) * (a + 2 * b + 2 * c + d);
    return next;
}
State euler(State initial, DiffEqs eqs, double h)
{
    return initial + eqs.apply(initial)*h;
}