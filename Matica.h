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

    // alokacia
    void alokuj(int r, int s);
    // dealokacia
    void dealokuj();

public:
    // konstruktor
    Matica(int r, int s);

    // destruktor
    ~Matica();

    // kopirovaci konstruktor
    Matica(const Matica& other);

    // operator priradenia
    Matica& operator=(const Matica& other);

    // operator [] na indexovanie riadkov
    Racionalne* operator[](int index);
    const Racionalne* operator[](int index) const;

    // gettery
    int getRiadky() const;
    int getStlpce() const;
};