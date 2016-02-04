#include "rational.h"

rational add(rational a, rational b) {
    rational c;
    c.den = a.den * b.den;
    c.num = a.num*b.den + b.num*a.den;
    return c;
}

rational mul(rational a, int scale) {
    rational c;
    c.den = a.den;
    c.num = a.num*scale;
    return c;
}

rational divide(rational a, int scale) {
    rational c;
    c.num = a.num;
    c.den = a.den*scale;
    return c;
}

double to_double(rational a) {
    return (double)a.num / (double)a.den;
}