#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

struct Fio {
	string surname;     
	string name;        
	string fathername;  
};

struct DateOfBirth {
	int day;    
	int month;  
	int year;   
};


struct VUZ {
	int godpostup;      
	string faculty;     
	string kafedra;     
	string group;       
	string booknumber;  
};


struct AcademicSubject {
	string name;  
	int mark;     
};


const int maxAcademicSubjects = 10;


struct Session {
	AcademicSubject academicSubjects[maxAcademicSubjects]; 
	int subject_count;                                      
};


const int maxSessions = 9;


struct Student {
	Fio fio;                        
	char sex;                    
	DateOfBirth date_of_birth;      
	VUZ vuz;                        
	
	
	Session sessions[maxSessions];  
	int session_count;             
};

void AcademicSubjectEntry(AcademicSubject* as);
void SessionEntry(Session* session);
void StudentEntry(Student* d);
void StudentsEntry(Student* (&d), int& n);
void ReadingStudents(Student* (&d), int& n, string fileName);
string DateToStr(DateOfBirth date);
string FioToStr(Fio fio);
void WritingStudents(Student* (&d), int n, string fileName);
void Print(Student* (&d), int n);
bool InputInt(string caption, int& value, int val_left, int val_right);
void Change(Student* (&d), int n);
void Copy(Student* (&d_d), Student* (&d_s), int n);
void DeleteStudent(Student* (&d), int& n);
void add(Student* (&d), int& n);
void Variant57(Student* (&d), int n);
