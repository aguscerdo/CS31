//
//  main.cpp
//  Assignment 3 - try 2
//
//  Created by Agustin Marinovic on 10/26/15.
//  Copyright © 2015 Agustin Marinovic. All rights reserved.
//

#include "grid.h"
#include <iostream>
#include <cmath>
#include <string>
#include <cassert>
#include <cctype>
using namespace std;

int numberOfSteps(char alpha, char num1, char num2); //Checks numbers intended after a letter (1 or 2 digits or return 1 if letter)
bool isRouteWellFormed(string route); //Checks if the route is viable
int navigateSegment(int r, int c, char dir, int maxSteps); //Checks the maximum steps that can be given in a single direction
int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps);
void moveAnalyzer(string stringCode); //Analyzes the string to set direction and steps aka vector
bool notInBound(int ar, int ac);

char letters[10000]; //Store Direction
int moveLength[10000]; //Store number
int counter(0);

int main ()
{
    int nSteps;
    int StartR(2), StartC(2), EndR(10), EndC(10);
    setSize(10, 10);
    setWall(2,4);
    setWall(2,6);
    setWall(4,4);
    setWall(4,6);
    setWall(6,4);
    setWall(6,6);
    setWall(7,7);
    setWall(8,8);
    setWall(9,9);
    
    draw(StartR, StartC, EndR, EndC);
    
    // Test isRouteWellFormed
    assert(isRouteWellFormed("4w3nesw4")==false);//Starts with digit
    assert(isRouteWellFormed("W123ens")==false);//3 digit number
    assert(isRouteWellFormed("HolaQueAse9")==false);//Non-legal characters
    assert(isRouteWellFormed("EsWnWn"));//Receive upper and lower case letters
    assert(isRouteWellFormed("NS2e03w1s11"));//Mix of 0, 1 and 2 digit numbers
    assert(isRouteWellFormed(""));//Empty string
    
    //Test navigateSegment
    assert(navigateSegment(2, 2, 'N', -2)==-1);//Negative maxSteps
    assert(navigateSegment(2, 4, 's', 3)==-1);//Start over a wall
    assert(navigateSegment(15, -2, 'W', 12)==-1);//Start outside the wall
    assert(navigateSegment(2, 2, 'k', 2)==-1);//Non-legal character
    assert(navigateSegment(2, 2, 'E', 4)==1);//Encounter a wall
    assert(navigateSegment(2, 2, 'n', 5)==1);//Encounter the boundary
    assert(navigateSegment(2, 2, 's', 4)==4);//No obstacles encounter and succesfully advanced
    assert(navigateSegment(2, 2, 'S', 1)==1);//Move south without encountering obstacles
    assert(navigateSegment(2, 2, 'N', 1)==1);//Move north without encountering obstacles
    assert(navigateSegment(2, 2, 'w', 1)==1);//Move west without encountering obstacles
    assert(navigateSegment(2, 2, 'e', 1)==1);//Move east without encountering obstacles
    assert(navigateSegment(2, 2, 'w', 1)==1);//Receive a lower case letter
    assert(navigateSegment(2, 2, 'N', 1)==1);//Receive upper case letter
    assert(navigateSegment(2, 3, 'E', 2)==0);//Starting next to a wall and moving in that direction
    assert(navigateSegment(1, 1, 'w', 3)==0);//Start next to an edge and move in that direction
    
    //Test navigateRoute
    assert(navigateRoute(2, 2, 10, 10, "123NotOkMate123", nSteps)==2);//Invalid String
    assert(navigateRoute(2, -2, 10, 10, "S1E2n3", nSteps)==2);//Start outside the grid
    assert(navigateRoute(2, 2, -2, 40, "S1", nSteps)==2);//Endpoint outside the grid
    assert(navigateRoute(2, 4, 10, 10, "n", nSteps)==2);//Start over a wall
    assert(navigateRoute(2, 2, 2, 4, "s2", nSteps)==2);//Endpoint over a wall
    assert(navigateRoute(2, 2, 10, 10, "E9s3N4W1", nSteps)==3 && nSteps==1);//Encounter a wall
    assert(navigateRoute(2, 2, 10, 10, "S10w23", nSteps)==3 && nSteps==8);//Encounter an edge
    assert(navigateRoute(2, 2, 10, 10, "S8E8", nSteps)==0 && nSteps==16);//Succesfully reach the endpoint
    assert(navigateRoute(2, 2, 10, 10, "se3s2w2n2", nSteps)==1 && nSteps==10);//Succesfully move, without reaching endpoint
    assert(navigateRoute(2, 2, 2, 2, "", nSteps)==0 && nSteps==0);//Inputing an empty string
}

void moveAnalyzer(string stringCode) //Stores in 2 arrays the direction and the magnitude of movement
{
    counter = 0;
    
    for (int chi = 0; chi < stringCode.size(); chi++)
    {
        letters[counter] = toupper(stringCode[chi]); //Store direction in the array
        
        if(isalpha(stringCode[chi]) && chi + 2 < stringCode.size()) //Make sure there are at least 2 more characters ahead to not be undefined
        {
            moveLength[counter] = numberOfSteps(stringCode[chi], stringCode[chi+1], stringCode[chi+2]);
            counter++;
        }
        else if (isalpha(stringCode[chi]) && chi + 1 < stringCode.size()) //Make sure there is at least 1 more character ahead to not be undefined

        {
            moveLength[counter] = numberOfSteps(stringCode[chi], stringCode[chi+1], 'a');
            counter++;
        }
        else if(isalpha(stringCode[chi]))
        {
            moveLength[counter] = numberOfSteps(stringCode[chi], 'a', 'a');
            counter++;
        }

    }
}

bool notInBound(int ar, int ac) //Checks if the position is not in the grid
{
    return ar <= 0 || ac <= 0 || ar > getRows() || ac > getCols();
}


int numberOfSteps(char alpha, char num1, char num2) //Checks the number of steps after a letter
{
    int magnitude = 0;
    
    if(isalpha(alpha))
    {
        if (isdigit(num1) && isdigit(num2)) //2 digit number
        {
            magnitude = (num1 - '0') * 10 + (num2 - '0');
        }
        else if (isdigit(num1) && isdigit(num2) == false) //1 digit number
        {
            magnitude = (num1 - '0');
        }
        else //No digits, just 1
        {
            magnitude = 1;
        }
    }
    return magnitude;
}

bool isRouteWellFormed(string route) //Checks if the string is acceptable, any error will return false
{
    bool theTruth = true;
    if (route != "")
    {
        for (int a(0); theTruth == true && a < route.size(); a++) //Loop through every letter of the string
        {
            if(isdigit(route[a])) //Check if its number
            {
                if(a > 1 && isdigit(route[a-1]) && isdigit(route[a-2])) //A 3 digit number is no no
                {
                    theTruth = false;
                }
                
                if(isdigit(route[0])) //The first char can't be a number
                {
                    theTruth = false;
                }
            } //End IF digit
            
            else if(isalpha(route[a])) //Check if char is a letter *** upper or lower
            {
                
                switch (toupper(route[a]))
                {
                    case 'N':
                        break;
                    case 'S':
                        break;
                    case 'W':
                        break;
                    case 'E':
                        break;
                    default:
                        theTruth = false;
                }
                
            } //End IF alpha
            
            else if(isdigit(route[a]) == false && isalpha(route[a]) == false) //Not a digit or alpha
            {
                theTruth = false;
            }
            
        } //End for loop
    }
    return theTruth;
}

int navigateSegment(int r, int c, char dir, int maxSteps)
{
    int maxPossible = maxSteps;
    

    if(notInBound(r, c))//Start position out of bounds
    {
        return -1;
    }
    else if(isWall(r,c) || maxSteps < 0)//If over a wall, or maxSteps is negative
    {
        return -1;
    }
    
    if(dir == 'N' || dir == 'n')
    {
        for (int pasos = 0; pasos < maxSteps; pasos++)
        {
            r--; //Advance North
            maxPossible = pasos + 1;
            if (notInBound(r,c))//Check if valid position
            {
                return pasos;
            }
            else if(isWall(r,c))
            {
                return pasos;
            }
        }
        
    }
    else if(dir == 'S' || dir == 's')
    {
        for (int pasos = 0; pasos < maxSteps; pasos++)
        {
            r++; //Advance South
            maxPossible = pasos + 1;
            if (notInBound(r,c))//Check if valid position
            {
                return pasos;
            }
            else if(isWall(r,c))
            {
                return pasos;
            }
        }
    }
    else if(dir == 'W' || dir == 'w')
    {
        for (int pasos = 0; pasos < maxSteps; pasos++)
        {
            
            c--; //Advance West
            maxPossible = pasos + 1;
            if (notInBound(r,c))//Check if valid position
            {
                return pasos;
            }
            else if(isWall(r,c))
            {
                return pasos;
            }
        }
    }
    else if(dir == 'E' || dir == 'e')
    {
        for (int pasos = 0; pasos < maxSteps; pasos++)
        {
            
            c++; //Advance East
            maxPossible = pasos + 1;
            if (notInBound(r,c))//Check if valid position
            {
                return pasos;
            }
            else if(isWall(r,c))//Check if valid position
            {
                return pasos;
            }
        }
    }
    else
    {
        return -1;
    }
    return maxPossible;
}



int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps)
{
    int accumulated(0), actualR(sr), actualC(sc), instantMax(0);
    
    if (isRouteWellFormed(route) == false) //Check if valid route; Else RETURN 2
    {
        return 2;
    }
    else if (notInBound(sr, sc) || notInBound(er, ec)) //Start or ending point outside the grid
    {
        return 2;
    }
    else if (isWall(sr, sc) || isWall(er, ec)) //Starts or ends over a wall
    {
        return 2;
    }
    
    moveAnalyzer(route); //Analyze string and store direction and number of steps
    
    for (int xi = 0; xi < counter; xi++)
    {
        instantMax = navigateSegment(actualR, actualC, letters[xi], moveLength[xi]);
        accumulated += instantMax;
        
        if (instantMax != moveLength[xi]) //Checks if the steps moved aren't the max, aka hit a wall; RETURN 3
        {
            nsteps = accumulated;
            return 3;
        }
        
        if(letters[xi] == 'N')
        {
            actualR -= instantMax;
        }
        else if(letters[xi] == 'S')
        {
            actualR += instantMax;
        }
        else if (letters[xi] == 'W')
        {
            actualC -= instantMax;
        }
        else if(letters[xi] == 'E')
        {
            actualC += instantMax;
        }
    }
    
    
    nsteps = accumulated;
    if (actualC == ec && actualR == er) //Checks if it ends in the supposed ending point
    {
        return 0; //@ EP
    }
    else
    {
        return 1; //Not @ EP
    }
}








