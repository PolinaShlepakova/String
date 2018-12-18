/*** Developed by Polina Shlepakova ***/

#include "my_string.h"
#include <exception>
#include <cstring>

MyString::MyString(): _len(0), _allocator(new char[_len + 1]) {
	_allocator[0] = '\0';
}

MyString::MyString(const char* pc)
try : _len(strlen(pc)), _allocator(new char[_len + 1]) {
//	copyArr(_allocator, pc, 0, 0, _len + 1);
	strcpy(_allocator, pc);
}	catch(...) {
	delete[] _allocator;
}

MyString::MyString(const MyString& str): _len(str.length()), _allocator(new char[_len + 1]) {
	for (size_t i = 0; i < _len; ++i) {
		(*this)[i] = str[i];
	}
	_allocator[_len] = '\0';
}

MyString::~MyString() {
	delete[] _allocator;
	_allocator = nullptr;
}

MyString& MyString::operator=(const MyString& str) {
	if (this == &str) {
		return *this;
	}
	resize(str.length());
	for (size_t i = 0; i < _len; ++i) {
		(*this)[i] = str[i];
	}
	return *this;
}

char& MyString::operator[](const size_t index) {
	if (index >= _len) {
		throw std::out_of_range("Index out of bounds");
	}
	return _allocator[index];
}

const char& MyString::operator[](const size_t index) const {
	if (index >= _len) {
		throw std::out_of_range("Index out of bounds");
	}
	return _allocator[index];
}

size_t MyString::length() const {return _len;}

void MyString::clear() {
	resize(0);
}

void MyString::resize(size_t newSize) {
	char* newAllocator = new char[newSize + 1];
	copyArr(newAllocator, _allocator, 0, 0, std::min(_len, newSize));
	newAllocator[newSize] = '\0';
	delete[] _allocator;
	_allocator = newAllocator;
	_len = newSize;
}

void MyString::swap(MyString& other) {
	size_t tmpLen = length();
	_len = other.length();
	other._len = tmpLen;

	char* tmpAllocator = _allocator;
	_allocator = other._allocator;
	other._allocator = tmpAllocator;
}

MyString& MyString::append(const MyString& str) {
	return append(str._allocator);
}

MyString& MyString::append(const char* str) {
	size_t len1 = length();
	size_t len2 = strlen(str);
	resize(len1 + len2);
	for (size_t i = 0; i < len2; ++i) {
		(*this)[len1 + i] = str[i];
	}
	return *this;
}

MyString& MyString::append(const char c) {
	size_t len = length();
	resize(length() + 1);
	(*this)[len] = c;
	return *this;
}

int MyString::compare(const MyString& other) const {
	bool equal = true;
	size_t i = 0;
	// while previous chars are equal and the end of either MyString is not reached
	while (equal && (i < length()) && (i < other.length())) {
		equal = (*this)[i] == other[i];
		++i;
	}
	// if all previous chars are equal, then the loop terminated
	// because the end of either MyString was reached
	// so the difference in length will be the result
	if (equal) {
		return static_cast<int>(length()) - static_cast<int>(other.length());
	}
	// if unequal chars were found,
	// then they determine the relation of strings
	return (*this)[i - 1] - other[i - 1];
}

int MyString::substr(const MyString& sub) const {
	return substr(sub._allocator);
}

int MyString::substr(const char* sub) const {
	bool equal = true;
	for (size_t i = 0; i < length(); ++i) {
		for (size_t j = 0, subLen = strlen(sub); j < subLen; ++j) {
			if ((*this)[i + j] != sub[j]) {
				equal = false;
				break;
			}
		}
		if (equal) {
			return static_cast<int>(i);
		}
		equal = true;
	}
	return -1;
}

MyString& MyString::insert(size_t pos, const MyString& sub) {
	size_t newLen = length() + sub.length();
	char* newAllocator = new char[newLen + 1];
	copyArr(newAllocator, _allocator, 0, 0, pos);
	copyArr(newAllocator, sub._allocator, pos, 0, sub.length());
	copyArr(newAllocator, _allocator, pos + sub.length(), pos, length() - pos);
	newAllocator[newLen] = '\0';

	delete[] _allocator;
	_allocator = newAllocator;
	_len = newLen;
	return *this;
}

void MyString::copyArr(char* dest, const char* src, const size_t destPos, const size_t srcPos, const size_t len) {
	if (dest == nullptr || src == nullptr) {
		throw std::invalid_argument("Pointer not defined");
	}
	strncpy(dest + destPos, src + srcPos, len);
}

MyString operator+(const MyString& str1, const MyString& str2) {
	MyString res(str1);
	return res += str2;
}

MyString& operator+=(MyString& str1, const MyString& str2) {
	return str1.append(str2);
}

MyString& operator+=(MyString& str, const char c) {
	return str.append(c);
}

bool operator==(const MyString& str1, const MyString& str2) {
	return str1.compare(str2) == 0;
}

bool operator!=(const MyString& str1, const MyString& str2) {
	return !(str1 == str2);
}

bool operator<(const MyString& str1, const MyString& str2) {
	return str1.compare(str2) < 0;
}

bool operator<=(const MyString& str1, const MyString& str2) {
	return str1.compare(str2) <= 0;
}

bool operator>(const MyString& arg1, const MyString& arg2) {
	return arg2 < arg1;
}

bool operator>=(const MyString& str1, const MyString& str2) {
	return str2 <= str1;
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
	for (size_t i = 0; i < str.length(); ++i) {
		os << str[i];
	}
	return os;
}

std::istream& operator>>(std::istream& is, MyString& str) {
	std::istream::sync_with_stdio(false);
	char fst;
	is.get(fst);
	auto length = static_cast<size_t>(is.rdbuf()->in_avail());

	char* input = new char[length + 1];
	input[0] = fst;
	is.read(input + 1, length);
	input[length] = '\0';

	str = MyString(input);
	delete[] input;
	return is;
}
