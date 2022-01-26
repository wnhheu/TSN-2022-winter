#include <iostream>
#include <bits/stdc++.h>
#include "Graph.h"
#include "Readin.h"
#include "Algorithm.h"

using namespace std;

int main()
{
    int from;
    int to;
    double upper_bound;
    double lower_bound;
    std::vector<link> my_link;
    std::vector<tunnel> my_tunnel;
    my_link.push_back(link());
    ReadIn readin;
    readin.read();
    my_link = readin.get_link_data();
    my_tunnel = readin.get_tunnel_data();
    Graph my_graph;
    my_graph.initialize(my_link);
    my_graph.createGraph();
    std::cin >> from >> to;
    std::cin >> lower_bound >> upper_bound;
    // Dijkstra my_dij(my_graph);
    // // my_dij.dijkstra(from, to);
    // for (int i = 0; i < my_tunnel.size(); ++i)
    // {
        Pulse pul(my_graph);
        // from = my_tunnel[i].source_id;
        // to = my_tunnel[i].ter_id;
        // lower_bound = my_tunnel[i].min_delay;
        // upper_bound = my_tunnel[i].max_delay;
        pul.set_start_and_end(from, to);
        pul.set_bound(lower_bound, upper_bound);
        pul.initialize();
        clock_t start;
        clock_t end;
        start = clock();
        pul.pulse_algorithm();
        end = clock();
        pul.print();
        pul.clear();
        std::cout << "Pulse time:   \033[33m" << double(end - start) / CLOCKS_PER_SEC * 1000 << "(ms)\033[0m" << endl;
    // }
}
