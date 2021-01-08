#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int n;
int _len;
char buf[200][200]; //

struct tree {
	int code; // 해당 노드의 코드

	// 1~4 분면에 해당하는 트리 노드
	tree* rt; // right-top
	tree* lt; // left-top
	tree* lb; // left-bottom
	tree* rb; // right-bottom
};

tree * dnc(tree * node, int sx, int sy, int len) { // 시작 좌표, 길이
	node = new tree(); // 트리 노드 메모리 할당 // malloc
	if (len == 1) { // 길이가 1이면 더이상 못나눔
		node->code = (buf[sx][sy] == '#' ? 1 : 0);
		return node;
	}

	// 만약 sx, sy ~ len 범위에 문자가 같으면
	int flag = 1;
	char pre = buf[sx][sy];
	for (int i = sx; i < sx + len; i++) {
		for (int j = sy; j < sy + len; j++) {
			if (pre != buf[i][j]) {
				flag = 0;
				// 4방향으로 나눠야함 // 1 2 3 4 분면 순으로
			}
		}
	}
	if (!flag) { // 문자가 다르면 나눠야함
		// len / 2 로 나눌것임
		// 현재 node는 intersection node이므로 
		node->code = 2;
		// 1사분면 //
		node->rt = dnc(node->rt, sx, sy + len / 2, len / 2);
		node->lt = dnc(node->rt, sx, sy, len / 2);
		node->lb = dnc(node->rt, sx + len / 2, sy, len / 2);
		node->rb = dnc(node->rt, sx + len / 2, sy + len / 2, len / 2);
	}
	else { // 문자가 같으면
		node->code = (buf[sx][sy] == '#' ? 1 : 0);
	}
	return node;
}
void dfs(tree* node) {
	
	if (node->code == 2) {
		
		cout << "2 ( ";
		dfs(node->rt);
		dfs(node->lt);
		dfs(node->lb);
		dfs(node->rb);
		cout << ") ";
	}
	else {
		cout << node->code << " ";
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	_len = pow(2, n);
	for (int i = 0; i < _len; i++) {
		for (int j = 0; j < _len; j++) {
			cin >> buf[i][j];
		}
	}
	tree* root = NULL;
	root = dnc(root, 0, 0, _len);
	// 결과는 root 부터 dfs 탐색
	dfs(root);

}