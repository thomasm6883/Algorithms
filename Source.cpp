/*
Matthew Thomas & Carter Wente
Cha: Isomporhic Detector
4/3/2022
CS-254

Time Estimate: 4.5 hours

Input from inputIso.txt & inputIso2.txt in the same file location as project
inputIso.txt includes graphs which requires circuit analysis
*/

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

vector<vector<int>> list1;
vector<vector<int>> list2;
string s;
int row = 0;
bool second = false;
bool vectEqual = false;

//reads two adjacency matrices from a file
void readFiles() {
	//open file and begin process
	ifstream myfile;
	myfile.open("inputIso3.txt");
	if (!myfile.is_open()) {
		cout << "Bad file, could not open..." << endl;
	}
	cout << "Begin Reading File" << endl;
	//get line until the end of the file
	while (getline(myfile, s)) {
		if (!second) {//depicting the first or second list
			cout << s << endl;
			if (s.empty()) {//check for the blank line seperating the lists
				second = true;
				row = 0;
			}
			else {//push back the row and then its elements
				list1.push_back(vector<int>());
				for (int i = 0; i < s.length(); i++) {
					list1[row].push_back(s[i] - '0');
				}
				row++;
			}
		}
		else {//push back the row and then its elements
			cout << s << endl;
			list2.push_back(vector<int>());
			for (int i = 0; i < s.length(); i++) {
				list2[row].push_back(s[i] - '0');
			}
			row++;
		}
	}
	myfile.close();
	cout << "File Closed" << endl;
	cout << endl;
}

bool compareV() {//compare vertices
	cout << "Checking Vertices" << endl;
	return (list1[0].size() == list2[0].size());
}

bool compareE() {//compare edges
	int numEdges1 = 0;
	int numEdges2 = 0;

	for (int i = 0; i < list1.size(); i++) {
		for (int j = 0; j < list1.size()-(list1.size()-i); j++) {
			if (list1[i][j] > 0) {//check edges in one half
				numEdges1++;
			}
			if (list2[i][j] > 0) {
				numEdges2++;
			}
		}
		if (list1[i][i] > 0) {//check self loops
			numEdges1++;
		}
		if (list2[i][i] > 0) {
			numEdges2++;
		}
	}
	cout << "Checking Edges" << endl;
	cout << numEdges1 << ", " << numEdges2 << endl;
	
	return (numEdges1 == numEdges2);
}

//Compare the degree sequence
bool compareD() {
	int d1 = 0;
	int d2 = 0;
	int total1 = 0;
	int total2 = 0;
	vector<int> degree1;
	vector<int> degree2;
	
	//count the degrees of each column
	cout << "Calculate Degrees" << endl;
	for (int i = 0; i < list1.size(); i++) {
		for (int j = 0; j < list1.size(); j++) {
			if (list1[j][i] > 0) {
				d1+=list1[j][i];
			}
			if (list2[j][i] > 0) {
				d2+=list2[j][i];
			}
		}
		degree1.push_back(d1);
		degree2.push_back(d2);

		cout << d1 << "," << d2 << " ";
		d1 = 0; d2 = 0;
	}
	cout << endl;

	sort(degree1.begin(), degree1.end());
	sort(degree2.begin(), degree2.end());


	return (degree1 == degree2);
}

//function to check if the lists are equal.
//I want to know if they arent so it cuts immediately if not equal
bool checkEqual() {
	bool equal = true;
	for (int i = 0; i < list1.size(); i++) {
		for (int j = 0; j < list1[0].size(); j++) {
			if (list1[i][j] != list2[i][j]) {
				equal = false;
				break;
			}
		}
		if (!equal) { break; }
	}
	return equal;
}

bool comparePermutations(int s, int e) {

	for (int i = 1; i < e; i++) {
		
		if (s == e) {
			if (checkEqual()) {vectEqual = true; }
		}
		else {
			//swap rows
			swap(list1[s], list1[i]);

			//switch columns
			for (int j = 0; j < list1.size(); j++) {
				swap(list1[j][s], list1[j][i]);
			}

			//compare
			if (checkEqual()) { vectEqual = true; }

			comparePermutations(s + 1, e);

			//switch columns
			for (int j = 0; j < list1.size(); j++) {
				swap(list1[j][s], list1[j][i]);
			}
			//swap rows
			swap(list1[s], list1[i]);
		}
	}
	
	return vectEqual;
}



//compare the two adjacency matrices to detect isomporphism
void compareLists() {
	//compare vertices
	if (compareV()) {
		//compare edges
		if (compareE()) {
			//compare degree
			if (compareD()) {
				//compare perumutations
				if (comparePermutations(0,list1.size()-1)) {
					cout << "These graphs are isomorphic" << endl;
				}
				else {
					cout << "Circuit Mismatch" << endl;
				}
			}
			else {
				cout << "Degrees mismatch" << endl;
			}
		}
		else {
			cout << "Edge mismatch" << endl;
		}
	}
	else {
		cout << "Vertice Mismatch" << endl;
	}

}

int main () {
	readFiles();
	compareLists();
}