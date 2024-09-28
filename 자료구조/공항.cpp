// Union-Find 문제
// 분리집합을 이용해서
// x 이하인 가장 큰 수를 빠르게 찾을 수 있다.

#include <iostream>
#include <vector>

using namespace std;

int Find(int* parent, int p) {
	if (parent[p] != p) {
		return parent[p] = Find(parent, parent[p]);
	}
	return p;
}

bool Union(int* parent, int a, int b) {
	int pa = Find(parent, a);
	int pb = Find(parent, b);

	if (pa != pb) {
		if (pa < pb)
			parent[pb] = parent[pa];
		else
			parent[pa] = parent[pb];
		return true;
	}
	else return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int G, P;
	int parent[100001] = { 0 };

	cin >> G >> P;
	for (int i = 0; i <= G; i++) parent[i] = i;
	
	vector<int> v;
	v.reserve(P);

	int tmp;
	for (int i = 0; i < P; i++) {
		cin >> tmp;
		v.push_back(tmp);
	}
	int ans = 0;
	for (int plane : v) {
		if (Find(parent, plane) != 0) {
			if (Union(parent, Find(parent, plane) - 1, Find(parent, plane)) == false)
				break;
		}
		else break;
		ans++;
	}
	cout << ans;

	return 0;
}