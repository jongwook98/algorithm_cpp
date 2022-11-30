#include<iostream>
#include<deque>

using namespace std;

typedef struct {
	int de;
	bool r;
}pl;

pl deg[200];

deque<int> dq;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, K;
	cin >> N >> K;

	int sp = 0;
	int ep = N - 1;

	int z_p = 0;

	for (int i = 0; i < 2 * N; i++) {
		cin >> deg[i].de;
		if (deg[i].de == 0) z_p += 1;
	}

	int time = 0;
	while (z_p < K) {
		sp = (sp + 2 * N - 1) % (2 * N);
		ep = (ep + 2 * N - 1) % (2 * N);
		int rep = dq.size();
		while (rep--) {
			int cur_r = dq.front();
			dq.pop_front();
			deg[cur_r].r = false;
			if (cur_r == ep) continue;
			int n_r = (cur_r + 1) % (2 * N);
			if (deg[n_r].de > 0 && !deg[n_r].r) {
				deg[n_r].r = true;
				deg[n_r].de -= 1;
				if (deg[n_r].de == 0) z_p++;
				if (n_r == ep) continue;
				dq.push_back(n_r);
			}
			else {
				dq.push_back(cur_r);
				deg[cur_r].r = true;
			}
		}
		if (deg[sp].de > 0) {
			dq.push_back(sp);
			deg[sp].r = true;
			deg[sp].de -= 1;
			if (deg[sp].de == 0) z_p++;
		}
		time++;
	}

	cout << time << '\n';

	return 0;
}
