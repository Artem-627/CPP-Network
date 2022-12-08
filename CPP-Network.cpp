#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Model.h"

const std::string dataset = "dataset.csv";
const double learning_rate = .00001;
const int epochs = 0;
const int batch_size = 1000;

int main() {
	Model model(784);
	model.Add(150);
	model.Add(10);

	system("pause");

	model.fit(dataset, learning_rate, epochs, batch_size);

	std::cout << "[Tests...]" << std::endl;
	std::cout << "Total accuracy = " << model.getTotalAccuracy(dataset, 10000) << std::endl;


	// Пример
	std::vector<double> predict = model.predict("C:/Users/Artem/source/repos/OpenCV/img1.jpg", true);

	int result = 0;
	for (int i = 0; i < 10; ++i) {
		if (predict[i] > predict[result]) {
			result = i;
		}
	}

	std::cout << "Number on picture: " << result << std::endl;

	model.graph({1, 2, 3, 4, 3, 3, 2, 3, 1});

	return 0;
}
