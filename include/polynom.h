#ifndef POLYNOM_H
#define POLYNOM_H

#include "forward_list.h"
#include <string>
#include <cstdint>

constexpr uint32_t MASK = 1023;
struct Monom 
{
    double coeff;
    uint32_t deg;

    Monom operator*(const Monom& other) const 
    { 
        uint32_t d = ((((deg >> 20) + (other.deg >> 20)) & MASK) << 20) |
                    ((((deg >> 10) + (other.deg >> 10)) & MASK) << 10) |
                    (((deg + other.deg) & MASK));
        return {coeff * other.coeff, d}; 
    }
};

class Polynom
{
private:
    ForwardList<Monom> data;
    void add_to_tail(double c, uint32_t d, ForwardList<Monom>::Iterator& last);

public:
    Polynom() {}
    Polynom(const std::string& expr);

    Polynom operator+(const Polynom& other) const;
    Polynom operator-(const Polynom& other) const;
    Polynom operator*(const Polynom& other) const;
    Polynom operator*(double с) const;
    
    double evaluate(double x, double y, double z) const;
    void print() const;
};

#endif