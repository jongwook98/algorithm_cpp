#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>

#define MAX 987654321

using namespace std;

int area[5];

int N;
int Map[21][21];

int ans = MAX;
int total = 0;

bool check[21][21];

void cal(int y, int x, int d1, int d2) {
	memset(check, false, sizeof(check));
	memset(area, 0, sizeof(area));
	vector<int> arr;

	for (int i = 0; i <= d1; i++) {
		check[y + i][x - i] = true;
	}
	for (int i = 1; i <= d2; i++) {
		check[y + i][x + i] = true;
	}
	for (int i = 0; i <= d2; i++) {
		check[y + d1 + i][x - d1 + i] = true;
	}
	for (int i = 0; i <= d1; i++) {
		check[y + d2 + i][x + d2 - i] = true;
	}

	for (int r = 1; r < y + d1; r++) {
		for (int c = 1; c <= x; c++) {
			if (check[r][c]) break;
			area[0] += Map[r][c];
		}
	}

	for (int r = 1; r <= y + d2; r++) {
		for (int c = N; c > x; c--) {
			if (check[r][c]) break;
			area[1] += Map[r][c];
		}
	}

	for (int r = y + d1; r <= N; r++) {
		for (int c = 1; c < x - d1 + d2; c++) {
			if (check[r][c]) break;
			area[2] += Map[r][c];
		}
	}

	for (int r = y + d2 + 1; r <= N; r++) {
		for (int c = N; c >= x - d1 + d2; c--) {
			if (check[r][c]) break;
			area[3] += Map[r][c];
		}
	}

	area[4] = total - area[0] - area[1] - area[2] - area[3];

	arr.push_back(area[0]);
	arr.push_back(area[1]);
	arr.push_back(area[2]);
	arr.push_back(area[3]);
	arr.push_back(area[4]);

	sort(arr.begin(), arr.end());

	//cout << area[0] << " " << area[1] << " " << area[2] << " " << area[3] << " " << area[4] << '\n';

	ans = min(ans, arr[4] - arr[0]);
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N;

	int num;
	for (int y = 1; y <= N; y++) for (int x = 1; x <= N; x++) {
		cin >> num;
		Map[y][x] = num;
		total += num;
	}

	for (int y = 1; y <= N - 2; y++) {
		for (int d1 = 1; d1 <= N - y - 1; d1++) {
			for (int d2 = 1; d2 <= N - y - d1; d2++) {
				for (int x = 1 + d1; x <= N - d2; x++) {
					cal(y, x, d1, d2);
				}
			}
		}
	}

	cout << ans << '\n';

	return 0;
}