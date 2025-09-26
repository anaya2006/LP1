#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Pro {
    int id;
    bool act;
    Pro(int id) {
        this->id = id;
        act = true;
    }
};

class Bully {
public:
    int TotalProcess;
    vector<Pro> process;
    int coordinator;  // current coordinator ID

    Bully() { srand(time(0)); } // seed randomness

    void initialiseBully() {
        cout << "Enter no of processes: ";
        cin >> TotalProcess;

        process.reserve(TotalProcess);

        for (int i = 0; i < TotalProcess; i++) {
            process.emplace_back(i);
        }

        // Coordinator is highest process ID initially
        coordinator = TotalProcess - 1;
        cout << "Initial coordinator assigned: Process " << coordinator << "\n";
    }

    void randomFailures() {
        // You can keep this if you want other random failures,
        // but as per current logic, failure is simulated only on coordinator on request
        for (int i = 0; i < TotalProcess; i++) {
            if (process[i].act && rand() % 10 == 0) {
                process[i].act = false;
                cout << ">>> Process " << i << " randomly FAILED!\n";
            } else if (!process[i].act && rand() % 90 == 0) {
                process[i].act = true;
                cout << ">>> Process " << i << " RECOVERED!\n";
            }
        }
    }

    int FetchMaximum() {
        int Ind = -1, maxId = -1;
        for (int i = 0; i < process.size(); i++) {
            if (process[i].act && process[i].id > maxId) {
                maxId = process[i].id;
                Ind = i;
            }
        }
        return Ind;
    }

    void Election(int starter) {
        cout << "Process " << coordinator << " (current coordinator) failed.\n";

        // coordinator already marked inactive in requestCoordinator

        cout << "Process " << starter << " initiates ELECTION.\n";

        for (int i = starter + 1; i < TotalProcess; i++) {
            if (process[i].act) {
                cout << "Process " << starter << " sends ELECTION message to " << i << endl;
            }
        }

        coordinator = FetchMaximum();

        if (coordinator == -1) {
            cout << "No active process available to become coordinator.\n";
        } else {
            cout << "Process " << coordinator << " becomes the new COORDINATOR.\n";

            for (int i = 0; i < TotalProcess; i++) {
                if (i != coordinator && process[i].act) {
                    cout << "Coordinator message sent from " << coordinator << " to " << i << endl;
                }
            }
        }
        cout << "---- End of Election ----\n";
    }

    void requestCoordinator() {
        if (coordinator == -1) {
            cout << "No active coordinator found.\n";
            return;
        }

        int requester;
        cout << "Enter process to request service from coordinator: ";
        cin >> requester;

        if (requester < 0 || requester >= TotalProcess) {
            cout << "Invalid process ID.\n";
            return;
        }
        if (!process[requester].act) {
            cout << "Process " << requester << " is currently inactive and cannot request.\n";
            return;
        }

        // Simulate random failure of the coordinator at request time (20% chance failure)
        bool coordActiveNow = (rand() % 10 < 8); // 0-7 active, 8-9 fail

        if (!coordActiveNow) {
            cout << "Coordinator " << coordinator << " did NOT respond. Failure detected!\n";

            // Mark coordinator as failed
            process[coordinator].act = false;

            // Start election by requester
            Election(requester);
        } else {
            cout << "Coordinator " << coordinator << " successfully responded to Process " << requester << ".\n";
        }
    }
};

int main() {
    Bully obj;
    obj.initialiseBully();

    char choice = 'y';
    while (choice == 'y' || choice == 'Y') {
        obj.requestCoordinator();
        cout << "Do you want another request? (y/n): ";
        cin >> choice;
    }

    return 0;
}




