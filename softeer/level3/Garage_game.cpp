#include<iostream>
#include<deque>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;

// 처음에 deque를 이용하여 구현
// -> 문제점 다시 복구할 때 하나하나 빼서 복구해야 하므로 속도가 굉장히 느리다
// 메모이제이션으로 배열을 만들어 memcpy 하는 것이 훨씬 빠른 방법

// 추가로 이 문제는 최대한 최적화를 해야 겨우 통과하는 문제이다
// 차고를 포함하는 최소의 직사각형을 구하기 위해 저장해놓은 my, MY, mx, MX 를 이용하여
// 배열값을 갱신하는 알고리즘을 최적화한다.

typedef struct {
	int y, x;
}pos;

deque<pos> dq;
vector<pos> v;
int total[45][15];
int idx[15];

int gar[15][15];
int ans;

int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };

void sel(int N, int cnt, int cur);

void cal(int N, int cnt, int cur) {

	int sco = 0;
	int my = 14, mx = 14, MY = 0, MX = 0;

	sco += v.size();

	while (!v.empty()) {
		int cy = v.back().y; int cx = v.back().x;
		v.pop_back();
		my = min(my, cy); mx = min(mx, cx);
		MY = max(MY, cy); MX = max(MX, cx);

		gar[cy][cx] = 0;
	}

	sco += (MY - my + 1) * (MX - mx + 1);

	int idxx[15];
	memcpy(idxx, idx, sizeof(idx));

	int ccc[15];
	for (int i = 0; i < 15; i++) ccc[i] = my;
	//memset(ccc, 0, sizeof(ccc));

	for (int x = mx; x <= MX; x++) {
		for (int y = my; y < N; y++) {
			if (gar[y][x] != 0) {
				gar[ccc[x]++][x] = gar[y][x];
			}
		}
		for (int y = ccc[x]; y < N; y++) {
			if (idx[x] < 45) {
				gar[y][x] = total[idx[x]++][x];
			}
		}
	}

	//cout << "SCO : " << sco << " CUR : " << cur << " CNT : " << cnt << '\n';

	/*for (int y = 0; y < N; y++){
		for (int x = 0; x < N; x++) cout << gar[y][x] << " ";
		cout << '\n';
	}*/

	sel(N, cnt + 1, cur + sco);

	memcpy(idx, idxx, sizeof(idxx));
}

void sel(int N, int cnt, int cur) {
	if (cnt >= 3) {
		ans = max(ans, cur);
		return;
	}

	int copy_gar[15][15];
	memcpy(copy_gar, gar, sizeof(gar));

	bool check[15][15];
	memset(check, false, sizeof(check));

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (!check[y][x]) {
				check[y][x] = true;

				dq.push_back({ y, x });
				v.push_back({ y, x });

				while (!dq.empty()) {
					int cy = dq.front().y; int cx = dq.front().x;
					dq.pop_front();
					for (int i = 0; i < 4; i++) {
						int ny = cy + dy[i]; int nx = cx + dx[i];

						if (ny >= 0 && ny < N && nx >= 0 && nx < N) {
							if (!check[ny][nx] && gar[ny][nx] == gar[cy][cx]) {
								check[ny][nx] = true;
								dq.push_back({ ny, nx });
								v.push_back({ ny, nx });
							}
						}
					}
				}
				cal(N, cnt, cur);

				memcpy(gar, copy_gar, sizeof(copy_gar));
			}
		}
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	int col;
	for (int y = 3 * N - 1; y >= 0; y--) {
		for (int x = 0; x < N; x++) {
			cin >> total[y][x];
		}
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			gar[y][x] = total[y][x];
			idx[x]++;
		}
	}

	//for (int y = 0; y < N; y++){
	//	for (int x = 0; x < N; x++) cout << gar[y][x] << " ";
	//	cout << '\n';
	//}

	sel(N, 0, 0);
	cout << ans << '\n';

	return 0;
}