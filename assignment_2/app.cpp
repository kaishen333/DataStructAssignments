#include	<iostream>
#include	<fstream>
#include	<string>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char *, BST *);
int menu();

int main() {
	BST t1,t2;
	int choice;
	while (1) {
		choice = menu(); //runs the choice menu and get user input
		if (choice == 1) {
			if (readFile("student.txt", &t1) == false) {
				cout << "Error opening file!" << endl;
			}
			else {
				cout << "Action was succesful!" << endl;
			}
			system("pause");
		}
		else if (choice == 2) {
			if (t1.deepestNodes() == false) {
				cout << "BST is empty!" << endl;
			}
			else {
				cout << "Action was succesful!" << endl;
			}
			system("pause");
		}
		else if (choice == 3) {
			int order,source;
			cout << "What order would you like the result to be displayed (1-Ascending, 2-Descending): ";  //Gives users the choice of displaying the output
			cin >> order; //Get the inpput from the user
			while (order < 1 || order>2) {  //Promts user to re-enter if the input exceeds the expected numbers
				cout << "The only valid choices are 1 and 2. Please re-enter: " << endl;
				cin >> order;
				cin.clear();
				cin.get();
			}
			cout << "Please enter the source you would like the result to be displayed (1-Screen, 2-File): ";  //Gives users the choice of displaying the output
			cin >> source; //Get the inpput from the user
			while (source < 1 || source>2) {  //Promts user to re-enter if the input exceeds the expected numbers
				cout << "The only valid choices are 1 and 2. Please re-enter: " << endl;
				cin >> choice;
				cin.clear();
				cin.get();
			}
			if (t1.display(order, source) == false) {
				cout << "Error opening file!" << endl;
			}
			else {
				cout << "Action was succesful!" << endl;
			}
			system("pause");
		}
		else if (choice == 4) {
			Student item;
			cout << "Please enter the root of the subtree you would like to clone: ";
			cin >> item.id;
			if (t2.CloneSubtree(t1, item) == false) {
				cout << "Action unsuccesful" << endl;
			}
			else {
				cout << "Original Tree\n";
				t1.inOrderPrint();
				cout << "CloneTree\n";
				t2.inOrderPrint();
				cout << "Action was succesful!" << endl;
			}
			system("pause");
		}
		else if (choice == 5) {
			Student item;
			cout << "Please enter the node of the subtree you would like to find the ancestor of: ";
			cin >> item.id;
			if (t1.printAncestor(item) == false) {
				cout << "Action unsuccesful" << endl;
			}
			else {
				cout << "\nAction was succesful!" << endl;
			}
			system("pause");
		}
		else if (choice == 6) {
			if (t1.printPath() == false) {
				cout << "Action was unsuccesful" << endl;
			}
			else {
				cout << "Action was succesful!" << endl;
			}
			system("pause");
		}
		else if (choice == 7) {
			cout << "Thank you and have a nice day!" << endl;
			system("pause");
			break;
		}
	}
}
int menu() {  //This function shows the actions users are able to peform
	int choice;
	system("cls");
	cout << "\n Please select a function you would like to perform" << endl;
	cout << "\n1. Read data to BST" << endl;
	cout << "2. Print deepest nodes" << endl;
	cout << "3. Display Student" << endl;
	cout << "4. Clone Subtree" << endl;
	cout << "5. Print Ancestor" << endl;
	cout << "6. Print Path" << endl;
	cout << "7. Exit" << endl;
	cout << "\nPlease enter your choice: ";
	cin >> choice; //Gets the input from user
	cin.clear();
	cin.get();
	while (choice < 1 || choice>7) {    //Promts user to re-enter if the input exceeds the expected numbers
		cout << "The only valid choices are 1-7. Please re-enter: " << endl;
		cin >> choice;
		cin.get();
		cin.clear();
	}
	return choice;  //Returns the choice that the user has inputed
}

bool readFile(const char *filename, BST *t1) {
	ifstream file1;
	file1.open(filename); //Opens the file "Student.txt"
	if (file1.fail())
		return false;
	string n,ad,dob,ph,co;
	int count = 0;
	while (!file1.eof()) { //Read the information from the file and copies it to the assigned variables
		Student student;
		file1.ignore(12);
		file1 >> student.id;
		file1.ignore(7);
		getline(file1, n);
		file1.ignore(10);
		getline(file1, ad);
		file1.ignore(6);
		getline(file1, dob);
		file1.ignore(14);
		getline(file1, ph);
		file1.ignore(9);
		getline(file1, co);
		file1.ignore(7);
		file1 >> student.cgpa;
		file1.ignore();
		strcpy_s(student.name, n.c_str());
		strcpy_s(student.address, ad.c_str());
		strcpy_s(student.DOB, dob.c_str());
		strcpy_s(student.course, co.c_str());
		strcpy_s(student.phone_no, ph.c_str());
		t1->insert(student);
		count++;
	}
	cout << "\nNumber of students read into BST: " << count << endl;
	file1.close();
	return true;
}
