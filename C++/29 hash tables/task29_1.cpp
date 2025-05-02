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

struct list {
	people inf;
	list* next;
	list* prev;
};

void push(list*& h, list*& t, people x) { //вставка элемента в конец списка
	list* r = new list; //создаем новый элемент
	r->inf = x;
	r->next = NULL; //всегда последний
	if (!h && !t) { //если список пуст
		r->prev = NULL; //первый элемент
		h = r; //это голова
	}
	else {
		t->next = r; //r - следующий для хвоста
		r->prev = t; //хвост - предыдущий для r
	}
	t = r; //r теперь хвост
}

void print(list* h, list* t) { //печать элементов списка
	list* p = h; //укзатель на голову
	while (p) { //пока не дошли до конца списка
		printPeople(p->inf);
		p = p->next; //переход к следующему элементу
	}
}

list* find(list* h, list* t, string surname, date dateOfBirth) {
	list* p = h; //укзатель на голову
	while (p) { //пока не дошли до конца списка
		if (p->inf.Surname == surname && p->inf.DateOfBirth == dateOfBirth) break; // если нашли, прекращаем цикл
		p = p->next; //переход к следующему элементу
	}
	return p; //возвращаем указатель
}

list* find(list* h, list* t, people x) {
	list* p = h; //укзатель на голову
	while (p) { //пока не дошли до конца списка
		if (p->inf == x) break; // если нашли, прекращаем цикл
		p = p->next; //переход к следующему элементу
	}
	return p; //возвращаем указатель
}

void insert_after(list*& h, list*& t, list* r, people y) { //вставляем после r
	list* p = new list; //создаем новый элемент
	p->inf = y;
	if (r == t) { //если вставляем после хвоста
		p->next = NULL; //вставляемый эл-т - последний
		p->prev = r; //вставляем после r
		r->next = p;
		t = p; //теперь хвост - p
	}
	else { //вставляем в середину списка
		r->next->prev = p; //для следующего за r эл-та предыдущий - p
		p->next = r->next; //следующий за p - следующий за r
		p->prev = r; //p вставляем после r
		r->next = p;
	}
}

void del_node(list*& h, list*& t, list* r) { //удаляем после r
	if (r == h && r == t) //единственный элемент списка
		h = t = NULL;
	else if (r == h) { //удаляем голову списка
		h = h->next; //сдвигаем голову
		h->prev = NULL;
	}
	else if (r == t) { //удаляем хвост списка
		t = t->prev; //сдвигаем хвост
		t->next = NULL;
	}
	else {
		r->next->prev = r->prev; //для следующего от r предыдущим становится r->prev
		r->prev->next = r->next; //для предыдущего от r следующим становится r->next
	}
	delete r; //удаляем r
}

void del_list(list*& h, list*& t) { //удаляем список
	while (h) { //пока список не пуст
		list* p = h; //указатель на голову
		h = h->next; //переносим голову
		h->prev = NULL; //обнуляем
		delete p; //удаляем p
	}
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

const int M = 7;

list* h[M];
list* t[M];

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

		push(h[hash], t[hash], p);
	}

	cout << "Хэш-таблица:" << endl;

	for (int i = 0; i < M; i++) {
		cout << i << ":" << endl;

		print(h[i], t[i]);
	}

	cout << endl;

	while (true) {
		cout << "Введите тип операции:" << endl;
		cout << "1 - вставить сотрудника в таблицу" << endl;
		cout << "2 - удалить сотрудника из таблицы" << endl;
		cout << "3 - найти сотрудника по фамилии и дате рождения" << endl;
		cout << "4 - вывод хэш-таблицы" << endl;

		int type;
		cin >> type;

		if (type == 1) {
			cout << "Введите данные о сотруднике\nПример: Иванов разработчик 24.12.1998 5 60000" << endl;

			people p;
			string d;
			cin >> p.Surname >> p.job >> d >> p.experience >> p.Salary;
			p.DateOfBirth = Str_to_Date(d);

			int hash = p.DateOfBirth.yy % M;

			push(h[hash], t[hash], p);
			cout << "Сотрудник добавлен в список " << hash << endl;
		}
		else if (type == 2) {
			cout << "Введите данные о сотруднике\nПример: Иванов разработчик 24.12.1998 5 60000" << endl;

			people p;
			string d;
			cin >> p.Surname >> p.job >> d >> p.experience >> p.Salary;
			p.DateOfBirth = Str_to_Date(d);

			int hash = p.DateOfBirth.yy % M;

			list* element = find(h[hash], t[hash], p);

			if (element) {
				del_node(h[hash], t[hash], element);

				cout << "Сотрудник удален из списка " << hash << endl;
			}
			else {
				cout << "Сотрудник не найден" << endl;
			}
		}
		else if (type == 3) {
			cout << "Введите фамилию и дату рождения" << endl;

			string surname, dateString;
			cin >> surname >> dateString;

			date dateOfBirth = Str_to_Date(dateString);

			int hash = dateOfBirth.yy % M;

			list* element = find(h[hash], t[hash], surname, dateOfBirth);

			if (element) {
				cout << "Найден сотрудник: ";
				printPeople(element->inf);
			}
			else {
				cout << "Сотрудник не найден" << endl;
			}
		}
		else if (type == 4) {
			cout << "Хэш-таблица:" << endl;

			for (int i = 0; i < M; i++) {
				cout << i << ":" << endl;

				print(h[i], t[i]);
			}
		}
		else {
			cout << "Некорректная операция" << endl;
		}

		cout << endl;
	}
}
