#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

#define TRUE 1
#define FALSE 0

using namespace std;

typedef struct {
	int v, cost;
	int A, B;
}info;

typedef struct {
	int v, cost;
}E_info;

struct cmp {
	bool operator()(info a, info b) {
		return a.cost > b.cost;
	}
};

bool Ecmp (E_info a, E_info b) {
	return a.cost < b.cost;
}

priority_queue<info, vector<info>, cmp> pq;
vector<E_info> Ev[801];
int check[801][2][2];

int N, E;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int Av, Bv, c;
	cin >> N >> E;

	for (int i = 0; i < E; i++) {
		cin >> Av >> Bv >> c;
		Ev[Av].push_back({ Bv, c });
		Ev[Bv].push_back({ Av, c });
	}
	cin >> Av >> Bv;

	for (int i = 1; i <= N; i++) {
		sort(Ev[i].begin(), Ev[i].end(), Ecmp);
	}

	for (int i = 1; i <= N; i++) {
		check[i][0][0] = int(1e9);
		check[i][0][1] = int(1e9);
		check[i][1][0] = int(1e9);
		check[i][1][1] = int(1e9);
	}
	if (Av == 1 || Bv == 1) {
		pq.push({ 1, 0, TRUE, FALSE });
	}
	else pq.push({ 1, 0, FALSE, FALSE });
	check[1][0][0] = 0;

	int is_A, is_B;
	while (!pq.empty()) {
		auto cur = pq.top(); pq.pop();
		//cout << cur.v << " " << cur.A << " " << cur.B << " " << cur.cost << '\n';

		if (cur.A == TRUE && cur.B == TRUE && cur.v == N) {
			cout << cur.cost << '\n';
			return 0;
		}
		for (E_info iter : Ev[cur.v]) {
			is_A = cur.A; is_B = cur.B;
			if (iter.v == Av) {
				is_A = TRUE;
			}
			if (iter.v == Bv) {
				is_B = TRUE;
			}
			if (check[iter.v][is_A][is_B] > cur.cost + iter.cost) {
				check[iter.v][is_A][is_B] = cur.cost + iter.cost;
				//cout << '\n' << "push : " << cur.v << " => " << iter.v << '\n';
				pq.push({ iter.v, cur.cost + iter.cost, is_A, is_B });
			}
		}
	}

	cout << -1 << '\n';

	return 0;
}