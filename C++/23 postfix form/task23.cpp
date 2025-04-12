#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct stack {
    float inf;
    stack* next;
};

void push(stack*& h, float x) {
    stack* r = new stack; //создаем новый элемент
    r->inf = x; //поле inf = x
    r->next = h; //следующим элементов является h
    h = r; //теперь r является головой
}

float pop(stack*& h) {
    float i = h->inf; //значение первого элемента
    stack* r = h; //указатель на голову стека
    h = h->next; //переносим указатель на следующий элемент
    delete r; //удаляем первый элемент
    return i; //возвращаем значение
}

void reverse(stack*& h) { //"обращение"стека
    stack* head1 = NULL; //инициализация буферного стека
    while (h) //пока стек не пуст
        push(head1, pop(h)); //переписываем из одного стека в другой
    h = head1; //переобозначаем указатели
}


int main()
{
    setlocale(LC_ALL, "rus");

    stack* st = NULL; // пустой стек

    cout << "Введите выражение в постфиксной форме" << endl;

    string s;
    getline(cin, s);

    string elem = ""; // текущее число или знак

    vector <string> elems;

    for (int i = 0; i < s.size(); i++) { // разделяем выражение на числа и знаки
        if (s[i] == ' ' && elem.size() > 0) {
            elems.push_back(elem);
            elem = "";
        }
        else if(s[i] != ' ') {
            elem += s[i];
        }
    }

    if (elem.size() > 0) {
        elems.push_back(elem);
    }

    for (int i = 0; i < elems.size(); i++) {
        if (elems[i] == "+" || elems[i] == "-" || elems[i] == "*" || elems[i] == "/") { // если встречаем операцию, то применяем её
            float y = pop(st); // к двум верхним элементам стека
            float x = pop(st);

            if (elems[i] == "+") {
                push(st, x + y);
            }
            else if (elems[i] == "-") {
                push(st, x - y);
            }
            else if (elems[i] == "*") {
                push(st, x * y);
            }
            else if (elems[i] == "/") {
                push(st, x / y);
            }
        }
        else { // если встречаем число, то добавляем его в стек
            push(st, stoi(elems[i]));
        }
    }

    cout << pop(st);
}