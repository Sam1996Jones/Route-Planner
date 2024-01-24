#include "resources.h"

/*
	This function reads the city name, x coordinate and y coordinate from a file.
	The format of the file must be:
	London 20 30
	Moscow 50 100
*/
void SetCityAttributes(vector <double> &x, vector<double> &y,vector<string> &cityname)
{
	string city;
	double xcoord;double ycoord;
	ifstream infile("city.txt");
	while(infile >> city >> xcoord >> ycoord)  //Reads values from a file
	{
		cityname.push_back(city); x.push_back(xcoord); y.push_back(ycoord); //Stores the read values into a vector
	}


}

/*This function calculates the distance between two cities and returns the value as a double*/
double CalcDistance(double x1,double y1,double x2, double y2)
{
	return  sqrt( pow(x1 - x2,2) + pow(y1-y2,2) ); //sqrt calculates the square root. pow raises the calculation to a given power.

}

/*This procedure sets the initial menu for the user within the trip planner*/
void Menu(vector<string>cityname)
{
	int counter = 0; //Used to loop through the city name vector
	
	while(counter < cityname.size() ){											// loops through the vector to present user with the city names
		cout << counter+1 << " for " << cityname[counter] << endl;
		counter++; //increments the counter by one
	}
	cout << "0 for end of route planning" << endl;
}

/*sets the new vectors for the cities to be visited*/
void VISITCityAttributes(vector <double> x, vector<double> y,vector<string> cityname,vector <double> &XVisit,
	vector <double> &YVisit, vector <string> &CityVisit,vector<int> CityNum){
		for(int i=0;i<CityNum.size();i++){
			XVisit.push_back(x[CityNum[i]-1]); //uses the value stored in the citynum from which the user inputted 
			YVisit.push_back(y[CityNum[i]-1]); // to store the new city values in another vector so that they can be
			CityVisit.push_back(cityname[CityNum[i]-1]); //easily accessed later
		}
}

/*Calculates the distance between and creates the tables of cities the user would like to visit*/
void OutputDistanceInfo(vector<string> cityname,vector <double> x, vector<double> y){
	vector <double> distances; //The distance between two cities to be calculated
	double TotalDistance=0; //Used to store the value of the total distance for the journey.
	double maxdistance=-99999999; double mindistance =99999999; //sets the max and min distance to extremley large/small values so that the max and min can be found
	string mincity1;string mincity2;string maxcity1;string maxcity2;
	double temp=0; //temp stores the distance calculated.


	FormatTable(" "); //Creates a blank space in the top left of the table.
	for(int i =0; i < cityname.size(); i++){
		//cout << "               " << cityname[i];
		FormatTable(cityname[i]);
	}
	cout<<endl;
	for(int p =0; p < cityname.size(); p++){                 //This for loops calculates the distances between each city and prints in as a table
		//cout << '\n' << cityname[p];
		FormatTable(cityname[p]);
		for(int z =0; z < cityname.size(); z++){            // The max and min distance between two cities is also calculated and stored
			temp = CalcDistance(x[p],y[p],x[z],y[z]);
			//cout << "\t\t" << temp;
			FormatTable(temp);
			if(temp>=maxdistance && temp!=0){             //The !=0 ensures that the min distance is not 0 
				maxdistance = temp;                        
				maxcity1 = cityname[p];
				maxcity2 = cityname[z];
			}else if (temp <= mindistance && temp!=0){
				mindistance = temp;
				mincity1 = cityname[p];
				mincity2 = cityname[z];
			}
		}
		cout << endl;
	}
	cout << endl;
	cout << "\nThe maximum distance is: " << maxdistance << " between " << maxcity1 << " & " << maxcity2 << endl;
	if(cityname.size() > 2){ //Only display the min distance if there are more than 2 cities
		cout << "The minimum distance is: " << mindistance << " between " << mincity1 << " & " << mincity2 << endl;
	}

	cout << "\nA possible route for this journey is: \n";
	for(int q = 0; q < cityname.size()-1 ;q++){                            //This loop calculates the total distance between the cities for a possible route
		distances.push_back(CalcDistance(x[q],y[q],x[q+1],y[q+1]));
		TotalDistance += distances[q];
	}
	cout << cityname[0];
	for(int j = 1;  j < cityname.size();j++){                           //This loop displays a possible route through the chosen cities.
		cout << " -> " << distances[j-1] <<" -> " << cityname[j];
	}
	distances.push_back(CalcDistance(x[0],y[0],x[x.size()-1],y[y.size()-1]));
	cout << " -> " << distances[distances.size()-1];
	TotalDistance+=distances[distances.size()-1];
	cout << "\nThe total distance for this journey is: " << TotalDistance << endl;

	//cout<<"\nThe shortest distance route for this journey is: "<<endl;;
	MinTripDistance(cityname,x,y);

}

/*This function finds out if the user had already input a city. if so asks the user to enter another input*/
int alreadyentered(vector<int> CityNumber, int Enteredvalue){
	bool collision=true; //Used to determine if the user has already input that city. Assumed true to start loop
	if(CityNumber.size() !=0){ //Will only loop if the size of the vector is not 0
			
		for(int h=0;h<CityNumber.size();h++){     //Loops through the vector to see if the user has already input a value
				if(Enteredvalue == CityNumber[h]){
					system("color c0");
					cout<<"You can only visit each city once. Please enter another number: ";
					if(!(cin>>Enteredvalue)){            //stops the user from entering an invalid input after the same city has been input again
						system("color c0");
						cout <<"Invalid input. Please enter a number from the list: ";
						cin.clear();                                          
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
						cin >> Enteredvalue;
					}
					h=-1; //sets the counter back to 0 so that it can loop again to make sure the user doesnt enter a value in a position
				}         //less than when a collision occured.
		}
	}
	return Enteredvalue;
}

/*This function helps format the table so that all of the values align to the left hand side.*/
template<typename format> void FormatTable(format value){
	const char space = ' ';
	const int WidthSpace = 15;
	cout << left << setw(WidthSpace) << setfill(space) << value;
}

/*This is one of the main functions of the program. It contains all of the code for the Trip Planner*/
void TripPlanner(vector <double> &Xcoord,vector<double> &Ycoord,vector<string> &City){
	vector <double> XcoordVisit; vector <double> YcoordVisit; vector <string> CityVisit; //Stores values for the cities to visit, input by user
	int temp; //This stores the user inputted number from the menu. The value here will be stored into a vector
	vector<int> CityToVisitNUM; //This is a vector of the number of cities wished to visit. value stored at [0] will be the start point.
	bool redo = true; //Decides if the user wants to find a new route.
	char _redo =' '; // input to decide if a new route is wanted
	string ListToVisit=""; //used to create a string of the cities they have chosen to visit
	int CounterForVisit=1; // used to loop through the cities to visit to add to the string ListToVisit

	
	
	do{
		cout <<"\t\t\t~~Around The World Trip Planner~~\n" << endl;
		cout<< "Please choose from which city you wish to start your travel; enter " <<  endl;
		Menu(City);
		while(1){
			
			if(!(cin>>temp)){
				system("color c0");
				cout <<"Invalid input. Please enter a number from the list: ";
				cin.clear();                                          
				cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Taken from C++ forums to stop program crashing when integer not entered.
				continue;
			}
			system("color 0e");
			if(temp > City.size()){     //Prevents the user entering a value that does not appear on the list.
				system("color c0");
				while(temp>City.size()){ //Keeps asking the user to enter a value until it is on the list
					cout <<"The value you have entered is not acceptable. Please enter an appropriate value from the list: ";
					cin >> temp;
				}
			}

			system("color 0e");
			
			if (temp <= 0){
				if(CityToVisitNUM.size()==1){
					system("color c0");
					system("cls");
					cout <<"Please enter more than 1 city: " << endl;
					Menu(City);
					cin >> temp;
				}else{system("cls");break;} //Drops out the loop if 0 is entered, otherwise add the number to the vector
			}
			temp = alreadyentered(CityToVisitNUM,temp);
			system("cls"); //clears the screen to make the layout of the menu look nicer
		
			system("color 0e");
			CityToVisitNUM.push_back(temp);
			system("cls");
			cout << "You chose you start your journey from " << City[CityToVisitNUM[0]-1];

			if (CityToVisitNUM.size() > 1 && temp != 0){                        //Used to display the cities the user has entered to visit
				ListToVisit += City[CityToVisitNUM[CounterForVisit]-1] + ", "; //Stores the value of the cities to visit into a string
				cout << "\nYou have chosen to visit " << ListToVisit;
				CounterForVisit++;
			}
	
			cout << "\n\nPlease choose which other city you would like to visit; enter " << endl;
			Menu(City);
		}
		if(CityToVisitNUM.size() != 0){     //Stops the calculations occuring if user enters 0 straight away. Stops program crashing.
			VISITCityAttributes(Xcoord,Ycoord,City,XcoordVisit,YcoordVisit,CityVisit,CityToVisitNUM); //Determines the x,y and name of the cities chosen to visit
			OutputDistanceInfo(CityVisit,XcoordVisit,YcoordVisit); //Calculates the distances between cities and outputs in a table
		}						                                  //This function also displays a possible route with the total distance

		cout << "\nWould you like to plan a new trip? Y/N: " << endl;
		cin >> _redo;
		if(_redo == 'n' || _redo =='N'){
			redo=false;               //if the user enter n or N redo will be set to false
		}else{
			CityVisit.clear();       //Clears the previous set of data stored within the vectors
			CityToVisitNUM.clear();
			XcoordVisit.clear();
			YcoordVisit.clear();
			ListToVisit="";      //sets back to initial value to be used for a new trip plan
			CounterForVisit=1;   // ^^
		}
		system("cls");
	}while(redo==true);							// if redo is set to false as above then the loop will terminate
}

/*Creates a simple menu which tells the user what options are available to select*/
void MainMenu()
{
	cout << "a. Show list of cities" << endl; 
	cout << "b. Add city (PASSWORD REQUIRED)" << endl;
	cout << "c. Remove city (PASSWORD REQUIRED)" << endl; 
	cout << "d. Find two cities with minimum distance" << endl;
	cout << "e. Find two cities with maximum distance" << endl;
	cout << "f. TRIP PLANNER" << endl;
	cout << "Please select an option from the list above. Enter x to exit the program." << endl;
}

/*Calculates the Minimum distance between two cities and displays the output to the user*/
void MinDistance(vector<double> x,vector<double> y, vector<string> city)
{
	double mindistance=99999999;
	double temp=0;
	string mincity1="";string mincity2="";
	for(int p =0; p < city.size(); p++){                
		for(int z =0; z < city.size(); z++){            
			temp = CalcDistance(x[p],y[p],x[z],y[z]);
			if (temp <= mindistance && temp!=0){
				mindistance = temp;
				mincity1 = city[p];
				mincity2 = city[z];
			}
		}
	}
	cout << "The minimum distance is: " << mindistance << " between " << mincity1 << " & " << mincity2 << endl;
}

/*Calculates the max distance between two cities and displays the output*/
void MaxDistance(vector<double> x,vector<double> y, vector<string> city)
{
	double maxdistance=-99999999;
	double temp=0;
	string maxcity1="";string maxcity2="";
	for(int p =0; p < city.size(); p++){                
		for(int z =0; z < city.size(); z++){            
			temp = CalcDistance(x[p],y[p],x[z],y[z]);
			
			if(temp>=maxdistance){             //The !=0 ensures that the min distance is not 0 
				maxdistance = temp;                        
				maxcity1 = city[p];
				maxcity2 = city[z];
			}
		}
	}
	cout << "The maximum distance is: " << maxdistance << " between " << maxcity1 << " & " << maxcity2 << endl;
}

/*This function displays all of the cities in vector*/
void DisplayCities(vector<string> cities)
{
	for(int x=0;x<cities.size();x++)
	{
		cout << cities[x] << endl;
	}
}

/*This function allows the user to add a city if entering the correct password*/
void AddCity(vector<string> &city,vector<double> &x,vector<double> &y)
{
	string temp = ""; //temp stores the user input into a string.
	double tempcoord =0; //temp stores the user input for a coordinate
		system("cls");
		cout << "Password accepted.\n\nPlease enter the name of the city you wish to add:" << endl;
		getline(cin, temp);getline(cin, temp);
		city.push_back(temp);
		cout <<"Please enter the X coordinate:" <<endl;
		cin >> tempcoord;
		x.push_back(tempcoord);
		cout <<"Please enter the Y coordinate:" <<endl;
		cin >> tempcoord;
		y.push_back(tempcoord);
		cout << "You have added: " << city[city.size()-1] << " ("<<x[x.size()-1]<<","<<y[y.size()-1]<<")" << endl;
		system("pause");
}

/*This functions checks if the password the user has entered is correct*/
bool ValidPassword(const string password)
{
	string userpass="";
	cout << "Please enter the password to access this feature: ";
	cin >> userpass;
	if(userpass==password) //If the user enters a correct password this function will return true
	{
		return true;
	}else
	{
		system("color c0");
		system("cls");
		cout << "You have entered an incorrect password. You will return to the main menu"<<endl;
		system("pause");
		system("color 0e");
		return false;
	}

}

/*This function removes a city and its x y coordinates from the list*/
void RemoveCity(vector<string> &city,vector<double> &x, vector<double> &y){
	string citytoremove="";  //Stores the city to be removed
	int position=0;        //To store the postion of the collison. will be incremented
	bool positionfound = false;
	system("cls");
	cout <<"Password accepted.\n" << endl;
	DisplayCities(city);
	cout<< "Type a city from the list above you wish to remove(case sensitive):" << endl;
	getline(cin, citytoremove);getline(cin, citytoremove);
	for(int x = 0;x<city.size();x++)
	{
		if(citytoremove == city[x])
		{
			position = x;        //If the city name is found then the postion is stored in countertemp variable
			positionfound = true;
		}
	}
	if(positionfound==true){                            //only occurs if a the chosen city to delete is in the list
		for(int i=position; i<city.size()-1;i++)
		{
			city[i] = city[i+1];                  //Stores the value in the next position in the previous position
			x[i] = x[i+1];						  // ie this removes the city
			y[i] = y[i+1];
		}
		city.pop_back();            //Removes the last value on the vector
		x.pop_back();
		y.pop_back();
		cout << "You have removed: " << citytoremove << " from the list." << endl;
		system("pause");
	}else
	{
		system("color c0");
		cout <<"The city you chose was not in the list. You will return to the main menu." << endl;
		system("pause");
		system("color 0e");
	}

}

/*Calculates and displays the minimum trip distance*/
void MinTripDistance(vector<string>city,vector<double>x,vector<double>y)
{
	vector<int> numOrder;
	int temp;
	double SmallestDistance=99999999;
	vector<double> distance;
	double Totaldistance=0;
	vector<int> PossibleOrder;
	int counter=0;
	int distcount=0;
	vector <string> cityOrder;
	vector <int> CityNumOrder;

	for(int z=1;z<=city.size()-1;z++)
	{
		numOrder.push_back(z);           //A vector of numbers corresponding to the positions in the city 
	}
	
	do{
		for(int i=0;i<city.size()-1;i++)
		{
			temp = numOrder[i];
			PossibleOrder.push_back(temp);        //Puts the new order of numbers into the possible order vector
		}
		for(int p=0;p<numOrder.size()-1;p++)
			{
				distance.push_back(CalcDistance(x[PossibleOrder[counter]],y[PossibleOrder[counter]],x[PossibleOrder[counter+1]],y[PossibleOrder[counter+1]]));
				counter++;                              //The distance is calculated between each city ^^
				if (counter==PossibleOrder.size()-1)
				{
					Totaldistance += (CalcDistance(x[PossibleOrder[0]],y[PossibleOrder[0]],x[0],y[0])); //Gets the distance between the starting city and the next city in the possible order
					for(int u = 0;u<PossibleOrder.size()-1;u++)
					{
							
						Totaldistance += distance[u];
					}
					Totaldistance += (CalcDistance(x[PossibleOrder[PossibleOrder.size()-1]],y[PossibleOrder[PossibleOrder.size()-1]],x[0],y[0]));

					if(Totaldistance < SmallestDistance)  
					{
						SmallestDistance= Totaldistance; 
						cityOrder.clear();                 
						CityNumOrder.clear();                
						for(int a=0;a<PossibleOrder.size();a++)
						{
							cityOrder.push_back(city[PossibleOrder[a]]);
							CityNumOrder.push_back(PossibleOrder[a]);
						}
						PossibleOrder.clear();     //Clears the possible order so that it can be set again. makes sure the vector size keep increasing.
					}
					PossibleOrder.clear();
				}
			}
		counter=0;
		Totaldistance =0;
		distcount++;
		if(distcount < Factorial(numOrder.size()))
		{
			distance.clear();  //clears until the loop is on the final sequence. 
		}
	}while(next_permutation(numOrder.begin(),numOrder.end())); //This function calculates all the possible orders of a sequence.

	/*cout << city[0] << " -> " << CalcDistance(x[0],y[0],x[CityNumOrder[0]],y[CityNumOrder[0]])<< " -> ";
	for(int j = 0;  j < cityOrder.size()-1;j++){                           
		cout << cityOrder[j] << " -> " << distance[j] << " -> "; 
	}
	distance.push_back(CalcDistance(x[0],y[0],x[CityNumOrder[CityNumOrder.size()-1]],y[CityNumOrder[CityNumOrder.size()-1]]));
	cout << cityOrder[cityOrder.size()-1] << " -> " << distance[distance.size()-1] << endl;*/

	cout << "The shortest distance for this journey is: " << SmallestDistance << endl;
}

/*Calculates the factorial of a number*/
int Factorial(int n){
	int number=1;
	for(int x=1;x<=n;x++)
	{
		number = number*x;
	}
	return number;
}