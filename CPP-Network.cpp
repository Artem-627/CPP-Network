#include <iostream>
#include <string>
#include <fstream>
#include "Model.h"

using namespace std;

const double learning_rate = 0.01;

int main() {
	//srand(time(NULL));
	//Model model(3);


	//model.Add(1);



	//vector<vector<double>> inputs;
	//vector<vector<double>> targets;


	//vector<double> inputs_buffer;
	//inputs_buffer.push_back(1);
	//inputs_buffer.push_back(2);
	//inputs_buffer.push_back(3);
	//inputs.push_back(inputs_buffer);

	//inputs_buffer.clear();
	//inputs_buffer.push_back(10);
	//inputs_buffer.push_back(11);
	//inputs_buffer.push_back(12);
	//inputs.push_back(inputs_buffer);

	//inputs_buffer.clear();
	//inputs_buffer.push_back(4);
	//inputs_buffer.push_back(5);
	//inputs_buffer.push_back(6);
	//inputs.push_back(inputs_buffer);

	//inputs_buffer.clear();
	//inputs_buffer.push_back(2);
	//inputs_buffer.push_back(4);
	//inputs_buffer.push_back(8);
	//inputs.push_back(inputs_buffer);



	//vector<double> targeta_buffer;
	//targeta_buffer.push_back(4);
	//targets.push_back(targeta_buffer);

	//targeta_buffer.clear();
	//targeta_buffer.push_back(13);
	//targets.push_back(targeta_buffer);

	//targeta_buffer.clear();
	//targeta_buffer.push_back(7);
	//targets.push_back(targeta_buffer);

	//targeta_buffer.clear();
	//targeta_buffer.push_back(16);
	//targets.push_back(targeta_buffer);



	//for (int i = 0; i < 5000; i++){
	//	for (int j = 0; j < 4; j++) {
	//		cout << i << " -> ";
	//		model.learn(inputs[j], targets[j], learning_rate);
	//	}
	//}

	//cout << endl << "<=============>" << endl;

	//vector<double> input;


	//input.clear();
	//input.push_back(1);
	//input.push_back(2);
	//input.push_back(3);

	//vector<double> predict = model.predict(input);

	//for (int i = 0; i < input.size(); i++)
	//	cout << input[i] << "; ";

	//cout << endl;
	//for (int i = 0; i < predict.size(); i++)
	//	cout << " " << i << ":  " << round(predict[i]) << endl;

	//cout << "<=============>" << endl;

	//input.clear();
	//input.push_back(7);
	//input.push_back(8);
	//input.push_back(9);

	//predict = model.predict(input);

	//for (int i = 0; i < input.size(); i++)
	//	cout << input[i] << "; ";

	//cout << endl;
	//for (int i = 0; i < predict.size(); i++)
	//	cout << " " << i << ":  " << round(predict[i]) << endl;

	//cout << "<=============>" << endl;

	//input.clear();
	//input.push_back(3);
	//input.push_back(4);
	//input.push_back(5);

	//predict = model.predict(input);

	//for (int i = 0; i < input.size(); i++)
	//	cout << input[i] << "; ";

	//cout << endl;
	//for (int i = 0; i < predict.size(); i++)
	//	cout << " " << i << ":  " << round(predict[i]) << endl;

	//cout << "<=============>" << endl;

	//input.clear();
	//input.push_back(5);
	//input.push_back(15);
	//input.push_back(25);

	//predict = model.predict(input);

	//for (int i = 0; i < input.size(); i++)
	//	cout << input[i] << "; ";

	//cout << endl;
	//for (int i = 0; i < predict.size(); i++)
	//	cout << " " << i << ":  " << round(predict[i]) << endl;

	//cout << "<=============>" << endl;

	//input.clear();
	//input.push_back(10);
	//input.push_back(9);
	//input.push_back(8);

	//predict = model.predict(input);

	//for (int i = 0; i < input.size(); i++)
	//	cout << input[i] << "; ";

	//cout << endl;
	//for (int i = 0; i < predict.size(); i++)
	//	cout << " " << i << ":  " << round(predict[i]) << endl;

	//cout << "<=============>" << endl;

	//input.clear();
	//input.push_back(2);
	//input.push_back(4);
	//input.push_back(8);

	//predict = model.predict(input);

	//for (int i = 0; i < input.size(); i++)
	//	cout << input[i] << "; ";

	//cout << endl;
	//for (int i = 0; i < predict.size(); i++)
	//	cout << " " << i << ":  " << round(predict[i]) << endl;

	//cout << "<=============>" << endl;


	fstream fin;


	fin.open("dataset.csv", ios::in);

	string line, word, temp;

	while (fin >> temp) {
		
		getline(fin, line);

		cout << line << endl;

	}


	return 0;
}



//тип работы : "дети", "государственный", "никогда не работал", "частный" или "самозанятый"
				//0		   1						 2						   3					4