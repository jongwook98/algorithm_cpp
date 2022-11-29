#include<iostream>
#include<deque>
#include<algorithm>

#define MAX 2147000000

using namespace std;

typedef struct {
	int time, index;
}info;

deque<info> A;
deque<info> B;
deque<info> C;
deque<info> D;

int ans[200000];

int min_time(int out_t) {
	int A_t, B_t, C_t, D_t;
	if (A.empty()) A_t = MAX; else A_t = A.front().time;
	if (B.empty()) B_t = MAX; else B_t = B.front().time;
	if (C.empty()) C_t = MAX; else C_t = C.front().time;
	if (D.empty()) D_t = MAX; else D_t = D.front().time;

	int min_out = min({ A_t, B_t, C_t, D_t });

	if (min_out < out_t) return out_t;
	else return min_out;
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, in_t;
	char pos;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> in_t >> pos;
		if (pos == 'A') A.push_back({ in_t, i });
		else if (pos == 'B') B.push_back({ in_t, i });
		else if (pos == 'C') C.push_back({ in_t, i });
		else if (pos == 'D') D.push_back({ in_t, i });
	}

	int out_t = 0;
	while (!A.empty() || !B.empty() || !C.empty() || !D.empty()) {
		bool go[4] = { false, false, false, false };
		out_t = min_time(out_t);

		if (!A.empty() && A.front().time <= out_t) {
			if (D.empty()) go[0] = true;
			else if (D.front().time > out_t) go[0] = true;
		}
		if (!B.empty() && B.front().time <= out_t) {
			if (go[0] == false) {
				if (A.empty()) go[1] = true;
				else if (A.front().time > out_t) go[1] = true;
			}
		}
		if (!C.empty() && C.front().time <= out_t) {
			if (go[1] == false) {
				if (B.empty()) go[2] = true;
				else if (B.front().time > out_t) go[2] = true;
			}
		}
		if (!D.empty() && D.front().time <= out_t) {
			if (go[2] == false) {
				if (C.empty()) go[3] = true;
				else if (C.front().time > out_t) go[3] = true;
			}
		}

		int idx;
		if (go[0] == true) {
			idx = A.front().index;
			ans[idx] = out_t;
			A.pop_front();
		}
		if (go[1] == true) {
			idx = B.front().index;
			ans[idx] = out_t;
			B.pop_front();
		}
		if (go[2] == true) {
			idx = C.front().index;
			ans[idx] = out_t;
			C.pop_front();
		}
		if (go[3] == true) {
			idx = D.front().index;
			ans[idx] = out_t;
			D.pop_front();
		}

		if (go[0] == false && go[1] == false && go[2] == false && go[3] == false) {
			while (!A.empty()) {
				ans[A.front().index] = -1;
				A.pop_front();
			}
			while (!B.empty()) {
				ans[B.front().index] = -1;
				B.pop_front();
			}
			while (!C.empty()) {
				ans[C.front().index] = -1;
				C.pop_front();
			}
			while (!D.empty()) {
				ans[D.front().index] = -1;
				D.pop_front();
			}

			break;
		}
		out_t++;
	}

	for (int i = 0; i < N; i++) {
		cout << ans[i] << '\n';
	}

	return 0;
}