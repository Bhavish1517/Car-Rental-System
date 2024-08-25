#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <iomanip>

using namespace std;
void customerData();
void readUserPass(); 
void carData(); 
int countUser(); 
void menu(); 
void admin(); 
void user(); 
void tNc(); 
void password(); 
void displayCar();
void showCarData();
void newUserPass();
void newCustData();
void existingCust();
void rentcar(int userIndex,int n);
void delCar();
void newCarData();

class car {
public:
    char plate_num[10];     //string plate_num;
    char brand[20];         //string brand;
    char model[20];         //string model;
    int seating_cap;
    char colour[20];        //string colour;
    float rate_per_hour;
    float rate_per_half;
    float rate_per_day;
    char transmission[10];

    int calculateRentalPrice(int hour) {
        int hour_24, hour_12, hour_1;
        int total, total_24, total_12, total_1;
        
        hour_24 = hour / 24;
        hour_12 = (hour - hour_24 * 24) / 12;
        hour_1 = (hour - hour_24 * 24 - hour_12 * 12) / 1;
        
        total_24 = hour_24 * rate_per_day;
        total_12 = hour_12 * rate_per_half;
        total_1 = hour_1 * rate_per_hour;
        
        total = total_24 + total_12 + total_1;
        return total;
    }

    int carCount()
    {
        int numOfCar = 0;
        ifstream ifs("car rental.txt"); 

        string line;
        while(getline(ifs, line))
        {
            if (!line.empty())
                numOfCar++;
        }
        ifs.close();
        return numOfCar;
    }

};

class customer{
    public:
	    int id;
	    char name[100];   //string name;
	    char phone[15];   //string phone;
	    char address[100];    //string address;

        int custCount()
        {
            int numOfCust = 0;
            ifstream ifs("Customer.txt"); 

            string line;
            while(getline(ifs, line))
            {
                if(!line.empty())
                    numOfCust++;
            }
            ifs.close();
            return numOfCust;
        }
};

class pass
{
public:
	int ID;
	char passWord[20];

    string getpassword()
    {
        string password;
        char ch;
        ch = cin.get();
        while(true) 
        {
            ch = cin.get();
            if (ch == '\n')
                break;
            password += ch;
        }
        return password;
    }
	
};

pass userPass[1000];
car rent[1000];
customer cust[1000];

void carData ()
{
	ifstream ifs;
	ifs.open("car rental.txt");
	int i = 0;
	
	while(ifs.getline(rent[i].plate_num,10,' '))
	{
		ifs.getline(rent[i].brand,20,' ');
		ifs.getline(rent[i].model,20,' ');
		ifs >> rent[i].seating_cap;
		ifs.ignore();
		ifs.getline(rent[i].colour,20,' ');
		ifs >> rent[i].rate_per_hour;
		ifs.ignore();
		ifs >> rent[i].rate_per_half;
		ifs.ignore();
		ifs >> rent[i].rate_per_day;
		ifs.ignore();
		ifs.getline(rent[i].transmission,6);
		i++;
		ifs>>ws;
	}
	
	ifs.close();
}

void readUserPass()
{
	ifstream ifs;
	ifs.open("UserPass.txt");
	
	int i=0;
    while(ifs >> userPass[i].ID) 
    {
    ifs.ignore(); // Read and discard the delimiter
    ifs.getline(userPass[i].passWord, 20);
    i++;
    }

	ifs.close();
    
}


void password()
{
    cout << "\n\nENTER THE ADMIN PASSWORD: ";
    string enteredPassword = userPass->getpassword();

    if(enteredPassword == "admin")
    {
        system("cls");
        admin();
    }
    else
    {
        cout << "\n\tWrong Password.. Call Administrator";
        cout << "\n\tReturning to Main Menu..";
        cout << "\n\nPress Enter to Continue.";
        getch();
        system("cls");
        menu();
    }
}

void customerData()
{
	ifstream ifs;
	ifs.open("Customer.txt");
	int i = 0;
	
    while(ifs >> cust[i].id) 
    {
    ifs.ignore(); // Read and discard the delimiter
    ifs.getline(cust[i].name, 100, ';');
    ifs.getline(cust[i].phone, 15, ';');
    ifs.getline(cust[i].address, 1500);
    i++;
    }
	ifs.close();
}

int countUser()
{
	int numOfCust = 0;
	ifstream ifs("UserPass.txt"); 

	string word;
	while(getline(ifs, word))
	{
    	if(!word.empty())
        	numOfCust++;
	}

	ifs.close();

	return numOfCust;
}

void displayCar()
    {
	    cout << "|  Plate Number\tBrand\t Model\tCapacity    Colour   Rate Per Hour(k)   Rate Per 12 Hour(k)   Rate Per 24 Hour(k)   Transmission" << endl;
	    cout << "|  =======================================================================================================================" << endl;
	    for(int i = 0; i < rent->carCount(); i++)
	    {
		    cout << "|   " << rent[i].plate_num << "\t\t" << rent[i].brand << "\t " << rent[i].model << "\t   " << rent[i].seating_cap << "\t     "
			    << rent[i].colour << "\t  " <<rent[i].rate_per_hour << "\t\t    " << rent[i].rate_per_half << "\t\t    " << rent[i].rate_per_day 
			    << "\t\t       " << rent[i].transmission << endl;
	    }
    }

void existingCust(bool neww, int idi = 100)
{
    int userID, n;
    char carSelect[10];
    int hour;

    if(neww == false)
    {
        cout << "\n\tPlease enter user ID: ";
        cin >> userID;
        n = cust->custCount();
    }
    else
    {
        userID = idi;
        n = cust->custCount() + 1;
    }

    int userIndex = -1; 
    for(int i = 0; i < n; i++)
    {
        if(userID == cust[i].id)
        {
            userIndex = i;              //Store the index of the user
            break;
        }
    }

    if(userIndex == -1)
    {
        cout << "\n\tUser not found in the system. Please create a new user or check the user ID.";
        cout << "\n\nPress Enter to Continue.";
        getch();
        system("cls");
        menu();
        return; 
    }

    else
    {
        rentcar(userIndex,n);
    }
    
    cout<<"\nPress any key to continue.";
    getch();
    system("cls");
    menu();
}

void rentcar(int userIndex, int n)
{
    char carSelect[10];
    int hour = 0;
    cout<<"\n\n\tWELCOME\n\tNAME: " << cust[userIndex].name << "\n\tID: " << cust[userIndex].id << "\n\n\n";

    displayCar();
    
    cout<<"\n\tPlease select car";
    cout<<"\n\tPlate Number: ";
    cin>>ws;
    cin>>carSelect;

    int j = -1;
    for(int i = 0; i < n; i++)
    {
        if(strcmp(carSelect, rent[i].plate_num) == 0)
        {
            j = i;
        }
    }

    if(j == -1)
    {
        cout<<"You have entered wrong car number!"<<endl;
        Sleep(2000);
        rentcar(userIndex,n);
    }
    else
    {
        cout<<"\n\tHours of rent: ";
        cin>>hour;
       
        while((hour<6)){
            cout<<"Minimum hours of rent is 6 !!  Please enter again or enter 0 to go back to menu"<<endl;
            cout<<"\n\tHours of rent: ";
            cin>>hour;
            if(hour == 0)
            {
                menu();
                break;
            }
            
        }
        
    
        int rental_price = rent[j].calculateRentalPrice(hour);

        cout<<"\tRental Price for " << hour << " hours: Rs " << rental_price << endl;
        cout<<"\n\tDo you want to rent?   1. Yes  2. No: ";
        int response;
        cin>>response;

        if(response == 1)
            {
                cout<<"\n                       Car Rental - Customer Invoice                  "<<endl;
                cout<<"	///////////////////////////////////////////////////////////"<<endl;
                cout<<"	| Invoice No. :"<<"------------------|"<<setw(10)<<"#Cnb81353"<<" |"<<endl;
                cout<<"	| User Id:"<<"-----------------------|"<<setw(10)<<cust[userIndex].id<<" |"<<endl;
                cout<<"	| Car Model :"<<"--------------------|"<<setw(10)<<rent[j].model<<" |"<<endl;
                cout<<"	| Car No. :"<<"----------------------|"<<setw(10)<<carSelect<<" |"<<endl;
                cout<<"	| Number of hours :"<<"--------------|"<<setw(10)<<hour<<" |"<<endl;
                cout<<"	| Your Rental Amount is :"<<"--------|"<<setw(10)<<rental_price<<" |"<<endl;
                cout<<"	 ________________________________________________________"<<endl;
                cout<<"\n";
                cout<<"	| Total Rental Amount is :"<<"-------|"<<setw(10)<<rental_price<<" |"<<endl;
                cout<<"	 ________________________________________________________"<<endl;
                cout<<"	 # This is a computer generated invoce and it does not"<<endl;
                cout<<"	 require an authorised signture #"<<endl;
                cout<<" "<<endl;
                cout<<"	///////////////////////////////////////////////////////////"<<endl;
                int f;
            }
    }

}

void newCustData()
{
	ofstream ofs;
    int new_id = cust->custCount() + 1001;

	ofs.open("Customer.txt", fstream::app);
	ofs << endl;

	cust[cust->custCount()].id = new_id;
	ofs << cust[cust->custCount()].id;
	ofs << ";";

	cout<<"\n\tPlease enter the data below : ";
	cout<<"\n\tName : ";
	cin>>ws;
	cin.getline(cust[cust->custCount()].name,100);

	ofs << cust[cust->custCount()].name<<";";

    cout<<"\n\tPhone Number : ";
	cin.getline(cust[cust->custCount()].phone,15);

	ofs << cust[cust->custCount()].phone;
	ofs << ";";
	
	cout<<"\n\tAddress : ";
	cin.getline(cust[cust->custCount()].address,500);

	ofs << cust[cust->custCount()].address;
	ofs.close();

	system("cls");
    existingCust(true,new_id);
}

void newCarData()
{
	ofstream ofs;
	ofs.open("car rental.txt" , fstream::app);
	ofs<<endl;
	
	int newCar = rent->carCount() + 1;
	cout<<"\n\tPlease enter the car data below : " << endl;
	
	cout<<"\n\tPlate Number : ";
	cin>>ws;
	cin.getline(rent[newCar].plate_num,10);
	ofs << rent[newCar].plate_num;
	ofs << " ";
	
	cout<<"\tBrand : ";
	cin.getline(rent[newCar].brand,20);
	ofs << rent[newCar].brand;
	ofs << " ";
	
	cout<<"\tModel : ";
	cin.getline(rent[newCar].model,20);
	ofs << rent[newCar].model;
	ofs << " ";
	
	cout<<"\tSeating Capacity : ";
	cin>>rent[newCar].seating_cap;
	ofs << rent[newCar].seating_cap;
	ofs << " ";
	
	cout<<"\tColour : ";
	cin>>ws;
	cin.getline(rent[newCar].colour,20);
	ofs << rent[newCar].colour;
	ofs << " ";
	
	cout<<"\tRate Per Hour (in thousand's): ";
	cin>>rent[newCar].rate_per_hour;
	ofs << rent[newCar].rate_per_hour;
	ofs << " ";
	
	cout<<"\tRate Per 12 Hour  (in thousand's): ";
	cin>>rent[newCar].rate_per_half;
	ofs << rent[newCar].rate_per_half;
	ofs << " ";
	
	cout<<"\tRate Per 24 Hour  (in thousand's): ";
	cin>>rent[newCar].rate_per_day;
	ofs << rent[newCar].rate_per_day;
	ofs << " ";
	
	cout<<"\tTranmission (A/M) : ";
	cin>>ws;
	cin.getline(rent[newCar].transmission,6);
	ofs << rent[newCar].transmission;
	
	ofs.close();
	system("cls");
	
	carData();
	admin();
}

void newUserPass()
{
	ofstream ofs;
	ofs.open("UserPass.txt", fstream::app);
	userPass[countUser()].ID = countUser()+1;
	string password;
	cout<<"\n\n\nID(DEFAULT): "<<userPass[countUser()].ID;
	cout<<"\n\nADD PASSWORD: ";
    password = userPass->getpassword();
	// put it in the text file
	strcpy(userPass[countUser()].passWord,password.c_str());
	ofs<<userPass[countUser()].ID;
	ofs<<";";
	ofs<<userPass[countUser()].passWord;
	ofs<<endl;	
	
	system("cls");
	admin();

}

void showCarData()
{
    displayCar();
	int x;
	cout<<"\n\t1. BACK";
	cout<<"\n\t2. MAIN MENU"<<endl<<"\n\n";
	cout<<"\n\nINPUT : ";
	cin>>x;
	system("cls");
	if(x==1)
		admin();
	else
        menu();
}

void admin()
{
	int x;
	cout<<"\n\t1. ADD ADMIN";
	cout<<"\n\t2. SHOW ALL CAR DATA";
	cout<<"\n\t3. ADD A NEW CAR";
	cout<<"\n\t4. DELETE CAR";
	cout<<"\n\t5. MENU";
	cout<<"\n\nINPUT : ";
	cin>>x;
	
	system("cls");
	switch (x) {
    case 1:
        newUserPass();
        break;
    case 2:
        showCarData();
        break;
    case 3:
        newCarData();
        break;
    case 4:
        delCar();
        break;
    case 5:
        menu();
        break;
    default:
        menu();
        break;
}
}

void user()
{
	int x;
	cout<<"\n\t1. NEW";
	cout<<"\n\t2. EXISTING";
	cout<<"\n\t3. MAIN MENU";
	cout<<"\n\n\nINPUT : ";
	cin>>x;
	system("cls");

	switch (x) 
    {
    case 1:
        newCustData();
        break;
    case 2:
        existingCust(false);
        break;
    case 3:
        menu();
        break;
    default:
        menu();
        break;
    }
}

void menu()
{
	int x;
	cout<<"\n\t1. ADMIN";
	cout<<"\n\t2. USER";
	cout<<"\n\t3. T&C";
	cout<<"\n\t4. EXIT\n";
	cout<<"\n\nINPUT : ";
	cin>>x;

	system("cls");
	
    switch (x)
    {
    case 1:
        password();
        break;
    case 2:
        user();
        break;
    case 3 :
        tNc();
        menu();
        break;
    case 4 :
		cout<<"\n\nThank you for choosing our Car Rentals.\nWe look forward to serving you and making your journey a memorable one.\nSafe travels!"<<endl;
		Sleep(1000);
		exit(0);
        break;
    default:
        menu();
        break;
    }
}

void delCar()
{
    char plate[10];
    
    ofstream ofs;
    ofs.open("temp.txt");
    
    displayCar();
    
    cout << "\nEnter the car plate number that you want to delete (CAPITAL LETTERS WITHOUT SPACES): ";
    
    cin>>plate;
    
    for (int i = 0; i < rent->carCount(); i++)
    {
        if (strcmp(plate, rent[i].plate_num) == 0)
        {
            continue;  // Skip the car entry with the specified plate number
        }
        
        ofs << rent[i].plate_num << " " << rent[i].brand << " " << rent[i].model << " "
            << rent[i].seating_cap << " " << rent[i].colour << " " << rent[i].rate_per_hour << " "
            << rent[i].rate_per_half << " " << rent[i].rate_per_day << " " << rent[i].transmission;
        
        if (i != rent->carCount() - 1)
        {
            ofs << endl;
        }
    }
    
    ofs.close();
    remove("car rental.txt");
    rename("temp.txt", "car rental.txt");
    system("cls");
    
    // Update car data and call the admin function again
    carData();
    admin();
}

void tNc()
{
	cout<<"\n\nWelcome to Car Rental Management System\n\n"<<endl;
	cout<<endl;
    cout<<"1. MINIMUM RENT TIME IS 6 HOURS\n";
    cout<<"2. THE USER SHOULD PAY FOR THE DAMAGES IN CASE OF ANY ACCIDENT\n";
    cout<<"3. PREPARE ITEMS AS BELOW\n";
    cout<<"   - Valid Driver's License\n";
    cout<<"   - Identity Proof\n";
    cout<<"   - Address Proof\n";
    cout<<"4. ADDITIONAL CHARGES WILL BE APPLIED IF NOT RETURNED WITHIN SPECIFIED TIME\n";
    cout<<"5. SAFE JOURNEY!\n";
    cout<<"\n\n PRESS ANY KEY TO CONTINUE :)\n";
                        
	getch();
    system("cls");
}

int main()
{ 
	cout<<"\n\nWelcome to Car Rental Management System\n\n"<<endl;
	readUserPass();
	customerData();
	carData();
    menu();
	return 0;
}
