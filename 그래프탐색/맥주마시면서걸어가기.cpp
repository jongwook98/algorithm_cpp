#include<iostream>
#include<cstring>
#include<cmath>
#include<deque>
#include<vector>

using namespace std;

typedef struct {
	int y, x, idx;
}info;

vector<info> v;
deque<info> dq;

bool check[100];

// 처음에 unordered_map을 이용하여 key 값을 사용자 정의 구조체 pos : int y, x 를 이용하여
// 값을 가져오려고 했지만 사용자 정의 구조체를 사용하여 key 값을 사용하는 경우에는 

// 해쉬 함수를 만들어서 같은 해시값이 리턴되지 않도록
// 해시 충돌이 발생하지 않도록 해시 함수를 작성해야함

// == 연산자 오버로딩이 필요하다. 해시 충돌(해시값 동일) 발생시 원소 비교가 가능해야하기 때문에
// 두 인스턴스가 같은지 다른지 판단할 수 있는 기준이 필요하다.

// unordered_map 같은 경우에는 정렬이 필요 없으므로 < 연산자 오버로딩은 필요없다.

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int t;
	cin >> t;

	while (t--) {
		int n, s_y, s_x, g_y, g_x;
		cin >> n;
		
		memset(check, false, sizeof(check));

		dq.clear();
		v.clear();

		cin >> s_y >> s_x;
		dq.push_back({ s_y, s_x, -1 });
		
		int py, px;
		for (int i = 0; i < n; i++) {
			cin >> py >> px;
			v.push_back({py, px, i});
		}
		cin >> g_y >> g_x;

		bool flag = false;

		while (!dq.empty()) {
			int cy = dq.front().y; int cx = dq.front().x;
			dq.pop_front();
			
			for (auto iter : v) {
				if (!check[iter.idx] && abs(iter.y - cy) + abs(iter.x - cx) <= 1000) {
					check[iter.idx] = true;
					dq.push_back({ iter.y, iter.x, iter.idx });
				}
			}
			
			if (abs(g_y - cy) + abs(g_x - cx) <= 1000) {
				cout << "happy" << '\n';
				flag = true;
				break;
			}
		}
		if (!flag) cout << "sad" << '\n';
	}
	return 0;
}