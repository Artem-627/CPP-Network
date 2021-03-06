#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>

using namespace std;

class Neuron {
public:
	vector<double> weights;
	vector<double> batch_correction;
	double value = 0;
	double error;

	Neuron(vector<double> weight) {
		this->weights = weight;
		this->new_batch_correction(weight.size());
	}

	void clear() {
		this->value = 0;
	}

	void new_batch_correction(int size) {
		this->batch_correction.clear();
		for (int i = 0; i < size; i++) {
			this->batch_correction.push_back(0);
		}
	}
};

class Model {
public:
	vector<vector<Neuron>> neurons;
	int now_index = 1;
	vector<double> Total_errors;
	double Total_error = 0;
	vector<double> Total_accuracies;
	double Total_accuracy = 0;
	HDC hDC;

	Model(int input_quantity) {
		cout << "[Create model...]" << endl;
		vector<Neuron> neuron_buffer; neuron_buffer.clear();
		for (int i = 0; i < input_quantity; i++) {
			neuron_buffer.push_back(Neuron({}));
		}
		this->neurons.push_back(neuron_buffer);
		cout << "[Layer with size = " << input_quantity << " created]" << endl;
	}

	Model() {}

	vector<double> softmax(vector<double> inputs) {
		vector<double> result;
		float EkeY = 0;
		for (int i = 0; i < inputs.size(); i++) {
			EkeY += exp(inputs[i]);
		}
		for (int i = 0; i < inputs.size(); i++) {
			result.push_back(exp(inputs[i]) / EkeY);
		}
		return result;
	}

	void initDraw() {
		this->hDC = GetDC(GetConsoleWindow());
		HPEN Pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		SelectObject(hDC, Pen);

		MoveToEx(hDC, 0, 160, NULL);
		LineTo(hDC, 800, 160);
		MoveToEx(hDC, 0, 40, NULL);
		LineTo(hDC, 800, 40);
	}
	
	void drawGraphic(vector<double> points, int thickness, int color[]) {
		//POINT* p = new POINT[points.size() + 1];
		//POINT* p = new POINT[10];
		//POINT p[500];

		HPEN Pen = CreatePen(PS_SOLID, thickness, RGB(color[0], color[1], color[2]));
		SelectObject(this->hDC, Pen);
		MoveToEx(this->hDC, 20, (-points[0] * 120) + 160, NULL);

		for (int i = 0; i < points.size(); i++)
		{
			LineTo(this->hDC, i + 20, (-points[i] * 120) + 160);
		}
	}

	double ReLU(double x) {
		return x > 0 ? x : 0;
		//return x;
		//return 1 / (1 + exp(-x));
	}
	
	double d_ReLU(double x) {
		return 1;
		//return ReLU(x) * (1 - ReLU(x)) == 0 ? ReLU(x) * (1 - ReLU(x)) : 1;
		//return ReLU(x) * (1 - ReLU(x));
	}

	double random(double min = 0, double max = 0.000001) {
		return ((double)rand() / RAND_MAX) * max + min;
	}

	void Add(int quantity) {
		vector<Neuron> neurons_buffer;	neurons_buffer.clear();
		vector<double> weights_buffer;	weights_buffer.clear();
		for (int i = 0; i < quantity; i++) {
			for (int k = 0; k < this->neurons[now_index - 1].size(); k++) {
				weights_buffer.push_back(random());
			}
			neurons_buffer.push_back(Neuron(weights_buffer));
			weights_buffer.clear();
		}
		neurons.push_back(neurons_buffer);
		now_index++;
		cout << "[Layer with size = " << quantity << " created]" << endl;
	}

	void ClearModel() {
		for (int layer = 1; layer < neurons.size(); layer++) {
			for (int neuron = 0; neuron < neurons[layer].size(); neuron++) {
				for (int weight = 0; weight < neurons[layer][neuron].weights.size(); weight++) {
					neurons[layer][neuron].clear();
				}
			}
		}
	}

	void ClearErrors() {
		for (int layer = 1; layer < neurons.size(); layer++) {
			for (int neuron = 0; neuron < neurons[layer].size(); neuron++) {
				for (int weight = 0; weight < neurons[layer][neuron].weights.size(); weight++) {
					neurons[layer][neuron].error = 0;
				}
			}
		}
	}

	void ShowNeurons() {
		for (int layer = 1; layer < neurons.size(); layer++) {
			for (int neuron = 0; neuron < neurons[layer].size(); neuron++) {
				for (int weight = 0; weight < neurons[layer][neuron].weights.size(); weight++) {
					cout << layer - 1 << "(" << weight << ") - " << layer << "(" << neuron << ")  =  " << neurons[layer][neuron].weights[weight] << endl;
				}
			}
		}
	}

	void ShowModel() {
		for (int layer = 0; layer < neurons.size(); layer++) {
			for (int neuron = 0; neuron < neurons[layer].size(); neuron++) {
				cout << layer << "(" << neuron << ")  =  " << neurons[layer][neuron].value << endl;
			}
			cout << "---" << endl;
		}
		cout << endl;
	}

	vector<double> predict(vector<double> inputs) {
		vector<double> predict;	predict.clear();
		ClearModel();
		//cout << "Cleared model: " << endl << endl;
		//this->ShowModel();
		//cout << endl << endl;
		for (int input = 0; input < neurons[0].size(); input++) {
			neurons[0][input].value = inputs[input];
			//cout << "neurons[0][input].value = inputs[input] = ";
		}
		//this->ShowModel();
		for (int layer = 1; layer < neurons.size(); layer++) {
			for (int neuron = 0; neuron < neurons[layer].size(); neuron++) {
				for (int weight = 0; weight < neurons[layer][neuron].weights.size(); weight++) {
					neurons[layer][neuron].value += neurons[layer - 1][weight].value * neurons[layer][neuron].weights[weight];
				}
			}
			//this->ShowModel();
		}
		for (int neuron = 0; neuron < neurons[neurons.size() - 1].size(); neuron++) {
			predict.push_back(ReLU(neurons[neurons.size() - 1][neuron].value));
		}
		return predict;
	}

	void learn(vector<double> task, vector<double> target, double learning_rate, bool corrected, int batch_size) {
		vector<double> predict = this->predict(task);
		if (predict.size() != target.size()) {
			cout << "Prediction size don't equal target size!";
			cout << "predict.size() = " << predict.size() << endl;
			cout << "target.size() = " << target.size() << endl;
			exit(10);
		}
		//this->ClearErrors();

		for (int i = 0; i < predict.size(); i++) {
			neurons[neurons.size() - 1][i].error = predict[i] - target[i];
			// Вывод ошибки каждого выходного нейрона
			if (corrected) {
				cout << "	";
				target[i] == 1 ? cout << "+ " : cout << "  ";
				cout << i << " > ";
				if (neurons[neurons.size() - 1][i].error >= 0)
					cout << " ";
				cout << neurons[neurons.size() - 1][i].error << endl;
			}
			Total_error += pow(abs(neurons[neurons.size() - 1][i].error), 2);
		}

		int max_predict = 0;
		int max_target = 0;
		for (int i = 0; i < predict.size(); i++) {
			if (predict[i] > predict[max_predict])	 max_predict = i;
		}
		for (int i = 0; i < target.size(); i++) {
			if (target[i] > target[max_target])	 max_target = i;
		}
		if (max_predict == max_target) Total_accuracy++;

		for (int layer = neurons.size() - 1; layer > 0; layer--) {
			for (int neuron = 0; neuron < neurons[layer].size(); neuron++) {
				double local_error = neurons[layer][neuron].error * d_ReLU(neurons[layer][neuron].value);
				//cout << "	local error[" << layer << "][" << neuron << "] = " << local_error << endl;
				for (int weight = 0; weight < neurons[layer][neuron].weights.size(); weight++) {

					neurons[layer - 1][weight].error += local_error * neurons[layer][neuron].weights[weight];
					//corrected ? neurons[layer - 1][weight].error /= batch_size : neurons[layer - 1][weight].error /= 1;
					double delta_weight = local_error * neurons[layer - 1][weight].value * learning_rate;
					//double delta_weight = local_error * learning_rate;
					//if (corrected)
					neurons[layer][neuron].weights[weight] -= delta_weight;
					//neurons[layer][neuron].batch_correction[weight] += delta_weight;
					//if (corrected) cout << delta_weight << endl;
					//if (corrected)
					//cout << "correction for neuron[" << layer << "][" << neuron << "].batch_correction[" << weight << "] = " << neurons[layer][neuron].batch_correction[weight] << endl;
					
				}
				//if (corrected) {
				//	for (int weight = 0; weight < neurons[layer][neuron].weights.size(); weight++) {
				//		//neurons[layer][neuron].batch_correction[weight] /= batch_size;
				//		neurons[layer][neuron].weights[weight] -= neurons[layer][neuron].batch_correction[weight];
				//		//cout << "Delta neuron[" << layer << "][" << neuron << "].weights[" << weight << "] = " << neurons[layer][neuron].batch_correction[weight] << endl;
				//	}
				//	neurons[layer][neuron].new_batch_correction(neurons[layer][neuron].batch_correction.size());
				//	//cout << "correction for neuron[" << layer << "][" << neuron << "].weights[" << weight << "] = " << neurons[layer][neuron].batch_correction[weight] << endl << endl;
				//}
			}
		}
		this->ClearErrors();
		if (corrected) {
			Total_accuracy /= batch_size;
			Total_error /= batch_size;
			cout << "	MSE: " << Total_error << ";	Accuracy: " << Total_accuracy<< endl;
			Total_errors.push_back(Total_error);
			Total_accuracies.push_back(Total_accuracy);
			cout << "	>--------------------------<" << endl;
			Total_error = 0;
			Total_accuracy = 0;
		}
	}
	
	void  fit(string dataset, double learning_rate, int epochs, int batch_size) {
		system("cls");

		fstream file_X_train;
		string line, word, temp;
		vector<double> X_train;
		vector<double> Y_train;

		for (int epoch = 1; epoch <= epochs; epoch++) {
			cout << "Epoch " << epoch << "/" << epochs << ": " << endl;
			int train_counter = 1;
			file_X_train.close();
			file_X_train.open(dataset, ios::in);
			while (file_X_train >> temp) {
				train_counter++;
				if (train_counter == 1000) break; // Выход из эпохи обучения раньше ее окончания
				if (train_counter % batch_size == 0) cout << "	" << train_counter << "/42000;" << endl;
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
				train_counter % batch_size == 0 ? this->learn(X_train, Y_train, learning_rate, true, batch_size) : this->learn(X_train, Y_train, learning_rate, false, batch_size);
				
			}
		}
	}
};

void safeModel(string namefile, Model* model) {
	ofstream file_to_write;
	file_to_write.open(namefile, ios_base::binary);
	file_to_write.write((char*)model, sizeof(model));
	file_to_write.close();
	cout << "Model saved" << endl;
}

Model loadModel(string namefile){
	Model model;
	ifstream file_to_read;
	file_to_read.open(namefile, ios_base::binary);
	file_to_read.read((char*)&model, sizeof(file_to_read));
	file_to_read.close();
	cout << "Model loaded" << endl;
	cout << "[Debug].loadModel()		Model loaded" << endl;
	return model;
}