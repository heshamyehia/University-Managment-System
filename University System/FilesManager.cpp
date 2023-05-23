#include"FilesManager.h"

vector<string> FilesManager::splitLine(string line) {
    vector<string> values;
    stringstream s_stream(line);
    while (s_stream.good()) {
        string substr;
        getline(s_stream, substr, ',');
        values.push_back(substr);
    }
    return values;
}

vector<int> FilesManager::splitLineToInt(string line) {
    vector<int> values;
    stringstream s_stream(line);
    while (s_stream.good()) {
        string substr;
        int value = 0;
        getline(s_stream, substr, ',');
        stringstream convert(substr);
        if (!(convert >> value)) {
            // Handle error case when conversion fails
        }
        values.push_back(value);
    }
    return values;
}
//test
void FilesManager::getFilesData(vector<Courses>& crs, vector<Student>& stud) {

    fstream ReadStrings, ReadInts, ReadVector;                          // 2 files to read one for ints and one for strings
    ReadInts.open("Courses_ints.txt", ios::in);           //opening the files
    ReadStrings.open("Courses_Data.txt", ios::in);
    ReadVector.open("Courses_Vectors.txt", ios::in);
    string lineStrings, LineInts, LineVectors;                          //2 strings to store the file data in them
    Courses course;
    int size = 0;
    while (getline(ReadStrings, lineStrings) && getline(ReadInts, LineInts)) {
        if (lineStrings == "" || LineInts == "") break;

        vector<string> Strings_Values = splitLine(lineStrings);                        //2 vectors to store each data type
        vector<int> Int_values = splitLineToInt(LineInts);


        course.setCourseName(Strings_Values[0]);
        course.setCourseCode(Strings_Values[1]);
        course.setInstructorName(Strings_Values[2]);

        course.setHours(Int_values[0]);
        course.setMaxNumberOfStudents(Int_values[1]);
        course.setRequirement(Int_values[2]);

        size++;



        crs.push_back(course);
    }
    while (getline(ReadVector, LineVectors)) {
        if (LineVectors == "") break;

        vector<string> CoursesCodes = splitLine(LineVectors);
        vector<Courses> PreReq;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < CoursesCodes.size(); j++) {
                if (crs[i].getCourseCode() == CoursesCodes[j]) {
                    PreReq.push_back(crs[i]);
                }
            }
        }
        auto it = PreReq.begin();
        PreReq.erase(it);

        // set prerequisites for all courses with matching course codes
        for (int i = 0; i < size; i++) {
            if (PreReq.size() > 0 && crs[i].getCourseCode() == CoursesCodes[0]) {
                crs[i].setPrerequisite(PreReq);
            }
        }
    }
    ReadInts.close();
    ReadStrings.close();
    ReadVector.close();






    fstream ReadStudStrings, ReadStudInts, ReadFinishedCourses, ReadCoursesInProgress;                          // 2 files to read one for ints and one for strings
    ReadStudInts.open("Student_ints.txt", ios::in);           //opening the files
    ReadStudStrings.open("Student_Data.txt", ios::in);
    ReadFinishedCourses.open("FinishedCourses.txt", ios::in);
    string lineStudStrings, LineStudInts, lineStudFinished;                          //2 strings to store the file data in them
    Student student;
    while (getline(ReadStudStrings, lineStudStrings) && getline(ReadStudInts, LineStudInts)) {
        if (lineStudStrings == "" || LineStudInts == "") break;
        vector<string> Student_Strings_Values = splitLine(lineStudStrings);                        //2 vectors to store each data type
        vector<int> Student_Int_values = splitLineToInt(LineInts);
        student.setName(Student_Strings_Values[0]);
        student.setEmail(Student_Strings_Values[1]);
        student.setPassword(Student_Strings_Values[2]);
        student.setAcademicYear(Student_Strings_Values[3]);

        student.setId(Student_Int_values[0]);
        student.setMaximumHoursAllowed(Student_Int_values[1]);
        student.setGPA(Student_Int_values[2]);




        stud.push_back(student);
    }
    ReadStudInts.close();
    ReadStudStrings.close();





    unordered_map<int, vector<Courses>> finishedCoursesMap;

    while (getline(ReadFinishedCourses, lineStudFinished)) {
        if (lineStudFinished == "") break;

        vector<string> CoursesCodes = splitLine(lineStudFinished);
        int studentIndex = 0;

        for (auto& student : stud) {
            vector<Courses> Finished;

            for (int j = 0; j < CoursesCodes.size(); j++) {
                for (auto& course : crs) {
                    if (course.getCourseCode() == CoursesCodes[j]) {
                        Finished.push_back(course);
                        break;
                    }
                }
            }

            if (studentIndex < stud.size()) {
                stud[studentIndex].setFinishedCourses(Finished);
            }

            studentIndex++;
        }
    }





}