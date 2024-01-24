#pragma once 
#include <iostream>
#include <vector>
#include <string>
#include <cmath>  //This is used to use the pow function
#include <iomanip> //Used for table formatting
#include <fstream>
#include <algorithm>
using namespace std;

//The list of all the functions used in the program are defined below
void SetCityAttributes(vector <double> &x, vector<double> &y,vector<string> &cityname);
double CalcDistance(double x1,double y1,double x2, double y2);
void Menu(vector<string>cityname);
void VISITCityAttributes(vector <double> x, vector<double> y,vector<string> cityname,vector <double> &XVisit,
	vector <double> &YVisit, vector <string> &CityVisit,vector<int> CityNum);
void OutputDistanceInfo(vector<string> cityname,vector <double> x, vector<double> y);
int alreadyentered(vector<int> CityNumber, int Enteredvalue);
template<typename format> void FormatTable(format value);
void TripPlanner(vector <double> &Xcoord,vector<double> &Ycoord,vector<string> &City);
void MainMenu();
void MinDistance(vector<double> x,vector<double> y, vector<string> city);
void MaxDistance(vector<double> x,vector<double> y, vector<string> city);
void DisplayCities(vector<string> cities);
void AddCity(vector<string> &city,vector<double> &x,vector<double> &y);
bool ValidPassword(const string password);
void RemoveCity(vector<string> &city,vector<double> &x, vector<double> &y);
void MinTripDistance(vector<string>city,vector<double>x,vector<double>y);
int Factorial(int n);