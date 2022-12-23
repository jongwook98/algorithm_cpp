#include<iostream>

using namespace std;

int DP[31];

// 해당 문제는 두번째 반복문인 for (int j = i - 4; j >= 0; j -= 2) DP[i] += DP[j] * 2; 가 핵심이고
// 그림을 그려서 점화식을 확실하게 세워야 할 것 같다.

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	DP[0] = 1;
	DP[2] = 3;
	for (int i = 4; i <= N; i += 2) {
		DP[i] += DP[i - 2] * 3;
		for (int j = i - 4; j >= 0; j -= 2) DP[i] += DP[j] * 2;
	}

	cout << DP[N] << '\n';

	return 0;
}