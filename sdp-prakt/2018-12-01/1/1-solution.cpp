#include <algorithm>
#include <iostream>
#include <utility>

struct Node {
	int value;

	Node* left;
	Node* right;
};

bool is_leaf(Node* node) {
	return !node;
}

//броя елементи в дървото О(N)
int count(Node* node) {
	return is_leaf(node) ? 0 : 1 + count(node->left) + count(node->right);
}

//o(N)
int height(Node* node) {
	return is_leaf(node) ? 0 : 1 + std::max(height(node->left), height(node->right));
}

//[min, max] е интервалът на допустимите елементи в поддървото,
//този интервал се определя от елементите в пътя до поддървото.
//Използваме го, за да проверим дали е изпълнена инвариантата:
//Всеки елемент е по-малък или равен на всички елементи в дясното си поддърво и
//по-голям или равен на всички елементи в лявото си поддърво
//INT_max == std::numeric_limits<int>::min()
//O(N)
bool is_bst(Node* node, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max()) {
	
	/*if (!is_leaf(node)) {
		return false;
	}

	if (node->value < min) {
		return false;
	}

	if (node->value > max) {
		return false;
	}

	if (!is_bst(node->left, min, node->value)) {
		return false;
	}

	if (!is_bst(node->right, node->value, max)) {
		return false;
	}

	return true;*/
	
	return is_leaf(node) ||
		(node->value >= min &&
			node->value <= max &&
			is_bst(node->left, min, node->value) &&
			is_bst(node->right, node->value, max));
}

//Броят на елементите в пълно двоично дърво е 2^h - 1
//O(N)
bool is_full_smart(Node* node) {
	return (1u << height(node)) - 1 == count(node);
}

//O(N) + O(N) => O(N)
bool is_complete_smart(Node* node) {
	return is_bst(node) && is_full_smart(node);
}

//struct Pair {
//	bool first;
//	int second;
//};
//В first пазим дали дървото ни е пълно
//В second пазим височината, ако дървото ни е пълно
std::pair<bool, int> is_full(Node* node) {
	if (is_leaf(node)) {
		return std::make_pair(true, 0);
	}

	std::pair<bool, int> left = is_full(node->left);
	std::pair<bool, int> right = is_full(node->right);

	if (left.first && right.first && left.second == right.second) {
		return  std::make_pair(true, left.second + 1);
	}
	return std::make_pair(false, -1);
}

//O(N)
bool is_complete(Node* node) {
	return is_bst(node) && is_full(node).first;
}