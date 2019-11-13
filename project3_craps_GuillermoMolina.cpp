//Guillermo Molina
//October 3, 2019
//Project 3: Craps Game
/*
 I have to develope an interactive program that will resemble the game Craps.
 The rules are that a player must roll two dice (each with 6 faces numbered 1-6 with no
 repeating numbers). If the sum of both dice is equal to 7 or 11 on the first throw then
 the player will automatically win. If the sum is 2,3, or 12 on the first throw then the
 player loses. If the sum is 4,5,6,8,9, or 1o on the first throw then the sum becomes
 the player's points. In order for the player to win, he must continue rolling the dice
 until your make your point. If the player rolls a 7 before making his point then he
 automatically loses.
 
 
 Some of the things that the program must do is:
 ++Play one or more games
 ++The input will consist of asking the user for their first name and last name
 ++Names may contain imbedded blank spaces
 ++The program will echo print the name as well as the interactive crap gram
 */
//
//  main.cpp
//  Craps
//
//  Created by Guillermo Molina Matus on 10/3/19.
//  Copyright © 2019 Guillermo Molina Matus. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

void menu(); //This will print out the menu screen
int rollDice(); //Function to roll the dice
void craps(); //This will start the game
void stats(); //Will show stats when user ends the program
void rules(); //Will display rules

//This is the require struct record
struct record
{
    string fName; //This will store the players first name
    string lName; //This will store the players last name
    float wins = 0; //This is the number of wins
    float losses = 0; //This is the number of losses
    float percentWins; //This is the average number of wins for the player
};
record Player;    //The variable is where the players record will be stored in


int main()
{
    string fMenuChoice; //This will receive the user input according to the menu
    char menuChoice; //This will receive only one character. It is also used for validation
    char option; //THis will be used to see if they want to play craps again
    
    cout << setw(35) << "WELCOME TO CRAPS" << endl; //This is the welcome screen on the documentation
    

    /*
     Usually if we use cin to receive a name then if the user enters two first names or last names then the program
     will simply ignore the second one. As a way to respect the user the we can use the function
     getline() to properly store multiple first or last names.
     */
    
    //We will start by asking the user for their first name
    cout << "Please input your first name then hit return" << endl;
    getline(cin, Player.fName);
    
    //We are going to ask the user for their last name now
    cout << "Please input your last name then hit return" << endl;
    getline(cin, Player.lName);
    
    //Here it is obvious that we are greeting the user
    cout << "Hi " << Player.fName << " " << Player.lName << "." << endl;

    do
    {
        menu();
        bool isnotletter=cin.fail();//cin.fail returns true if the input is something that disagrees with the data type (ex string and int would)
       isnotletter = false;

        cin >> fMenuChoice; //This will accept multiple characters as a choice for the menu. This will be used for validation
        menuChoice = fMenuChoice[0]; //This will only send the first character to menuChoice for further processing
        while (menuChoice != 'q' && menuChoice != 'Q') //This will run as long as the user does not decide to quit
        {
            if (isalpha(menuChoice)) //This checks to make sure that menuChoice is only letters
            {
                if(fMenuChoice.size() > 1) //If the users input is more than one character then the program will not run
                {
                    system("CLS");
                    cout << "\nYou made an invalid selection." << endl;
                    cout << "Please try again!" << endl;
                }
                else
                {
                    if (menuChoice == 'P' || menuChoice == 'p')
                    {
                        craps();
                    }
                    else if (menuChoice == 'R' || menuChoice == 'r')
                    {
                        rules();
                    }
                    else //If the user inputs a choice not displayed on the menu screen
                    {
                        system("CLS");
                        cout << "\nYou made an invalid selection" << endl;
                        cout << "Please try again" << endl;
                    }
                }
            }
            else if (!isalpha(menuChoice)) //If the user inputs a number then this will be printed on the screen
            {
                system("CLS");
                cout << "\nYou made an invalid selecton" << endl;
                cout << "Please try again" << endl;
            }
            menu();
            cin >> fMenuChoice; //This will accept multiple characters as a choice for the menu. This will be used for validation
            cout << endl;
            menuChoice = fMenuChoice[0]; //This will only send the first character to menuChoice for further processing
        
        }
        if (menuChoice == 'q' || menuChoice == 'Q')
        {
            stats(); //Once the players ends the game then it will display the stats
        }
        
        cout << "\n\nWould you like to play Craps again? " << endl;
        cin >> option;
        
    }
    while (option == 'y' || option == 'Y');
    
    
    
    return 0;
}


//*******************************************************************
// stats() Function
//
// task: When the player chooses to end the program then this function
// will be activated and display the users their stats.
// data in: this will be triggered if menuChoice == 'Q'
// data returned: The program will display the user their win/lose
// ratio with a little message
//*******************************************************************
void stats()
{
    cout<<setprecision(2)<<fixed;
    float wins = Player.wins, losses = Player.losses;
    Player.percentWins = (wins / (wins + losses) ) * 100; //Formula to find average number of wins
    
    
    if (wins == losses)
    {
        cout << "\n\nWow, you just broke even with " << wins << " win(s) and " << losses << " loss(es). You of course won " << Player.percentWins << "% of your games." << endl;
    }
    else if (wins < losses)
    {
        cout << "\n\nToo bad you only won " << wins << " game(s) and lost " << losses << " game(s). You won " << Player.percentWins << "% of your games." << endl;
    }
    else if (wins > losses)
    {
        cout << "\n\nHurray you won " << wins << " game(s) and lost " << losses << " game(s). You won " << Player.percentWins << "% of your games." << endl;
    }
}



//*******************************************************************
// menu() Function
//
// task: When called it will simply display the menu to the player
// data in: None
// data returned: None
//*******************************************************************
void menu() //Menu Screen
{
    cout << "Please make a choice of the following" << endl;
    cout << "P-----Play craps" << endl;
    cout << "R-----See rules" << endl;
    cout << "Q-----Quit game" << endl;
}

//*******************************************************************
// craps() Function
//
// task: Depending on what selection the user makes on the menu page
// something different will Happen. Three options are: (P) it will play
// the game craps, (R) will display the game rules to the user, and
// (Q) will quit the game
// data in: Data in will be the players choice on the menu screen
// this could either be char menuChoice or fMenuChoice
// data returned: When this function finishes it will let the user
// know what they rolled rolled and at the end if they won or not
//*******************************************************************


void craps()
{
    enum Status { WIN , LOSS, CONTINUE };
    Status gameStatus;
    int sum; //Will hold the sum of both die
    int rollCounter = 0; //Will count the number of rolls
    int points; //Player points
    srand(time(NULL)); //Uses seed to generate random number
    sum = rollDice();
    rollCounter++;

    
    switch( sum )
    {
       case 7:
       case 11:
          gameStatus = WIN; // Basically if the roll is equal to 7 or 11 then it will set game
//            status to WIN
          break;
       case 2:
       case 3:
       case 12:
          gameStatus = LOSS; // Sets gameStatus to Loss for eveything aboe
          break;
       default:
          gameStatus = CONTINUE; //Any other roll will set gameStatus to Continue
          points = sum;
          cout << "Point is " << points << endl;
          break;

    }

    // If sum is 4,5,6,8,9 or 10 it will keep rolling until the player either losses or wins
    while ( gameStatus == CONTINUE )
    {
       sum = rollDice();
       rollCounter++;
       
       if ( sum == points )
          gameStatus = WIN;

       else
          if ( sum == 7 )
             gameStatus = LOSS;

    }

    //This will display a message depending on the result
    if ( gameStatus == WIN ) {
       cout << "\nPlayer wins\n" << endl;
        Player.wins++;

    }
    else {
       cout << "\nPlayer loses\n" << endl;
        Player.losses++;
    }

}


int rollDice()
{
    int die1,die2, rollSum;
    
    //roll tow dice
    die1 = 1 + rand() % 6;
    die2 = 1 + rand() % 6;
    
    //total and prints results
    rollSum = die1 + die2;
    cout << "You rolled a " << die1 << " and a " << die2 << " = " << rollSum << endl;
    
    return rollSum;
}

//*******************************************************************
// rules() Function
//
// task: When called it will simply display the rules to the player
// data in: None
// data returned: None
//*******************************************************************
void rules()
{
    cout << "\n\nHere are the rules. A player rolls 2 dice. Each die has 6 faces. These faces contain 1, 2, 3, 4, 5, and 6 spots. After the dice have come to rest, the sume of the spots on the two upward faces is calculated. If the sum is 7 or 11 on the first throw, the player wins. If the sim is 2, 3, or 12 on the first throw (called 'craps'), then player loses (the house wins). If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then that sum becomes the player's 'points'. To win, you must continue rolling the dice until you make your point. The player loses by rolling a 7 before making the point." << endl;
}
