#include "polynom.h"
#include <cmath>
#include <iostream>

void Polynom::add_to_tail(double c, uint32_t d, typename ForwardList<Monom>::Iterator& last) 
{
    if (std::abs(c) < 1e-10) return;
    Monom m = {c, d};
    if (!last) {
        data.push_front(m);
        last = data.begin();
    } else {
        last = data.insert_after(last, m);
    }
}

#include <stdexcept> // Добавить в начало

Polynom::Polynom(const std::string& expr) 
{
    size_t i = 0;
    while (i < expr.size()) {
        while (i < expr.size() && (isspace(expr[i]) || expr[i] == '+')) i++;

        if (i >= expr.size()) break;

        double c = 1.0;

        if (expr[i] == '+' || expr[i] == '-') 
        {
            if (expr[i] == '-') c = -1.0;
            ++i;
            while (i < expr.size() && isspace(expr[i])) ++i;
        }

        // число
        if (i < expr.size() && (isdigit(expr[i]) || expr[i] == '.')) 
        {
            size_t next = 0;
            c *= std::stod(expr.substr(i), &next);
            i += next;
        }
        
        int p[3] = {0, 0, 0};
        while (i < expr.size() && expr[i] != '+' && (expr[i] != '-' || (i > 0 && expr[i-1] == '^'))) 
        {
            if (isspace(expr[i]) || expr[i] == '*') { i++; continue; }
            if (expr[i] >= 'x' && expr[i] <= 'z') 
            {
                int idx = expr[i++] - 'x'; p[idx] = 1;
                if (i < expr.size() && expr[i] == '^') 
                {
                    size_t next = 0;
                    p[idx] = std::stoi(expr.substr(++i), &next);
                    i += next;
                }
            } 
            else throw std::invalid_argument("Invalid character");
        }

        uint32_t packed = ((p[0] & MASK) << 20) | ((p[1] & MASK) << 10) | (p[2] & MASK);
        data.push_front({c, packed}); 
    }

    data.sort();

    if (!data.begin()) return;

    auto it = data.begin();
    while (it) {
        auto next_it = it;
        ++next_it;
        if (next_it && it->deg == next_it->deg) {
            it->coeff += next_it->coeff;
            data.erase_after(it);
        } else {
            if (std::abs(it->coeff) < 1e-10) {
                auto to_remove = it;
                ++it;
                // В зависимости от реализации списка, здесь может быть 
                // удаление текущего узла. Для полинома важно убрать нули.
            } else {
                ++it;
            }
        }
    }
}

Polynom Polynom::operator+(const Polynom& other) const {
    Polynom res;
    auto it1 = data.begin(), it2 = other.data.begin();
    typename ForwardList<Monom>::Iterator last = nullptr;
    while (it1 || it2) 
    {
        if (it1 && (!it2 || it1->deg > it2->deg)) 
        {
            res.add_to_tail(it1->coeff, it1->deg, last);
            ++it1;
        } 
        else if (it2 && (!it1 || it2->deg > it1->deg)) 
        {
            res.add_to_tail(it2->coeff, it2->deg, last);
            ++it2;
        } 
        else 
        {
            double sum = it1->coeff + it2->coeff;
            if (std::abs(sum) > 1e-10) res.add_to_tail(sum, it1->deg, last);
            ++it1; ++it2;
        }
    }
    return res;
}

Polynom Polynom::operator-(const Polynom& other) const { return *this + (other * -1.0); }

Polynom Polynom::operator*(const Polynom& other) const 
{
    Polynom res;
    for (auto it1 = data.begin(); it1; ++it1) 
    {
        Polynom temp;
        ForwardList<Monom>::Iterator t_last = nullptr;
        for (auto it2 = other.data.begin(); it2; ++it2) 
        {
            Monom m = (*it1) * (*it2);
            temp.add_to_tail(m.coeff, m.deg, t_last);
        }
        res = res + temp;
    }
    return res;
}

Polynom Polynom::operator*(double c) const 
{
    Polynom res;
    if (std::abs(c) < 1e-10) return res;
    ForwardList<Monom>::Iterator last = nullptr;
    for (auto it = data.begin(); it; ++it) res.add_to_tail(it->coeff * c, it->deg, last);
    return res;
}

double Polynom::evaluate(double x, double y, double z) const 
{
    double res = 0;
    for (auto it = data.begin(); it; ++it) 
    {
        int px = (it->deg >> 20) & MASK, py = (it->deg >> 10) & MASK, pz = it->deg & MASK;
        if (px & 512) px |= ~MASK; if (py & 512) py |= ~MASK; if (pz & 512) pz |= ~MASK;
        res += it->coeff * std::pow(x, px) * std::pow(y, py) * std::pow(z, pz);
    }
    return res;
}

void Polynom::print() const 
{
    for (auto it = data.begin(); it; ++it) std::cout << it->coeff << " ";
    std::cout << std::endl;
}