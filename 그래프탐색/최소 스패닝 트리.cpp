// Union-find 알고리즘처럼 풀기는 했으나
// 함수화가 안되서 디버깅 힘들고, 눈에 잘 안들어 옴.
// 코드 분리좀 해서 푸는 습관 들여보기

#include<iostream>
#include<queue>
#include<vector>

using namespace std;

typedef struct {
	int Av, Bv, cost;
}edges;

struct cmp {
	bool operator()(edges a, edges b) {
		return a.cost > b.cost;
	}
};

priority_queue<edges, vector<edges>, cmp> pq;

int min_head[10001];
vector<int> min_arr[10001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int V, E;
	cin >> V >> E;

	for (int i = 1; i <= V; i++) min_head[i] = i;

	int Av, Bv, C;
	for (int i = 0; i < E; i++) {
		cin >> Av >> Bv >> C;
		pq.push({ Av, Bv, C });
	}

	int ans = 0;
	while (!pq.empty()) {
		edges cur = pq.top(); pq.pop();

		if (min_head[cur.Av] != min_head[cur.Bv]) {

#ifdef debug
			cout << '\n';
			cout << cur.Av << " " << cur.Bv << " " << cur.cost << " : " << ans << '\n';

			cout << " min_head  start : " << '\n';
			for (int i = 1; i <= V; i++) {
				cout << min_head[i] << " ";
			}
			cout << '\n';
#endif
			ans += cur.cost;
			int temp;
			if (min_head[cur.Av] < min_head[cur.Bv]) {
				temp = min_head[cur.Bv];
				for (int iter : min_arr[temp]) {
					min_arr[min_head[cur.Av]].push_back(iter);
					min_head[iter] = min_head[cur.Av];
				}
				min_arr[temp].clear();

				min_head[temp] = min_head[cur.Av];
				min_arr[min_head[cur.Av]].push_back(temp);
			}
			else {
				temp = min_head[cur.Av];
				for (int iter : min_arr[temp]) {
					min_arr[min_head[cur.Bv]].push_back(iter);
					min_head[iter] = min_head[cur.Bv];
				}
				min_arr[temp].clear();

				min_head[temp] = min_head[cur.Bv];
				min_arr[min_head[cur.Bv]].push_back(temp);
			}
		}
	}

	cout << ans;

	return 0;
}