#include <iostream>
#include <vector>

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
        g[v].push_back(u); // неориентированный граф
    }

    cout << "Степени вершин: ";

    for (int i = 0; i < n; i++)
        cout << g[i].size() << ' ';
}

/*
5 4
1 2
2 3
3 4
4 5

*/