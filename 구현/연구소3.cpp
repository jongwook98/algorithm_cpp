#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>

#define MAX 1234567

using namespace std;

typedef struct {
	int y, x;
}pos;

int N, M;
int Mvir;

bool check[50][50];

int Map[50][50];
int area = 0;

int ans = MAX;

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

vector<pos> sel;
vector<pos> virus;

void cal() {
	memset(check, false, sizeof(check));
	int time = 0, gone = 0;

	queue<pos> q;
	for (auto iter : sel) q.push(iter);
	
	while (!q.empty() && gone < area) {
		int rep = q.size();
		while (rep--) {
			int cy = q.front().y; int cx = q.front().x; q.pop();

			for (int i = 0; i < 4; i++) {
				int ny = cy + dy[i]; int nx = cx + dx[i];

				if (ny >= 0 && ny < N && nx >= 0 && nx < N && !check[ny][nx]) {
					if (Map[ny][nx] == 0) {
						gone++; check[ny][nx] = true;
						q.push({ ny, nx });
					}
					else if (Map[ny][nx] == 2) {
						check[ny][nx] = true;
						q.push({ ny, nx });
					}
				}
			}
		}
		time++;
	}
	if (gone == area) ans = min(ans, time);
}

void comb(int r, int cur) {
	if (r == M) cal();

	else {
		for (int i = cur; i < Mvir; i++) {
			sel.push_back(virus[i]);
			comb(r + 1, i + 1);
			sel.pop_back();
		}
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N >> M;

	int kind;
	for (int y = 0; y < N; y++) for (int x = 0; x < N; x++) {
		cin >> kind;
		if (kind == 2) virus.push_back({ y, x });
		else if (kind == 0) area++;
		Map[y][x] = kind;
	}

	Mvir = virus.size();
	comb(0, 0);

	if (ans == MAX) cout << -1 << '\n';
	else cout << ans << '\n';

	return 0;
}