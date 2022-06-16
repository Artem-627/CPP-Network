#include <iostream>
#include "Model.h"

using namespace std;

int main() {
	//srand(time(NULL));
	Model model(3);

	//model.Add(2);
	model.Add(1);

	//model.ShowModel();

	vector<double> input;
	input.push_back(1);
	input.push_back(2);
	input.push_back(1.6);
	//vector<double> predict = model.predict(input);


	//model.ShowModel();

	//for (int i = 0; i < predict.size(); i++)
	//	cout << " " << i << ":  " << predict[i] << endl;

	vector<double> target;
	target.push_back(0.7);
	double learning_rate = 0.1;

	for (int i = 0; i < 15; i ++)
		model.learn(input, target, learning_rate);

	return 0;
}