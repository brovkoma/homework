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

    cout << "Введите стартовую вершину" << endl;

    int start;
    cin >> start;
    start--;

    d[start] = 0;

    // алгоритм Форда-Беллмана

    for (int i = 0; i < n - 1; i++) { // n - 1 раз перебираем все ребра
        for (int j = 0; j < U.size(); j++) {
            d[V[j]] = min(d[V[j]], d[U[j]] + W[j]); // обновляем расстояние до конца ребра через расстояние до начала
        }
    }

    cout << "Расстояния до всех вершин: ";

    for (int i = 0; i < n; i++) {
        cout << d[i] << ' ';
    }
}