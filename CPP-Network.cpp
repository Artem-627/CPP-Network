#include <iostream>
#include "Model.h"

using namespace std;

int main() {
	//srand(time(NULL));
	Model model(2);


	//model.Add(5);
	model.Add(2);

	cout << model.d_ReLU(0.5) << endl;
	cout << model.d_ReLU(1) << endl;



	vector<double> input;
	input.push_back(1);
	input.push_back(1);
	//input.push_back(1.6);

	//model.ShowModel();
	//model.ShowNeurons();

	vector<double> predict = model.predict(input);

	//model.ShowModel();
	//model.ShowNeurons();

	//for (int i = 0; i < predict.size(); i++)
	//	cout << " " << i << ":  " << predict[i] << endl;

	vector<double> target;
	target.push_back(0.5);
	target.push_back(0.08);
	double learning_rate = 0.1;

	for (int i = 0; i < 100; i ++)
		model.learn(input, target, learning_rate);

	return 0;
}



//тип работы : "дети", "государственный", "никогда не работал", "частный" или "самозанятый"
				//0		   1						 2						   3					4