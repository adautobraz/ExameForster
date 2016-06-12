#ifndef CIRCUIT_H
#define CIRCUIT_H
#include "Circuit.h"
#include "LogicGates.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct Signals{
    string name = "sinal generico";
    int value = -1;
};

class Circuit
{
    public:
        Circuit();
        virtual ~Circuit();
        int solveCircuit(string F, vector<Signals> inputs);

    protected:

    private:
        vector<Signals> S;
        int findSignal(string name);
        int solveLogicGate(int x1, int x2, string gate);
};

#endif // CIRCUIT_H
