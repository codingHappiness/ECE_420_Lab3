#include "rational.h"

rational add(rational a, rational b) {
    rational c;
    c.den = a.den * b.den;
    c.num = a.num*b.den + b.num*a.den;
    return c;
}

rational sub(rational a, rational b) {
    rational c;
    c.den = a.den * b.den;
    c.num = a.num*b.den - b.num*a.den;
    return c;
}

rational mul(rational a, rational b) {
    rational c;
    c.den = a.den*b.den;
    c.num = a.num*b.num;
    return c;
}

rational divide(rational a, rational b) {
    rational c;
    c.num = a.num*b.den;
    c.den = a.den*b.num;
    return c;
}

double to_double(rational a) {
    return (double)a.num / (double)a.den;
}