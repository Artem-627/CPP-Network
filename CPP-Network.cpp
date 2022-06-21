#include <iostream>
#include "Model.h"

using namespace std;

const double learning_rate = 0.1;

int main() {
	//srand(time(NULL));
	Model model(2);


	//model.Add(5);
	model.Add(1);



	vector<vector<double>> inputs;
	vector<vector<double>> targets;


	vector<double> inputs_buffer;
	inputs_buffer.push_back(-1);
	inputs_buffer.push_back(-1);
	inputs.push_back(inputs_buffer);

	inputs_buffer.clear();
	inputs_buffer.push_back(-1);
	inputs_buffer.push_back(1);
	inputs.push_back(inputs_buffer);

	inputs_buffer.clear();
	inputs_buffer.push_back(1);
	inputs_buffer.push_back(-1);
	inputs.push_back(inputs_buffer);

	inputs_buffer.clear();
	inputs_buffer.push_back(1);
	inputs_buffer.push_back(1);
	inputs.push_back(inputs_buffer);


	vector<double> targeta_buffer;
	targeta_buffer.push_back(1);
	targets.push_back(targeta_buffer);

	targeta_buffer.clear();
	targeta_buffer.push_back(0);
	targets.push_back(targeta_buffer);

	targeta_buffer.clear();
	targeta_buffer.push_back(0);
	targets.push_back(targeta_buffer);

	targeta_buffer.clear();
	targeta_buffer.push_back(1);
	targets.push_back(targeta_buffer);



	//input.push_back(1.6);

	//model.ShowModel();
	//model.ShowNeurons();


	//model.ShowModel();
	//model.ShowNeurons();

	//for (int i = 0; i < predict.size(); i++)
	//	cout << " " << i << ":  " << predict[i] << endl;

	//vector<double> target;
	//target.push_back(0.5);
	//target.push_back(0.08);

	for (int i = 0; i < 50; i++){
		for (int j = 0; j < 4; j++) {
			cout << "j = " << j << endl;
			model.learn(inputs[j], targets[j], learning_rate);
		}
	}

	cout << endl << "<=============>" << endl;

	vector<double> input;
	input.push_back(-1);
	input.push_back(1);

	vector<double> predict = model.predict(input);

	for (int i = 0; i < predict.size(); i++)
		cout << " " << i << ":  " << predict[i] << endl;

	cout << endl << "<=============>" << endl;

	input.clear();
	input.push_back(1);
	input.push_back(1);

	predict.clear();
	predict = model.predict(input);

	for (int i = 0; i < predict.size(); i++)
		cout << " " << i << ":  " << predict[i] << endl;

	cout << endl << "<=============>" << endl;

	input.clear();
	input.push_back(1);
	input.push_back(-1);

	predict.clear();
	predict = model.predict(input);

	for (int i = 0; i < predict.size(); i++)
		cout << " " << i << ":  " << predict[i] << endl;

	cout << endl << "<=============>" << endl;

	input.clear();
	input.push_back(-1);
	input.push_back(-1);

	predict.clear();
	predict = model.predict(input);

	for (int i = 0; i < predict.size(); i++)
		cout << " " << i << ":  " << predict[i] << endl;

	return 0;
}



//тип работы : "дети", "государственный", "никогда не работал", "частный" или "самозанятый"
				//0		   1						 2						   3					4