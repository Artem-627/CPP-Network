#include <iostream>
#include <string>
#include <fstream>
#include "Model.h"

using namespace std;

const double learning_rate = .00000001;

int main() {
	//srand(time(NULL));
	Model model(784);


	//model.Add(20);
	model.Add(10);



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


	fstream file_X_train;
	fstream file_X_test;


	file_X_train.open("dataset.csv", ios::in);
	file_X_test.open("dataset.csv", ios::in);

	string line, word, temp;

	vector<double> X_train;
	vector<double> Y_train;

	int train_counter = 0;
	int test_counter = 0;

	while (file_X_train >> temp) {
		train_counter++;
		if (train_counter == 5000) break;

		X_train.clear();
		Y_train.clear();
		int Y_train_target = stoi(temp.substr(0, 1));
		for (int i = 0; i < 10; i++) {
			if (i == Y_train_target) Y_train.push_back(1);
			else					Y_train.push_back(0);
		}
		temp.erase(0, 2);
		size_t pos = 0;
		string token;
		while ((pos = temp.find(",")) != string::npos) {
			token = temp.substr(0, pos);
			X_train.push_back(stoi(token));
			temp.erase(0, pos + 1);
		}
		X_train.push_back(stoi(temp));
		cout << train_counter << endl;
		model.learn(X_train, Y_train, learning_rate);
	}

	int true_counter = 0;
	int false_counter = 0;

	vector<double> X_test;
	while (file_X_test >> temp) {
		test_counter++;

		X_test.clear();
		int Y_test = stoi(temp.substr(0, 1));
		cout << "Number: " << Y_test << endl;
		temp.erase(0, 2);
		size_t pos = 0;
		string token;
		while ((pos = temp.find(",")) != string::npos) {
			token = temp.substr(0, pos);
			X_test.push_back(stoi(token));
			temp.erase(0, pos + 1);
		}
		X_test.push_back(stoi(temp));

		vector<double> predict = model.softmax(model.predict(X_test));

		cout << endl;
		int max_result = predict[0];
		for (int i = 0; i < predict.size(); i++) {
			cout << " " << i << ":  " << round(predict[i]) << ";		" << predict[i] << endl;
			if (predict[i] > max_result)	 max_result = i;
		}
		cout << "	Predict: " << max_result << ";	   Target: " << Y_test << endl;
		cout << "<=================================>" << endl;
		if (max_result == Y_test)	true_counter++;
		else						false_counter++;


		if (test_counter == 11) break;
	}

	cout << endl << "True:	" << true_counter << endl;
	cout << "False:	" << false_counter << endl;


	return 0;
}



//тип работы : "дети", "государственный", "никогда не работал", "частный" или "самозанятый"
				//0		   1						 2						   3					4