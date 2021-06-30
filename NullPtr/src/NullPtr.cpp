//============================================================================
// Name        : NullPtr.cpp
// Author      : ChandrashekarC
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

void func(int) {
}
void func(int*) {
}
void func(bool) {
}

void func(double*) { /*...*/
}

struct nullptr_tt {
	void operator&() const = delete;  // Can't take address of nullptr
	template<class T>
	inline operator T*() const {
		return 0;
	}
	template<class C, class T>
	inline operator T C::*() const {
		return 0;
	}
};

struct C {
	void func();
};

struct String {
	String(uint32_t) { /* size of string */
	}
	String(const char*) { /* string */
	}
};

int main() {

	cout << "!!!Modern C++!!!" << endl; // prints !!!Modern C++!!!
	// Implicit conversion
	char *str = NULL; // Implicit conversion from void * to char *
	int i = NULL;     // OK, but `i` is not pointer type

	// Function calling ambiguity

//	func(NULL);     // Which one to call?

//	String s1( NULL );   // error: call to constructor of 'String' is ambiguous
	String s2(5);

//	In such cases, you need explicit cast (i.e., String s((char*)0)).
	String s((char*) 0);

	nullptr_tt nullptrr;

	int *ptr = nullptrr;                // OK
	void (C::*method_ptr)() = nullptrr; // OK
	nullptr_tt n1, n2;
	n1 = n2;

	//nullptr_tt *null = &n1;           // Address can't be taken.

	//Now, func( int* ) will be called as nullptr will implicitly be deduced to int*.
//	func(nullptr);


	// Typecasting on nullptr_t

	// int ptr_not_ok = reinterpret_cast<int>(nullptr); // Not OK
	long ptr_ok = reinterpret_cast<long long>(nullptr); // OK


//	func(nullptr);                            // compilation error, ambiguous call!

	// func(reinterpret_cast<int*>(nullptr)); // error: invalid cast from type 'std::nullptr_t' to type 'int*'
	func(static_cast<int*>(nullptr));         // OK


	// nullptr_t is comparable
	if (ptr == 0);          // OK
	if (ptr <= nullptrr){}    // OK

//	int a = 0;
//	if(a == nullptr);    // error: invalid operands to binary expression ('int' and 'nullptr_t')

	const int a = 0;
	if (a == nullptrr);
	return 0;
}
