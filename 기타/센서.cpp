#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

priority_queue<int, vector<int>, greater<int>> pq;
priority_queue<int, vector<int>, greater<int>> anpq;

// 이진탐색으로 찾아보기 -> 모든 집중국의 수신 가능영역의 크기가 같지 않으므로 해결 힘들다.

// 이 문제는 인접한 두개의 센서의 거리차를 계산한 후
// 센서의 개수 - 집중국의 개수 만큼 작은 순서로 센서의 거리차를 더하면 되는 문제..

// 센서의 개수 - 집중국의 개수 만큼 인접한 센서를 근처 집중국에 넣어야 하므로 집중국의
// 수신가능 영역의 거리를 그대로 더하는 것과 같다.

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, K;
	cin >> N >> K;

	int temp;
	for (int i = 0; i < N; i++) {
		cin >> temp; pq.push(temp);
	}

	int ans = 0, cnt = 0;
	int pre = 0;
	while (!pq.empty()) {
		if (cnt++ == 0) pre = pq.top();
		else {
			anpq.push(pq.top() - pre);
			pre = pq.top();
		}
		pq.pop();
	}

	cnt = 0;
	while (!anpq.empty() && cnt < N - K) {
		ans += anpq.top(); anpq.pop();
		cnt++;
	}

	cout << ans << '\n';

	return 0;
}