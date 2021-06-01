#include <string>

namespace TestPrograms {
    
    inline std::string fibonacciRec = R"(
    int fibonacciRec(int n) {
	    if(n == 0) { return 0; }
	    if(n == 1) { return 1; }
	    return fibonacciRec(n - 1) + fibonacciRec(n - 2);
    }
    
    int main() {
	    print(intToString(fibonacciRec(10))); #prints 55
	    return 0;
    })";

    inline std::string fibonacciIter = R"(
    int fibonacciIter(int n) {
	    #special cases
        if(n == 0) { return 0; }
	    if(n == 1) { return 1; }
	    
	    #declare variables
        int prevprev = 0;
	    int prev = 1;
	    int current;
	    
	    #main loop
        for(int i = 2; i <= n; ++i) {
		    current = prev + prevprev;
		    prevprev = prev;
		    prev = current;
	    }
        
	    return current;
    }
    
    int main() {
	    print(intToString(fibonacciIter(10))); #prints 55
	    return 0;
    })";

    inline std::string findMax = R"(
    int findMax(Matrix<int>[n_cols, n_rows] matrix) {
    	#n_cols and n_rows always an int
        
        int max = INT_MIN; #environmental constant
	    for(int i = 0; i < n_cols; ++i) {
		    for(int j = 0; j < n_rows; ++j) {
			    if(matrix[i, j] > max) { max = matrix[i, j]; }
		    }
	    }
	    return max;
	    
    }
    
    int main() {
	    Matrix<int>[2, 2] matrix;
    	matrix[0, 0] = -3;
	    matrix[0, 1] = 3;
	    matrix[1, 0] = 14;
	    matrix[1, 1] = -14;
	    print(intToString(findMax(matrix))); #prints 14
	    return 0;
    })";

    inline std::string concatStringMatrix = R"(
    string concatStringMatrix(Matrix<string>[n_cols, n_rows] matrix) {
        string concatString = "";
        for(int i = 0; i < n_cols; ++i) {
		    for(int j = 0; j < n_rows; ++j) {
			    concatString += matrix[i, j];
		    }
	    }
	    return concatString;
    }
    
    int main() {
	    Matrix<string>[2, 2] matrix;
	    matrix[0, 0] = "ala ";
	    matrix[0, 1] = "ma ";
	    matrix[1, 0] = "kota ";
	    matrix[1, 1] = "i psa";
	    print(concatStringMatrix(matrix)); #prints "ala ma kota i psa"
	    return 0;
    })";

    inline std::string average = R"(
    float average(Vector<float>[n] vector) {
    	float sum = 0.0;
    	for(int i = 0; i < n; ++i) {
    		sum += vector[i];
    	}
    	return sum / intToFloat(n);
    }

    int main() {
    	Vector<float>[2] vector;
    	vector[0] = 2.0;
    	vector[1] = 3.0;
    	print(floatToString(average(vector))); #prints 2.5
    	return 0;
    })";

    inline std::string printAgeDescription = R"(
    void printAgeDescription(int age) {
    	```
    	In this function a switch statement is used to print information about 
        your age.
    	```
    	switch {
    	case age < 0:
    		print("Your age is incorrect");
    	case age < 18:
    		print("You are a kid.");
    	case age < 60:
    		print("You are an adult.");
    	default:
    		print("You are a pensioner.");
    	}
    }
    
    int main() {
    	int age = stringToInt(input());
    	printAgeDescription(age);
    	return 0;
    })";

    inline std::string includeFile = R"(
    @include "../examples/YearInfo.ml"

    int main() {
    	printYearInfo(2021);
    	return 0;
    })";

    inline std::string copyByValue = R"(
    int addOne(int x) {
	    x++;
    	return x;
    }

    int main() {
    	int a = 3;

    	addOne(a);
    	print(intToString(a)); #prints 3
    
        a = addOne(a);
    	print(intToString(a)); #prints 4
    
    return 0;
    })";

    inline std::string copying = R"(
    int main() {
    	Vector<int>[2] vector;
    	print("0: "vector[0]", 1: "vector[1]"\n"); #prints "0: 0, 1: 0"
    	vector[0] = 3;
    	vector[1] = 5;
    
    	Vector<int>[2] vectorCopy = vector;
    	print("0: "vectorCopy[0]", 1: "vectorCopy[1]"\n"); #prints "0: 3, 1: 5"
        return 0;
    })";

    inline std::string scope = R"(
    int main() {
    	{
    		int a = 10;
    	}
    	print(intToString(a));	#error - no such variable "a"
    	return 0;
    })";

    inline std::string divideByZero = R"(
    int main() {
    	int a = 1 / 0;	#error - cannot divide by 0
    	return 0;
    })";

    inline std::string strongTyping = R"(
    int main() {
        int a = 0;
        float b = intToFloat(a); #ok
        float c = a; #error
        return 0;
    })";

}