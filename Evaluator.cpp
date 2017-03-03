#include "Evaluator.h"
#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>

using std::stack;
using std::string;
using std::istringstream;
using std::isdigit;

const std::string Evaluator::OPERATORS = "+-*/^%!=><&(){}[]";


void Evaluator::evalOP(std::string& ope, istringstream& token, bool isbool)
{
	int result;
	int rhs, lhs;
	if (number_stack.empty()) {
		
		if (ope == "*" || ope == "/" || ope == "%") {
			rhs = 1;
		}
		else {
			rhs = 0;
		}
	}
	else {
		rhs = number_stack.top();
		number_stack.pop();
	}
	if (number_stack.empty()) {
		if (ope == "*" || ope == "/" || ope == "%") {
			lhs = 1;
		}
		else {
			lhs = 0;
		}
	}
	else {
		lhs = number_stack.top();
		number_stack.pop();
	}
	
	if (isbool == true) {
		bool i = false;
		i = comparing_operator(ope, rhs, lhs);
		if (i == true) {
			result = 1;
		}
		else {
			result = 0;
		}
	}
	if(isbool == false) {
		result = doOperator(ope, rhs, lhs);
	}
	
	
	operator_stack.pop();
	number_stack.push(result);	
}

string Evaluator::evaluateInfix(std::string & expr)
{
	while (!number_stack.empty() || !operator_stack.empty()) { //make sure both stacks are empty
		if (!number_stack.empty()) {
			number_stack.pop();
		}
		else if (!operator_stack.empty()) {
			operator_stack.pop();
		}
		
	}
	check_invalid_expressions(expr);
	istringstream tokens(expr);
	char letter;
	bool is_bool = false;
	string previous = "";
	string op = "";
	int index = 0;
	int result;
	bool negative = false;

	while (tokens >> letter) {				
		if (isdigit(letter)) {			//read digit number and push it to number stack
			tokens.putback(letter);     //append first letter to last letter in case on multiple digit number
			int n;
			tokens >> n;
			//n = letter - '0';  //convert char type to int type			
			number_stack.push(n);			
		}		
		else if (is_Operator(letter)) {
			op += letter;			// plus type char to convert char type to string type
			if (op == ">" || op == "<" || op == "<=" || op == ">=" || op == "&&" || op == "||" || op == "!=" || op == "==" || op == "!") {
				is_bool = true;
			}
			string ope = previous + letter;
			if (ope == "++" || ope == "--" || ope == "==" || ope == ">=" || ope == "<=" || ope == "&&" || ope == "||" || ope == "!=") {
					
				operator_stack.push(ope);
					
					previous = "";
					if (ope == "++" || ope == "--") {
						int r;
						tokens >> r;
						letter = r;
						r = doOperator(ope, r, 0);
						number_stack.push(r);
						operator_stack.pop();						
					}
					
			}
			else {
				
				operator_process(op, tokens, is_bool);
				
			}
			op = "";
								
		}
		else if (letter == ' ') {
			continue;
		}
		/*if (negative == true && letter == '-') {
			int n = letter + '0';
			operator_stack.top() = "+";

			n *= -1;
			number_stack.pop();
			number_stack.push(n);
			letter = ' ';
		}*/
		if (negative == true && letter == '-'){ //change operator sign of negative number
			operator_stack.push("+");
			letter = ' ';
			negative = false;
		}
		if (letter == '-') {
			char nxtnxt = ' ';
			//tokens.putback(nxtnxt);
			tokens >> nxtnxt;
			if (nxtnxt != '-'){
				negative = true;
				int a = nxtnxt - '0'; // minus '0' to convert char type to int type
				a = a * -1;
				number_stack.push(a);
				operator_stack.pop();	
				
				letter = ' ';
				
				operator_stack.push("+");
				
			}			
		}	
		previous = letter;
	}
	while (!operator_stack.empty() && !number_stack.empty()) {
		
			evalOP(operator_stack.top(), tokens, is_bool);
			if (!operator_stack.empty()) {
				operator_stack.pop();
			}
			
		
	}

	//output string and adjust the boolen value to output
	if (is_bool == true && number_stack.top() == 1) {
		return "True";
	}
	else if ( is_bool == false && number_stack.top() == 0){
		return "False";
	}
	else {
		return to_string(number_stack.top());
	}
	
	
}


void Evaluator::operator_process(string op, istringstream& token, bool isbool)
{
	if (operator_stack.empty() || (op == "(") || (op == "[") || (op == "{")) {
		if (op == ")" || op == "]" || op == "}") {
			cout << "Unmatched close parenthesis" << endl;
			system("pause");
			exit(0);		
		}
		operator_stack.push(op);
				
	}
	else {
		if (precedence(operator_stack.top()) <= precedence(op) && (op != ")") && (op != "}") && (op != "]")) {
			operator_stack.push(op);
		
			
		}
		else {
			// Pop all stacked operators with equal
			// or higher precedence than op.
			while (!operator_stack.empty()
				&& (operator_stack.top() != "(")
				&& (operator_stack.top() != "[")
				&& (operator_stack.top() != "{")
				&& (precedence(operator_stack.top()) >= precedence(op))) {
				evalOP(operator_stack.top(), token, isbool);
				
					operator_stack.pop();
				
				
			}
			// assert: Operator stack is empty or 
			//         top of stack is '(' or current
			//         operator precedence > top of stack operator
			//         precedence;
			if (op == ")" || op == "]" || op == "}") {
				if (!operator_stack.empty()
					|| ((operator_stack.top() == "(") || (operator_stack.top() == "[") || (operator_stack.top() == "{"))) {
					
					evalOP(operator_stack.top(), token, isbool);
					operator_stack.pop();
					
				}
				else {
					cout << "Unmatched close parentheses" << endl;
					system("pause");
					exit(0);
				}
			}
			else {
				
				operator_stack.push(op);			}
		}
	}
}

int Evaluator::precedence(std::string op)
{
	if (op == "+" || op == "-") {
		return 5;
	}
	else if (op == "||") {
		return 1;
	}
	else if (op == "&&") {
		return 2;
	}
	else if (op == "==" || op == "!=") {
		return 3;
	}
	else if (op == ">" || op == "<" || op == ">=" || op == "<=") {
		return 4;
	}
	else if (op == "*" || op == "/" || op == "%") {
		return 6;
	}
	else if (op == "^") {
		return 7;
	}
	else if (op == "!" || op == "++" || op == "--") {
		return 8;
	}
	
}

void Evaluator::check_invalid_expressions(std::string expr){
	for (int i = 0; i < expr.size(); i++) {
		if (i == 0 && expr[i] == ')' || expr[i] == ']' || expr[i] == '}') {
			cout << "Expression can't start with a closing parenthesis @ char: " << i << endl;
			system("pause");
			exit(0);
		}
		if ( number_stack.empty() && ((expr[0] == '>') || (expr[0] == '<') || (expr[0] == '&') || (expr[0] == '='))) {
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


int Evaluator::doOperator(string ope, int rhs, int lhs)
{
	int result;
	if (ope == "+"){
		return result = lhs + rhs;
	}
	else if (ope == "-") {
		return result = lhs - rhs;
	}
	else if (ope == "/") {
		return result = lhs / rhs;
	}
	else if (ope == "*") {
		return result = lhs * rhs;
	}
	else if (ope == "^") {
		return result = (int)pow((double)lhs, rhs);
	}
	else if (ope == "--") {
		return result = rhs - 1;
	}
	else if (ope == "++") {
		return result = rhs + 1;
	}
	else if (ope == "%") {
		return result = lhs % rhs;
	}
	
}

bool Evaluator::comparing_operator(std::string ope, int r, int l)
{
	bool result;
	if (ope == ">=") {
		return result = l >= r;
	}
	else if (ope == ">") {
		return result = l > r;
	}
	else if (ope == "<") {
		return result = l < r;
	}
	else if (ope == "<=") {
		return result = l <= r;
	}
	else if (ope == "==") {
		return result = l == r;
	}
	else if (ope == "!=") {
		return result = l != r;
	}
	else if (ope == "&&") {
		return result = l && r;
	}
	else if (ope == "||") {
		return result = l || r;
	}
	else if (ope == "!") {
		return result = !r;
	}
}



