#pragma once

#typedef struct {
    int num;
    int den;
} rational;

rational add(rational a, rational b);
rational mul(rational a, int scale);
rational div(rational a, int scale);
double to_double(rational a);