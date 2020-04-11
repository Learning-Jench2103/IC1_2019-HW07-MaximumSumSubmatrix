#include<iostream>
#include<vector>
#include<iomanip>
#include<string>
#include<math.h>
#include<sstream>
#include<Windows.h>
#include<ctime>
using namespace std;

int inputNaturalNumber(string);
int inputInteger(string);
inline int maximum(int, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
inline string int2str(int&);
int chooseOption_0to9(int, int, string, string);
inline void inputMatrix(const int&, const int&, vector<int>&, int&);
inline void generateMatrix(const int&, const int&, vector<int>&, int&);
inline void printOriginalMatrix(const int, const int, vector<int>&, const int);
inline void findSubMatrix(vector<int>&, int, int, int);
inline void printSubMatrix(const int, const int, const int, const int, const int, vector<int>&, const int);

bool debug = true;
string input;

unsigned long long timesCount = 0;

int main() {
	do {
		system("cls");
		// let users to input the height of a matrix //
		int height = inputNaturalNumber("The Height of Matrix");

		// let users to input the width of a matrix //
		system("cls");
		cout << "Please input The Height of Matrix :" << height << endl << endl;
		int width = inputNaturalNumber("The Width of Matrix");
		if (debug) {	//execute only for debug
			cout << "---------------- Debug ----------------" << endl << endl;
			//////////////////////////////////////////////////////////////////
			cout << "Height = " << height << endl << "width = " << width << endl << "max = " << maximum(height, width) << endl << endl;
			//////////////////////////////////////////////////////////////////
			cout << "---------------- Debug ----------------" << endl << endl;
			system("pause");
		}

		vector<int> matrix(height * width);

		int length = 0;	//remember the length of the longest number in the matrix
		system("cls");

		// decide either input materials of the matrix or generate them randomly //
		switch (chooseOption_0to9(1, 2, "Choose how to generate the matrix?", "(1:input by yourself  2:generate by computer):")) {
		case 1:inputMatrix(height, width, matrix, length); break;
		case 2:generateMatrix(height, width, matrix, length); break;
		}

		system("cls");
		printOriginalMatrix(height, width, matrix, length);
		cout << endl;

		clock_t start, end;
		timesCount = 0;
		start = clock();
		// Compute and output the maximum sum and the submatrix //
		findSubMatrix(matrix, height, width, length);
		end = clock();

		if (debug) {
			cout << "Consuming time = " << static_cast<double>((__int64)end - (__int64)start) / CLOCKS_PER_SEC << endl << "Compute times = " << timesCount << endl << endl;
		}

		Sleep(1000);

	} while (chooseOption_0to9(1, 2, "Do you want to execute again?", "(1:Yes   2:No):") == 1);

	system("pause");
	return 0;
}

int inputNaturalNumber(string variableName) {
	int value = 0;
	while (1) {
		cout << "Please input " << variableName << " :";
		getline(cin, input);
		// check if all materials in input are numbers //
		if (input[0] == '-') {
			cout << variableName << " can't be minus number or characters!" << endl << endl;
			Sleep(1000);
			continue;
		}
		bool inputError = false;
		for (int i = 0; i < input.length(); i++) {
			if (input[i] < '0' || input[i]>'9') {
				inputError = true;
			}
		}
		if (inputError) {
			cout << "Integer please!" << endl << endl;
			Sleep(1000);
			continue;
		}
		else {
			// convert string input into int //
			for (int i = 0; i < input.length(); i++) {
				value += ((__int64)input[i] - '0') * pow(10.0, static_cast<double>((__int64)input.length() - 1 - i));
			}
			if (value == 0) {
				cout << variableName << " can't be 0!" << endl << endl;
				Sleep(1000);
				continue;
			}
			break;
		}
	}
	cout << endl;
	return value;
}

int inputInteger(string variableName) {
	int value = 0;
	bool inputError;
	while (1) {
		cout << "Please input " << variableName << " :";
		getline(cin, input);
		// check if all materials in input are numbers //
		if (!(input[0] == '-' || (input[0] >= '0' && input[0] <= '9'))) {
			cout << "Integer please!" << endl << endl;
			Sleep(1000);
			continue;
		}
		inputError = false;
		for (int k = 1; k < input.length(); k++) {
			if (input[k] < '0' || input[k]>'9') {
				inputError = true;
			}
		}
		if (inputError) {
			cout << "Integer please!" << endl << endl;
			Sleep(1000);
			continue;
		}
		else {
			// convert string input into int //
			if (input[0] == '-') {
				for (int k = 1; k < input.length(); k++) {
					value += ((__int64)input[k] - '0') * pow(10.0, static_cast<double>((__int64)input.length() - 1 - k));
				}
				value *= -1;
			}
			else {
				for (int k = 0; k < input.length(); k++) {
					value += ((__int64)input[k] - '0') * pow(10.0, static_cast<double>((__int64)input.length() - 1 - k));
				}
			}
			break;
		}
	}
	return value;
}

int chooseOption_0to9(int min, int max, string question, string option) {
	while (1) {
		cout << question << option;
		getline(cin, input);
		if (input.length() != 1) {
			cout << "One digit only please!" << endl << endl;
			Sleep(1000);
			continue;
		}
		// check if the characters been inputted are not out of range //
		if ((input[0] - '0') < min || (input[0] - '0') > max) {
			cout << min << " to " << max << " please!" << endl << endl;
			Sleep(1000);
			continue;
		}
		break;
	}
	return (input[0] - '0');
}

inline int maximum(int a, int b, int c, int d, int e, int f, int g) {	//the function needs at least 2 integers
	int max = a;
	if (b > max)max = b;
	if (c > max)max = c;
	if (d > max)max = d;
	if (e > max)max = e;
	if (f > max)max = f;
	if (g > max)max = g;
	return max;
}

inline string int2str(int& number) {	// convert int into string
	string s;
	stringstream ss(s);
	ss << number;
	return ss.str();
}

inline void inputMatrix(const int& height, const int& width, vector<int>& array, int& length) {
	int buffer;
	int counter;
	int number;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			system("cls");
			cout << "The size of the matrix is " << height << " ¡Ñ " << width << " ." << endl << endl;
			for (int k = 0; k < i; k++) {
				for (int l = 0; l < width; l++) {
					cout << "A(" << k + 1 << "," << l + 1 << ") = " << array[k * width + l] << endl;
				}
			}
			for (int l = 0; l < j; l++) {
				cout << "A(" << i + 1 << "," << l + 1 << ") = " << array[i * width + l] << endl;
			}

			// make up the name of the variable that should be inputted //
			string name = "the number of A(";
			number = i + 1;
			name.insert(name.length(), int2str(number));
			name.insert(name.length(), ",");
			number = j + 1;
			name.insert(name.length(), int2str(number));
			name.insert(name.length(), ")");

			array[i * width + j] = inputInteger(name);
			buffer = array[i * width + j];
			counter = 0;
			// count the length of longest number in the matrix //
			while (1) {
				if (buffer == 0)break;
				buffer /= 10;
				counter++;
			}
			if (counter > length) {
				length = counter;
			}
		}
	}
}

inline void generateMatrix(const int& height, const int& width, vector<int>& array, int& length) {
	srand(time(NULL));
	int buffer;
	int counter;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			array[i * width + j] = rand() % 10000;
			if (rand() % 2) {
				array[i * width + j] *= -1;
			}
		}
	}
	length = 5;
}

inline void printOriginalMatrix(const int height_end, const int width_end, vector<int>& matrix, const int length) {
	cout << "The original matrix :" << endl;
	cout << "  ¢b" << setw(((__int64)length + 3) * width_end + 1) << "¢b";
	cout << endl;
	cout << "¢y" << setw(((__int64)length + 3) * width_end + 5) << "¢j" << endl;
	for (int i = 0; i < height_end; i++) {
		cout << "¢y ";
		for (int j = 0; j < width_end; j++) {
			if (j == 0) {
				cout << setw((__int64)length + 2) << matrix[i * width_end + j];
				continue;
			}
			cout << setw((__int64)length + 3) << matrix[i * width_end + j];
		}
		cout << "   ¢j" << endl;
		cout << "¢y" << setw(((__int64)length + 3) * width_end + 5) << "¢j" << endl;
	}
	cout << "  ¢v" << setw(((__int64)length + 3) * width_end + 1) << "¢v" << endl << endl;
}

inline void findSubMatrix(vector<int>& matrix, int height, int width, int length) {
	int sum = 0;
	int max = matrix[0];
	

	// variables to remember where the max sub-matrix is //
	int height_start = 0;
	int height_end = 0;
	int width_start = 0;
	int width_end = 0;

	
	vector<int> matrixTemp(width);
	for (int upper = 0; upper < height; upper++) {
		for (int lower = upper; lower < height; lower++) {
			for (int i = 0; i < width; i++) {
				matrixTemp[i] = 0;
			}
			for (int column = 0; column < width; column++) {
				for (int row = upper; row <= lower; row++) {
					matrixTemp[column] += matrix[row * width + column];
					timesCount++;
				}
			}
			for (int left = 0; left < width; left++) {
				for (int right = left; right < width; right++) {
					sum = 0;
					for (int column = left; column <= right; column++) {
						sum += matrixTemp[column];
						timesCount++;
					}
					if (sum > max) {
						max = sum;
						height_start = upper;
						height_end = lower;
						width_start = left;
						width_end = right;
						timesCount++;
					}
				}
			}
		}
	}
	
	/*
	for (int upper = 0; upper < height; upper++) {
		for (int lower = upper; lower < height; lower++) {
			for (int left = 0; left < width; left++) {
				for (int right = left; right < width; right++) {
					sum = 0;
					for (int row = upper; row <= lower; row++) {
						for (int column = left; column <= right; column++) {
							sum += matrix[row * width + column];
							timesCount++;
						}
					}
					if (sum > max) {
						height_start = upper;
						height_end = lower;
						width_start = left;
						width_end = right;
						max = sum;
					}
				}
			}
		}
	}
	*/

	if (max >= 0) {
		printSubMatrix(height_start, height_end, width_start, width_end, width, matrix, length);
	}
	else {
		max = 0;
		cout << "The sub-matrix that has the maximum sum :" << endl << endl;
		cout << "  ¢b" << setw(((__int64)length + 3) + 1) << "¢b";
		cout << endl;
		cout << "¢y" << setw(((__int64)length + 3) + 5) << "¢j" << endl;
		cout << "¢y" << setw(((__int64)length + 3) + 5) << "¢j" << endl;
		cout << "  ¢v" << setw(((__int64)length + 3) + 1) << "¢v" << endl << endl;
	}
	cout << endl << "Maximum sum = " << max << endl << endl << endl;
}

inline void printSubMatrix(const int height_start, const int height_end, const int width_start, const int width_end, const int width, vector<int>& matrix, const int length) {
	cout << "The sub-matrix that has the maximum sum :" << endl;
	cout << "  ¢b" << setw(((__int64)length + 3) * ((__int64)width_end - (__int64)width_start + 1) + 1) << "¢b";
	cout << endl;
	cout << "¢y" << setw(((__int64)length + 3) * ((__int64)width_end - (__int64)width_start + 1) + 5) << "¢j" << endl;
	for (int i = height_start; i <= height_end; i++) {
		cout << "¢y ";
		for (int j = width_start; j <= width_end; j++) {
			if (j == width_start) {
				cout << setw((__int64)length + 2) << matrix[i * width + j];
				continue;
			}
			cout << setw((__int64)length + 3) << matrix[i * width + j];
		}
		cout << "   ¢j" << endl;
		cout << "¢y" << setw(((__int64)length + 3) * ((__int64)width_end - (__int64)width_start + 1) + 5) << "¢j" << endl;
	}
	cout << "  ¢v" << setw(((__int64)length + 3) * ((__int64)width_end - (__int64)width_start + 1) + 1) << "¢v" << endl << endl;
}