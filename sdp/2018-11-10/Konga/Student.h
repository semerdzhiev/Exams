#pragma once
#include <string>

enum University {
	FMI,
	TU,
	UNSS,
	UNKNOW
};

struct Student {
	Student(const std::string& name, const std::string& uni);

	std::string name;
	University uni;

	bool tolerate(const Student& other) const;
};

void printStudent(const Student& student);
