#include <iostream>
#include <vector>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    cout << "Введите число вершин и число ребер" << endl;

    int n, m;
    cin >> n >> m;

    cout << "Введите ребра" << endl;

    vector <int> U, V, W; // начала, концы и веса ребер

    for (int i = 0; i < m; i++) {
        int u, v, w; // концы ребра и вес
        cin >> u >> v >> w;

        u--; // в программе будем нумеровать ребра с 0, а во вводе с 1
        v--;

        U.push_back(u);
        V.push_back(v);
        W.push_back(w);

        swap(u, v); // граф неориентированный, поэтому начало и конец могут быть поменяны местами

        U.push_back(u);
        V.push_back(v);
        W.push_back(w);
    }

    vector <int> d(n, 1e9); // расстояния от стартовой вершины до всех остальных
    vector <int> p(n, -1); // предыдущая вершина на кратчайшем пути до данной вершины

    cout << "Введите стартовую вершину" << endl;

    int start;
    cin >> start;
    start--;

    d[start] = 0;

    // алгоритм Форда-Беллмана

    for (int i = 0; i < n - 1; i++) { // n - 1 раз перебираем все ребра
        for (int j = 0; j < U.size(); j++) {
            if (d[V[j]] > d[U[j]] + W[j]) {
                d[V[j]] = d[U[j]] + W[j]; // обновляем расстояние до конца ребра через расстояние до начала
                p[V[j]] = U[j]; // и предыдущую вершину на пути
            }

        }
    }

    for (int i = 0; i < n; i++) {
        cout << "Путь до вершины " << i + 1 << " длины " << d[i] << ": ";

        vector <int> path; // восстановление самого пути

        int cur = i;

        while (cur != -1) {
            path.push_back(cur);
            cur = p[cur];
        }

        reverse(path.begin(), path.end());

        for (int j = 0; j < path.size(); j++) {
            cout << path[j] + 1;

            if (j + 1 < path.size()) {
                cout << "->";
            }
        }

        cout << "\n";
    }
}

/*
Пример входных данных:
5 5
1 2 1
2 3 1
3 4 1
4 5 1
1 5 2
1

*/