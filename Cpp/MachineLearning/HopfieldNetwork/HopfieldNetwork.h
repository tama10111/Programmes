/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HopfieldNetwork.h
 * Author: tama
 *
 * Created on 10 février 2018, 12:40
 */

#ifndef HOPFIELDNETWORK_H
#define HOPFIELDNETWORK_H

#include <cstdlib>
#include <cstring>
#include <cstdio>

class HopfieldNetwork {
public:
 
    HopfieldNetwork(int number_of_neurons, int* pattern);
    virtual ~HopfieldNetwork();
    void train();
    void computeNextState();
    void writePattern();
    
    int number_of_neurons;
    
    int* pattern;
    int* neuron;
    
    int** w;

};

#endif /* HOPFIELDNETWORK_H */

