#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

#define MAX 1000000000

// 우선순위 큐, 사용자 정의 정렬

using namespace std;

typedef struct {
	int s, p, m;
}pro;

typedef struct {
	int ps, idx;
}info;

struct compare {
	bool operator()(pro a, pro b) {
		if (a.s != b.s) return a.s > b.s;
		return a.p < b.p;
	}
};

bool comp(info a, info b) {
	return a.ps < b.ps;
}

int check[100000];
int ans[100000];

priority_queue<pro, vector<pro>, compare> pq;
vector<info> v;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	int pr, si, pi;
	for (int i = 0; i < N; i++) {
		cin >> pr;
		for (int j = 0; j < pr; j++) {
			cin >> si >> pi;
			pq.push({ si, pi, i });
		}
	}

	int M;
	cin >> M;

	int psi;

	for (int i = 0; i < M; i++) {
		cin >> psi;
		v.push_back({ psi, i });
	}

	sort(v.begin(), v.end(), comp);

	/*
	// debug
	pro ex;
	while (!pq.empty()) {
		ex = pq.top();
		pq.pop();

		cout << ex.s << " " << ex.p << " " << ex.m << '\n';
	}
	cout << "V" << '\n';

	for (info inff : v) cout << inff.ps << " " << inff.idx << '\n';
	*/

	pro od;
	info inf;

	int cur = 0;
	int cur_idx = 0;
	long long sum_p = 0;

	for (int i = 0; i < M; i++) ans[i] = -1;

	while (!pq.empty() && cur_idx < v.size()) {
		od = pq.top();
		pq.pop();

		cur = od.s;
		if (check[od.m] == 0) {
			check[od.m] = od.p;
			sum_p += od.p;
		}
		else if (check[od.m] < od.p) {
			sum_p -= check[od.m];
			sum_p += od.p;
			check[od.m] = od.p;
		}

		if (sum_p > MAX) sum_p = MAX;

		while (cur_idx < v.size()) {
			inf = v[cur_idx];
			if (sum_p >= inf.ps) {
				ans[inf.idx] = cur;
				cur_idx += 1;
			}
			else break;
		}
	}

	for (int i = 0; i < M; i++) {
		cout << ans[i] << " ";
	}
	cout << '\n';

	return 0;
}