/*
* List.h
* List template class
*/

#pragma once

template<typename ElementType>
class ListIterator;

template<typename ElementType>
class List {
	friend class ListIterator<ElementType>;
private:
	ElementType* elems;
	int cap, n;

	/*
	* Resizes the list when it gets full by doubling its capacity
	*/
	void resize();
public:
	List();

	/*
	* Copy constructor
	* Input: l - List&
	* Output:
	*/
	List(const List& l);

	/*
	* Assigment operator
	* Input: l - List&
	* Output:
	*/
	List& operator=(const List& l);

	/*
	* Gets the current size of the list
	* Input:
	* Output: returns the size
	*/
	int size() const noexcept;

	/*
	* Adds an element to the list
	* Input: el - ElementType&
	* Output:
	*/
	void add(const ElementType& el);

	/*
	* Gets the element from an index
	* Input: ind - int&
	* Output: returns the element
	*/
	ElementType& get(const int& ind) const noexcept;

	/*
	* Removes the element from the position given by an iterator
	* Input: it - ListIterator& (must be valid)
	* Output:
	*/
	void remove(const ListIterator<ElementType>& it);

	/*
	* Creates an iterator at the beginning of the list
	* Input:
	* Output: returns the iterator
	*/
	ListIterator<ElementType> begin() const noexcept;

	/*
	* Creates an invalid iterator at the end of the list
	* Input:
	* Output:
	*/
	ListIterator<ElementType> end() const noexcept;

	~List();
};

template<typename ElementType>
void List<ElementType>::resize() {
	const int newCap = cap * 2;
	ElementType* newElems = new ElementType[newCap];
	for (int i = 0; i < n; i++) {
		newElems[i] = elems[i];
	}
	delete[] elems;
	elems = newElems;
	cap = newCap;
}

template<typename ElementType>
List<ElementType>::List() {
	cap = 2;
	n = 0;
	elems = new ElementType[cap];
}

template<typename ElementType>
List<ElementType>::List(const List<ElementType>& l) {
	elems = new ElementType[l.cap];
	for (int i = 0; i < l.n; i++) {
		elems[i] = l.elems[i];
	}
	n = l.n;
	cap = l.cap;
}

template<typename ElementType>
List<ElementType>& List<ElementType>::operator=(const List<ElementType>& l) {
	delete[] elems;
	elems = new ElementType[l.cap];
	for (int i = 0; i < l.n; i++) {
		elems[i] = l.elems[i];
	}
	n = l.n;
	cap = l.cap;
	return *this;
}

template<typename ElementType>
int List<ElementType>::size() const noexcept {
	return n;
}

template<typename ElementType>
void List<ElementType>::add(const ElementType& el) {
	if (n == cap) {
		resize();
	}
	elems[n++] = el;
}

template<typename ElementType>
ElementType& List<ElementType>::get(const int& ind) const noexcept {
	return elems[ind];
}

template<typename ElementType>
void List<ElementType>::remove(const ListIterator<ElementType>& it) {
	for (int i = 0; i < n; i++) {
		if (*it == get(i)) {
			for (int j = i; j < n - 1; j++) {
				elems[j] = elems[j + 1];
			}
			n--;
		}
	}
}

template<typename ElementType>
ListIterator<ElementType> List<ElementType>::begin() const noexcept {
	return ListIterator<ElementType>(*this);
}

template<typename ElementType>
ListIterator<ElementType> List<ElementType>::end() const noexcept {
	return ListIterator<ElementType>(*this, n);
}

template<typename ElementType>
List<ElementType>::~List() {
	delete[] elems;
}


template<typename ElementType>
class ListIterator {
private:
	const List<ElementType>& list;
	int index;
public:
	ListIterator(const List<ElementType>& l) noexcept;

	ListIterator(const List<ElementType>& l, int i) noexcept;

	/*
	* Checks if the iterator is valid
	* Input:
	* Output: returns true if the iterator is valid, false otherwise
	*/
	bool valid() const noexcept;

	/*
	* Moves the iterator to the next element
	* Input:
	* Output:
	*/
	void next() noexcept;

	/*
	* Gets the element currently referred by the iterator
	* Input:
	* Output: returns the element
	*/
	ElementType& get() const noexcept;

	/* 
	* * operator overload: gets the element currently referred by the iterator
	* Input:
	* Output: returns the element
	*/
	ElementType& operator*() const noexcept;

	/*
	* ++ operator overload: moves the iterator to the next element
	* Input:
	* Output: returns a ListIterator&
	*/
	ListIterator& operator++() noexcept;

	/*
	* == operator overload: checks if two iterators are equal
	* Input: other - ListIterator&
	* Output: returns true if the operators have the same index, false otherwise
	*/
	bool operator==(const ListIterator& other) noexcept;

	/*
	* != operator overload: checks if two iterators are not equal
	* Input: other - ListIterator&
	* Output: returns true if the operators have different indexes, false otherwise
	*/
	bool operator!=(const ListIterator& other) noexcept;

	/*
	* Assignment operator for ListIterator
	* Input: other - ListIterator&
	* Output: returns a ListOperator& with the attributes of other
	*/
	ListIterator& operator=(const ListIterator& other);
};

template<typename ElementType>
ListIterator<ElementType>::ListIterator(const List<ElementType>& l) noexcept :list{ l }, index{ 0 } {}

template<typename ElementType>
ListIterator<ElementType>::ListIterator(const List<ElementType>& l, int i) noexcept :list{ l }, index{ i } {}

template<typename ElementType>
bool ListIterator<ElementType>::valid() const noexcept {
	return index < list.n;
}

template<typename ElementType>
void ListIterator<ElementType>::next() noexcept {
	index++;
}

template<typename ElementType>
ElementType& ListIterator<ElementType>::get() const noexcept {
	return list.elems[index];
}

template<typename ElementType>
ElementType& ListIterator<ElementType>::operator*() const noexcept {
	return list.elems[index];
}

template<typename ElementType>
ListIterator<ElementType>& ListIterator<ElementType>::operator++() noexcept {
	index++;
	return *this;
}

template<typename ElementType>
bool ListIterator<ElementType>::operator==(const ListIterator<ElementType>& other) noexcept {
	return index == other.index;
}

template<typename ElementType>
bool ListIterator<ElementType>::operator!=(const ListIterator<ElementType>& other) noexcept {
	return !(*this == other);
}

template<typename ElementType>
ListIterator<ElementType>& ListIterator<ElementType>::operator=(const ListIterator<ElementType>& other) {
	index = other.index;
	return *this;
}