#include <iostream>
#include "Model.h"

using namespace std;

const double learning_rate = .02;

int main() {
	//srand(time(NULL));
	Model model(2);


	model.Add(2);
	model.Add(1);



	vector<vector<double>> inputs;
	vector<vector<double>> targets;


	vector<double> inputs_buffer;
	inputs_buffer.push_back(2);
	inputs_buffer.push_back(7);
	inputs.push_back(inputs_buffer);

	inputs_buffer.clear();
	inputs_buffer.push_back(1);
	inputs_buffer.push_back(15);
	inputs.push_back(inputs_buffer);

	inputs_buffer.clear();
	inputs_buffer.push_back(3);
	inputs_buffer.push_back(1);
	inputs.push_back(inputs_buffer);

	//inputs_buffer.clear();
	//inputs_buffer.push_back(1);
	//inputs_buffer.push_back(0);
	//inputs.push_back(inputs_buffer);

	//inputs_buffer.clear();
	//inputs_buffer.push_back(1);
	//inputs_buffer.push_back(1);
	//inputs.push_back(inputs_buffer);


	vector<double> targeta_buffer;
	targeta_buffer.push_back(18);
	targets.push_back(targeta_buffer);

	targeta_buffer.clear();
	targeta_buffer.push_back(32);
	targets.push_back(targeta_buffer);

	targeta_buffer.clear();
	targeta_buffer.push_back(8);
	targets.push_back(targeta_buffer);

	//targeta_buffer.clear();
	//targeta_buffer.push_back(1);
	//targets.push_back(targeta_buffer);

	//targeta_buffer.clear();
	//targeta_buffer.push_back(1);
	//targets.push_back(targeta_buffer);



	//input.push_back(1.6);

	model.ShowModel();
	//model.ShowNeurons();


	//model.ShowModel();
	//model.ShowNeurons();

	//for (int i = 0; i < predict.size(); i++)
	//	cout << " " << i << ":  " << predict[i] << endl;

	//vector<double> target;
	//target.push_back(0.5);
	//target.push_back(0.08);

	for (int i = 0; i < 100; i++){
		for (int j = 0; j < 2; j++) {
			model.learn(inputs[j], targets[j], learning_rate);
		}
	}

	cout << endl << "<=============>" << endl;

	vector<double> input;


	input.clear();
	input.push_back(2);
	input.push_back(6);

	vector<double> predict = model.predict(input);

	for (int i = 0; i < input.size(); i++)
		cout << input[i] << "; ";

	cout << endl;
	for (int i = 0; i < predict.size(); i++)
		cout << " " << i << ":  " << predict[i] << endl;

	cout << "<=============>" << endl;

	input.clear();
	input.push_back(1);
	input.push_back(5);

	predict = model.predict(input);

	for (int i = 0; i < input.size(); i++)
		cout << input[i] << "; ";

	cout << endl;
	for (int i = 0; i < predict.size(); i++)
		cout << " " << i << ":  " << predict[i] << endl;

	cout << "<=============>" << endl;



	return 0;
}



//тип работы : "дети", "государственный", "никогда не работал", "частный" или "самозанятый"
				//0		   1						 2						   3					4