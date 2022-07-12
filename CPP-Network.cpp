#include <iostream>
#include <string>
#include "Model.h"

using namespace std;

const double learning_rate = .000000001;
//const double learning_rate = .001;

int main() {
	Model model(784);
	model.Add(10);


	cout << endl << "Press Enter to start fit...";
	getchar();
	model.fit("dataset.csv", learning_rate, 1, 100);


	fstream file_X_test;
	file_X_test.open("dataset.csv", ios::in);
	string line, word, temp;
	int test_counter = 0;
	float true_counter = 0;
	float false_counter = 0;

	cout << "[Tests...]" << endl;
	vector<double> X_test;
	while (file_X_test >> temp) {
		test_counter++;

		X_test.clear();
		int Y_test = stoi(temp.substr(0, 1));
		//cout << "Number: " << Y_test << endl;
		temp.erase(0, 2);
		size_t pos = 0;
		string token;
		while ((pos = temp.find(",")) != string::npos) {
			token = temp.substr(0, pos);
			X_test.push_back(stoi(token));
			temp.erase(0, pos + 1);
		}
		X_test.push_back(stoi(temp));

		vector<double> predict = model.predict(X_test);
		//vector<double> predict_chances = model.softmax(predict);

		//cout << endl;
		int max_result = predict[0];
		for (int i = 0; i < predict.size(); i++) {
			//cout << " " << i << ":  " << round(predict[i]) << ";		" << predict[i] << endl;
			if (predict[i] > predict[max_result])	 max_result = i;
		}
		//cout << "Predict: " << max_result << ";	   Target: " << Y_test << endl;
		//cout << "<=================================>" << endl;
		if (max_result == Y_test)	true_counter++;
		else						false_counter++;


		if (test_counter == 100) break;
	}

	cout << endl << "True:	" << true_counter / 1 << "%" << endl;
	cout << "False:	" << false_counter / 1 << "%" << endl;

	int error_colors[] = { 255, 0, 0 };
	int acc_colors[] = { 0, 255, 0 };

	cout << endl << "Press Enter to see graphics...";
	getchar();
	system("cls");
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << "Press Enter to exit..." << endl;
	Sleep(100);
	model.initDraw();
	model.drawGraphic(model.Total_errors, 2, error_colors);
	model.drawGraphic(model.Total_accuracies, 2, acc_colors);
	/*getchar();*/

	return 0;
}



//тип работы : "дети", "государственный", "никогда не работал", "частный" или "самозанятый"
				//0		   1						 2						   3					


	//for (int epoch = 1; epoch <= 10; epoch++) {
	//	cout << "Epoch " << epoch << "/10: " << endl;
	//	int train_counter = 0;
	//	file_X_train.close();
	//	file_X_train.open("dataset.csv", ios::in);
	//	while (file_X_train >> temp) {
	//		train_counter++;
	//		//if (train_counter == 1001) break;
	//		if (train_counter % 1000 == 0) cout << "	" << train_counter << "/42000;" << endl;
	//		X_train.clear();
	//		Y_train.clear();
	//		int Y_train_target = stoi(temp.substr(0, 1));
	//		for (int i = 0; i < 10; i++) {
	//			if (i == Y_train_target) Y_train.push_back(1);
	//			else					Y_train.push_back(0);
	//		}
	//		temp.erase(0, 2);
	//		size_t pos = 0;
	//		string token;
	//		while ((pos = temp.find(",")) != string::npos) {
	//			token = temp.substr(0, pos);
	//			X_train.push_back(stoi(token));
	//			temp.erase(0, pos + 1);
	//		}
	//		X_train.push_back(stoi(temp));
	//		//cout << train_counter << "	Target: " << Y_train_target << endl;
	//		model.learn(X_train, Y_train, learning_rate);
	//	}
	//}