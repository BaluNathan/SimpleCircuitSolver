/* 
 * File:   Rparser.h
 * Author: balu
 *
 * Created on October 10, 2015, 3:56 PM
 */

#ifndef RPARSER_H
#define	RPARSER_H

#include "Node.h"
#include "Resistor.h"
#include "NodeList.h"
#include "ResistorList.h"

#include <sstream>
#include <string>
#include <string.h>
#include <iostream>

using namespace std;

//function prototypes for Rparser -> see Rparser.cpp for detailed function descriptions

string removeTrailWhite(string line);

bool invalArg(stringstream* ssInput);
bool resistCheck(double resist);
bool tooFewArg(stringstream* ssInput);
bool tooManyArg(stringstream* ssInput);

void insertR(stringstream* ssInput, string name, double resist, int node1, int node2, NodeList& network);
void modifyR(stringstream* ssInput, string name, double resist, NodeList& network);
void printR(stringstream* ssInput, string name, NodeList& network);
void deleteR(stringstream* ssInput, string name, NodeList& network);
void printNode(stringstream* ssInput, string junk, int node1, NodeList& network);
void setV(stringstream* ssInput, int node1, NodeList& network);
void unsetV(stringstream* ssInput, int node1, NodeList& network);
void solve(NodeList& network);

void parser(NodeList& network);



#endif	/* RPARSER_H */

