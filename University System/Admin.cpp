#include "Admin.h"
#include<iostream>
#include<string>
#include<string.h>
#include "Courses.h"
#include <unordered_set>
#include<cmath>
#include <map>
#include "Student.h"
#include<fstream>

using namespace std;

//constructors
Admin::Admin() {
	Password = Name = "";
	LoadStudents();
	LoadCourses();
	LoadFinishedCourses();
	LoadStudentsInProgressCourses();
	LoadGrades();
	LoadStudentsEnrolled();
	LoadPrerequisite();
	loadAdmin();
}

Admin::Admin(string Sname, string pass) {
	Name = Sname;
	Password = pass;
}
//Setters
void Admin::setName(string name) {

	Name = name;
}
void Admin::setPassword(string password) {
	Password = password;

}
void Admin::setStudent(map<int, Student*>stud) {
	students = stud;
}
void Admin::setCourse(unordered_map<string, Courses*>crs) {
	courses = crs;
}
// Getters#
string Admin::getName() {
	return Name;
}
string Admin::getPassword() {
	return Password;
}
map<int, Student*> Admin::getStudents() {
	return students;

}
unordered_map<string, Courses*> Admin::getCourses() {
	return courses;
}
vector<Admin> Admin::getadmins() {
	return admins;
}
                                                                                      //Functions
Admin Admin::LogIn() {

	bool login = false;
	do {
		string email, password;
		cout << "Please Enter Your Email : ";
		cin >> email;
		cout << endl;
		cout << "PLease Enter Your Password : ";
		cin >> password;



		for (auto admin : admins) {

			if (admin.getName() == email && admin.getPassword() == password) {
				return admin;
				login = true;

				break;
			}
		}
		if (!login) {
			cout << "invalid email or password , Please Try Again " << endl;
			cout << "---------------------------------------------------------------------------------" << endl;
		}

	} while (!login);



}
void Admin::AddStudent() {
	string name, password, email, academicYear;
	int maxHoursAllowed;
	int id;
	id = students.size() + 1;
	cout << "Enter student name: ";
	cin >> name;
	cout << "Enter student password: ";
	cin >> password;
	cout << "Enter student maximum hours allowed: ";
	cin >> maxHoursAllowed;
	cout << "Enter student academic year: ";
	cin >> academicYear;
	email = name + to_string(id) + "@gmail.com";
	Student* stud = new Student(name, email, password, academicYear, id, maxHoursAllowed);
	students.insert({ id, stud });
	cout << "Successfully added student with email: " << email << endl;

}
void Admin::AddCourse() {
	string name, code, inst;
	bool req;
	int max, hrs;
	code = to_string(courses.size() + 1);
	cout << "Enter course name: ";
	cin >> name;

	cout << "Enter course instructor: ";
	cin >> inst;
	cout << "Press 1 if required and 0 if elective : ";
	cin >> req;
	cout << "Enter max students : ";
	cin >> max;
	cout << "Enter course hours: ";
	cin >> hrs;

	Courses* course = new Courses(name, code, inst, max, hrs, req);
	courses.insert({ code,course });

}
void Admin::AddPrerequisites() {
	cout << "Enter course code to add Prerequisites : ";
	string code;
	cin >> code;
	if (!CourseExist(code)) {
		cout << "Invalid course code, Please Try Again...." << endl;
		AddPrerequisites();
	}
	else {
		vector<string>temp;
		temp = courses[code]->getPrerequisite();
		cout << "Enter prerequisite course code : ";
		string PreReqCode;
		cin >> PreReqCode;
		if (CourseExist(PreReqCode)) {
			temp.push_back(PreReqCode);
			courses[code]->setPrerequisite(temp);
			cout << courses[PreReqCode]->getCourseName()<<" Added to prerequisites of : "<<courses[code]->getCourseName();
		}
		else {
			cout << "Course doesn't exist, Please Try Again...." << endl;
			AddPrerequisites();
		}
	}

}
void Admin::displaystuds()
{
	string crscode;
	cout << "Enter course code: ";
	cin >> crscode;

	if (!CourseExist(crscode)) {
		cout << "Invalid course code , Please Try Again...." << endl ;
		cout<< "-------------------------------------------------------------------------------------" << endl;
		displaystuds();
		return;
	}

	cout << "Students Enrolled : " << endl;
	vector<int> enrolledStudents = courses[crscode]->getStudentsenrolled();

	if (enrolledStudents.empty()) {
		cout << "No students enrolled in this course " << endl;
		cout<< "-------------------------------------------------------------------------------------" << endl;
		return;
	}

	for (auto studentId : enrolledStudents) {
		if (students.find(studentId) != students.end()) {
			cout << "Name: " << students[studentId]->getName() << "  " << "ID: " << students[studentId]->getId() << endl;
		}
	}
}
void Admin::addgrades()
{
	string CourseCode;
	float grade;
	int studentid;
	bool found = false;
	cout << "Enter Student Id : " << endl;
	cin >> studentid;
	if (!studentexists(studentid)) {
		cout << "Invalid Id , Please Try Again...." << endl;
		addgrades();
	}
	else {

		cout << "Enter Course Code : ";
		cin >> CourseCode;
		if (!CourseExist(CourseCode)) {
			cout << "Invalid Course Code, Please Try Again.... " << endl;
			addgrades();
		}
		else {
			bool correct = false;
			while (!correct) {
				cout << "Enter Student grade : ";
				cin >> grade;
				if (grade <= 0 || grade > 4) {
					cout << "Invalid Grade , Please Enter Grade between 0 and 4" << endl;

				}
				else
				{
					students[studentid]->setGrades(CourseCode, grade);
					vector<string>finishd;
					finishd = students[studentid]->getFinishedCourses();
					finishd.push_back(CourseCode);
					students[studentid]->setFinishedCourses(finishd);
					cout << "Grade Added Successfully.... ";
					found = true;
					correct = true;
				}
			}
		}
	}
	vector<string> temp;
	if (found) {
		for (auto i : students[studentid]->getCoursesInProgress()) {
			if (i != CourseCode) {
				temp.push_back(i);
			}
		}
		students[studentid]->setCoursesInProgress(temp);
		saveInProgCourses();
  
	}

}
void Admin::ViewListofallCourses()
{
	int id;
	cout << "Enter Student ID : " << endl;
	cin >> id;
	if (!studentexists(id)) {
		cout << "Invalid Id,Please Try Again...." << endl;
		ViewListofallCourses();
	}
	else {
		students[id]->ViewYourCourses();
	}

}
void Admin::editcourse()
{
	string name, code, inst;
	bool req;
	int max, hrs;
	int choice;

	cout << "Enter course code: ";
	cin >> code;
	if (!CourseExist(code)) {
		cout << "invalid course code" << endl;
		editcourse();
	}
	else {
		cout << "What would you like to edit in Course's data?" << endl;
		cout << "1. Name" << endl;
		cout << "2. instructor" << endl;
		cout << "3. Requriement" << endl;
		cout << "4. Maximum Students allowed" << endl;
		cout << "5. Course Hours" << endl;

		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Enter new name: ";
			cin >> name;
			courses[code]->setCourseName(name);
			cout << "Name updated successfully." << endl;
			break;
		case 2:
			cout << "Enter new instructor: ";
			cin >> inst;
			courses[code]->setInstructorName(inst);
			cout << "Instructor name updated successfully." << endl;
			break;
		case 3:
			cout << "Enter course requriement: ";
			cin >> req;
			courses[code]->setRequirement(req);
			cout << "Course requirement updated successfully." << endl;
			break;

		case 4:
			cout << "Enter new maximum students allowed: ";
			cin >> max;
			courses[code]->setMaxNumberOfStudents(max);
			cout << "Maximum students allowed updated successfully." << endl;
			break;

		case 5:
			cout << "Enter new Course hours allowed: ";
			cin >> hrs;
			courses[code]->setHours(hrs);
			cout << "new Course hours updated successfully." << endl;
			break;
		default:
			cout << "Invalid choice. Please try again...." << endl;
			editcourse();
			break;
		}
	}

}
void Admin::editStudentData() {
	int id, Max_Hours;
	string name;
	string email;
	string Academic_Year;
	cout << "Enter Id of student you want to edit: " << endl;
	cin >> id;
	if (!studentexists(id)) {
		cout << "Invalid Id, Please Try Again...." << endl;
		editStudentData();
	}
	else {
		int choice;
		Admin a1;

		cout << "Student's Data: " << endl;
		DisplayStudentData(id);

		cout << "What would you like to edit in student's data?" << endl;
		cout << "1. Name" << endl;
		cout << "2. Email" << endl;
		cout << "3. Academic Year" << endl;
		cout << "4. Maximum hours allowed" << endl;
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Enter new name: ";
			cin >> Name;
			cout << "Name updated successfully." << endl;
			break;
		case 2:
			cout << "Enter new email: ";
			cin >> email;
			cout << "Email updated successfully." << endl;
			break;
		case 3:
			cout << "Enter new academic year: ";
			cin >> Academic_Year;
			cout << "Academic year updated successfully." << endl;
			break;

		case 4:
			cout << "Enter new maximum hours allowed: ";
			cin >> Max_Hours;
			cout << "Maximum hours updated successfully." << endl;
			break;

		default:
			cout << "Invalid choice. Please try again." << endl;
			break;
		}


		students[id]->setName(name);
		students[id]->setEmail(email);
		students[id]->setAcademicYear(Academic_Year);
		students[id]->setMaximumHoursAllowed(Max_Hours);
	}
}
void Admin::changeStudent(int id, string email, string password, string name) {

	students[id]->setName(name);
	students[id]->setEmail(email);
	students[id]->setPassword(password);

}

                                                               


                                                                                 //needed Functions 
bool Admin::studentexists(int studid) {
	bool found = false;
	for (auto i : students) {
		if (i.first == studid) {
			found = true;
			break;
		}
	}
	return found;

}
Student Admin::getStudent(int studid) {

	string name = students[studid]->getName();
	int id = students[studid]->getId();
	string email = students[studid]->getEmail();
	string password = students[studid]->getPassword();
	string academicyear = students[studid]->getAcademicYear();
	int MaxHours = students[studid]->getMaximumHoursAllowed();
	Student s1 = Student(name, email, password, academicyear, id, MaxHours);
	return s1;

}
void Admin::addAdmin(string name, string pass) {
	Admin temp(name, pass);
	admins.push_back(temp);
}
bool Admin::CourseExist(string id) {                   //to check if course Exist
	bool found = false;
	for (auto i : courses) {
		if (i.first == id) {
			found = true;
			break;
		}
	}
	return found;
}
bool Admin::CourseExistByName(string name) {
	bool found = false;
	for (auto i : courses) {
		if (i.second->getCourseName() == name) {
			found = true;
			break;
		}
	}
	return found;
}
Student* Admin::getStudentByEmail(string email) {
	int id;
	for (auto i : students) {
		if (i.second->getEmail() == email)
		{
			id = i.first;
			break;
		}

	}
	return students[id];
}
void Admin::DisplayStudentData(int id)
{
	cout << "Student Name: " << students[id]->getName() << endl;
	cout << "Student Email: " << students[id]->getEmail() << endl;
	cout << "Student Academic Year: " << students[id]->getAcademicYear() << endl;
	cout << "Student Maximum Hours allowed: " << students[id]->getMaximumHoursAllowed() << endl;
}

                                                                          //Bonus Functions
void Admin::CalcAvg() {
	string code;
	float sum = 0;
	float temp = 0;
	int cnt = 0;
	float avg = 0;
	
	for (auto ts : courses) {
		code = ts.first;

		for (auto sd : students) {
			temp = sum;
			sum += sd.second->getGrade(code);
			if (temp != sum) {
				cnt++;
			}
		}
		avg = sum / cnt;
		cout  << ts.second->getCourseName() << endl;
		if (!isnan(avg))
			cout << "Average = " << avg << endl;
		else
			cout << "No Grades Added To This course " << endl;
		cout << "---------------------------"<<endl;
		sum = 0;
		temp = 0;
		cnt = 0;
	}
}
void Admin::maxmin() {
	string code;

	
	float val = 0;
	float temp = 10;
	int min = 10;
	float max = 0;

	for (auto ts : courses) {
		code = ts.first;

		for (auto sd : students) {

			val = sd.second->getGrade(code);
			if (val > max) {
				max = val;
			}
			temp = sd.second->getGrade(code);

			if (temp > 0 && temp < min) {
				min = temp;
			}

		}

		cout << ts.second->getCourseName() << endl;
		if (isnan(max) || max == 0)
			cout << "No Grades Added To This Course " << endl;
		else
		{
		cout<< "Maximun Grade :  " << max << "      Minimum Grade : " << min << endl;
		}
		cout << "--------------------------------------------"<<endl;
		max = 0;
		min = 10;
	}






}
void Admin::successrate() {
	string code;

	float grade;
	float cnt = 0;
	float sum = 0;
	float rate = 0;
	for (auto ts : courses) {
		code = ts.first;   

		for (auto sd : students) {

			grade = sd.second->getGrade(code);
			if (grade > 0) {
				cnt++;
				if (grade > 2) {
					sum++;
				}

			}

		}
		rate = sum / cnt;
		cout << ts.second->getCourseName() << endl;
		if (!isnan(rate)) {
			cout << "Success Rate : " << rate << endl;
		}
		else
		{
			cout << "No Grades In this Course...." << endl;
		}
	cout << "-------------------------------------------" << endl;
	cnt = 0;
	sum = 0;
	rate = 0;
	}
}



                                                                                      //Load and store in files
void Admin::LoadStudents() {
	ifstream file("LoadStudent.txt");
	string Name;
	string Email;
	string Password;
	string AcademicYear;
	int Id;
	int MaximumHoursAllowed;
	float GPA;
	while (file >> Id >> Email >> Password >> AcademicYear >> Name >> MaximumHoursAllowed) {
		Student* student = new Student(Name, Email, Password, AcademicYear, Id, MaximumHoursAllowed);
		students.insert({ Id,student });
	}
}
void Admin::SaveStudents() {
	ofstream file("LoadStudent.txt");
	for (const auto& element : students) {
		file << element.first << " " << element.second->getEmail() << " " << element.second->getPassword() << " " << element.second->getAcademicYear() << " " << element.second->getName() << " " << to_string(element.second->getMaximumHoursAllowed()) << endl;
	}
	file.close();
}
void Admin::LoadGrades() {
	ifstream file("LoadGrades.txt");
	float grade;
	string CourseCode;
	int StudentID;
	while (file >> StudentID >> CourseCode >> grade) {

		students[StudentID]->setGradeMap(CourseCode, grade);
	}


}
void Admin::SaveGrades() {
	map<string, float> Grades;
	ofstream file("LoadGrades.txt");
	int StudentID;
	for (const auto& element : students) {

		for (const auto& element2 : students[element.first]->getGradeMap()) {
			file << element.first << " " << element2.first << " " << element2.second << endl;

		}
	}
	file.close();
}
void Admin::LoadCourses() {
	ifstream file("LoadCourses.txt");
	string Course_Name;
	string Course_Code;
	string Instructor_Name;
	int MaxNumberOfStudents;
	int Hours;
	bool Requirement;
	vector<string> preq;
	while (file >> Course_Code >> Course_Name >> Instructor_Name >> MaxNumberOfStudents >> Hours >> Requirement) {
		Courses* course = new Courses(Course_Name, Course_Code, Instructor_Name, MaxNumberOfStudents, Hours, Requirement);
		courses.insert({ Course_Code,course });

	}

}
void Admin::SaveCourses() {
	ofstream file("LoadCourses.txt");
	for (const auto& element : courses) {
		file << element.first << " " << element.second->getCourseName() << " " << element.second->getInstructorName() << " " << element.second->getMaxNumberOfStudents() << " " << element.second->getHours() << " " << element.second->getRequirement() << endl;
	}
}
void Admin::SaveStudentsFinishedCourses() {

	ofstream file("StudentFinishedCourses.txt");
	if (!file) {
		cout << "Error opening file StudentFinishedCourses.txt" << endl;
		return;
	}

	for (auto element : students) {
		file << element.first << " ";
		for (auto fincourses : element.second->getFinishedCourses()) {
			file << fincourses << " ";
			// save the course code
		}
		file << endl;
	}

	file.close();
}
void Admin::LoadFinishedCourses() {
	ifstream file("StudentFinishedCourses.txt");
	string Course_Code;
	int StudentId;

	while (file >> StudentId) {
		vector<string> temp;
		getline(file, Course_Code);
		istringstream ss(Course_Code);
		while (ss >> Course_Code) {
			temp.push_back(Course_Code);

		}


		students[StudentId]->setFinishedCourses(temp);
	}

}
void Admin::SaveStudentsInProgressCourses(string x)
{
	if (x == "1")
		rename("temp.txt", "StudentsInProgressCourses.txt");
	else if (x == "2")
		rename("temp2.txt", "StudentsInProgressCourses.txt");


}
void Admin::LoadStudentsInProgressCourses()
{
	ifstream file("StudentsInProgressCourses.txt");
	string Course_Code;
	int StudentId;

	while (file >> StudentId) {
		vector<string> temp;
		getline(file, Course_Code); // read the rest of the line
		istringstream ss(Course_Code);
		while (ss >> Course_Code) {

			temp.push_back(Course_Code);

		}


		students[StudentId]->setCoursesInProgress(temp);

	}



}
void Admin::SaveStudentsEnrolled() {

	rename("temp3.txt", "SaveStudentsEnrolled.txt");

}
void Admin::LoadStudentsEnrolled()
{

	ifstream file("SaveStudentsEnrolled.txt");
	string line;
	string Course_Code;
	int StudentId;

	while (getline(file, line)) {
		istringstream iss(line);
		if (iss >> Course_Code) {
			vector<int> temp; // Declare vector inside the loop
			while (iss >> StudentId) {
				temp.push_back(StudentId);
			}

			courses[Course_Code]->setStudentsEnrolled(temp);
			temp.clear(); // Clear vector after using it
		}
	}
}
void Admin::loadAdmin() {
	ifstream file("AdminData.txt");
	string name;
	string password;

	while (file >> name >> password) {
		Admin temp(name, password);
		admins.push_back(temp);
	}
}
void Admin::saveAdmin() {
	ofstream file("AdminData.txt");
	for (auto i : admins) {
		file << i.getName() << i.getPassword();
	}

}
void Admin::LoadPrerequisite() {


	ifstream file("Prerequisites.txt");
	string Course_Code;
	string Main_Course;
	string line;


	while (getline(file, line)) {
		vector<string> temp;
		istringstream iss(line);
		if (iss >> Main_Course) {
			while (iss >> Course_Code) {
				temp.push_back(Course_Code);
			}
			courses[Main_Course]->setPrerequisite(temp);
		}
	}
}
void Admin::SavePrerequisite() {

	ofstream file("Prerequisites.txt");
	for (const auto& element : courses) {
		file << element.first << " ";
		for (auto PreReqCourses : element.second->getPrerequisite()) {
			file << PreReqCourses << " ";
		}
		file << endl;
	}
}
void Admin::saveInProgCourses() {
	fstream file;
	file.open("temp2.txt", fstream::out);

	for (auto element : students) {
		file << element.first << " ";

		for (auto inprogcourses : element.second->getCoursesInProgress()) {
			file << inprogcourses << " ";
			// save the course code
		}
		file << endl;
	}
	file.close();


}
void Admin::saveEnrolled() {
	ofstream file("SaveStudentsEnrolled.txt");
	for (auto crs : courses) {
		file << crs.first << " ";
		for (auto Studenroll : crs.second->getStudentsenrolled()) {
			file << Studenroll << " ";
		}
		file << endl;
	}
	file.close();
}


                                                                                  //Bonus Functions







