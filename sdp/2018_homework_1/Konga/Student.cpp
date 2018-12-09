#include "Student.h"
#include <iostream>

University uni_from_string(const std::string& str) {
	if (str == "fmi") {
		return FMI;
	}
	if (str == "tu") {
		return TU;
	}
	if (str == "unss") {
		return UNSS;
	}
	return UNKNOW;
}

Student::Student(const std::string& name, const std::string& uni)
	: name(name)
	, uni(uni_from_string(uni))
{}

bool Student::tolerate(const Student& other) const {
	switch (uni) {
	case FMI:
		return other.uni != UNSS;
	case TU:
		return other.uni != FMI;
	case UNSS:
		return other.uni != TU;
	default:
		return false;
	}
}


void printStudent(const Student& student) {
	//спестяваме си условни конструкции
	const char* universities[] = { "FMI", "TU" , "UNSS", "UNKNOW" };
	std::cout << "-(" << student.name << ", " << universities[student.uni] << ")-";
}
