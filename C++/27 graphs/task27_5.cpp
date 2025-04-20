#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    cout << "Введите число вершин и число ребер" << endl;

    int n, m;
    cin >> n >> m;

    vector <vector <int> > g(n); // список смежности

    cout << "Введите ребра" << endl;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        u--; // вершины будем нумеровать с нуля
        v--;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    cout << "Введите вершины A и B" << endl;
    int a, b;
    cin >> a >> b;

    a--;
    b--;

    queue <int> q;

    q.push(a);
    vector <int> used(n), p(n); // used - посещена ли вершина, p - предыдущая вершина в пути от a до данной
    used[a] = 1;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int i = 0; i < g[v].size(); i++) {
            int to = g[v][i];

            if (used[to] == 0) {
                used[to] = 1;
                p[to] = v;
                q.push(to);
            }
        }
    }

    if (used[b] == 0) {
        cout << "Нет пути";
        return 0;
    }

    vector <int> path;

    path.push_back(b);

    int cur = b;

    while (cur != a) {
        cur = p[cur];
        path.push_back(cur);
    }

    reverse(path.begin(), path.end());

    cout << "Кратчайший путь: ";

    for (int i = 0; i < path.size(); i++)
        cout << path[i] + 1 << ' ';
}

/*
5 5
1 2
2 3
3 4
4 5
5 1
1 4

*/