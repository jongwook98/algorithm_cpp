#include<iostream>
#include<deque>
#include<vector>
#include<queue>
#include<cstring>

using namespace std;

/*
이 문제를 거의 6시간은 넘게 쓴듯

생각하지 못한 경우의 수가 너무 많았음..

1. 동일한 거리인 사람이 많은 경우 행 / 렬로 우선순위 결정
2. 사람이 서있어도 택시는 지나갈 수 있음
3. A의 도착지가 B의 출발지인 경우
4. 택시의 첫 시작점이 누군가의 출발지인 경우 -> 탐색하다가 출발지를 찾은 경우처럼 나머지 초기화
*/

typedef struct {
	int y, x;
	int g;
}info; 

struct compare {
	bool operator()(info a, info b) {
		if (a.y != b.y) return a.y > b.y;
		return a.x > b.x;
	}
};

int check[20][20];
int Map[20][20];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

deque<info> dq;
vector<info> dep;
vector<info> des;
priority_queue<info, vector<info>, compare> pq;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M, G;
	cin >> N >> M >> G;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> Map[y][x];
			if (Map[y][x] == 1) Map[y][x] = -1;
		}
	}

	int sy, sx;
	cin >> sy >> sx;
	dq.push_back({ sy - 1, sx - 1, G });
	check[sy - 1][sx - 1] = 1;
	
	int idx = 0;
	
	int ssy, ssx, ddy, ddx;
	for (int i = 0; i < M; i++) {
		cin >> ssy >> ssx >> ddy >> ddx;
		Map[ssy - 1][ssx - 1] = i + 1;
		dep.push_back({ ssy - 1, ssx - 1, 0 });
		des.push_back({ ddy - 1, ddx - 1, 0 });

		if (sy - 1 == ssy - 1 && sx - 1 == ssx - 1) {
			idx = i + 1;
			Map[sy - 1][sx - 1] = 0;
		}
	}

	
	int succ = 0;
	
	while (!dq.empty()) {
		auto iter = dq.front(); dq.pop_front();
		int cy = iter.y; int cx = iter.x; int cur = iter.g;
		bool flag = false;

		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i]; int nx = cx + dx[i];
			
			if (ny >= 0 && ny < N && nx >= 0 && nx < N && cur > 0) {
				if (check[ny][nx] == 0 && Map[ny][nx] != -1) {
					check[ny][nx] = check[cy][cx] + 1;
					dq.push_back({ ny, nx, cur - 1 });
					if (idx == 0 && Map[ny][nx] != 0) {
						if (!pq.empty()) {
							if (cur > pq.top().g) pq.push({ ny,nx, cur - 1 });
						}
						else pq.push({ ny, nx, cur - 1 });
					}
					else if (idx != 0 && ny == des[idx - 1].y && nx == des[idx - 1].x) {
						succ++;
						flag = true;

						G = cur - 1 + check[cy][cx] * 2;
						memset(check, 0, sizeof(check));

						if (Map[ny][nx] != 0) {
							idx = Map[ny][nx];
							Map[ny][nx] = 0;
						}
						else idx = 0;

						dq.clear();
						dq.push_back({ ny, nx, G });
						check[ny][nx] = 1;

						if (succ == M) {
							cout << G << '\n';
							return 0;
						}
						break;
					}
				}
			}
		}
		if (flag) continue;

		if (dq.empty() || !pq.empty()) {
			if (!pq.empty()) {
				if (dq.empty()) {
					dq.clear();
					memset(check, 0, sizeof(check));
					
					auto nter = pq.top();
					dq.push_back({ nter.y, nter.x, nter.g });
					check[nter.y][nter.x] = 1;

					idx = Map[nter.y][nter.x];
					Map[nter.y][nter.x] = 0;

					G = nter.g;

					while (!pq.empty()) pq.pop();
				}
				
				else if (check[cy][cx] >= check[pq.top().y][pq.top().x]) {
					dq.clear();
					memset(check, 0, sizeof(check));

					auto nter = pq.top();
					dq.push_back({ nter.y, nter.x, nter.g });
					check[nter.y][nter.x] = 1;

					idx = Map[nter.y][nter.x];
					Map[nter.y][nter.x] = 0;

					G = nter.g;

					while (!pq.empty()) pq.pop();
				}
			}
		}
	}

	cout << -1 << '\n';

	return 0;
}