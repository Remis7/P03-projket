#include "Racionalne.h"

void Racionalne::zjednodus()
{
    if (menovatel == 0)
    {
        throw runtime_error("CHYBA: Menovatel nemoze byt nula!!!");
    }
    if (menovatel < 0)
    {
        menovatel = -menovatel;
        citatel = -citatel;
    }
    int common = gcd(abs(citatel), abs(menovatel));
    citatel /= common;
    menovatel /= common;
}

// konstruktor
Racionalne::Racionalne(int c, int m) : citatel(c), menovatel(m)
{
    zjednodus();
}

// getery
int Racionalne::getNum() const
{
    return citatel;
}

int Racionalne::getDen() const
{
    return menovatel;
}

// binarni operatory
Racionalne operator+(const Racionalne& lhs, const Racionalne& rhs)
{
    return Racionalne(lhs.citatel * rhs.menovatel + rhs.citatel * lhs.menovatel, lhs.menovatel * rhs.menovatel);
}

Racionalne operator-(const Racionalne& lhs, const Racionalne& rhs)
{
    return Racionalne(lhs.citatel * rhs.menovatel - rhs.citatel * lhs.menovatel, lhs.menovatel * rhs.menovatel);
}

Racionalne operator*(const Racionalne& lhs, const Racionalne& rhs)
{
    return Racionalne(lhs.citatel * rhs.citatel, lhs.menovatel * rhs.menovatel);
}

Racionalne operator/(const Racionalne& lhs, const Racionalne& rhs)
{
    if (rhs.citatel == 0)
    {
        throw runtime_error("CHYBA: delenie nulou!!!");
    }
    return Racionalne(lhs.citatel * rhs.menovatel, lhs.menovatel * rhs.citatel);
}

// operatory porovnavania
bool Racionalne::operator==(const Racionalne& other) const
{
    return citatel == other.citatel && menovatel == other.menovatel;
}

bool Racionalne::operator!=(const Racionalne& other) const
{
    return !(*this == other);
}

// operator vypisu
ostream& operator<<(ostream& os, const Racionalne& r)
{
    if (r.menovatel == 1)
    {
        os << r.citatel;
    }
    else
    {
        os << r.citatel << "/" << r.menovatel;
    }
    return os;
}
