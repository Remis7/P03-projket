#pragma once
#include <iostream>
#include <stdexcept>
#include <numeric>
#include <cmath>
#include "Racionalne.h"
#include "SusLinRovnic.h"
#include "Matica.h"

using namespace std;

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

        const char labels[] = "xyz";
        cout << "Vysledky (korene):" << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << labels[i] << " = " << system[i] << endl;
        }
    }

    catch (const runtime_error& e)
    {
        cerr << "CHYBA: " << e.what() << endl;
    }
    catch (const out_of_range& e)
    {
        cerr << "CHYBA: Index riadku mimo rozsah!" << e.what() << endl;
    }
    return 0;
}

