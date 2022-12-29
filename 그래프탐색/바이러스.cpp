#include<iostream>
#include<vector>

using namespace std;

vector<int> v[101];
bool check[101];
int ans;

void dfs(int N, int cur) {
	for (int iter : v[cur]) {
		if (!check[iter]) {
			check[iter] = true;
			ans++;

			dfs(N, iter);
		}
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;
	cin >> N >> M;

	int A, B;
	while (M--) {
		cin >> A >> B;
		v[A].push_back(B);
		v[B].push_back(A);
	}

	check[1] = true;
	dfs(N, 1);

	cout << ans << '\n';

	return 0;
}