#include "Evaluator.h"
#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <stdio.h>
using namespace std;

const std::string Evaluator::OPERATORS = "+-*/^%!=><&";


double Evaluator::evalPostfix(std::string expr)
{
	// stack is holding input numbers
	stack<double> nstack;

	for (string::iterator it = expr.begin(); it != expr.end(); it++) {
		char letter = *it;
		// simply push digits to stack
		if (isdigit(letter)) {
			// char -> int conversion
			nstack.push(letter - '0');
		}
		else {
			// doing actual operations
			double rhs = nstack.top();
			nstack.pop();
			double lhs = nstack.top();
			nstack.pop();
			double result;
			
			switch (letter) {
			case '+': result = lhs + rhs; break;
			case '-': result = lhs - rhs; break;
			case '*': result = lhs * rhs; break;
			case '^': result = (int)pow((double)lhs, rhs); break;
			case '/': result = lhs / rhs; break;
			}
			nstack.push(result);
		}
	}
	return nstack.top();
	
}


int Evaluator::precedence(char op)
{
	
	switch (op) {
	case '+': return 1;
	case '-': return 2;
	case '*': return 3;
	case '/': return 3;
	case '^': return 4;
	}
	return 0;
}


std::string Evaluator::infixToPostfix(std::string expr)
{
	stack<char> ostack; //stack holding operators
	stack<string> sostack;
	char previous;
	int openParens = 0;
	string postfix;
	vector<string> pfix;
	for (string::iterator it = expr.begin(); it != expr.end(); it++) {
		char ch = *it;
		
		if (ostack.empty()) {
			check_invalid_expressions(expr);
		}
		//Ignore whitespace
		if (isspace(ch)) {
			continue;
		}
		//read number
		if (isdigit(ch)) {
			postfix.append(1, ch);
			
		}
		else if (ch == '(' || ch == '[' || ch == '{') { 
			openParens++;
			ostack.push(ch);
			sostack.push(to_string(ch));
			

		}
		else if (is_Operator(ch)) { //read operator and put it to operator stack
			if (ostack.empty()) {
				ostack.push(ch);
				sostack.push(to_string(ch));
			}
			else {
				char op = ostack.top();
				while (precedence(op) > precedence(ch)) {
					ostack.pop();
					sostack.pop();
					postfix.append(1, op);
					pfix.push_back(to_string(ch));
				}
				ostack.push(ch);
				sostack.push(to_string(ch));
			}
		}
		else if (ch == ')') {
			openParens--;
			while (!ostack.empty() && ostack.top() != '(') {
				postfix.append(1, ostack.top());
				pfix.push_back(to_string(ch));
				ostack.pop();
				sostack.pop();
			}
			if (!ostack.empty()) {
				ostack.pop();
			}
		}
		else {
			// Operator or operand error?
			if (is_Operator(previous) || previous == '(' || previous == ')') {
				throw "operand error";
			}
			else {
				throw "operator error";
			}
		}
		previous = ch;
	}

	// Check paranthesis
	if (openParens > 0) {
		throw "imbalanced paranthesis error";
	}

	// Add stacked elements to output string
	while (!ostack.empty()) {
		postfix.append(1, ostack.top());
		pfix.push_back(sostack.top());
		
		ostack.pop();
		sostack.pop();
	}

	return postfix;
}

void Evaluator::check_invalid_expressions(std::string expr)
{
	for (int i = 0; i < expr.size(); i++) {
		if (i == 0 && expr[i] == ')' || expr[i] == ']' || expr[i] == '}') {
			cout << "Expression can't start with a closing parenthesis @ char: " << i << endl;
			system("pause");
			exit(0);
		}
		if (i==0 &&expr[i] == '>' || expr[i] == '<' || expr[i] == '&' || expr[i] == '=') {
			cout << "Expression can't start with a binary operator @ char: "<< i << endl;
			system("pause");
			exit(0);
		}		

	}
	int n = 1;
	while (n < expr.size()-1) {
	
		if (expr[n-1] == expr[n]  == expr[n + 1]) {
			cout << "Two binary operators in a row @ char: " << n << endl;
			system("pause");
			exit(0);
		}
		if ( isdigit(expr[n - 1]) && expr[n] == ' ' && isdigit(expr[n + 1])) {
			cout << "Two operands in a row @ char: " << n << endl;
			system("pause");
			exit(0);
		}

		//cout << "A unary operand can't be followed by a binary operator @ char: " << n << endl;
		n++;
	}
}
