#pragma once
#include "ArrayClass.h"
#include "Exception.h"

using namespace std;

/**
 * Joseph McGill
 * December 5th, 2014
 *
 * This class implements Strings in C++. This was done as an exercise
 * to reinforce understanding of Strings.
 **/
class String: virtual public ArrayClass<char> {
    friend ostream& operator<< (ostream& s, const String& str);

public:
	String();
	String(int n);
	String(const String& str);
	String(const char* s);
	virtual ~String();
	void operator= (const String& str);
	virtual int length() const;
	virtual int allocation() const;
	bool operator == (const String& str) const;
	bool operator < (const String& str) const;
	bool operator > (const String& str) const;
	void concatenate(const String& str);
	int index(char c, int start) const;
	int index(char c) const;
	int lastIndex(char c, int start) const;
	int lastIndex(char c) const;
	String substring(int left, int len) const;
	String operator + (const String& str);
	bool equalsIgnoreCase(const String& str);
	char charAt(int index);
};
