/*
 * Примерно решение на задачата от първо контролно, група от 9:00, СДП 2018/2019.
 * 
 * Автор : Иван Филипов	
 */

#include <iostream> // std::cout, std::endl
#include "browser.h"

/* имплементации на методите на класа "window" */

// инициализация на статичната константа
const string window::default_url = "http://exam_dsa";

size_t window::destroy_tabs_chain(tab* first) {
	
	size_t destroyed = 0; // колко елемента общо сме "разрушили"
	tab* it; // указател, сочещ към елемента за освобождаване
	// минаваме през елементите докато не стигнем края
	while (first != nullptr) {
		// запомняме къде се намира текущия първи елемент
		it = first;
		// минаваме една стъпка напред
		first = first->next_ptr;
		// премахваме стария "текущ"
		delete it;
		// увеличаваме броя на "разрушените" <-- коментар стил "леймър"
		++destroyed;
	}
	// тук ще изпуснем "леймърсия" коментар
	return destroyed;
}

// имплементацията на този метод по условие
// е "с какъвто формат пожелаете"
void window::print_tabs_formatted() const {
	
	string all_tabs_formatted; // тук ще държим целия резултатен стринг
	string cur_tab_formatted;  // стринг - за текущо форматирания "прозорец"
	
	tab* it = head_ptr; // указател към началото на елементите
	// минаваме през всички елементи
	while (it != nullptr) {
		// забравяме за стария текущ стринг	
		cur_tab_formatted.clear(); 
		cur_tab_formatted = "{ \"" + it->url + "\", "; // форматираме ...
		cur_tab_formatted += (std::to_string(it->timestamp) + " }, ");  
		// добавяме текущия текст към цялостния
		all_tabs_formatted += cur_tab_formatted;
		it = it->next_ptr; // стъпка напред в списъка
	}
	
	// махаме послените ", " - добавени излищно в текста
	if (!all_tabs_formatted.empty()) {
		// от C++ 11 имаме pop_back, иначе можем да използваме erase
		all_tabs_formatted.pop_back();
		all_tabs_formatted.pop_back();
	}
	// отпечатваме резултата
	std::cout << all_tabs_formatted << std::endl;
}
	
void window::tab_request(const string& url) {
	
	if (empty()) { 
		// при празен прозорец просто съзадаваме елемента като "глава"
		head_ptr = new tab(url);
		cur_size = 1;
		if (url != window::default_url) { // ако не е дефолтния url имаме случай на прозорец,
			std::cout << "Append" << std::endl; //от които сме премахнали всички табове и сега добавяме нов
			print_tabs_formatted();
		}
		return;
	}
	
	if (head_ptr->url == url) {
		// ако главата съдържа този url, премахваме целия списък
		clear();
		std::cout << "Trim" << std::endl;
		print_tabs_formatted();
		return;
	}
	
	// тук можем да се сетим, че нямаме случай, в който имаме повече от едно срещане
	// на url в целия прозорец, защото командите не ни го позволяват.
	
	// случаят, в който имаме повече от един елемент и главата не е със съдржание url
	// проверяваме дали има срещане на url,
	// като запомняме и елемента преди срещането, за да можем
	// лесно да добавим елемента в края
	tab* slow_ptr = head_ptr; // този винаги ще е една стъпка назад
	tab* fast_ptr = head_ptr->next_ptr; // с този ще минем през елементите
	// минаваме през елементите
	while (fast_ptr != nullptr) {
		// ако имаме срещане
		if (fast_ptr->url == url) { 
			cur_size -= destroy_tabs_chain(fast_ptr->next_ptr); // освобождаваме паметта за всички следващи раздели
			fast_ptr->next_ptr = nullptr; // "прекъсваме" веригата, иначе next_ptr ще е "увиснал" указател
			std::cout << "Trim" << std::endl;
			print_tabs_formatted();
			return;	
		}
		// стъпка напред
		slow_ptr = fast_ptr;
		fast_ptr = fast_ptr->next_ptr;
	}
	// стигнали сме до края и не сме премахнали табове
	// добавяме в края
	slow_ptr->next_ptr = new tab(url); // от конструктора next_ptr = nullptr
	++cur_size;
	std::cout << "Append" << std::endl;
	print_tabs_formatted();
}

/* имплементации на методите на класа "browser" */

void browser::window_open() {
	// когато нямаме повече свободни места ...
	if (top >= browser::MAX_WINDOW_COUNT) {
		std::cout << "can't create new window, \
		              because the browser is FULL" << std::endl;
		return;
	}
	// към "раздела" сочен от top правим заявка за нов
	// дефолтен "раздел"
	windows[top++].tab_request(); // местим топ с 1, след извиличането
	if (top == 1) // обработка за текстовете
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
	// по условие трябва да освободим паметта за последния таб,
	// той се намира на индекс [top - 1], затова --top ни върши двойна работа
	windows[--top].clear();
	std::cout << "Current window closed!" << std::endl;
}

void browser::print_uptime() {
	
	if (empty()) {
		std::cout << 0 << std::endl;
		return;
	}
	// разлика между текущото време и времето на най - стария "раздел" в текущия
	std::cout << time(nullptr) - windows[top - 1].get_head_timestamp() << std::endl;
}

void browser::close() {
	
	size_t all_tabs_count = 0;
	for (size_t i = top; i > 0; i--)
		all_tabs_count += windows[i - 1].size();	// сумираме размерите на всички табове
	// отпечатваме статистиката
	std::cout << "Total closed \"tabs\" : " << all_tabs_count << std::endl
	          << "Total time of usage : " << time(nullptr) - creation_timestamp << std::endl;
	// !!! не е нужно да викаме clean на всеки "раздел", тък като деструктора
	// на браузер ще извика деструкторите на всички "window", които ще освободят ресурсите
}
	
const window& browser::get_current_window() const {
	// при празен браузер все пак трабва да върнем нещо,
	// тък като нямаме редеренция към отворен window, то хвърлянето на 
	// изключение е единствения ни ход
	if (empty())
		throw std::logic_error("empty browser!");
	// връщаме текущия
	return windows[top - 1];
}

window& browser::get_current_window() {
	
	if (empty())
		throw std::logic_error("empty browser!");
	
	return windows[top - 1];
}
