#include "instance.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

bool INSTANCE::loadFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }

    string line;

    file >> numnodes;
    file.ignore();  


    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);
        Edge e;
        char comma;  

        if (ss >> e.node1 >> comma >> e.node2 >> comma >> e.weight) {
            if (comma == ',') {  
                edges.push_back(e);
            }
        }
 
    }

	for (int i = 0; i < numnodes; i++)
	{
		nodes.push_back(i);
	}

    return true;
}

void INSTANCE::displayData()
{
    cout << "Number of nodes: " << numnodes << endl;
    cout << "Edges:" << endl;

    for (const Edge& e : edges)
    {
        cout << e.node1 << " " << e.node2 << " " << e.weight << endl;
    }
}

