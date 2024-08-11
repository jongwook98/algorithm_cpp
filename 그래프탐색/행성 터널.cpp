// Union-Find 공부 1h

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
int parent[100001];
int N, res;
vector<pair<int, int>> v[3];
vector<pair<int, pair<int, int>>> planet;

int Find(int x)
{
	if (parent[x] == x)
		return x;
	return parent[x] = Find(parent[x]);

}

bool SameParent(int a, int b)
{
	a = Find(a);
	b = Find(b);

	if (a != b)
		return false;
	else
		return true;
}

void Union(int a, int b)
{
	a = Find(a);
	b = Find(b);
	if (a != b)
		parent[a] = b;
}

int main(void)
{
	int x, y, z;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> x >> y >> z;
		v[0].push_back(make_pair(x, i));
		v[1].push_back(make_pair(y, i));
		v[2].push_back(make_pair(z, i));
		parent[i] = i;
	}

	sort(v[0].begin(), v[0].end());
	sort(v[1].begin(), v[1].end());
	sort(v[2].begin(), v[2].end());

	for (int i = 0; i < N - 1; i++)
	{
		planet.push_back(make_pair(abs(v[0][i].first - v[0][i + 1].first), make_pair(v[0][i].second, v[0][i + 1].second)));
		planet.push_back(make_pair(abs(v[1][i].first - v[1][i + 1].first), make_pair(v[1][i].second, v[1][i + 1].second)));
		planet.push_back(make_pair(abs(v[2][i].first - v[2][i + 1].first), make_pair(v[2][i].second, v[2][i + 1].second)));
	}
	sort(planet.begin(), planet.end());

	for (int i = 0; i < planet.size(); i++)
	{
		if (!SameParent(planet[i].second.first, planet[i].second.second))
		{
			res += planet[i].first;
			Union(planet[i].second.first, planet[i].second.second);
		}
	}
	cout << res;

}

/*
// 처음에 푼 문제
// 유니온-파인드가 익숙하지 않아서
// 벡터에 저장하면서 했더니 메모리 초과
// 풀어보는 시간 1h 

#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

typedef struct {
	int idx, val;
}info;

bool comp(info a, info b) {
	return a.val < b.val;
}


typedef struct {
	int sidx, bidx, val;
}pq_info;

struct cmp {
	bool operator()(pq_info a, pq_info b) {
		return a.val > b.val;
	}
};

vector<info> xv, yv, zv;
vector<int> pv[100000];

priority_queue<pq_info, vector<pq_info>, cmp> pq;

int min_p_arr[100000];

int N;

void setup(vector<info> cur) {
	sort(cur.begin(), cur.end(), comp);

	int last = int(1e9) + 5;
	int last_p = int(1e9);
	for (auto iter : cur) {
		if (last == iter.val) {
			int max_p = max(min_p_arr[last_p], iter.idx);
			int min_p = min(min_p_arr[last_p], iter.idx);

			min_p_arr[max_p] = min_p;
			pv[min_p].push_back(max_p);
			pv[max_p].clear();
		}
		else if (last_p < N) {
			pq.push({ min(min_p_arr[last_p], iter.idx), max(min_p_arr[last_p], iter.idx), iter.val - last});
			last_p = iter.idx;
		}
		last_p = iter.idx;
		last = iter.val;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	int x, y, z;
	for (int i = 0; i < N; i++) {
		cin >> x >> y >> z;
		xv.push_back({ i, x });
		yv.push_back({ i, y });
		zv.push_back({ i, z });
		pv[i].push_back(i);
		min_p_arr[i] = i;
	}
	
	setup(xv);
	setup(yv);
	setup(zv);

	long long ans = 0;

	//for (int i = 0; i < N; i++) cout << min_p_arr[i] << " ";
	//cout << '\n';

	while (!pq.empty()) {
		auto cur = pq.top(); pq.pop();

		if (min_p_arr[cur.sidx] == min_p_arr[cur.bidx]) continue;

		//for (int i = 0; i < N; i++) cout << min_p_arr[i] << " ";
		//cout << '\n';

		//cout << ans << " " << cur.sidx << " " << cur.bidx << '\n';
		ans += cur.val;

		int clear_v = min_p_arr[cur.bidx];
		for (int iter : pv[min_p_arr[cur.bidx]]) {
			min_p_arr[iter] = min_p_arr[cur.sidx];
			pv[min_p_arr[cur.sidx]].push_back(iter);
		}
		pv[clear_v].clear();
	}

	//for (int i = 0; i < N; i++) cout << min_p_arr[i] << " ";
	//cout << '\n';


	cout << ans;

	return 0;
}
*/