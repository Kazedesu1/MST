//#include <iostream>
//#include "instance.h"
//#include "solver.h"
//
//int main() {
//	INSTANCE instance;
//	instance.loadFromFile("data/1.csv");
//	instance.displayData();
//	Prim prim(instance);
//	prim.solve();
//	prim.displaySolution();
//	Kruskal kruskal(instance);
//	kruskal.solve();
//	kruskal.displaySolution();
//	return 0;
//}

#include <iostream>
#include <fstream>
#include <chrono>
#include "instance.h"
#include "solver.h"

int main() {
    std::ofstream outputFile("MST.csv");
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file MST.csv" << std::endl;
        return 1;
    }

    // Print the header
    outputFile << "Filename,Obj,runtime\n";

    for (int i = 1; i <= 20; ++i) {
        std::string filename = "datanetwork200/network_nodes_" + std::to_string(i) + ".csv";
        INSTANCE instance;
        if (!instance.loadFromfilenetwork(filename)) {
            std::cerr << "Failed to load file: " << filename << std::endl;
            continue;
        }

        Kruskal kruskal(instance);
        kruskal.solve();
        kruskal.displaySolution();


        // Print the results
        outputFile << filename << "," << kruskal.total << "," << kruskal.runtime << "\n";
    }

    outputFile.close();
    return 0;
}