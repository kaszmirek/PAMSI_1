#include "algorithms.h"



//////MERGE SORT/////

template<typename T>
void merge(T *tab, T *tmp, int lewy, int srodek, int prawy)
{
    for (int i = lewy; i <= prawy; i++) tmp[i] = tab[i];

    int i = lewy;
    int j = srodek + 1;
    int q = lewy;

    while (i <= srodek && j <= prawy)
    {
        if (tmp[i] < tmp[j]) tab[q++] = tmp[i++];
        else tab[q++] = tmp[j++];
    }
    while (i <= srodek) tab[q++] = tmp[i++];
}


template<typename T>
void mergesort(T *tab, T *tmp, int lewy, int prawy)
{
    if (lewy < prawy)
    {
        int srodek = (lewy + prawy) / 2;
        mergesort(tab, tmp, lewy, srodek);
        mergesort(tab, tmp, srodek + 1, prawy);
        merge(tab, tmp, lewy, srodek, prawy);
    }
}


template<typename T>
void mergeWrap(T *tab, T *tmp, int lewy, int prawy, int maxdepth)
{
    mergesort(tab, tmp, lewy, prawy);
}



/////QUICK SORT/////

template<typename T>
int partition(T *tab, int lewy, int prawy)
{
    int pivot = tab[(lewy + prawy) / 2], i = lewy, j = prawy; //pivot selection is always middle

    while (true)
    {
        while (tab[j] > pivot) j--;

        while (tab[i] < pivot) i++;

        if (i < j)  std::swap(tab[i++], tab[j--]);
        else return j;
    }
}


template<typename T>
void quicksort(T *tab, int lewy, int prawy)
{
    if (lewy < prawy)
    {
        int q = partition(tab, lewy, prawy);
        quicksort(tab, lewy, q);
        quicksort(tab, q + 1, prawy);
    }
}


template<typename T>
void quickWrap(T *tab, T *tmp, int lewy, int prawy, int maxdepth)
{
    quicksort(tab, lewy, prawy);
}



//////INSERTION SORT//////

template<typename T>
void insertionsort(T *tab, int lewy, int prawy)
{
    for (int i = lewy + 1; i <= prawy; i++)
    {
        int key = tab[i];
        int j = i;

        while (j > lewy && tab[j - 1] > key)
        {
            tab[j] = tab[j - 1];
            j--;
        }
        tab[j] = key;
    }
}


/// HEAP SORT ////
template<typename T>
void heapsort(T *lewy, T *prawy)
{
    std::make_heap(lewy, prawy);
    std::sort_heap(lewy, prawy);
}



//// INTRO SORT /////

template<typename T>
void introsort(T *tab, T *lewy, T *prawy, int maxdepth)
{
    if ((prawy - lewy) < 16) insertionsort(tab, lewy - tab, prawy - tab);
    else if (maxdepth == 0) heapsort(lewy, prawy + 1);
    else
    {
        int pivot = partition(tab, lewy - tab, prawy - tab);
        introsort(tab, lewy, tab + pivot, maxdepth - 1);
        introsort(tab, tab + pivot + 1, prawy, maxdepth - 1);
    }
}


template<typename T>
void introWrap(T *tab, T *tmp, int lewy, int prawy, int maxdepth)
{
    introsort(tab, tab, tab + prawy , maxdepth);
}


template void introWrap<int>(int*, int*, int, int, int);
template void mergeWrap<int>(int*, int*, int, int, int);
template void quickWrap<int>(int*, int*, int, int, int);

template void introWrap<double>(double*, double*, int, int, int);
template void mergeWrap<double>(double*, double*, int, int, int);
template void quickWrap<double>(double*, double*, int, int, int);
