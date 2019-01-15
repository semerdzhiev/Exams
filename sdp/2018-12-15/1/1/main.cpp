/*
 * �������� ������� �� ������ 1 �� ����� ���������, ������� 1, ��� 2018/2019.
 * 
 * ����� : ���� �������	
 */

#include <iostream>   // std::cout
#include <functional> // std::less, std::grater

// std::less � std::greater �� ���������� ��������  ������������� ������, ����� �� ���������
// �� ������������ �� ��� ��������. ���������� �� �� �� �� ������� ���� ���������� ��������� �� ������� �� �� ����,
// ���� � ���� � ��� ��� �� ����� ����������� � "min heap", � "max heap" 
// ����� �� �� ����������� ����:
template<typename T>
struct custom_less {
	bool operator() (const T& lhs, const T& rhs) const { return lhs < rhs; }
};

template<typename T>
struct custom_greater {
	bool operator() (const T& lhs, const T& rhs) const { return lhs > rhs; }
};

#include "binary_heap.hpp"

// � ���� ��������� �� ��������������
// ����������������, ����� �� ���� �� ��������
class dual_heap {

private:
	// � ���� ���� �� ������ ������ �������� ��-����� �� ��������
	// ������ ��� � "max" ����, �� ������ �� �� � ���-������� ������� -
	// ��������� ���-������ �� ���������(� ���� � ������ ��)
	binary_heap<int, std::less<int>>    max_heap; // ���
	// binary_heap<int, custom_less<int>>    max_heap;
	// � ���� ����, �� �������� ��-�������� ��������,
	// ������ ��� � "min" ����, �� ������� ���� �� � ���-������ ����
	// ��-�������� �������� -> ���-������ �� ���������(��� ��� ������ ��)
	binary_heap<int, std::greater<int>> min_heap; // ���
	// binary_heap<int, custom_greater<int>> min_heap;
private:
	// ������� ������� � ����� �� ������
	// ���� ��� ����� �� �� ��������� ������� �� ������ ���� ��� ������
	// �� ����������� ���� �����, ��� ���� �� ������ ���� insert ��������
	// �������� �� �����: O(1)
	void fix_heaps_balance() {
		
		if (max_heap.size() > min_heap.size() + 1) {
			int top = max_heap.top();
			max_heap.pop();
			min_heap.push(top);
			return;
		}
		
		if (min_heap.size() > max_heap.size() + 1) {
			int top = min_heap.top();
			min_heap.pop();
			max_heap.push(top);
			return;
		} 
	}
	
public:
	// �������� �� ��� �������,
	// �������� �� �����: O(logn), ������ n e ����� �� ���� ����������� ��������
	void insert(int new_el) {
		// ��� ������ ��������, ����� ����� � ����������� � ��-������� ��������
		if (empty()) {
			max_heap.push(new_el); // O(1)
			return;
		}
		// ��� ����� ������� � ��-����� �� ���-������� ������� ���� �������, 
		// �� ������ �� �� ������� ���� ��-��������
		if (new_el >= max_heap.top())
			min_heap.push(new_el); // O(logn)
		else // ��������� ��� � ��-����� -> ����� ���� ��-�������
			max_heap.push(new_el); // O(logn)
		// ����������� ���� � ����� ����������� �� ������� �� ������ ���� ��� ������,
		// ����������� ������� ���-����� 1 � ���������� �� �� ����������� ���������� � �������������
		// ������������� �� ����������
		fix_heaps_balance(); // O(logn)
	}
	// ������� ���������, �� ���� � �� �� � ���� �����
	// // �������� �� �����: O(1)
	double median() const {
		
		if (empty())
			throw std::logic_error("empty heap!");
		// ��� ����� ����� �� � ����� �������, �� ����� ���� � ����� =>
		// ��������� � ������ ����������� �� ����� �������� ���-������ �� �������(����� ����� �� ����������)
		if (size() % 2 == 0)
			return static_cast<double>(min_heap.top() + max_heap.top()) / 2; // O(1)
		
		// ��� ������� � �������:
		// � ����� �������� ��� ������ ��������, ������ ���� � ��������
		if (max_heap.size() > min_heap.size()) // O(1)
			return max_heap.top(); // O(1)
		else
			return min_heap.top(); // O(1)
	}
	// ���������� �� ���������
	// �������� �� �����: O(logn), ������ n � ���� �� ������ �������� � ����������
	void remove() {
		
		if (empty()) // O(1)
			throw std::logic_error("empty heap!");
		
		// � ����� ��������� ����� ������ ��������, �� ��� ������
		if (max_heap.size() > min_heap.size()) {
			max_heap.pop(); // O(logn)
			return;
		}
		
		if (min_heap.size() > max_heap.size()) {
			min_heap.pop(); // O(logn)
			return;
		}
		// ��� ����� �������� �� � ����� ����, �� ���������� �� ������, � ����� ����� ��������
		// ��� ������� ������ ����������� � ������
		max_heap.pop();
	}
	
	// ���������� �� ����� ��������� � ����� �� ���������� �� ����� �����
	// �������� �� �����: O(1)
	size_t size() const {
		
		return min_heap.size() + max_heap.size();
	}
	// ������ ��������� � ������ <=> ����� �� ����� �� ������
	// �������� �� �����: O(1)
	bool empty() const {
		 
		return max_heap.empty() && min_heap.empty(); 
	}
	// �����, ����� �� ������� ���������� ��������� �� ����������.
	// �� �� ������� �� ��������, �� �� ������ �� ������� ����� �� ������.
	void debug_state() const {
		
		std::cout << "\n--------------------";
		std::cout << "\nmax heap (smaller elements): ";
		for (int el: max_heap.get_raw())
			std::cout << el << ", ";
		
		std::cout << "\nmin heap (bigger elements) : ";
		for (int el: min_heap.get_raw())
			std::cout << el << ", ";
		std::cout << "\ncurrent median: (" << median() << ")";
		std::cout << "\n--------------------\n\n";
	}
};

// ������� �������, ��� �� �� ��������
// ����� �������, �� �� �������� ���������� �� ���������� ��
void test_dual_heap() {
	
	dual_heap dh;
	
	std::cout << ">>>>>>INSERT TESTING<<<<<<\n";
	for (int i : { 1, 2, 3, 4, 5 }) {
		dh.insert(i);
		std::cout << "\nafter inserting " << i << ':';
		dh.debug_state();
	}
	
	std::cout << ">>>>>>REMOVE TESTING<<<<<<\n";
	for (int i = 0; i < 3; i++) {
		dh.remove();
		std::cout << "\nafter removing median :";
		dh.debug_state();
	}
	
	std::cout << ">>>>>>INSERT, THEN REMOVE TESTING<<<<<<\n";
	dh.insert(42);
	dh.debug_state();
	// ����������, �� ���������� ���������, � �� ����� �������, ����� ��� ��������
	dh.remove();
	dh.debug_state();
	
	std::cout << ">>>>>>INSERT [1:10] in empty container TESTING<<<<<<\n";
	dual_heap dh_one_to_ten;
	for (int i = 1; i < 11; i++)
		dh_one_to_ten.insert(i);
	dh_one_to_ten.debug_state();
}

int main() {
	
	test_dual_heap();
	
	return 0;	
}
