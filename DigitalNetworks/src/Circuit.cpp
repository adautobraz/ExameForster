#include "Circuit.h"
#include "LogicGates.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>

Circuit::Circuit()
{
    //ctor
}

Circuit::~Circuit()
{
    //dtor
}

int Circuit::findSignal(string name){
    int result=-1;
    for(int i=0; i<S.size();i++){
        if(S[i].name == name)
            result = S[i].value;
    }
    return result;
}


 int Circuit::solveLogicGate(int x1, int x2, string gate){
    vector<int> sinais;
    int value;
    sinais.push_back(x1);
    if(gate == "or"){
        sinais.push_back(x2);
        LogicGates logicGate(LOGIC_GATE::OR, 2);
        value = logicGate.solve(sinais);
    }
    else if(gate == "not"){
        LogicGates logicGate(LOGIC_GATE::NOT);
        value = logicGate.solve(sinais);
    }
    else if(gate == "and"){
        sinais.push_back(x2);
        LogicGates logicGate(LOGIC_GATE::AND, 2);
        value = logicGate.solve(sinais);
    }
    else if(gate == "nand"){
        sinais.push_back(x2);
        LogicGates logicGate(LOGIC_GATE::NAND, 2);
        value = logicGate.solve(sinais);
    }
    if(gate == "nor"){
        sinais.push_back(x2);
        LogicGates logicGate(LOGIC_GATE::NOR, 2);
        value = logicGate.solve(sinais);
    }
    return value;
}


int Circuit::solveCircuit(string F, vector<Signals> inputs){

    //Ler a string
    string buf; // Have a buffer string
    stringstream ss(F); // Insert the string into a stream
    vector<string> bool_func; // Create vector to hold our words
    stack <Signals> P;
    S = inputs;
    int result=-1;

    while (ss >> buf)
        bool_func.push_back(buf);
    //cout<< bool_func.size() <<endl;
    for(int i=0; i<bool_func.size();i++){
        if(bool_func[i] == ")"){
            Signals in1, in2, gate;
            in1 = P.top();
            //cout<< in1.name << " " << in1.value  << endl;
            P.pop();
            if(!P.empty()){
                gate = P.top();
                //cout<< gate.name << " " << gate.value  << endl;
                P.pop();
                if(gate.name!="not"){
                    in2 = P.top();
                    //cout<< in2.name << " " << in2.value  << endl;
                    P.pop();
                }
                gate.value = solveLogicGate(in1.value,in2.value,gate.name);
                if(P.empty())
                     result = gate.value;
                P.push(gate);
            }
            else
                result = in1.value;
        }
        else if (bool_func[i] != "("){
            //cout << bool_func[i] <<endl;
            Signals j;
            j.name = bool_func[i];
            j.value = findSignal(j.name);
            P.push(j);
        }
    }
    return result;
}
