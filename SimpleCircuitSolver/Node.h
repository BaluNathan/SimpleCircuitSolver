/* 
 * File:   Node.h
 * Author: balu
 *
 * Created on October 31, 2015, 9:35 PM
 */

#ifndef NODE_H
#define	NODE_H

#include "ResistorList.h"


class Node {
    
    friend class NodeList;
    friend class ResistorList;
    friend class Resistor;

private:
    int nodeID;
    double voltage;

    ResistorList* resList;

    Node* next;
    Node* prev;
    
    bool set;
  

public:

    //****SEE NODE.CPP FOR FUNCTION DESCRIPTIONS
    //NOTE** not all getters/setters were used due to heavy reliance on friend function
    //they are kept for modularity and ease of modification later


    Node(int _nodeID);


    ~Node();

    void setNodeID(int value);
    int getNodeID()const;

    void setVoltage(double value);
    double getVoltage()const;
    
    void unsetVoltage();

    void setNext(Node* _next);
    Node* getNext()const;

    void setPrev(Node* _prev);
    Node* getPrev()const;

    void setResList(int resist, int node1, int node2);
    ResistorList* getResList()const;
    
    void delResList();
    
    int resCount(const Node* const)const;
    
    void print()const;

};

#endif	/* NODE_H */

