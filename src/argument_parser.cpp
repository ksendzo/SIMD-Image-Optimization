
#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <unordered_map>
#include "operation.h"
#include <fstream>
#include <sstream>

using namespace std;

unordered_map<string, operation_types> names = {
	{"add", ADD},
	{"sub", SUB},
	{"isb", ISUB},
	{"mul", MUL},
	{"div", DIV},
	{"idi", IDIV},
	{"pow", POW},
	{"log", LOG},
	{"abs", ABS},
	{"min", MIN},
	{"max", MAX},
	{"inv", INV},
	{"gra", GRAY},
	{"fil", FILTER}
};

vector<pair<operation_types, int>*> to_do;

vector<vector<vector<float>>> filter_matrix;

vector<vector<float>> read_filter(string fileName, int radius) {
	ifstream file(fileName);

	if (!file) {
		cerr << "Error opening file: " << fileName << endl;
	}
	int n = radius * 2 + 1;
	vector<vector<float>> matrix(n, vector<float>(n));
	float value;
	string line;

	for (int i = 0; i < n; i++) {
		getline(file, line);
		istringstream iss(line);

		for (int j = 0; j < n; j++) {
			iss >> matrix[i][j];
		}
	}

	file.close();
	return matrix;
}

void parse_arguments(int argc, char* argv[]) {

	for (int i = 3; i < argc; i++) {
		string arg = argv[i];
		string name = arg.substr(0, 3);
		if (arg.length() > 3) {
			string param = arg.substr(4, arg.length() - 5);
			if (name != "fil") {
				to_do.push_back(new pair<operation_types, int>(names[name], stoi(param)));
			}
			else {
				int pos = arg.find(',');
				int radius = stoi(arg.substr(4, pos - 4));
				string fileName = arg.substr(pos + 1, arg.length() - pos - 2);
				vector<vector<float>> matrix = read_filter(fileName, radius);

				to_do.push_back(new pair<operation_types, int>(names[name], filter_matrix.size()));
				filter_matrix.push_back(matrix);
			}
		}
		else to_do.push_back(new pair<operation_types, int>(names[name], 0));
	}
}