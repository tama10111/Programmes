/* 
 * File:   perceptron.h
 * Author: tama
 *
 * Created on 26 janvier 2018, 18:44
 */

/*
 * COMMENTS
 * 
 */

#ifndef PERCEPTRON_H
#define PERCEPTRON_H

class Perceptron {
    
private :
    double* t_input;
    double* t_weight;
    double output;
    double bias;
    double learning_rate;
    int number_of_inputs;

    void learn(double* input_vector, double expected_output, double error);

public :
    Perceptron(int number_of_inputs, double bias, double learning_rate);
    ~Perceptron();
    void train(double** learning_set, double* expected_output_set, double error, int sizeof_set);
    double test(double** learning_set, double* expected_output_set, int sizeof_set);
    double getOutput();
    void computeOutput();
    double* getWeights();
    void write_input(double* input_vector);

};

#endif /* PERCEPTRON_H */

