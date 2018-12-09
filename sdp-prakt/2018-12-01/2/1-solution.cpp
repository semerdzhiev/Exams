#include <vector>
#include <algorithm>
#include <utility>

struct Node {
	int value;

	Node* left;
	Node* right;
};

bool is_leaf(Node* node) {
	return !node;
}

//броя елементи в дървото
int count(Node* node) {
	return is_leaf(node) ? 0 : 1 + count(node->left) + count(node->right);
}

//[min, max] е интервалът на допустимите елементи в поддървото,
//този интервал се определя от елементите в пътя до поддървото.
//Използваме го, за да проверим дали е изпълнена инвариантата:
//Всеки елемент е по-малък или равен на всички елементи в дясното си поддърво и
//по-голям или равен на всички елементи в лявото си поддърво
//INT_max == std::numeric_limits<int>::min()
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

//O(N^2)
Node* get_largest_bst_subtree(Node* root) {
	if (is_bst(root)) {
		return root;
	}
	Node* left = get_largest_bst_subtree(root->left);
	Node* right = get_largest_bst_subtree(root->right);

	return count(left) > count(right) ? left : right;
}

struct Tree{
	Node* root;
	int count;
	int min;
	int max;
	
	Tree(Node* root = nullptr, int count = 0, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max())
		: root(root)
		, count(count)
		, min(min)
		, max(max)
		{}
};
Tree get_largest_bst_subtree_help(Node* root) {
	if (is_leaf(root)) {
		return Tree();
	}
	
	Tree left = get_largest_bst_subtree_help(root->left);
	Tree right = get_largest_bst_subtree_help(root->right);

	/*
		за да можем да подобрим отговора,
		трябва най-голямото наредено дърво в лятото поддърво
		да има за корен лявото дете на текущия елемент.
		аналогично за дясното дете.

		остава да проверим, дали можем да "закачим" текущия елемент,
		към тези две дървета.
		За да ги обединим, трябва да са изпълнени условията,
		корена на лявото поддърво да е по-малък или равен на текущия елемент,
		корена на дясното поддърво да е по-голям или равен на текущия елемент.
	*/

	if (left.root == root->left &&
		right.root == root->right &&
		(is_leaf(root->left) || left.max <= root->value) &&
		(is_leaf(root->right) || right.min >= root->value)) {
		return Tree(
			root, 
			1 + left.count + right.count, 
			is_leaf(root->left) ? root->value : left.min,
			is_leaf(root->right) ? root->value : right.max
		);
	}
	return left.count < right.count ? right : left;
}

//O(N)
Node* get_largest_bst_subtree_smart(Node* root) {
	return get_largest_bst_subtree_help(root).root;
}
