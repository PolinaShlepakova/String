#include <iostream>
#include "my_string.h"

int main() {
	// constructors
	MyString s0;
	std::cout << s0 << ", len: " << s0.length() << std::endl;
	MyString s1("my string");
	std::cout << s1 << ", len: " << s1.length() << std::endl;
	// copy constructor
	const MyString cs(s1);
	MyString s2(s1);
	std::cout << cs << std::endl;
	std::cout << s2 << std::endl;
	// assignment
	s0 = s1;
	std::cout << "assignment: " << s0 << std::endl;
	// indexing
	std::cout << s0 << "[3] : " << s0[3] << std::endl;
	std::cout << cs << "[4] : " << cs[4] << std::endl;
	try {
		s0[1000];
	} catch (std::out_of_range) {
		std::cout << "Got out of range exception as expected" << std::endl;
	}
	// clear
	s0.clear();
	std::cout << "cleared: " << s0 << ", len: " << s0.length() << std::endl;
	// resize
	std::cout << "before resize: " << s1 << std::endl;
	s1.resize(3);
	std::cout << " after resize: " << s1 << ", len: " << s1.length() << std::endl;
	std::cout << "before resize: " << s2 << std::endl;
	s2.resize(15);
	std::cout << " after resize: " << s2 << ", len: " << s2.length() << std::endl;

	// swap
	MyString one("one");
	MyString twentyOne("twenty one");
	std::cout << "before swap: " << one << " and " << twentyOne << std::endl;
	one.swap(twentyOne);
	std::cout << " after swap: " << one << " and " << twentyOne << std::endl;
	// append
	twentyOne.append(one);
	std::cout << twentyOne << std::endl;
	twentyOne.append('1');
	std::cout << twentyOne << std::endl;
	twentyOne.append("ttt");
	std::cout << twentyOne << std::endl;
	// compare
	MyString abc("abc");
	MyString abcc("abcc");
	MyString cba("cba");
	std::cout << abc << " compared to " << abcc << " : " << abc.compare(abcc) << std::endl;
	std::cout << cba << " compared to " << abc << " : " << cba.compare(abc) << std::endl;
	std::cout << abc << " compared to " << abc << " : " << abc.compare(abc) << std::endl;
	std::cout << std::boolalpha;
	std::cout << abc << " == " << abc << " : " << (abc == abc) << std::endl;
	std::cout << abc << " != " << abcc << " : " << (abc == abcc) << std::endl;
	// substr
	MyString sup("12345554371238123");
	MyString sub1("11");
	MyString sub2("5");
	MyString sub3("123");
	const char* sub4("55");
	std::cout << "Position of " << sub1 << " in " << sup << " : " << sup.substr(sub1) << std::endl;
	std::cout << "Position of " << sub2 << " in " << sup << " : " << sup.substr(sub2) << std::endl;
	std::cout << "Position of " << sub3 << " in " << sup << " : " << sup.substr(sub3) << std::endl;
	std::cout << "Position of " << sub4 << " in " << sup << " : " << sup.substr(sub4) << std::endl;
	// insert
	std::cout << "before insertion: " << sub1 << std::endl;
	sub1.insert(1, sub3);
	std::cout << " after insertion: " << sub1 << std::endl;
	std::cout << "before insertion: " << sub1 << std::endl;
	sub1.insert(0, sub3);
	std::cout << " after insertion: " << sub1 << std::endl;
	std::cout << "before insertion: " << sub2 << std::endl;
	sub2.insert(1, sub3);
	std::cout << " after insertion: " << sub2 << std::endl;
	// +
	std::cout << (abc + abcc) << std::endl;
	std::cout << abc << std::endl;
	// +=
	abc += abcc;
	std::cout << abc << std::endl;

	// input operator
	MyString input;
	std::cout << "Input a string: ";
	std::cin >> input;
	std::cout << "Your string: " << input << ", len: " << input.length() << std::endl;

	return 0;
}
