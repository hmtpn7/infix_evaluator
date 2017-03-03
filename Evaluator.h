#include <cmath>
#include <iostream>
#include <stack>
#include <string>



#ifndef EVALUATOR_H_
#define EVALUATOR_H_
using namespace std;
class Evaluator {
	// Public member functions
public:
	
	
	string evaluateInfix(std::string& expr);
	void evalOP(std::string& ope, istringstream& token, bool isbool);
	// Function prototypes
	

	void operator_process(string op, istringstream& token, bool isbool);
	
	int precedence(std::string op);
	

	
	int doOperator(std::string ope, int rhs, int lhs);
	bool comparing_operator(std::string ope, int r, int l);

	void check_invalid_expressions(std::string expr);
	// Private member functions
private:
	
	
	
	stack<string> operator_stack;
	stack<int> number_stack;
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
	
	static const std::string OPERATORS;

};
#endif


