/*
	Journey Planner

		Sam Jones

	This program allows the user to organise a journey from cities read from a file.
	The format for the file must be: <city name> <x coordinate> <y coordinate>
	The input for the main menu is a char from the list. Quit 'x'
	The input for the Trip Planner menu is an integer from the list. Stop inputs '0'

*/
#include "resources.h"

int main()
{
	system("color 0e");
	string MenuOption =""; //used string to stop user entering multiple inputs
	vector <double> Xcoord; vector <double> Ycoord; vector <string> City; //Creates variables for the city name and x,y coordinates
	const string password = "pizza"; //This password is used for adding/removing a city. it cannot be changed.

	SetCityAttributes(Xcoord,Ycoord,City); //Calls the function to set the x,y coords and city name.

	while(1)
	{
		system("cls");
		MainMenu();
		cin.clear();
		getline(cin, MenuOption); //Reads the whole line as one string. Doent allow multiple inputs by whitespace separation
		MenuOption[0] = tolower(MenuOption[0]); //Allows the user to enter uppercase or lowercase letters
		if (MenuOption.size()>1) //If more than one character was entered set string to Z therefor throw and error message
		{
			system("cls");
			system("color c0");
			cout << "You must enter one character only.\n" << endl;
			MainMenu();
			getline(cin, MenuOption);
			system("color 0e");
		} 
		if (MenuOption == "x") break;    //Terminates the program if the user enters x
		switch (MenuOption[0])  //
		{
			case('a'):
				{
					system("color 0e");
					system("cls");
					DisplayCities(City);
					system("pause");
					system("cls");
					break;
				}
			case('b'):
				{
					system("color 0e");
					system("cls");
					if(ValidPassword(password)==true){
						AddCity(City,Xcoord,Ycoord);           //If the user enters the correct password this function can be called.
					}
					break;
				}
			case('c'):
				{
					system("color 0e");
					system("cls");
					if(ValidPassword(password)==true){
						RemoveCity(City,Xcoord,Ycoord);
					}
					break;
				}
			case('d'):
				{
					system("color 0e");
					system("cls");
					MinDistance(Xcoord,Ycoord,City);
					system("pause");
					system("cls");
					break;
				}
			case('e'):
				{
					system("color 0e");
					system("cls");
					MaxDistance(Xcoord,Ycoord,City);
					system("pause");
					system("cls");
					break;
				}
			case('f'):
				{
					system("color 0e");
					system("cls");
					TripPlanner(Xcoord,Ycoord,City);
					break;
				}
			default:
				{
					if (MenuOption==""){system("cls");break;} //Stops the program throwing error message after coming out of other cases.
					system("cls");
					system("color c0");
					cout << "Please enter a correct letter from the menu\n" << endl;
					break;
				}
		}
	}
	return 0;
}

		