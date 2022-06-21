#include <iostream>
#include "Model.h"

using namespace std;

const double learning_rate = 0.1;

int main() {
	//srand(time(NULL));
	Model model(2);


	//model.Add(5);
	model.Add(2);

	cout << model.d_ReLU(0.5) << endl;
	cout << model.d_ReLU(1) << endl;


	vector<vector<double>> inputs;
	vector<vector<double>> targets;



	vector<double> inputs_buffer;
	inputs_buffer.push_back(0);
	inputs_buffer.push_back(0);
	inputs.push_back(inputs_buffer);

	inputs_buffer.clear();
	inputs_buffer.push_back(0);
	inputs_buffer.push_back(1);
	inputs.push_back(inputs_buffer);

	inputs_buffer.clear();
	inputs_buffer.push_back(1);
	inputs_buffer.push_back(0);
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

	for (int i = 0; i < 50; i ++)
		for (int j = 0; j < dataset.size(); j ++)
			model.learn(inputs[j], targets[j], learning_rate);

	vector<double> input;
	input.push_back(0);
	input.push_back(1);

	vector<double> predict = model.predict(input);

	for (int i = 0; i < predict.size(); i++)
		cout << " " << i << ":  " << predict[i] << endl;

	return 0;
}



//тип работы : "дети", "государственный", "никогда не работал", "частный" или "самозанятый"
				//0		   1						 2						   3					4