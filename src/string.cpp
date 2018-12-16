/*** Developed by Polina Shlepakova ***/

#include "string.h"
#include <exception>

String::String(): _len(0), _allocator(new char[_len + 1]) {
	_allocator[0] = '\0';
}

String::String(const char* pc)
try : _len(countLen(pc)), _allocator(new char[_len + 1]) {
	copyArr(_allocator, pc, 0, 0, _len + 1);
}	catch(...) {
	delete[] pc;
}

String::String(const String& str): _len(str.length()), _allocator(new char[_len + 1]) {
	for (size_t i = 0; i < _len; ++i) {
		(*this)[i] = str[i];
	}
	_allocator[_len] = '\0';
}

String::~String() {
	delete[] _allocator;
	_allocator = nullptr;
}

String& String::operator=(const String& str) {
	if (this == &str) {
		return *this;
	}
	resize(str.length());
	for (size_t i = 0; i < _len; ++i) {
		(*this)[i] = str[i];
	}
	return *this;
}

char& String::operator[](const size_t index) {
	if (index >= _len) {
		throw std::out_of_range("Index out of bounds");
	}
	return _allocator[index];
}

const char& String::operator[](const size_t index) const {
	if (index >= _len) {
		throw std::out_of_range("Index out of bounds");
	}
	return _allocator[index];
}

size_t String::length() const {return _len;}

void String::clear() {
	resize(0);
}

void String::resize(size_t newSize) {
	char* newAllocator = new char[newSize + 1];
	copyArr(newAllocator, _allocator, 0, 0, std::min(_len, newSize));
	newAllocator[newSize] = '\0';
	delete[] _allocator;
	_allocator = newAllocator;
	_len = newSize;
}

void String::swap(String& other) {
	size_t tmpLen = length();
	_len = other.length();
	other._len = tmpLen;

	char* tmpAllocator = _allocator;
	_allocator = other._allocator;
	other._allocator = tmpAllocator;
}

String& String::append(const String& str) {
	size_t len = length();
	resize(length() + str.length());
	for (size_t i = 0; i < str.length(); ++i) {
		(*this)[len + i] = str[i];
	}
	return *this;
}

String& String::append(const char c) {
	size_t len = length();
	resize(length() + 1);
	(*this)[len] = c;
	return *this;
}

int String::compare(const String& other) const {
	bool equal = true;
	size_t i = 0;
	// while previous chars are equal and the end of either String is not reached
	while (equal && (i < length()) && (i < other.length())) {
		equal = (*this)[i] == other[i];
		++i;
	}
	// if all previous chars are equal, then the loop terminated
	// because the end of either String was reached
	// so the difference in length will be the result
	if (equal) {
		return static_cast<int>(length()) - static_cast<int>(other.length());
	}
	// if unequal chars were found,
	// then they determine the relation of strings
	return (*this)[i - 1] - other[i - 1];
}

int String::substr(const String& sub) const {
	bool equal = true;
	for (size_t i = 0; i < length(); ++i) {
		for (size_t j = 0; j < sub.length(); ++j) {
			if ((*this)[i + j] != sub[j]) {
				equal = false;
				break;
			}
		}
		if (equal) {
			return i;
		}
		equal = true;
	}
	return -1;
}

String& String::insert(size_t pos, const String& sub) {
	size_t newLen = length() + sub.length();
	char* newAllocator = new char[newLen + 1];
	copyArr(newAllocator, _allocator, 0, 0, pos);
	copyArr(newAllocator, sub._allocator, pos, 0, sub.length());
	copyArr(newAllocator, _allocator, pos + sub.length(), pos, length() - pos);
	delete[] _allocator;
	_allocator = newAllocator;
	_len = newLen;
	_allocator[_len] = '\0';
	return *this;
}

size_t String::countLen(const char* pc) {
	if (pc == nullptr) {
		throw std::invalid_argument("Pointer not defined");
	}
	size_t i = 0;
	while (pc[i] != '\0') {
		++i;
	}
	return i;
}

void String::copyArr(char* dest, const char* src, const size_t destPos, const size_t srcPos, const size_t len) {
	if (dest == nullptr || src == nullptr) {
		throw std::invalid_argument("Pointer not defined");
	}
	for (size_t i = 0; i < len; ++i) {
		dest[destPos + i] = src[srcPos + i];
	}
}

String operator+(const String& str1, const String& str2) {
	String res(str1);
	return res += str2;
}

String& operator+=(String& str1, const String& str2) {
	return str1.append(str2);
}

String& operator+=(String& str, const char c) {
	return str.append(c);
}

bool operator==(const String& str1, const String& str2) {
	return str1.compare(str2) == 0;
}

bool operator!=(const String& str1, const String& str2) {
	return !(str1 == str2);
}

bool operator<(const String& str1, const String& str2) {
	return str1.compare(str2) < 0;
}

bool operator<=(const String& str1, const String& str2) {
	return str1.compare(str2) <= 0;
}

bool operator>(const String& arg1, const String& arg2) {
	return arg2 < arg1;
}

bool operator>=(const String& str1, const String& str2) {
	return str2 <= str1;
}

std::ostream& operator<<(std::ostream& os, const String& str) {
	for (size_t i = 0; i < str.length(); ++i) {
		os << str[i];
	}
	return os;
}

std::istream& operator>>(std::istream& is, String& str) {
	std::cin.sync_with_stdio(false);
	char fst;
	std::cin.get(fst);
	size_t waiting = std::cin.rdbuf()->in_avail();
	char* input = new char[waiting + 1];
	input[0] = fst;
	std::cin.read(input + 1, waiting);
	input[waiting] = '\0';
	str = String(input);
	delete[] input;
	return is;
}
