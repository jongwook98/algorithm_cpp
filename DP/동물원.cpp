#include<iostream>

using namespace std;

int DP[100000][3];

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	DP[0][0] = 1; // 사자 없
	DP[0][1] = 1; // 사자 왼
	DP[0][2] = 1; // 사자 오

	for (int i = 1; i < N; i++) {
		DP[i][0] = (DP[i - 1][0] + DP[i - 1][1] + DP[i - 1][2]) % 9901;
		DP[i][1] = (DP[i - 1][0] + DP[i - 1][2]) % 9901;
		DP[i][2] = (DP[i - 1][0] + DP[i - 1][1]) % 9901;
	}

	cout << (DP[N - 1][0] + DP[N - 1][1] + DP[N - 1][2]) % 9901 << '\n';

	return 0;
}