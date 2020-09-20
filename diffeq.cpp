#include <functional>
#include <iostream>
#include <vector>

using namespace std;

struct State
{
    vector<double> vars;
};
struct DiffEqs
{
    vector<function<double(State)>> funcs;
    State apply(State conditions)
    {
        int idx = 0;
        State out;
        for (function<double(State)> diffEq : funcs)
        {
            out.vars.push_back(diffEq(conditions));
        }
        return out;
    }
};

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

int main()
{

    DiffEqs eqs = {
        {[](State s) -> double {
             return s.vars[0];
         },
         [](State s) -> double {
             return s.vars[1];
         },
         [](State s) -> double {
             return s.vars[2];
         }}};

    State initial = {{1, 2, 3}};
    double h = 0.5;

    for (int i = 0; i < 10; i++)
    {
        State a = eqs.apply(initial);
        State b = eqs.apply(initial + (h / 2) * a);
        State c = eqs.apply(initial + (h / 2) * b);
        State d = eqs.apply(initial + h * c);
        State next = initial + (h / 6) * (a + 2 * b + 2 * c + d);
        initial = next;
    }
    for (double v : initial.vars)
    {
        cout << v << ' ';
    }
}