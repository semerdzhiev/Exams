/*
 * Примерно решение на задача 1 от второ контролно, вариант 1, СДП 2018/2019.
 * 
 * Автор : Иван Филипов	
 */

#include <iostream>   // std::cout
#include <functional> // std::less, std::grater

// std::less и std::greater са стандартни шаблонни  функционаелни обекти, който се използват
// за стравнението на два елемента. Използваме ги за да ги подадем като темплейтни аргументи на шаблона ни за хийп,
// така с един и същ код за хийпа реализираме и "min heap", и "max heap" 
// можем да ги реализираме така:
template<typename T>
struct custom_less {
	bool operator() (const T& lhs, const T& rhs) const { return lhs < rhs; }
};

template<typename T>
struct custom_greater {
	bool operator() (const T& lhs, const T& rhs) const { return lhs > rhs; }
};

#include "binary_heap.hpp"

// в този контейнер ще имплементираме
// функционалността, която се иска от задачата
class dual_heap {

private:
	// в този хийп ще държим всички елементи по-малки от медианта
	// понеже той е "max" хийп, то върхът му ще е най-големия елемент -
	// съответно най-близък до медианата(а може и самата тя)
	binary_heap<int, std::less<int>>    max_heap; // или
	// binary_heap<int, custom_less<int>>    max_heap;
	// в този хийп, ще съхраним по-големите елементи,
	// понеже той е "min" хийп, то неговия връх ще е най-малкия сред
	// по-големите елементи -> най-близък до медианата(или пък самата тя)
	binary_heap<int, std::greater<int>> min_heap; // или
	// binary_heap<int, custom_greater<int>> min_heap;
private:
	// помощна функция с която ще следим
	// дали има нужда да се прехвърли елемент от единия хийп към другия
	// ще прехвърляме само върха, ако това се налага след insert операция
	// сложност по време: O(1)
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
	// добавяне на нов елемент,
	// сложност по време: O(logn), където n e броят на вече съхранените елементи
	void insert(int new_el) {
		// ако нямаме елементи, новия отива в прирамидата с по-малките елементи
		if (empty()) {
			max_heap.push(new_el); // O(1)
			return;
		}
		// ако новия елемент е по-голям от най-големия елемент сред малките, 
		// то трябва да го добавим сред по-големите
		if (new_el >= max_heap.top())
			min_heap.push(new_el); // O(logn)
		else // съответно ако е по-малък -> отива сред по-малките
			max_heap.push(new_el); // O(logn)
		// проверяваме дали е нужно прехвърляне на елемент от единия хийп към другия,
		// поддържайки разлика най-много 1 в големините им си гарантираме коректност и бързодействие
		// бързодействие на операциите
		fix_heaps_balance(); // O(logn)
	}
	// връщаме медианата, тя може и да не е цяло число
	// // сложност по време: O(1)
	double median() const {
		
		if (empty())
			throw std::logic_error("empty heap!");
		// ако двата хийпа са с равни размери, то общия брой е четен =>
		// медианата е средно аритметично на двата елемента най-близки до средата(двата върха на пирамидите)
		if (size() % 2 == 0)
			return static_cast<double>(min_heap.top() + max_heap.top()) / 2; // O(1)
		
		// ако размера е нечетен:
		// в която пирамида има повече елементи, нейния връх е медината
		if (max_heap.size() > min_heap.size()) // O(1)
			return max_heap.top(); // O(1)
		else
			return min_heap.top(); // O(1)
	}
	// премахване на медианата
	// сложност по време: O(logn), където n е броя на всички елементи в контейнера
	void remove() {
		
		if (empty()) // O(1)
			throw std::logic_error("empty heap!");
		
		// в която прирамида имаме повече елементи, от нея махаме
		if (max_heap.size() > min_heap.size()) {
			max_heap.pop(); // O(logn)
			return;
		}
		
		if (min_heap.size() > max_heap.size()) {
			min_heap.pop(); // O(logn)
			return;
		}
		// ако двете пирамиди са с равен брой, то премахваме от същата, в която бихме добавили
		// нов елемент когато контейнерът е празен
		max_heap.pop();
	}
	
	// големината на нашия контейнер е сбора от големините на двата хийпа
	// сложност по време: O(1)
	size_t size() const {
		
		return min_heap.size() + max_heap.size();
	}
	// нашият контейнер е празен <=> двата му хийпа са празни
	// сложност по време: O(1)
	bool empty() const {
		 
		return max_heap.empty() && min_heap.empty(); 
	}
	// метод, който ни показва вътрешното състояние на контейнера.
	// не се изисква от задачата, но ни помага да вникнем какво се случва.
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

// тестова функция, тук ще си разпишем
// разни тестове, за да проверим държанието на контейнера ни
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
	// забележете, че премахваме медианата, а не същия елемент, който сме добавили
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
