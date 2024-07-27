#include<iostream>

using namespace std;

int N, M;
int arr[2001];
bool DP[2001][2001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	int num;
	for (int i = 1; i <= N; i++) {
		cin >> num;
		arr[i] = num;

		DP[i][i] = true;
	}

	for (int diff = 1; diff < N; diff++) {
		for (int idx = 1; diff + idx <= N; idx++) {
			if (arr[idx] == arr[idx + diff]) {
				if (diff >= 2) {
					if (DP[idx + 1][idx + diff - 1]) DP[idx][idx + diff] = true;
				}
				else DP[idx][idx + diff] = true;
			}
			else {
				DP[idx][idx + diff] = false;
			}
		}
	}


	cin >> M;
	int S, E;
	while (M--) {
		cin >> S >> E;
		if (DP[S][E]) cout << '1' << '\n';
		else cout << '0' << '\n';
	}

	return 0;
}