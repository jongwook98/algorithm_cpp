// 가장 긴 증가하는 부분 수열2 풀이를 그대로 가져오고
// 부분 수열2 풀이에서는 정확한 부분 수열을 가져 올 수 없으므로
// 이 문제에서는 각 숫자가 어느 타이밍에 어떤 곳에 위치하는지 기록하여
// 역순으로 꺼내면 해결 가능
// 
// 문제를 해결하는 전체적인 알고리즘은 다른 사이트 참고

#include<iostream>
#include<vector>
#include<queue>
#include<stack>

using namespace std;

typedef struct {
	int num, idx, value;
}info;

struct cmp {
	bool operator()(info a, info b) {
		if (a.value == b.value) return a.idx < b.idx;
		else return a.value < b.value;
	}
};

priority_queue<info, vector<info>, cmp> pq;
vector<int> v;
stack<int> s;

int N;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	
	int num;
	for (int i = 0; i < N; i++) {
		cin >> num;

		int left = 0, right = int(v.size() - 1), mid = (left + right + 1) / 2;

		while (left <= right) {
			if (num > v[mid]) {
				left = mid + 1;
			}
			else if (num == v[mid]) break;
			else {
				right = mid - 1;
			}
			mid = (left + right + 1) / 2;
		}

		if (mid > int(v.size() - 1) || num > v.back()) {
			v.push_back(num);
			pq.push({ num, i, int(v.size()) });
		}
		else {
			v[mid] = num;
			pq.push({ num, i, mid + 1 });
		}
	}

	cout << v.size() << '\n';

	auto base = pq.top(); pq.pop();
	num = base.num;
	int idx = base.idx, value = base.value;

	s.push(num);

	while (!pq.empty()) {
		auto cur = pq.top(); pq.pop();

		if (value == cur.value || idx < cur.idx || num <= cur.num) continue;
		else {
			value = cur.value; idx = cur.idx, num = cur.num;
			s.push(cur.num);
		}
	}

	while (!s.empty()) {
		cout << s.top() << " ";
		s.pop();
	}

	return 0;
}