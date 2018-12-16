/*** Developed by Polina Shlepakova ***/

#ifndef _STRING_H_
#define _STRING_H_

#include <iostream>

class String {
public:
	String();
	explicit String(const char* pc);
	String(const String& str);
	~String();
	String& operator=(const String& str);

	char& operator[](const size_t index);
	const char& operator[](const size_t index) const;

	size_t length() const;
	void clear();
	void resize(size_t newSize);

	void swap(String& other);
	String& append(const String& str);
	String& append(const char c);
	int compare(const String& other) const;
	int substr(const String& sub) const;
	String& insert(size_t pos, const String& sub);

private:
	size_t _len;
	char* _allocator;

	static size_t countLen(const char* pc);
	static void copyArr(char* dest, const char* src, const size_t destPos, const size_t srcPos,
						const size_t len);
};

String operator+(const String& arg1, const String& arg2);
String& operator+=(String& arg1, const String& arg2);
String& operator+=(String& str, const char c);

bool operator==(const String& arg1, const String& arg2);
bool operator!=(const String& arg1, const String& arg2);
bool operator< (const String& arg1, const String& arg2);
bool operator<=(const String& arg1, const String& arg2);
bool operator> (const String& arg1, const String& arg2);
bool operator>=(const String& arg1, const String& arg2);

std::ostream& operator<<(std::ostream& os, const String& str);
std::istream& operator>>(std::istream& is, String& str);

#endif // _STRING_H_
