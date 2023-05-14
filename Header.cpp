#include "Header.h";

void AcademicSubjectEntry(AcademicSubject* as) {
    cout << "\t�������� ��������: ";
    cin >> as->name;
    cout << "\t������: ";
    cin >> as->mark;
}

void SessionEntry(Session* session) {
    cout << "������� ���������� ���������: ";
    cin >> session->subject_count;

    for (int i = 0; i < session->subject_count; i++) {
        AcademicSubject* as = &(session->academicSubjects[i]);

        cout << "������� ������� �" << (i + 1) << endl;
        AcademicSubjectEntry(as);
    }

}

void StudentEntry(Student* s) {
    cout << "������� ���: ";
    cin >> s->fio.surname;
    cin >> s->fio.name;
    cin >> s->fio.fathername;

    cout << "������� ��� (�/�)";
    cin >> s->sex;

    cout << "������� ���� �������� (�� �� ����): ";
    cin >> s->date_of_birth.day;
    cin >> s->date_of_birth.month;
    cin >> s->date_of_birth.year;

    cout << "������ � ����: ��� �����������, ���������, �������, ������, ����� �������:" << endl;
    cin >> s->vuz.godpostup;
    cin >> s->vuz.faculty;
    cin >> s->vuz.kafedra;
    cin >> s->vuz.group;
    cin >> s->vuz.booknumber;

    cout << "������� ������." << endl;

    cout << "������� ���������� ������: ";
    cin >> s->session_count;

    for (int i2 = 0; i2 < s->session_count; i2++) {
        cout << "������� �������� ������ �" << (i2 + 1) << endl;
        SessionEntry(&(s->sessions[i2]));
    }
}

void StudentsEntry(Student* (&d), int& n) {
    cout << "������� ���������� ���������: ";
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
        cout << "������ ��������." << endl;
    }
    else {
        cout << "������ ��� �������� �����." << endl;
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
        cout << "������ ��������." << endl;
    }
    else {
        cout << "������ ��� �������� �����." << endl;
    }
    writing.close();
}

void Print(Student* (&d), int n) {
    for (int i = 0; i < n; i++) {
        Student* s = &d[i];

        cout << "������� �" << (i + 1) << endl;
        cout << "��� " << FioToStr(s->fio) << " " << s->sex << endl;
        cout << "���� �������� " << DateToStr(s->date_of_birth) << endl;
        cout << "���� ����������� " << s->vuz.godpostup << ", ��������� " << s->vuz.faculty << ", ������� " << s->vuz.kafedra
            << ", ������ " << s->vuz.group << ", ����� ������� " << s->vuz.booknumber << endl;
        cout << "������:\n";
        for (int i2 = 0; i2 < s->session_count; i2++) {
            Session* ssn = &(s->sessions[i2]);
            cout << "������ �" << (i2 + 1) << endl;
            for (int i3 = 0; i3 < ssn->subject_count; i3++) {
                AcademicSubject* as = &(ssn->academicSubjects[i3]);
                cout << "\t�������: " << as->name << ", ������: " << as->mark << endl;
            }
        }
        cout << endl;
    }
}

bool InputInt(string caption, int& value, int val_left, int val_right) {
    cout << caption;
    cin >> value;

    if (value < val_left || value > val_right) {
        cout << "����� ������ �������." << endl;
        return false;
    }

    return true;
}

void Change(Student* (&d), int n) {
    int _n, sel;

    if (!InputInt("������� ����� �������� (�� 1 �� " + to_string(n) + "): ", _n, 1, n))
        return;

    if (!InputInt(string(
        "��� ������ ��������?\n") +
        "1. ���;\n" +
        "2. ���;\n" +
        "3. ���� ��������;\n" +
        "4. ������ � ����;\n" +
        "5. ������.\n" +
        ">",
        sel, 1, 5)
        )
        return;

    Student* s = &d[_n - 1];
    switch (sel)
    {
    case 1: {
        cout << "������� ���: " << FioToStr(s->fio) << endl;
        cout << "������� ����� ���: ";
        cin
            >> s->fio.surname
            >> s->fio.name
            >> s->fio.fathername;
        break;
    }
    case 2: {
        cout << "������� ���: " << s->sex << endl;
        cout << "������� ����� ���: ";
        cin >> s->sex;
        break;
    }
    case 3: {
        cout << "������� ���� ��������: " << DateToStr(s->date_of_birth) << endl;
        cout << "������� ����� ���� ��������: ";
        cin
            >> s->date_of_birth.day
            >> s->date_of_birth.month
            >> s->date_of_birth.year;
        break;
    }
    case 4: {
        cout << "������� ������ � ����: " << s->vuz.godpostup << ", " << s->vuz.faculty << ", " << s->vuz.kafedra << ", "
            << s->vuz.group << ", " << s->vuz.booknumber << endl;
        cout << "������� ������ � ����: ��� �����������, ���������, �������, ������, ����� �������";
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
            "��� ������ �������?\n") +
            "1. �������� ������;\n" +
            "2. �������� ������;\n" +
            ">",
            sel1, 1, 2))
            return;

        switch (sel1)
        {
        case 1: {
            int sel2, ssn_change;

            // ���� ������ ������
            if (!InputInt("������� ����� ������ (�� 1 �� " + to_string(s->session_count) + "): ", ssn_change, 1, s->session_count))
                return;

            Session* ssn = &(s->sessions[ssn_change - 1]);

            if (!InputInt(string(
                "��� ������ ������� � ������ ������?\n") +
                "1. �������� �������;\n" +
                "2. �������� �������;\n" +
                ">",
                sel2, 1, 2))
                return;

            switch (sel2)
            {
            case 1: {
                int as_change;

                // ���� ������ ��������
                if (!InputInt("������� ����� �������� (�� 1 �� " + to_string(ssn->subject_count) + "): ", as_change, 1, ssn->subject_count))
                    return;

                // ��������� ��������
                AcademicSubject* as = &(ssn->academicSubjects[as_change - 1]);
                cout << "������� ������ � ��������: ��������: " << as->name << "; ������: " << as->mark << endl;
                cout << "������� ����� ������ � ��������:\n";
                AcademicSubjectEntry(as);

                break;
            }
            case 2: {
                // �������� ����������� ���������� ����������
                if (ssn->subject_count == maxAcademicSubjects) {
                    cout
                        << "����� �� ���������� ���������� � ��������� ��������." << endl
                        << "������ �� ��������." << endl;
                    return;
                }

                // ���������� ��������
                AcademicSubject* as = &(ssn->academicSubjects[ssn->subject_count++]);
                cout << "������� ������ � ��������:\n";
                AcademicSubjectEntry(as);

                break;
            }
            }

            break;
        }
        case 2: {
            // �������� ����������� ���������� ����������
            if (s->session_count == maxSessions) {
                cout
                    << "����� �� ���������� ���������� � ������� ��������." << endl
                    << "������ �� ��������." << endl;
                return;
            }

            // ���������� ������
            int n_session = s->session_count++;
            cout << "������� �������� ������ �" << (n_session + 1) << endl;
            SessionEntry(&(s->sessions[n_session]));

            break;
        }
        }


        break;
    }
    }
    cout << "������ ��������" << endl;
}

void Copy(Student* (&d_d), Student* (&d_s), int n) {
    for (int i = 0; i < n; i++) {
        d_d[i] = d_s[i];
    }
}

void DeleteStudent(Student* (&d), int& n)
{
    int _n;

    if (!InputInt("������� ���������� ����� �������� (�� 1 �� " + to_string(n) + ")", _n, 1, n))
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

    cout << "������ �������." << endl;
}

void add(Student* (&d), int& n) {
    Student* buf;

    buf = new Student[n];
    Copy(buf, d, n);
    d = new Student[n + 1];
    Copy(d, buf, n);

    StudentEntry(&d[n]);
    n++;

    cout << endl << "������ ���������" << endl;

    delete[]buf;
}

void Variant57(Student* (&d), int n) {
    
}
