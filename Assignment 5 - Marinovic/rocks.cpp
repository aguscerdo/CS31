//
//  rocks.cpp
//  Assignment-5
//
//  Created by Agustin Marinovic on 11/9/15.
//  Copyright © 2015 Agustin Marinovic. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include "utilities.h"

using namespace std;

const int MAXWORDS = 9500;

int manageOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum);
int rocks(const char rWord[MAXWORDLEN+1], const char pWord[MAXWORDLEN+1]);
int pebbles(const char rWord[MAXWORDLEN+1], const char pWord[MAXWORDLEN+1]);
bool goodWord(const char words[][MAXWORDLEN+1], const char pWord[], int nWords);


int main()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    char theWords[MAXWORDS][MAXWORDLEN+1]; //Create array to hold words
    int nOfWords = loadWords(theWords, MAXWORDS);
    
    if (nOfWords < 1) //Not enough words loaded
    {
        cout << "No words were loaded, so I can't play the game." << endl;
        return -1;
    }
    
    int nRounds;
    cout << "How many rounds do you want to play? "; //Number of Rounds to play
    cin >> nRounds;
    cin.ignore(256,'\n');
    
    if (nRounds < 1) //Non positive number of rounds
    {
        cout << "The number of rounds must be positive." << endl;
        return -1;
    }
    
    int maxAttempts(0), minAttempts(nOfWords), cumulativeAttempts(0);
    double averageAttempts;
    
    for (int phi(0); phi < nRounds; phi++) //Start rounds
    {
        cout << "\nRound " << phi << endl;
        int random = randInt(0, nOfWords - 1);
        long wordLength = strlen(theWords[random]);
        cout << "The secret word is " << wordLength << " letters long." << endl;
        
        cerr << theWords[random] << endl;
        
        int nTries = manageOneRound(theWords, nOfWords, random); //Game on
        
        if (nTries == 1) //Display attempts
            cout << "You got it in 1 try." << endl;
        else
            cout << "You got it in " << nTries << " tries." << endl;
        
        if (nTries > maxAttempts) //Min, Max and Average
            maxAttempts = nTries;
        if (nTries < minAttempts)
            minAttempts = nTries;
        cumulativeAttempts += nTries;
        averageAttempts = static_cast<double> (cumulativeAttempts)/static_cast<double>(phi+1);
        
        cout << "Average: " << averageAttempts << ", minimum: " << minAttempts << ", maximum: " << maxAttempts << endl;
        
    }// END FOR
    
}




int manageOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum)
{
    if(nWords < 0 || wordnum < 0 || wordnum >= nWords) //Non valid integers
        return -1;
    
    
    char pWord[MAXWORDLEN+1];
    int nRocks, nPebbles;
    int attempts = 1;
    bool theTruth;
    
    
    while (true)
    {
        theTruth = false;
        while (!(theTruth))
        {
            cout << "Probe word: "; //Ask for a word
            cin >> pWord;
            cin.ignore(100, '\n');
            theTruth = goodWord(words, pWord, nWords); //Check if it's a good word
        }
        
        nRocks = rocks(words[wordnum], pWord); //Check for rocks then pebbles
        nPebbles = pebbles(words[wordnum], pWord);
        
        if (nRocks == strlen(pWord))//Correct Word, rocks == strlen
            break;
        
        cout << "Rocks: " << nRocks << ", Pebbles: " << nPebbles << endl;
        attempts++;
    }
    
    
    return attempts;
}

int rocks(const char rWord[MAXWORDLEN+1], const char pWord[MAXWORDLEN+1])
{
    int nRocks = 0;
    
    if (strlen(rWord) < strlen(pWord)) //From 0 to whichever str is the shortest
    {
        for (int x = 0; x < strlen(rWord); x++)
        {
            if (rWord[x] == pWord[x]) //Both letters in the same position are equal, add 1 to rocks
                nRocks++;
        }
    }
    else
    {
        for (int x = 0; x < strlen(pWord); x++)
        {
            if (rWord[x] == pWord[x])
                nRocks++;
        }
    }
    return nRocks;
}


int pebbles(const char rWord[MAXWORDLEN+1], const char pWord[MAXWORDLEN+1])
{
    bool nonValidR[MAXWORDLEN+1]; //Arrays to store if a letter has been taken (false) or otherwise a good letter (true)
    bool nonValidP[MAXWORDLEN+1];
    int nPebbles = 0;
    
    for (int xi = 0; xi < MAXWORDLEN+1; xi++) //Mark all letters as good (for now)
    {
        nonValidR[xi] = true;
        nonValidP[xi] = true;
    }
    
    if (strlen(rWord) < strlen(pWord)) //Mark all Rocks as taken letters, marked from the random word and player word
    {
        for (int x = 0; x < strlen(rWord); x++)
        {
            if (rWord[x] == pWord[x])
            {
                nonValidR[x] = false;
                nonValidP[x] = false;
            }
        }
    }
    else
    {
        for (int x = 0; x < strlen(pWord); x++)
        {
            if (rWord[x] == pWord[x])
            {
                nonValidR[x] = false;
                nonValidP[x] = false;
            }
        }
    }
    
    
    for (int a(0); a < strlen(rWord); a++) //Every letter of the random word
    {
        for (int b(0); b < strlen(pWord); b++) //Every letter of the inputed word
        {
            if(nonValidR[a] && nonValidP[b] && rWord[a] == pWord[b]) //Check if: Letter hasn't been taken (rock or another pebble) and if letters match
            {
                nPebbles++;
                nonValidR[a] = false; //If pebble, mark letter as taken in players word and add 1 to nPebbles
                nonValidP[b] = false;
                break;
            }
        }
    }
    
    return nPebbles;
}

bool goodWord(const char words[][MAXWORDLEN+1], const char pWord[], int nWords)
{
    if (strlen(pWord) > MAXWORDLEN || strlen(pWord) < MINWORDLEN) //Wrong number of letters
    {
        cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
        return false;
    }
    
    for (int a(0); a < strlen(pWord); a++)
    {
        if( !(islower(pWord[a]))) //If a character is not acceptable, require a new word
        {
            cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
            return false;
        }
    }
    
    bool outcome = false;
    
    for (int a(0); a < nWords; a++) //Check if the word is in the array
    {
        if (strcmp(words[a], pWord) == 0)
        {
            outcome = true;
            break;
        }
    }
    
    if (outcome == false) //Word not on the array
    {
        cout << "I don't know that word." << endl;
        return false;
    }
    return true;
}