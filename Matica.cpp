#include "Matica.h"

// alokacia
void Matica::alokuj(int r, int s)
{
    riadky = r;
    stlpce = s;
    data = new Racionalne * [riadky];
    for (int i = 0; i < riadky; ++i)
    {
        data[i] = new Racionalne[stlpce];
    }
}

// dealokacia
void Matica::dealokuj()
{
    if (data != nullptr)
    {
        for (int i = 0; i < riadky; ++i)
        {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }
}

// konstruktor
Matica::Matica(int r, int s)
{
    if (r <= 0 || s <= 0)
    {
        throw runtime_error("Neplatne rozmery matice!!!");
    }
    alokuj(r, s);
}

// destruktor
Matica::~Matica()
{
    dealokuj();
}

// kopirovaci konstruktor
Matica::Matica(const Matica& other)
{
    alokuj(other.riadky, other.stlpce);
    for (int i = 0; i < riadky; ++i)
    {
        for (int j = 0; j < stlpce; ++j)
        {
            data[i][j] = other.data[i][j];
        }
    }
}

// operator priradenia
Matica& Matica::operator=(const Matica& other)
{
    if (this != &other)
    {
        dealokuj();
        alokuj(other.riadky, other.stlpce);
        for (int i = 0; i < riadky; ++i)
        {
            for (int j = 0; j < stlpce; ++j)
            {
                data[i][j] = other.data[i][j];
            }
        }
    }
    return *this;
}

// operator [] 
Racionalne* Matica::operator[](int index)
{
    if (index < 0 || index >= riadky)
    {
        throw out_of_range("Index riadku mimo rozsah!!!");
    }
    return data[index];
}

//  pristup k datam na citanie
const Racionalne* Matica::operator[](int index) const
{
    if (index < 0 || index >= riadky)
    {
        throw out_of_range("Index riadku mimo rozsah!!!");
    }
    return data[index];
}

// --- gettery ---
int Matica::getRiadky() const 
    { 
        return riadky; 
    }
int Matica::getStlpce() const 
    { 
        return stlpce; 
    }
