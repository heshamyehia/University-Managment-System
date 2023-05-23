#include <iostream>
#include"Student.h" 
#include<string>
#include<fstream> 
#include"Admin.h"
#include <Windows.h>


using namespace std;




int main() {

	HWND consoleWindow = GetConsoleWindow();
	bool TryAgain = false;
	Student* student{};
	Admin admin;
	Courses c1;



	do {

		cout << "Do you want to log in as a student or an admin?" << endl;
		cout << "Press 1 for student , or 2 for admin" << endl;

		string LogAns;
		cin >> LogAns;


		if (LogAns == "1") {
			TryAgain = true;
			student = student->LogIn();
			cout << "Welcome To Your Account " << student->getName() << "!" << endl;
			cout << "-------------------------------------------------------------------------------------" << endl;

			string BackToMenu = "B";

			string answer;
			while (BackToMenu == "B" || BackToMenu == "b")
			{
				cout << "1. View List for all available courses " << endl;
				cout << "2. Filter Courses " << endl;
				cout << "3. View Details of a specefic course " << endl;
				cout << "4. Register for a course " << endl;
				cout << "5. View all your courses " << endl;
				cout << "6. View your courses grades and cumulative GPA " << endl;
				cout << "7. Edit your data" << endl;
				cout << "8. Exit and Save Changes" << endl;
				cin >> answer;
				if (answer == "1") {
					student->ViewList();
					cout << endl << "press B to back to menu" << endl;
					cin >> BackToMenu;
					cout << "-------------------------------------------------------------------------------------" << endl;
				}
				else if (answer == "2") {
					student->FilterCourses();
					cout << endl << "press B to back to menu" << endl;
					cin >> BackToMenu;
					cout << "-------------------------------------------------------------------------------------" << endl;
				}

				else if (answer == "3") {
					student->ViewDetails();
					cout << endl << "press B to back to menu" << endl;
					cin >> BackToMenu;
					cout << "-------------------------------------------------------------------------------------" << endl;
				}

				else if (answer == "4") {
					student->Register();
					cout << endl << "press B to back to menu" << endl;
					cin >> BackToMenu;
					cout << "-------------------------------------------------------------------------------------" << endl;
				}

				else if (answer == "5") {
					student->ViewYourCourses();
					cout << endl << "press B to back to menu" << endl;
					cin >> BackToMenu;
					cout << "-------------------------------------------------------------------------------------" << endl;
				}

				else if (answer == "6") {
					student->GradesAndGPA();
					cout << endl << "press B to back to menu" << endl;
					cin >> BackToMenu;
					cout << "-------------------------------------------------------------------------------------" << endl;
				}

				else if (answer == "7") {
					student->Edit();
					cout << endl << "press B to back to menu" << endl;
					cin >> BackToMenu;
					cout << "-------------------------------------------------------------------------------------" << endl;
				}

				else if (answer == "8") {

					admin.SaveStudentsInProgressCourses(LogAns);
					// Close the console window using Windows API
					PostMessage(consoleWindow, WM_CLOSE, 0, 0);
					return 0; // Terminate the program
				}

				else {
					cout << "Invalid Number , Please Try Again..." << endl;
					cout<< "-------------------------------------------------------------------------------------" << endl;
				}
			}
		}

		else if (LogAns == "2") {
			TryAgain = true;

			Admin a1 = admin.LogIn();
			cout << "Welcome To Your Account " << a1.getName() << "!" << endl;
			cout << "-------------------------------------------------------------------------------------" << endl;


			string BackToMenu = "B";

			string answer;
			while (BackToMenu == "B" || BackToMenu == "b")
			{
				cout << "1. Add new student " << endl;
				cout << "2. Add new course " << endl;
				cout << "3. Add course's prerequisites " << endl;
				cout << "4. Display students in a specefic course " << endl;
				cout << "5. Add grades to a student " << endl;
				cout << "6. View list of all courses " << endl;
				cout << "7. Edit course" << endl;
				cout << "8. Calculate Average Grades of All Courses" << endl;
				cout << "9. Maximum and Minimum Grades" << endl;
				cout << "10.Success Rate Of Each CourseH" << endl;
				cout << "11. Exit and Save Changes" << endl;
				
				cin >> answer;

				if (answer == "1") {
					admin.AddStudent();
					cout << endl << "press B to back to menu" << endl;
					cin >> BackToMenu;
					cout << "-------------------------------------------------------------------------------------" << endl;
				}

				else if (answer == "2") {
					admin.AddCourse();
					cout << endl << "press B to back to menu" << endl;
					cin >> BackToMenu;
					cout << "-------------------------------------------------------------------------------------" << endl;
				}

				else if (answer == "3") {
					admin.AddPrerequisites();
					cout << endl << "press B to back to menu" << endl;
					cin >> BackToMenu;
					cout << "-------------------------------------------------------------------------------------" << endl;

				}
				else if (answer == "4") {
					admin.displaystuds();

					cout << "-------------------------------------------------------------------------------------" << endl;

					cout << endl << "press B to back to menu" << endl;
					cin >> BackToMenu;
					cout << "-------------------------------------------------------------------------------------" << endl;

				}

				else if (answer == "5") {
					admin.addgrades();
					cout << endl << "press B to back to menu" << endl;
					cin >> BackToMenu;
					cout << "-------------------------------------------------------------------------------------" << endl;

				}
				else if (answer == "6") {
					admin.ViewListofallCourses();
					cout << endl << "press B to back to menu" << endl;
					cin >> BackToMenu;
					cout << "-------------------------------------------------------------------------------------" << endl;

				}
				else if (answer == "7") {
					admin.editcourse();
					cout << endl << "press B to back to menu" << endl;
					cin >> BackToMenu;
					cout << "-------------------------------------------------------------------------------------" << endl;

				}
				else if (answer == "8") {
					admin.CalcAvg();
					cout << endl << "press B to back to menu" << endl;
					cin >> BackToMenu;
					cout << "-------------------------------------------------------------------------------------" << endl;
				}

				else if (answer == "9") {
					admin.maxmin();
					cout << endl << "press B to back to menu" << endl;
					cin >> BackToMenu;
					cout << "-------------------------------------------------------------------------------------" << endl;
				}
				else if (answer == "10") {
					admin.successrate();
					cout << endl << "press B to back to menu" << endl;
					cin >> BackToMenu;
					cout << "-------------------------------------------------------------------------------------" << endl;
				}

				else if (answer == "11") {

					// Close the console window using Windows API

					admin.SaveStudents();
					admin.SaveCourses();
					admin.SaveGrades();
					admin.SavePrerequisite();
					admin.SaveStudentsEnrolled();
					admin.SaveStudentsFinishedCourses();
					admin.SaveStudentsInProgressCourses(LogAns);

					PostMessage(consoleWindow, WM_CLOSE, 0, 0);
					return 0; // Terminate the program
				}
				else {
					cout << "Invalid Number , Please Try Again..." << endl;
					cout<< "-------------------------------------------------------------------------------------" << endl;

				}
			}
		}
		

		else
			cout << "Invalid number,Please try again" << endl;

	}

	while (TryAgain == false);



	return 0;

}