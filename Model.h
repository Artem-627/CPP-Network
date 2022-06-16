#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Neuron {
public:
	vector<double> weights;
	double value = NULL;
	double error;
	Neuron(vector<double> weight) {
		cout << "[Neuron with size = " << weight.size() << " created]" << endl;
		this->weights = weight;
	}

	void clear() {
		double value = NULL;
	}
};

class Model {
public:
	vector<vector<Neuron>> neurons;
	int now_index = 1;
	Model(int input_quantity) {
		cout << "[Create model...]" << endl;
		vector<Neuron> neuron_buffer; neuron_buffer.clear();
		for (int i = 0; i < input_quantity; i++) {
			neuron_buffer.push_back(Neuron({}));
		}
		this->neurons.push_back(neuron_buffer);
	}

	double ReLU(double x) {
		return x > 0 ? x : 0;
		//return x;
		//return 1 / (1 + exp(-x));
	}
	double d_ReLU(double x) {
		return 1;
		//return ReLU(x) * (1 - ReLU(x));
	}

	double random(double min = 0, double max = 1) {
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
		for (int input = 0; input < neurons[0].size(); input++) {
			neurons[0][input].value = inputs[input];
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

	void learn(vector<double> task, vector<double> target, double learning_rate) {
		vector<double> predict = this->predict(task);
		if (predict.size() != target.size())  exit(1);
		//double MSE = 0;
		//double error = 0;
		for (int i = 0; i < predict.size(); i++) {
			//cout << "	" << predict[i] << "		" << target[i] << endl;
			double error = predict[i] - target[i];
			neurons[neurons.size() - 1][i].error = error == 0 ? 0 : pow(error, 2) * error / abs(error);
			//neurons[neurons.size() - 1][i].error = predict[i] - target[i];
			cout << "neurons[" << neurons.size() - 1 << "][" << i << "].error = " << neurons[neurons.size() - 1][i].error << endl;
			//MSE += pow(predict[i] - target[i], 2);
		}
		//MSE /= predict.size();
		//cout << error << endl;
		//cout << MSE << endl;
		//cout << "---" << endl;
		for (int layer = neurons.size() - 1; layer > 0; layer--) {
			for (int neuron = 0; neuron < neurons[layer].size(); neuron++) {
				for (int weight = 0; weight < neurons[layer][neuron].weights.size(); weight++) {
					//double local_error = neurons[layer][neuron].error * d_ReLU(neurons[layer][neuron].value);
					double local_error = neurons[layer][neuron].error * d_ReLU(neurons[layer][neuron].value);
					//cout << "local_error = " << neurons[layer][neuron].error << " * " << d_ReLU(neurons[layer][neuron].value) << " = " << local_error << endl;
					//neurons[layer][neuron].weights[weight] += neurons[layer - 1][weight].value * neurons[layer][neuron].weights[weight] * neurons[layer][neuron].error * learning_rate;
					//neurons[layer][neuron].weights[weight] += d_ReLU(neurons[layer][neuron].value) * neurons[layer][neuron].error * neurons[layer - 1][weight].value * learning_rate;
					//cout << "neurons[" << layer << "][" << neuron << "].error = " << local_error << endl;
					//cout << "neurons[" << layer << "][" << neuron << "].weights[" << weight << "] = " << neurons[layer][neuron].weights[weight];
					double delta_weight = local_error * neurons[layer - 1][weight].value * learning_rate;
					//cout << neurons[layer][neuron].weights[weight] << ";	";
					neurons[layer][neuron].weights[weight] -= delta_weight;
					//cout << neurons[layer][neuron].weights[weight] << ";	" << delta_weight << endl;
					//cout << "  =>  " << neurons[layer][neuron].weights[weight] << endl << "-" << endl;
				}
			}
		}
	}
};