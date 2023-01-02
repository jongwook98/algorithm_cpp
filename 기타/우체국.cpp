#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// 우체국이 세워지는 위치는 마을 중 하나인 이유
// 우체국에서 마을까지의 거리는 우체국과의 상대거리이기 때문에
// 마을 - 우체국의 절댓값 * 인원 수로 식을 세웠을 때
// 마을이 위치한 곳에서 기울기가 가장 작다.

// 구간합을 이용하여 mid 지점까지의 인원수와 mid + 1 부터 끝지점까지의 인원수를 비교하여
// 왼쪽의 합이 더 큰 경우에 ans와 비교 후 더 적은 값 저장

// 가능한 경우가 여러 가지인 경우에는 더 작은 위치를 출력하도록 해야하기 때문에..

typedef struct {
	int pos, num;
}info;

int ans;

vector<info> v;
vector<long long> sum_;

bool compare(info a, info b) {
	return a.pos < b.pos;
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	sum_.resize(N);

	int pos, num;
	for (int i = 0; i < N; i++) {
		cin >> pos >> num;
		v.push_back({ pos, num });
	}

	sort(v.begin(), v.end(), compare);

	for (int i = 0; i < N; i++) {
		if (i == 0) sum_[i] = v[i].num;
		else sum_[i] = sum_[i - 1] + v[i].num;
	}

	int left = 0;
	int right = N - 1;

	int ans = 1000000;

	while (left <= right) {
		int mid = (left + right) / 2;
		
		long long leftsum = sum_[mid];
		long long rightsum = sum_[N - 1] - sum_[mid];

		if (leftsum >= rightsum) {
			right = mid - 1;
			ans = min(ans, v[mid].pos);
		}
		else left = mid + 1;
	}

	cout << ans << '\n';

	return 0;
}