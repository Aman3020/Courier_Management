#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm> 
using namespace std;

class Courier {
private:
    string tracking_id;
    string sender_name;
    string receiver_name;
    string sender_address;
    string receiver_address;

public:
    Courier() {}

    void input() {
        cout << "Enter Tracking ID: ";
        cin >> tracking_id;
        cin.ignore();
        cout << "Enter Sender Name: ";
        getline(cin, sender_name);
        cout << "Enter Receiver Name: ";
        getline(cin, receiver_name);
        cout << "Enter Sender Address: ";
        getline(cin, sender_address);
        cout << "Enter Receiver Address: ";
        getline(cin, receiver_address);
    }

    void display() const {
        cout << tracking_id << "\t" << sender_name << "\t" << receiver_name
             << "\t" << sender_address << "\t" << receiver_address << endl;
    }

    string getTrackingID() const {
        return tracking_id;
    }

    string toCSV() const {
        return tracking_id + "," + sender_name + "," + receiver_name + "," + sender_address + "," + receiver_address;
    }

    void updateDetails() {
        cout << "Updating Courier - " << tracking_id << endl;
        cout << "Enter New Sender Name: ";
        getline(cin, sender_name);
        cout << "Enter New Receiver Name: ";
        getline(cin, receiver_name);
        cout << "Enter New Sender Address: ";
        getline(cin, sender_address);
        cout << "Enter New Receiver Address: ";
        getline(cin, receiver_address);
    }
};

class CourierManager {
private:
    const string filename = "courier.txt";

public:
    void insertCourier() {
        Courier courier;
        courier.input();

        ofstream file(filename, ios::app);
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }
        file << courier.toCSV() << endl;
        file.close();
        cout << "Courier Added Successfully!" << endl;
    }

    void displayCouriers() {
        ifstream file(filename);
        if (!file) {
            cout << "No records found." << endl;
            return;
        }

        string line;
        cout << "TrackingID\tSender\tReceiver\tSenderAddress\tReceiverAddress" << endl;
        cout << "-----------------------------------------------------------------" << endl;

        while (getline(file, line)) {
            replace(line.begin(), line.end(), ',', '\t');
            cout << line << endl;
        }

        file.close();
    }

    void searchCourier() {
        string search_id;
        cout << "Enter Tracking ID to Search: ";
        cin >> search_id;

        ifstream file(filename);
        if (!file) {
            cout << "File Error." << endl;
            return;
        }

        string tid, sname, rname, saddr, raddr;
        bool found = false;

        while (getline(file, tid, ',') &&
               getline(file, sname, ',') &&
               getline(file, rname, ',') &&
               getline(file, saddr, ',') &&
               getline(file, raddr)) {

            if (tid == search_id) {
                cout << "Courier Found:\n";
                cout << tid << "\t" << sname << "\t" << rname << "\t" << saddr << "\t" << raddr << endl;
                found = true;
                break;
            }
        }

        if (!found)
            cout << "Courier Not Found." << endl;

        file.close();
    }

    void deleteCourier() {
        string search_id;
        cout << "Enter Tracking ID to Delete: ";
        cin >> search_id;

        ifstream file(filename);
        ofstream temp("temp.txt");

        if (!file || !temp) {
            cout << "File Error." << endl;
            return;
        }

        string tid, sname, rname, saddr, raddr;
        bool found = false;

        while (getline(file, tid, ',') &&
               getline(file, sname, ',') &&
               getline(file, rname, ',') &&
               getline(file, saddr, ',') &&
               getline(file, raddr)) {

            if (tid == search_id) {
                found = true;
            } else {
                temp << tid << "," << sname << "," << rname << "," << saddr << "," << raddr << endl;
            }
        }

        file.close();
        temp.close();

        remove(filename.c_str());
        rename("temp.txt", filename.c_str());

        if (found)
            cout << "Courier Deleted Successfully." << endl;
        else
            cout << "Courier Not Found." << endl;
    }

    void updateCourier() {
        string search_id;
        cout << "Enter Tracking ID to Update: ";
        cin >> search_id;
        cin.ignore();

        ifstream file(filename);
        ofstream temp("temp.txt");

        if (!file || !temp) {
            cout << "File Error." << endl;
            return;
        }

        string tid, sname, rname, saddr, raddr;
        bool found = false;

        while (getline(file, tid, ',') &&
               getline(file, sname, ',') &&
               getline(file, rname, ',') &&
               getline(file, saddr, ',') &&
               getline(file, raddr)) {

            if (tid == search_id) {
                Courier courier;
                courier = Courier();
                courier.input();
                temp << courier.toCSV() << endl;
                found = true;
            } else {
                temp << tid << "," << sname << "," << rname << "," << saddr << "," << raddr << endl;
            }
        }

        file.close();
        temp.close();

        remove(filename.c_str());
        rename("temp.txt", filename.c_str());

        if (found)
            cout << "Courier Updated Successfully." << endl;
        else
            cout << "Courier Not Found." << endl;
    }
};

int main() {
    CourierManager manager;
    int choice;

    do {
        cout << "\n******** Courier Management System ********\n";
        cout << "1. Insert Courier\n";
        cout << "2. Display Couriers\n";
        cout << "3. Search Courier\n";
        cout << "4. Delete Courier\n";
        cout << "5. Update Courier\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: 
                manager.insertCourier(); 
                break;
            case 2: 
                manager.displayCouriers(); 
                break;
            case 3: 
                manager.searchCourier(); 
                break;
            case 4: 
                manager.deleteCourier(); 
                break;
            case 5: 
                manager.updateCourier(); 
                break;
            case 6: 
                cout << "Thank You. Exiting Program." << endl; break;
            default: 
                cout << "Invalid Choice. Please select 1-6." << endl;
        }

    } while (choice != 6);

    return 0;
}
