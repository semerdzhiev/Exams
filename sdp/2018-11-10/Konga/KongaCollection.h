#pragma once

#include "Vector.hpp"
#include "Queue.hpp"
#include "Student.h"

typedef Queue<Student> Konga;

class KongaCollection {
public:
	KongaCollection();

	bool append(const Student& student, int index);

	void removeFirst(int index);

	void removeLast(int index);

	bool empty() const;

	int size() const;

	bool merge(int firstIndex, int secondIndex);

	void remove(const std::string& name, int index);

	void remove_with_lambda(const std::string& name, int index);

	void print() const;

private:
	Vector<Konga> collection;

	void remove_if_empty(int index);

	void after_split(int index);
};
