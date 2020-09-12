#include	<iostream>
#include 	<fstream>
#include	<string>
#include	<cstdlib>
#include	"List.h"
#include	"Student.h"
bool BuildStuList(const char*, List*);
bool DeleteRecord(List*, char*);
bool InsertResult(const char*, List*);
bool Display(List, int);
bool getAverageCGPAByCourse(List);
bool filterStudent(List, List*, char*, int, int);
bool findEligibleFYPStudent(List, List*);
bool identifyGoodPoorStudent(List, List*, List*);
int menu();
using namespace std;

int main() {
	int choice;
	List stulist,goodlist,poorlist,list2,FYPlist; //Creates list containing student information
    while (1) {
        choice = menu(); //runs the choice menu and get user input
        if (choice == 1) {
            if (BuildStuList("student.txt", &stulist) == false) { 
                cout << "Error opening file!" << endl;
            }
            else {
                cout << "Action was succesful!" << endl;
            }
            system("pause");
        }
        else if (choice == 2) {
            char stuID[8];
            cout << "Please enter student ID of student you would like to delete: "; 
            cin.getline(stuID,8); //Get user to input student id 
            if (DeleteRecord(&stulist, stuID) == true) {    
                cout << "Action performed successfully" << endl;
            }
            else {
                cout << "entry not found" << endl;
            }
            system("pause");
        }
        else if (choice == 3) {
            if (InsertResult("exam.txt", &stulist) == false) { 
                cout << "Error opening file!" << endl;
            }
            else {
                cout << "Action was succesful!" << endl;
            }
            system("pause");
        }
        else if (choice == 4) {
            int source;
            cout << "Please enter the source you would like the result to be displayed (1-Screen, 2-File): ";  //Gives users the choice of displaying the output
            cin >> source; //Get the inpput from the user
            while (source < 1 || source>2) {  //Promts user to re-enter if the input exceeds the expected numbers
                cout << "The only valid choices are 1 and 2. Please re-enter: " << endl;
                cin >> choice;
                cin.clear();
                cin.get();
            }
            if (Display(stulist, source) == true) { //Calls the function display
                cout << "Action performed succesfully" << endl;
            }
            else {
                cout << "Error" << endl;
            }
            system("pause");
        }
        else if (choice == 5) {
            if (getAverageCGPAByCourse(stulist) == false) {
                cout << "Action performed failed" << endl;
            }
            else
            {
                cout << "Action performed successfully" << endl;
            }
            system("pause");
        }
        else if (choice == 6) {
            char course[3];
            int year, credit;
            //Get student information
            cout << "Please enter the student information: " << endl;
            cout << "Course (eg:CS): " << endl;
            cin.getline(course, 3);
            int x = strlen(course);
            for (int i = 0; i < x; i++) {
                course[i] = toupper(course[i]);
            }
            //Check if course code is valid, if not, re-enter
            while (strcmp(course, "CS") != 0 && strcmp(course, "CN") != 0 && strcmp(course, "CT") != 0 && strcmp(course, "IA") != 0 && strcmp(course, "IB") != 0) {
                cout << "Invalid course code, please re-enter: " << endl;
                cin.getline(course, 3);
                for (int i = 0; i < x; i++) {
                    course[i] = toupper(course[i]);
                }
            }
            cout << "Year: " << endl;
            cin >> year;
            cout << "Total credits:" << endl;
            cin >> credit;
            if (filterStudent(stulist, &list2, course, year, credit) == true) {
                cout << "Action performed successfully" << endl;
                Display(list2, 1);
            }
            else {
                cout << "Action performed failed" << endl;
            }
            system("pause");
        }
        else if (choice == 7) {
            if (findEligibleFYPStudent(stulist, &FYPlist) == true) {
                cout << "Action performed successfully" << endl;
                Display(FYPlist, 1);
            }
            else {
                cout << "Action performed failed" << endl;
            }
            system("pause");
        }
        else if (choice == 8) {
            if (identifyGoodPoorStudent(stulist, &goodlist, &poorlist) == false) {
                cout << "Student list is empty" << endl;
            }
            else {
                cout << "Action performed succesfully" << endl;
            }
            system("pause");
        }
        else if (choice == 9) {
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
	cout << "\n1. Read Student Information" << endl;
	cout << "2. Delete Student From Record" << endl;
	cout << "3. Insert Past Exam Result" << endl;
	cout << "4. Display Student Information" << endl;
	cout << "5. Get Average CGPA By Course" << endl;
	cout << "6. Filter Student" << endl;
	cout << "7. Find Eligible FYP Student" << endl;
	cout << "8. Identify Good and Poor Result Student" << endl;
	cout << "9. Exit" << endl;
	cout << "\nPlease enter your choice: ";
	cin >> choice; //Gets the input from user
	cin.clear();
	cin.get();
    while (choice < 1 || choice>9) {    //Promts user to re-enter if the input exceeds the expected numbers
        cout << "The only valid choices are 1-9. Please re-enter: " << endl;
        cin >> choice;
        cin.get();
        cin.clear();
    }
	return choice;  //Returns the choice that the user has inputed
}

bool BuildStuList(const char* filename, List* stulist) { 
    ifstream file1;
    file1.open(filename); //Opens the file "Student.txt"
    if (file1.fail())
        return false;
    string n, i, c, p;
    while (!file1.eof()) {  //Read the information from the file and copies it to the assigned variables
        file1.ignore(13);
        getline(file1, i);
        file1.ignore(7);
        getline(file1, n);
        file1.ignore(9);
        getline(file1, c);
        file1.ignore(14);
        getline(file1, p);
        file1.ignore();
        Student student;
        strcpy_s(student.name, n.c_str());
        strcpy_s(student.id, i.c_str());
        strcpy_s(student.course, c.c_str());
        strcpy_s(student.phone_no, p.c_str());
        int position = 1,count=0;
        while (1) { //While loop runs through the whole list to check if a duplicate student ID exists
            Student search;
            stulist->get(position, search);
            if (search.compareID(student) == true) { //Check if student ID is identical
                count++;
            }
            if (stulist->find(position) == NULL) { 
                break;  //Breaks the loop once the list has been fully traversed
            }
            position++;
        }
        if (count == 0) {
            stulist->insert(student); //Insert the record into the list if no duplicate was found
        }
    }
    file1.close();
    return true;
}
bool DeleteRecord(List* stulist, char* stuID) {
    int position =1,empty=0;
    string i = stuID;
    Student testing; 
    strcpy_s(testing.id, i.c_str()); //Load the given student id into the test struct
    while (1) {  //Traverse the list
        Student search;  
        stulist->get(position, search);
        //Search for matching ID and remove record
        if (search.compareID(testing) == true) { 
            stulist->remove(position); 
            return true;
        }
        if (stulist->find(position) == NULL) { //Breaks the loop if none is found
            empty++;
            break;
        }
        position++;
    }
    if (empty == 1) {
        return false;  //Returns false if no record was found
    }
}
bool Display(List stulist, int choice) {
    
    if (choice == 1) {
        Node* n = stulist.head;
        int count = 1;
        //Print student information
        for (int i = 0; i < stulist.count; i++) {  
            cout << "-------------------------------------STUDENT " << count << "----------------------------------------" ;
            n->item.print(cout);  
            cout << "\n-----------------------------------PAST EXAM RESULT-----------------------------------" << endl;
            for (int i = 0; i < n->item.exam_cnt; i++) {
                Student student;
                n->item.exam[i].print(cout); 
            }
            cout << "-------------------------------------STUDENT " << count << "----------------------------------------\n" << endl;
            n = n->next;
            count++;
        }    
        return true;
    }
    else {
        ofstream text("student_result.txt"); //Create an output text file
        Node* n = stulist.head; 
        int count = 1;
        //Print student information
        for (int i = 0; i < stulist.count; i++) { 
            text << "-------------------------------------STUDENT " << count << "----------------------------------------";
            n->item.print(text);
            text << "\n-----------------------------------PAST EXAM RESULT-----------------------------------" << endl;
            for (int i = 0; i < n->item.exam_cnt; i++) {
                Student student;
                n->item.exam[i].print(text);
            }
            text << "-------------------------------------STUDENT " << count << "----------------------------------------\n" << endl;
            n = n->next;
            count++;
        }
        return true;
    }
}
bool InsertResult(const char*filename, List*stulist) {
    ifstream file1;
    file1.open(filename); //Opens the file"Exam.txt"
    if (file1.fail())
        return false;
    while (!file1.eof()) {
        Exam exam;  
        char id[10];
        file1.ignore();
        file1 >> id >> exam.trimester >> exam.year >> exam.numOfSubjects; //Get info from file into struct
        Student s; 
        strcpy_s(s.id, id);  
        Node* n = stulist->head; 
        for (int i = 0; i < exam.numOfSubjects; i++) { //Reads subject info and insert into exam array,repeats for the numofsubjects
            file1 >> exam.sub[i].subject_code >> exam.sub[i].subject_name >> exam.sub[i].credit_hours >> exam.sub[i].marks;
        }    
        while (n) { //Traverse the studentlist to find identical id and insert exam arr into list
            if (n->item.compareID(s)){
                exam.calculateGPA();  
                n->item.exam[n->item.exam_cnt] = exam; 
                n->item.exam_cnt += 1; 
                n->item.calculateCurrentCGPA();
                break;
            }
            else {
                n = n->next; 
            }
        }
    }   
    file1.close();
    return true;
}
bool getAverageCGPAByCourse(List list) {
    if (list.empty())
        return false;
    Student student;
    int cs_st = 0, ia_st = 0, ib_st = 0, cn_st = 0, ct_st = 0;
    int cn_below = 0, ct_below = 0, ia_below = 0, ib_below = 0, cs_below = 0;
    int cn_above = 0, ct_above = 0, ia_above = 0, ib_above = 0, cs_above = 0;
    double cs_to = 0, averagecs, ia_to = 0, averageia, ib_to = 0, averageib, cn_to = 0, averagecn, ct_to = 0, averagect;
    int index = 1, i = 1;
    //Traverse the list go get course and gpa info
    while (1) {
        list.get(index, student);
        if (strcmp(student.course, "CN") == 0) {
            cn_to += student.current_cgpa;
            cn_st++;
        }
        else if (strcmp(student.course, "CS") == 0) {
            cs_to += student.current_cgpa;
            cs_st++;
        }
        else if (strcmp(student.course, "IA") == 0) {
            ia_to += student.current_cgpa;
            ia_st++;
        }
        else if (strcmp(student.course, "CT") == 0) {
            ct_to += student.current_cgpa;
            ct_st++;
        }
        else if (strcmp(student.course, "IB") == 0) {
            ib_to += student.current_cgpa;
            ib_st++;
        }
        if (list.find(index) == NULL) {
            break;
        }
        index++;
    }
    //Assign 0 to average if course count is 0
    if (cn_st == 0) {
        averagecn = 0;
    }
    else {
        averagecn = cn_to / cn_st;
    }
    if (ct_st == 0) {
        averagect = 0;
    }
    else {
        averagect = ct_to / ct_st;
    }
    if (cs_st == 0) {
        averagecs = 0;
    }
    else {
        averagecs = cs_to / cs_st;
    }
    if (ia_st == 0) {
        averageia = 0;
    }
    else {
        averageia = ia_to / ia_st;
    }
    if (ib_st == 0) {
        averageib = 0;
    }
    else {
        averageib = ib_to / ib_st;
    }
    //Count average cgpa for each course
    while (1) {
        list.get(i, student);
        if (list.find(i) == NULL) {
            break;
        }
        if (strcmp(student.course, "CN") == 0) {
            if ((student.current_cgpa) < averagecn)
                cn_below++;
            else if ((student.current_cgpa) >= averagecn)
                cn_above++;
        }
        else if (strcmp(student.course, "CS") == 0) {
            if (student.current_cgpa < averagecs)
                cs_below++;
            else if ((student.current_cgpa) >= averagecs)
                cs_above++;
        }
        else if (strcmp(student.course, "CT") == 0) {
            if ((student.current_cgpa) < averagect)
                ct_below++;
            else if ((student.current_cgpa) >= averagect)
                ct_above++;
        }
        else if (strcmp(student.course, "IA") == 0) {
            if ((student.current_cgpa) < averageia)
                ia_below++;
            else if ((student.current_cgpa) >= averageia)
                ia_above++;
        }
        else if (strcmp(student.course, "IB") == 0) {
            if ((student.current_cgpa) < averageib)
                ib_below++;
            else if ((student.current_cgpa) >= averageib)
                ib_above++;
        }
        i++;
    }
    //Prints result
    cout << "       Course       Average CGPA     No.of Students        No.of Students " << endl;
    cout << "                                      Below Average        Above Average  " << endl;
    cout << "        CS            " << setprecision(4)<<averagecs << "\t\t" << cs_below << "\t\t\t" << cs_above <<endl;
    cout << "        IA            " << averageia << "\t\t" << ia_below << "\t\t\t" << ia_above <<endl;
    cout << "        IB            " << averageib << "\t\t" << ib_below << "\t\t\t" << ib_above << endl;
    cout << "        CN            " << averagecn << "\t\t" << cn_below << "\t\t\t" << cn_above << endl;
    cout << "        CT            " << averagect << "\t\t" << ct_below << "\t\t\t" << ct_above <<endl;
    return true;
}
bool filterStudent(List list1, List* list2, char* course, int year, int credit) {
    int position = 1, id, count=0;
    if (list1.empty() || !list2->empty())
        return false;
    year = year % 100;
    Student student;
    //Traverse the list to find matching record(s) with details given
    while (1) {
        list1.get(position, student);
        id = atoi(student.id);
        id /= 100000;
        if (strcmp(student.course, course) == 0 && id == year && student.totalCreditsEarned==credit ) {
            list2->insert(1, student);
            count++;
        }
        if (list1.find(position) == NULL) {
            break;
        }
        position++;
    }
    if (count == 0) {
        cout << "Student does not exist!" << endl;
    }
    return true;
}
bool findEligibleFYPStudent(List stulist, List* FYPlist) {
    if (stulist.empty())
        return false;
    Student student;
    int position = 1;
    while (1) {
        //Traverse the list to find students that fit the criteria
        bool fyp1 = false, fyp2 = false, credit = false;
        stulist.get(position, student);
        if (student.totalCreditsEarned >= 30) {
            credit = true;
        }
        for (int j = 0; j < sizeof(student.exam) / sizeof(student.exam[j]); j++) {
            for (int i = 0; i < student.exam[j].numOfSubjects; i++) {
                if (strcmp(student.exam[j].sub[i].subject_code, "UCCD2502") == 0) {
                    if (student.exam[j].sub[i].marks >= 50)
                        fyp1 = true;
                    else fyp1 = false;
                }
                else if (strcmp(student.exam[j].sub[i].subject_code, "UCCD2513") == 0) {
                    if (student.exam[j].sub[i].marks >= 50)
                        fyp2 = true;
                    else fyp2 = false;
                }
            }
        }
        //Insert student recrod into fyp list if all criterias are met
        if (credit && fyp1 && fyp2) {
            FYPlist->insert(1, student);
        }
        if (stulist.find(position) == NULL) {
            break;
        }
        position++;

    }
    if (FYPlist->empty()) cout << "There is no student that is eligible to take FYP" << endl;
    return true;
}
bool identifyGoodPoorStudent(List stulist, List* goodlist, List* poorlist) {
    if (stulist.find(1) == NULL) {
        return false; //Retrun false if stulist is empty
    }
    else {
        int position = 1, goodcount = 0, poorcount = 0;
        while (1) {  //Traverses the list to find students
            Student search;
            stulist.get(position, search);
            if (stulist.find(position) == NULL) {
                break;  //Breaks the loop once the list has been fully traversed
            }
            else {
                if (search.current_cgpa >= 3.5 && search.exam_cnt >= 3) { //Check if student is good
                    int count = 0, fail = 0;
                    for (int i = 0; i < 10; i++) {
                        if (search.exam[i].gpa >= 3.5) {
                            count++;
                        }
                        for (int j = 0; j < search.exam[i].numOfSubjects; j++)
                            if (search.exam[i].sub[j].marks <= 49) {
                                fail++;
                            }
                    }
                    if (count >= 3 && fail == 0) {
                        goodlist->insert(search); //Insert the student in good list if all criterias are met
                        goodcount++;
                    }
                }
                else if (search.current_cgpa <= 2.0 && search.exam_cnt >= 3) { //Check if student is poor
                    int count = 0;
                    for (int i = 0; i < 10; i++) {
                        if (search.exam[i].gpa <= 2.0) {
                            count++;
                        }
                    }
                    if (count > 3) {
                        poorlist->insert(search); //Insert the student in poor list if all criterias are met
                        poorcount++;
                    }
                }

            }
            position++;
        }
        //Prints the result
        if (goodcount == 0) {
            cout << "\nThere is no student in good list\n " << endl;
        }
        else {
            cout << "\nStudent in good list: \n" << endl;
            Display(*goodlist, 1);
        }
        if (poorcount == 0) {
            cout << "\nThere is no student in poor list\n " << endl;
        }
        else {
            cout << "\nStudent in poor list: \n" << endl;
            Display(*poorlist, 1);
        }
        return true;
    }
}