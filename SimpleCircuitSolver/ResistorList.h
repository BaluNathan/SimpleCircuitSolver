/* 
 * File:   ResistorList.h
 * Author: balu
 *
 * Created on October 31, 2015, 9:36 PM
 */

#ifndef RESISTORLIST_H
#define	RESISTORLIST_H

#include <string>

#include "Resistor.h"


//RESISTOR LIST CLASS -> SEE ResistorList.cpp FOR FUNCTION DESCRIPTIONS


class ResistorList {
    
    friend class NodeList;
    friend class Node;
    friend class Resistor;
    
private:
    Resistor* head;

public:
    ResistorList();
    ~ResistorList();

    void insertRes(double resistance, int node1, int node2, string name);

    Resistor* findRes(string _name);

   bool delRes(string _name);
   void calculate(double& rEq);


};

#endif	/* RESISTORLIST_H */

