#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

struct Node {
	int value;
	Node *left, *right;
};

bool is_leaf(Node* node) {
	return !node;
}

//обхождаме дървото с dfs О(N),
//използваме рекурсия, вместо стек
//пазим си изминатия път в path
//резултатъв в path  е пътя от корена до елементът със стойност value
bool find_path(Node* root, int value, std::vector<int>& path) {
	if (is_leaf(root)) {
		return false;
	}
	path.push_back(root->value);

	/*if (root->value == value) {
		return true;
	}

	if (find_path(root->left, value, path)) {
		return true;
	}

	if (find_path(root->right, value, path)) {
		return true;
	}*/

	if (root->value == value || find_path(root->left, value, path) || find_path(root->right, value, path)) {
		return true;
	}

	path.pop_back();
	return false;
}

//O(N)
std::vector<int> getPath(Node* root, int a, int b) {
	std::vector<int> path_a, path_b, res;

	find_path(root, a, path_a);
	find_path(root, b, path_b);

	//дали и двата елемента се срещат в дървото
	if (path_a.size() && path_b.size()) {
		size_t i = 0;
		for (; i < std::min(path_a.size(), path_b.size()) && path_a[i] == path_b[i]; ++i);
		--i;
		//елементър path_a[i] (или path_b[i]) е най-ниският им общ родител LCA
		//(последният общ елемент в пътищата от корена до елементите)

		//резултатът е обединиение на пътя от А до LCA и пътя от LCA до B

		for (size_t j = path_a.size() - 1; j > i; --j) {
			res.push_back(path_a[j]);
		}
		for (size_t j = i; j < path_b.size(); ++j) {
			res.push_back(path_b[j]);
		}
	}

	return res;
}
