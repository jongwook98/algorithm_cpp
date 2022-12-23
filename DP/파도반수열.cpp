#include<iostream>

using namespace std;

long long DP[100];

// int 범위 초과

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	DP[0] = 1;
	DP[1] = 1;
	DP[2] = 1;
	DP[3] = 2;
	DP[4] = 2;

	for (int i = 5; i < 100; i++) DP[i] = DP[i - 1] + DP[i - 5];

	int T;
	cin >> T;

	while (T--) {
		int N;
		cin >> N;
		cout << DP[N - 1] << '\n';
	}

	return 0;
}