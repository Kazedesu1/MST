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
    int node1, node2, weight;
};
class INSTANCE
{
public:
    vector<Edge> edges;
	vector<int> nodes;
    int numnodes;
    bool loadFromFile(const std::string& filename = "data/1.csv");
    void displayData();
};
