#include<iostream>
#include<queue>
#include<cmath>
#include<algorithm>

// 나의 풀이 생각
// 완전 이진 트리 -> 부모 노드 번호 = 자식 노드 번호 / 2 를 이용하여 보고서 올리기
// 짝수날, 홀수날 작업이 달라지므로 두가지 queue를 생성하여 각각 처리

// 부하직원이 올린 일은 다음날에 처리할 수 있으므로
// 루트 노드부터 내려오는 top-down 방식으로 구현

// softeer 인증평가 해설과 동일하게 풀었음

using namespace std;

typedef struct {
	queue<int> q_left;
	queue<int> q_right;
}group;

group tree[1024];
queue<int> last[1024];

long long ans;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int H, K, R;
	cin >> H >> K >> R;
	int sc;

	for (int i = 0; i < pow(2, H); i++) {
		for (int j = 0; j < K; j++) {
			cin >> sc;
			last[i].push(sc);
		}
	}

	int time = 0;
	int idx;
	int p_idx = pow(2, H) - 1;
	while (++time <= R) {
		for (int i = 0; i < pow(2, H); i++) {
			if (time % 2 == 1) {
				if (!tree[i].q_left.empty()) {
					if (i == 0) ans += tree[i].q_left.front();
					else {
						if (i % 2 == 1) {
							idx = (i - 1) / 2;
							tree[idx].q_left.push(tree[i].q_left.front());
						}
						else if (i % 2 == 0) {
							idx = (i - 2) / 2;
							tree[idx].q_right.push(tree[i].q_left.front());
						}
					}
					tree[i].q_left.pop();
				}
			}
			else if (time % 2 == 0) {
				if (!tree[i].q_right.empty()) {
					if (i == 0) ans += tree[i].q_right.front();
					else {
						if (i % 2 == 1) {
							idx = (i - 1) / 2;
							tree[idx].q_left.push(tree[i].q_right.front());
						}
						else if (i % 2 == 0) {
							idx = (i - 2) / 2;
							tree[idx].q_right.push(tree[i].q_right.front());
						}
					}
					tree[i].q_right.pop();
				}
			}
		}
		for (int i = 0; i < pow(2, H); i++) {
			if (!last[i].empty()) {
				if (i % 2 == 0) {
					idx = (i + p_idx - 1) / 2;
					tree[idx].q_left.push(last[i].front());
				}
				else if (i % 2 == 1) {
					idx = (i + p_idx - 2) / 2;
					tree[idx].q_right.push(last[i].front());
				}
				last[i].pop();
			}
		}
	}

	cout << ans << '\n';

	return 0;
}