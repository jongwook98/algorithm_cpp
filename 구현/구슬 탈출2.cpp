#include<iostream>
#include<string>
#include<queue>

using namespace std;

typedef struct {
	int ry, rx;
	int by, bx;
	int cnt;
	bool fail;
}q_info;

queue<q_info> q;

int N, M;
char Map[10][10];
bool check[100][100]; // y * 10 + x;

int dy[4] = { 0, 0, -1, 1 };
int dx[4] = { -1, 1, 0, 0 };
int gy, gx;

string str;

q_info move_ball(int ry, int rx, int by, int bx, int cnt, int d) {
	bool flag = true;
	bool Rflag = false;
	bool Bflag = false;

	bool Rgflag = false;
	bool Bgflag = false;
	
	while (flag) {
		flag = false;

		int nry = ry + dy[d]; int nrx = rx + dx[d];
		int nby = by + dy[d]; int nbx = bx + dx[d];

		if (Map[nry][nrx] != '#') {
			if (nry == by && nrx == bx) Bflag = true;
			else if (Map[nry][nrx] == '.') {
				ry = nry; rx = nrx;
				flag = true;
			}
			else if (Map[nry][nrx] == 'O') Rgflag = true;
		}

		if (Map[nby][nbx] != '#') {
			if (nby == ry && nbx == rx) Rflag = true;
			else if (Map[nby][nbx] == '.') {
				by = nby; bx = nbx;
				flag = true;
			}
			else if (Map[nby][nbx] == 'O') Bgflag = true;
		}
	}

	if (Rgflag || Bgflag) {
		if (Bflag || Rflag) return { ry, rx, by, bx, cnt + 1, true };
		else if (Rgflag == true) return { gy, gx, by, bx, cnt + 1, false };
		else return { ry, rx, by, bx, cnt + 1, true };
	}
	else if (Bflag || Rflag) {
		if (Bflag) return { by - dy[d], bx - dx[d], by, bx, cnt + 1, false };
		else return { ry, rx, ry - dy[d], rx - dx[d], cnt + 1, false };
	}
	else return { ry, rx, by, bx, cnt + 1, false };
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	cin.ignore();
	
	int ry = 0, rx = 0, by = 0, bx = 0;

	for (int i = 0; i < N; i++) {
		getline(cin, str);
		int j = 0;
		for (char ch : str) {
			if (ch == 'R') {
				ry = i; rx = j;
				Map[i][j++] = '.';
			}
			else if (ch == 'B') {
				by = i; bx = j;
				Map[i][j++] = '.';
			}
			else if (ch == 'O') {
				gy = i; gx = j;
				Map[i][j++] = ch;
			}
			else Map[i][j++] = ch;
		}
	}

	check[ry * 10 + rx][by * 10 + bx] = true;
	q.push({ ry, rx, by, bx, 0, false });

	int ans = -1;
	while (!q.empty() && ans == -1) {
		auto cur = q.front(); q.pop();
		if (cur.cnt >= 10) break;

		//cout << "cur : " << cur.ry << " " << cur.rx << " " << cur.by << " " << cur.bx << " " << cur.cnt << '\n';

		q_info next;
		for (int i = 0; i < 4; i++) {
			next = move_ball(cur.ry, cur.rx, cur.by, cur.bx, cur.cnt, i);

			if (next.fail == true) continue;

			if (next.ry == gy && next.rx == gx) ans = next.cnt;

			if (!check[next.ry * 10 + next.rx][next.by * 10 + next.bx]) {
				check[next.ry * 10 + next.rx][next.by * 10 + next.bx] = true;
				q.push(next);
			}
		}
	}

	cout << ans;

	return 0;
}