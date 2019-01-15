/*
 * Примерно решение на задача 1 от второ контролно, вариант 1, СДП 2018/2019.
 * 
 * Автор : Иван Филипов	
 */
 
#pragma once

#include <utility>    // std::swap()
#include <functional> // std::less()
#include <vector>     // std::vector

// Темплейтна реализация на двоична пирамида
// можем да реализираме и min_heap и max_heap, като
// подаваме допълнителен темплейтен аргумент - функционален обект за сравение
template<typename T, typename Compare = std::less<T>> // използвай std::less като дефолтна сравняваща функция
class binary_heap {
	
private :
	/* скрити член данни */
	std::vector<T> data;  // реализираме хийпа върху вектор 
	Compare         cmp;  // функция за сравение на всеки два елемента
	
public :	
	/* грижа за живота на обектите от класа */
	// нямаме динамична памет, така, че можем да използваме
	// генерираните от компилатора версии
	binary_heap() = default;
	binary_heap(const Compare& cmp); // допълнителен конструктор с параметър функция за сравнение
	binary_heap(const binary_heap&)            = default;
	binary_heap& operator=(const binary_heap&) = default;
	~binary_heap()                             = default;

private :
	/* помощни методи */
	// връща лявото дете на родител на даден иднекс
	size_t get_left_child_ind(size_t index) const;
	// връща лявото дете на родител на даден иднекс
	size_t get_right_child_ind(size_t index) const;
	// връща родителя на елемент от даден индекс, -1 ако елементът няма родител
	int get_parent_ind(size_t index) const;
	// "пресява" елемент на даден индекс надолу по пирамидата
	void sift_down(size_t index);
	// "пресява" елемент на даден индекс нагоре по пирамидата
	void sift_up(size_t index);

public:
	/* интерфейс на класа */
	// достъп до елемента на върха, без да го поменяме О(1)
	const T& top() const;
	// добавя елемент в пирамидата, О(logn)
	void push(const T& el);
	// премахва върха на пирамидата, О(logn)
	void pop();
	// казва дали пирамидата е празна
	bool empty() const;
	// връща размера на пирамидата
	size_t size() const;
	
	const std::vector<T>& get_raw() const { return data; }
};

template<typename T, typename Compare>
binary_heap<T, Compare>::binary_heap(const Compare& cmp) : cmp(cmp) {
	//...
}

template<typename T, typename Compare>
inline
size_t binary_heap<T, Compare>::get_left_child_ind(size_t index) const {
	
	return index * 2 + 1;
}

template<typename T, typename Compare>
inline
size_t binary_heap<T, Compare>::get_right_child_ind(size_t index) const {
	
	return index * 2 + 2;
}

template<typename T, typename Compare>
inline
int binary_heap<T, Compare>::get_parent_ind(size_t index) const {
	
	return (index) ? (index - 1) / 2 : -1 ;
}

template<typename T, typename Compare>
void  binary_heap<T, Compare>::sift_down(size_t index) {
	
	if (empty())
		return;

	T el_to_swap = data[index];
	size_t left_child_ind = get_left_child_ind(index);

	size_t size = data.size();
	// "пресяваме" докато не достигнем желаната позиция
	while (left_child_ind < size) {
		int right_child_ind = get_right_child_ind(index);
		// с кое дете да се сменим
		if (left_child_ind < size - 1 && cmp(data[left_child_ind] , data[right_child_ind]))
			left_child_ind = right_child_ind;
		// проверка дали не сме си на мястото
		if (!cmp(el_to_swap, data[left_child_ind]))
			break;
		// слизаме едно ниво надолу
		data[index] = data[left_child_ind];
		index = left_child_ind;
		left_child_ind = get_left_child_ind(left_child_ind);
	}

	data[index] = el_to_swap;
}

template<typename T, typename Compare>
void  binary_heap<T, Compare>::sift_up(size_t index) {
	
	T el_to_swap = data[index];
	int cur_parent = get_parent_ind(index);

	while (cur_parent >= 0 && cmp(data[cur_parent], el_to_swap)) {
		data[index] = data[cur_parent];
		index = cur_parent;
		cur_parent = get_parent_ind(index);
	}
	data[index] = el_to_swap;
}

template<typename T, typename Compare>
const T& binary_heap<T, Compare>::top() const {
	
	return data.front();
}

template<typename T, typename Compare>
void binary_heap<T, Compare>::push(const T& el) {
	
	data.push_back(el);
	sift_up(data.size() - 1);
}

template<typename T, typename Compare>
void binary_heap<T, Compare>::pop() {
	
	std::swap(data.front(), data.back());
	data.pop_back();
	sift_down(0);
}

template<typename T, typename Compare>
inline bool binary_heap<T, Compare>::empty() const {
	
	return data.empty();
}

template<typename T, typename Compare>
inline size_t binary_heap<T, Compare>::size() const {
	
	return data.size();
}
