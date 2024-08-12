// 낚시꾼 위치의 상어를 정렬해
// 잡을 수 있는 상어를 바로 확인할 수 있도록
// 큰 상어부터 이동시켜 중복되는 좌표는 먹힌 것으로 판단
// 풀이시간 1h 20m
//
// 풀이시간 단축하려면
// 입력되는 좌표가 0부터 시작하는지, 1부터 시작하는지 확인
// 정렬시키는 함수가 올바르게 작동하는지 확인 (cmp)

#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>

using namespace std;

typedef struct {
	int idx, r, c, s, d, z;
}info;

struct cmp {
	bool operator()(info a, info b) {
		return a.z < b.z;
	}
};

priority_queue<info, vector<info>, cmp> pq;

typedef struct {
	int idx, r, z;
}shark;

bool shark_cmp(shark a, shark b) {
	return a.r < b.r;
}

vector<shark> sv[100];

int dy[5] = { 0, -1, 1, 0, 0 };
int dx[5] = { 0, 0, 0, 1, -1 };

int R, C, M;
bool catched[10000];
bool is_shark[100][100];

info make_correct(info cur) {
	info output = cur;
	
	if (cur.d == 1 || cur.d == 2) {
		int next = cur.r + dy[cur.d] * cur.s;
		while (!(next >= 0 && next < R)) {
			if (next < 0) next = abs(next);
			else if (next >= R) next = 2 * R - 2 - next;

			if (output.d == 1) output.d = 2;
			else output.d = 1;
		}
		output.r = next;
	}
	else {
		int next = cur.c + dx[cur.d] * cur.s;
		while (!(next >= 0 && next < C)) {
			if (next < 0) next = abs(next);
			else if (next >= C) next = 2 * C - 2 - next;

			if (output.d == 3) output.d = 4;
			else output.d = 3;
		}
		output.c = next;
	}

	return output;
}

void shark_move() {
	memset(is_shark, false, sizeof(is_shark));
	priority_queue<info, vector<info>, cmp> temp_pq;

	int next_d = 0;
	int next;

	info tmp;
	while (!pq.empty()) {
		auto cur = pq.top(); pq.pop();
		if (catched[cur.idx]) continue;

		tmp = make_correct(cur);

		if (is_shark[tmp.r][tmp.c]) {
			//cout << "is eaten by another shark" << '\n';
			continue;
		}
		is_shark[tmp.r][tmp.c] = true;

		temp_pq.push(tmp);
		sv[tmp.c].push_back({tmp.idx, tmp.r, tmp.z});
	}
	pq = temp_pq;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> R >> C >> M;
	
	int r, c, s, d, z;
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> s >> d >> z;

		if (d == 1 || d == 2) s %= ((R - 1) * 2);
		else s %= ((C - 1) * 2);

		pq.push({ i, r - 1, c - 1, s, d, z });
		sv[c - 1].push_back({ i, r - 1, z });
	}

	int ans = 0;
	for (int i = 0; i < C; i++) {
		if (!sv[i].empty()) {
			sort(sv[i].begin(), sv[i].end(), shark_cmp);
			auto cur = sv[i][0];

			//cout << "CATCH : " << cur.idx << " " << cur.z << '\n';

			catched[cur.idx] = true;
			ans += cur.z;
		}
		for (int j = 0; j < C; j++) sv[j].clear();
		shark_move();

		//cout << "fisher : " << i << '\n';
		//for (int tx = 0; tx < C; tx++) {
		//	if (!sv[tx].empty()) {
		//		cout << "x : " << tx << '\n';
		//		for (auto iter : sv[tx]) cout << iter.idx << " " << iter.r << " " << iter.z << '\n';
		//		cout << '\n';
		//	}
		//}
	}

	cout << ans << '\n';

	return 0;
}