#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;

struct Pro {
    int id;
    bool act;
    Pro(int id) {
        this->id = id;
        act = true;
    }
};

class ring {
public:
    int TotalProcess;
    vector<Pro> process;
    vector<int> message;

    ring() {}
    
    void initialisering() {
        cout << "Enter number of processes: ";
        cin >> TotalProcess;
        
        // Validate input
        if (TotalProcess <= 0) {
            cout << "Invalid number of processes. Setting to 1." << endl;
            TotalProcess = 1;
        }
        
        process.reserve(TotalProcess);
        for (int i = 0; i < TotalProcess; i++) {
            process.emplace_back(i);
        }
        cout << "Initialized " << TotalProcess << " processes (IDs 0 to " << TotalProcess-1 << ")" << endl;
    }

    void Election() {
        int initializedProcess;
        cout << "Enter initiator process ID (0 to " << TotalProcess-1 << "): ";
        cin >> initializedProcess;
        
        // Validate initiator process
        if (initializedProcess < 0 || initializedProcess >= TotalProcess) {
            cout << "Invalid initiator ID. Choosing process 0 as initiator." << endl;
            initializedProcess = 0;
        }

        cout << "Process no " << process[FetchMaximum()].id << " fails" << endl;
        process[FetchMaximum()].act = false; // Fixed: Set process as inactive
        message.clear(); // Clear message array
        
        cout << "Election Initiated by process " << initializedProcess << endl;

        int old = initializedProcess;
        int newer = (old + 1) % TotalProcess;

        // Add initiator's PID to message array
        message.push_back(process[old].id);
        cout << "Message array: ";
        for (int pid : message) cout << pid << " ";
        cout << endl;

        while (true) {
            if (process[newer].act) {
                cout << "Process " << process[old].id << " pass Election(" << process[old].id << ") to " << process[newer].id << endl;
                message.push_back(process[newer].id);
                cout << "Message array: ";
                for (int pid : message) cout << pid << " ";
                cout << endl;
                this_thread::sleep_for(chrono::seconds(2));
                old = newer;
            }

            newer = (newer + 1) % TotalProcess;
            if (newer == initializedProcess) {
                break;
            }
        }

        cout << "Process " << process[FetchMaximum()].id << " becomes coordinator" << endl;
        int coord = process[FetchMaximum()].id;

        old = coord;
        newer = (old + 1) % TotalProcess;

        while (true) {
            if (process[newer].act) {
                cout << "Process " << process[old].id << " pass Coordinator(" << coord << ") message to process " << process[newer].id << endl;
                old = newer;
                this_thread::sleep_for(chrono::seconds(2));
            }
            newer = (newer + 1) % TotalProcess;
            if (newer == coord) {
                cout << "End Of Election " << endl;
                break;
            }
        }
    }

    int FetchMaximum() {
        int Ind = 0;
        int maxId = -9999;
        for (int i = 0; i < process.size(); i++) {
            if (process[i].act && process[i].id > maxId) {
                maxId = process[i].id;
                Ind = i;
            }
        }
        return Ind;
    }
};

int main() {
    ring object;
    object.initialisering();
    object.Election();
    return 0;
}
