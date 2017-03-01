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
	/*string test = "1+++1";
	for (int i = 1; i < test.size(); i++) {
		cout << test[0];
	}
		system("pause");*/
	while (cin) {
		getline(cin, line);
		// skip empty lines
		if (line.size() == 0) {
			continue;
		}
		try {
			cout << eval.evalInfix(line) << endl;
		
		}
		catch (char const* e) {
			cerr << e << endl;
		}
	}
	return 0;
}
