#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <vector>
using namespace std;

time_t currTime;

class admin
{
public:
    int tno;
    char tname[10];
    char bp[10];
    char dest[10];

    int c1, c1fare, c2, c2fare;
    int d, m, y;
    int sleeper[120], ac[60];

    admin()
    {
        for (int i = 0; i < 60; i++)
        {
            ac[i] = 1;
        }
        for (int i = 0; i < 120; i++)
        {
            sleeper[i] = 1;
        }
        c1 = 60;
        c2 = 120;
    }

    void getDetail();
    void displayDetail();
    int deleteDetail(int check)
    {
        if (tno == check)
        {
            return 1;
        }
        return -1;
    }
};

class ticket
{
public:
    char source[10], destination[10], train_name[10];
    int d, m, y, seat_type, num_seats, train_number, seats[6], passenger_age[6];
    char passenger_name[6][20];
    int pnr;
    void book_ticket()
    {
        fstream file;
        admin a;
        cout << "\nEnter train number from above list:: ";
        cin >> train_number;
        file.open("trainlist.txt", ios::in | ios::out);
        while (file.read((char *)&a, sizeof(a)))
        {
            if (train_number == a.tno)
            {
                strcpy(source, a.bp);
                strcpy(destination, a.dest);
                strcpy(train_name, a.tname);
                d = a.d;
                m = a.m;
                y = a.y;
                cout << "\n\n\t\t\t------SELECT YOUR SEAT TYPE------\n\t\t\t[1]AC\n\t\t\t[2]Sleeper\nEnter your choice:: ";
                cin >> seat_type;
                if (seat_type == 1)
                {
                    cout << "----------------------\n";
                    for (int i = 0; i < 60; i++)
                    {
                        cout << "|";
                        if (a.ac[i] == 1)
                        {
                            if (i + 1 <= 9)
                            {
                                cout << "0";
                            }
                            cout << i + 1;
                        }
                        else
                        {
                            cout << "  ";
                        }
                        if ((i + 1) % 3 == 0)
                        {
                            cout << "|  ";
                        }
                        if ((i + 1) % 6 == 0)
                        {
                            if ((i + 1) % 12 == 0)
                            {
                                cout << "\n----------------------\n";
                            }
                            else
                            {
                                cout << endl << endl;
                            }
                        }
                    }
                    cout << "\nHow many seats do you want to reserve? : ";
                    cin >> num_seats;
                    if (num_seats < 1)
                    {
                        cout << "\nInvalid Input!!!\n";
                    }
                    else if (num_seats > 6)
                    {
                        cout << "\nMaximum 6 seats can be reserved using this system!\nPlease visit your nearest railway station for bulk booking!\n";
                    }
                    else if (a.c1 < num_seats)
                    {
                        cout << "\nSorry! Only " << a.c1 << " seats are available for selected train!!!\n";
                    }
                    else
                    {
                        cout<<"\n\t\t\tVisible Seat No Is Available For Reservation\n";
                        cout << "\nEnter " << num_seats << " seat numbers of your choice: ";
                        for (int i = 0; i < num_seats; i++)
                        {
                            cin >> seats[i];
                            a.ac[seats[i] - 1] = 0;
                            a.c1--;
                        }
                        for (int i = 0; i < num_seats; i++)
                        {
                            cout << "\n\tEnter passenger " << i + 1 << " name: ";
                            cin >> passenger_name[i];
                            cout << "\tAge: ";
                            cin >> passenger_age[i];
                        }
                        file.seekp(-sizeof(a), ios::cur);
                        file.write((char *)&a, sizeof(a));
                    }
                }
                else if (seat_type == 2)
                {
                    cout << "----------------------------\n";
                    for (int i = 0; i < 120; i++)
                    {
                        cout << "|";
                        if (a.sleeper[i] == 1)
                        {
                            if (i + 1 <= 9)
                            {
                                cout << "00";
                            }
                            else if (i + 1 > 9 && i + 1 < 100)
                            {
                                cout << "0";
                            }
                            cout << i + 1;
                        }
                        else
                        {
                            cout << "   ";
                        }
                        if ((i + 1) % 3 == 0)
                        {
                            cout << "|  ";
                        }
                        if ((i + 1) % 6 == 0)
                        {
                            if ((i + 1) % 12 == 0)
                            {
                                cout << "\n----------------------------\n";
                            }
                            else
                            {
                                cout << endl << endl;
                            }
                        }
                    }
                    cout << "\nHow many seats do you want to reserve? : ";
                    cin >> num_seats;
                    if (num_seats < 1)
                    {
                        cout << "\nInvalid Input!!!\n";
                    }
                    else if (num_seats > 6)
                    {
                        cout << "\nMaximum 6 seats can be reserved using this system!\nPlease visit your nearest railway station for bulk booking!\n";
                    }
                    else if (a.c2 < num_seats)
                    {
                        cout << "\nSorry! Only " << a.c1 << " seats are available for selected train!!!\n";
                    }
                    else
                    {
                        cout<<"\n\t\t\tVisible Seat No Is Available For Reservation\n";
                        cout << "\nEnter " << num_seats << " seat numbers of your choice: ";
                        for (int i = 0; i < num_seats; i++)
                        {
                            cin >> seats[i];
                            a.sleeper[seats[i] - 1] = 0;
                            a.c2--;
                        }
                        for (int i = 0; i < num_seats; i++)
                        {
                            cout << "\n\tEnter passenger " << i + 1 << " name: ";
                            cin >> passenger_name[i];
                            cout << "\tAge                  : ";
                            cin >> passenger_age[i];
                        }
                        file.seekp(-sizeof(a), ios::cur);
                        file.write((char *)&a, sizeof(a));
                    }
                }
            }
        }
        srand((unsigned)time(&currTime));
        pnr = rand();
        file.close();
    }

    void print_ticket()
    {
        cout << "\nPNR No               :" << pnr;
        cout << "\nTrain No             :" << train_number;
        cout << "\nTrain Name           :" << train_name;
        cout << "\nBoarding Station     :" << source;
        cout << "\nDestination Station  :" << destination;
        cout << "\nDate Of Travel       :" << d << "-" << m << "-" << y;
        cout << "\nClass Type           :";
        if (seat_type == 1)
            cout << "AC";
        else if (seat_type == 2)
            cout << "Sleeper";
        cout << "\nNo Of Seats Reserved :" << num_seats;
        cout << "\nReserved Seat Nos    :";
        for (int i = 0; i < num_seats; i++)
        {
            cout << seats[i] << " ";
        }
        cout << "\n\n\t\t-------Passenger Details-------\n";
        cout << "\n\t|SR NO." << "\t\t" << "|NAME" << "\t\t" << "|AGE" << "\t";
        for (int i = 0; i < num_seats; i++)
        {
            cout << "\n\t|" << i + 1 << "\t\t" << "|" << passenger_name[i] << "\t\t" << "|" << passenger_age[i] << "\t";
        }
        cout << endl;
    }
    void cancel_ticket()
    {
        admin a;
        ifstream input("trainlist.txt");
        ofstream output("primary.txt", ios::app);
        while (input.read((char *)&a, sizeof(a)))
        {

            if (train_number == a.tno && d == a.d && m == a.m && y == a.y)
            {

                if (seat_type == 1)
                {
                    for (int i = 0; i < num_seats; i++)
                    {
                        a.ac[seats[i] - 1] = 1;
                        a.c1++;
                    }
                }
                else if (seat_type == 2)
                {
                    for (int i = 0; i < num_seats; i++)
                    {
                        a.sleeper[seats[i] - 1] = 1;
                        a.c2++;
                    }
                }
                output.write((char *)&a, sizeof(a));
            }
            else
            {
                output.write((char *)&a, sizeof(a));
            }
        }
        input.close();
        output.close();
        remove("trainlist.txt");
        rename("primary.txt", "trainlist.txt");
    }
};

class reg
{
public:
    char id[10];
    char pass[10];
    void getid()
    {
        cout << "\nEnter your ID:";
        cin >> id;
        cout << "Enter the Password: ";
        cin >> pass;
        cout << "\n";
    }
    void displayid()
    {
        cout << "\n|" << "User ID:" << "\t" << "|" << "Password\n";
        cout << "|" << id << "\t\t" << "|" << pass << "\n\n";
    }
};

int check_date(int d, int m, int y);

void print_time()
{
    time(&currTime);
    cout << "\n\t\t\t     " << ctime(&currTime) << endl;
}

char pwd[10] = "admin";

int main()
{
    admin a;
    reg b;
    int choice = 0;
    while (1)
    {
        system("CLS");
        choice = 0;
        currTime = time(0);
        char *dt = ctime(&currTime);
        cout << "\n\t\t\t     " << dt << endl;
        cout << "\n\t\t\t|\tSELECT YOUR OPTION\t|";
        cout << "\n\t\t\t\t[1].Login";
        cout << "\n\t\t\t\t[2].Register";
        cout << "\n\t\t\t\t[3].Exit\n:: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
        login:
            system("CLS");
            char tempid[10];
            char temppass[10];
            int flag = 0;
            cout<<"LOGIN::\n";
            cout << "\nEnter your ID    : ";
            cin >> tempid;
            cout << "Enter the Password : ";
            cin >> temppass;
            ifstream fin("id.txt");
            while (fin.read((char *)&b, sizeof(b)))
            {
                if (!(strcmp(tempid,b.id)))
                {
                    if (!(strcmp(temppass,b.pass)))
                    {
                        flag = 1;
                        break;
                    }
                    
                }
            }
            fin.close();
            if (flag == 1)
            {
                cout << "\t\t\tLOGIN SUCCESSFULL!\n";
                system("PAUSE");
                int option = 0;
                while (option != 5)
                {
                    system("CLS");
                    print_time();
                    cout << "\n\t\t\t------RAILWAY RESERVATION SYSTEM-----\n\t\t\t     [1]RESERVATION\n\t\t\t     [2]CANCELLATION\n\t\t\t     [3]VIEW TICKET\n\t\t\t     [4]ENQUIRY\n\t\t\t     [5]RETURN TO MAIN MENU\nENTER YOUR CHOICE:: ";
                    cin >> option;
                    switch (option)
                    {
                    case 1:
                    {
                        char source[20], destination[20];
                        int d, m, y, fl = 0;
                        vector<int> available_trains;
                        cout << "\nRESERVATION\n" <<"\tBoarding point    : ";
                        cin >> source;
                        cout << "\tDestination point        : ";
                        cin >> destination;
                    input_date:
                        cout << "\tDate of travel (DD MM YYYY): ";
                        cin >> d >> m >> y;
                        if (check_date(d, m, y) == 0)
                        {
                            cout << endl;
                            goto input_date;
                        }
                        ifstream fin("trainlist.txt");
                        while (fin.read((char *)&a, sizeof(a)))
                        {
                            if (strcmp(source, a.bp) == 0 && strcmp(destination, a.dest) == 0 && d == a.d && m == a.m && y == a.y)
                            {
                                available_trains.push_back(a.tno);
                                fl++;
                            }
                        }
                        fin.close();
                        if (fl == 0)
                        {
                            cout << "\nNo trains available for above route and selected date!!!\n";
                        }
                        else
                        {
                            fin.open("trainlist.txt");
                            system("CLS");
                            cout << "\n|Train No." << "\t" << "|Train Name" << "\t" << "|Boarding pt." << "\t" << "|Destination pt." << "\t";
                            cout << "|AC-Class" << "\t" << "|AC-Class Fare" << "\t" << "|SC-Class" << "\t" << "|SC-Class Fare" << "\t";
                            cout << "|Day" << "-" << "Month" << "-" << "Year" << "\n";
                            while (fin.read((char *)&a, sizeof(a)))
                            {
                                for (int i = 0; i < fl; i++)
                                {
                                    if (available_trains[i] == a.tno)
                                    {
                                        a.displayDetail();
                                    }
                                }
                            }
                            fin.close();
                            ticket t;
                            t.book_ticket();
                            system("CLS");
                            t.print_ticket();
                            ofstream fout("passenger.txt", ios::app);
                            fout.write((char *)&t, sizeof(t));
                            fout.close();
                        }
                        system("PAUSE");
                        break;
                    }
                    case 2:
                    {
                        ifstream fin("passenger.txt");
                        ofstream fout("temp.txt");
                        int temp;
                        ticket t;
                        int fl = 0;
                        cout << "\nEnter PNR:: ";
                        cin >> temp;
                        while (fin.read((char *)&t, sizeof(t)))
                        {
                            if (temp == t.pnr)
                            {
                                fl = 1;
                                t.cancel_ticket();
                                cout << "\n\t\t\tCANCELLATION SUCCESSFULL!" << endl;
                            }
                            else
                            {
                                fout.write((char *)&t, sizeof(t));
                            }
                        }
                        if (fl == 0)
                        {
                            cout << "\nPNR NOT FOUND\n\n";
                        }
                        fout.close();
                        fin.close();
                        remove("passenger.txt");
                        rename("temp.txt", "passenger.txt");
                        system("PAUSE");
                        break;
                    }

                    case 3:
                    {
                        ifstream fin("passenger.txt");
                        int temp = 0;
                        int chk = 0;
                        ticket t;
                        system("CLS");
                        cout << "Enter PNR number: ";
                        cin >> temp;
                        while (fin.read((char *)&t, sizeof(t)))
                        {
                            if (temp == t.pnr)
                            {
                                chk = 1;
                                t.print_ticket();
                            }
                        }
                        fin.close();
                        if (chk==0)
                        {
                            cout << "\nPNR NOT FOUND\n";
                        }
                        
                        system("PAUSE");
                        break;
                    }
                    case 4:
                    {
                        char source[10], destination[10];
                        int d, m, y, fl = 0;
                        vector<int> available_trains;
                        system("CLS");
                        cout << "\nENQUIRY\n\tBoarding point: ";
                        cin >> source;
                        cout << "\tDestination point: ";
                        cin >> destination;
                        enter_date:
                        cout << "\tDate of travel (DD MM YYYY): ";
                        cin >> d >> m >> y;
                        if (check_date(d, m, y) == 0)
                        {
                            cout << endl;
                            goto enter_date;
                        }
                        ifstream fin("trainlist.txt");
                        while (fin.read((char *)&a, sizeof(a)))
                        {
                            if (strcmp(source, a.bp) == 0 && strcmp(destination, a.dest) == 0 && d == a.d && m == a.m && y == a.y)
                            {
                                available_trains.push_back(a.tno);
                                fl++;
                            }
                        }
                        fin.close();
                        if (fl == 0)
                        {
                            cout << "\nNo trains available for above route and selected date!!!\n";
                        }
                        else
                        {
                            system("CLS");
                            fin.open("trainlist.txt");
                            cout << "\n|Train No." << "\t" << "|Train Name" << "\t" << "|Boarding pt." << "\t" << "|Destination pt." << "\t";
                            cout << "|AC-Class" << "\t" << "|AC-Class Fare" << "\t" << "|S-Class" << "\t" << "|S-Class Fare" << "\t";
                            cout << "|Day" << "-" << "Month" << "-" << "Year" << "\n";
                            while (fin.read((char *)&a, sizeof(a)))
                            {
                                for (int i = 0; i < fl; i++)
                                {
                                    if (available_trains[i] == a.tno)
                                    {
                                        a.displayDetail();
                                    }
                                }
                            }
                            fin.close();
                            cout << endl;
                        }
                        system("PAUSE");
                        break;
                    }

                    case 5:
                    {
                        cout << "\n\t\t\t------THANK  YOU!!!------";
                        cout << "\n\t\t\t-------VISIT AGAIN-------\n";
                        main();
                        break;
                    }

                    case 6:
                    {
                        ifstream fin("passenger.txt");
                        ticket t;
                        system("CLS");
                        while (fin.read((char *)&t, sizeof(t)))
                        {
                            t.print_ticket();
                        }
                        fin.close();
                        system("PAUSE");
                        break;
                    }

                    default:
                        {
                            cout << "\nEnter Valid Option\n";
                            break;
                        }
                    }
                }
            }
            else if (flag == 0)
            {
                char temp;
                cout << "\n\t\t\tWRONG CREDENTIALS!";
                cout << "\n\t\t\tPlease Try Again!\n";
                cout << "\n\t\t\tDo you want to continue or register? (Y->continue and N->register)\n:: ";
                cin >> temp;
                if (temp == 'y' || temp == 'Y')
                {
                    goto login;
                }
                if(temp == 'n' || temp =='N')
                {
                    goto regis;
                }
            }
            fin.close();
            system("PAUSE");
            break;
        }

        case 2:
        {
            regis:
            system("CLS");
            ofstream fout("id.txt", ios::app);
            cout<<"REGISTRATION::\n";
            b.getid();
            fout.write((char *)&b, sizeof(b));
            fout.close();
            cout << "\n\t\t\tREGISTRATION SUCCESSFULL\n";
            system("PAUSE");
            break;
        }

        case 3:
        {
            system("CLS");
            print_time();
            cout << "\n\t\t\t\t-------Thank-You!--------\n";
            exit(0);
            break;
        }

        case 4:
        {
            system("CLS");
            char temp[10];
            cout << "\nEnter Admin Password\n:: ";
            cin >> temp;
            if (!strcmp(temp, pwd))
            {
                cout << "\n\t\t\tLOGIN SUCCESSFULL!" << endl;
                system("PAUSE");
                choice = 0;
                while (choice != 4)
                {
                    system("CLS");
                    print_time();
                    cout << "\n\t\t\t     -----ADMIN MENU-----\n\t\t\t     [1].ADD TRAIN\n\t\t\t     [2].DELETE TRAIN\n\t\t\t     [3].TRAIN LIST\n\t\t\t     [4].RETURN TO MAIN MENU\nEnter Your Choice:: ";
                    cin >> choice;
                    switch (choice)
                    {
                    case 1:
                    {
                        system("CLS");
                        ofstream fout("trainlist.txt", ios::app);
                        a.getDetail();
                        fout.write((char *)&a, sizeof(a));
                        fout.close();
                        cout<<"\n\t\t\tTrain Added Successfully!\n";
                        system("PAUSE");
                        break;
                    }

                    case 2:
                    {
                        system("CLS");
                        ifstream fin("trainlist.txt");
                        ofstream fout("temp.txt");
                        int temp;
                        cout << "\nEnter The Train No To Delete:: ";
                        cin >> temp;
                        int flag = 0;
                        while (fin.read((char *)&a, sizeof(a)))
                        {
                            if (a.deleteDetail(temp) == 1)
                            {
                                flag = 1;
                            }
                            else
                            {
                                fout.write((char *)&a, sizeof(a));
                            }
                        }
                        if (flag == 1)
                        {
                            cout << "\n\t\t\tDELETION SUCCESSFULL!\n";
                        }
                        else
                        {
                            cout << "\n\t\t\tDELETION UNSUCCESSFULL!\n";
                        }
                        fin.close();
                        fout.close();
                        remove("trainlist.txt");
                        rename("temp.txt", "trainlist.txt");
                        system("PAUSE");
                        break;
                    }

                    case 3:
                    {
                        ifstream fin("trainlist.txt");
                        system("CLS");
                        cout << "\n|Train No." << "\t" << "|Train Name" << "\t" << "|Boarding pt." << "\t" << "|Destination pt." << "\t";
                        cout << "|F-Class" << "\t" << "|AC-Class Fare" << "\t" << "|S-Class" << "\t" << "|S-Class Fare" << "\t";
                        cout << "|Day" << "-" << "Month" << "-" << "Year" << "\n";
                        while (fin.read((char *)&a, sizeof(a)))
                        {
                            a.displayDetail();
                        }
                        fin.close();
                        system("PAUSE");
                        break;
                    }

                    case 5:
                    {
                        ifstream fin("id.txt");
                        system("CLS");
                        while (fin.read((char *)&b, sizeof(b)))
                        {
                            b.displayid();
                        }
                        fin.close();
                        system("PAUSE");
                        break;
                    }

                    case 4:
                    {
                        system("CLS");
                        cout << "\n\n";
                        main();
                    }

                    default:
                    {
                        cout << "\nEnter Valid Choice!\n";
                        break;
                    }
                    }
                }
            }
            else
                cout << "\nINCORRECT PASSWORD!" << endl;
            break;
        }

        default:
            system("CLS");
            cout << "\nPlease Enter Valid Option!\n";
            system("PAUSE");
            break;
        }
    }

    return 0;
}

// get details of train
void admin::getDetail()
{
    cout << "\n--Add New details--\n";
    cout << "Train no                           : ";
    cin >> tno;
    cout << "Train Name                         : ";
    cin >> tname;
    cout << "Boarding point                     : ";
    cin >> bp;
    cout << "Destination point                  : ";
    cin >> dest;
    cout << "Fare per ticket for AC seats       : ";
    cin >> c1fare;
    cout << "Fare per ticket for sleeper seats  : ";
    cin >> c2fare;
    cout << "Date of travel (DD MM YYYY)        : ";
    cin >> d >> m >> y;
}

void admin::displayDetail()
{
    cout << "|" << tno << "\t\t" << "|" << tname << "\t\t" << "|" << bp << "\t\t" << "|" << dest << "\t\t\t";
    cout << "|" << c1 << "\t\t" << "|" << c1fare << "\t\t" << "|" << c2 << "\t\t" << "|" << c2fare << "\t\t";
    cout << "|" << d << "-" << m << "-" << y << "\n";
}

int check_date(int d, int m, int y)
{
    if (y <= 2021 || y >= 2025)
    {
        cout << "\nTicket cannot be booked for the year " << y << "!!!\n";
        return 0;
    }
    else if ((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) && (d < 1 || d > 31))
    {
        cout << "\nInvalid date!!!\n";
        return 0;
    }
    else if ((m == 2) && (d < 1 || d > 28) && y != 2024)
    {
        cout << "\nInvalid date!!!\n";
        return 0;
    }
    else if (m < 1 || m > 12)
    {
        cout << "\nInvalid month!!!\n";
        return 0;
    }
    else if ((m == 4 || m == 6 || m == 9 || m == 11) && (d < 1 || d > 30))
    {
        cout << "\nInvalid date!!!\n";
        return 0;
    }
    else
    {
        return 1;
    }
    return 1;
}
