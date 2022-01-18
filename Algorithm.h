#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "Graph.h"
#include <bits/stdc++.h>
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

    bool dijkstra(int source_id, int ter_id) //dijkstra 求解dis值
    {
//V为顶点集，S为已求得最短距离的点的集合，T为余下点的集合，初始时，S={},T=V,T用带pair的vector实现，当T为空时，代表所有点均以到达集合S中，算法结束，当一个节点从集合T中迁移至S中时，这个顶点对应的距离值便是此节点到起点的最短距离值。
        long max = 1e8;
        VertexNode *vn = graph.get_vn();
        VertexNode *vnr = graph.get_vnr();
        int *dis = graph.get_dis();
        int parent[graph.node_size()];//更新时记录每个节点的父节点，只有这个距离更新，此节点的父>节点才会更新
        for (int i = 0; i < graph.node_size(); i++)
            parent[i] = -1;
        vector<pair<int, int>> queue;//不是优先级队列,第一个代表距离，第二个代表节点
        for (int i = 0; i < graph.node_size(); i++) {
            if (vnr[i].id != -1) {
                if (vnr[i].id == ter_id)
                    queue.push_back(make_pair(0, vnr[i].id));//起点的距离值为0
                else
                    queue.push_back(make_pair(max, vnr[i].id));//初始化其他点的距离>为max
            }
        }

        vector<pair<int, int>>::iterator it = queue.begin();
        while (!queue.empty()) {
            sort(queue.begin(), queue.end());//对剩余节点进行排序
            vector<pair<int, int>>::iterator tmp = queue.begin();
            if (dis[queue.begin()->second] > queue.begin()->first)
                dis[queue.begin()->second] = queue.begin()->first;//队首的距离值为最短的，而且要出队
            EdgeNode *p = vnr[tmp->second].firstEdge;
            int d = tmp->first;//存储此节点出队的距离值
            while (p != NULL) {

                for (it = queue.begin() + 1; it != queue.end(); it++) {
                    if (p->ter_id == it->second)//在T中找到要更新的点
                    {
                        if (d + p->cost < it->first) { //需要更新,相等的话则不再更新,相等代表距离一样，但经过的顶点更多
                            it->first = d + p->cost;
                            parent[it->second] = tmp->second; //更>新父节点
                        }

                        break;
                    }
                }
                p = p->next;
            }
            queue.erase(queue.begin());//删除起始节点
        }
    }

};

class Astar : public Algorithm
{
public:
    Astar(const Graph &oth)
    {
        graph = oth;
    }

    bool astar(int source_id, int ter_id, int k)//A star 求解K短路
    {
        VertexNode *vn = graph.get_vn();
        VertexNode *vnr = graph.get_vnr();
        int *dis = graph.get_dis();
        if (vn[source_id].id == -1) {
            cout << "node doesn't exist" << endl;
            return 0;
        }
        int count = 0;//终点出现次数
        int i = 1, loc = 1;    //步数
        int fx[10000], gx[10000], hx[10000];//A star中的函数值,即扩展的节点序列，暂定10000
        int node[10000];             //存储节个序列中实际对应的每个节点
        int parent[10000];           //每个序列的父节点
        for (int i = 0; i < 10000; i++) {
            fx[i] = 0;
            gx[i] = 0;
            hx[i] = 0;
            node[i] = -1;
            parent[i] = 0;
        }
//添加父节点
        priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, greater<pair<pair<int, int>, int>>> q; //优先级队列，第一个int存储的是fx值，第二个存储的是gx值，第三个存储的是扩展的节点序列，满足当fx值相等时，则选择fx较小的
        gx[1] = 0;
        hx[1] = dis[source_id];
        node[1] = source_id;//先将起点入队
        fx[1] = gx[1] + hx[1];
        parent[0] = -1;  //便于沿着父节点数组一直找到起点
        parent[1] = 0;
        q.push(make_pair(make_pair(fx[1], gx[1]), 1));
        while (!q.empty()) {
            pair<pair<int, int>, int> tmp = q.top();
            q.pop();
            if (node[tmp.second] == ter_id) {//找到终点
                vector<int> vec;
                // 用vector存储此条路径
                int now = tmp.second;
                while (parent[now] != -1) {
                    vec.push_back(node[now]);//节点存入vector
                    now = parent[now];//找到父节点
                }
                EdgeNode *p = vn[node[tmp.second]].firstEdge;
                while (p != NULL) //将子女节点入队
                {
                    ++loc;
                    gx[loc] = gx[tmp.second] + p->cost;
                    node[loc] = p->ter_id;
                    parent[loc] = tmp.second;
                    hx[loc] = dis[p->ter_id];
                    fx[loc] = gx[loc] + hx[loc];
                    q.push(make_pair(make_pair(fx[loc], gx[loc]), loc));
                    p = p->next;

                }
                count++;
                if (count == k) {
                    vector<int>::iterator it = vec.end() - 1;
                    cout << "k = " << k << endl;
                    for (it; it >= vec.begin(); it--)
                        cout << *it << "  ";//输出节点序列
                    cout << fx[tmp.second] << endl;//输出总的fx值
                    break;//找到第K短路，退出
                }

            } else {//将当前节点的子女节点入队
                EdgeNode *p = vn[node[tmp.second]].firstEdge;
                while (p != NULL) {
                    ++loc;
                    if(loc == 1521)
                        int x = 0;
                    gx[loc] = gx[tmp.second] + p->cost;
                    node[loc] = p->ter_id;
                    parent[loc] = tmp.second;
                    hx[loc] = dis[p->ter_id];
//                    EdgeNode *tmp = p;
                    fx[loc] = gx[loc] + hx[loc];
//                    p = tmp;
                    q.push(make_pair(make_pair(fx[loc], gx[loc]), loc));
                    p = p->next;

                }
            }

        }
        return 1;
    }

};

#endif