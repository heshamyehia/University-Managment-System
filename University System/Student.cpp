#include "Student.h"
#include"Courses.h"
#include<fstream>    
#include"Admin.h"
#include<iostream>
#include <algorithm> // for std::transform
#include <cctype> 
//Constructors

Admin a1 = Admin();
int Student::StudentsCounter = 0;
Student::Student() {
	Name = "";
	Email = "";
	Password = "";
	AcademicYear = "";
	Id = 0;
	MaximumHoursAllowed = 0;
	GPA = 0;
	StudentsCounter++;

}
Student::Student(string name, string email, string password, string academicyear, int id, int MaxHours) {

	Name = name;
	Email = email;
	Password = password;
	AcademicYear = academicyear;
	Id = id;
	MaximumHoursAllowed = MaxHours;
	GPA = 0;
	StudentsCounter++;
}


//Setters
void Student::setName(string name) {
	Name = name;

}
void Student::setEmail(string email) {
	Email = email;
}
void Student::setPassword(string password) {
	Password = password;
}
void Student::setAcademicYear(string academicyear) {
	AcademicYear = academicyear;
}
void Student::setId(int id) {
	Id = id;
}
void Student::setMaximumHoursAllowed(int MaxHours) {
	MaximumHoursAllowed = MaxHours;
}
void Student::setGPA(float gpa) {
	GPA = gpa;
}
void Student::setGrades(string crscode, float grade) {
	Grades[crscode] = grade;
}
void Student::setFinishedCourses(vector<string> FCourses) {
	FinishedCourses_code = FCourses;

}
void Student::setCoursesInProgress(vector <string>PCourses) {
	CoursesInProgress = PCourses;
}

//void Student::setGradeMap(map < string, float > mp) {
//
//	 Grades=mp;
//
//}
// 
void Student::setGradeMap(string CrsCode, float grade) {

	Grades.insert({ CrsCode,grade });
}

void Student::setgrades(map < string, float > g) {
	Grades = g;
}




//Getters

string Student::getName() {
	return Name;
}
string Student::getEmail() {
	return Email;
}
string Student::getPassword() {
	return Password;
}
string Student::getAcademicYear() {
	return AcademicYear;
}
int Student::getId() {
	return Id;
}
int Student::getMaximumHoursAllowed() {
	return MaximumHoursAllowed;
}
float Student::getGPA() {
	return GPA;
}
float Student::getGrade(string courseCode) {

	return Grades[courseCode];

}

vector <string> Student::getFinishedCourses() {
	return FinishedCourses_code;

}
vector<string> Student::getCoursesInProgress() {
	return CoursesInProgress;

}
map < string, float > Student::getGradeMap() {

	return Grades;

}

bool caseInsensitiveStringCompare(string& str1, string& str2) {				//compares strings and case insensitive
	if (str1.size() != str2.size()) {
		return false; // Different sizes, not equal
	}

	string lowercaseStr1(str1);
	string lowercaseStr2(str2);

	// Convert both strings to lowercase
	transform(lowercaseStr1.begin(), lowercaseStr1.end(), lowercaseStr1.begin(), [](unsigned char c) {
		return tolower(c);
		});

	transform(lowercaseStr2.begin(), lowercaseStr2.end(), lowercaseStr2.begin(), [](unsigned char c) {
		return tolower(c);
		});

	return lowercaseStr1 == lowercaseStr2;
}		
                                                               //displays all courses availeble ( not finished or in progress )

void Student::ViewList() {					

	bool finishedCrs;
	bool inprogCrs;
	cout << "The List of all the courses available: " << endl;
	for (auto course : a1.getCourses()) {
		finishedCrs = true; // Initialize the flags for each course
		inprogCrs = true;
		for (auto finCrs : FinishedCourses_code) {
			if (course.first == finCrs) {
				finishedCrs = false;
				break;
			}
		}
		for (auto inprgCrs : CoursesInProgress) {
			if (course.first == inprgCrs) {
				inprogCrs = false;
				break;
			}
		}
		if (finishedCrs && inprogCrs) {
			cout << "The course code is: " << course.first << "    " << " The course name is: " << course.second->getCourseName() << endl << endl;
		}
	}
}

void Student::FilterCourses() {

	cout << "To display required courses press 1 and for elective courses press 2 : " << endl;
	string choice;
	cin >> choice;

	bool isreq = false;
	if (choice == "1") {
		isreq = 1;
	}
	else if (choice == "2")
		isreq = 0;
	else {
		cout << "Invalid Number , Please Try Again...." << endl;
		FilterCourses();
		return;
	}
	cout << "The Desired courses are: "<<endl;
	for (auto course : a1.getCourses()) {
		if (course.second->getRequirement() == isreq)
			cout << "The course code is : " << course.second->getCourseCode() << "  The course name is : " << course.second->getCourseName() << endl;
	}
}
void Student::ViewDetails() {									//displays all details for the course entered.

	cout << "Enter course Name : ";
	string  name;
	cin >> name;
	bool found = false;

		Courses* course{};
		for (auto crs : a1.getCourses()) {
			string s = crs.second->getCourseName();
			if (caseInsensitiveStringCompare(s, name)) {
				course = crs.second;
				found = true;
				break;
			}
		}
		if (!found) {
			cout << "Invalid Name , Please Try Again...." << endl;
			ViewDetails();
		}
			
		else
		{
			cout << "The course code is : " << course->getCourseCode() << endl;
			cout << "The course name is : " << course->getCourseName() << endl;
			cout << "The course instructor is : " << course->getInstructorName() << endl;
			cout << "The course max hours are : " << course->getHours() << endl;
			cout << "The course is : ";
			if (course->getRequirement() == 1)
			{
				cout << "Required " << endl;

			}
			else {
				cout << "Elective " << endl;
			}
			unordered_map<string, Courses*>allcrs = a1.getCourses();
			cout << "The course Max students is : " << course->getMaxNumberOfStudents() << endl;
			auto prerequisites = course->getPrerequisite();
			if (prerequisites.empty()) {
				cout << "None";
			}
			else {
				cout << endl << "The pre-required courses are : " << endl;
				for (auto prereq : course->getPrerequisite()) {
					cout << allcrs[prereq]->getCourseName() << endl;
				}
			}
		}
		
}
void Student::Register() {					// if student wants to register in a specefic course.

	cout << "Enter course Name : ";
	string  name;
	cin >> name;
	bool Found=false;
		Courses* course{};

		for (auto crs : a1.getCourses()) {
			string s = crs.second->getCourseName();
			if (caseInsensitiveStringCompare(s, name)) {
				course = crs.second;
				Found = true;
				break;
			}
		}if (!Found) {
			cout << "Invalid Course Name , Please Try Again...." << endl;
			cout<< "-------------------------------------------------------------------------------------" << endl;
			Register();
		}
		else
		{

			for (auto crs : FinishedCourses_code) {
				if (crs == course->getCourseCode()) {
					cout << "You already finished this course" << endl;
					return;
				}
			}
			for (auto crs : CoursesInProgress) {
				if (crs == course->getCourseCode()) {
					cout << "You already registered in this course" << endl;
					return;
				}
			}
			if (course->getMaxNumberOfStudents() == course->getNumberOfStudentsRegistered()) {
				cout << "This course has maximum number of students" << endl;
				return;
			}
			bool prerequisitesCompleted = true;
			for (auto crs : course->getPrerequisite()) {
				bool completed = false;
				for (auto finishedCrs : FinishedCourses_code) {
					if (finishedCrs == crs) {
						completed = true;
						break;
					}
				}
				if (!completed) {
					prerequisitesCompleted = false;
					break;
				}
			}

			if (prerequisitesCompleted) {


				CoursesInProgress.push_back(course->getCourseCode());
				course->AddStudent_toCourse(Id);
				cout << "Successfully registered for course: " << course->getCourseName() << endl;
				course->incrementNumberOfStudentRegisterd();
				a1.SaveStudents();
			}
			else {
				cout << "Error: You have not completed the prerequisites for this course." << endl;
				return;
			}

			saveInProgCourses();

		}
}
void Student::ViewYourCourses() {
	unordered_map<string, Courses*>allcrs = a1.getCourses();
	cout << "Finished courses:" << endl;
	if (FinishedCourses_code.empty()) {
		cout << "You haven't completed any courses yet." << endl;
	}
	else {

		for (auto& course : FinishedCourses_code) {
			cout << allcrs[course]->getCourseName() << endl;
		}
	}
	cout << endl << "Courses in progress:" << endl;
	if (CoursesInProgress.empty()) {
		cout << "You haven't registered for any courses yet." << endl;
	}
	else {
		for (auto& course : CoursesInProgress) {
			cout << allcrs[course]->getCourseName() << endl;
		}
	}
}
void Student::GradesAndGPA() {
	double totalGradePoints = 0.0;
	int totalCredits = 0;

	unordered_map<string, Courses*>allcrs = a1.getCourses();
	for (auto crs : FinishedCourses_code) {
		cout << "your grade in course  " << allcrs[crs]->getCourseName() << " is : " << Grades[allcrs[crs]->getCourseCode()] << endl;
		totalGradePoints += Grades[allcrs[crs]->getCourseCode()] * allcrs[crs]->getHours();
		totalCredits += allcrs[crs]->getHours();
	}
	if (totalCredits == 0) {
		cout << "You haven't completed any courses yet." << endl;
	}
	cout << "Your cumulative GPA is : " << (totalGradePoints / totalCredits);

}
void Student::Edit() {
	int choice;


	cout << "What would you like to edit?" << endl;
	cout << "1. Name" << endl;
	cout << "2. Email" << endl;
	cout << "3. Password" << endl;
	cin >> choice;

	switch (choice) {
	case 1:
		cout << "Enter new name: ";
		cin >> Name;
		cout << "Name updated successfully." << endl;
		break;
	case 2:
		cout << "Enter new email: ";
		cin >> Email;
		cout << "Email updated successfully." << endl;
		break;
	case 3:
		cout << "Enter new password: ";
		cin >> Password;
		cout << "Password updated successfully." << endl;
		break;
	default:
		cout << "Invalid choice. Please try again." << endl;
		Edit();

	}
	a1.changeStudent(Id, Email, Password, Name);
	a1.SaveStudents();
}
Student* Student::LogIn() {

	bool login = false;
	do {
		string email, password;
		cout << "Please Enter Your Email : ";
		cin >> email;
		cout << endl;
		cout << "PLease Enter Your Password : ";
		cin >> password;
		map<int, Student*> map1 = a1.getStudents();

		for (auto stud : map1) {

			if (stud.second->getEmail() == email && stud.second->getPassword() == password) {
				return stud.second;
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
void Student::saveInProgCourses() {
	fstream file;
	file.open("temp.txt", fstream::out);

	for (auto element : a1.getStudents()) {
		file << element.first << " ";

		for (auto inprogcourses : element.second->getCoursesInProgress()) {
			file << inprogcourses << " ";
			// save the course code
		}
		file << endl;
	}
	file.close();


}
