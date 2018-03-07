/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HopfieldNetwork.cpp
 * Author: tama
 * 
 * Created on 10 février 2018, 12:41
 */

#include "HopfieldNetwork.h"
#include "Window.h"


HopfieldNetwork::HopfieldNetwork(int number_of_neurons, int* pattern){

    this->number_of_neurons = number_of_neurons;
    this->pattern = pattern;
    
    this->neuron = (int*) std::malloc(number_of_neurons*sizeof(int));
    this->w = (int**) std::malloc(number_of_neurons*sizeof(int*));    

    memset(this->neuron, 0, number_of_neurons*sizeof(int));
    
    for(int i = 0; i<number_of_neurons; i++){
        this->w[i] = (int*) std::malloc(number_of_neurons*sizeof(int));
        memset(this->w[i], 0, number_of_neurons*sizeof(int));
    }
}

HopfieldNetwork::~HopfieldNetwork() {

    std::free(this->neuron);
    std::free(this->w);
}

void HopfieldNetwork::writePattern(){
    for(int i = 0; i<this->number_of_neurons; i++){
        this->neuron[i] = this->pattern[i];
    }
}

void HopfieldNetwork::computeNextState(){

    int s_next[this->number_of_neurons];
    int acc;
    
    for(int i = 0; i<this->number_of_neurons; i++){
        acc = 0;
        for(int j = 0; j<this->number_of_neurons; j++){
            acc+=this->w[i][j]*this->neuron[j];
        }
        if(acc > 0){
            s_next[i] = 1;
        } else{
            s_next[i] = -1;
        }        
    }
    
    for(int i = 0; i<this->number_of_neurons; i++){
        this->neuron[i] = s_next[i];
    }
}

void HopfieldNetwork::train(){
    for(int i = 1; i<number_of_neurons; i++){
        for(int j = 0; j<i; j++){
            this->w[i][j] = pattern[i]*pattern[j];;
            this->w[j][i] = this->w[i][j];            
        }
    }
}

int main(){
    
    FILE* f = fopen("file", "r");

    int* img1 = (int*) std::malloc(24*32*sizeof(int));
    int* img2 = (int*) std::malloc(24*32*sizeof(int));
    
    for(int i = 0; i<32*24; i++){
        fread(&(img1[i]), 1, 1, f);
    }
    
    for(int i = 0; i<32*24; i++){
        fread(&(img2[i]), 1, 1, f);
    }
        
    int* pattern = (int*) std::malloc(32*24*8*sizeof(int));
    
    for(int i = 0; i<32*3; i++){
        for(int j = 7; j!=0; j--){
            pattern[8*i+j] = img1[8*i+j-7]%2;
            img1[8*i+j-7]/=2; 
        }
    }
    
    Window window(32*24);
    HopfieldNetwork hn(24*32*8, pattern);

    hn.writePattern();
    hn.train();
    
}