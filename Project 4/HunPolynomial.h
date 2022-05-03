#pragma once
#include <iostream>
#include<cmath>
#include <vector>
#include <stack>
using std::ostream, std::vector, std::stack;


class HunPolynomial
{
private:
    vector<int> coefficiants;

public:
    HunPolynomial();
    HunPolynomial(const vector<int>& coefficiants);

    void Set(const vector<int>& coefficiants);
    HunPolynomial operator+(const HunPolynomial& other) const;
    HunPolynomial operator-(const HunPolynomial& other) const;
    HunPolynomial operator*(const HunPolynomial& other) const;
    friend ostream& operator<<(ostream& out, const HunPolynomial& polynomial);
    float operator()(const float& x) const;
};