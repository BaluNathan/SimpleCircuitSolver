/* 
 * File:   main.cpp
 * Author: balu
 *
 * Created on October 10, 2015, 10:31 AM
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <sstream>
#include "Rparser.h"


using namespace std;


int main(int argc, char** argv) {
    
    //initialize node list
    NodeList network;
   
    //call parser function - all functionality contained within
    //parser.cpp
    parser(network);
   
    
    return (0);
}

