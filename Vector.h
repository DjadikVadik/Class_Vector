#pragma once
#include <iostream>

template<typename T>
class Vector {
	T* arr;
	unsigned int size;
	unsigned int capacity;

public:

	// конструкторы и деструктор
	Vector();
	Vector(unsigned int capacity);
	~Vector();

	// конструктор копирования и переноса
	Vector(const Vector& other);
	Vector(Vector&& other);

	// перегрузка операторов
	bool operator==(const Vector& other);
	bool operator!=(const Vector& other);
	const T operator[](int index);
	Vector& operator=(const Vector& other);

	// методы
private:	
	// метод проверки наличия свободного места в векторе и выдиление новой памяти, если места нет
	void full_capacity();
public:
	int _size();
	int _capacity();
	void print();
	void push_beck(const T& value);
	void push_front(const T& value);
	void pop_beck();
	void pop_front();
	void insert(int index, const T& value);
	void erase(int index);
	void remove_by_value(const T& value);
	void trim_to_size();
	int index_of(T& value);
	int last_index_of(T& value);
	void reverse();
	void sort_asc();
	void sort_desc();
	void shuffle();
	bool equals(const Vector* other);
};

#pragma region КОНСТРУКТОРЫ И ДЕСТРУКТОР

template<typename T>
Vector<T>::Vector() {
	capacity = 10;
	size = 0;
	arr = new T[capacity];
}

template<typename T>
Vector<T>::Vector(unsigned int capacity) {
	if (capacity < 10) capacity = 10;
	this->capacity = capacity;
	size = 0;
	arr = new T[capacity];
}

template<typename T>
Vector<T>::~Vector() {
	delete[] arr;
	arr = nullptr;
}

#pragma endregion

#pragma region КОНСТРУКТОР КОПИРОВАНИЯ И ПЕРЕНОСА

template<typename T>
Vector<T>::Vector(const Vector& other)
{
	capacity = other.capacity;
	size = other.size;
	delete[] arr;
	arr = new T[capacity];

	for (int i = 0; i < size; ++i)
		arr[i] = other.arr[i];
}

template<typename T>
Vector<T>::Vector(Vector&& other)
{
	capacity = other.capacity;
	size = other.size;
	arr = other.arr;
	other.arr = nullptr;
}
#pragma endregion

#pragma region ПЕРЕГРУЗКА ОПЕРАТОРОВ

template<typename T>
bool Vector<T>::operator==(const Vector& other)
{
	if (size != other.size) return false;
	for (int i = 0; i < size; i++)
		if (arr[i] != other.arr[i]) return false;
	return true;
}

template<typename T>
bool Vector<T>::operator!=(const Vector& other)
{
	if (*this == other) return false;
	return true;
}

template<typename T>
const T Vector<T>::operator[](int index)
{
	if (index < 0 || index >= size) throw std::exception("incorrect index!!!");
	else return arr[index];
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
	if (this == &other) return *this;
	capacity = other.capacity;
	size = other.size;
	delete[] arr;
	arr = new T[capacity];

	for (int i = 0; i < size; ++i)
		arr[i] = other.arr[i];

	return *this;
}

#pragma endregion

#pragma region МЕТОДЫ

template<typename T>
void Vector<T>::full_capacity()
{
	if (capacity > size) return;
	else {
		capacity *= 2;
		T* arr1 = new T[capacity];

		for (int i = 0; i < size; i++)
			arr1[i] = arr[i];

		delete[] arr;
		arr = arr1;
		arr1 = nullptr;
	}
}

template<typename T>
int Vector<T>::_size()
{
	return size;
}

template<typename T>
int Vector<T>::_capacity()
{
	return capacity;
}

template<typename T>
void Vector<T>::print()
{
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << "   ";
	std::cout << "\n";
}

template<typename T>
void Vector<T>::push_beck(const T& value)
{
	full_capacity();
	arr[size] = value;
	size++;
}

template<typename T>
void Vector<T>::push_front(const T& value)
{
	insert(0, value);
}

template<typename T>
void Vector<T>::pop_beck()
{
	size--;
}

template<typename T>
void Vector<T>::pop_front()
{
	erase(0);
}

template<typename T>
void Vector<T>::insert(int index, const T& value)
{
	if (index < 0 || index >= size) throw std::exception("incorrect index!!!");
	full_capacity();

	for (int i = size; i >= 0; i--) {
		if (i > index) arr[i] = arr[i - 1];
		else if (i == index) arr[i] = value;
		else break;
	}
	size++;
}

template<typename T>
void Vector<T>::erase(int index)
{
	if (index < 0 || index >= size) throw std::exception("incorrect index!!!");
	for (int i = 0; i < size; i++) {
		if (i <= index) continue;
		else arr[i - 1] = arr[i];
	}
	size--;
}

template<typename T>
void Vector<T>::remove_by_value(const T& value)
{
	for (int i = 0; i < size; i++)
		if (arr[i] == value) erase(i);
}

template<typename T>
void Vector<T>::trim_to_size()
{
	capacity = size;
	T* arr1 = new T[capacity];

	for (int i = 0; i < size; i++)
		arr1[i] = arr[i];

	delete[] arr;
	arr = arr1;
	arr1 = nullptr;
}

template<typename T>
int Vector<T>::index_of(T& value)
{
	for (int i = 0; i < size; i++)
		if (arr[i] == value) return i;
	return -1;
}

template<typename T>
int Vector<T>::last_index_of(T& value)
{
	for (int i = size - 1; i >= 0; i--)
		if (arr[i] == value) return i;
	return -1;
}

template<typename T>
void Vector<T>::reverse()
{
	for (int i = 0; i < size / 2; i++)
		std::swap(arr[i], arr[size - 1 - i]);
}

template<typename T>
void Vector<T>::sort_asc()
{
	for (int i = 0; i < size - 1; i++)
		for (int j = 1; j < size - i; j++)
			if (arr[j - 1] > arr[j])
				std::swap(arr[j - 1], arr[j]);
}

template<typename T>
void Vector<T>::sort_desc()
{
	for (int i = 0; i < size - 1; i++)
		for (int j = 1; j < size - i; j++)
			if (arr[j - 1] < arr[j])
				std::swap(arr[j - 1], arr[j]);
}

template<typename T>
void Vector<T>::shuffle()
{
	srand(time(0));
	for (int i = 0; i < size; i++) {
		int a = rand() % size;
		int b = rand() % size;
		std::swap(arr[a], arr[b]);
	}
}

template<typename T>
bool Vector<T>::equals(const Vector* other)
{
	return *this == *other;
}

#pragma endregion
