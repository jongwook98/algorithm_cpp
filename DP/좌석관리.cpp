#include<iostream>
#include<vector>

using namespace std;

// 그림을 그려가면서 풀어 볼 때
// 피보나치 수열의 형식을 띈다

vector<int> v;
int cur = 1;

int DP[41];

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;
	cin >> N >> M;

	int num;
	for (int i = 0; i < M; i++) {
		cin >> num;
		v.push_back(num - cur);
		cur = num + 1;
	}
	v.push_back(N - cur + 1);

	DP[0] = 1;
	DP[1] = 1;
	DP[2] = 2;

	for (int i = 3; i <= 40; i++) {
		DP[i] = DP[i - 1] + DP[i - 2];
	}

	int ans = 1;
	for (int iter : v) {
		ans *= DP[iter];
	}

	cout << ans << '\n';

	return 0;
}