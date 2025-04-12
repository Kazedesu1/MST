#include "instance.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

static double manhattanDistance(double x1, double y1, double x2, double y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool INSTANCE::loadFromfilenetwork(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }

    string line;
    getline(file, line); // Bỏ qua dòng tiêu đề

    vector<pair<double, double>> coordinates; // Lưu tọa độ các node

    while (getline(file, line))
    {
        stringstream ss(line);
        int nodeID;
        double x, y;
        char comma;

        if (ss >> nodeID >> comma >> x >> comma >> y) {
            if (comma == ',') {
                nodes.push_back(nodeID);
                coordinates.push_back({ x, y });
            }
        }
    }
    file.close();

    numnodes = nodes.size();

    // Tính khoảng cách Euclidean giữa mọi cặp node
    for (size_t i = 0; i < coordinates.size(); i++) {
        for (size_t j = i + 1; j < coordinates.size(); j++) {
            double weight = manhattanDistance(coordinates[i].first, coordinates[i].second,
                coordinates[j].first, coordinates[j].second);
            edges.push_back({ nodes[i], nodes[j], weight });
        }
    }

    return true;
}

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

