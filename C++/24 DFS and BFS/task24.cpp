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

struct queue {
    int inf;
    queue* next;
};

void push(queue*& h, queue*& t, int x) { //вставка элемента в очередь
    queue* r = new queue; //создаем новый элемент
    r->inf = x;
    r->next = NULL; //всегда последний
    if (!h && !t) { //если очередь пуста
        h = t = r; //это и голова и хвост
    }
    else {
        t->next = r; //r - следующий для хвоста
        t = r; //теперь r - хвост
    }
}

int pop(queue*& h, queue*& t) { //удаление элемента из очереди
    queue* r = h; //создаем указатель на голову
    int i = h->inf; //сохраняем значение головы
    h = h->next; //сдвигаем указатель на следующий элемент
    if (!h) //если удаляем последний элемент из очереди
        t = NULL;
    delete r; //удаляем первый элемент
    return i;
}


int main()
{
    setlocale(LC_ALL, "rus");

    cout << "Введите число вершин" << endl;

    int n;
    cin >> n;

    vector <vector <int> > g(n); // список смежности

    for (int i = 0; i < n; i++) {
        cout << "Введите количество вершин, смежных с вершиной " << i << endl;
        int k;
        cin >> k;

        cout << "Введите вершины, смежные с вершиной " << i << endl;

        for (int j = 0; j < k; j++) {
            int x;
            cin >> x;

            g[i].push_back(x);
        }
    }

    stack* st = NULL;
    vector <int> used(n); // какие вершины уже посетили

    cout << "Введите вершину, из которой нужно делать обход" << endl;

    int start;
    cin >> start;

    cout << "Обход в глубину: ";

    push(st, start);

    while (st) {
        int v = pop(st);

        if (used[v] == 1) {
            continue;
        }

        cout << v << ' ';
        used[v] = 1;

        for (int i = (int)g[v].size() - 1; i >= 0; i--) {
            int to = g[v][i];

            if (used[to] == 0) {
                push(st, to);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        used[i] = 0;
    }

    cout << endl;

    queue* h = NULL;
    queue* t = NULL;
    cout << "Обход в ширину: ";

    used[start] = 1;
    push(h, t, start);

    while (h) {
        int v = pop(h, t);

        cout << v << ' ';

        for (int i = 0; i < g[v].size(); i++) {
            int to = g[v][i];

            if (used[to] == 0) {
                used[to] = 1;
                push(h, t, to);
            }
        }
    }
}

/*
* Пример входных данных
7
4
1 2 4 5
2
0 3
2
0 5
1
1
2
0 6
3
0 2 6
2
4 5
0
*/