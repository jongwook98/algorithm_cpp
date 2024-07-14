#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

typedef struct {
	int init, v, cost;
}pq_info;

typedef struct {
	int v, cost;
}info;

struct cmp {
	bool operator()(pq_info a, pq_info b) {
		return a.cost > b.cost;
	}
};

bool comp(info a, info b) {
	return a.cost < b.cost;
}

vector<info> v[101];
priority_queue<pq_info, vector<pq_info>, cmp> pq;

int dis[101][101];

int n, m;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) dis[i][j] = int(1e9);
	}

	int sc, dc, cost;
	for (int i = 0; i < m; i++) {
		cin >> sc >> dc >> cost;
		v[sc].push_back({ dc, cost });
	}

	for (int i = 1; i <= n; i++) {
		sort(v[i].begin(), v[i].end(), comp);
		dis[i][i] = 0;
		pq.push({ i, i, 0 });
	}

	while (!pq.empty()) {
		pq_info cur = pq.top(); pq.pop();

		for (info iter : v[cur.v]) {

			//cout << cur.v << " " << cur.cost << " " << iter.v << " " << iter.cost << '\n';

			if (dis[cur.init][iter.v] > cur.cost + iter.cost) {
				dis[cur.init][iter.v] = cur.cost + iter.cost;
				pq.push({ cur.init, iter.v, cur.cost + iter.cost });
			}
		}

	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (dis[i][j] == int(1e9)) cout << "0 ";
			else cout << dis[i][j] << " ";
			//cout << dis[i][j] << " ";
		}
		cout << '\n';
	}


	return 0;
}