#include<iostream>
#include<vector>
#include<queue>
#include<cstring>

using namespace std;

typedef struct {
	int num;
	bool know;
}info;

int N, M;
int truth_m;

struct cmp {
	bool operator()(info a, info b) {
		return a.know < b.know;
	}
};

priority_queue<info, vector<info>, cmp> pq;
priority_queue<info, vector<info>, cmp> next_pq;
vector<int> pmv[51];

bool know_m[51];
bool know_p[51];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	cin >> truth_m;

	int m;
	for (int i = 0; i < truth_m; i++) {
		cin >> m;
		know_m[m] = true;
	}

	int pm;
	for (int i = 0; i < M; i++) {
		cin >> m;
		bool know_truth = false;
		for (int j = 0; j < m; j++) {
			cin >> pm;
			pmv[i].push_back(pm);

			if (know_m[pm] == true) know_truth = true;
		}
		pq.push({ i, know_truth });
	}

	if (truth_m == 0) {
		cout << M;
		return 0;
	}

	info cur;
	bool is_changed = false;
	do {
		is_changed = false;
		while (!pq.empty()) {
			cur = pq.top(); pq.pop();

			if (cur.know == true) {
				know_p[cur.num] = true;
				for (int iter : pmv[cur.num]) {
					know_m[iter] = true;
				}
			}
			else {
				bool know_truth = false;
				for (int iter : pmv[cur.num]) {
					if (know_m[iter] == true) {
						know_truth = true;
						break;
					}
				}
				if (know_truth == true) {
					is_changed = true;
					know_p[cur.num] = true;
					next_pq.push({ cur.num, true });
				}
				else {
					next_pq.push({ cur.num, false });
				}
			}
		}
		pq = next_pq;
		next_pq = {};
	} while (is_changed);

	int ans = 0;
	for (int i = 0; i < M; i++) {
		if (know_p[i] == false) ans++;
	}

	cout << ans << '\n';

	return 0;
}