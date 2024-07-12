#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

int ans = 0;
char Map[21][21];

bool c_alpha[26];
bool check[21][21];

int R, C;

void dfs(int cy, int cx, int num) {
	ans = max(ans, num);

	for (int i = 0; i < 4; i++) {
		int ny = cy + dy[i]; int nx = cx + dx[i];
		if (ny >= 0 && ny < R && nx >= 0 && nx < C) {
			if (check[ny][nx] == false && c_alpha[Map[ny][nx] - 'A'] == false) {
				
				check[ny][nx] = true; c_alpha[Map[ny][nx] - 'A'] = true;
				dfs(ny, nx, num + 1);
				check[ny][nx] = false; c_alpha[Map[ny][nx] - 'A'] = false;
			}
		}
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> R >> C;
	cin.ignore();
	
	string str;

	for (int i = 0; i < R; i++) {
		getline(cin, str);
		int j = 0;
		for (char ch : str) {
			Map[i][j++] = ch;
		}
	}

	c_alpha[Map[0][0] - 'A'] = true;
	check[0][0] = true;

	dfs(0, 0, 1);

	cout << ans << '\n';

	return 0;
}