#include "HunPolynomial.h"

HunPolynomial::HunPolynomial() : coefficiants({}) {}

HunPolynomial::HunPolynomial(const vector<int>& coefficiants) : coefficiants(coefficiants) {}

void HunPolynomial::TrimCoefficiants()
{
    vector<int> trimmedCoefficiants;
    bool leadingZero = true;

    for (int i = 0; i < coefficiants.size(); ++i)
    {
        if (coefficiants[i] != 0)
        {
            leadingZero = false;
            trimmedCoefficiants.push_back(coefficiants[i]);
        }
        else if (!leadingZero)
            trimmedCoefficiants.push_back(coefficiants[i]);
    }

    coefficiants = trimmedCoefficiants;
}

void HunPolynomial::Set(const vector<int>& coefficiants) { this->coefficiants = coefficiants; }

HunPolynomial HunPolynomial::operator+(const HunPolynomial& other) const
{
    stack<int> result;
    int i = coefficiants.size() - 1, j = other.coefficiants.size() - 1;

    while (i >= 0 || j >= 0)
    {
        int sum = 0;

        if (i >= 0)
        {
            sum += coefficiants[i];
            --i;
        }

        if (j >= 0)
        {
            sum += other.coefficiants[j];
            --j;
        }

        result.push(sum);
    }

    vector<int> resultVector;
    while (!result.empty())
    {
        resultVector.push_back(result.top());
        result.pop();
    }

    return HunPolynomial(resultVector);
}

HunPolynomial HunPolynomial::operator-(const HunPolynomial& other) const
{
    stack<int> result;
    int i = coefficiants.size() - 1, j = other.coefficiants.size() - 1;

    while (i >= 0 || j >= 0)
    {
        int difference = 0;

        if (i >= 0)
        {
            difference += coefficiants[i];
            --i;
        }

        if (j >= 0)
        {
            difference -= other.coefficiants[j];
            --j;
        }

        result.push(difference);
    }

    vector<int> resultVector;
    while (!result.empty())
    {
        resultVector.push_back(result.top());
        result.pop();
    }

    return HunPolynomial(resultVector);
}

HunPolynomial HunPolynomial::operator*(const HunPolynomial& other) const
{
    vector<int> result((coefficiants.size() + other.coefficiants.size()), 0);

    for (int i = 0; i < coefficiants.size(); ++i)
    {
        unsigned int power1 = (coefficiants.size() - 1) - i;

        for (int j = 0; j < other.coefficiants.size(); ++j)
        {
            unsigned int power2 = (other.coefficiants.size() - 1) - j;
            unsigned int power = (result.size() - 1) - (power1 + power2);

            result[power] += coefficiants[i] * other.coefficiants[j];
        }
    }

    return HunPolynomial(result);
}

ostream& operator<<(ostream& out, HunPolynomial& polynomial)
{
    polynomial.TrimCoefficiants();

    if (polynomial.coefficiants.size() == 1 && polynomial.coefficiants[0] != 0)
    {
        if (polynomial.coefficiants[0] > 0)
            out << polynomial.coefficiants[0];
        else
            out << "- " << -polynomial.coefficiants[0];

        return out;
    }

    for (int i = 0; i < polynomial.coefficiants.size(); ++i)
    {
        int coefficiant = polynomial.coefficiants[i];
        if (coefficiant == 0)
            continue;
        if (i == 0)
        {
            if (coefficiant > 0 && coefficiant != 1)
                out << coefficiant << "*";
            else if (coefficiant < 0 && coefficiant != -1)
                out << "- " << -coefficiant << "*";
            else if (coefficiant == -1)
                out << "- ";
        }
        else if (i > 0 && i < polynomial.coefficiants.size() - 1)
        {
            if (coefficiant > 0 && coefficiant != 1)
                out << " + " << coefficiant << "*";
            else if (coefficiant < 0 && coefficiant != -1)
                out << " - " << -coefficiant << "*";
            else if (coefficiant == 1)
                out << " + ";
            else if (coefficiant == -1)
                out << " - ";
        }
        else if (i == polynomial.coefficiants.size() - 1)
        {
            if (coefficiant > 0)
                out << " + " << coefficiant;
            else if (coefficiant < 0)
                out << " - " << -coefficiant;
        }

        if (i < polynomial.coefficiants.size() - 2)
            out << "x^" << (polynomial.coefficiants.size() - 1 - i);
        else if (i == polynomial.coefficiants.size() - 2)
            out << "x";
    }

    return out;
}

float HunPolynomial::operator()(const float& x) const
{
    float result = 0;

    for (int i = 0; i < coefficiants.size(); ++i)
        result += coefficiants[i] * pow(x, coefficiants.size() - 1 - i);

    return result;
}