//
//  main.cpp
//  royalty
//
//  Created by Agustin Marinovic on 10/7/15.
//  Copyright © 2015 Agustin Marinovic. All rights reserved.
//

#include <iostream>
using namespace std;

int unitsSent;
string title, premium;
double basePrice, royalties;


int main()
{
    
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "Units sent: ";     //Inputs number of units sent
    cin >> unitsSent;
    cin.ignore(10000, '\n');
    
    if (unitsSent < 0)      //If unitsSent is negative, cout error and stop program
    {
        cout << "---\nThe number of units sent must be nonnegative." << endl;
        return 1;
    }
    
    cout << "Title: ";      //Inputs title, gets string including spaces, not just word
    getline(cin, title);
    
    if (title == "")        //If the title is empty, cout error and stop program
    {
        cout << "---\nYou must enter a title." << endl;
        return 2;
    }
    
    cout << "Base price: ";     //Inputs price
    cin >> basePrice;
    
    if (basePrice < 0)      //If price is negative, cout error and stop program
    {
        cout << "---\nThe base price must be nonnegative." << endl;
        return 3;
    }
    
    cout << "Premium item? (y/n): ";        //Inputs Premum, as y or n
    cin >> premium;
    
    if (premium == "y" || premium == "n")       //If premium is y or n, nothing happens. If it's anything else then cout error
    {}
    else
    {
        cout << "---\nYou must enter y or n." << endl;
        return 4;
    }
    
    
    if (unitsSent >= 0 && unitsSent <= 400)     //Case S <= 400 sold
    {
        royalties = unitsSent * basePrice * 0.09;
    }
    else if (unitsSent > 400 && unitsSent <= 1200)      //Case 400 < S <= 1200
    {
        if (premium == "y")     //Checks for premium item to apply correct percentage
            royalties = basePrice * 400 * 0.09 + basePrice * (unitsSent - 400) * 0.16;
        else if (premium == "n")
            royalties = basePrice * 400 * 0.09 + basePrice * (unitsSent - 400) * 0.13;
    }
    else if (unitsSent > 1200)      //Case S > 1200
    {
        if (premium == "y")     //Checks premum to apply correct percentage
            royalties = basePrice * (400 * 0.09 + 800 * 0.16) + basePrice * (unitsSent - 1200) * 0.14;
        else if (premium == "n")
            royalties = basePrice * (400 * 0.09 + 800 * 0.13) + basePrice * (unitsSent - 1200) * 0.14;
    }
    
    cout << "---\n" << title << " earned $" << royalties << " in royalties." << endl; //Outputs answer if everything was imput correctly
    
}
