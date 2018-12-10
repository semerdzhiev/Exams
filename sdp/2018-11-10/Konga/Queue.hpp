#pragma once

template <class Data>
class Queue {
	struct Node {
		Node(const Data& value, Node* prev = nullptr, Node* next = nullptr)
			: value(value)
			, prev(prev)
			, next(next)
		{}

		Data value;
		Node* prev;
		Node* next;
	};
	Node* head;
	Node* tail;

public:

	Queue()
		: head(nullptr)
		, tail(nullptr)
	{}

	Queue(const Queue& other) {
		copyFrom(other);
	}

	Queue& operator=(const Queue& other) {
		if (this != &other) {
			clean();
			copyFrom(other);
		}
		return *this;
	}

	~Queue() {
		clean();
	}

	bool empty() const {
		return !head;
	}

	Data& front() {
		return head->value;
	}

	const Data& front() const {
		return head->value;
	}

	Data& back() {
		return tail->value;
	}

	const Data& back() const {
		return tail->value;
	}

	void clear() {
		clean();
		head = tail = nullptr;
	}

	void pushBack(const Data& value) {
		if (empty()) {
			tail = head = new Node(value);
		}
		else {
			tail->next = new Node(value, tail);
			tail = tail->next;
		}
	}

	void popBack() {
		Node* node = tail;
		if (tail && tail->prev) {
			tail = tail->prev;
			tail->next = nullptr;
		}
		else {
			tail = head = nullptr;
		}
		delete node;
	}

	void popFront() {
		Node* node = head;
		if (head && head->next) {
			head = head->next;
			head->prev = nullptr;
		}
		else {
			head = tail = nullptr;
		}
		delete node;
	}

	void append(Queue& other) {

		if (empty()) {
			head = other.head;
			tail = other.tail;
		}
		else if(!other.empty()) {
			tail->next = other.head;
			other.head->prev = tail;
			tail = other.tail;
		}
		other.head = other.tail = nullptr;
	}

	/*
		Методът split_if приема като аргумент функция, 
		която трябва да приема като единствен аргумент Data
		и да връща true за елемента, от който нататък искаме да разделим опашката.

		Аргументът на UnaryPredicate може да бъде от тип: Data, const Data, const Data&, Data&.

		Така променяйки аргумента на функцията split_if, 
		можем да разделяме опашката: по име на студент, по факултетен номер на студент.
		Ако имаме опашка от тип std::string,
		може да я разделим от първия елемент, 
		който има за префикс "konga".
		
		Това е добра практика, защото кода ни е лесно преизпозваем.
	*/

	template<class UnaryPredicate>
	void split_if(Queue& queue, UnaryPredicate p) {
		queue.clean();

		for (Node* i = head; i; i = i->next) {
			if (p(i->value)) {

				queue.head = i;
				queue.tail = tail;
				
				if (i == head) {
					head = tail = nullptr;
				}
				else {
					tail = i->prev;
					tail->next = i->prev = nullptr;
				}
				return;
			}
		}
		queue.head = queue.tail = nullptr;
	}

	/*
		Тук имаме опростен вариант на горната функция,
		с разликата, че се появява един допълнителен аргумент.
		
		С допълнителния аргумент можем да използваме
		нашия предикат без "специални техники".
		Погледнете извикването на функциите split_if в KongaCollection.cpp.
	*/

	template<class T, class BinaryPredicate>
	void split_if(Queue& queue, T value, BinaryPredicate p) {
		queue.clean();

		for (Node* i = head; i; i = i->next) {
			if (p(i->value, value)) {

				queue.head = i;
				queue.tail = tail;

				if (i == head) {
					head = tail = nullptr;
				}
				else {
					tail = i->prev;
					tail->next = i->prev = nullptr;
				}
				return;
			}
		}
		queue.head = queue.tail = nullptr;
	}
	
	/*
		Променяйки аргумента имаме фунция, 
		която отпечатва елементите на стандартния изход
		или
		ги сериализира във файл.

		Забележете, че тук функцията не е template,
		защото ще позвалим подаването на фунцкии от тип void(Data&),
		които могат да променят нашите елементи.
		(това, че методът е const не ни предпазва от това!!!)
	*/

	void for_each(void(*f)(const Data&)) const {
		for (Node* i = head; i; i = i->next) {
			f(i->value);
		}
	}

private:

	Queue(Node* head, Node* tail)
		: head(head)
		, tail(tail)
	{}

	void clean() {
		while (head) {
			Node* node = head;
			head = head->next;
			delete node;
		}
	}

	void copyFrom(const Queue& other) {

		head = tail = nullptr;

		for (Node* i = other.head; i; i = i->next) {
			pushBack(i->value);
		}
	}
};