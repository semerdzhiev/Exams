#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

struct Node {
	int value;
	std::vector<Node> children;
};

void get_nth_front_help(Node& node, int level, std::vector<Node*>& res) {
	if (level == 0) {
		res.push_back(&node);
	}
	else {
		for (size_t i = 0; i < node.children.size(); ++i) {
			get_nth_front_help(node.children[i], level - 1, res);
		}
	}
}

std::vector<Node*> get_nth_front(Node* root, int level) {
	std::vector<Node*> res;
	if (level >= 0 && root) {
		get_nth_front_help(*root, level, res);
	}
	return res;
}
