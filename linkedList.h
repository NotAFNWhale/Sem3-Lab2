#pragma once

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <cmath>

#include <stdexcept>


#define INDEX_OUT_OF_RANGE_MESSAGE "index out of range"
#define NEGATIVE_SIZE_MESSAGE "size is negative"
#define ZERO_SIZE_MESSAGE "size is 0"



template <typename T> class LinkedList{
private:
	struct Record{
		T item;
		Record *next = nullptr;
	};

	Record *head = nullptr;
	int size = 0;

public:

	LinkedList() : size(0) {}

	LinkedList(T *items, int size) : LinkedList() {
		if(size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);

		Record **ptr = &(this->head);
		for(int i = 0; i < size; i++){
			*ptr = new Record;
			(*ptr)->item = items[i];
			ptr = &((*ptr)->next);
		}

		this->size = size;
	}


	LinkedList(int size) : LinkedList() {
		if(size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);

		Record **ptr = &(this->head);
		for(int i = 0; i < size; i++){
			*ptr = new Record;
			(*ptr)->item = T();
			ptr = &((*ptr)->next);
		}

		this->size = size;
	}


	LinkedList(const LinkedList<T> &list){
		Record *ptr = list.head;
		Record **newPtr = &(this->head);

		for(int i = 0; i < list.size; i++, ptr = ptr->next){
			*newPtr = new Record;
			(*newPtr)->item = ptr->item;
			newPtr = &((*newPtr)->next);

		}

		this->size = list.size;
	}

	virtual ~LinkedList(){
		Record *ptr = this->head;
		Record *next;
		while(ptr != nullptr){
			next = ptr->next;
			delete ptr;
			ptr = next;
		}
		this->size = 0;
	}


	T GetFirst() const {
		if(this->size == 0) throw std::length_error(ZERO_SIZE_MESSAGE);

		return this->head->item;
	}

	T GetLast() const {
		if(this->size == 0) throw std::length_error(ZERO_SIZE_MESSAGE);

		Record *ptr = this->head;
		while(ptr->next != nullptr) ptr = ptr->next;
		return ptr->item;
	}
	
	T Get(int index) const {
		if(index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


		Record *ptr;
		{
		int i = 0;
		for(i = 0, ptr = this->head; i < index; i++, ptr = ptr->next);
		}

		return ptr->item;
	}

	void Set(const T &item, int index){
		if(index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


		Record *ptr;
		{
		int i = 0;
		for(i = 0, ptr = this->head; i < index; i++, ptr = ptr->next);
		}

		ptr->item = item;
	}

	LinkedList<T>* GetSublist(int start, int end) const { //end excluding
		if(start < 0 || start >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
		if(end < 0 || end > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
		if(start > end) throw std::logic_error("end must be not less than start");

		LinkedList<T> *newList = new LinkedList<T>();


		Record *ptr = this->head;
		Record **newPtr = &newList->head;

		for(int i = 0; i < end; i++, ptr = ptr->next){
			if(i >= start){
				*newPtr = new Record;
				(*newPtr)->item = ptr->item;
				newPtr = &((*newPtr)->next);
			}

		}

		newList->size = end - start;

		return newList;
	}

	int GetSize() const { return this->size; }
	
	void Append(const T &item){
		Record **ptr = &(this->head);
		while(*ptr != nullptr) ptr = &((*ptr)->next);

		(*ptr) = new Record;
		(*ptr)->item = item;

		this->size++;
	}
	
	void Prepend(const T &item){
		Record *ptr = new Record{item, this->head};
		this->head = ptr;

		this->size++;		
	}

	void RemoveAt(int index){
		if(index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


		Record preHead;
		preHead.next = this->head;
		Record *ptr;

		{
		int i = 0;
		for(i = 0, ptr = &preHead; i < index; i++, ptr = ptr->next);
		}

		Record *tmp = ptr->next;
		ptr->next = ptr->next->next;
		delete tmp;

		this->head = preHead.next;

		this->size--;
	}

	void insertAt(const T &item, int index){
		if(index < 0 || index > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


		Record preHead;
		preHead.next = this->head; 
		Record *ptr;

		{
		int i = 0;
		for(i = 0, ptr = &preHead; i < index; i++, ptr = ptr->next);
		}

		ptr->next = new Record{item, ptr->next};
		this->head = preHead.next;

		this->size++;
	}

	LinkedList<T>* concat(const LinkedList<T> &list) const {
		Record *ptr1 = this->head;
		Record *ptr2 = list.head;

		LinkedList<T> *newList = new LinkedList<T>();
		Record **ptr = &(newList->head);
		while(ptr1 != nullptr){
			*ptr = new Record{
				ptr1->item,
				ptr1->next
			};

			ptr1 = ptr1->next;
			ptr = &((*ptr)->next);
		}
		while(ptr2 != nullptr){
			*ptr = new Record{
				ptr2->item,
				ptr2->next
			};

			ptr2 = ptr2->next;
			ptr = &((*ptr)->next);
		}

		newList->size = this->size + list.size;
		return newList;
	}


	bool operator==(const LinkedList<T> &list) const {
		if(this->size != list.size) return false;

		for(int i = 0; i < this->size; i++){
			if(this->Get(i) != list.Get(i)) return false;
		}

		return true;
	}

};
