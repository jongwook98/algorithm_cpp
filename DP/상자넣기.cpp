#include<iostream>
#include<algorithm>

using namespace std;

int bsize[1000];
int DP[1000];
int ans;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++) cin >> bsize[i];

	for (int i = 0; i < N; i++) DP[i] = 1;

	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			if (bsize[i] < bsize[j]) DP[j] = max(DP[j], DP[i] + 1);
		}
	}

	for (int i = 0; i < N; i++) ans = max(ans, DP[i]);
	cout << ans << '\n';

	return 0;
}