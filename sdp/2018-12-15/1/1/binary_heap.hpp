/*
 * �������� ������� �� ������ 1 �� ����� ���������, ������� 1, ��� 2018/2019.
 * 
 * ����� : ���� �������	
 */
 
#pragma once

#include <utility>    // std::swap()
#include <functional> // std::less()
#include <vector>     // std::vector

// ���������� ���������� �� ������� ��������
// ����� �� ����������� � min_heap � max_heap, ����
// �������� ������������ ���������� �������� - ������������ ����� �� ��������
template<typename T, typename Compare = std::less<T>> // ��������� std::less ���� �������� ���������� �������
class binary_heap {
	
private :
	/* ������ ���� ����� */
	std::vector<T> data;  // ����������� ����� ����� ������ 
	Compare         cmp;  // ������� �� �������� �� ����� ��� ��������
	
public :	
	/* ����� �� ������ �� �������� �� ����� */
	// ������ ��������� �����, ����, �� ����� �� ����������
	// ������������ �� ����������� ������
	binary_heap() = default;
	binary_heap(const Compare& cmp); // ������������ ����������� � ��������� ������� �� ���������
	binary_heap(const binary_heap&)            = default;
	binary_heap& operator=(const binary_heap&) = default;
	~binary_heap()                             = default;

private :
	/* ������� ������ */
	// ����� ������ ���� �� ������� �� ����� ������
	size_t get_left_child_ind(size_t index) const;
	// ����� ������ ���� �� ������� �� ����� ������
	size_t get_right_child_ind(size_t index) const;
	// ����� �������� �� ������� �� ����� ������, -1 ��� ��������� ���� �������
	int get_parent_ind(size_t index) const;
	// "�������" ������� �� ����� ������ ������ �� ����������
	void sift_down(size_t index);
	// "�������" ������� �� ����� ������ ������ �� ����������
	void sift_up(size_t index);

public:
	/* ��������� �� ����� */
	// ������ �� �������� �� �����, ��� �� �� �������� �(1)
	const T& top() const;
	// ������ ������� � ����������, �(logn)
	void push(const T& el);
	// �������� ����� �� ����������, �(logn)
	void pop();
	// ����� ���� ���������� � ������
	bool empty() const;
	// ����� ������� �� ����������
	size_t size() const;
	
	const std::vector<T>& get_raw() const { return data; }
};

template<typename T, typename Compare>
binary_heap<T, Compare>::binary_heap(const Compare& cmp) : cmp(cmp) {
	//...
}

template<typename T, typename Compare>
inline
size_t binary_heap<T, Compare>::get_left_child_ind(size_t index) const {
	
	return index * 2 + 1;
}

template<typename T, typename Compare>
inline
size_t binary_heap<T, Compare>::get_right_child_ind(size_t index) const {
	
	return index * 2 + 2;
}

template<typename T, typename Compare>
inline
int binary_heap<T, Compare>::get_parent_ind(size_t index) const {
	
	return (index) ? (index - 1) / 2 : -1 ;
}

template<typename T, typename Compare>
void  binary_heap<T, Compare>::sift_down(size_t index) {
	
	if (empty())
		return;

	T el_to_swap = data[index];
	size_t left_child_ind = get_left_child_ind(index);

	size_t size = data.size();
	// "���������" ������ �� ��������� �������� �������
	while (left_child_ind < size) {
		int right_child_ind = get_right_child_ind(index);
		// � ��� ���� �� �� ������
		if (left_child_ind < size - 1 && cmp(data[left_child_ind] , data[right_child_ind]))
			left_child_ind = right_child_ind;
		// �������� ���� �� ��� �� �� �������
		if (!cmp(el_to_swap, data[left_child_ind]))
			break;
		// ������� ���� ���� ������
		data[index] = data[left_child_ind];
		index = left_child_ind;
		left_child_ind = get_left_child_ind(left_child_ind);
	}

	data[index] = el_to_swap;
}

template<typename T, typename Compare>
void  binary_heap<T, Compare>::sift_up(size_t index) {
	
	T el_to_swap = data[index];
	int cur_parent = get_parent_ind(index);

	while (cur_parent >= 0 && cmp(data[cur_parent], el_to_swap)) {
		data[index] = data[cur_parent];
		index = cur_parent;
		cur_parent = get_parent_ind(index);
	}
	data[index] = el_to_swap;
}

template<typename T, typename Compare>
const T& binary_heap<T, Compare>::top() const {
	
	return data.front();
}

template<typename T, typename Compare>
void binary_heap<T, Compare>::push(const T& el) {
	
	data.push_back(el);
	sift_up(data.size() - 1);
}

template<typename T, typename Compare>
void binary_heap<T, Compare>::pop() {
	
	std::swap(data.front(), data.back());
	data.pop_back();
	sift_down(0);
}

template<typename T, typename Compare>
inline bool binary_heap<T, Compare>::empty() const {
	
	return data.empty();
}

template<typename T, typename Compare>
inline size_t binary_heap<T, Compare>::size() const {
	
	return data.size();
}
