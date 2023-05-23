#include <map>
#include <unordered_map>
#include "Student.h"
#include<vector>


class Admin
{                                                                             //Variables
	string Name;
	string Password;
	map<int, Student*> students;
	unordered_map<string, Courses*> courses; // use unorderd map if files order bother you
	vector<Admin> admins;

public:

	//Constructors
	Admin();
	Admin(string, string);
	//Setters

	void setName(string name);
	void setPassword(string password);
	void setStudent(map<int, Student*>);
	void setCourse(unordered_map<string, Courses*>);


	//Getters
	string getName();
	string getPassword();
	map<int, Student*>getStudents();
	unordered_map<string, Courses*>getCourses();
	vector<Admin>getadmins();
	//Required Functions

	Admin LogIn();
	void AddStudent();
	void AddCourse();
	void AddPrerequisites();
	void displaystuds();
	void addgrades();
	void ViewListofallCourses();
	void editcourse();


	//Needed Function

	void editStudentData();
	void changeStudent(int id, string email, string password, string name);
	Student getStudent(int studid);
	bool studentexists(int studid);
	void addAdmin(string name, string pass);
	bool CourseExist(string id);
	bool CourseExistByName(string name);
	Student* getStudentByEmail(string email);
	void DisplayStudentData(int id);
	//load & save files

	void LoadStudents();
	void LoadGrades();
	void LoadCourses();
	void LoadFinishedCourses();
	void LoadStudentsInProgressCourses();
	void LoadStudentsEnrolled();
	void loadAdmin();
	void LoadPrerequisite();



	void SaveStudents();
	void SaveGrades();
	void SaveCourses();
	void SaveStudentsFinishedCourses();
	void SaveStudentsInProgressCourses(string);
	void SaveStudentsEnrolled();
	void saveAdmin();
	void SavePrerequisite();

	//~Admin(void);
	void saveInProgCourses();
	void saveEnrolled();

	void CalcAvg();
	void maxmin();
	void successrate();

};