// Author: German Savchenko
// 
// Vaccine Scheduling project
//
// Objective: design and develop an optimal online algorithm for scheduling patients using as little hospitals as possible 
// (machine minimization problem)

#include <iostream>
#include <iomanip>
#include <fstream>
#include <bitset>
#include <limits>
#include <typeinfo>
#include <vector>
#include <string>


using namespace std;

const uint8_t inputEntries = 4;
const string fileName = "../txt/20-2.txt";

const uint32_t MACHINES = 40;
const uint32_t SLOTS = 90;

uint32_t nMachines = 0;
uint32_t nEntries = 0;

int centralBuffer[MACHINES][SLOTS];

void initBuffer() {
	for (int i = 0; i < MACHINES; i++) {
		for (int j = 0; j < SLOTS; j++) {
			centralBuffer[i][j] = 0;
		}
	}
}

struct initArr {
	int p1;
	int p2;
	int gap;
};


void updateCentralBuffer(uint32_t t, uint32_t procTime, uint32_t machine) { //register scheduled jabs
	for (int i = t; i < t + procTime; i++) {
		centralBuffer[machine][i] = procTime;
	}
}

void printCentralBuffer() {
	for (int i = 0; i < MACHINES; i++) {
		for (int j = 0; j < SLOTS; j++) {
			cout << (int)centralBuffer[i][j];
		}
		cout << "\n";
	}
	cout << "\n\n\n";
}

void printCentralBuffferToFile() {
	ofstream myfile("txt/printed.txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < MACHINES; i++) {
			for (int j = 0; j < SLOTS; j++) {
				myfile << (int)centralBuffer[i][j];
			}
			myfile << "\n";
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}

void printArray(auto in) {
	for (auto i : in) { //C++11
		cout << i << " ";
	}
	cout << "\n";
}

void assignCurrent(array<int, inputEntries> input, initArr init) {
	const uint32_t t1_1 = input[0];
	const uint32_t t1_2 = input[1];
	const uint32_t delay = input[2];
	const uint32_t lengthInterval2 = input[3];
	const uint32_t firstJab = 0;
	const uint32_t secondJab = 2;
	int8_t selectedMachine = -1;

	printCentralBuffer();

	if (nEntries == 0) {
		updateCentralBuffer(t1_1, init.p1, 0); //register first jab leftmost spot
		updateCentralBuffer(t1_1 + init.p1 + delay + init.gap, init.p2, 0); //register second jab leftmost spot
		nEntries++;
		//TODO: RECORD ENTRY

	}
	else {
		bool found = false;
		int32_t foundEmpty[2] = { -1, -1 }; //if < 0 --> not found | {timeSlot, machine}
		bool foundEmptyTrig = false;

		uint32_t t2_1, t2_2;

		//iterate through feasible timeslot
		//if you find snapping - snap
		//if no snapping, place most left
		//if no available spots, new machine

		cout << "processing.. " << nEntries << "\t t1_1: " << t1_1 << "\t delay: " << delay << endl;

		if (t1_2 > SLOTS) { cout << "out of bounds for second jab" << endl; exit(0); }

		//FIRST JAB

		for (uint32_t i = 0; i <= nMachines; i++) { //iterate through each machine
			for (uint32_t j = t1_1; j <= t1_2; j++) { //check in the feasible slot of each machine
				if (centralBuffer[i][j] >= 1) { continue; }
				if (j < t1_2 - init.p1) {
					for (uint8_t z = 0; z < init.p1 + 1; z++) {
						if ((centralBuffer[i][j + z] >= 1 && z < init.p1)) {
							break;
							//                            if (foundEmptyTrig == false) foundEmptyTrig = false;
						}
						if (z == init.p2 - 1) {
							foundEmptyTrig = true;
							foundEmpty[0] = j; foundEmpty[1] = i;
						}
						if (centralBuffer[i][j + z + 1] < 1 && z + 1 == init.p1) { found = false; break; }
						found = true;
					}
				}
				if (found) { updateCentralBuffer(j, init.p1, i); t2_1 = j + init.p1 + delay + init.gap; break; }
			}
			if (found) break;
		}
		if (!found) {

			if (foundEmptyTrig) {
				updateCentralBuffer(foundEmpty[0], init.p1, foundEmpty[1]);
				t2_1 = foundEmpty[0] + init.p1 + delay + init.gap;
			}

			else {
				nMachines++; updateCentralBuffer(t1_1, init.p1, nMachines);
				t2_1 = t1_1 + init.p1 + delay + init.gap;
			}
		}

		found = false;
		foundEmpty[0] = -1; foundEmpty[1] = -1; //if < 0 --> not found | {timeSlot, machine}
		foundEmptyTrig = false;



		//SECOND JAB
		t2_2 = t2_1 + lengthInterval2;
		if (t2_2 > SLOTS) { cout << "out of bounds for second jab" << endl; exit(0); }

		for (uint32_t i = 0; i <= nMachines; i++) { //iterate through each machine
			for (uint32_t j = t2_1; j <= t2_2; j++) { //check in the feasible slot of each machine
				if (centralBuffer[i][j] >= 1) continue;
				if (j < t2_2 - init.p2) {
					for (uint8_t z = 0; z < init.p2 + 1; z++) {
						if ((centralBuffer[i][j + z] >= 1 && z < init.p2)) {
							//                            if (foundEmptyTrig == false) foundEmptyTrig = false;
							break;
						}
						if (z == init.p2 - 1) {
							foundEmptyTrig = true;
							foundEmpty[0] = j; foundEmpty[1] = i;
						}
						if (centralBuffer[i][j + z + 1] < 1 && z + 1 == init.p2) { found = false; break; }
						found = true;
					}
				}

				if (found) { updateCentralBuffer(j, init.p2, i); break; }
			}
			if (found) break;
		}
		if (!found) {
			if (foundEmptyTrig) { updateCentralBuffer(foundEmpty[0], init.p2, foundEmpty[1]); }
			else { nMachines++; updateCentralBuffer(t2_1, init.p2, nMachines); }
		}
	}
	nEntries++;
}


array<int, inputEntries> stringParser(string s_)
{
	string text = s_;
	string delim = ", ";
	vector<string> numbers{};
	array<int, inputEntries> out;
	size_t pos = 0;

	while ((pos = text.find(delim)) != string::npos) {
		numbers.push_back(text.substr(0, pos));
		text.erase(0, pos + delim.length());
	}

	numbers.push_back(text); //push last element

	for (int i = 0; i < numbers.size(); i++) {
		out[i] = stoi(numbers.at(i));
	}
	return out;
}


initArr readFile(string inputFileLocation) {
	initArr a;
	ifstream inFile;
	uint8_t i = 0;

	inFile.open(inputFileLocation);
	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}
	inFile >> a.p1;
	inFile >> a.p2;
	inFile >> a.gap;

	inFile.close();
	return a;
}


initArr readFile(string inputFileLocation, initArr init) {
	ifstream inFile;
	uint8_t i = 0;
	inFile.open(inputFileLocation);

	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}

	array<int, inputEntries> tmp;
	string s;

	while (getline(inFile, s)) { //filter ','
		if (i < 3) {
			i++;
			continue;
		}
		if (s != "x")assignCurrent(stringParser(s), init);
		else { inFile.close(); return init; }
	}

	inFile.close();
	return init;
}

int main()
{
	initBuffer();
	initArr init = readFile(fileName);
	cout << "inits have been loaded\n";
	readFile(fileName, init);
	cout << "processing complete\n\n";
	printCentralBuffferToFile();
	cout << "machines used: " << nMachines + 1 << endl;
	return 0;
}

