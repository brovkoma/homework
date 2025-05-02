#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

struct date {//дата
	int dd, mm, yy;
};

bool operator == (date x, date y) { // проверка двух дат на равенство
	return (x.dd == y.dd && x.mm == y.mm && x.yy == y.yy);
}

bool operator != (date x, date y) {
	return !(x == y);
}

struct people {//данные о человеке
	string Surname; //фамилия
	string job; //должность
	date DateOfBirth; //дата рождения
	int experience; //стаж работы
	int Salary; //зарплата
};

bool operator == (people x, people y) {
	return (x.Surname == y.Surname && x.job == y.job && x.DateOfBirth == y.DateOfBirth
		&& x.experience == y.experience && x.Salary == y.Salary);
}

void printPeople(people p) {
	date d = p.DateOfBirth;
	cout << p.Surname << ' ' << p.job << ' ' << d.dd / 10 << d.dd % 10 << '.' << d.mm / 10 << d.mm % 10 << '.' << d.yy <<
		' ' << p.experience << ' ' << p.Salary << endl;
}

date Str_to_Date(string str) {//из строки в дату
	date x;
	string temp = str.substr(0, 2);//день
	x.dd = atoi(temp.c_str());
	temp = str.substr(3, 2);//месяц
	x.mm = atoi(temp.c_str());
	temp = str.substr(6, 4);//год
	x.yy = atoi(temp.c_str());
	return x;
}

ifstream in("input.txt");

const int M = 30;

people* a[M];

int main()
{
	SetConsoleCP(1251);
	setlocale(LC_ALL, "rus");

	while (in.peek() != EOF) {
		people p;
		string d;
		in >> p.Surname >> p.job >> d >> p.experience >> p.Salary;
		p.DateOfBirth = Str_to_Date(d);

		int hash = p.DateOfBirth.yy % M; // хэширование методом деления по году рождения

		while (a[hash]) { // пока текущая ячейка занята, увеличиваем номер ячейки
			hash = (hash + 1) % M;
		}

		a[hash] = new people(p);
	}

	cout << "Хэш-таблица:" << endl;

	for (int i = 0; i < M; i++) {
		cout << i << ": ";

		if (a[i]) {
			printPeople(*a[i]);
		}
		else {
			cout << "NULL" << endl;
		}
	}

	cout << endl;

	while (true) {
		cout << "Введите тип операции:" << endl;
		cout << "1 - вставить сотрудника в таблицу" << endl;
		cout << "2 - найти сотрудника по фамилии и дате рождения" << endl;
		cout << "3 - вывод хэш-таблицы" << endl;

		int type;
		cin >> type;

		if (type == 1) {
			cout << "Введите данные о сотруднике\nПример: Иванов разработчик 24.12.1998 5 60000" << endl;

			people p;
			string d;
			cin >> p.Surname >> p.job >> d >> p.experience >> p.Salary;
			p.DateOfBirth = Str_to_Date(d);

			int hash = p.DateOfBirth.yy % M;

			while (a[hash]) { // пока текущая ячейка занята, увеличиваем номер ячейки
				hash = (hash + 1) % M;
			}

			a[hash] = new people(p);

			cout << "Сотрудник добавлен в ячейку " << hash << endl;
		}
		else if (type == 2) {
			cout << "Введите фамилию и дату рождения" << endl;

			string surname, dateString;
			cin >> surname >> dateString;

			date dateOfBirth = Str_to_Date(dateString);

			int hash = dateOfBirth.yy % M;

			while (a[hash] && (a[hash]->Surname != surname || a[hash]->DateOfBirth != dateOfBirth)) {
				hash = (hash + 1) % M;
			}

			if (a[hash]) {
				cout << "Найден сотрудник: ";
				printPeople(*a[hash]);
			}
			else {
				cout << "Сотрудник не найден" << endl;
			}
		}
		else if (type == 3) {
			cout << "Хэш-таблица:" << endl;

			for (int i = 0; i < M; i++) {
				cout << i << ": ";

				if (a[i]) {
					printPeople(*a[i]);
				}
				else {
					cout << "NULL" << endl;
				}
			}
		}
		else {
			cout << "Некорректная операция" << endl;
		}

		cout << endl;
	}
}
