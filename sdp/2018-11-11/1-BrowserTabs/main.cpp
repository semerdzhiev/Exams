/*
 * Примерно решение на задачата от първо контролно, група от 9:00, СДП 2018/2019.
 * 
 * Автор : Иван Филипов	
 */

#include <iostream>
#include "browser.h"

int main() {
	// създаваме браузера
	browser special_browser;
	// отваряме първия прозорец
	special_browser.window_open();
	// тук ще четем командите
	string cmd;
	// безкраен цикъл
	while (true) {
		std::cout << "> ";
		std::cin >> cmd; // прочитаме текущата
		// сравняваме си команда по команда...
		if (cmd == "WINDOW") {
			string type;
			std::cin >> type; // трябва да прочетем и типа OPEN или CLOSE
			
			if (type == "OPEN" || type == "-O") {
				special_browser.window_open();
				continue;
			} else if (type == "CLOSE" || type == "-C") {
				special_browser.window_close();
				continue;
			} 
		// ако стигнем дотук, то втория стинг е невалиден
		// ще "пропаднем" до долу, където ще кажем, невалиден вход
		}
		
		if (cmd == "UPTIME") {
			special_browser.print_uptime();
			continue;
		}
		
		if (cmd == "TAB") {
			string url;
			std::cin >> url;
			try {
				special_browser.get_current_window().tab_request(url); // ако е празен браузерът ше хвърлим изключение
			} catch (std::exception& e) { // можем да се справим с него, не е нужно програмата ни да се "счупи"
				std::cout << e.what() << std::endl;
			}
			continue;
		}
		
		if (cmd == "EXIT") {
			special_browser.close(); // ще отпечата статистиката
			break; // излизаме от безкрайния цикъл
		}
		
		std::cout << "unknown command!" << std::endl;
	}
	
	return 0;
}
