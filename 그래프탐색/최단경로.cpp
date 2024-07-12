#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

typedef struct {
	int v, cost;
}info;

struct cmp {
	bool operator()(info a, info b) {
		return a.cost > b.cost;
	}
};

bool comp(info a, info b) {
	return a.cost < b.cost;
}

vector<info> Ev[20001];
priority_queue<info, vector<info>, cmp> pq;
int V, E;
long long Cost[20001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> V >> E;
	for (int i = 1; i <= V; i++) {
		Cost[i] = -1;
	}

	int sv;
	cin >> sv;

	Cost[sv] = 0;
	pq.push({ sv, 0 });

	int av, bv, c;
	for (int i = 0; i < E; i++) {
		cin >> av >> bv >> c;
		Ev[av].push_back({ bv, c });
	}

	for (int i = 1; i <= V; i++) {
		sort(Ev[i].begin(), Ev[i].end(), comp);
	}

	while (!pq.empty()) {
		info cur = pq.top(); pq.pop();

		for (info iter : Ev[cur.v]) {
			if (Cost[iter.v] == -1 || Cost[iter.v] > cur.cost + iter.cost) {
				pq.push({ iter.v, cur.cost + iter.cost });
				Cost[iter.v] = cur.cost + iter.cost;
			}
		}
	}

	for (int i = 1; i <= V; i++) {
		if (Cost[i] == -1) cout << "INF" << '\n';
		else cout << Cost[i] << '\n';
	}

	return 0;
}