// 비숍을 두 구간으로 나누어 시간 복잡도 줄이기

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef struct {
	int y, x;
}pos;

int N;
vector<pos> posv[2];
vector<pos> putv[2];

int ans[2] = { 0, 0 };

bool is_possible(int color, int y, int x) {
	for (pos iter : putv[color]) {
		if (abs(iter.y - y) - abs(iter.x - x) == 0) return false;
	}
	return true;
}

void dfs(int color, int cnt) {
	if (is_possible(color, posv[color][cnt].y, posv[color][cnt].x)) {
		putv[color].push_back({posv[color][cnt].y, posv[color][cnt].x});
		ans[color] = max(ans[color], int(putv[color].size()));
		
		if (cnt + 1 < posv[color].size()) dfs(color, cnt + 1);
		putv[color].pop_back();
		if (cnt + 1 < posv[color].size()) dfs(color, cnt + 1);
	}
	else if (cnt + 1 < posv[color].size()) dfs(color, cnt + 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	bool puton;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> puton;
			if (puton == true) {
				if (i % 2 == j % 2) posv[0].push_back({ i, j });
				else posv[1].push_back({ i, j });
			}
		}
	}

	if (posv[0].size() > 0)	dfs(0, 0);
	if (posv[1].size() > 0) dfs(1, 0);

	cout << ans[0] + ans[1];

	return 0;
}