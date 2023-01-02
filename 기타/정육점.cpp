#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

typedef struct {
	int w, p;
}info;

struct compare {
	bool operator()(info a, info b) {
		if (a.p != b.p) return a.p > b.p;
		return a.w < b.w;
	}
};

priority_queue<info, vector<info>, compare> pq;
vector<int> v;

// 같은 가격의 고기를 여러개 사는 것과 한 단계 높은 고기를 사는 것을 비교해야함

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;
	cin >> N >> M;

	int w, p;
	for (int i = 0; i < N; i++) {
		cin >> w >> p;
		pq.push({ w, p });
	}

	int cur_p = -1;
	int sum_ = 0;
	int cur_sum_ = 0;
	int cur_pri_ = 0;

	int ans = -1;

	while (!pq.empty()) {
		auto iter = pq.top(); pq.pop();

		if (cur_p != iter.p) {
			cur_p = iter.p;
			sum_ += cur_sum_;
			cur_sum_ = iter.w;
			cur_pri_ = iter.p;
		}
		else {
			if (sum_ + cur_sum_ + iter.w >= M) {
				if (ans == -1) ans = cur_pri_ + iter.p;
				ans = min(ans, cur_pri_ + iter.p);
			}
			cur_sum_ += iter.w;
			cur_pri_ += iter.p;
		}
		if (sum_ + iter.w >= M) {
			if (ans != -1) cout << min(ans, iter.p) << '\n';
			else cout << iter.p << '\n';
			return 0;
		}
	}

	if (ans != -1) cout << ans << '\n';
	else cout << -1 << '\n';
	return 0;
}