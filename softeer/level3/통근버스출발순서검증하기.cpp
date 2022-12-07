#include<iostream>

using namespace std;

int arr[5000];
int cnt[5000][5000];
long long ans[5000][5000];

int main(int argc, char** argv)
{
	int N;
	cin >> N;

	for (int i = 0; i < N; i++) cin >> arr[i];

	for (int i = 0; i < N - 2; i++) {
		for (int k = i + 2; k < N; k++) {
			if (arr[i] > arr[k]) cnt[i][k] = 1;
		}
	}

	for (int i = 0; i < N - 2; i++) {
		int sum_ = 0;
		for (int k = i + 2; k < N; k++) {
			ans[i][k] = cnt[i][k] + sum_;
			sum_ += cnt[i][k];
		}
	}

	// 자료형 주의하기....!
	long long res = 0;
	for (int i = 0; i < N - 2; i++) {
		for (int j = i + 1; j < N - 1; j++) {
			if (arr[i] < arr[j]) res += ans[i][N - 1] - ans[i][j];
		}
	}

	cout << res << '\n';

	return 0;
}