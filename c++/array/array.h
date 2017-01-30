#ifndef __ARRAYCLASS__
#define __ARRAYCLASS__
#pragma once
#include <iostream>
#include "Exception.h"

/**
 * Joseph McGill
 * December 5th, 2014
 *
 * This class serves as a template class for Arrays. It contains
 * functions to manipulate arrays of any object. This was done as an exercise
 * to better understand arrays.
 **/
template <class DataType>
class ArrayClass {
protected:
	int _size;
	DataType* paObject;
	void copy(const ArrayClass<DataType>& a);

public:
	ArrayClass();
	ArrayClass(int n);
	ArrayClass(int n, const DataType& val);
	ArrayClass(const ArrayClass<DataType>& a);
	virtual DataType* getPAObject();
	virtual ~ArrayClass();
	virtual int allocation() const;
	virtual DataType& operator[] (int k);
	void operator= (const ArrayClass<DataType>& a);
};


template <class DataType>
ArrayClass<DataType>::ArrayClass() {
	_size = 0;
	paObject = new DataType[1];
	if (paObject == NULL) {
		throw ArrayMemoryException();
	}
	_size = 1;

}

/* Constructor*/
template <class DataType>
ArrayClass<DataType>::ArrayClass(int n) {
	_size = 0;
	paObject = new DataType[n];
	if (paObject == NULL) {
		throw ArrayMemoryException(); //throws if the array is not created
	}
	_size = n;
}

/* Constructor*/
template <class DataType>
ArrayClass<DataType>::ArrayClass(int n, const DataType& val) {
	_size = 0;

	paObject = new DataType[n];
	if (paObject == NULL) {
		throw ArrayMemoryException(); //throws if the array is not created
	}
	_size = n;

	/* Fills the empty array with a value*/
	for (int i = 0; i < n; i++) {
		paObject[i] = val;
	}
}

/* Copy Constructor*/
template <class DataType>
ArrayClass<DataType>::ArrayClass(const ArrayClass<DataType>& a) {
	copy(a); //Copies the parameter into the array
}

/* Destructor*/
template <class DataType>
ArrayClass<DataType>::~ArrayClass() {
	if (paObject != NULL) {
		delete[] paObject;
		paObject = NULL;
	}

	_size = 0;
}

/* Size function*/
template <class DataType>
int ArrayClass<DataType>::allocation() const {
	return _size; //Returns the size of the array
}

/* Copy function*/
template <class DataType>
void ArrayClass<DataType>::copy(const ArrayClass<DataType>& a) {
	_size = 0;
	paObject = new DataType[a._size];
	if (paObject == NULL) {
		throw ArrayMemoryException(); //throws if the array is not created
	}

	_size = a._size;
	for (int i = 0; i < _size; i++) {
		paObject[i] = a.paObject[i];
	}
}

/* Getter for the pointer to the first object in the array*/
template <class DataType>
DataType* ArrayClass<DataType>::getPAObject() {
	return paObject; //Returns a pointer to the first object in the array

}

/* Overloaded [] operator*/
template <class DataType>
DataType& ArrayClass<DataType>::operator[] (int k) {
	if ((k < 0) || (k >= allocation())) {
		throw ArrayBoundsException(); //Throws if the parameter is
		                              //not in the array
	}
	return paObject[k]; //Returns the object in the specified location
}

/* Overloaded = operator*/
template <class DataType>
void ArrayClass<DataType>::operator= (const ArrayClass<DataType>& a) {
	if (paObject != NULL) {
		delete[] paObject;
	}
	copy(a);
}
#endif
