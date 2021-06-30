//============================================================================
// Name        : Regex.cpp
// Author      : ChandrashekarC
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <regex>

using namespace std;

#define C_ALL(X) cbegin(X), cend(X)

class demo {
private:
	uint32_t m_var_1 = 0;
	bool m_var_2 = false;
	string m_var_3 = "";
	float m_var_4 = 0.0;
public:
	demo(uint32_t var_1, bool var_2, string var_3, float var_4) :
			m_var_1(var_1), m_var_2(var_2), m_var_3(var_3), m_var_4(var_4) {
	}
};

bool is_valid_email_id(string_view str) {
	static const regex r(
			R"(\w+@\w+\.(?:com|in))");
    return regex_match(str.data(), r);
}


template <class T>
void swap(T& a, T& b) {
    T tmp(a);   // we now have two copies of a
    a = b;      // we now have two copies of b (+ discarded a copy of a)
    b = tmp;    // we now have two copies of tmp (+ discarded a copy of b)
}

template <class T>
void swap_move(T& a, T& b) {
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}

template <typename Functor>
void f(Functor functor) {
    cout << __PRETTY_FUNCTION__ << endl;
}

int g() {
    static int i = 0;
    return i++;
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	demo obj { 123, true, "lol", 1.1 };

	try {
		static const auto r = std::regex(R"(\\)")
;	// Escape sequence error
} catch (const std::regex_error &e) {
	assert(strcmp(e.what(), "Unexpected end of regex when escaping.") == 0);
	assert(e.code() == std::regex_constants::error_escape);
}

	const string input = "ABC:1->   PQR:2;;;   XYZ:3<<<"s;
	const regex r(R"((\w+):(\w+);)");
	const regex rr(
			R"((\w+):(\d))");

	smatch m;
	if (regex_search(input, m, r)) {
		assert(m.size() == 3);
		assert(m[0].str() == "PQR:2;");              // Entire match
		assert(m[1].str() == "PQR");                 // Substring that matches 1st group
		assert(m[2].str() == "2");                   // Substring that matches 2nd group
		assert(m.prefix().str() == "ABC:1->   ");    // All before 1st character match
		assert(m.suffix().str() == ";;   XYZ:3<<<"); // All after last character match
		for (string &&str : m) {                     // Alternatively. You can also do
			cout << str << endl;
		}
	}

	assert(regex_match(input, m, r) == false);
	assert(
			regex_search(input, m, r) == true && m.ready() == true
					&& m[1] == "PQR");


	assert(is_valid_email_id("chandrashekarc@gmail.com") == true);
	assert(is_valid_email_id("@abc.com") == false);


	const vector<smatch> matches{
	        sregex_iterator{C_ALL(input), rr},
	        sregex_iterator{}
	    };

	assert(matches[0].str(0) == "ABC:1"
	        && matches[0].str(1) == "ABC"
	        && matches[0].str(2) == "1");
	    assert(matches[1].str(0) == "PQR:2"
	        && matches[1].str(1) == "PQR"
	        && matches[1].str(2) == "2");
	    assert(matches[2].str(0) == "XYZ:3"
	        && matches[2].str(1) == "XYZ"
	        && matches[2].str(2) == "3");

	    auto generator = [i = 0]() mutable { return ++i; };
	    auto lambda_func = [i = 0]() mutable { return i++; };
	    cout << generator() << endl; // 1
	    cout << generator() << endl; // 2
	    cout << generator() << endl; // 3

	    f(lambda_func); // Pass lambda
	    f(g);            // Pass function



	    auto employee = std::make_tuple(32, "Chandrashekar", "Bangalore");
	    cout << std::get<0>(employee) << endl; // 32
	    cout << std::get<1>(employee) << endl; // "Chandrashekar"
	    cout << std::get<2>(employee) << endl; // "Bangalore"
	return 0;
}
