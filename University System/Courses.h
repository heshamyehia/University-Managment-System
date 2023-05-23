#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;


class Courses
{
	//Variables
private:
	string Course_Name;
	string Course_Code;
	string Instructor_Name;
	int MaxNumberOfStudents;
	int Hours;
	bool Requirement;
	vector<string> Prerequisites_Courses_Code;
	int NumberOfStudentsRegistered = 0;
	vector<int> StudentsEnrolled;




public:                                                       //Constructors
	Courses();
	Courses(string coursename, string coursecode, string instname, int maxstud, int hours, bool req);
	Courses(string name);


	//Setters
	void setCourseName(string name);
	void setCourseCode(string code);
	void setInstructorName(string instName);
	void setMaxNumberOfStudents(int maxStud);
	void setHours(int hours);
	void setRequirement(bool requirement);
	void setPrerequisite(vector<string> prerequisite);
	void setStudentsEnrolled(vector<int>);



	//Getters
	string getCourseName();
	string getCourseCode();
	string getInstructorName();
	int getMaxNumberOfStudents();
	int getHours();
	int getNumberOfStudentsRegistered();
	bool getRequirement();
	vector<string> getPrerequisite();
	vector<int> getStudentsenrolled();


	//Function
	void incrementNumberOfStudentRegisterd();
	void AddStudent_toCourse(int id);

	//~Courses();
};




