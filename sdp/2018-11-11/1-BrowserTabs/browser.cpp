/*
 * �������� ������� �� �������� �� ����� ���������, ����� �� 9:00, ��� 2018/2019.
 * 
 * ����� : ���� �������	
 */

#include <iostream> // std::cout, std::endl
#include "browser.h"

/* ������������� �� �������� �� ����� "window" */

// ������������� �� ���������� ���������
const string window::default_url = "http://exam_dsa";

size_t window::destroy_tabs_chain(tab* first) {
	
	size_t destroyed = 0; // ����� �������� ���� ��� "���������"
	tab* it; // ��������, ����� ��� �������� �� �������������
	// �������� ���� ���������� ������ �� ������� ����
	while (first != nullptr) {
		// ��������� ���� �� ������ ������� ����� �������
		it = first;
		// �������� ���� ������ ������
		first = first->next_ptr;
		// ���������� ������ "�����"
		delete it;
		// ����������� ���� �� "�����������" <-- �������� ���� "������"
		++destroyed;
	}
	// ��� �� �������� "���������" ��������
	return destroyed;
}

// ��������������� �� ���� ����� �� �������
// � "� ������� ������ ���������"
void window::print_tabs_formatted() const {
	
	string all_tabs_formatted; // ��� �� ������ ����� ���������� ������
	string cur_tab_formatted;  // ������ - �� ������ ������������ "��������"
	
	tab* it = head_ptr; // �������� ��� �������� �� ����������
	// �������� ���� ������ ��������
	while (it != nullptr) {
		// ��������� �� ������ ����� ������	
		cur_tab_formatted.clear(); 
		cur_tab_formatted = "{ \"" + it->url + "\", "; // ����������� ...
		cur_tab_formatted += (std::to_string(it->timestamp) + " }, ");  
		// �������� ������� ����� ��� ���������
		all_tabs_formatted += cur_tab_formatted;
		it = it->next_ptr; // ������ ������ � �������
	}
	
	// ������ ��������� ", " - �������� ������� � ������
	if (!all_tabs_formatted.empty()) {
		// �� C++ 11 ����� pop_back, ����� ����� �� ���������� erase
		all_tabs_formatted.pop_back();
		all_tabs_formatted.pop_back();
	}
	// ����������� ���������
	std::cout << all_tabs_formatted << std::endl;
}
	
void window::tab_request(const string& url) {
	
	if (empty()) { 
		// ��� ������ �������� ������ ���������� �������� ���� "�����"
		head_ptr = new tab(url);
		cur_size = 1;
		if (url != window::default_url) { // ��� �� � ��������� url ����� ������ �� ��������,
			std::cout << "Append" << std::endl; //�� ����� ��� ���������� ������ ������ � ���� �������� ���
			print_tabs_formatted();
		}
		return;
	}
	
	if (head_ptr->url == url) {
		// ��� ������� ������� ���� url, ���������� ����� ������
		clear();
		std::cout << "Trim" << std::endl;
		print_tabs_formatted();
		return;
	}
	
	// ��� ����� �� �� �����, �� ������ ������, � ����� ����� ������ �� ���� �������
	// �� url � ����� ��������, ������ ��������� �� �� �� ����������.
	
	// �������, � ����� ����� ������ �� ���� ������� � ������� �� � ��� ��������� url
	// ����������� ���� ��� ������� �� url,
	// ���� ��������� � �������� ����� ���������, �� �� �����
	// ����� �� ������� �������� � ����
	tab* slow_ptr = head_ptr; // ���� ������ �� � ���� ������ �����
	tab* fast_ptr = head_ptr->next_ptr; // � ���� �� ����� ���� ����������
	// �������� ���� ����������
	while (fast_ptr != nullptr) {
		// ��� ����� �������
		if (fast_ptr->url == url) { 
			cur_size -= destroy_tabs_chain(fast_ptr->next_ptr); // ������������� ������� �� ������ �������� �������
			fast_ptr->next_ptr = nullptr; // "����������" ��������, ����� next_ptr �� � "�������" ��������
			std::cout << "Trim" << std::endl;
			print_tabs_formatted();
			return;	
		}
		// ������ ������
		slow_ptr = fast_ptr;
		fast_ptr = fast_ptr->next_ptr;
	}
	// �������� ��� �� ���� � �� ��� ���������� ������
	// �������� � ����
	slow_ptr->next_ptr = new tab(url); // �� ������������ next_ptr = nullptr
	++cur_size;
	std::cout << "Append" << std::endl;
	print_tabs_formatted();
}

/* ������������� �� �������� �� ����� "browser" */

void browser::window_open() {
	// ������ ������ ������ �������� ����� ...
	if (top >= browser::MAX_WINDOW_COUNT) {
		std::cout << "can't create new window, \
		              because the browser is FULL" << std::endl;
		return;
	}
	// ��� "�������" ����� �� top ������ ������ �� ���
	// �������� "������"
	windows[top++].tab_request(); // ������ ��� � 1, ���� ������������
	if (top == 1) // ��������� �� ����������
		std::cout << "Browser started." << std::endl;
	else
		std::cout << "New window opened!" << std::endl;
}

void browser::window_close() {
	
	if (empty()) {
		std::cout << "can't close a window, because the browser is EMPTY" 
		          << std::endl;
		return;
	}
	// �� ������� ������ �� ��������� ������� �� ��������� ���,
	// ��� �� ������ �� ������ [top - 1], ������ --top �� ����� ������ ������
	windows[--top].clear();
	std::cout << "Current window closed!" << std::endl;
}

void browser::print_uptime() {
	
	if (empty()) {
		std::cout << 0 << std::endl;
		return;
	}
	// ������� ����� �������� ����� � ������� �� ��� - ������ "������" � �������
	std::cout << time(nullptr) - windows[top - 1].get_head_timestamp() << std::endl;
}

void browser::close() {
	
	size_t all_tabs_count = 0;
	for (size_t i = top; i > 0; i--)
		all_tabs_count += windows[i - 1].size();	// �������� ��������� �� ������ ������
	// ����������� ������������
	std::cout << "Total closed \"tabs\" : " << all_tabs_count << std::endl
	          << "Total time of usage : " << time(nullptr) - creation_timestamp << std::endl;
	// !!! �� � ����� �� ������ clean �� ����� "������", ��� ���� �����������
	// �� ������� �� ������ ������������� �� ������ "window", ����� �� ��������� ���������
}
	
const window& browser::get_current_window() const {
	// ��� ������ ������� ��� ��� ������ �� ������ ����,
	// ��� ���� ������ ���������� ��� ������� window, �� ���������� �� 
	// ���������� � ����������� �� ���
	if (empty())
		throw std::logic_error("empty browser!");
	// ������� �������
	return windows[top - 1];
}

window& browser::get_current_window() {
	
	if (empty())
		throw std::logic_error("empty browser!");
	
	return windows[top - 1];
}
