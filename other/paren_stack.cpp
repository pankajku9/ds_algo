/*
 * expStack.cpp
 *
 *  Created on: Nov 6, 2018
 *      Author: pankajku
 */

#include<iostream>
#include<stack>
#include<string>
#include<cassert>
#include<stdexcept>

using namespace std;

class paren {

	bool is_open_brac(char ch) {
		if (ch == '{' || ch == '[' || ch == '(')
			return true;

		return false;
	}

	bool is_close_brac(char ch) {
		if (ch == '}' || ch == ']' || ch == ')')
			return true;

		return false;
	}

	bool is_match_brac(char ch1, char ch2) {
		char exp_brackets[][2] = { { '{', '}' }, { '[', ']' }, { '(', ')' } };
		for (int i = 0; i < 3; i++) {
			if (ch1 == exp_brackets[i][0] && ch2 == exp_brackets[i][1])
				return true;
		}
		return false;
	}

	bool is_balanced(string input_str) {
		stack<char> exp_stk;
		int i = 0;
		for (; i < input_str.size(); i++) {
			char ch = input_str[i];
			std::cout << ch;
			if (is_open_brac(ch)) {
				cout << "open barc, push to stack";
				exp_stk.push(ch);
			} else if (is_close_brac(ch)) {
				char ch1 = exp_stk.top();
				cout << "close barc ";
				if (is_match_brac(ch1, ch)) {
					exp_stk.pop();
					cout << "pop from stack ";
				} else {
					cout << "no matching opening barc ";
					break;
				}
			}
			cout << std::endl;
		}

		if (i == input_str.size() && exp_stk.empty()) {
			return true;
		} else {
			false;
		}
	}

	void test1() {
		string str = "{[(){}]}";
		bool ret = is_balanced(str);
		std::cout << ret << std::endl;
		assert(true == ret);

		str = "{[(){}}";
		ret = is_balanced(str);
		std::cout << ret << std::endl;
		assert(true == ret);
	}
};
template<typename T>
class QWith2Stack{
	std::stack<T> frontS;
	std::stack<T> backS;

	void push(T a){
		backS.push(a);
	}

	void moveFromRear() {
		while (!rearS.empty()) {
			auto a = rearS.top();
			frontS.push(a);
			rearS.pop();
		}
	}

	T pop(){

		if(frontS.empty() && rearS.empty())
			throw std::out_of_range("Stack Underflow");

		if(frontS.empty() && !rearS.empty()){
			moveFromRear();
		}

		auto a = frontS.top();
		frontS.pop();
		return a;

	}

	void push(T a){
		rearS.push(a);
	}

	void front(){

	}

	void back(){

	}


};
int main() {

	return 0;
}
