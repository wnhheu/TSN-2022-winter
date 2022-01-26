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

    bool dijkstra(double source_id, double ter_id); //dijkstra 求解delay值
};

class Astar : public Algorithm
{
public:
    Astar(const Graph &oth)
    {
        graph = oth;
    }

    bool astar(double source_id, double ter_id, double k); //A star 求解K短路
};

class Pulse : public Algorithm
{
private:
    struct node
    {
        double id;
        double dis;
        friend bool operator<(const node &a, const node &b)
        {
            return a.dis < b.dis;
        }
        friend bool operator>(const node &a, const node &b)
        {
            return a.dis > b.dis;
        }
        node(double id = 0, double dis = 0) : id(id), dis(dis) {}
    };

    struct Path
    {
        std::vector<int> path_info;
        double cost;
        double delay;
        Path()
        {
            cost = 1000000;
            delay = 1000000;
            path_info.reserve(50);
        }

        void clear()
        {
            path_info.clear();
        }

        void push_back(double x)
        {
            path_info.push_back(x);
        }

        double size()
        {
            return path_info.size();
        }

        friend bool operator<(const Path &a, const Path &b)
        {
            return a.cost < b.cost;
        }
        friend bool operator>(const Path &a, const Path &b)
        {
            return a.cost > b.cost;
        }
    };

    struct pulse_info
    {
        // set capacity
        Path mini_cost;
        Path mini_delay;
        Path random_rep;
        double maxi_delay;
        pulse_info()
        {
            maxi_delay = 1000000;
        }
        void clear()
        {
            mini_cost.clear();
            mini_delay.clear();
            random_rep.clear();
            maxi_delay = 1000000;
        }
    };

    double dis[5000];
    double cost_map[5000];
    double delay_map[5000];
    bool *visited;
    int num;
    int start;
    int end;
    double t = 0;
    double lower_bound;
    double upper_bound;
    double total_cost;
    double quo;
    std::vector<Path> res;
    pulse_info info[5000];
    std::priority_queue<node, std::vector<node>, greater<node>> heap;

    bool check(int u, double cost, double delay);

    bool update(int u, int *path, int &cnt, double p, double cost, double delay);

    static bool Compare(Path a, Path b)
    {
        return a.cost < b.cost;
    }

    void update_delay_info();

public:
    Pulse(const Graph &oth)
    {
        graph = oth;
        num = graph.node_size();
        // dis = new double [num];
        visited = new bool[num];
        start = -1;
        end = -1;
        lower_bound = -1;
        upper_bound = -1;
        total_cost = 1000000;
        quo = 0.8;
        for (int i = 0; i < num; ++i)
        {
            dis[i] = 1000000;
            visited[i] = false;
        }
            
    }

    void dijkstra(int s, int t, bool flag);

    void set_start_and_end(double s, double t)
    {
        start = s;
        end = t;
    }

    void clear();

    void set_bound(double l, double u)
    {
        lower_bound = l;
        upper_bound = u;
    }

    void initialize();

    double dfs(int u, int *path, int &cnt, double cost, double delay);

    void pulse_algorithm();

    void print();
};

#endif