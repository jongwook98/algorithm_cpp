#include<iostream>
#include<vector>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

typedef struct {
	int y, x;
}pos;

pos point[20];
bool check[20];

int N;
pos onevect;
double ans;

void cal() {
	onevect = { 0, 0 };
	for (int i = 0; i < N; i++) {
		if (check[i]) {
			onevect.y -= point[i].y;
			onevect.x -= point[i].x;
		}
		else {
			onevect.y += point[i].y;
			onevect.x += point[i].x;
		}
	}
	ans = min(ans, sqrt(pow(onevect.y, 2) + pow(onevect.x, 2)));
}

void dfs(int cur, int cnt) {
	if (cnt >= N / 2) {
		cal();
		return;
	}
	for (int i = cur; i < N; i++) {
		check[i] = true;
		dfs(i + 1, cnt + 1);
		check[i] = false;
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cout << fixed; // 소수점을 고정시켜 표현   -->> cout.unsetf(ios::fixed); 를 이용하여 cout.fixed 초기화 할 수 있다..?
	cout.precision(7); // 숫자 n 자리까지 출력 -> 상단에 fixed를 사용하면 소수 자리수를 표시

	int T;
	cin >> T;

	while (T--) {
		memset(point, 0, sizeof(point));
		memset(check, false, sizeof(check));
		ans = 1e9;

		cin >> N;

		for (int i = 0; i < N; i++) {
			cin >> point[i].y >> point[i].x;
		}
		dfs(0, 0);
		cout << ans << '\n';
	}

	return 0;
}