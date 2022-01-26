#ifndef GRAPH_H
#define GRAPH_H
#include <bits/stdc++.h>
struct link
{
    int link_id;
    int source_id;
    int ter_id;
    int cost;
    int bandwidth;
    int delay;
    int srlgNum;
    int *srlgs;
    link()
    {
        link_id = -1;
        source_id = -1;
        ter_id = -1;
        cost = -1;
        bandwidth = -1;
        delay = -1;
        srlgNum = -1;
        srlgs = nullptr;
    }
};

struct EdgeNode
{ //图用邻接表存储，这是邻接表中的边表节点，类中成员均为pulic,便于访问和修改

    EdgeNode(int ter_id = -1, int cost = -1) : ter_id(ter_id), cost(cost) { next = nullptr; }

    EdgeNode(const link &oth)
    {
        next = nullptr;
        cost = oth.cost;
        ter_id = oth.ter_id;
        bandwidth = oth.bandwidth;
        delay = oth.delay;
        srlgNum = oth.srlgNum;
        srlgs = new int[srlgNum];
        for (int i = 0; i < srlgNum; ++i)
        {
            srlgs[i] = oth.srlgs[i];
        }
    }

    EdgeNode(const EdgeNode &oth)
    {
        next = oth.next;
        cost = oth.cost;
        ter_id = oth.ter_id;
        bandwidth = oth.bandwidth;
        delay = oth.delay;
        srlgNum = oth.srlgNum;
        srlgs = new int[srlgNum];
        for (int i = 0; i < srlgNum; ++i)
        {
            srlgs[i] = oth.srlgs[i];
        }
    }

    EdgeNode &operator=(const EdgeNode &oth)
    {
        next = oth.next;
        cost = oth.cost;
        ter_id = oth.ter_id;
        bandwidth = oth.bandwidth;
        delay = oth.delay;
        srlgNum = oth.srlgNum;
        srlgs = new int[srlgNum];
        for (int i = 0; i < srlgNum; ++i)
        {
            srlgs[i] = oth.srlgs[i];
        }
    }

    ~EdgeNode() 
    {
        delete srlgs;
    }

    int ter_id;
    int cost;
    int bandwidth;
    int delay;
    int srlgNum;
    int *srlgs;
    EdgeNode *next;
};

struct VertexNode
{ //邻接表中的顶点表节点，所有成员均为public
    VertexNode(int id = -1, EdgeNode *firstEdge = nullptr) : id(id), firstEdge(firstEdge) {}
    int id;
    EdgeNode *firstEdge;
    ~VertexNode() {}
};

class Graph
{
private:
    const int node_num = 2000;
    int num;
    VertexNode *vn;
    VertexNode *vnr; //正图、反图，用正向和反向的邻接表表示

    int link_size;

    std::vector<link> links;

    bool check_same_link(int start, int end, int cost, int delay)
    {

    }

public:
    Graph()
    {
        link_size = -1;
        vn = new VertexNode[node_num];
        vnr = new VertexNode[node_num];
        num = 0;
        // std::memset(delay, 0, sizeof delay);
    }

    Graph(const Graph &oth)
    {
        vn = new VertexNode[node_num];
        vnr = new VertexNode[node_num];
        num = oth.num;
        for (int i = 0; i < node_num; ++i)
        {
            vn[i] = oth.vn[i];
            vnr[i] = oth.vnr[i];
        }
    }
    Graph operator=(const Graph &oth)
    {
        vn = new VertexNode[node_num];
        vnr = new VertexNode[node_num];
        num = oth.num;
        for (int i = 0; i < node_num; ++i)
        {
            vn[i] = oth.vn[i];
            vnr[i] = oth.vnr[i];
        }
        return *this;
    }

    void initialize(std::vector<link> &my_link);

    int createGraph(); //构造图

    int node_size()
    {
        return num;
    }

    VertexNode *get_vn()
    {
        return vn;
    }

    VertexNode *get_vnr()
    {
        return vnr;
    }

    // int *get_delay()
    // {
    //     return delay;
    // }
};

#endif