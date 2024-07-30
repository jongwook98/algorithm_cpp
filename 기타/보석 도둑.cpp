// 가방과 보석을 오름차순으로 정렬하고
// 가방에 넣을 수 있으면 가격을 기준으로 하는
// 우선순위 큐에 집어 넣고,
// 더 이상 넣을 수 없는 무게의 보석이 들어오면
//
// 큐에 있는 가장 큰 가치의 보석을 꺼내는 것,


#include<iostream>
#include<queue>
#include<algorithm>

#define MAX 300000

using namespace std;

int N, K;

priority_queue<int, vector<int>, less<int>> pq;

pair<int, int> jewelry[MAX];
int bag[MAX];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		cin >> jewelry[i].first >> jewelry[i].second;
	}
	for (int i = 0; i < K; i++) {
		cin >> bag[i];
	}

	sort(jewelry, jewelry + N);
	sort(bag, bag + K);

	int idx = 0;
	long long ans = 0;
	for (int i = 0; i < K; i++) {
		while (idx < N && bag[i] >= jewelry[idx].first) {
			pq.push(jewelry[idx++].second);
		}
		if (!pq.empty()) {
			ans += pq.top();
			pq.pop();
		}
	}

	cout << ans;

	return 0;
}