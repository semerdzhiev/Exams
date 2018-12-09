#pragma once

#include <cassert>

template <class Data >
class Vector {
public:
	Vector()
		: data(nullptr)
		, size(0)
		, capacity(0)
	{}

	Vector(const Vector& other) {
		copyFrom(other);
	}

	Vector& operator=(const Vector& other) {
		if (this != &other) {
			delete[] data;
			copyFrom(other);
		}
		return *this;
	}

	~Vector() {
		delete[] data;
	}

	int getSize() const {
		return size;
	}

	int getCapacity() const {
		return capacity;
	}

	void popBack() {
		assert(size);
		--size;
	}

	void push_back(const Data& value) {
		if (size == capacity) {
			resize();
		}

		data[size++] = value;
	}

	Data& back() {
		assert(size);
		return data[size - 1];
	}

	const Data& back() const {
		assert(size);
		return data[size - 1];
	}

	Data& operator[](int index) {
		assert(index >= 0 && index < size);
		return data[index];
	}

	const Data& operator[](int index) const {
		assert(index >= 0 && index < size);
		return data[index];
	}

private:
	Data* data;
	int size;
	int capacity;

	void copyFrom(const Vector& other) {
		size = other.size;
		capacity = other.capacity;
		data = capacity ? new Data[capacity] : nullptr;

		for (int i = 0; i < size; ++i) {
			data[i] = other.data[i];
		}
	}

	void resize() {
		capacity = capacity ? 2 * capacity : 16;
		Data* temp = new Data[capacity];

		for (int i = 0; i < size; ++i) {
			temp[i] = data[i];
		}

		delete[] data;
		data = temp;
	}
};