#include <iostream>
#include "algorithms.h"
#include <chrono>
#include <fstream>
#include <bits/stdc++.h>

#define NTABLIC 100 // ilosc tablic do posortowania // do testow
#define RodzajZmiennej int


template<typename T>
using SortujWsk = void (*)(T*, T*, int, int, int);


//funkcje do sortowania
template<typename T>
void sortujprocent(int *tab, int n, double procent) //sortuje zadany procent tablicy
{
    if(procent==100)
    {
        std::sort(tab, tab + n, std::greater<int>());
        return;
    }
    std::sort(tab, tab + (int)((n*procent) / 100));
}

template<typename T>
double sortuj(SortujWsk<RodzajZmiennej> fw, int n, T *tab, T *tmp)
{
    //pomiar czasu//
    auto t_start = std::chrono::high_resolution_clock::now(); //start clock
    fw(tab, tmp, 0, n-1, log(n) * 2);
    auto t_end = std::chrono::high_resolution_clock::now(); //stop clock

    return std::chrono::duration<double, std::milli>(t_end - t_start).count(); //return the time difference
}

template<typename T>
void sprawdzczyposortowane(T *tab, int n)
{
    for (int i = 0; i < n - 1 ; i++)
    {
        if(tab[i] > tab[i + 1])
        {
            std::cout << "Tablica nie jest posortowana!\nZamykanie...";
            std::cin.get();
            exit(1);
        }
    }
}

//funkcja do pliku//
void sprawdzplik (std::ofstream &file)
{
    if (!file.is_open())
    {
        std::cout << "Nie udalo sie otworzyc pliku!\nZamykanie...";
        std::cin.get();
        exit(1);
    }
}

//funkcje tablic//
template<typename T>
T *nowatablica(int n)
{
    return new T[n];
}

template<typename T>
void usuntablice(T *tab)
{
    delete [] tab;
}

template<typename T>
void wypelnij(T *tab, int n)
{
    for (int i = 0; i < n; i++)
    {
        tab[i] = rand() % 100000+1;
    }
}



int main()
{
    std::ofstream file("wyniki.txt");
    sprawdzplik(file);

    srand(time(NULL));

    int ntablic = NTABLIC; //liczba powtorzen sortowania
    int ntab[5]= {10000, 50000, 100000, 500000, 1000000};
    double procenttab[8]= {0, 25, 50, 75, 95, 99, 99.7, 100};  //100% - posortowane w odwrotnej kolejnosci

    SortujWsk<RodzajZmiennej> merge_wsk= &mergeWrap, quick_wsk= &quickWrap, intro_wsk= &introWrap; //wskazniki na algorytmy sortujace
    SortujWsk<RodzajZmiennej> wsktab[3]= {merge_wsk, quick_wsk, intro_wsk}; //tablica wskaznikow

    double licznik=0;
    int iter = 0;
    std::string alg[3] = {"QUCIK_SORT", "MERGE_SORT", "INTRO_SORT"};


    for (SortujWsk<RodzajZmiennej> fw : wsktab) //dla kazdego algorytmu sortujacego
    {
        std::cout << alg[iter++] << std::endl;
        for (double procent : procenttab) //dla kazdego procentu sortowania
        {
            for (int n : ntab) //dla kazdego rozmiaru tablicy
            {
                RodzajZmiennej *tab = nowatablica<RodzajZmiennej>(n);
                RodzajZmiennej *temp = nowatablica<RodzajZmiennej>(n);

                for (int i = 0; i < ntablic ; i++) //dla kazdej tablicy
                {
                    wypelnij<RodzajZmiennej>(tab, n);
                    sortujprocent<RodzajZmiennej>(tab, n, procent);
                    licznik += sortuj<RodzajZmiennej>(fw, n, tab, temp);
                    sprawdzczyposortowane<RodzajZmiennej>(tab, n);
                }
                usuntablice<RodzajZmiennej>(tab);
                usuntablice<RodzajZmiennej>(temp);

                std::cout << n << " posortowano!" << std::endl;

                file << licznik / ntablic << " "; //liczy sredni czas sortowania pojedynczej tablicy
                licznik = 0;
            }
            std::cout << procent << " % gotowe!" << std::endl;

        }
        file << "\n";
    }
    std::cout << "Koniec";
    std::cin.get();
    file.close();

    return 0;
}

