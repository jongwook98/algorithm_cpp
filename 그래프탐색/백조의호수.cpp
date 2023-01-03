#include<iostream>
#include<deque>
#include<cstring>

using namespace std;

// 함수화를 하지 않아 조금 지저분하지만
// 이 문제는 여러개의 BFS를 잘 굴리면 해결 할 수 있는 문제
// 첫 번째 백조, 두 번째 백조에 대해 각각의 BFS 생성,
// 빙판이 녹는 BFS 생성

// 각각의 방문여부를 따져 다음 사이클에 이미 방문한 곳을 다시 방문하지 않도록
// 설계하면 문제해결

typedef struct {
	int y, x;
	char item;
}pos;

deque<pos> dq;
deque<pos> ndq;

deque<pos> Ldq;
deque<pos> nLdq;

deque<pos> Rdq;
deque<pos> nRdq;

char Map[1500][1500];
bool check[1500][1500];

bool Rcheck[1500][1500];
bool Lcheck[1500][1500];

int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int R, C;
	cin >> R >> C;

	char temp;
	bool sec = false;
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			cin >> temp;
			Map[y][x] = temp;
			if (temp == 'L' && !sec) {
				Map[y][x] = 'R';
				nRdq.push_back({ y, x, 'R' });
				sec = true;
			}
			else if (temp == 'L' && sec) {
				nLdq.push_back({ y, x, 'L' });
			}
		}
	}

	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			if (!check[y][x] && Map[y][x] != 'X') {
				check[y][x] = true;
				dq.push_back({ y, x, Map[y][x] });
				while (!dq.empty()) {
					auto iter = dq.front(); dq.pop_front();
					int cy = iter.y; int cx = iter.x; char cur = iter.item;

					for (int i = 0; i < 4; i++) {
						int ny = cy + dy[i]; int nx = cx + dx[i];
						if (ny >= 0 && ny < R && nx >= 0 && nx < C && !check[ny][nx]) {
							check[ny][nx] = true;
							if (Map[ny][nx] == 'X') {
								ndq.push_back({ ny, nx, '.' });
							}
							else dq.push_back({ ny, nx, '.'});
						}
					}
				}
			}
		}
	}

	int ans = 0;
	while (true) {

		deque<pos> Ldq(nLdq);
		deque<pos> Rdq(nRdq);
		deque<pos> dq(ndq);

		nLdq.clear(); nRdq.clear(); ndq.clear();

		while (!Ldq.empty()) {
			auto iter = Ldq.front(); Ldq.pop_front();
			int cy = iter.y; int cx = iter.x; char cur = iter.item;

			for (int i = 0; i < 4; i++) {
				int ny = cy + dy[i]; int nx = cx + dx[i];
				if (ny >= 0 && ny < R && nx >= 0 && nx < C && !Lcheck[ny][nx]) {
					Lcheck[ny][nx] = true;
					if (Map[ny][nx] == 'X') {
						nLdq.push_back({ ny, nx, cur });
					}
					else if (Rcheck[ny][nx]) {
						cout << ans << '\n';
						return 0;
					}
					else Ldq.push_back({ ny, nx, cur });
				}
			}
		}

		while (!Rdq.empty()) {
			auto iter = Rdq.front(); Rdq.pop_front();
			int cy = iter.y; int cx = iter.x; char cur = iter.item;

			for (int i = 0; i < 4; i++) {
				int ny = cy + dy[i]; int nx = cx + dx[i];
				if (ny >= 0 && ny < R && nx >= 0 && nx < C && !Rcheck[ny][nx]) {
					Rcheck[ny][nx] = true;
					if (Map[ny][nx] == 'X') {
						nRdq.push_back({ ny, nx, cur });
					}
					else if (Lcheck[ny][nx]) {
						cout << ans << '\n';
						return 0;
					}
					else Rdq.push_back({ ny, nx, cur });
				}
			}
		}

		while (!dq.empty()) {
			auto iter = dq.front(); dq.pop_front();
			int cy = iter.y; int cx = iter.x; char cur = iter.item;
			if (Map[cy][cx] == 'X') Map[cy][cx] = '.';

			for (int i = 0; i < 4; i++) {
				int ny = cy + dy[i]; int nx = cx + dx[i];
				if (ny >= 0 && ny < R && nx >= 0 && nx < C && !check[ny][nx]) {
					check[ny][nx] = true;
					if (Map[ny][nx] == 'X') {
						ndq.push_back({ ny, nx, '.' });
					}
					else dq.push_back({ ny, nx, '.' });
				}
			}
		}
		ans++;
	}

	cout << ans << '\n';

	return 0;
}