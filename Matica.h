#pragma once
#include <iostream>
#include <stdexcept>
#include "Racionalne.h"

using namespace std;


class Matica
{
private:
    int riadky;
    int stlpce;
    Racionalne** data;
    // alokacia pamate
    void alokuj(int r, int s)
    {
        riadky = r;
        stlpce = s;
        data = new Racionalne * [riadky];
        for (int i = 0; i < riadky; ++i)
        {
            data[i] = new Racionalne[stlpce];
        }
    }
    // dealokacia pamate
    void dealokuj()
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
public:
    // konstruktor
    Matica(int r, int s)
    {
        if (r <= 0 || s <= 0) throw runtime_error("Neplatne rozmery matice!!!");
        alokuj(r, s);
    }
    // destruktor
    ~Matica()
    {
        dealokuj();
    }
    // kopirovaci konstruktor
    Matica(const Matica& other)
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
    Matica& operator=(const Matica& other)
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
    // operator [] na indexovanie
    Racionalne* operator[](int index)
    {
        if (index < 0 || index >= riadky) throw out_of_range("!");
        return data[index];
    }
    // pristup k datam na citanie
    const Racionalne* operator[](int index) const
    {
        if (index < 0 || index >= riadky) throw out_of_range("!");
        return data[index];
    }
    // gettery
    int getRiadky() const
    {
        return riadky;
    }
    int getStlpce() const
    {
        return stlpce;
    }

};
