#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "Graph.h"
#include <bits/stdc++.h>

using namespace std;

class Algorithm
{
protected:
    Graph graph;
};

class Dijkstra : public Algorithm
{
public:
    Dijkstra(const Graph &oth)
    {
        graph = oth;
    }

    bool dijkstra(int source_id, int ter_id); //dijkstra 求解delay值
};

class Astar : public Algorithm
{
public:
    Astar(const Graph &oth)
    {
        graph = oth;
    }

    bool astar(int source_id, int ter_id, int k); //A star 求解K短路
};

class Pulse : public Algorithm
{
private:
    struct node
    {
        int id;
        int dis;
        friend bool operator<(const node &a, const node &b)
        {
            return a.dis < b.dis;
        }
        friend bool operator>(const node &a, const node &b)
        {
            return a.dis > b.dis;
        }
        node(int id = 0, int dis = 0) : id(id), dis(dis) {}
    };

    struct pulse_info
    {
        // set capacity
        std::vector<int> mini_cost;
        std::vector<int> mini_delay;
        std::vector<int> random_rep;
        int mini_cost_cost;
        int mini_cost_delay;
        int mini_delay_cost;
        int mini_delay_delay;
        int random_rep_cost;
        int random_rep_delay;
        pulse_info()
        {
            mini_cost_cost = INT32_MAX;
            mini_cost_delay = INT32_MAX;
            mini_delay_cost = INT32_MAX;
            mini_delay_delay = INT32_MAX;
            random_rep_cost = INT32_MAX;
            random_rep_delay = INT32_MAX;
        }
    };

    int dis[2000];
    int cost_map[2000];
    int delay_map[2000];
    bool *visited;
    int num;
    int start;
    int end;
    int t = 0;
    int lower_bound;
    int upper_bound;
    int total_cost;
    pulse_info info[2000];
    std::priority_queue<node, std::vector<node>, greater<node>> heap;

    bool check(int u, int cost, int delay);

    bool update(int u, int *path, int &cnt, double p, int cost, int delay);

public:
    Pulse(const Graph &oth)
    {
        graph = oth;
        num = graph.node_size();
        // dis = new int [num];
        visited = new bool[num];
        start = -1;
        end = -1;
        lower_bound = -1;
        upper_bound = -1;
        total_cost = INT32_MAX;
        for (int i = 0; i < num; ++i)
            dis[i] = INT32_MAX;
        for (int i = 0; i < num; ++i)
            visited[i] = false;
    }

    void dijkstra(int s, int t, bool flag);

    void set_start_and_end(int s, int t)
    {
        start = s;
        end = t;
    }

    void set_bound(int l, int u)
    {
        lower_bound = l;
        upper_bound = u;
    }

    void initialize();

    void dfs(int u, int *path, int &cnt, int cost, int delay);

    void pulse_algorithm();

    void print();

};

#endif