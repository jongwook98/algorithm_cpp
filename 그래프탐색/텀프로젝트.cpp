#include<iostream>
#include<cstring>

using namespace std;

// 시간초과를 줄이는 방법을 모르겠어서 다른 블로그 참조

// 처음 시간초과를 해결하는 방법

// -> 1번 dfs로 1번을 포함하지 않는 사이클을 발견했을 때
// 그 해당 사이클에 포함된 번호와 찾아가는 과정에서 지나친 노드들에 대해서
// 다시 방문하지 않도록 해야 O(N) 복잡도로 해결 할 수 있음

// 새로운 방문정보를 만들어 해당 배열은 다시 방문할 가능성이 없는 경우에만 체크
// 사이클이 형성될 경우 사이클에 포함된 노드들을 더하고, 전체 학생 수에서 빼서 답을 구한다..

int fol[100001];
bool check[100001];
bool check_dfs[100001];

int ans = 0;

void dfs(int cur, int N) {

	check_dfs[cur] = true;
	int next = fol[cur];

	if (!check_dfs[next]) {
		dfs(next, N);
	}
	else if (!check[next]) {
		for (int i = next; i != cur; i = fol[i]) {
			ans++;
			cout << "i : " << i << " ";
		}
		cout << '\n';
		ans++;
	}
	check[cur] = true;
};

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int T;
	cin >> T;

	while (T--) {
		int N;
		cin >> N;

		for (int i = 1; i <= N; i++) cin >> fol[i];

		for (int i = 1; i <= N; i++) {
			if (!check[i]) {
				dfs(i, N);
			}
		}

		cout << N - ans << '\n';

		ans = 0;
		memset(check, false, sizeof(check));
		memset(check_dfs, false, sizeof(check_dfs));
	}


	return 0;
}