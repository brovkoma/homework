#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

    int n = 64; // представим шахматную доску как граф
    // вершина (i * 8 + j) соответствует клетке (i, j)

    vector <vector <int> > g(n); // список смежности

    for(int i = 0; i < 64; i++) // заполняем список смежности
        for (int j = 0; j < 64; j++) {
            int x = abs(i / 8 - j / 8);
            int y = abs(i % 8 - j % 8);

            if (x == 1 && y == 2 || x == 2 && y == 1) {
                g[i].push_back(j);
            }
        }

    queue* h = NULL;
    queue* t = NULL;
    vector <int> used(n); // какие вершины уже посетили
    vector <int> p(n); // из какой вершины пришли в данную

    cout << "Введите стартовую и конечную клетки" << endl;

    string s, f;
    cin >> s >> f;

    int start = (s[0] - 'A') * 8 + (s[1] - '1');
    int finish = (f[0] - 'A') * 8 + (f[1] - '1');

    used[start] = 1;
    push(h, t, start);

    while (h) {
        int v = pop(h, t);

        for (int i = 0; i < g[v].size(); i++) {
            int to = g[v][i];

            if (used[to] == 0) {
                used[to] = 1;
                p[to] = v;
                push(h, t, to);
            }
        }
    }

    vector <int> path; // кратчайший путь

    int v = finish;

    while (v != start) {
        path.push_back(v);
        v = p[v];
    }

    path.push_back(v);

    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++) {
        cout << char(path[i] / 8 + 'A') << char(path[i] % 8 + '1') << ' ';
    }
}