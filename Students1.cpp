#include "Header.h";

int Menu() {
	int statemenu;

	system("cls");
	cout
		<< "�������� ��������:" << endl
		<< "1. ���� ������ ��������" << endl
		<< "2. �������� ���� ���������" << endl
		<< "3. ��������� ������" << endl
		<< "4. �������� ������" << endl
		<< "5. ���������� ������" << endl
		<< "6. ���������� ������ � ����" << endl
		<< "0. �����" << endl
		<< ">";
	cin >> statemenu;

	return statemenu;
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	const string fileName = "students.txt";


	int students_count = 0;
	Student* students;

	while (true)
	{
		switch (Menu()) {
		case 0: {
			return 0;
		}
		case 1: {
			int actions;

			cout << "���� ������ �������(1) ��� �� �����(2): ";
			cin >> actions;

			switch (actions)
			{
			case 1: {
				system("cls");
				StudentsEntry(students, students_count);
				break;
			}
			case 2: {
				ReadingStudents(students, students_count, fileName);
				break;
			}
			default:
				cout << "������� ������ ����� ��������." << endl;
				break;
			}
			break;
		}
		case 2: {
			system("cls");
			if (students_count != 0) {
				Print(students, students_count);
			}
			else {
				cout << "������ �����" << endl;
			}
			break;
		}
		case 3: {
			system("cls");
			if (students_count != 0) {
				Change(students, students_count);
			}
			else {
				cout << "������ �����" << endl;
			}
			break;
		}
		case 4: {
			system("cls");
			if (students_count != 0) {
				DeleteStudent(students, students_count);
			}
			else {
				cout << "������ �����" << endl;
			}
			break;
		}
		case 5: {
			system("cls");
			if (students_count != 0) {
				add(students, students_count);
			}
			else {
				cout << "������ �����" << endl;
			}
			break;
		}
		case 6: {
			system("cls");
			if (students_count != 0) {
				WritingStudents(students, students_count, fileName);
			}
			else {
				cout << "������ �����" << endl;
			}
			break;
		}
		default: {
			cout << "������� ������ ����� �������� " << endl;
			system("cls");
			break;
		}
		}

		system("pause");
	}
}