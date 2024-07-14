// 정방향, 역방향 다익스트라로 시간 줄이기
// 20m 구현, [2344KB, 0ms]
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

typedef struct {
	int v, cost;
}info;

struct comp {
	bool operator()(info a, info b) {
		return a.cost > b.cost;
	}
};

bool cmp(info a, info b) {
	return a.cost < b.cost;
}

int N, M, X;

int Carr[1001];
int reverse_Carr[1001];

vector<info> edges[1001];
vector<info> reverse_edges[1001];

priority_queue<info, vector<info>, comp> pq;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> X;

	int sv, ev, c;
	for (int i = 0; i < M; i++) {
		cin >> sv >> ev >> c;
		edges[sv].push_back({ ev, c });
		reverse_edges[ev].push_back({ sv, c });
	}

	for (int i = 1; i <= N; i++) {
		sort(edges[i].begin(), edges[i].end(), cmp);
		sort(reverse_edges[i].begin(), reverse_edges[i].end(), cmp);

		Carr[i] = int(1e9);
		reverse_Carr[i] = int(1e9);
	}
	Carr[X] = 0;
	reverse_Carr[X] = 0;

	pq.push({ X, 0 });
	while (!pq.empty()) {
		info cur = pq.top(); pq.pop();

		for (info iter : edges[cur.v]) {
			if (Carr[iter.v] > cur.cost + iter.cost) {
				Carr[iter.v] = cur.cost + iter.cost;
				pq.push({ iter.v, cur.cost + iter.cost });
			}
		}
	}

	pq.push({ X, 0 });
	while (!pq.empty()) {
		info cur = pq.top(); pq.pop();

		for (info iter : reverse_edges[cur.v]) {
			if (reverse_Carr[iter.v] > cur.cost + iter.cost) {
				reverse_Carr[iter.v] = cur.cost + iter.cost;
				pq.push({ iter.v, cur.cost + iter.cost });
			}
		}
	}

	int ans = 0;
	for (int i = 1; i <= N; i++) {
		ans = max(ans, Carr[i] + reverse_Carr[i]);
	}

	cout << ans;

	return 0;
}

/*
먼저 풀어봤던 알고리즘
=> 플로이드 방식으로 진행
// 15m 구현, [15428KB, 144ms]


#include<algorithm>
#include<iostream>
#include<queue>
#include<vector>

using namespace std;

typedef struct {
	int v, cost;
}info;

typedef struct {
	int init, v, cost;
}pq_info;

struct cmp {
	bool operator()(pq_info a, pq_info b) {
		return a.cost > b.cost;
	}
};

bool comp(info a, info b) {
	return a.cost < b.cost;
}


int N, M, X;
int ucheck[1001][1001];
int ans = 0;

vector<info> Ev[1001];
priority_queue<pq_info, vector<pq_info>, cmp> pq;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> X;

	int sv, ev, c;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) ucheck[i][j] = int(1e9);
	}

	for (int i = 0; i < M; i++) {
		cin >> sv >> ev >> c;
		Ev[sv].push_back({ ev, c });
		ucheck[sv][ev] = c;
	}
	
	for (int i = 1; i <= N; i++) {
		sort(Ev[i].begin(), Ev[i].end(), comp);
		ucheck[i][i] = 0;
		pq.push({ i, i, 0 });
	}

	while (!pq.empty()) {
		pq_info cur = pq.top(); pq.pop();
		if (ucheck[cur.init][cur.v] < cur.cost) continue;

		for (info iter : Ev[cur.v]) {
			if (ucheck[cur.init][iter.v] > cur.cost + iter.cost) {
				ucheck[cur.init][iter.v] = cur.cost + iter.cost;
				pq.push({ cur.init, iter.v, cur.cost + iter.cost });
			}
		}
	}

	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) cout << ucheck[i][j] << " ";
		cout << '\n';
	}
	cout << '\n';
	

	for (int i = 1; i <= N; i++) {
		ans = max(ans, ucheck[i][X] + ucheck[X][i]);
	}
	
	cout << ans << '\n';

	return 0;
}
*/