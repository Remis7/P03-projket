
#include <iostream>
#include <stdexcept>
#include <numeric>
#include <cmath>

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
            throw runtime_error("CHYBA: Menovatel nemoze byt nula!!!");
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
    friend Racionalne operator+(const Racionalne& lhs, const Racionalne& rhs);

    // operator minus
    friend Racionalne operator-(const Racionalne& lhs, const Racionalne& rhs);

    // operator krat
    friend Racionalne operator*(const Racionalne& lhs, const Racionalne& rhs);

    // operator deleno
    friend Racionalne operator/(const Racionalne& lhs, const Racionalne& rhs);

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

// operator plus
Racionalne operator+(const Racionalne& lhs, const Racionalne& rhs)
{
    return Racionalne(lhs.citatel * rhs.menovatel + rhs.citatel * lhs.menovatel, lhs.menovatel * rhs.menovatel);;
}

// operator minus
Racionalne operator-(const Racionalne& lhs, const Racionalne& rhs)
{
    return Racionalne(lhs.citatel * rhs.menovatel - rhs.citatel * lhs.menovatel, lhs.menovatel * rhs.menovatel);
}

// operator krat
Racionalne operator*(const Racionalne& lhs, const Racionalne& rhs)
{
    return Racionalne(lhs.citatel * rhs.citatel, lhs.menovatel * rhs.menovatel);
}

// operator deleno
Racionalne operator/(const Racionalne& lhs, const Racionalne& rhs)
{
    if (rhs.citatel == 0)
    {
        throw runtime_error("CHYBA: delenie nulou!!!");
    }
    return Racionalne(lhs.citatel * rhs.menovatel, lhs.menovatel * rhs.citatel);
}



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
        if (index < 0 || index >= riadky) throw out_of_range("Index riadku mimo rozsah!!!");
        return data[index];
    }

    // pristup k datam na citanie
    const Racionalne* operator[](int index) const
    {
        if (index < 0 || index >= riadky) throw out_of_range("Index riadku mimo rozsah!!!");
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

class SusLinRovnic
{
private:
    Matica rozsirenieMatice;
    Racionalne* vysledky;
    int n;

public:
    // konverzny konstruktor
    SusLinRovnic(const Matica& m) : rozsirenieMatice(m)
    {
        n = m.getRiadky();
        if (m.getStlpce() != n + 1)
        {
            throw runtime_error("Matica nema spravny rozmer pre sustavu (n x n+1)!!!");
        }
        vysledky = new Racionalne[n];
    }

    // destruktor
    ~SusLinRovnic()
    {
        delete[] vysledky;
    }

    // kopirovaci konstruktor
    SusLinRovnic(const SusLinRovnic& other) : rozsirenieMatice(other.rozsirenieMatice), n(other.n)
    {
        vysledky = new Racionalne[n];
        for (int i = 0; i < n; i++)
        {
            vysledky[i] = other.vysledky[i];
        }
    }

    // operator rovna sa
    SusLinRovnic& operator=(const SusLinRovnic& other)
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

    // vypocet korenou (Gaussova eliminacia)
    void vyries()
    {
        for (int i = 0; i < n; i++)
        {
            // hladanie nenuloveho prvku
            int pivot = i;
            while (pivot < n && rozsirenieMatice[pivot][i] == Racionalne(0))
            {
                pivot++;
            }
            if (pivot == n)
            {
                throw runtime_error("Sustava nema prave jedno riesenie (singularna matica)!!!");
            }
            // vymena riadkou ak treba
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

    // operator [] pre pristup ku korenom
    Racionalne operator[](int index) const
    {
        if (index < 0 || index >= n)
        {
            throw out_of_range("Index korena mimo rozsah!!!");
        }
        return vysledky[index];
    }

    // operator tlace na konzolu
    friend ostream& operator<<(ostream& os, const SusLinRovnic& ls)
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
                

                long long hore = abs(val.getNum());
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
};



int main()
{
    try
    {
        cout << "--- Test sustavy linearnych rovnic ---" << endl;
        
        Matica m(3, 4);

        m[0][0] = Racionalne(2, 5);
        m[0][1] = Racionalne(1 , 4);
        m[0][2] = Racionalne(-1, 5);
        m[0][3] = Racionalne(8, 4);

        m[1][0] = Racionalne(-3, 4);
        m[1][1] = Racionalne(-1, 3);
        m[1][2] = Racionalne(2, 5);
        m[1][3] = Racionalne(-6, 2);

        m[2][0] = Racionalne(-2, 6);
        m[2][1] = Racionalne(1, 5);
        m[2][2] = Racionalne(2, 4);
        m[2][3] = Racionalne(-3, 5);

        SusLinRovnic system(m);
        
        cout << system << endl;

        cout << "Riesim sustavu..." << endl;
        system.vyries();

        char labels[] = { 'x', 'y', 'z' };
        cout << "Vysledky (korene):" << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << labels[i] << " = " << system[i] << endl;
        }
    }

    catch (const runtime_error& e)
    {
        cerr << "CHYBA (Runtime): " << e.what() << endl;
    }
    catch (const out_of_range& e)
    {
        cerr << "CHYBA (Index): " << e.what() << endl;
    }
    catch (...)
    {
        cerr << "Neznama chyba." << endl;
    }

    return 0;
}

