#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

priority_queue<int, vector<int>, less<int>> maxheap;
priority_queue<int, vector<int>, greater<int>> minheap;

// 값이 들어올 때마다 중간값을 출력해주어야 하기 때문에
// maxheap의 top이 중간값이 되도록 설정해야 함

// 1. minheap 의 값들이 maxheap의 top 보다 크도록 설정해놓고
// 2. maxheap의 top 이 minheap의 top 보다 커지면 둘이 스왑하여
// 3. 1. 조건을 유지함
// 4. 들어온 수가 짝수일 경우 중간값의 작은값을 출력해야 하므로 maxheap의 size를 minheap의 size보다 항상 크도록 설정

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	int num;
	while (N--) {
		cin >> num;
		if (maxheap.size() > minheap.size()) minheap.push(num);
		else maxheap.push(num);

		if (!maxheap.empty() && !minheap.empty()) {
			if (maxheap.top() > minheap.top()) {
				int temp = maxheap.top(); maxheap.pop();
				maxheap.push(minheap.top());
				minheap.pop();
				minheap.push(temp);
			}
		}

		cout << maxheap.top() << '\n';
	}
	return 0;
}