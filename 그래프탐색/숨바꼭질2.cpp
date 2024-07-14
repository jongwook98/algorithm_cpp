// 계속 틀린 이유가 무엇인지 디버깅 해야할 듯,
// 누나랑 동생 위치 같은 경우, 출력 어떻게 될지 미리 생각하기.

#include<iostream>
#include<queue>

using namespace std;

typedef struct {
	int pos, cost;
}info;

int N, K;
int ans = 0;
int min_a = -1;
int ucheck[100001];

queue<info> q;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> K;

	if (N == K) {
		cout << "0" << '\n' << "1";
		return 0;
	}
	for (int i = 0; i <= 100000; i++) {
		ucheck[i] = int(1e9);
	}

	ucheck[N] = 0;
	q.push({ N, 0 });

	while (!q.empty()) {
		int cp = q.front().pos; int cc = q.front().cost; q.pop();

		if (cp == K && ucheck[cp] >= cc) {
			ucheck[cp] = cc;
			ans++;
		}

		if (cp > 0 && ucheck[cp - 1] >= cc + 1) {
			ucheck[cp - 1] = cc + 1;
			q.push({ cp - 1, cc + 1 });
		}
		if (cp < 100000 && ucheck[cp + 1] >= cc + 1) {
			ucheck[cp + 1] = cc + 1;
			q.push({ cp + 1, cc + 1 });
		}
		if (cp <= 50000 && ucheck[cp * 2] >= cc + 1) {
			ucheck[cp * 2] = cc + 1;
			q.push({ cp * 2, cc + 1 });
		}
	}

	cout << ucheck[K] << '\n' << ans;

	return 0;
}