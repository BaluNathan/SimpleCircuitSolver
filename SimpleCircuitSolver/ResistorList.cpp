/* 
 * File:   ResistorList.cpp
 * Author: balu
 * 
 * Created on October 31, 2015, 9:36 PM
 */

#include "ResistorList.h"
#include "Resistor.h"
#include "Node.h"
#include <string>
#include <iostream>

//constructor sets head to null
ResistorList::ResistorList() {
    this->head = NULL;
}

//deconstructor - deletes all resistors in list
ResistorList::~ResistorList() {
    Resistor* p;
    while (this->head != NULL) {
        p = this->head;
        this->head = p->next;
        p->next = NULL;
        delete p;
    }
}

//insert resistor into correct spot
void ResistorList::insertRes(double resistance, int node1, int node2, string name) {
    Resistor* n = new Resistor(name, resistance, node1, node2);
    Resistor* p = head;
    Resistor* prev = NULL;
    while (p != NULL) {
        prev = p;
        p = p->next;
    }
    n->next = p;
    if (prev == NULL) head = n;
    else prev->next = n;

}

//find resistor in list
Resistor* ResistorList::findRes(string _name) {
    Resistor* p = this->head;
    while (p != NULL) {
        if (p->name == _name) return p;
        p = p->next;
    }
    return p;
}

//delete resistor in list -> return bool for confirmation
bool ResistorList::delRes(string _name) {
    Resistor* p = head;
    Resistor* prev = NULL;
    while (p != NULL && p->name != _name) {
        prev = p;
        p = p->next;
    }

    if (p == NULL) return false;
    if (prev == NULL) head = p->next;
    else {
        prev->next = p->next;
        p->next = NULL;

    }

    delete p;
    p = NULL;
    return true;
}

//calculate R equivalent -> second term in equation 3 from lab document
void ResistorList::calculate(double& rEq) {
    rEq = 0;
    Resistor* p = head;
    while (p != NULL) {
        rEq += (1 / (p->resistance));
        p = p->next;
    }
    
    rEq=(1/rEq);

    return;
}

