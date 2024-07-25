// 수열의 크기가 1,000,000 이므로
// 적절한 위치 찾는 알고리즘을 O(logN) 시간에 찾아야 함 => 이분 탐색 생각해야 함
//
// 문제를 해결하는 전체적인 알고리즘은 다른 사이트 참고

#include<iostream>
#include<vector>

using namespace std;

vector<int> v;

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

		if (mid > int(v.size() - 1) || num > v.back()) v.push_back(num);
		else v[mid] = num;
	}

	cout << v.size() << '\n';

	return 0;
}