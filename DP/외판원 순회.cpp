// 정말 유명한 외판원 순회 문제
// 푸는 방법을 떠올릴 수 없어서 공부한 부분
// 
// 외판원 순회 즉, 모든 도시를 방문하고 다시 돌아오는 경우는
// 첫 시작 도시에 따라 값이 달라질 것 같지만,
// 시작 도시가 달라져도 순서만 달라질 뿐
// 결국 가장 짧은 루트로 탐색된다.
// 그래서 0번 도시에서 출발한 것으로 가정한다.
//
// dfs의 전체 출력이 한 번인 이유는 모든 가능한 경로를
// 중복 없이 검사한 후, 가장 짧은 패스의 값을 갖는 것을 출력한다.

#include<iostream>
#include<algorithm>
#include<cstring>

#define INF int(1e9);

using namespace std;

int N;
int W[16][16];
int DP[16][1 << 16];

int dfs(int cur, int visit) {

	if (visit == (1 << N) - 1) { // 탐색 완료
		if (W[cur][0] == 0) return INF; // 이동 불가능
		return W[cur][0];
	}

	if (DP[cur][visit] != -1) { // 이미 탐색했으면
		return DP[cur][visit];
	}

	DP[cur][visit] = INF; // 탐색안한 곳 INF로 초기화

	for (int i = 0; i < N; i++) {
		if (W[cur][i] == 0) continue; // 길이 없을 때,
		if ((visit & (1 << i)) == (1 << i)) continue; // 이미 방문 했을 때,

		DP[cur][visit] = min(DP[cur][visit], W[cur][i] + dfs(i, visit | 1 << i));
	}

	return DP[cur][visit];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) cin >> W[i][j];
	}

	memset(DP, -1, sizeof(DP));
	cout << dfs(0, 1);

	return 0;
}