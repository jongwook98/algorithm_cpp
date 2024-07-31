// 이분 탐색, 투포인터 문제
// 소요 시간 1h, 실행 시간 3416ms
// 4개의 배열에 대해 각각의 연산을 수행하지 않고
// 두 개 씩 계산하여 각각 중복되는 값을
// 한 번에 처리하면 검색하는 중복 시간을 줄일 수 있음. 

#include<iostream>
#include<algorithm>

#define MAX 4000

using namespace std;

int N;
int A[MAX], B[MAX], C[MAX], D[MAX];
int AB[MAX * MAX], CD[MAX * MAX];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> A[i] >> B[i] >> C[i] >> D[i];
	}

	for (int a = 0; a < N; a++) {
		for (int b = 0; b < N; b++) AB[a * N + b] = A[a] + B[b];
	}

	for (int c = 0; c < N; c++) {
		for (int d = 0; d < N; d++) CD[c * N + d] = C[c] + D[d];
	}

	sort(AB, AB + N * N);
	sort(CD, CD + N * N);

	long long ans = 0;
	for (long long i = 0; i < N * N;) {
		long long idx = 1;
		while (i + idx < N * N && AB[i] == AB[i + idx]) idx += 1;

		long long left = 0, right = N * N - 1;
		while (left <= right) {
			long long mid = (left + right) / 2;

			if (AB[i] + CD[mid] == 0) {
				long long mleft = mid, mright = mid;
				while (mleft - 1 >= 0 && CD[mleft - 1] == CD[mid]) mleft -= 1;
				while (mright + 1 < N * N && CD[mright + 1] == CD[mid]) mright += 1;

				ans += idx * (mright - mleft + 1);
				break;
			}
			else if (AB[i] + CD[mid] > 0) {
				right = mid - 1;
			}
			else left = mid + 1;

		}
		i += idx;
	}

	cout << ans;

	return 0;
}