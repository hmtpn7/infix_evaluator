#include "inFixEvaluator.h"
#include <sstream>
#include <cctype>
using std::stack;
using std::string;
using std::istringstream;
using std::isdigit;

const std::string Infix_Evaluator::OPERATORS = "+-*/%";

/** Evaluates a postfix expression.
@param expression The expression to be evaluated
@return The value of the expression
@throws Syntax_Error if a syntax error is detected
*/
int Infix_Evaluator::eval(const std::string& expression) {
	// Be sure the stack is empty
	/*while (!operand_stack.empty())
		operand_stack.pop();
*/
	// Process each token
	istringstream tokens(expression);
	char next_char;
	while (tokens >> next_char) {
		if (isdigit(next_char)) {
			tokens.putback(next_char);
			int value;
			tokens >> value;
			operand_stack.push(value);
		}
		else if (is_operator(next_char)) {
			int result = eval_op(next_char);
			operand_stack.push(result);
		}
		else {
			throw Syntax_Error("Invalid character encountered");
		}
	}


		/*if (isdigit(next_char)) {
			operand_stack.push(next_char - '0');
		}
		else {
			int rhs = operand_stack.top();
			operand_stack.pop();
			int lhs = operand_stack.top();
			operand_stack.pop();
			int result;
			switch (next_char)
			{
			case '+': result = rhs + lhs; break;
			case '-': result = rhs - lhs; break;
			case '*': result = rhs * lhs; break;
			case '^': result = (int)pow((double)lhs, rhs); break;
			case '/': result = rhs / lhs; break;
			default:
				break;
			}
			operand_stack.push(result);
		}
	}
	return operand_stack.top();*/
}

/** Evaluates the current operator.
This function pops the two operands off the operand
stack and applies the operator.
@param op A character representing the operator
@throws Syntax_Error if top is attempted on an empty stack
*/
//template <typename T>
int Infix_Evaluator::eval_op(char op) {
	/*if (operand_stack.empty())
		throw Syntax_Error("Stack is empty");*/
	int rhs = operand_stack.top();
	operand_stack.pop();
	/*if (operand_stack.empty())
		throw Syntax_Error("Stack is empty");*/
	int lhs = operand_stack.top();
	operand_stack.pop();
	int result = 0;
	switch (op) {
		case '+': result = lhs + rhs;
			break;
		case '-': result = lhs - rhs;
			break;
		case '*': result = lhs * rhs;
			break;
		case '/': result = lhs / rhs;
			break;
		case '%': result = lhs % rhs;
			break;
		}
	return result;
}

//string Infix_Evaluator::infixToPostfix(string expr)
//{
//	string postfix;
//	stack<char> stack;
//	char previous;
//	int openParens = 0;
//
//	for (string::iterator it = expr.begin(); it != expr.end(); it++) {
//		char letter = *it;
//		// skip whitespaces
//		if (isspace(letter)) {
//			continue;
//		}
//		if (isdigit(letter)) {
//			postfix.append(1, letter);
//		}
//		else if (letter == '(') {
//			openParens++;
//			stack.push(letter);
//		}
//		else if (is_operator(letter)) {
//			if (stack.empty()) {
//				stack.push(letter);
//			}
//			else {
//				char op = stack.top();
//				while (eval_op(op) > eval_op(letter)) {
//					stack.pop();
//					postfix.append(1, op);
//				}
//				stack.push(letter);
//			}
//		}
//		else if (letter == ')') {
//			openParens--;
//			while (!stack.empty() && stack.top() != '(') {
//				postfix.append(1, stack.top());
//				stack.pop();
//			}
//			if (!stack.empty()) {
//				stack.pop();
//			}
//		}
//		else {
//			// Operator or operand error?
//			if (is_operator(previous) || previous == '(' || previous == ')') {
//				throw "operand error";
//			}
//			else {
//				throw "operator error";
//			}
//		}
//		previous = letter;
//	}
//
//	// Check paranthesis
//	if (openParens > 0) {
//		throw "imbalanced paranthesis error";
//	}
//
//	// Add stacked elements to output string
//	while (!stack.empty()) {
//		postfix.append(1, stack.top());
//		stack.pop();
//	}
//
//	return postfix;
//}
//
//int Infix_Evaluator::evalPostfix(string expr)
//{
//	return 0;
//}
