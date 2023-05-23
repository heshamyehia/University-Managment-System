#include "Courses.h"
#include"Student.h"
#include"Admin.h"

//Constructor
Courses::Courses() {
	Course_Name = "";
	Course_Code = "";
	Instructor_Name = "";
	MaxNumberOfStudents = 0;
	Hours = 0;
	Requirement = false;
}

Courses::Courses(string coursename, string coursecode, string instname, int maxstud, int hours, bool req) {
	Course_Name = coursename;
	Course_Code = coursecode;
	Instructor_Name = instname;
	MaxNumberOfStudents = maxstud;
	Hours = hours;
	Requirement = req;

}
Courses::Courses(string name) {
	Course_Name = name;
	Course_Code = "";
	Instructor_Name = "";
	MaxNumberOfStudents = 0;
	Hours = 0;
	Requirement = false;

}

//Setters
void Courses::setCourseName(string name) {
	Course_Name = name;
}
void Courses::setCourseCode(string code) {
	Course_Code = code;
}
void Courses::setInstructorName(string instName) {
	Instructor_Name = instName;
}
void Courses::setMaxNumberOfStudents(int maxStud) {
	MaxNumberOfStudents = maxStud;
}
void Courses::setHours(int hours) {
	Hours = hours;
}
void Courses::setRequirement(bool requirement) {
	Requirement = requirement;
}

void Courses::setPrerequisite(vector<string> prerequisite) {
	Prerequisites_Courses_Code = prerequisite;

}
void Courses::setStudentsEnrolled(vector<int> stud) {
	StudentsEnrolled = stud;
}

//Getters
string Courses::getCourseName() {
	return Course_Name;
}
string Courses::getCourseCode() {
	return Course_Code;
}
string Courses::getInstructorName() {
	return Instructor_Name;
}
int Courses::getMaxNumberOfStudents() {
	return MaxNumberOfStudents;
}
int Courses::getHours() {
	return Hours;
}
int Courses::getNumberOfStudentsRegistered() {
	return NumberOfStudentsRegistered;
}
bool Courses::getRequirement() {
	return Requirement;
}
vector<string> Courses::getPrerequisite() {
	return Prerequisites_Courses_Code;
}
vector<int> Courses::getStudentsenrolled() {
	return StudentsEnrolled;
}

//Functions


void Courses::incrementNumberOfStudentRegisterd() {

	NumberOfStudentsRegistered++;

}

void Courses::AddStudent_toCourse(int id) {

	StudentsEnrolled.push_back(id);


}




