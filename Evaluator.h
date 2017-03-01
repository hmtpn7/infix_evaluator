#include <cmath>
#include <iostream>
#include <stack>
#include <string>


#ifndef EVALUATOR_H_
#define EVALUATOR_H_

class Evaluator {
	// Public member functions
public:
	
	double evalPostfix(std::string expr);
	
	// Function prototypes
	
	double evalInfix(std::string expr) { return evalPostfix(infixToPostfix(expr)); };
	
	//bool is_Operator(char cha);
	int precedence(char op);
	std::string infixToPostfix(std::string expr);

	void check_invalid_expressions(std::string expr);
	// Private member functions
private:
	



	/** Determines whether a character is an operator.
	@param ch The character to be tested
	@return true if the character is an operator
	*/

	
	// Data fields
	bool is_Operator(char ch) const {
		return OPERATORS.find(ch) != std::string::npos;
	}
	/*bool is_BOperator(string ch) const {
		return ch == "&&" || ch == ">=" || ch == "<=" || ch == "==" || ch == "!=" || ch == "<" || ch == ">" || ch == "||" || ch == "^" || ch == "%" || ch == "/" || ch == "+" || ch == "-" || ch == "*";
	}
	bool is_UOperator(string ch) const {
		return ch == "!" || ch == "&" || ch == "*" || ch == "++" || ch == "--";
	}*/
	static const std::string UOPERATORS;
	static const std::string BOPERATORS;
	static const std::string OPERATORS;
	std::stack<int> operand_stack;

};
#endif