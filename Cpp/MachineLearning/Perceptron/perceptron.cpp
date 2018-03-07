#include "perceptron.h"
#include <cstdlib>
#include <cstring>
#include <cmath>

Perceptron::Perceptron(int number_of_inputs, double bias, double learning_rate){
    
    this->bias = bias;
    this->learning_rate = learning_rate;
    this->output = 0;
    this->t_input = (double*) std::malloc(number_of_inputs*sizeof(double));
    this->t_weight = (double*) std::malloc(number_of_inputs*sizeof(double));
    this->number_of_inputs = number_of_inputs;
    
    for(int i = 0; i<number_of_inputs; i++){
        this->t_input[i] = 0.0;
        this->t_weight[i] = 0.0;
    }
}

Perceptron::~Perceptron(){
    std::free(this->t_input);
    std::free(this->t_weight);
}

void Perceptron::write_input(double* input_vector){
    for(int i = 0; i<this->number_of_inputs; i++){
        this->t_input[i] = input_vector[i];
    }
}

void Perceptron::computeOutput(){
    double z = 0.0;
    for(int i = 0; i<this->number_of_inputs; i++){
        z += this->t_input[i]*this->t_weight[i];
    }
    
    /* UTILE POUR UN PERCEPTRON BINAIRE
    if(z >=this->bias){
        this->output = 1.0;
    } else{
        this->output = 0.0;
    }
    */
    
    this->output = tanh(z);
}

void Perceptron::learn(double* input_vector, double expected_output, double error){
    
    this->write_input(input_vector);
    this->computeOutput();
    
    for(int i = 0; i<this->number_of_inputs; i++){
        this->t_weight[i] += this->learning_rate*(expected_output-this->output)*this->t_input[i];
    }
}

void Perceptron::train(double** learning_set, double* expected_output_set, double error, int sizeof_set){
    for(int i = 0; i<sizeof_set; i++){
        this->learn(learning_set[i], expected_output_set[i], error);
    }
}

double Perceptron::getOutput(){
    return this->output; 
}

double* Perceptron::getWeights(){
    return this->t_weight;
}

double Perceptron::test(double** learning_set, double* expected_output_set, int sizeof_set){
    double acc = 0.0;
    for(int i = 0; i<sizeof_set; i++){
        this->write_input(learning_set[i]);
        this->computeOutput();
        if(this->output == expected_output_set[i]){
            acc+=1.0;
        }
    }
    return acc/((double) sizeof_set)*100.0;
}
