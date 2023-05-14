#include <Windows.h>
#include <string>
#include <fstream>
#include <limits>
#include <iostream>

using namespace std;

struct Student
{
	char name[90]; // Ф.И.О
	int birth_day; // день рождения
	int birth_month; // месяц рождения
	int birth_year; // год рождения
	int admissionYear; // год поступления
	char faculty[10]; // факультет
	char department[10]; // кафедра
	char group[14]; // группа
	char recordBookNumber[10]; // номер зачетной книжки
	char subjects[2][8][50];
	int marks[2][8]; // оценки за предметы (2 сессии, 8 предметов)
};

bool isValidMark(int mark) {
	return mark >= 0 && mark <= 5;

}

void addStudent() {
	Student student;
	ofstream file("students.bin", ios::binary | ios::app);

	if (!file) {
		cout << "Ошибка открытия файла!" << endl;
		return;
	}

	cout << "Добавление студента в список: " << endl;
	cout << "Введите Ф.И.О. студента: ";
	cin.getline(student.name, 90);
	cout << "Введите дату рождения студента (ДД.ММ.ГГГГ): ";

	string birth_day, birth_month, birth_year;
	getline(cin, birth_day, '.');
	getline(cin, birth_month, '.');
	getline(cin, birth_year);

	student.birth_day = stoi(birth_day);
	student.birth_month = stoi(birth_month);
	student.birth_year = stoi(birth_year);

	cout << "Введите год поступления студента: ";
	cin >> student.admissionYear;
	cin.ignore();
	cout << "Введите факультет (институт): ";
	cin.getline(student.faculty, 10);
	cout << "Введите кафедру: ";
	cin.getline(student.department, 10);
	cout << "Введите группу: ";
	cin.getline(student.group, 14);
	cout << "Введите номер зачетной книжки: ";
	cin.getline(student.recordBookNumber, 10);

	// Присваиваем порядковый номер, равный номеру зачетной книжки
	string recordBookNumber = student.recordBookNumber;
	int studentNumber = stoi(recordBookNumber);

	for (int j = 0; j < 2; j++) {
		cout << "+---Сессия " << j + 1 << "---+" << endl;
		for (int k = 0; k < 8; k++) {
			cout << "Название предмета " << k + 1 << ": ";
			cin.ignore();
			cin.getline(student.subjects[j][k], 50);

			bool validMark = false;
			int mark;
			while (!validMark) {
				cout << "Оценка по предмету " << k + 1 << ": ";
				cin >> mark;
				if (cin.fail() || !isValidMark(mark)) {
					cout << "Оценка должна быть числом в диапазоне от 0 до 10. Пожалуйста, введите оценку заново." << endl;
					cin.clear();
					cin.ignore();
				}
				else {
					validMark = true;
				}
			}

			student.marks[j][k] = mark;
			cin.ignore();
		}
	}

	file.write(reinterpret_cast<char*>(&student), sizeof(Student));
	file.close();

	cout << "Студент успешно добавлен!" << endl;
}

void showStudent() {
	ifstream file("students.bin", ios::binary | ios::in);

	if (!file) {
		cout << "Ошибка открытия файла!" << endl;
		return;
	}

	cout << "Введите номер зачетной книжки студента: ";
	string recordBookNumber;
	cin >> recordBookNumber;
	cin.ignore();

	Student student;
	bool found = false;
	file.clear();

	while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
		if (recordBookNumber == student.recordBookNumber) {
			cout << "Найден студент с номером зачетной книжки: " << recordBookNumber << endl;
			cout << "Ф.И.О. студента: " << student.name << endl;
			cout << "Дата рождения: " << student.birth_day << "." << student.birth_month << "." << student.birth_year << endl;
			cout << "Год поступления: " << student.admissionYear << endl;
			cout << "Факультет: " << student.faculty << endl;
			cout << "Кафедра: " << student.department << endl;
			cout << "Группа: " << student.group << endl;

			cout << "Оценки за предметы:" << endl;
			for (int i = 0; i < 2; i++) {
				cout << "+---Сессия " << i + 1 << "---+" << endl;
				for (int j = 0; j < 8; j++) {
					cout << "Предмет: " << student.subjects[i][j] << ", Оценка: " << student.marks[i][j] << endl;
				}
			}

			found = true;
			break;
		}
	}

	file.close();
	if (!found) {
		cout << "Студент с номером зачетной книжки " << recordBookNumber << " не найден." << endl;
	}
}

void updateStudent() {
	fstream file("students.bin", ios::binary | ios::in | ios::out | ios::ate);

	if (!file) {
		cout <<
			"Ошибка открытия файла!" << endl;
		return;
	}

	cout << "Введите номер зачетной книжки студента, данные которого нужно изменить: ";
	string recordBookNumber;
	cin >> recordBookNumber;

	Student student;
	bool found = false;

	while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
		if (recordBookNumber == student.recordBookNumber) {
			cout << "Найден студент с номером зачетной книжки: " << recordBookNumber << endl;

			cout << "Введите новые данные студента: " << endl;
			cout << "Введите Ф.И.О. студента: ";
			cin.ignore();
			cin.getline(student.name, 90);
			cout << "Введите дату рождения студента (ДД.ММ.ГГГГ): ";

			string birth_day, birth_month, birth_year;
			getline(cin, birth_day, '.');
			getline(cin, birth_month, '.');
			getline(cin, birth_year);

			student.birth_day = stoi(birth_day);
			student.birth_month = stoi(birth_month);
			student.birth_year = stoi(birth_year);

			cout << "Введите год поступления студента: ";
			cin >> student.admissionYear;
			cin.ignore();
			cout << "Введите факультет (институт): ";
			cin.getline(student.faculty, 50);
			cout << "Введите кафедру: ";
			cin.getline(student.department, 30);
			cout << "Введите группу: ";
			cin.getline(student.group, 14);

			for (int j = 0; j < 2; j++) {
				cout << "+---Сессия " << j + 1 << "---+" << endl;
				for (int k = 0; k < 8; k++) {
					cout << "Название предмета " << k + 1 << ": ";
					cin >> student.subjects[j][k];
					cout << "Оценка по предмету " << k + 1 << ": ";
					cin >> student.marks[j][k];
					cin.ignore();
				}
			}

			// Возвращаемся на позицию записи и перезаписываем данные студента
			file.seekp(-static_cast<int>(sizeof(Student)), ios::cur);
			file.write(reinterpret_cast<char*>(&student), sizeof(Student));

			cout << "Данные студента успешно обновлены!" << endl;

			found = true;
			break;
		}
	}

	file.close();

	if (!found) {
		cout << "Студент с номером зачетной книжки " << recordBookNumber << " не найден." << endl;
	}
}

void deleteStudent() {
	ifstream fileIn("students.bin", ios::binary);
	ofstream fileOut("temp.bin", ios::binary);

	if (!fileIn || !fileOut) {
		cout << "Ошибка открытия файла!" << endl;
		return;
	}

	cout << "Введите номер зачетной книжки студента, данные которого нужно удалить: ";
	string recordBookNumber;
	cin >> recordBookNumber;
	cin.ignore();

	Student student;
	bool found = false;

	while (fileIn.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
		if (recordBookNumber != student.recordBookNumber) {
			// Записываем данные студента, кроме удаляемого, во временный файл
			fileOut.write(reinterpret_cast<char*>(&student), sizeof(Student));
		}
		else {
			found = true;
		}
	}

	fileIn.close();
	fileOut.close();

	// Удаляем исходный файл
	remove("students.bin");
	// Переименовываем временный файл в исходное имя
	rename("temp.bin", "students.bin");

	if (found) {
		cout << "Данные студента успешно удалены!" << endl;
	}
	else {
		cout << "Студент с номером зачетной книжки " << recordBookNumber << " не найден." << endl;
	}
}

void ClearConsole() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

bool isValidMark(int mark);
void addStudent();
void showStudent();
void updateStudent();
void deleteStudent();
void ClearConsole();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int choice;
	do {
		ClearConsole();
		cout << "========== Меню ==========" << endl;
		cout << "1. Ввести данные студента" << endl;
		cout << "2. Вывести данные студента" << endl;
		cout << "3. Изменить данные студента" << endl;
		cout << "4. Удалить данные студента" << endl;
		cout << "0. Выход" << endl;
		cout << "Выберите пункт: ";
		cin >> choice;

		switch (choice) {
		case 0:
			cout << "Программа завершена." << endl;
			break;
		case 1:
			ClearConsole();
			cout << "Вы выбрали ввод данных студента." << endl;
			cin.ignore();
			addStudent();
			break;
		case 2:
			ClearConsole();
			cout << "Вы выбрали вывод данных студента." << endl;
			cin.ignore();
			showStudent();
			break;
		case 3:
			ClearConsole();
			cout << "Вы выбрали изменение данных студента." << endl;
			cin.ignore();
			updateStudent();
			break;
		case 4:
			ClearConsole();
			cout << "Вы выбрали удаление данных студента:" << endl;
			deleteStudent();
			break;
		default:
			ClearConsole();
			cout << "Некорректный выбор. Попробуйте снова." << endl;
			break;
		}

		cout << "Нажмите Enter, чтобы продолжить...";
		cin.ignore();
		cin.get();
	} while (choice != 0);
	return 0;
}