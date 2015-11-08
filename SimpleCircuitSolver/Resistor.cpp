/* 
 * File:   Resistor.cpp
 * Author: balu
 * 
 * Created on October 31, 2015, 9:34 PM
 */

#include "Resistor.h"
#include <string>
#include <iostream>
#include <iomanip>

//constructor
Resistor::Resistor(string _name, double value, int node1, int node2) {
    this->next = NULL;    
    this->name = _name;
    this->resistance = value;
    this->endpoints[0] = node1;
    this->endpoints[1]= node2;
    
}

//destructor
Resistor::~Resistor() {

}

//name getter
string Resistor::getName()const {
    return(this->name);
}

//resistance setter
void Resistor::setRes(double value) {
    this->resistance= value;
}

//resistance getter
double Resistor::getRes()const {
    return(this->resistance);
}

//print resistor
void Resistor::print()const{
    cout << setfill(' ') << setw(20) << left << name;
    cout<< setw(8) << right << fixed << setprecision(2) << resistance;
    cout<< " Ohms " << endpoints[0] << " -> " << endpoints[1] << endl;
}