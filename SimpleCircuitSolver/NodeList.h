/* 
 * File:   NodeList.h
 * Author: balu
 *
 * Created on October 31, 2015, 9:36 PM
 */

#ifndef NODELIST_H
#define	NODELIST_H

#include "Node.h"

#include <string>
using namespace std;

//Node list class header file

//SEE NodeList.cpp FOR FUNCTION DESCRIPTIONS

class NodeList {
    
    friend class ResistorList;
    friend class Node;
    friend class Resistor;  
    
private:
   
    Node* head; 

public:
    NodeList();
    ~NodeList();
    
    Node* getHead()const;
    
    Node* findNode(int value);
    Node* insertNode(int value); //find or insert
    
    bool resCheck(string _name);
    
    void changeResVal(string _name, double value);
    
    Resistor* resSearch(string _name);
    
    void delRes(string _name);
    
    void delAll();
    
    void printAll()const;
    
    void setV(int node1, double _voltage);
    
    void unsetV(int node1);
    
    bool anySetCheck()const;
    
    void solve();
};

#endif	/* NODELIST_H */

