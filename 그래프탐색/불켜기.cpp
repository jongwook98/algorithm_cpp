#include<iostream>
#include<vector>
#include<deque>

using namespace std;

// 방문 했을 때 불켜기 실행
// 불이 켜지는 장소가 갈 수 있을 때 deque에 넣음

// 다음 현재 방문한 곳에서 4방향에 대해서 갈 수 있는 정보로 체크한 다음
// 갈 수 있고 불이 켜져 있으면 deque에 넣음

// 방문을 한 이후에 불을 켜므로 방문정보를 나타내는 visited 와 deque에 들어간 place를 따로 저장함

typedef struct {
	bool possi; // 갈 수 있는 경우
	bool light; // 불을 키는 경우
	bool visited; // 방문 한 경우
	bool place; // deque에 들어간 경우
}info;

typedef struct {
	int y, x;
}pos;

vector<pos> v[100][100];
deque<pos> dq;

info check[100][100];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

int ans = 1;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;
	cin >> N >> M;

	int x, y, a, b;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> a >> b;
		v[y - 1][x - 1].push_back({ b - 1, a - 1 });
	}
	
	dq.push_back({ 0, 0 });
	check[0][0] = { true, true, false };

	while (!dq.empty()) {
		int cy = dq.front().y; int cx = dq.front().x; dq.pop_front();

		if (check[cy][cx].visited == false) {
			check[cy][cx].visited = true;

			for (auto iter : v[cy][cx]) {
				if (check[iter.y][iter.x].light == false) {
					check[iter.y][iter.x].light = true;
					ans++;

					if (check[iter.y][iter.x].possi == true && check[iter.y][iter.x].place == false) {
						check[iter.y][iter.x].place = true;
						dq.push_back({ iter.y , iter.x });
					}
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i]; int nx = cx + dx[i];

			if (ny >= 0 && ny < N && nx >= 0 && nx < N) {
				check[ny][nx].possi = true;

				if (check[ny][nx].possi == true && check[ny][nx].light == true && check[ny][nx].visited == false && check[ny][nx].place == false) {
					check[ny][nx].place = true;
					dq.push_back({ ny, nx });
				}
			}
		}
	}

	cout << ans << '\n';

	return 0;
}