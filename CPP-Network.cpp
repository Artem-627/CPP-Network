#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Model.h"

const double learning_rate = .0001;

float getPixelColor(cv::Mat image, int x, int y) {
	float color = (float)(image.at<cv::Vec3b>(cv::Point(y, x))[0] + image.at<cv::Vec3b>(cv::Point(y, x))[1] + image.at<cv::Vec3b>(cv::Point(y, x))[2]) / (3 * 255);
	return color;
}

int main() {
	Model model(784);
	model.Add(100);
	model.Add(10);

	system("pause");

	model.fit("dataset.csv", learning_rate, 5, 1000);

	std::cout << "[Tests...]" << std::endl;
	std::cout << "Total accuracy = " << model.getTotalAccuracy("dataset.csv", 10000) << std::endl;


	// Пример
	cv::Mat img = cv::imread("C:/Users/Artem/source/repos/OpenCV/img1.jpg");
	img.resize(28, 28);

	std::vector<double> image(28*28);

	for (int i = 0; i < 28; ++i) {
		for (int j = 0; j < 28; ++j) {
			image[28 * i + j] = (float)getPixelColor(img, i, j);
		}
	}

	std::vector<double> predict = model.predict(image);
	int result = 0;
	for (int i = 0; i < 10; ++i) {
		if (predict[i] > predict[result]) {
			result = i;
		}
	}

	std::cout << "Number on picture: " << result << std::endl;

	cv::namedWindow("Image");
	cv::imshow("Image", img);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}
