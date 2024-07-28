// 투포인터 풀이
// 실행 시간 : 28ms;

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<long long> v;
int N;

long long ans = 30000000001;
int arr[3];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	long long num;
	for (int i = 0; i < N; i++) {
		cin >> num;
		v.push_back(num);
	}

	sort(v.begin(), v.end(), less<long long>());

	for (int left = 0; left < N - 2; left++) {
		int right = N - 1, mid = left + 1;
		
		while (mid < right) {
			long long sum = v[left] + v[right] + v[mid];

			if (abs(sum) < ans) {
				ans = abs(sum);
				arr[0] = v[left];
				arr[1] = v[mid];
				arr[2] = v[right];
			}

			if (sum < 0) mid++;
			else right--;
		}
	}

	for (int i = 0; i < 3; i++) cout << arr[i] << " ";

	return 0;
}



// 첫 풀이
// 소요 시간 : 45m, 실행 시간 : 404ms;
// 왼쪽, 오른쪽을 정해놓고 mid 값을 이분 탐색하는 알고리즘으로 풀었다.
// 이 문제는 투포인터를 사용할 때 더 적은 시간이 소요된다고 함

/*
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<long long int> v;
int N;

long long int ans = 30000000001;
vector<int> ans_v;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	
	long long int num;
	for (int i = 0; i < N; i++) {
		cin >> num;
		v.push_back(num);
	}

	sort(v.begin(), v.end(), less<long long int>());

	for (int l = 0; l < N - 2; l++) {
		for (int r = N - 1; r > l + 1; r--) {
			long long int cur = v[l] + v[r];
			int left = l + 1, right = r - 1 , mid;

			while (left <= right) {
				mid = (left + right) / 2;

				if (abs(cur + v[mid]) < abs(ans)) {
					ans_v.clear();
					ans = cur + v[mid];
					ans_v.push_back(l);
					ans_v.push_back(mid);
					ans_v.push_back(r);
				}

				if (cur + v[mid] < 0) {
					left = mid + 1;
				}
				else if (cur + v[mid] == 0) break;
				else {
					right = mid - 1;
				}
			}
		}
	}

	for (int iter : ans_v) cout << v[iter] << " ";

	return 0;
}
*/