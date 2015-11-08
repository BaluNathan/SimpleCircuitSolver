/* 
 * File:   Node.cpp
 * Author: balu
 * 
 * Created on October 31, 2015, 9:35 PM
 */

#include "Node.h"
#include "ResistorList.h"
#include <iomanip>
#include <iostream>


//constructor
Node::Node(int _nodeID) {
    this->nodeID = _nodeID;
    this->next = NULL;
    this->prev = NULL;
    this->resList = new ResistorList;
    this->set = false;
    this->voltage = 0.00;
}

//destructor -> deletes resistor list of current node
Node::~Node() {
    delete (this->resList);    
}

//getters and setters for various values in the class

void Node::setNodeID(int value) {
    this->nodeID = value;
}

int Node::getNodeID()const {
    return (this->nodeID);
}

void Node::setVoltage(double value) {
    this->voltage = value;
    this->set = true;
}

void Node::unsetVoltage() {
    this->voltage = 0;
    this->set = false;
}

double Node::getVoltage()const {
    return (this->voltage);
}

void Node::setNext(Node* _next) {
    this->next = _next;
}

Node* Node::getNext()const {
    return (this->next);
}

void Node::setPrev(Node* _prev) {
    this->prev = _prev;
}

Node* Node::getPrev()const {
    return (this->prev);
}

ResistorList* Node::getResList()const {// do i need this?
    return resList;
}

//delete res list in node
void Node::delResList() {
    Resistor* p;
    //ResistorList* q;
    while (this->resList->head!=NULL){
        p=this->resList->head;
        this->resList->head = p->next;
        p->next = NULL;
        delete p;
    }
}

//return count of number of resistors in node
int Node::resCount(const Node*)const {
    Resistor* p = this->resList->head;
    int count = 0;
    while (p != NULL) {
        count++;
        p = p->next;
    }

    return count;

}
//print current node 
void Node::print()const {
    if (this->resList->head != NULL) {
        cout << "Connections at node " << this->nodeID << ": " << resCount(this) << " resistor(s)" << endl;
        Resistor* p = resList->head;
        while (p != NULL) {
            cout << "  ";
            p->print();
            p = p->next;
        }
        return;
    }
    else if(this->set){
        cout << "Connections at node " << this->nodeID << ": " << fixed << setprecision(2) << this->voltage << " V" << endl;
        return;
    }
    else return;
}
