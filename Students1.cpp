#include "Header.h";

int Menu() {
	int statemenu;

	system("cls");
	cout
		<< "Выберите действие:" << endl
		<< "1. Ввод данных студента" << endl
		<< "2. Показать всех студентов" << endl
		<< "3. Изменение данных" << endl
		<< "4. Удаление данных" << endl
		<< "5. Добавление данных" << endl
		<< "6. Сохранение данных в файл" << endl
		<< "0. Выход" << endl
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

			cout << "Ввод данных вручную(1) или из файла(2): ";
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
				cout << "Неверно введен номер действия." << endl;
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
				cout << "Данные пусты" << endl;
			}
			break;
		}
		case 3: {
			system("cls");
			if (students_count != 0) {
				Change(students, students_count);
			}
			else {
				cout << "Данные пусты" << endl;
			}
			break;
		}
		case 4: {
			system("cls");
			if (students_count != 0) {
				DeleteStudent(students, students_count);
			}
			else {
				cout << "Данные пусты" << endl;
			}
			break;
		}
		case 5: {
			system("cls");
			if (students_count != 0) {
				add(students, students_count);
			}
			else {
				cout << "Данные пусты" << endl;
			}
			break;
		}
		case 6: {
			system("cls");
			if (students_count != 0) {
				WritingStudents(students, students_count, fileName);
			}
			else {
				cout << "Данные пусты" << endl;
			}
			break;
		}
		default: {
			cout << "Неверно введен номер действия " << endl;
			system("cls");
			break;
		}
		}

		system("pause");
	}
}