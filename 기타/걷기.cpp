#include<iostream>
#include<algorithm>

using namespace std;

// 난이도 실버 4이긴 하지만 예제 없이 모든 경우를 생각하기 어려웠음
// 풀기전에 모든 경우를 고려해봐야 겠다.

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	long long X, Y;
	cin >> X >> Y;

	long long W, S;
	cin >> W >> S;

	long long ans;
	if (2 * W <= S) {
		ans = W * (X + Y);
	}
	else if (W <= S) {
		ans = min(X, Y) * S + (max(X, Y) - min(X, Y)) * W;
	}
	else {
		if (X % 2 != Y % 2) ans = (max(X, Y) - 1) * S + W;
		else ans = max(X, Y) * S;
	}

	cout << ans << '\n';

	return 0;
}