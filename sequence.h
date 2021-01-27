#pragma once

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <cmath>

#include <stdexcept>

#include "dynamicArray.h"
#include "linkedList.h"



template <typename T> class Sequence{
protected:
	int size = 0;
public:

	virtual T GetFirst() const = 0;
	virtual T GetLast() const = 0;
	virtual T Get(int index) const = 0;
	virtual int GetSize() const { return this->size; }
	virtual Sequence<T>* GetSubsequence(int start, int end) const = 0; //end excluding
	virtual void Set(const T &item, int index) = 0;
	virtual void Append(const T &item) = 0;
	virtual void Prepend(const T &item) = 0;
	virtual void insertAt(const T &item, int index) = 0;
	virtual Sequence<T>* concat(const Sequence<T>& seq) const = 0;
	virtual bool operator==(const Sequence<T> &seq){
		if(this->size != seq.size) return false;

		for(int i = 0; i < this->size; i++){
			if(this->Get(i) != seq.Get(i)) return false;
		}
		return true;
	}
};


template <typename T> class ArraySequence : public Sequence<T>{
protected:
	DynamicArray<T> *array;

public:
	ArraySequence()
	{
		this->array = new DynamicArray<T>();
		this->size = 0;
	}

	ArraySequence(const ArraySequence<T> &seq){
		this->array = new DynamicArray<T>(*seq.array);
		this->size = seq.size;
	}

	ArraySequence(DynamicArray<T>* array){
		this->array = array;
		this->size = array->GetSize();
	}


	ArraySequence(T *items, int size){
		this->array = new DynamicArray<T>(items, size);
		this->size = size;
	}

	ArraySequence(int size)
	{
		this->array = new DynamicArray<T>(size);
		this->size = size;
	}

	virtual ~ArraySequence(){
		delete this->array;
		this->size = 0;
	}

	virtual T GetFirst() const override {
		return this->array->Get(0);
	}

	virtual T GetLast() const override {
		return this->array->Get(this->size - 1);
	}

	virtual T Get(int index) const override {
		return this->array->Get(index);
	}

	virtual void Set(const T &item, int index) override {
		if(index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		this->array->Set(item, index);
	}


	virtual ArraySequence<T>* GetSubsequence(int start, int end) const override {
		if(start < 0 || start >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
		if(end < 0 || end > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
		if(start > end) throw std::logic_error("end must be not less than start");


		DynamicArray <T>* subArray = new DynamicArray <T>(end - start);
		for (int i = 0; i < end - start; i++)
			subArray->Set(this->array->Get(i + start), i);

		ArraySequence<T>* subSequence = new ArraySequence<T>(subArray);
		return subSequence;
	}

	virtual void Append(const T &item) override {
		this->array->resize(this->size + 1);
		this->array->Set(item, this->size);
		this->size++;
	}

	virtual void Prepend(const T &item) override {
		this->array->resize(this->size + 1);
		T t1 = this->array->Get(0);
		T t2;
		for(int i = 0; i < this->size; i++){
			t2 = t1;
			t1 = this->array->Get(i + 1);
			this->array->Set(t2, i + 1);
		}
		this->array->Set(item, 0);

		this->size++;
	}

	virtual void insertAt(const T &item, int index) override {
		if(index < 0 || index > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		this->array->resize(this->size + 1);
		T t1 = this->array->Get(index);
		T t2;
		for(int i = index; i < this->size; i++){
			t2 = t1;
			t1 = this->array->Get(i + 1);
			this->array->Set(t2, i + 1);
		}
		this->array->Set(item, index);

		this->size++;
	}

	virtual ArraySequence<T>* concat(const Sequence<T>& seq) const override {
		DynamicArray<T> *array = new DynamicArray<T>(this->size + seq.GetSize());
		ArraySequence<T> *newSequence = new ArraySequence<T>(array);
		for(int i = 0; i < this->size; i++)
			newSequence->Set(this->Get(i), i);

		for(int i = 0; i < seq.GetSize(); i++)
			newSequence->Set(seq.Get(i), i + this->size);

		return newSequence;
	}

};


template <typename T> class ListSequence : public Sequence<T>{
protected:
	LinkedList<T> *list;
public:
	ListSequence(){
		this->list = new LinkedList<T>();
		this->size = 0;
	}

	ListSequence(const ListSequence<T> &seq){
		this->list = new LinkedList<T>(*seq.list);
		this->size = seq.size;
	}

	ListSequence(LinkedList<T> *list){
		this->list = list;
		this->size = list->GetSize();
	}

	ListSequence(T *items, int size){
		this->list = new LinkedList<T>(items, size);
		this->size = size;
	}

	ListSequence(int size){
		this->list = new LinkedList<T>(size);
		this->size = size;
	}

	virtual ~ListSequence(){
		delete this->list;
		this->size = 0;
	}


	virtual T GetFirst() const override {
		return this->list->GetFirst();
	}
	
	virtual T GetLast() const override {
		return this->list->GetLast();
	}

	virtual T Get(int index) const override {
		return this->list->Get(index);
	}


	virtual ListSequence<T>* GetSubsequence(int start, int end) const override {
		LinkedList<T> *subList = this->list->GetSublist(start, end);
		ListSequence<T> *seq = new ListSequence<T>(subList);
		return seq;
	}

	virtual void Set(const T &item, int index) override {
		this->list->Set(item, index);
	}

	virtual void Append(const T &item) override {
		this->list->Append(item);
		this->size++;
	}

	virtual void Prepend(const T &item) override {
		this->list->Prepend(item);
		this->size++;
	}

	virtual void insertAt(const T &item, int index) override {
		this->list->insertAt(item, index);
		this->size++;
	}

	virtual ListSequence<T>* concat(const Sequence<T>& seq) const override {
		ListSequence<T> *newSequence = new ListSequence<T>();

		for(int i = 0; i < this->size; i++)
			newSequence->Append(this->Get(i));

		for(int i = 0; i < seq.GetSize(); i++)
			newSequence->Append(seq.Get(i));

		return newSequence;
	}


};
