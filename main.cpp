#include <iostream>
#include <bits/stdc++.h>
#include "Graph.h"
#include "Readin.h"
#include "Algorithm.h"


using namespace std;




int main() {
    int from;
    int to;
    int k;
    int upper_bound;
    int lower_bound;
    std::vector<link> my_link;
    my_link.push_back(link());
    ReadIn readin;
    readin.read();
    my_link = readin.get_data();
    Graph my_graph;
    my_graph.initialize(my_link);
    my_graph.createGraph();
    std::cin >> from >> to;
    std::cin >> lower_bound >> upper_bound;
    // Dijkstra my_dij(my_graph);
    // my_dij.dijkstra(from, to);
    Pulse pul(my_graph);
    pul.set_start_and_end(from, to);
    pul.set_bound(lower_bound, upper_bound);
    pul.initialize();
    clock_t start;
    clock_t end;

    start = clock();
    pul.pulse_algorithm();
    end = clock();
    pul.print();
    std::cout << "Pulse time:   \033[33m" << double(end - start) / CLOCKS_PER_SEC * 1000 << "(ms)\033[0m" << endl;
}