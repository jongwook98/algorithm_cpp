#include<iostream>
#include<algorithm>

using namespace std;

int stair[300];
int DP[300][2];

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++) cin >> stair[i];

	DP[0][0] = stair[0];
	DP[1][0] = stair[1];

	for (int i = 0; i < N - 1; i++) {
		DP[i + 1][1] = DP[i][0] + stair[i + 1];
		if (i == N - 1) continue;
		DP[i + 2][0] = max({ DP[i][0], DP[i][1]}) + stair[i + 2];
	}
	cout << max(DP[N - 1][0], DP[N - 1][1]) << '\n';

	return 0;
}