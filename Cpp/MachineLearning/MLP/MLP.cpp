/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MLP.cpp
 * Author: tama
 *
 * Created on 30 janvier 2018, 09:08
 */

#include <cstdlib>
#include <cstdio>
#include <cmath>

#include "MLP.h"

MLP::MLP(int n_layer, int neuron_per_layer, double learning_rate) {

    this->n_layer = n_layer;
    this->neuron_per_layer = neuron_per_layer;
    this->learning_rate = learning_rate;

    this->vector_error = (double*) std::malloc(neuron_per_layer*sizeof(double));
    this->neurons = (double**) std::malloc(n_layer*sizeof(double*));
    this->d_neurons = (double**) std::malloc(n_layer*sizeof(double*));
    this->weights = (double***) std::malloc((n_layer-1)*sizeof(double**));

    for(int i = 0; i<n_layer; i++){
        this->neurons[i] = (double*) std::malloc(neuron_per_layer*sizeof(double));
        this->d_neurons[i] = (double*) std::malloc(neuron_per_layer*sizeof(double));
        this->weights[i] = (double**) std::malloc(neuron_per_layer*sizeof(double*));
        for(int j = 0; j<neuron_per_layer; j++){
            this->neurons[i][j] = 0;
            this->d_neurons[i][j] = 0;
            this->weights[i][j] = (double*) std::malloc(neuron_per_layer*sizeof(double));
            for(int k = 0; k<neuron_per_layer; k++){
                if(i!=n_layer-1){this->weights[i][j][k] = (rand()%2 ? 1 : -1)*(rand()%2);}
            }
        }
    }
}

MLP::~MLP() {

    for(int i = 0; i<this->n_layer; i++){
        for(int j = 0; j<this->neuron_per_layer; j++){
            std::free(this->weights[i][j]);
        }
        std::free(this->neurons[i]);
        std::free(this->d_neurons[i]);
        std::free(this->weights[i]);
    }

    std::free(this->neurons);
    std::free(this->d_neurons);
    std::free(this->weights);
    std::free(this->vector_error);

    for(int i = 0; i<this->sizeof_set; i++){
        std::free(this->training_set[0][i]);
        std::free(this->training_set[1][i]);
    }

    std::free(this->training_set[0]);
    std::free(this->training_set[1]);
}

/*
 * l layer
 * i computed neuron on layer l
 * j neuron on layer l-1
 */

void MLP::computeOutput(double * input_vector){
    this->writeInput(input_vector);
    double z = 0;
    for(int l = 1; l<this->n_layer; l++){
        for(int i = 0; i<this->neuron_per_layer; i++){
            for(int j = 0; j<this->neuron_per_layer; j++){
                z += this->neurons[l-1][j]*this->weights[l-1][j][i];
            }
            this->neurons[l][i] = 1.0/(1.0+exp(-z)); z = 0;
        }
    }
}

void MLP::writeInput(double * input_vector){
    for(int i = 0; i<this->neuron_per_layer; i++){
        this->neurons[0][i] = input_vector[i];
    }
}

void MLP::backpropagation(double* expected_output){

    double o;

    for(int i = 0; i<this->neuron_per_layer; i++){
        o = this->neurons[this->n_layer-1][i];
        this->d_neurons[this->n_layer-1][i] = o*(1-o)*(expected_output[i]-o);
    }

    double sum = 0;

    for(int l = this->n_layer-2; l != 0; l--){
        for(int i = 0; i<this->neuron_per_layer; i++){
            for(int j = 0; j<this->neuron_per_layer; j++){
                sum += this->d_neurons[l+1][j]*this->weights[l][i][j];
            }
            this->d_neurons[l][i] = this->neurons[l][i]*(1-this->neurons[l][i])*sum;
            sum = 0;
        }
    }
    for(int l = 0; l<this->n_layer-1; l++){
        for(int i = 0; i<this->neuron_per_layer; i++){
            for(int j = 0; j<this->neuron_per_layer; j++){
                this->weights[l][i][j] += this->learning_rate*this->d_neurons[l+1][j]*this->neurons[l][i];
            }
        }
    }
}

void MLP::train(){
    for(int i = 0; i<this->sizeof_set; i++){
        this->computeOutput(this->training_set[0][i]);
        this->computeError(this->training_set[1][i]);
        this->backpropagation(this->training_set[1][i]);
    }
}

void MLP::computeError(double* expected_output){
    this->error = 0;
    double o, eo;
    for(int i = 0; i<this->neuron_per_layer; i++){
        o = this->neurons[this->n_layer-1][i];
        eo = expected_output[i];
        this->error += (o-eo)*(o-eo);
    }
    this->error/=2;
}

void MLP::setTrainingSet(double** input_set, double** expected_output_set, int sizeof_set){
    this->training_set[0] = input_set;
    this->training_set[1] = expected_output_set;
    this->sizeof_set = sizeof_set;
}
