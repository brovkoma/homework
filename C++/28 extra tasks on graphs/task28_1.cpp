#include <iostream>
#include <vector>

using namespace std;

vector <int> deleted; // для каждого ребра хранится, удалено ли оно из графа (когда проходим по ребру, оно удаляется)
vector <vector <pair <int, int> > > g; // список смежности: хранится смежная вершина и индек ребра в неё
vector <int> cycle; // эйлеров цикл

void eulerCycle(int v) {
	while (!g[v].empty() && deleted[g[v].back().second]) { // очищаем список смежности с конца от уже удаленных ребер
		g[v].pop_back();
	}

	if (g[v].empty()) { // если из текущей вершины не осталось ребер, то завершаем поиск цикла
		return;
	}

	int edge = g[v].back().second; // индекс ребра, по которому сейчас переходим
	int to = g[v].back().first; // вершина, в которую переходим

	deleted[edge] = 1; // при переходе по ребру оно удаляется из графа

	eulerCycle(to); // проходим по ребру

	cycle.push_back(v); // цикл строим в обратном порядке: записываем текущую вершину v в цикл
						// после обработки вершины to (сначала в цикле будет записана вершина to, потом v)

	eulerCycle(v); // перезапускаем алгоритм, чтобы проверить другие ребра из текущей вершины
}

int main() {
	setlocale(LC_ALL, "rus");

	cout << "Введите число вершин и число ребер" << endl;

	int n, m;
	cin >> n >> m;

	g.resize(n);
	deleted.resize(m, 0);

	cout << "Введите ребра" << endl;

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;

		u--;
		v--;

		g[u].push_back({v, i});
		g[v].push_back({u, i});
	}

	vector <int> odd; // вершины с нечетной степенью

	for(int i = 0; i < n; i++)
		if (g[i].size() % 2 != 0) {
			odd.push_back(i);
		}

	if (odd.size() == 0) { // граф либо несвязный, либо есть эйлеров цикл
		for (int i = 0; i < n; i++) {
			if (g[i].size() > 0) {
				eulerCycle(i); // ищем эйлеров цикл из первой неизолированной вершины
				break;
			}
		}

		if (cycle.size() != m) {
			cout << "Нет эйлерова пути: граф несвязный" << endl;
			return 0;
		}

		cout << "Эйлеров цикл:" << endl;

		for (int i = 0; i < cycle.size(); i++) {
			cout << cycle[i] + 1 << ' ';
		}

		cout << endl;
	}
	else if(odd.size() == 2) { // граф либо несвязный, либо есть эйлеров путь
		int u = odd[0], v = odd[1]; // добавляем дополнительное ребро и ищем эйлеров цикл

		g[u].push_back({ v, m });
		g[v].push_back({ u, m });
		deleted.push_back(0);

		for (int i = 0; i < n; i++) {
			if (g[i].size() > 0) {
				eulerCycle(i); // ищем эйлеров цикл из первой неизолированной вершины
				break;
			}
		}

		if (cycle.size() != m + 1) {
			cout << "Нет эйлерова пути: граф несвязный" << endl;
			return 0;
		}

		int i = 0; // разрываем цикл по ребру u-v и получаем путь

		while (i < cycle.size()) {
			int j = (i + 1) % cycle.size();

			if (cycle[i] == u && cycle[j] == v || cycle[i] == v && cycle[j] == u) {
				break;
			}

			i = j;
		}

		cout << "Эйлеров путь: ";

		for (int j = 1; j <= cycle.size(); j++) {
			cout << cycle[(i + j) % cycle.size()] + 1 << ' ';
		}

		cout << endl;
	}
	else {
		cout << "Нет эйлерова пути: нечетных вершин > 2" << endl;
	}
}

/*
5 6
1 2
2 3
3 4
4 1
1 5
5 2

*/