//#include <iostream>
//#include "inFixEvaluator.h"
//#include "Infix_To_Postfix.h"
//
//using namespace std;
//
//int main() {
//	Infix_To_Postfix eval; 
//	eval.convert("2+2^2*3");
//	//cout << result;
//
//	system("pause");
//	return 0;
//}


#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include "Evaluator.h"
using namespace std;



int main(int argc, char const *argv[])
{
	Evaluator eval;
	string line = "";
	
	
	
	while (cin) {
		getline(cin, line);
		// skip empty lines
		if (line.size() == 0) {
			continue;
		}
		try {
			
			cout << eval.evaluateInfix(line) <<endl;
		}
		catch (char const* e) {
			cerr << "error" << endl;
		}
	}
	return 0;
}
