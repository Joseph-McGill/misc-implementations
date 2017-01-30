#include "String.h"
#include <fstream>
#include "Array.h"

/**
 * Joseph McGill
 * December 5th, 2014
 *
 * This class implements Strings in C++. This was done as an exercise
 * to reinforce understanding of Strings.
 **/

/* Default constructor*/
String::String():ArrayClass<char> (1, '\0') {

}

/* Constructor taking a parameter for string size*/
String::String(int n):ArrayClass<char> (n+1, '\0') {

}

/* Copy constructor*/
String::String(const String& str):ArrayClass<char> (str) {

}

/* Constructor taking a char pointer parameter*/
#pragma warning(disable:4996)
String::String(const char* s):ArrayClass<char> (strlen(s) + 1) {
	strcpy(paObject, s);
}



/* Destructor*/
String::~String() {

}

/* Overloaded = operator*/
void String::operator = (const String& str) {
	if (allocation() == 0) {
		ArrayClass<char>::operator= (str);
		return;
	}

	int max = str.length();
	bool overflow = false;
	if ((_size - 1) < max) {
		ArrayClass<char>::operator= (str);
		return;
	}
	strncpy(paObject, str.paObject, max);
	paObject[max] = '\0';
}

/* Length function */
int String::length() const {
	return strlen(paObject);
}

/* Size function */
int String::allocation() const {
	return ArrayClass<char>::allocation() - 1;
}

/* Overloaded == operator */
bool String::operator == (const String& str) const {
	return (strcmp(paObject, str.paObject) == 0); //compares the characters
	                                              //in two strings
}

/* Overloaded < operator */
bool String::operator < (const String& str) const {
	return (strcmp(paObject, str.paObject) < 0); //compares the characters
	                                             //in two strings
}

/* Overloaded > operator */
bool String::operator > (const String& str) const {
	return (strcmp(paObject, str.paObject) > 0); //compares the characters
	                                             //in two strings
}

/* Concatenate function */
void String::concatenate(const String& str) {

	int len = length();
	int max = str.length();
	bool overflow = false;
	if (allocation() < max + len) {
		overflow = true;
		max = allocation() - len;
	}
	strncpy(paObject + len, str.paObject, max);
	paObject[max + len] = '\0';
	if (overflow) {
		throw StringSizeException(); //throws StringSizeException if the
		                             //string is too big
	}
}

/* index function */
int String::index(char c, int start) const {

	if (start >= length()) {
		return -1;
	}

	char* pc = strchr(paObject + start, c);
	if (pc == NULL) {
		return -1;
	}
	/* Returns the index of the character or -1 if the index does not exist */
	return (pc - paObject);
}

/* index function */
int String::index(char c) const {
	return index(c, 0); //returns the index of the char parameter
}

/* lastIndex function */
int String::lastIndex(char c, int start) const {
	int index = -1;
	if (start >= length()) {
		return index;
	}
	for (int i = start; i < allocation(); i++) {
		if (paObject[i] == c) {
			index = i;
		}
	}
	return index; //returns the last index of the parameter
}

/* lastIndex function */
int String::lastIndex(char c) const {
	int index = -1;
	for (int i = 0; i < allocation(); i++) {
		if (paObject[i] == c) {
			index = i;
		}
	}

	return index; //returnst he last index of the parameter
}

/* charAt function */
char String::charAt(int index) {
	return paObject[index]; //returns the character at the index
}

/* substring function */
String String::substring(int left, int len) const {
	if (left < 0) {
		throw ArrayBoundsException(); //throws an exception if the
		                              //left index is less than zero
	}
	String sub(len);
	if (left > length()) {
		return sub;
	}
	int max = len;
	if ((max + left) > length()) {
		max = length() - left;
	}

	strncpy(sub.paObject, &paObject[left], max);
	sub.paObject[max] = '\0';
	return sub; //returns a newly created string from the string
	            //that called this method
}

/* Overloaded + operator */
String String::operator + (const String& str) {
	String temp(length() + str.length());
	temp = (*this); //sets temp equal to the calling string
	temp.concatenate(str); //adds the parameter to the end of temp
	return temp; //returns temp
}

/* equalsIgnoreCase function */
bool String::equalsIgnoreCase(const String& str) {
	return (stricmp(paObject, str.paObject)); //compares to strings
	                                          //while ignoring case
}

/* Overloaded << operator */
ostream& operator<< (ostream& s, const String& str) {
	s << str.paObject; //outputs the string to a file
	return s;
}

