#pragma once
#include <iostream>
#include <stdexcept>
#include <numeric>

using namespace std;
class Racionalne
{
private:
    long long citatel;
    long long menovatel;
    void zjednodus()
    {
        if (menovatel == 0)
        {
            throw runtime_error("Menovatel nemoze byt nula!!");
        }
        if (menovatel < 0)
        {
            menovatel = -menovatel;
            citatel = -citatel;
        }
        long long common = gcd(abs(citatel), abs(menovatel));
        citatel /= common;
        menovatel /= common;
    }
public:
    // konstruktory
    Racionalne(long long c = 0, long long m = 1) : citatel(c), menovatel(m)
    {
        zjednodus();
    }
    // gettery
    long long getNum() const
    {
        return citatel;
    }
    long long getDen() const
    {
        return menovatel;
    }
    // operator plus
    friend Racionalne operator+(const Racionalne& lhs, const Racionalne& rhs) {
        return Racionalne(lhs.citatel * rhs.menovatel + rhs.citatel * lhs.menovatel, lhs.menovatel * rhs.menovatel);
    }
    // operator minus
    friend Racionalne operator-(const Racionalne& lhs, const Racionalne& rhs) { 
        return Racionalne(lhs.citatel * rhs.menovatel - rhs.citatel * lhs.menovatel, lhs.menovatel * rhs.menovatel); }
    // operator krat
    friend Racionalne operator*(const Racionalne& lhs, const Racionalne& rhs) { 
        return Racionalne(lhs.citatel * rhs.citatel, lhs.menovatel * rhs.menovatel); }
    // operator deleno
    friend Racionalne operator/(const Racionalne& lhs, const Racionalne& rhs) {
        if (rhs.citatel == 0)
        {
            throw runtime_error("delenie nulou!!");
        }
        return Racionalne(lhs.citatel * rhs.menovatel, lhs.menovatel * rhs.citatel);
    }
    // operatory porovnavania
    bool operator==(const Racionalne& other) const
    {
        return citatel == other.citatel && menovatel == other.menovatel;
    }
    bool operator!=(const Racionalne& other) const
    {
        return !(*this == other);
    }
    // operator na vypis
    friend ostream& operator<<(ostream& os, const Racionalne& r)
    {
        if (r.menovatel == 1) os << r.citatel;
        else os << r.citatel << "/" << r.menovatel;
        return os;
    }
};
