//
//  main.cpp
//  Assignment-5
//
//  Created by Agustin Marinovic on 10/29/15.
//  Copyright © 2015 Agustin Marinovic. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;


int appendToAll(string a[], int n, string value)
{
    if (n < 0)
        return -1;
    if (n == 0)
        return 0;
    
    for (int i = 0; i < n; i++) //Add value to the end of each string
    {
        a[i] += value;
    }
    
    return n;
}

int lookup(const string a[], int n, string target)
{
    if (n < 0)
        return -1;
    
    for (int i = 0; i < n; i++)//Go through every element and check if it matches
    {
        if (a[i] == target)
            return i;
    }
    
    return -1;
}

int positionOfMax(const string a[], int n)
{
    string theLongest = "";
    int maxPos = -1;
    if (n < 0)
        return -1;
    
    for (int i = n-1; i >= 0; i--)
    {
        if (a[i] >= theLongest )//Compare each element with a theLongest, if the element is >=
        {
            maxPos = i;
            theLongest = a[i];//Replace theLongest with the new element
        }
    }
    return maxPos;
}

int rotateLeft(string a[], int n, int pos)
{
    if (n <= 0 || pos < 0 || pos >= n)
        return -1;
    
    string meanWhile = a[pos];//Store momentarily the intended item to move
    
    for (int i = pos; i < n; i++)//Starting from pos, replace each item with the following item
    {
        a[i] = a[i+1];
    }
    
    a[n-1] = meanWhile;//Append the taken item to the end of the array
    
    return pos;
}

int countRuns(const string a[], int n)
{
    int consecutive = 0;
    
    if (n < 0)
        return -1;
    
    
    for (int i = 1; i < n; i++)//If an element if different from the previous one, add 1 to the return variabek
    {
        if (i == 1)
            consecutive = 1;
        if (a[i] != a[i-1])
        {
            consecutive++;
        }
    }
    
    return consecutive;
}

int flip(string a[], int n)
{
    string meanWhile1;
    
    if (n < 0)
        return -1;
    
    for (int i = 0; i < n/2; i++)//Go n/2 times, if even then half will work, if odd, the decimal place will be truncated
    {
        if (n-1-i != i)
        {
            meanWhile1 = a[i];
            a[i] = a[n-1-i];
            a[n-1-i] = meanWhile1;
        }
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    
    if (n1 >= n2)
    {
        for (int i = 0; i < n1; i++)//If n1 is bigger, go up to n1 times to find the first different item
        {
            if (a1[i] != a2[i])
                return i;
        }
        return n2;
    }
    else
    {
        for (int i = 0; i < n2; i++)//If n2 is bigger, go n2 times to find the first different item
        {
            if (a1[i] != a2[i])
                return i;
        }
        return n1;
    }
    
}

int subsequence(const string a1[], int n1, const string a2[], int n2) // *** Check case empty array
{
    if (n1 < 0 || n2 < 0 || n2 > n1)
        return -1;
    else if (n2 == 0)
        return 0;
    
    int theNumber = 0;

    for (int i = 0; i < n1; i++)//Goes through the elements of the second array
    {
        if (a1[i] == a2[0])//If any element in a1 is equal to the first element in a2
        {
            for (int z = 0; z < n2; z++)//Starting in the element found, check if the following elements of each array are equal
            {
                if (a1[i+z] == a2[z])
                    theNumber++;
                else
                    return -1;
            }
            if (theNumber == n2)
                return i;
        }
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    
    for (int i = 0; i < n1; i++)//Go through a1 elements
    {
        for (int z = 0; z < n2; z++)//Go through a2 elements
        {
            if (a1[i] == a2[z])
                return i;
        }
    }
    
    
    return -1;
}

int split(string a[], int n, string splitter)
{
    if (n < 0)
        return -1;
    
    string waitForIt;
    
    for (int c = 0; c < n; c++) //Go thorough every element
    {
        for (int d = c + 1; d < n; d++) //Check if there is a following element that is smaller
        {
            if(a[c] > a[d]) //If there is such element, swap them
            {
                waitForIt = a[c];
                a[c] = a[d];
                a[d] = waitForIt;
            }
        }
    }
    
    for (int omicron(0); omicron < n; omicron++) //Look for the first element NOT < than splitter and return it
    {
        if (!(a[omicron] < splitter))
            return omicron;
    }
    return n;
}



int main()
{
    
    
    
}

    
