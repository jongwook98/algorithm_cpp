#include<iostream>
#include<deque>
#include<vector>
#include<cstring>
#include<cmath>

using namespace std;

// 방문여부 확인에 좌표 + 획득한 점수로 BFS 탐색하였다.
// 점수는 더러운 칸을 임의로 0, 1, 2 ~ 9 의 번호를 매겨 2의 승수로 비트마스킹하여
// 모든 가능한 칸을 탐색하였다
// 시간초과는 나지 않았지만 다른 사람의 코드 속도인 4ms의 비해 100배 느린 412ms의 속도가 나왔다.

// 시간을 줄일 수 있는 방법
// 더러운 칸 -> 더러운 칸의 거리를 다 구한다음
// 시작 -> 더러운 칸 -> 더러운 칸을 더한 가장 짧은 거리 출력

typedef struct {
	int y, x, point;
}info;

int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };

char Map[20][20];

deque<info> dq;

int check[20][20][1024];
int ob;

void search(int W, int H) {
	while (!dq.empty()) {
		info iter = dq.front(); dq.pop_front();
		for (int i = 0; i < 4; i++) {
			int ny = iter.y + dy[i]; int nx = iter.x + dx[i];
			int cur = iter.point;

			if (cur == pow(2, ob) - 1) {
				cout << check[iter.y][iter.x][cur] -1 << '\n';
				return;
			}

			if (ny >= 0 && ny < H && nx >= 0 && nx < W) {
				int temp = int(pow(2, Map[ny][nx] - '0'));
				if (Map[ny][nx] >= '0' && Map[ny][nx] < '0' + 10 && !(cur & temp)) {
					dq.push_back({ ny, nx, cur + temp });
					check[ny][nx][cur + temp] = check[iter.y][iter.x][cur] + 1;
				}
				else if (Map[ny][nx] != 'x' && check[ny][nx][cur] == 0) {
					dq.push_back({ ny, nx, cur });
					check[ny][nx][cur] = check[iter.y][iter.x][cur] + 1;
				}
			}
		}
	}
	cout << -1 << '\n';
	return;
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int w, h;
	char temp;

	while (true) {
		cin >> w >> h;
		if (w == 0 && h == 0) break;

		memset(check, false, sizeof(check));
		memset(Map, 0, sizeof(Map));
		dq.clear();
		ob = 0;

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				cin >> temp;
				Map[y][x] = temp;
				if (temp == 'o') {
					dq.push_back({ y, x, 0 });
					check[y][x][0] = 1;
				}
				else if (temp == '*') {
					Map[y][x] = '0' + ob++;
				}
			}
		}
		search(w, h);
	}

	return 0;
}