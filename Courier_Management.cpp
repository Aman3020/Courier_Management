#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <ctime>
using namespace std;

class Courier {
private:
    string tracking_id;
    string sender_name;
    string receiver_name;
    string sender_address;
    string receiver_address;
    string status; // Pending / In Transit / Delivered

    bool isValidAddress(const string& addr) {
        return !addr.empty() && addr.length() > 3 && addr.find(',') == string::npos;
    }

public:
    Courier() {}

    void input(const vector<string>& existingIDs = {}) {
        do {
            cout << "Enter Tracking ID: ";
            cin >> tracking_id;
            cin.ignore();
            if (tracking_id.empty() || find(existingIDs.begin(), existingIDs.end(), tracking_id) != existingIDs.end()) {
                cout << "Invalid or duplicate Tracking ID. Try again.\n";
                tracking_id.clear();
            }
        } while (tracking_id.empty());

        do {
            cout << "Enter Sender Name: ";
            getline(cin, sender_name);
            if (sender_name.empty()) cout << "Sender Name cannot be empty.\n";
        } while (sender_name.empty());

        do {
            cout << "Enter Receiver Name: ";
            getline(cin, receiver_name);
            if (receiver_name.empty()) cout << "Receiver Name cannot be empty.\n";
        } while (receiver_name.empty());

        do {
            cout << "Enter Sender Address: ";
            getline(cin, sender_address);
            if (!isValidAddress(sender_address)) cout << "Invalid address. Try again.\n";
        } while (!isValidAddress(sender_address));

        do {
            cout << "Enter Receiver Address: ";
            getline(cin, receiver_address);
            if (!isValidAddress(receiver_address)) cout << "Invalid address. Try again.\n";
        } while (!isValidAddress(receiver_address));

        do {
            cout << "Enter Status (Pending/In Transit/Delivered): ";
            getline(cin, status);
            if (status != "Pending" && status != "In Transit" && status != "Delivered")
                cout << "Invalid status. Try again.\n";
        } while (status != "Pending" && status != "In Transit" && status != "Delivered");
    }

    void display() const {
        cout << tracking_id << "\t" << sender_name << "\t" << receiver_name
             << "\t" << sender_address << "\t" << receiver_address << "\t" << status << endl;
    }

    string getTrackingID() const { return tracking_id; }
    string getStatus() const { return status; }

    string toCSV() const {
        return tracking_id + "," + sender_name + "," + receiver_name + "," + sender_address + "," + receiver_address + "," + status;
    }

    void updateDetails() {
        cout << "Updating Courier - " << tracking_id << endl;
        do {
            cout << "Enter New Sender Name: ";
            getline(cin, sender_name);
            if (sender_name.empty()) cout << "Sender Name cannot be empty.\n";
        } while (sender_name.empty());

        do {
            cout << "Enter New Receiver Name: ";
            getline(cin, receiver_name);
            if (receiver_name.empty()) cout << "Receiver Name cannot be empty.\n";
        } while (receiver_name.empty());

        do {
            cout << "Enter New Sender Address: ";
            getline(cin, sender_address);
            if (!isValidAddress(sender_address)) cout << "Invalid address. Try again.\n";
        } while (!isValidAddress(sender_address));

        do {
            cout << "Enter New Receiver Address: ";
            getline(cin, receiver_address);
            if (!isValidAddress(receiver_address)) cout << "Invalid address. Try again.\n";
        } while (!isValidAddress(receiver_address));

        do {
            cout << "Enter New Status (Pending/In Transit/Delivered): ";
            getline(cin, status);
            if (status != "Pending" && status != "In Transit" && status != "Delivered")
                cout << "Invalid status. Try again.\n";
        } while (status != "Pending" && status != "In Transit" && status != "Delivered");
    }

    // Static helper to parse from CSV
    static Courier fromCSV(const string& line) {
        Courier c;
        size_t pos = 0, prev = 0;
        vector<string> fields;
        while ((pos = line.find(',', prev)) != string::npos) {
            fields.push_back(line.substr(prev, pos - prev));
            prev = pos + 1;
        }
        fields.push_back(line.substr(prev));
        if (fields.size() == 6) {
            c.tracking_id = fields[0];
            c.sender_name = fields[1];
            c.receiver_name = fields[2];
            c.sender_address = fields[3];
            c.receiver_address = fields[4];
            c.status = fields[5];
        }
        return c;
    }
};

class CourierFileHandler {
    string filename;
public:
    CourierFileHandler(const string& fname) : filename(fname) {}

    vector<Courier> readAll() {
        vector<Courier> couriers;
        ifstream file(filename);
        if (!file) throw runtime_error("File open error");
        string line;
        while (getline(file, line)) {
            Courier c = Courier::fromCSV(line);
            if (!c.getTrackingID().empty())
                couriers.push_back(c);
        }
        return couriers;
    }

    void writeAll(const vector<Courier>& couriers) {
        ofstream file(filename);
        if (!file) throw runtime_error("File write error");
        for (const auto& c : couriers)
            file << c.toCSV() << endl;
    }

    void append(const Courier& c) {
        ofstream file(filename, ios::app);
        if (!file) throw runtime_error("File append error");
        file << c.toCSV() << endl;
    }
};

class CourierManager {
private:
    const string filename = "courier.txt";
    CourierFileHandler fileHandler;

public:
    CourierManager() : fileHandler(filename) {}

    void insertCourier() {
        try {
            vector<Courier> couriers = fileHandler.readAll();
            vector<string> ids;
            for (const auto& c : couriers) ids.push_back(c.getTrackingID());
            Courier courier;
            courier.input(ids);
            fileHandler.append(courier);
            cout << "Courier Added Successfully!" << endl;
        } catch (exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void displayCouriers() {
        try {
            vector<Courier> couriers = fileHandler.readAll();
            if (couriers.empty()) {
                cout << "No records found." << endl;
                return;
            }
            cout << "TrackingID\tSender\tReceiver\tSenderAddress\tReceiverAddress\tStatus" << endl;
            cout << "--------------------------------------------------------------------------" << endl;
            for (const auto& c : couriers)
                c.display();
        } catch (exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void filterByStatus() {
        try {
            vector<Courier> couriers = fileHandler.readAll();
            string status;
            cout << "Enter status to filter (Pending/In Transit/Delivered): ";
            getline(cin, status);
            cout << "TrackingID\tSender\tReceiver\tSenderAddress\tReceiverAddress\tStatus" << endl;
            cout << "--------------------------------------------------------------------------" << endl;
            for (const auto& c : couriers)
                if (c.getStatus() == status)
                    c.display();
        } catch (exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void searchCourier() {
        try {
            vector<Courier> couriers = fileHandler.readAll();
            string search_id;
            cout << "Enter Tracking ID to Search: ";
            cin >> search_id;
            cin.ignore();
            bool found = false;
            for (const auto& c : couriers) {
                if (c.getTrackingID() == search_id) {
                    cout << "Courier Found:\n";
                    c.display();
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Courier Not Found." << endl;
        } catch (exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void deleteCourier() {
        try {
            vector<Courier> couriers = fileHandler.readAll();
            string search_id;
            cout << "Enter Tracking ID to Delete: ";
            cin >> search_id;
            cin.ignore();
            bool found = false;
            vector<Courier> updated;
            for (const auto& c : couriers) {
                if (c.getTrackingID() == search_id) {
                    found = true;
                } else {
                    updated.push_back(c);
                }
            }
            if (found) {
                fileHandler.writeAll(updated);
                cout << "Courier Deleted Successfully." << endl;
            } else {
                cout << "Courier Not Found." << endl;
            }
        } catch (exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void updateCourier() {
        try {
            vector<Courier> couriers = fileHandler.readAll();
            string search_id;
            cout << "Enter Tracking ID to Update: ";
            cin >> search_id;
            cin.ignore();
            bool found = false;
            for (auto& c : couriers) {
                if (c.getTrackingID() == search_id) {
                    c.updateDetails();
                    found = true;
                    break;
                }
            }
            if (found) {
                fileHandler.writeAll(couriers);
                cout << "Courier Updated Successfully." << endl;
            } else {
                cout << "Courier Not Found." << endl;
            }
        } catch (exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
};

// Authentication function
bool authenticate() {
    string user, pass;
    const string USERNAME = "admin";
    const string PASSWORD = "password";
    cout << "Admin Login\nUsername: ";
    getline(cin, user);
    cout << "Password: ";
    getline(cin, pass);
    return (user == USERNAME && pass == PASSWORD);
}

int main() {
    if (!authenticate()) {
        cout << "Authentication failed. Exiting.\n";
        return 1;
    }
    CourierManager manager;
    int choice;
    do {
        cout << "\n******** Courier Management System ********\n";
        cout << "1. Insert Courier\n";
        cout << "2. Display Couriers\n";
        cout << "3. Search Courier\n";
        cout << "4. Delete Courier\n";
        cout << "5. Update Courier\n";
        cout << "6. Filter by Status\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: manager.insertCourier(); break;
            case 2: manager.displayCouriers(); break;
            case 3: manager.searchCourier(); break;
            case 4: manager.deleteCourier(); break;
            case 5: manager.updateCourier(); break;
            case 6: manager.filterByStatus(); break;
            case 7: cout << "Thank You. Exiting Program." << endl; break;
            default: cout << "Invalid Choice. Please select 1-7." << endl;
        }
    } while (choice != 7);
    return 0;
}

