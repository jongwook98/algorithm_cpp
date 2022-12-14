#include<iostream>
#include<vector>
#include<deque>
#include<algorithm>

using namespace std;

// 입력 조건을 보아 생각한대로 구현해도 시간초과 없이 정상적으로 잘 동작함을 생각함 

vector<int> v;
deque<int> d;

int weight[10];
bool check[10];

int ans;

void cal(int N, int M, int K) {
	d.clear();
	for (int iter : v) d.push_back(weight[iter]);

	int cur = 0, time = 0;
	int sum = 0;
	while (time < K) {

		int w = d.front();
		d.pop_front();
		d.push_back(w);

		if (cur + w > M) {
			sum += cur;
			cur = w;
			time += 1;
		}
		else {
			cur += w;
		}
	}
	if (ans == 0) ans = sum;
	else ans = min(ans, sum);
}

void dfs(int N, int M, int K) {
	if (v.size() >= N) {
		cal(N, M, K);
		return;
	}

	for (int i = 0; i < N; i++) {
		if (!check[i]) {
			check[i] = true;
			v.push_back(i);

			dfs(N, M, K);

			v.pop_back();
			check[i] = false;
		}
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M, K;
	cin >> N >> M >> K;

	for (int i = 0; i < N; i++) cin >> weight[i];

	dfs(N, M, K);

	cout << ans << '\n';

	return 0;
}