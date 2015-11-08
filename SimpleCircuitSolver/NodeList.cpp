/* 
 * File:   NodeList.cpp
 * Author: balu
 * 
 * Created on October 31, 2015, 9:36 PM
 */

#define MIN_ITERATION_CHANGE 0.0001
#include "NodeList.h"
#include "Node.h"
#include "ResistorList.h"
#include "Resistor.h"
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

//node list constructor -> sets head to null
NodeList::NodeList() {
    this->head = NULL;
}

//node list deconstructor -> deletes all nodes
//and within nodes, deconstructors delete all resistor lists
NodeList::~NodeList() {
    Node* p;
    while (this->head != NULL) {
        p = this->head;
        this->head = p->next;
        p->next = NULL;
        delete p;
        p = NULL; 
    }
}

//getter for list head
Node* NodeList::getHead()const {
    return head;
}

//find node function searches through node list for node with specified number
//returns pointer to it
Node* NodeList::findNode(int value) {
    Node* p = this->head;
    while (p != NULL) {
        if (p->nodeID == value) return p;
        if (p->nodeID > value) return NULL;
        p = p->next;
    }
    return p;
}

//insert node function
Node* NodeList::insertNode(int value) {
    //use find node to check if node already exists
    //if not, insert
    //in either case, return pointer to specified node
    if (findNode(value) == NULL) {
        Node* n = new Node(value);
        Node* p = head;
        Node* prev = NULL;
        while (p != NULL && p->nodeID < value) {
            prev = p;
            p = p->next;
        }
        n->next = p;
        if (prev == NULL) head = n;
        else prev->next = n;
        n->prev = prev;
        return n;
    } else return (findNode(value));
}

//search for resistors in the entire node list, return pointer to it 
//if found
Resistor* NodeList::resSearch(string _name) {
    Node* p = head;
    Resistor* q;
    while (p != NULL) {
        q = p->resList->findRes(_name);
        if (q != NULL) {
            return q;
        }
        p = p->next;
    }

    return q;
}

//change value of specified resistor, return bool if completed successfully
void NodeList::changeResVal(string _name, double value) {
    Node* p = head;
    while (p != NULL) {
        Resistor* q = p->resList->findRes(_name);
        while (q != NULL) {
            if (q->getName() == _name) {
                q->setRes(value);
                break;
            }
        }
        p = p->next;
    }

}

//delete specified resistor
void NodeList::delRes(string _name) {

    Node* p = head;
    bool isDel = false;
    while (!isDel) {
        isDel = p->resList->delRes(_name);
        if (!isDel) p = p->next;
    }

}

//delete all resistors in all nodes
void NodeList::delAll() {
    Node* p = head;
    while (p != NULL) {
        p->delResList();
        p = p->next;
    }
    return;
}

//print all nodes
void NodeList::printAll()const {
    Node* p = head;
    while (p != NULL) {
        p->print();
        p = p->next;
    }
}

//set voltage for specified node
void NodeList::setV(int node1, double _voltage) {
    findNode(node1)->setVoltage(_voltage);
}

//unset voltage for specified node
void NodeList::unsetV(int node1) {
    findNode(node1)->unsetVoltage();
}

//check if atleast one node has a set voltage
bool NodeList::anySetCheck()const {
    Node* p = head;
    while (p != NULL) {
        if (p->set) return true;
        else p = p->next;
    }
}

//solve algorithm
void NodeList::solve() {
    bool done = false; //flag to see if iterations are done
    bool nodeChange = false; //flag to see if iteration for one specific node
    while (!done) {
        Node* p = this->head; //pointer to node list head
        while (p != NULL) { 
            if (!(p->set) && p->resList->head != NULL) { //make sure that the current node does not have a set voltage
                                                         // and contains resistors
                double termA = 0;//term 1 for the voltage calculation (from lab 4 equation 3)
                double termB = 0;//term 2 for same equation
                double vOld = p->voltage; // holder for old voltage -> for iteration change calculation
                
                p->resList->calculate(termA);//calculate term A, R equivalent

                Resistor* q = p->resList->head;//pointer to first resistor in current node's resistor list
                while (q != NULL) {
                    int nodeNeeded; //variable to the hold the node from which we need voltage
                    if (q->endpoints[0] == p->nodeID) { // the if block checks which of the resistor's
                        nodeNeeded = q->endpoints[1];  //endpoints is the one that we need
                    } else {
                        nodeNeeded = q->endpoints[0];
                    }
                    //add one V/R term to term B
                    termB += (this->findNode(nodeNeeded)->voltage)/(q->resistance);
                   
                    //move to next resistor
                    q = q->next;
                }
                
                //once all resistors are cycled through, you have values for 
                //term A and term B -> calculate the voltage
                p->voltage = (termA * termB);
                          
                //check if the voltage change is less than the min iteration change
                if (abs(vOld - (termA*termB))  <= MIN_ITERATION_CHANGE) nodeChange = true;
                else nodeChange = false;
            }
            p = p->next;//go to next node
        }
        if (nodeChange) done = true; //nodechange will only be true, if every single node voltage change was within min iteration range
    }
    
    //print output in specified format
    cout << "Solve:" << endl;
    Node* r = head;
    while (r != NULL) {
        if (r->resList->head != NULL) cout << "Node " << r->nodeID << ": " << r->voltage << " V" << endl;
        r = r->next;
    }
    return;
}

