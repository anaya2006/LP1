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

Bully() { srand(time(0)); } // seed randomness

void initialiseBully() {

cout << "Enter no of processes: ";

cin >> TotalProcess;

process.reserve(TotalProcess);

for (int i = 0; i < TotalProcess; i++) {

process.emplace_back(i);

}

}

 

// simulate random failure/recovery of processes

void randomFailures() {

for (int i = 0; i < TotalProcess; i++) {

if (process[i].act && rand() % 30 == 0) {

process[i].act = false;

cout << ">>> Process " << i << " randomly FAILED!\n";

} else if (!process[i].act && rand() % 50 == 0) {

process[i].act = true;

cout << ">>> Process " << i << " RECOVERED!\n";

}

}

}

int FetchMaximum() {

int Ind = -1, maxId = -9999;

for (int i = 0; i < process.size(); i++) {

if (process[i].act && process[i].id > maxId) {

maxId = process[i].id;

Ind = i;

}

}

return Ind;

}

void Election(int starter) {

cout << "Process " << FetchMaximum() << " (current coordinator) failed.\n";

process[FetchMaximum()].act = false;

cout << "Process " << starter << " initiates ELECTION.\n";

for (int i = starter + 1; i < TotalProcess; i++) {

 

if (process[i].act) {

cout << "Process " << starter << " sends ELECTION message to " << i << endl;

}

}

int coord = FetchMaximum();

cout << "Process " << coord << " becomes the new COORDINATOR.\n";

for (int i = 0; i < TotalProcess; i++) {

if (i != coord && process[i].act) {

cout << "Coordinator message sent from " << coord << " to " << i << endl;

}

}

cout << "---- End of Election ----\n";

}

void requestCoordinator() {

int coord = FetchMaximum();

if (coord == -1) {

cout << "No active process left!\n";

return;

}

cout << "Enter process to request service from coordinator: ";

int requester;

cin >> requester;

randomFailures(); // simulate random failures/recoveries before request

if (!process[coord].act) {

cout << "Coordinator " << coord << " did NOT respond. Failure detected!\n";

Election(requester);

 

} else {

cout << "Coordinator " << coord << " successfully responded to Process " << requester <<

".\n";

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

 



