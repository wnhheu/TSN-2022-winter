#ifndef GRAPH_H
#define GRAPH_H
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

struct EdgeNode { //图用邻接表存储，这是邻接表中的边表节点，类中成员均为pulic,便于访问和修改
    
    EdgeNode(int ter_id = -1, int cost = -1) : ter_id(ter_id), cost(cost) { next = NULL; }

    EdgeNode(const link &oth);

    EdgeNode(const EdgeNode &oth);

    EdgeNode &operator=(const EdgeNode &oth);

    ~EdgeNode() {}

    int ter_id;
    int cost;
    int bandwidth;
    int delay;
    int srlgNum;
    int *srlgs;
    EdgeNode *next;
};

struct VertexNode { //邻接表中的顶点表节点，所有成员均为public
    VertexNode(int id = -1, EdgeNode *firstEdge = NULL) : id(id), firstEdge(firstEdge) {}
    int id;
    EdgeNode *firstEdge;
    ~VertexNode() {}
};

class Graph
{
private:
    const int node_num = 10000;

    VertexNode *vn;
    VertexNode *vnr;//正图、反图，用正向和反向的邻接表表示

    int link_size;

    std::vector<link> links;

    int *dis;//每个节点的dis值
public:
    Graph();

    Graph(const Graph &oth)
    {
        vn = new VertexNode [node_num];
        vnr = new VertexNode [node_num];
        dis = new int [node_num];
        for(int i = 0; i < node_num; ++i)
        {
            vn[i] = oth.vn[i];
            vnr[i] = oth.vnr[i];
            dis[i] = oth.dis[i];
        }
    }
    Graph operator=(const Graph &oth)
    {
        vn = new VertexNode [node_num];
        vnr = new VertexNode [node_num];
        dis = new int [node_num];
        for(int i = 0; i < node_num; ++i)
        {
            vn[i] = oth.vn[i];
            vnr[i] = oth.vnr[i];
            dis[i] = oth.dis[i];
        }
    }


    void initialize(std::vector<link> &my_link);

    int createGraph();  //构造图

    int node_size()
    {
        return node_num;
    }

    VertexNode *get_vn()
    {
        return vn;
    }

    VertexNode *get_vnr()
    {
        return vnr;
    }

    int *get_dis()
    {
        return dis;
    }
};

#endif