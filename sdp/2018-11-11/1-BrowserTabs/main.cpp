/*
 * �������� ������� �� �������� �� ����� ���������, ����� �� 9:00, ��� 2018/2019.
 * 
 * ����� : ���� �������	
 */

#include <iostream>
#include "browser.h"

int main() {
	// ��������� ��������
	browser special_browser;
	// �������� ������ ��������
	special_browser.window_open();
	// ��� �� ����� ���������
	string cmd;
	// �������� �����
	while (true) {
		std::cout << "> ";
		std::cin >> cmd; // ��������� ��������
		// ���������� �� ������� �� �������...
		if (cmd == "WINDOW") {
			string type;
			std::cin >> type; // ������ �� �������� � ���� OPEN ��� CLOSE
			
			if (type == "OPEN" || type == "-O") {
				special_browser.window_open();
				continue;
			} else if (type == "CLOSE" || type == "-C") {
				special_browser.window_close();
				continue;
			} 
		// ��� ������� �����, �� ������ ����� � ���������
		// �� "���������" �� ����, ������ �� �����, ��������� ����
		}
		
		if (cmd == "UPTIME") {
			special_browser.print_uptime();
			continue;
		}
		
		if (cmd == "TAB") {
			string url;
			std::cin >> url;
			try {
				special_browser.get_current_window().tab_request(url); // ��� � ������ ��������� �� ������� ����������
			} catch (std::exception& e) { // ����� �� �� ������� � ����, �� � ����� ���������� �� �� �� "�����"
				std::cout << e.what() << std::endl;
			}
			continue;
		}
		
		if (cmd == "EXIT") {
			special_browser.close(); // �� �������� ������������
			break; // �������� �� ���������� �����
		}
		
		std::cout << "unknown command!" << std::endl;
	}
	
	return 0;
}
