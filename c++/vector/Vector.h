#pragma once
#include "Array.h"
#include "Exception.h"

/**
 * Joseph McGill
 * December 5th, 2014
 *
 * This class serves as a template for a Vector object.
 * It contains functions to create and manipulate Vectors,
 * as well as functions to insert and remove data into the
 * Vectors. This was done as an exercise to better understand Vectors.
 **/
template <class DataType> //Declares this class to be a template for DataType
class Vector:virtual public ArrayClass<DataType>
{

protected:
	int _currSize;
	int _incFactor;
public:
	Vector();
	Vector(int n);
	Vector(int n, DataType& val);
	Vector(const Vector<DataType>& v);
	Vector(const ArrayClass<DataType>& ac);
	virtual ~Vector();
	void operator = (const Vector<DataType>& v);
	void operator = (const ArrayClass<DataType>& ac);
	void QuickSort(Vector<DataType>& list, int left, int right);
	void swapEntry(DataType a, DataType b);
	void insert(const DataType& item, int index);
	void remove(int index);
	void add(const DataType& item);
	int capacity() const;
	int incFactor() const;
	void setIncFactor(int f);
	void setCapacity(int f);
	virtual int allocation() const;

};

/* Default constructor */
template <class DataType>
Vector<DataType>::Vector(): ArrayClass<DataType>() {
	_currSize = 0;
	_incFactor = _size*2;
}

/* Constructor with  parameter for increment factor */
template <class DataType>
Vector<DataType>::Vector(int n): ArrayClass<DataType>(n) {
	_currSize = 0;
	_incFactor = n;
}

/* Constructor with parameters for incrememnt factor and default value */
template <class DataType>
Vector<DataType>::Vector(int n, DataType& val): ArrayClass<DataType> (n, val){
	_currSize = 0;
	_incFactor = capacity * 2;
}

/* Copy Constructor for copying a Vector */
template <class DataType>
Vector<DataType>::Vector(const Vector<DataType>& v): ArrayClass<DataType>(v) {
	_currSize = v._currSize;
	_incFactor = v.incFactor();
}

/* Copy Constructor for coypying an ArrayClass<DataType> object */
template <class DataType>
Vector<DataType>::Vector(const ArrayClass<DataType>& ac):
                  ArrayClass<DataType> (ac) {
	_currSize = ac.size();
	_incFactor = (_currSize + 1) / 2;
}

/* Destructor */
template <class DataType>
Vector<DataType>::~Vector() {

}

/* Overloaded = operator */
template <class DataType>
void Vector<DataType>::operator= (const Vector<DataType>& v) {
	ArrayClass<DataType>::copy(v);
	_currSize = v._currSize;
	_incFactor = v.incFactor();
}

/* Overloaded = operator */
template <class DataType>
void Vector<DataType>::operator= (const ArrayClass<DataType>& ac) {
	ArrayClass<DataType>::copy(ac);
	_currSize = ac.size();
	_incFactor = (_currSize + 1) / 2;
}


/* Insert function */
template <class DataType>
void Vector<DataType>::insert(const DataType& item, int index) {
	if ((index < 0) || (index > _currSize)) {
		throw ArrayBoundsException(); //throws an exception if
		                              //the user tries to access an
		                              //index that is not in the array
	}

	/* Increases the capacity if adding the item would fill the array */
	if ((_currSize + 1) == _size) {
		setCapacity(_size + _incFactor);
	}

	_currSize++;
	/* Shifts the remaining elements */
	for (int i = _currSize - 1; i > index; i--) {
		(*this)[i] = (*this)[i - 1];
	}

	/* Inserts the item */
	(*this)[index] = item;
}

/* Remove funciton */
template <class DataType>
void Vector<DataType>::remove(int index) {

	if ((index < 0) || (index >= _currSize)) {
		throw ArrayBoundsException(); //throws an exception if
		                              //the user tries to access an
		                              //index that is not in the array
	}

	/* Changes capacity if removing the item would drop
	 * the Vector below half */
	if (_currSize <= (_size - _incFactor)) {
		setCapacity(_size - _incFactor);
	}

	/* Shifts the remaining items*/
	for (int i = index; i < (_currSize - 1); i++) {
		(*this)[i] = (*this)[i + 1];
	}
	_currSize--;
}

/* Add function */
template <class DataType>
void Vector<DataType>::add(const DataType& item) {
	insert(item, _currSize); //adds item to the end of the Vector by
	                         //calling insert function
}

/* Size funciton */
template <class DataType>
int Vector<DataType>::allocation() const {
	return _currSize;

}

/* capacity function */
template <class DataType>
int Vector<DataType>::capacity() const {
	return _size;
}

/* IncFactor function */
template <class DataType>
int Vector<DataType>::incFactor() const {
	return _incFactor;
}

/* setIncFactor function */
template <class DataType>
void Vector<DataType>::setIncFactor(int f) {
	/* sets incFactor to f if f is greater than 0 */
	if (f >= 0) {
		_incFactor = f;
	}
}

/* setCapacity function */
template <class DataType>
void Vector<DataType>::setCapacity(int f) {

	int len = _currSize;
	if (len > f) {
		len = f;
	}

	DataType* paNew = new DataType[f]; //creates a DataType pointer
	if (paNew == NULL) {
		throw  ArrayMemoryException(); //throws an exception if paNew is NULL
	}

	/* Copies the elements of paObject into paNew */
	for (int i = 0; i < len; i++) {
		paNew[i] = paObject[i];
	}
	/* Deletes the contents of paObject and frees up the memory */
	if (paObject != NULL) {
		delete[] paObject;
	}
	paObject = paNew; //sets the pointer paObject to paNew
	_size = f;

	if (_currSize > len) {
		_currSize = len;
	}
}
