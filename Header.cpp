#include "Header.h";

void AcademicSubjectEntry(AcademicSubject* as) {
    cout << "\tНазвание предмета: ";
    cin >> as->name;
    cout << "\tОценка: ";
    cin >> as->mark;
}

void SessionEntry(Session* session) {
    cout << "Введите количество предметов: ";
    cin >> session->subject_count;

    for (int i = 0; i < session->subject_count; i++) {
        AcademicSubject* as = &(session->academicSubjects[i]);

        cout << "Введите предмет №" << (i + 1) << endl;
        AcademicSubjectEntry(as);
    }

}

void StudentEntry(Student* s) {
    cout << "Введите ФИО: ";
    cin >> s->fio.surname;
    cin >> s->fio.name;
    cin >> s->fio.fathername;

    cout << "Введите пол (М/Ж)";
    cin >> s->sex;

    cout << "Введите Дату рождения (дд мм гггг): ";
    cin >> s->date_of_birth.day;
    cin >> s->date_of_birth.month;
    cin >> s->date_of_birth.year;

    cout << "Данные о Вузе: год поступления, Факультет, кафедра, группа, номер зачетки:" << endl;
    cin >> s->vuz.godpostup;
    cin >> s->vuz.faculty;
    cin >> s->vuz.kafedra;
    cin >> s->vuz.group;
    cin >> s->vuz.booknumber;

    cout << "Введите сессии." << endl;

    cout << "Введите количество сессий: ";
    cin >> s->session_count;

    for (int i2 = 0; i2 < s->session_count; i2++) {
        cout << "Введите предметы сессии №" << (i2 + 1) << endl;
        SessionEntry(&(s->sessions[i2]));
    }
}

void StudentsEntry(Student* (&d), int& n) {
    cout << "Введите количесвто студентов: ";
    cin >> n;

    d = new Student[n];
    for (int i = 0; i < n; i++)
        StudentEntry(&d[i]);
}

void ReadingStudents(Student* (&d), int& n, string fileName)
{
    ifstream reading(fileName);
    if (reading.is_open())
    {
        reading >> n;
        d = new Student[n];
        for (int i = 0; i < n; i++)
        {
            Student* s = &d[i];

            reading
                >> s->fio.surname
                >> s->fio.name
                >> s->fio.fathername
                >> s->sex
                >> s->date_of_birth.day
                >> s->date_of_birth.month
                >> s->date_of_birth.year
                >> s->vuz.godpostup
                >> s->vuz.faculty
                >> s->vuz.kafedra
                >> s->vuz.group
                >> s->vuz.booknumber
                >> s->session_count;
            for (int i2 = 0; i2 < s->session_count; i2++) {
                Session* ssn = &(s->sessions[i2]);

                reading >> ssn->subject_count;
                for (int i3 = 0; i3 < ssn->subject_count; i3++) {
                    AcademicSubject* as = &(ssn->academicSubjects[i3]);

                    reading >> as->name >> as->mark;
                }
            }
        }
        cout << "Данные прочтены." << endl;
    }
    else {
        cout << "Ошибка при открытии файла." << endl;
    }
    reading.close();
}

string DateToStr(DateOfBirth date) {
    return to_string(date.day) + "." + to_string(date.month) + "." + to_string(date.year);
}

string FioToStr(Fio fio) {
    return fio.surname + " " + fio.name + " " + fio.fathername;
}

void WritingStudents(Student* (&d), int n, string fileName)
{
    ofstream writing(fileName);
    if (writing.is_open())
    {
        writing << n << endl;
        for (int i = 0; i < n; i++)
        {
            Student* s = &d[i];

            writing
                << FioToStr(s->fio) << " " << s->sex << endl
                << s->date_of_birth.day << " " << s->date_of_birth.month << " " << s->date_of_birth.year << endl
                << s->vuz.godpostup << " " << s->vuz.faculty << " " << s->vuz.kafedra << " " << s->vuz.group << " " << s->vuz.booknumber << endl
                << s->session_count << endl;
            for (int i2 = 0; i2 < s->session_count; i2++) {
                Session* ssn = &(s->sessions[i2]);

                writing << ssn->subject_count << " ";
                for (int i3 = 0; i3 < ssn->subject_count; i3++) {
                    AcademicSubject* as = &(ssn->academicSubjects[i3]);

                    writing << as->name << " " << as->mark << " ";
                }
                writing << endl;
            }
        }
        cout << "Данные записаны." << endl;
    }
    else {
        cout << "Ошибка при открытии файла." << endl;
    }
    writing.close();
}

void Print(Student* (&d), int n) {
    for (int i = 0; i < n; i++) {
        Student* s = &d[i];

        cout << "Студент №" << (i + 1) << endl;
        cout << "ФИО " << FioToStr(s->fio) << " " << s->sex << endl;
        cout << "Дата рождения " << DateToStr(s->date_of_birth) << endl;
        cout << "Дата поступления " << s->vuz.godpostup << ", Факультет " << s->vuz.faculty << ", Кафедра " << s->vuz.kafedra
            << ", Группа " << s->vuz.group << ", Номер зачетки " << s->vuz.booknumber << endl;
        cout << "Оценки:\n";
        for (int i2 = 0; i2 < s->session_count; i2++) {
            Session* ssn = &(s->sessions[i2]);
            cout << "Сессия №" << (i2 + 1) << endl;
            for (int i3 = 0; i3 < ssn->subject_count; i3++) {
                AcademicSubject* as = &(ssn->academicSubjects[i3]);
                cout << "\tПредмет: " << as->name << ", Оценка: " << as->mark << endl;
            }
        }
        cout << endl;
    }
}

bool InputInt(string caption, int& value, int val_left, int val_right) {
    cout << caption;
    cin >> value;

    if (value < val_left || value > val_right) {
        cout << "Номер введен неверно." << endl;
        return false;
    }

    return true;
}

void Change(Student* (&d), int n) {
    int _n, sel;

    if (!InputInt("Введите номер элемента (от 1 до " + to_string(n) + "): ", _n, 1, n))
        return;

    if (!InputInt(string(
        "Что хотите изменить?\n") +
        "1. ФИО;\n" +
        "2. Пол;\n" +
        "3. Дату рождения;\n" +
        "4. Данные о вузе;\n" +
        "5. Сессию.\n" +
        ">",
        sel, 1, 5)
        )
        return;

    Student* s = &d[_n - 1];
    switch (sel)
    {
    case 1: {
        cout << "Текущее ФИО: " << FioToStr(s->fio) << endl;
        cout << "Введите новое ФИО: ";
        cin
            >> s->fio.surname
            >> s->fio.name
            >> s->fio.fathername;
        break;
    }
    case 2: {
        cout << "Текущий пол: " << s->sex << endl;
        cout << "Введите новый пол: ";
        cin >> s->sex;
        break;
    }
    case 3: {
        cout << "Текущая дата рождения: " << DateToStr(s->date_of_birth) << endl;
        cout << "Введите новую дату рождения: ";
        cin
            >> s->date_of_birth.day
            >> s->date_of_birth.month
            >> s->date_of_birth.year;
        break;
    }
    case 4: {
        cout << "Текущие данные о вузе: " << s->vuz.godpostup << ", " << s->vuz.faculty << ", " << s->vuz.kafedra << ", "
            << s->vuz.group << ", " << s->vuz.booknumber << endl;
        cout << "Введите Данные о Вузе: год поступления, Факультет, кафедра, группа, номер зачетки";
        cin
            >> s->vuz.godpostup
            >> s->vuz.faculty
            >> s->vuz.kafedra
            >> s->vuz.group
            >> s->vuz.booknumber;
        break;
    }
    case 5: {
        int sel1;

        if (!InputInt(string(
            "Что хотите сделать?\n") +
            "1. Изменить сессию;\n" +
            "2. Добавить сессию;\n" +
            ">",
            sel1, 1, 2))
            return;

        switch (sel1)
        {
        case 1: {
            int sel2, ssn_change;

            // ввод номера сессии
            if (!InputInt("Введите номер сессии (от 1 до " + to_string(s->session_count) + "): ", ssn_change, 1, s->session_count))
                return;

            Session* ssn = &(s->sessions[ssn_change - 1]);

            if (!InputInt(string(
                "Что хотите сделать в данной сессии?\n") +
                "1. Изменить предмет;\n" +
                "2. Добавить предмет;\n" +
                ">",
                sel2, 1, 2))
                return;

            switch (sel2)
            {
            case 1: {
                int as_change;

                // ввод номера предмета
                if (!InputInt("Введите номер предмета (от 1 до " + to_string(ssn->subject_count) + "): ", as_change, 1, ssn->subject_count))
                    return;

                // изменение предмета
                AcademicSubject* as = &(ssn->academicSubjects[as_change - 1]);
                cout << "Текущие данные о предмете: Название: " << as->name << "; Оценка: " << as->mark << endl;
                cout << "Введите новые данные о предмете:\n";
                AcademicSubjectEntry(as);

                break;
            }
            case 2: {
                // проверка возможности добавления информации
                if (ssn->subject_count == maxAcademicSubjects) {
                    cout
                        << "Лимит на добавления информации о предметах исчерпан." << endl
                        << "Данные не изменены." << endl;
                    return;
                }

                // добавление предмета
                AcademicSubject* as = &(ssn->academicSubjects[ssn->subject_count++]);
                cout << "Введите данные о предмете:\n";
                AcademicSubjectEntry(as);

                break;
            }
            }

            break;
        }
        case 2: {
            // проверка возможности добавления информации
            if (s->session_count == maxSessions) {
                cout
                    << "Лимит на добавления информации о сессиях исчерпан." << endl
                    << "Данные не изменены." << endl;
                return;
            }

            // добавление сессии
            int n_session = s->session_count++;
            cout << "Введите предметы сессии №" << (n_session + 1) << endl;
            SessionEntry(&(s->sessions[n_session]));

            break;
        }
        }


        break;
    }
    }
    cout << "Данные изменены" << endl;
}

void Copy(Student* (&d_d), Student* (&d_s), int n) {
    for (int i = 0; i < n; i++) {
        d_d[i] = d_s[i];
    }
}

void DeleteStudent(Student* (&d), int& n)
{
    int _n;

    if (!InputInt("Введите порядковый номер студента (от 1 до " + to_string(n) + ")", _n, 1, n))
        return;

    _n--;

    Student* buf = new Student[n];
    Copy(buf, d, n);
    d = new Student[n];
    for (int i = 0, q = 0; i < n; i++)
        if (i != _n)
            d[q++] = buf[i];
    n--;
    delete[] buf;

    cout << "Данные удалены." << endl;
}

void add(Student* (&d), int& n) {
    Student* buf;

    buf = new Student[n];
    Copy(buf, d, n);
    d = new Student[n + 1];
    Copy(d, buf, n);

    StudentEntry(&d[n]);
    n++;

    cout << endl << "Данные добавлены" << endl;

    delete[]buf;
}

void Variant57(Student* (&d), int n) {
    
}
