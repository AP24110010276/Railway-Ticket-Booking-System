#include <iostream>

#include <string>

#include <limits>

using namespace std;



class TrainClass {

protected:

    string className;

    int totalSeats;

    int bookedSeats;

public:

    TrainClass(string name, int seats) : className(name), totalSeats(seats), bookedSeats(0) {}

    virtual void display() {

        cout << className << " Class - Total Seats: " << totalSeats

             << ", Available: " << totalSeats - bookedSeats << endl;

    }

    bool bookSeat() {

        if (bookedSeats < totalSeats) {

            bookedSeats++;

            return true;

        }

        return false;

    }

    bool cancelSeat() {

        if (bookedSeats > 0) {

            bookedSeats--;

            return true;

        }

        return false;

    }

};



class Sleeper : public TrainClass {

public:

    Sleeper(int seats) : TrainClass("Sleeper", seats) {}

};

class AC : public TrainClass {

public:

    AC(int seats) : TrainClass("AC", seats) {}

};

class General : public TrainClass {

public:

    General(int seats) : TrainClass("General", seats) {}

};



class Passenger {

public:

    string name;

    int age;

    string bookedClass;

    string boardingPoint;

    string droppingPoint;



    Passenger() : name(""), age(0), bookedClass(""), boardingPoint(""), droppingPoint("") {}

    Passenger(string n, int a, string bc, string bp, string dp)

        : name(n), age(a), bookedClass(bc), boardingPoint(bp), droppingPoint(dp) {}



    void display() {

        cout << "Name: " << name << ", Age: " << age

             << ", Class: " << bookedClass

             << ", Boarding: " << boardingPoint

             << ", Dropping: " << droppingPoint << endl;

    }

};



class RailwaySystem {

    Passenger passengers[100];

    int passengerCount;

    Sleeper sleeper;

    AC ac;

    General general;



public:

    RailwaySystem() : sleeper(5), ac(3), general(10), passengerCount(0) {}



    void bookTicket() {

        if (passengerCount >= 100) {

            cout << "Passenger limit reached!\n";

            return;

        }



        string name, classType, boarding, dropping;

        int age;



        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter name: ";

        getline(cin, name);

        cout << "Enter age: ";

        cin >> age;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter class (Sleeper/AC/General): ";

        getline(cin, classType);

        cout << "Enter boarding point: ";

        getline(cin, boarding);

        cout << "Enter dropping point: ";

        getline(cin, dropping);



        bool success = false;

        if (classType == "Sleeper") success = sleeper.bookSeat();

        else if (classType == "AC") success = ac.bookSeat();

        else if (classType == "General") success = general.bookSeat();



        if (success) {

            passengers[passengerCount++] = Passenger(name, age, classType, boarding, dropping);

            cout << "Ticket booked successfully!\n";

        } else {

            cout << "No seats available in this class!\n";

        }

    }



    void cancelTicket() {

        string name;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter passenger name to cancel: ";

        getline(cin, name);



        bool found = false;

        for (int i = 0; i < passengerCount; i++) {

            if (passengers[i].name == name) {

                string c = passengers[i].bookedClass;

                if (c == "Sleeper") sleeper.cancelSeat();

                else if (c == "AC") ac.cancelSeat();

                else if (c == "General") general.cancelSeat();



                for (int j = i; j < passengerCount - 1; j++) passengers[j] = passengers[j + 1];

                passengerCount--;

                cout << "Ticket cancelled successfully!\n";

                found = true;

                break;

            }

        }

        if (!found) cout << "Passenger not found!\n";

    }



    void checkAvailability() {

        sleeper.display();

        ac.display();

        general.display();

    }



    void viewHistory() {

        if (passengerCount == 0) {

            cout << "No bookings yet!\n";

            return;

        }

        for (int i = 0; i < passengerCount; i++) passengers[i].display();

    }



    void menu() {

        int choice;

        do {

            cout << "\n--- Railway Ticket Booking ---\n";

            cout << "1. Book Ticket\n2. Cancel Ticket\n3. Check Seat Availability\n";

            cout << "4. View Booking History\n5. Exit\nChoose: ";

            cin >> choice;

            switch (choice) {

            case 1: bookTicket(); break;

            case 2: cancelTicket(); break;

            case 3: checkAvailability(); break;

            case 4: viewHistory(); break;

            case 5: cout << "Exiting...\n"; break;

            default: cout << "Invalid choice!\n";

            }

        } while (choice != 5);

    }

};



int main() {

    RailwaySystem system;

    system.menu();

    return 0;

}