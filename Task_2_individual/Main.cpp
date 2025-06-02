#include "Fun.h"

int main() {
    Factory factory;
    int choice;
    string id, value;

    while (true) {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            cout << "Enter ID: ";
            getline(cin, id);
            cout << "Enter string value: ";
            getline(cin, value);
            factory.createSymbString(id, value);
            break;
        }
        case 2: {
            cout << "Enter ID: ";
            getline(cin, id);
            cout << "Enter binary value (0s and 1s): ";
            getline(cin, value);
            factory.createBinString(id, value);
            break;
        }
        case 3: {
            cout << "Enter ID of object to delete: ";
            getline(cin, id);
            factory.deleteObject(id);
            break;
        }
        case 4: {
            cout << "Enter ID of object to show: ";
            getline(cin, id);
            factory.showObjectById(id);
            break;
        }
        case 5: {
            factory.clear();
            cout << "Exiting program..." << endl;
            return 0;
        }
        default: {
            cout << "Invalid choice. Try again." << endl;
            break;
        }
        }
    }

    return 0;
}