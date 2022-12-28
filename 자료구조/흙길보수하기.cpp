#include<iostream>
#include<queue>
#include<vector>

using namespace std;

typedef struct {
	int sp, ep;
}info;

struct compare{
	bool operator()(info a, info b) {
		return a.sp > b.sp;
	}
};

priority_queue<info, vector<info>, compare> pq;

int cnt;
int cur = -1;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, L;
	cin >> N >> L;

	int csp, cep;
	while (N--) {
		cin >> csp >> cep;
		pq.push({ csp, cep });
	}

	while (!pq.empty()) {
		csp = pq.top().sp; cep = pq.top().ep;
		pq.pop();

		int ccnt = 0;

		//cout << "cur : " << cur << " cnt : " << cnt << '\n';

		if (cep - 1 > cur) {
			if (cur >= csp) {
				csp = cur + 1;
			}
			if (csp == cep) {
				cnt += 1;
				cur = csp + L - 1;
			}
			else {
				ccnt = (cep - csp) / L;
				if ((cep - csp) % L != 0) ccnt++;

				cur = csp + L * ccnt - 1;
			}
		}
		cnt += ccnt;

		//cout << "cur : " << cur << " cnt : " << cnt << '\n';

	}

	cout << cnt << '\n';

	return 0;
}