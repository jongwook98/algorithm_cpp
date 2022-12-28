#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

typedef struct {
	int sp, ep;
}info;

struct compare {
	bool operator()(info a, info b) {
		if (a.sp != b.sp) return a.sp > b.sp;
		return a.ep > b.ep;
	}
};

priority_queue<info, vector<info>, compare> pq;

int sp = -1000000001;
int ep = -1000000001;

int ans;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	int csp, cep;
	while (N--) {
		cin >> csp >> cep;
		pq.push({ csp, cep });
	}

	while (!pq.empty()) {
		csp = pq.top().sp; cep = pq.top().ep;
		pq.pop();

		if (csp > ep) {
			ans += ep - sp;
			sp = csp;
			ep = cep;
		}
		else {
			ep = max(ep, cep);
		}
	}
	ans += ep - sp;
	cout << ans << '\n';

	return 0;
}