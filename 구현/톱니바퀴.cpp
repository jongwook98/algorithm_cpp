#include<iostream>
#include<string>
#include<deque>
#include<queue>
#include<cstring>
#include<cmath>

using namespace std;

typedef struct {
	int s, d;
}order;

deque<int> dq[5];
queue<order> od;
queue<order> work;

string instr;
bool check[5];

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	for (int i = 1; i < 5; i++) {
		getline(cin, instr, '\n');
		for (int j = 0; j < 8; j++) dq[i].push_back(int(instr[j]) - int('0'));
	}

	int K;
	cin >> K;
	
	int ss, dd;

	while (K--) {
		cin >> ss >> dd;
		od.push({ ss, dd });
	}

	while (!od.empty()) {
		order info = od.front(); od.pop();
		
		work.push({ info.s, info.d });
		memset(check, false, sizeof(check));

		while (!work.empty()) {
			order cur = work.front(); work.pop();
			check[cur.s] = true;

			int pre_n = cur.s - 1;
			int next_n = cur.s + 1;

			if (pre_n >= 1 && !check[pre_n]) {
				if (dq[cur.s][6] != dq[pre_n][2]) work.push({ pre_n, cur.d * -1 });
			}
			if (next_n <= 4 && !check[next_n]) {
				if (dq[cur.s][2] != dq[next_n][6]) work.push({ next_n, cur.d * -1 });
			}

			if (cur.d == 1) {
				int temp = dq[cur.s].back(); dq[cur.s].pop_back();
				dq[cur.s].push_front(temp);
			}
			else if (cur.d == -1) {
				int temp = dq[cur.s].front(); dq[cur.s].pop_front();
				dq[cur.s].push_back(temp);
			}
		}
	}

	int ans = 0;
	for (int i = 1; i <= 4; i++) {
		if (dq[i][0]) ans += pow(2, i - 1);
	}

	cout << ans << '\n';

	return 0;
}