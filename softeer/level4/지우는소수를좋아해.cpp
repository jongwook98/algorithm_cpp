#include<iostream>
#include<cmath>
#include<vector>
#include<queue>

// 틀린 문제..
// 구글링해보니 다익스트라로 해결한다는데
// priority queue를 이용하여 적은 레벨로 항상 갈 수 있도록 했는데
// 왜 내 풀이는 안되는지 한번 찾아보자.

using namespace std;

typedef struct {
	int node, value;
}info;

struct compare {
	bool operator()(info a, info b) {
		return a.value > b.value;
	}
};

bool check[1000000001];
int point[10001];
int pre = 2;
int minimum;

vector<info> v[10001];
priority_queue<info, vector<info>, compare> pq;

void is_prime(int N) {

	for (int i = pre; i <= int(sqrt(N)); i++) {
		for (int j = i + i; j <= N; j += i) check[j] = true;
		pre = i;
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;
	cin >> N >> M;

	int A, B, C;
	while (M--) {
		cin >> A >> B >> C;
		v[A].push_back({ B, C });
		v[B].push_back({ A, C });
	}

	for (int i = 1; i <= N; i++) point[i] = int(1e9 + 1);

	pq.push({ 1, 0 });
	info cur;

	int cnt = 0;

	while (!pq.empty()) {
		cur = pq.top();
		pq.pop();

		if (cur.value > pre) is_prime(cur.value);
		if (cur.value > minimum) minimum = cur.value;

		if (point[cur.node] == int(1e9 + 1)) N--;
		point[cur.node] = minimum;

		//cout << N << '\n';

		if (N == 0) for (int i = minimum; i < 1000000001; i++) {
			if (!check[i]) {
				cout << i << '\n';
				return 0;
			}
		}

		for (info iter : v[cur.node]) {
			if (point[iter.node] == int(1e9 + 1)) {
				pq.push({ iter.node, iter.value });
			}
		}

		//cnt++;
		//if (cnt > 2) {
		//while (!pq.empty()) {
		//	cout << pq.top().node << " " << pq.top().value << '\n';
		//	pq.pop();
		//}
		//cout << '\n';
		//}
	}

	return 0;
}