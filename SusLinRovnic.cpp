#include "SusLinRovnic.h"

// konverzny konstruktor
SusLinRovnic::SusLinRovnic(const Matica& m) : rozsirenieMatice(m)
{
    n = m.getRiadky();
    if (m.getStlpce() != n + 1)
    {
        throw runtime_error("Matica nema spravny rozmer pre sustavu (n x n+1)!!!");
    }
    vysledky = new Racionalne[n];
}

// destruktor 
SusLinRovnic::~SusLinRovnic()
{
    delete[] vysledky;
}

// kopirovaci konstruktor
SusLinRovnic::SusLinRovnic(const SusLinRovnic& other) : rozsirenieMatice(other.rozsirenieMatice), n(other.n)
{
    vysledky = new Racionalne[n];
    for (int i = 0; i < n; i++)
    {
        vysledky[i] = other.vysledky[i];
    }
}

// operator priradenia
SusLinRovnic& SusLinRovnic::operator=(const SusLinRovnic& other)
{
    if (this != &other)
    {
        delete[] vysledky;
        rozsirenieMatice = other.rozsirenieMatice;
        n = other.n;
        vysledky = new Racionalne[n];
        for (int i = 0; i < n; i++)
        {
            vysledky[i] = other.vysledky[i];
        }
    }
    return *this;
}

// vypocet korenov (Gaussova eliminacia) 
void SusLinRovnic::vyries()
{
    for (int i = 0; i < n; i++)
    {
        // hladanie nenuloveho pivotu
        int pivot = i;
        while (pivot < n && rozsirenieMatice[pivot][i] == Racionalne(0))
        {
            pivot++;
        }
        if (pivot == n)
        {
            throw runtime_error("Sustava nema prave jedno riesenie (singularna matica)!!!");
        }

        // vymena riadkov ak treba
        if (pivot != i)
        {
            for (int j = 0; j <= n; j++)
            {
                swap(rozsirenieMatice[i][j], rozsirenieMatice[pivot][j]);
            }
        }

        // eliminacia pod pivotom
        for (int k = i + 1; k < n; k++)
        {
            Racionalne faktor = rozsirenieMatice[k][i] / rozsirenieMatice[i][i];
            for (int j = i; j <= n; j++)
            {
                rozsirenieMatice[k][j] = rozsirenieMatice[k][j] - (faktor * rozsirenieMatice[i][j]);
            }
        }
    }

    // spatna substitucia
    for (int i = n - 1; i >= 0; i--)
    {
        Racionalne sum(0);
        for (int j = i + 1; j < n; j++)
        {
            sum = sum + (rozsirenieMatice[i][j] * vysledky[j]);
        }
        vysledky[i] = (rozsirenieMatice[i][n] - sum) / rozsirenieMatice[i][i];
    }
}

// operator [] 
Racionalne SusLinRovnic::operator[](int index) const
{
    if (index < 0 || index >= n)
    {
        throw out_of_range("Index korena mimo rozsah!!!");
    }
    return vysledky[index];
}

// operator tlace na konzolu
ostream& operator<<(ostream& os, const SusLinRovnic& ls)
{
    os << "Sustava rovnic (rozsirena matica):" << endl;

    char labels[] = { 'x', 'y', 'z' };

    for (int i = 0; i < ls.n; i++)
    {
        for (int j = 0; j < ls.n; j++)
        {
            Racionalne val = ls.rozsirenieMatice[i][j];

            if (j == 0)
            {
                if (val.getNum() < 0)
                {
                    os << "-";
                }
            }
            else
            {
                if (val.getNum() >= 0)
                {
                    os << " + ";
                }
                else
                {
                    os << " - ";
                }
            }

            int hore = abs(val.getNum());
            Racionalne absolutna(hore, val.getDen());

            os << absolutna;

            if (j < 3)
            {
                os << labels[j];
            }
            else
            {
                os << "x" << (j - 1);   
            }
        }
        os << " = " << ls.rozsirenieMatice[i][ls.n] << endl;
    }
    return os;
}
