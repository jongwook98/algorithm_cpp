#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>

using namespace std;

// 내가 한번에 찾지 못하고 디버깅을 통해서 찾은 경우

// 1. 300을 제외한 450 보다 작은수 + 450 보다 큰 수 가 900을 넘을 경우
// 300 + 450 보다 큰 수가 900을 넘지 않을 경우에 300을 소모하여 채워야 적은 경우다.

// 2. 450 보다 큰 수가 더이상 존재하지 않고, 450 보다 작은 수와 300만 존재할 경우에는
// 300 세가지로 다 빼놓고 시작해야 적은 경우다.

// 3. 450 보다 작은 수가 더이상 존재하지 않고, 450 보다 큰 수와 300만 존재할 경우에는
// 300과 450보다 큰 수를 같이 채워 넣는다.

int num[301];
bool check[301];

struct compare_b {
	bool operator()(int a, int b) {
		return a < b;
	}
};

struct compare_s {
	bool operator()(int a, int b) {
		return a > b;
	}
};

priority_queue<int, vector<int>, compare_s> pq_s;
priority_queue<int, vector<int>, compare_b> pq_b;

int main(int argc, char** argv)
{
	int T, N;
	cin >> T;

	while (T--) {
		cin >> N;

		int mib;
		int ans = 0;

		memset(check, false, sizeof(check));
		memset(num, 0, sizeof(num));

		for (int i = 0; i < N; i++) {
			cin >> mib;

			if (mib > 600) {
				ans += 1;
				continue;
			}

			num[mib - 300] += 1;

			if (!check[mib - 300]) {
				check[mib - 300] = true;
				if (mib > 450) pq_b.push(mib);
				else if (mib > 300) pq_s.push(mib);
			}
		}

		int cur_s = 0, cur_b = 0;
		while (!pq_b.empty() || !pq_s.empty()) {

			if (!pq_b.empty() && !pq_s.empty()) {
				cur_s = pq_s.top();
				cur_b = pq_b.top();
			}
			else if (!pq_b.empty()) {
				while (!pq_b.empty()) {
					cur_b = pq_b.top();
					if (num[0] > 0) {
						int temp = min(num[0], num[cur_b - 300]);
						ans += temp;
						num[0] -= temp;
						num[cur_b - 300] -= temp;

						if (num[cur_b - 300] == 0) pq_b.pop();
					}

					else {
						pq_b.pop();
						ans += num[cur_b - 300];
					}
				}
				break;
			}
			else if (!pq_s.empty()) {
				int toans = 0;

				if (num[0] > 2) {
					ans += int(num[0] / 3);
					num[0] %= 3;
				}
				toans += num[0];
				num[0] = 0;
				while (!pq_s.empty()) {
					cur_s = pq_s.top();

					pq_s.pop();
					toans += num[cur_s - 300];
				}
				ans += (toans / 2) + (toans % 2);
				break;
			}

			if (cur_s + cur_b > 900) {
				if (num[0] > 0) {
					int temp = min(num[0], num[cur_b - 300]);
					ans += temp;
					num[0] -= temp;
					num[cur_b - 300] -= temp;

					if (num[cur_b - 300] == 0) pq_b.pop();
				}
				else {
					ans += num[cur_b - 300];
					pq_b.pop();
				}
			}
			else {
				int temp = min(num[cur_s - 300], num[cur_b - 300]);
				ans += temp;
				num[cur_s - 300] -= temp;
				num[cur_b - 300] -= temp;

				if (num[cur_s - 300] == 0) pq_s.pop();
				if (num[cur_b - 300] == 0) pq_b.pop();
			}
		}

		if (num[0] > 0) {
			ans += int(num[0] / 3);
			if (num[0] % 3 > 0) ans++;
		}

		cout << ans << '\n';
	}

	return 0;
}