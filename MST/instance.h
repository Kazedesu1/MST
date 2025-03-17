#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
struct Edge
{
    int node1, node2;
    double weight;
};
class INSTANCE
{
public:
    vector<Edge> edges;
	vector<int> nodes;
    int numnodes;
    bool loadFromFile(const std::string& filename = "data300/mst_instance_0.csv");
    void displayData();
	bool loadFromfilenetwork(const std::string& filename = "datanetwork200/network_nodes_1.csv");
};

