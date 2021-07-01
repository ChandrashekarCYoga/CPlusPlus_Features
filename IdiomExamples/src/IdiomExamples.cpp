//============================================================================
// Name        : IdiomExamples.cpp
// Author      : ChandrashekarC
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

struct resource {
	resource(int x, int y) {
		cout << "resource acquired\n";
	}
	~resource() {
		cout << "resource destroyed\n";
	}
};

void func() {
	resource *ptr = new resource(1, 2);
	int x;
	std::cout << "Enter an integer: ";
	std::cin >> x;
	if (x == 0)
		throw 0; // the function returns early, and ptr won't be deleted!
	if (x < 0)
		return; // the function returns early, and ptr won't be deleted!
	// do stuff with ptr here
	delete ptr;
}

//In the above code, the early return or throw statement, causing the function
//to terminate without ptr being deleted.
//In addition, the memory allocated for variable ptr is now leaked (and leaked
//again every time this function is called and returns early).

/**
 * Resource Acquisition Is Initialization idiom is the most powerful & vastly used idiom
 * although the name is really terrible as the idiom is rather about resource release than acquisition.
 * RAII guarantee the release of resource at the end of a scope/destruction.
 * It thus ensures no resource leaks and provides basic exception safety guarantee.
 */

template<class T>
class smart_ptr {
	T *m_ptr;
public:
	template<typename ... Args>
	smart_ptr(Args &&... args) :
			m_ptr(new T(std::forward<Args>(args)...)) {
	}
	~smart_ptr() {
		delete m_ptr;
	}

	smart_ptr(const smart_ptr &rhs) = delete;
	smart_ptr& operator=(const smart_ptr &rhs) = delete;

	smart_ptr(smart_ptr &&rhs) :
			m_ptr(exchange(rhs.m_ptr, nullptr)) {
	}
	smart_ptr& operator=(smart_ptr &&rhs) {
		if (&rhs == this)
			return *this;
		delete m_ptr;
		m_ptr = exchange(rhs.m_ptr, nullptr);
		return *this;
	}

	T& operator*() const {
		return *m_ptr;
	}
	T* operator->() const {
		return m_ptr;
	}
};

/**
 * Note that no matter what happens after ptr declaration, ptr will be destroyed when the
 * function terminates (regardless of how it terminates).
 * As the ptr is a local object, the destructor will be called while the function stack
 * frame rewinds. Hence, we are assured that the resource will be properly cleaned up.
 *
 */
void func1() {
	auto ptr = smart_ptr<resource>(1, 2); // now ptr guarantee the release of resource
	// ...
}

/**
 * A function can not overloaded only by its return type.
 */
//int from_string(const char *str) { return std::stoi(str); }
//float from_string(const char *str) { return std::stof(str); } // error

/**
 * Solution
 */
class from_string {
	const string m_str;

public:
	from_string(const char *str) :
			m_str(str) {
	}
	template<typename type>
	operator type() {
		if constexpr (is_same_v<type, float>)
			return stof(m_str);
		else if (is_same_v<type, int>)
			return stoi(m_str);
	}
};

int n_int = from_string("123");
float n_float = from_string("123.111");
// Will only work with C++17 due to `is_same_v`

int main() {
	cout << "!!!Modern C++!!!" << endl; // prints !!!Modern C++!!!
	return 0;
}
