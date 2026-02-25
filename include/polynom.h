#include "forward_list.h"
struct Monom
{
    double coef_;
    int deg_;
    Monom operator+(Monom m)
    {
        Monom res;
        if(deg_ == m.deg_)
        {
            res.coef_ = coef_ + m.coef_;
            res.deg_ = deg_;
        }
        return res;   
    }

    Monom operator-(Monom m)
    {
        Monom res;
        if(deg_ == m.deg_)
        {
            res.coef_ = coef_ - m.coef_;
            res.deg_ = deg_;
        }
        return res;   
    }
};

class Polynom
{
    ForwardList<Monom> p;
    
};