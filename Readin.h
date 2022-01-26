#ifndef READIN_H
#define READIN_H
#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

class ReadIn
{
private:
    std::vector<link> links;

    std::vector<tunnel> tunnels;

    void split_topo(std::vector<link> &links, std::string &line);

    void split_tunnel(std::vector<link> &links, std::string &line);

    void read_topo();

    void read_tunnel();

public:

    std::vector<link> &get_link_data()
    {
        return links;
    }

        std::vector<tunnel> &get_tunnel_data()
    {
        return tunnels;
    }

    void read()
    {
        read_topo();
        read_tunnel();
    }
};

#endif
