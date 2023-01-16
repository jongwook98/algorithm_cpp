#include<iostream>
#include<deque>
#include<cstring>
#include<string>
#include<vector>

using namespace std;

// 문의 종류별로 좌표 저장
// 빈 공간, 열쇠, 문서인 맵을 방문하지 않았다면 deque 구조에 넣고 check.place로 deque에 넣음을 확인
// 다음 deque에서 빠져나온 것이 문서, 열쇠일 때

// 1. 문서
// 전체 문서 개수에서 -1, 찾은 문서 + 1 하고 남은 문서가 0일 때 종료

// 2. 열쇠
// 사용하지 않은 열쇠라면 해당되는 모든 문을 열고 -> '.' 방문 가능한 곳인지 확인
// 가능한 곳이라면 deque에 넣고 place : true

// 현재 좌표에서 4방향으로 뻗어나갈 수 있으므로 4방향은 방문 가능한 것으로 체크

typedef struct {
	int y, x;
}pos;

typedef struct {
	bool possi;
	bool place;
}info;

vector<pos> door[26];
bool key[26];
info check[100][100];

char Map[100][100];
string str;

deque<pos> dq;

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int T;
	cin >> T;

	while (T--) {
		int h, w;
		cin >> h >> w;

		int cnt = 0;

		for (int y = 0; y < h; y++) {
			cin >> str;
			int x = 0;
			for (char ch : str) {
				if (ch == '$') cnt++;
				else if (ch >= 'A' && ch <= 'Z') door[ch - 'A'].push_back({ y, x });
				Map[y][x++] = ch;
			}
		}

		cin >> str;
		if (str != "0") {
			for (char ch : str) {
				if (key[ch - 'a'] == false) {
					key[ch - 'a'] = true;
					for (auto iter : door[ch - 'a']) Map[iter.y][iter.x] = '.';
				}
			}
		}

		if (cnt == 0) {
			cout << "0" << '\n';
			continue;
		}

		for (int x = 0; x < w; x++) {
			check[0][x].possi = true;
			if (check[0][x].place == false && (Map[0][x] == '.' || Map[0][x] == '$' || (Map[0][x] >= 'a' && Map[0][x] <= 'z'))) {
				check[0][x].possi = true; check[0][x].place = true;
				dq.push_back({ 0, x });
			}

			check[h - 1][x].possi = true;
			if (check[h - 1][x].place == false && (Map[h - 1][x] == '.' || Map[h - 1][x] == '$' || (Map[h - 1][x] >= 'a' && Map[h - 1][x] <= 'z'))) {
				check[h - 1][x].possi = true; check[h - 1][x].place = true;
				dq.push_back({ h - 1, x });
			}
		}

		for (int y = 0; y < h; y++) {
			check[y][0].possi = true;
			if (check[y][0].place == false && (Map[y][0] == '.' || Map[y][0] == '$' || (Map[y][0] >= 'a' && Map[y][0] <= 'z'))) {
				check[y][0].possi = true; check[y][0].place = true;
				dq.push_back({ y, 0 });
			}

			check[y][w - 1].possi = true;
			if (check[y][w - 1].place == false && (Map[y][w - 1] == '.' || Map[y][w - 1] == '$' || (Map[y][w - 1] >= 'a' && Map[y][w - 1] <= 'z'))) {
				check[y][w - 1].possi = true; check[y][w - 1].place = true;
				dq.push_back({ y, w - 1 });
			}
		}

		int ans = 0;
		while (!dq.empty()) {
			int cy = dq.front().y; int cx = dq.front().x; dq.pop_front();
			char cur = Map[cy][cx];

			//cout << "cy : " << cy << " cx : " << cx << " cur : " << cur << '\n';

			if (cur == '$') {
				ans++; cnt--;
				if (cnt == 0) break;
			}
			else if (cur >= 'a' && cur <= 'z' && key[cur - 'a'] == false) {
				key[cur - 'a'] = true;
				for (auto iter : door[cur - 'a']) {
					Map[iter.y][iter.x] = '.';

					if (check[iter.y][iter.x].possi == true && check[iter.y][iter.x].place == false) {
						check[iter.y][iter.x].place = true;
						dq.push_back({ iter.y, iter.x });
					}
				}
			}

			for (int i = 0; i < 4; i++) {
				int ny = cy + dy[i]; int nx = cx + dx[i];
				
				if (ny >= 0 && ny < h && nx >= 0 && nx < w) {
					check[ny][nx].possi = true;
					if (check[ny][nx].place == false && (Map[ny][nx] == '.' || Map[ny][nx] == '$' || (Map[ny][nx] >= 'a' && Map[ny][nx] <= 'z'))) {
						if (check[ny][nx].possi == true && check[ny][nx].place == false) {
							check[ny][nx].place = true;
							dq.push_back({ ny, nx });
						}
					}
				}
			}
		}

		cout << ans << '\n';

		dq.clear();
		for (int i = 0; i < 26; i++) door[i].clear();
		memset(key, false, sizeof(key));
		memset(check, false, sizeof(check));
	}

	return 0;
}