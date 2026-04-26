#pragma once

#include <iostream>
#include <stdexcept>
#include "Matica.h"
#include "Racionalne.h"

using namespace std;

class SusLinRovnic
{
private:
    Matica rozsirenieMatice;   
    Racionalne* vysledky;      
    int n;                  

public:
    // konverzny konstruktor
    SusLinRovnic(const Matica& m);

    // destruktor
    ~SusLinRovnic();

    // kopirovaci konstruktor
    SusLinRovnic(const SusLinRovnic& other);

    // operator priradenia
    SusLinRovnic& operator=(const SusLinRovnic& other);

    // vypocet korenov (Gaussova eliminacia)
    void vyries();

    // operator [] pre pristup ku korenom
    Racionalne operator[](int index) const;

    // operator vypisu na konzolu
    friend ostream& operator<<(ostream& os, const SusLinRovnic& ls);
};
