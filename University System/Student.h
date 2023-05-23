#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include"Courses.h"


using namespace std;


class Student
{                                                             //variables
private:
	string Name;
	string Email;
	string Password;
	string AcademicYear;
	int Id;
	int MaximumHoursAllowed;
	float GPA;
	vector<string> FinishedCourses_code;					// Code of finished courses
	vector<string>CoursesInProgress;						// Code of courses in progress
	static int StudentsCounter;
	map < string, float > Grades;


	//constructors

public:
	Student();
	Student(string name, string email, string password, string academicyear, int id, int MaxHours);

	//setters

	void setName(string name);
	void setEmail(string email);
	void setPassword(string password);
	void setAcademicYear(string academicyear);
	void setId(int id);
	void setMaximumHoursAllowed(int MaxHours);
	void setGPA(float gpa);
	void setGrades(string crscode, float grade);
	void setFinishedCourses(vector<string>);
	void setCoursesInProgress(vector <string>);
	void setGradeMap(string CrsCode, float grade);
	void setgrades(map < string, float >);


	void saveInProgCourses();



	//Getters

	string getName();
	string getEmail();
	string getPassword();
	string getAcademicYear();
	int getId();
	int getMaximumHoursAllowed();
	float getGPA();
	float getGrade(string courseCode);
	vector <string> getFinishedCourses();
	vector<string>getCoursesInProgress();
	map < string, float > getGradeMap();




	// Required Functions
	Student* LogIn();
	void ViewList();
	void FilterCourses();
	void ViewDetails();
	void Register();
	void ViewYourCourses();
	void GradesAndGPA();
	void Edit();


	//~Student();

	void SaveStudentsFinishedCourses();
	void SaveStudentsInProgressCourses();


};

