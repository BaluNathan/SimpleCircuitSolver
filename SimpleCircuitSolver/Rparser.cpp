
#include "Rparser.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <string.h>
//#define MAX_NODE_NUMBER  5000
using namespace std;

string removeTrailWhite(string line) {
    //fct to remove trailing whitespace

    //assign string var to all possible forms of whitespace: tab, return etc.
    string whitespace = " \n\t\r\f";

    //integer equal to the position of last character in line input from user that is NOT whitespace
    int strEnd = line.find_last_not_of(whitespace);

    //return substring of line that does not include whitespace using strEnd as last character 
    return (line.substr(0, strEnd + 1));
}

bool invalArg(stringstream* ssInput) {

    if ((*ssInput).fail()) {
        cout << "Error: invalid argument" << endl;
        return 1;
    }

    if (((*ssInput).peek() != ' ') && ((*ssInput).peek() != '\r') && ((*ssInput).peek() != '\n') && ((*ssInput).peek() != '\t') && (!(*ssInput).eof())) {
        cout << "Error: invalid argument" << endl;
        return 1;
    }

    return 0;

}

bool resistCheck(double resist) {
    if (resist < 0) {
        cout << "Error: negative resistance" << endl;
        return 1;
    }

    return 0;
}

bool tooFewArg(stringstream* ssInput) {
    if ((*ssInput).eof()) {
        cout << "Error: too few arguments" << endl;
        return 1;
    }

    return 0;
}

bool tooManyArg(stringstream* ssInput) {
    if (!(*ssInput).eof()) {
        cout << "Error: too many arguments" << endl;
        return 1;
    }
}

void insertR(stringstream* ssInput, string name, double resist, int node1, int node2, NodeList& network) {
    //read in first argument - name
    *ssInput >> name;

    //name = all is invalid
    if (name == "all") {
        cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
        return;
    }

    if (invalArg(ssInput)) return;

    //if eof flag detected after reading in name -> too few arguments
    if (tooFewArg(ssInput)) return;

    //read in second arg - resistor value
    *ssInput >> resist;

    if (invalArg(ssInput)) return;

    //account for invalid negative resistance error    
    if (resistCheck(resist)) return;

    //eof flag = too few args
    if (tooFewArg(ssInput)) return;

    //read in first node value
    *ssInput >> node1;

    if (invalArg(ssInput)) return;

    //check for eof
    if (tooFewArg(ssInput)) return;

    //read in node 2 value
    *ssInput >> node2;

    if (invalArg(ssInput)) return;

    //make sure node1 != node 2
    if (node1 == node2) {
        cout << "Error: both terminals of resistor connect to node " << node1 << endl;
        return;
    }

    //put node endpoints in array
    int endpoints[2] = {node1, node2};

    //check for extra args 
    if (tooManyArg(ssInput)) return;

    //check if resistor already exists
    if (network.getHead() != NULL) {

        if (network.resSearch(name)) {
            cout << "Error: resistor " << name << " already exists" << endl;
            return;
        }
    }

    //insert new nodes if not already existing & insert resistors in correct spots
    network.insertNode(node1)->getResList()->insertRes(resist, node1, node2, name);
    network.insertNode(node2)->getResList()->insertRes(resist, node1, node2, name);

    //output
    cout << "Inserted: resistor " << name << " " << fixed << setprecision(2) << resist << " Ohms " << node1 << " -> " << node2 << endl;
}

void modifyR(stringstream* ssInput, string name, double resist, NodeList& network) {
    //read in name
    *ssInput >> name;

    //same error checking for name arg as for insertR
    if (name == "all") {
        cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
        return;
    }

    if (invalArg(ssInput)) return;

    if (tooFewArg(ssInput)) return;

    //read in resistor value
    *ssInput >> resist;

    //error checks - same as insertR error checks for resistor arg        
    if (invalArg(ssInput)) return;

    if (resistCheck(resist)) return;

    if (tooManyArg(ssInput)) return;

    if (network.getHead() != NULL) {
        //make sure specified resistor exists
        if (network.resSearch(name) == NULL) {
            cout << "Error: resistor " << name << " not found" << endl;
            return;
        }

        //get old resistance value for output
        double temp = network.resSearch(name)->getRes();

        //change resistance value
        network.changeResVal(name, resist);

        //output
        cout << "Modified: resistor " << name << " from " << temp << " Ohms to " << resist << " Ohms" << endl;
        return;
    } else {
        //error  output
        cout << "Error: resistor " << name << " not found" << endl;
        return;
    }

}

void printR(stringstream* ssInput, string name, NodeList& network) {
    //read in name
    *ssInput>>name;

    //name error checking - same as insertR
    if (invalArg(ssInput)) return;

    if (tooManyArg(ssInput)) return;

    if (network.getHead() != NULL) {
        if (network.resSearch(name) == NULL) {
            cout << "Error: resistor " << name << " not found" << endl;
            return;
        } else {
            cout << "Print:" << endl;
            network.resSearch(name)->print();
        }
    } else {
        cout << "Error: resistor " << name << " not found" << endl;
        return;
    }
}

void deleteR(stringstream* ssInput, string name, NodeList& network) {
    //read in name
    *ssInput>>name;

    //error checking in name arg
    if (invalArg(ssInput)) return;

    if (tooManyArg(ssInput)) return;

    //delete all
    if (name == "all") {
        if (network.getHead() != NULL) network.delAll();
        cout << "Deleted: all resistors" << endl;
    } else {
        //check if specific resistor exists ~ if so delete it
        if ((network.getHead() == NULL) || (network.resSearch(name) == NULL)) {
            cout << "Error: resistor " << name << " not found" << endl;
        } else {
            network.delRes(name);
            network.delRes(name);
            cout << "Deleted: resistor " << name << endl;
        }        
    }
}

void printNode(stringstream* ssInput, string junk, int node1, NodeList& network) {

    //printNode must accept one arg of type int, but can also be keyword
    //'all' of type string - to check first init junk string and read in
    *ssInput>>junk;

    //check for random junk left in string stream 
    if (invalArg(ssInput)) return;

    //if not keyword all
    if (junk != "all") {

        //this means junk is either int or invalid string - to check
        //pump back into temp stringstream and read into var node1 (of
        //type int)
        stringstream temp(junk);
        temp>>node1;

        //error checking
        if (invalArg(&temp)) return;

        // if (nodeCheck(node1)) return;

        if (tooManyArg(ssInput)) return;

        //print out node info for give node
        cout << "Print:" << endl;
        if (network.findNode(node1) != NULL) {
            network.findNode(node1)->print();
        }
   
    } else {

        if (tooManyArg(ssInput)) return;

        //output - only triggers with keyword all
        //cycle through node list and print out node info for all nodes
        cout << "Print:" << endl;
        if (network.getHead() != NULL) {
            network.printAll();
        }
        return;
    }
}

void setV(stringstream* ssInput, int node1, NodeList& network) {
    
    //assumption is made that erroneous setV input will not be given
    //declare new double voltage and read in node number and voltage from 
    //input
    double voltage;

    *ssInput>>node1;
    *ssInput>>voltage;
    
    //find the correct node and set it to the right voltage
    if (network.getHead() != NULL) {
        if (network.findNode(node1) != NULL) {
            network.findNode(node1)->setVoltage(voltage);
        }
    } else network.insertNode(node1)->setVoltage(voltage); //if the specified node doesnt exist 
                                                            //make it and set voltage

    cout << "Set: node " << node1 << " to " << fixed << setprecision(2) << voltage << " Volts" << endl;
}

void unsetV(stringstream* ssInput, int node1, NodeList& network) {
    //read in node number -> assume always correct input
    *ssInput>>node1;
    
    //if the specified node exists, unset voltage
    if (network.getHead() != NULL) {
        if (network.findNode(node1) != NULL) {
            network.findNode(node1)->unsetVoltage();

        }
    }
    //regardless of voltage existence or not, output
    cout << "Unset: the solver will determine the voltage of node " << node1 << endl;
}

void solve(NodeList& network) {

    //if atleast one of the nodes have a set voltage, solve the circuit 
    if (network.anySetCheck()) {
        network.solve();
    } else {
        cout << "Error: no nodes have their voltage set" << endl;
        return;
    }


}

void parser(NodeList& network) {

    //initialize while loop - runs while cin is not empty
    while (!cin.eof()) {

        //initialize variables
        string line, cmd, name, junk;
        double resist;
        int node1, node2;

        //prompt user and  take input from keyboard
        cout << "> ";
        getline(cin, line, '\n');

        //identify and remove trailing whitespace in input - assign remaining
        //substring to new string - initialize string stream with fixed string
        stringstream ssInput(removeTrailWhite(line));

        //read in first command from string stream
        ssInput >> cmd;

        //address scenario in which user inputs valid command with no arguments
        if (ssInput.eof() && (cmd == "maxVal" || cmd == "insertR" || cmd == "modifyR" || cmd == "printR" || cmd == "printNode" || cmd == "deleteR")) { //doesnt work if there is space after command!!
            cout << "Error: too few arguments" << endl;
            continue;
        }

        //identify and parse command using if statement chain
        if (cmd == "setV") {
            setV(&ssInput, node1, network);

        } else if (cmd == "unsetV") {

            unsetV(&ssInput, node1, network);

        } else if (cmd == "solve") {

            solve(network);

        } else if (cmd == "insertR") {

            insertR(&ssInput, name, resist, node1, node2, network);


        } else if (cmd == "modifyR") {

            modifyR(&ssInput, name, resist, network);


        } else if (cmd == "printR") {

            printR(&ssInput, name, network);


        } else if (cmd == "deleteR") {

            deleteR(&ssInput, name, network);

        } else if (cmd == "printNode") {

            printNode(&ssInput, junk, node1, network);

        } else {

            //only triggers if command has typo or is wrong
            if (!cin.eof()) {
                cout << "Error: invalid command" << endl;
                continue;
            }
        }
    }//end while loop

}