#include<iostream>
#include<queue>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

// 위상정렬 Topology Sort

typedef struct {
	int idg, time;
	vector<int> v;
}info;

typedef struct {
	int node;
	int time;
}tt;

struct compare {
	bool operator()(tt a, tt b) {
		return a.time > b.time;
	}
};

info indeg[1001];
int D[1001];
priority_queue<tt, vector<tt>, compare> pq;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int T;
	cin >> T;

	while (T--) {
		memset(indeg, 0, sizeof(indeg));
		memset(D, 0, sizeof(D));

		int N, K, W;
		cin >> N >> K;

		for (int i = 1; i <= N; i++) cin >> D[i];

		int A, B;
		for (int j = 0; j < K; j++) {
			cin >> A >> B;
			indeg[A].v.push_back(B);
			indeg[B].idg++;
		}
		cin >> W;

		for (int i = 1; i <= N; i++) {
			if (indeg[i].idg == 0) pq.push({ i, D[i]});
		}

		int ct = 0;
		while (!pq.empty() && indeg[W].time == 0) {
			tt iter = pq.top(); pq.pop();
			ct = iter.time;

			indeg[iter.node].time = ct;

			for (int nnode : indeg[iter.node].v) {
				if (--indeg[nnode].idg == 0) {
					pq.push({ nnode, ct + D[nnode] });
				}
			}
		}
		cout << indeg[W].time << '\n';
		while (!pq.empty()) pq.pop();
	}

	return 0;
}