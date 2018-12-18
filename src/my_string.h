/*** Developed by Polina Shlepakova ***/

#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#include <iostream>

class MyString {
public:
	MyString();
	explicit MyString(const char* pc);
	MyString(const MyString& str);
	~MyString();
	MyString& operator=(const MyString& str);

	char& operator[](const size_t index);
	const char& operator[](const size_t index) const;

	size_t length() const;
	void clear();
	void resize(size_t newSize);

	void swap(MyString& other);
	MyString& append(const MyString& str);
	MyString& append(const char* str);
	MyString& append(const char c);
	int compare(const MyString& other) const;
	int substr(const MyString& sub) const;
	int substr(const char* sub) const;
	MyString& insert(size_t pos, const MyString& sub);

private:
	size_t _len;
	char* _allocator;

	static void copyArr(char* dest, const char* src, const size_t destPos, const size_t srcPos,
						const size_t len);
};

MyString operator+(const MyString& arg1, const MyString& arg2);
MyString& operator+=(MyString& arg1, const MyString& arg2);
MyString& operator+=(MyString& str, const char c);

bool operator==(const MyString& arg1, const MyString& arg2);
bool operator!=(const MyString& arg1, const MyString& arg2);
bool operator< (const MyString& arg1, const MyString& arg2);
bool operator<=(const MyString& arg1, const MyString& arg2);
bool operator> (const MyString& arg1, const MyString& arg2);
bool operator>=(const MyString& arg1, const MyString& arg2);

std::ostream& operator<<(std::ostream& os, const MyString& str);
std::istream& operator>>(std::istream& is, MyString& str);

#endif // _STRING_H_
