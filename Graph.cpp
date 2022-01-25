#include "Graph.h"
void Graph::initialize(std::vector<link> &my_link)
{
    links = my_link;
    link_size = links.size();
}

int Graph::createGraph() { //构造图
    int source_id, ter_id;
    int tmp[2000];
    for(int i = 0; i < 2000; ++i)
        tmp[i] = 0;
    int cost;
    for (int i = 0; i < link_size; i++) {
        source_id = links[i].source_id;
        ter_id = links[i].ter_id;
        if(source_id == 766 || ter_id == 766)
            int x = 0;
        ++tmp[source_id];
        ++tmp[ter_id];
        cost = links[i].cost;
        if (vn[source_id].id == -1) vn[source_id].id = source_id;
        if (vn[ter_id].id == 'Z') vn[ter_id].id = ter_id;
        EdgeNode *edge_new = new EdgeNode(links[i]);
        edge_new->ter_id = links[i].ter_id;
        EdgeNode *p = vn[source_id].firstEdge;
        edge_new->next = nullptr;
        if (vn[source_id].firstEdge == nullptr) {
            vn[source_id].firstEdge = edge_new;
        } else {
            while (p->next != NULL)
                p = p->next;
            p->next = edge_new;//一个边有两个边表节点， 添加第一个边表节点

        }
        EdgeNode *edge_new2 = new EdgeNode(links[i]);
        edge_new2->ter_id = source_id;
        edge_new2->next = nullptr;
        p = vn[ter_id].firstEdge;
        if (vn[ter_id].firstEdge == nullptr)
            vn[ter_id].firstEdge = edge_new2;
        else {
            while (p->next != NULL)
                p = p->next;
            p->next = edge_new2;//一条边有两个边表节点，添加第二个边表节点
        }
    }

    for(int i = 0; i < 2000; ++i)
    {
        if(tmp[i] != 0)
            ++num;
    }

    for (int i = 0; i < node_num; i++) //无向图的复制
        vnr[i] = vn[i];

    return 1;
}
