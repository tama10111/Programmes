/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MLP.h
 * Author: tama
 *
 * Created on 30 janvier 2018, 09:08
 */

#ifndef MLP_H
#define MLP_H

class MLP {
public:

    int n_layer;
    int neuron_per_layer;
    int sizeof_set;

    double learning_rate;
    double error;
    double* vector_error;

    double** neurons;
    double** d_neurons;

    double** training_set[2];

    double*** weights;


    MLP(int n_layer, int neuron_per_layer, double learning_rate);
    virtual ~MLP();

    void computeOutput(double* input_vector);
    void writeInput(double* input_vector);
    void backpropagation(double* expected_output);
    void train();
    void computeError(double* expected_output);
    void setTrainingSet(double** input_set, double** expected_output_set, int sizeof_set);
};

#endif /* MLP_H */
