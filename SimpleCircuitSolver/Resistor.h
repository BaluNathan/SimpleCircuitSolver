/* 
 * File:   Resistor.h
 * Author: balu
 *
 * Created on October 31, 2015, 9:34 PM
 */

#ifndef RESISTOR_H
#define	RESISTOR_H
#include <string>

using namespace std;

//RESISTOR CLASS HEADER FILE
//SEE Resistor.cpp FOR DETAILED FUNCTION DESCRIPTIONS

class Resistor {
    
    friend class NodeList;
    friend class ResistorList;
    friend class Node;
    
private:
    string name;
    double resistance;
    int endpoints[2];
    Resistor* next;
    
public:

    //**NOTE: this class has very limited getter/setter functions because of 
    //heavy usage of friend classes
    
    Resistor(string _name, double value, int node1, int node2);
    
    ~Resistor();
    

    string getName()const;
   
    void setRes(double value);
    double getRes()const;

    void print()const;
};

#endif	/* RESISTOR_H */

