#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

struct Node {
	int value;
	std::vector<Node> children;
};

void get_between_help(Node& node, int a, int b, std::vector<Node*>& res) {
	if (a <= node.value && node.value <= b) {
		res.push_back(&node);
	}

	for (size_t i = 0; i < node.children.size(); ++i) {
		get_between_help(node.children[i], a, b, res);
	}
}

//O(N)
std::vector<Node*> get_between(Node* root, int a, int b) {
	std::vector<Node*> res;
	if (root) {
		get_between_help(*root, a, b, res);
	}
	return res;
}
