#pragma once
#ifndef SOLVER_H
#define SOLVER_H
#include "instance.h"
#include <vector>
#include <set>

class Prim {
public:
    Prim(const INSTANCE& instance);
    void solve();
    void displaySolution() const;
    double runtime;
    double total = 0;

    INSTANCE instance;
    std::vector<Edge> mstree;
};

class Kruskal {
public:
    Kruskal(const INSTANCE& instance);
    void solve();
    void displaySolution() const;
    double runtime;
    double total = 0;
    int find(vector<int>& parent, int i) const;
    void unionSet(vector<int>& parent, vector<int>& rank, int x, int y) const;
    const INSTANCE& instance;
    std::vector<Edge> mstree;
};

#endif // SOLVER_H