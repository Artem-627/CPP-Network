#include <iostream>
#include <string>
#include "Model.h"

const double learning_rate = .00001;

int main() {
	Model model(784);
	model.Add(100);
	model.Add(10);

	system("pause");

	model.fit("dataset.csv", learning_rate, 3, 1000);

	std::cout << "[Tests...]" << std::endl;
	std::cout << model.getTotalAccuracy("dataset.csv", 10000) << std::endl;



	return 0;
}
