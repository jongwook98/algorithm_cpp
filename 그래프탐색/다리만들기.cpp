#include<iostream>
#include<deque>
#include<vector>
#include<queue>
#include<algorithm>

/*
첫 BFS에서 섬의 번호를 매겼고,
가장자리인 지역을 prioirty_queue에 좌표, 번호, 거리의 정보를 넣었다

priority_queue는 거리를 기준으로 정렬하며 같은 거리일 경우에는 번호로 정렬하였다.

다음 BFS에서는 priority_queue 의 좌표, 번호, 거리를 기준으로 다음 바다의 좌표로 다리를 놓는 경우를 생각했으며
다른 섬에서 부터 건설된 다리를 만날 경우 현재 거리까지만 검사하여 가장 최소로 이어질 수 있는 경우를 계산하여
출력하였다.
*/

using namespace std;

typedef struct {
	int y, x;
	int num, dist;
}pos;

struct compare {
	bool operator()(pos a, pos b) {
		if (a.dist != b.dist) return a.dist > b.dist;
		return a.num > b.num;
	}
};

typedef struct {
	int num, dist;
}info;

int Map[100][100];
info check[100][100];
bool pq_check[100][100];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

deque<pos> dq;
priority_queue<pos, vector<pos>, compare> pq;

int ans = int(1e9);

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) cin >> Map[y][x];
	}

	int number = 0;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (check[y][x].dist == 0 && Map[y][x] == 1) {
				number++;

				check[y][x].dist = -1;
				dq.push_back({ y, x, number, 0 });
				Map[y][x] = number;

				while (!dq.empty()) {
					int cy = dq.front().y; int cx = dq.front().x; int cur = dq.front().num;
					dq.pop_front();

					for (int i = 0; i < 4; i++) {
						int ny = cy + dy[i]; int nx = cx + dx[i];

						if (ny >= 0 && ny < N && nx >= 0 && nx < N && check[ny][nx].dist == 0 && Map[ny][nx] == 1) {
							check[ny][nx].dist = -1;
							dq.push_back({ ny, nx, cur, 0 });
							Map[ny][nx] = cur;
						}
						if (ny >= 0 && ny < N && nx >= 0 && nx < N && !pq_check[cy][cx] && Map[ny][nx] == 0) {
							pq.push({ cy, cx, cur, 0 });
							pq_check[cy][cx] = true;
						}
					}
				}
			}
		}
	}

	bool flag = false;
	int base = int(1e9);

	while (!pq.empty()) {
		int cy = pq.top().y; int cx = pq.top().x; int cnum = pq.top().num; int cdist = pq.top().dist; pq.pop();

		if (flag && cdist > base) break;

		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i]; int nx = cx + dx[i];

			if (flag && cdist > base) break;

			if (ny >= 0 && ny < N && nx >= 0 && nx < N && !pq_check[ny][nx]) {
				pq_check[ny][nx] = true;
				check[ny][nx] = { cnum, cdist + 1 };
				pq.push({ ny, nx, cnum, cdist + 1 });
			}
			else if (ny >= 0 && ny < N && nx >= 0 && nx < N && check[ny][nx].num != cnum && check[ny][nx].dist != -1) {
				flag = true;
				base = min(base, cdist);

				ans = min(ans, check[ny][nx].dist + cdist);
			}
		}
	}

	cout << ans << '\n';

	return 0;
}