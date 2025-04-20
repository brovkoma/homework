#include <iostream>
#include <vector>

using namespace std;

vector <vector <int> > g; // список смежности
vector <int> used; // посещена ли каждая вершина

void dfs(int v) {
    used[v] = 1;

    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];

        if (used[to] == 0) {
            dfs(to);
        }
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    cout << "Введите число вершин и число ребер" << endl;

    int n, m;
    cin >> n >> m;

    g.resize(n);
    used.resize(n, 0);

    cout << "Введите ребра" << endl;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        u--; // вершины будем нумеровать с нуля
        v--;

        g[u].push_back(v);
    }

    cout << "Введите вершину, из которой нужно проверять достижимость" << endl;
    int v;
    cin >> v;
    v--;

    dfs(v);

    cout << "Недостижимые вершины: ";

    for (int i = 0; i < n; i++)
        if (used[i] == 0)
            cout << i + 1 << ' ';
}

/*
5 4
1 2
2 3
3 4
4 5
3

*/