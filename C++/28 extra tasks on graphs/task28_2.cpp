#include <iostream>
#include <vector>

using namespace std;

vector <int> used, topsort;
vector <vector <int> > g;

void dfs(int v) {
	used[v] = 1; // used[v] = 1 - вошли в вершину, но ещё окончательно не вышли
				// если сейчас можно перейти в вершину с used = 1, то это цикл

	for (int i = 0; i < g[v].size(); i++) {
		int to = g[v][i];

		if (used[to] == 0) {
			dfs(to);
		}
		else if (used[to] == 1) {
			cout << "Есть циклы, топологическая сортировка невозможна" << endl;
			exit(0);
		}
	}

	topsort.push_back(v); // в топологическую сортировку вершина записывается после того, как записаны все достижимые из неё
						// получается топологическая сортировка в перевернутом виде
	used[v] = 2; // used = 2 - окончательно вышли из вершины, циклов из неё не нашли
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

		u--;
		v--;

		g[u].push_back(v);
	}

	for (int i = 0; i < n; i++) {
		if (used[i] == 0) {
			dfs(i);
		}
	}

	cout << "Топологическая сортировка: ";

	reverse(topsort.begin(), topsort.end());

	for (int i = 0; i < topsort.size(); i++) {
		cout << topsort[i] + 1 << ' ';
	}
}

/*
5 5
1 4
4 2
1 2
2 5
5 3

*/