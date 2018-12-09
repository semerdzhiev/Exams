#include "KongaCollection.h"
#include <iostream>

KongaCollection::KongaCollection() {
	//по условие имаме една празна опашка в началото
	collection.push_back(Konga());
}

bool KongaCollection::append(const Student& student, int index) {
	if (collection[index].empty() || student.tolerate(collection[index].back())) {
		collection[index].pushBack(student);
		return true;
	}
	return false;
}

void KongaCollection::removeFirst(int index) {
	collection[index].popFront();
	remove_if_empty(index);
}

void KongaCollection::removeLast(int index) {
	collection[index].popBack();
	remove_if_empty(index);
}

bool KongaCollection::merge(int firstIndex, int secondIndex) {
	if (collection[secondIndex].front().tolerate(collection[firstIndex].back())) {
		collection[firstIndex].append(collection[secondIndex]);
		remove_if_empty(secondIndex);
		return true;
	}
	return false;
}

bool studentNameIs(const Student& st, const std::string& name) {
	return st.name == name;
}

/*
	Различното подаване на аргументи при двата варианта на split_if
*/

void KongaCollection::remove(const std::string& name, int index) {
	collection.push_back(Konga());
	collection[index].split_if(collection.back(), name, studentNameIs);

	after_split(index);
}

void KongaCollection::remove_with_lambda(const std::string& name, int index) {
	collection.push_back(Konga());
	collection[index].split_if(collection.back(), [name](const Student& st) {
		return st.name == name;
	});
	after_split(index);
}

/*
	извикваме метода split_if на опашката
	и след това popFront() на новата опакта
*/

void KongaCollection::after_split(int index) {
	if (!collection.back().empty()) {
		collection.back().popFront();
	}

	remove_if_empty(collection.getSize() - 1);
	remove_if_empty(index);
}

void KongaCollection::print() const {
	for (int i = 0; i < collection.getSize(); ++i) {
		std::cout << "Line" << i << ": ";

		collection[i].for_each(printStudent);

		std::cout << std::endl;
	}
}

void KongaCollection::remove_if_empty(int index) {
	if (collection[index].empty()) {
		std::swap(collection[index], collection.back());
		collection.back().clear();
		collection.popBack();
	}
}

bool KongaCollection::empty() const {
	return collection.getSize() == 0;
}

int KongaCollection::size() const {
	return collection.getSize();
}