#include<iostream>
#include<deque>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

/*
문제를 풀 때 구조를 확실하게 잡을 것..

만약 맞고 틀린것을 확인할 수 없었다면 틀렸을 것 같다.

순간이동 경우에 같은 시간으로 이동할 수 있으므로
단순한 BFS로 풀 수 없다

priority_queue를 이용하여 힙구조로 탐색했어야 함
*/

typedef struct {
	int pos, time;
}info;

struct compare {
	bool operator()(info a, info b) {
		return a.time > b.time;
	}
};

priority_queue<info, vector<info>, compare> pq;

int check[100001];
int ans = int(1e9);

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	int N, K;
	cin >> N >> K;

	if (N == K) {
		cout << 0 << '\n';
		return 0;
	}

	for (int i = 0; i <= 100000; i++) check[i] = int(1e9);

	pq.push({ N, 0 });
	check[N] = 0;

	while (!pq.empty()) {
		int cp = pq.top().pos; int ct = pq.top().time; pq.pop();

		if (K > cp) {
			if (cp * 2 == K) {
				check[K] = min(check[K], ct);
				ans = min(ans, ct);
			}
			else if (cp * 2 <= 100000 && check[cp * 2] > check[cp]) {
				check[cp * 2] = check[cp];
				pq.push({ cp * 2, ct });
			}
			if (cp + 1 == K) {
				check[K] = min(check[K], ct + 1);
				ans = min(ans, ct + 1);
			}
			else if (cp + 1 <= 100000 && check[cp + 1] > check[cp] + 1) {
				check[cp + 1] = check[cp] + 1;
				pq.push({ cp + 1, ct + 1 });
			}
			if (cp - 1 >= 0 && check[cp - 1] > check[cp] + 1) {
				check[cp - 1] = check[cp] + 1;
				pq.push({ cp - 1, ct + 1 });
			}
		}
		else {
			if (cp - 1 == K) {
				check[K] = min(check[K], ct + 1);
				ans = min(ans, ct + 1);
			}
			else if (cp - 1 >= 0 && check[cp - 1] > check[cp] + 1) {
				check[cp - 1] = check[cp] + 1;
				pq.push({ cp - 1, ct + 1 });
			}
		}
	}

	cout << ans << '\n';

	return 0;
}