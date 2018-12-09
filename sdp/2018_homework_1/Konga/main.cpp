#include <iostream>
#include "KongaCollection.h"

void menu() {
	KongaCollection collection;
	
	std::string command;
	std::string name;
	std::string uni;
	int index;
	int secondIndex;

	do {
		std::cin >> command;

		// not checked if index is out of range
		if (command == "append") {
			std::cin >> name >> uni >> index;

			if (!collection.append(Student(name, uni), index)) {
				std::cout << "Incompatible people" << std::endl;
			}
		}
		else if (command == "removeFirst") {
			std::cin >> index;

			collection.removeFirst(index);
		}
		else if (command == "removeLast") {
			std::cin >> index;

			collection.removeLast(index);
		}
		else if (command == "merge") {
			std::cin >> index >> secondIndex;

			if (!collection.merge(index, secondIndex)) {
				std::cout << "Incompatible people" << std::endl;
			}
		}
		else if (command == "print") {
			collection.print();
		}
		else if (command == "remove") {
			std::cin >> name >> index;
			collection.remove(name, index);
		}
		else if (command == "quit") {
			return;
		}
		else {
			std::cout << "Invalid command" << std::endl;
		}
	} while (!collection.empty());
}

int main() {

	menu();

	return 0;
}