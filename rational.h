#pragma once

typedef struct {
    int num;
    int den;
} rational;

rational add(rational a, rational b);
rational sub(rational a, rational b);
rational mul(rational a, rational b);
rational divide(rational a, rational b);
double to_double(rational a);