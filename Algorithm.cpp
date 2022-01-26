#include "Algorithm.h"
#include <cstdlib> // Header file needed to use srand and rand
#include <ctime>   // Header file needed to use time
/*
bool Dijkstra::dijkstra(int source_id, int ter_id) //dijkstra 求解delay值
{
    //V为顶点集，S为已求得最短距离的点的集合，T为余下点的集合，初始时，S={},T=V,T用带pair的vector实现，当T为空时，代表所有点均以到达集合S中，算法结束，当一个节点从集合T中迁移至S中时，这个顶点对应的距离值便是此节点到起点的最短距离值。
    long max = 1e8;
    VertexNode *vn = graph.get_vn();
    VertexNode *vnr = graph.get_vnr();
    int *delay = graph.get_delay();
    int parent[graph.node_size()]; //更新时记录每个节点的父节点，只有这个距离更新，此节点的父>节点才会更新
    for (int i = 0; i < graph.node_size(); i++)
        parent[i] = -1;
    std::vector<std::pair<int, int>> queue; //不是优先级队列,第一个代表距离，第二个代表节点
    for (int i = 0; i < graph.node_size(); i++)
    {
        if (vnr[i].id != -1)
        {
            if (vnr[i].id == ter_id)
                queue.push_back(std::make_pair(0, vnr[i].id)); //起点的距离值为0
            else
                queue.push_back(std::make_pair(max, vnr[i].id)); //初始化其他点的距离>为max
        }
    }

    vector<pair<int, int>>::iterator it = queue.begin();
    while (!queue.empty())
    {
        sort(queue.begin(), queue.end()); //对剩余节点进行排序
        vector<pair<int, int>>::iterator tmp = queue.begin();
        if (delay[queue.begin()->second] > queue.begin()->first)
            delay[queue.begin()->second] = queue.begin()->first; //队首的距离值为最短的，而且要出队
        EdgeNode *p = vnr[tmp->second].firstEdge;
        int d = tmp->first; //存储此节点出队的距离值
        while (p != NULL)
        {

            for (it = queue.begin() + 1; it != queue.end(); it++)
            {
                if (p->ter_id == it->second) //在T中找到要更新的点
                {
                    if (d + p->cost < it->first)
                    { //需要更新,相等的话则不再更新,相等代表距离一样，但经过的顶点更多
                        it->first = d + p->cost;
                        parent[it->second] = tmp->second; //更>新父节点
                    }

                    break;
                }
            }
            p = p->next;
        }
        queue.erase(queue.begin()); //删除起始节点
    }
    return false;
}
*/
// 先搜哪一条路 
// 空间换时间 

bool Astar::astar(int source_id, int ter_id, int k) //A star 求解K短路
{
    VertexNode *vn = graph.get_vn();
    VertexNode *vnr = graph.get_vnr();
    // int *delay = graph.get_delay();
    int *delay = nullptr;
    if (vn[source_id].id == -1)
    {
        cout << "node doesn't exist" << endl;
        return 0;
    }
    int count = 0;                       //终点出现次数
    int i = 1, loc = 1;                  //步数
    int fx[20000], gx[20000], hx[20000]; //A star中的函数值,即扩展的节点序列，暂定20000
    int node[20000];                     //存储节个序列中实际对应的每个节点
    int parent[20000];                   //每个序列的父节点
    for (int i = 0; i < 20000; i++)
    {
        fx[i] = 0;
        gx[i] = 0;
        hx[i] = 0;
        node[i] = -1;
        parent[i] = 0;
    }
    //添加父节点
    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, greater<pair<pair<int, int>, int>>> q; //优先级队列，第一个int存储的是fx值，第二个存储的是gx值，第三个存储的是扩展的节点序列，满足当fx值相等时，则选择fx较小的
    gx[1] = 0;
    hx[1] = delay[source_id];
    node[1] = source_id; //先将起点入队
    fx[1] = gx[1] + hx[1];
    parent[0] = -1; //便于沿着父节点数组一直找到起点
    parent[1] = 0;
    q.push(std::make_pair(std::make_pair(fx[1], gx[1]), 1));
    while (!q.empty())
    {
        pair<pair<int, int>, int> tmp = q.top();
        q.pop();
        if (node[tmp.second] == ter_id)
        { //找到终点
            vector<int> vec;
            // 用vector存储此条路径
            int now = tmp.second;
            while (parent[now] != -1)
            {
                vec.push_back(node[now]); //节点存入vector
                now = parent[now];        //找到父节点
            }
            EdgeNode *p = vn[node[tmp.second]].firstEdge;
            while (p != NULL) //将子女节点入队
            {
                ++loc;
                gx[loc] = gx[tmp.second] + p->cost;
                node[loc] = p->ter_id;
                parent[loc] = tmp.second;
                hx[loc] = delay[p->ter_id];
                fx[loc] = gx[loc] + hx[loc];
                q.push(std::make_pair(std::make_pair(fx[loc], gx[loc]), loc));
                p = p->next;
            }
            count++;
            if (count == k)
            {
                std::vector<int>::iterator it = vec.end() - 1;
                cout << "k = " << k << endl;
                for (it; it >= vec.begin(); it--)
                    cout << *it << "  ";        //输出节点序列
                cout << fx[tmp.second] << endl; //输出总的fx值
                break;                          //找到第K短路，退出
            }
        }
        else
        { //将当前节点的子女节点入队
            EdgeNode *p = vn[node[tmp.second]].firstEdge;
            while (p != NULL)
            {
                ++loc;
                if (loc == 1521)
                    int x = 0;
                gx[loc] = gx[tmp.second] + p->cost;
                node[loc] = p->ter_id;
                parent[loc] = tmp.second;
                hx[loc] = delay[p->ter_id];
                //                    EdgeNode *tmp = p;
                fx[loc] = gx[loc] + hx[loc];
                //                    p = tmp;
                q.push(std::make_pair(std::make_pair(fx[loc], gx[loc]), loc));
                p = p->next;
            }
        }
    }
    return 1;
}


// dijkstra algorithm 
// if(flag == 0)--search according to cost
// if(flag == 1)--search according to delay
void Pulse::dijkstra(int s, int t, bool flag)   
{
    dis[s] = 0;
    heap.push(node(s, 0));
    while (!heap.empty())
    {
        int u = heap.top().id;
        heap.pop();
        if (visited[u])
            continue;
        visited[u] = true;
        if (u == t)
        {
            heap = {};
            break;
        }
        for (EdgeNode *i = graph.get_vn()[u].firstEdge; i != nullptr; i = i->next)
        {
            int ter = i->ter_id;
            int weight;
            if (flag == false)
                weight = i->cost;
            else
                weight = i->delay;
            if (dis[u] + weight < dis[ter])
            {
                dis[ter] = dis[u] + weight;
                heap.push(node(ter, dis[ter]));
            }
        }
    }
    // std::cout << "error: no such nodes" << std::endl;
}
// initialize the graph
// do dijkstra from end to every other nodes, from two perspectives--cost and delay
// store the result of dijkstras in cost_map and delay_map
void Pulse::initialize()    
{
    dijkstra(end, start, 0);
    int buf[1000];
    int cnt = 0;
    for (int i = 0; i < num; ++i)
    {
        if (dis[i] == INT32_MAX)
            buf[cnt++] = i;
        else
            cost_map[i] = dis[i];
    }
    for (int i = 0; i < cnt; ++i)
    {
        for (int j = 0; j < num; ++j)
        {
            visited[j] = false;
            dis[j] = INT32_MAX;
        }
        dijkstra(end, buf[i], 0);
        cost_map[buf[i]] = dis[buf[i]];
    }

    for (int i = 0; i < num; ++i)
    {
        visited[i] = false;
        dis[i] = INT32_MAX;
    }

    dijkstra(end, start, 1);
    cnt = 0;
    for (int i = 0; i < num; ++i)
    {
        if (dis[i] == INT32_MAX)
            buf[cnt++] = i;
        else
            delay_map[i] = dis[i];
    }
    for (int i = 0; i < cnt; ++i)
    {
        for (int j = 0; j < num; ++j)
        {
            visited[j] = false;
            dis[j] = INT32_MAX;
        }
        dijkstra(end, buf[i], 1);
        delay_map[buf[i]] = dis[buf[i]];
    }

    for (int i = 0; i < num; ++i)
    {
        visited[i] = false;
        dis[i] = INT32_MAX;
    }
}

 // prune accordding to bound and infeasibility
bool Pulse::check(int u, int cost, int delay) 
{
    if (cost_map[u] + cost >= total_cost)
        return false;
    if (delay_map[u] + delay > upper_bound)
        return false;
    return true;
}
// update the path node U records
// according to the rule mentioned in Chapter 4 of 2012.10 paper
bool Pulse::update(int u, int *path, int &cnt, double p, int cost, int delay)
{
    bool flag = false;
    if (info[u].mini_cost.cost > cost)  // Update the path with minimum cost
    {
        info[u].mini_cost.clear();
        for (int i = 0; i < cnt; ++i)
        {
            info[u].mini_cost.push_back(path[i]);
        }
        info[u].mini_cost.push_back(u);
        info[u].mini_cost.cost = cost;
        info[u].mini_cost.delay = delay;
        flag = true;
    }
    if (info[u].mini_delay.delay > delay)   // Update the path with minimum delay
    {
        info[u].mini_delay.clear();
        for (int i = 0; i < cnt; ++i)
        {
            info[u].mini_delay.push_back(path[i]);
        }
        info[u].mini_delay.push_back(u);
        info[u].mini_delay.cost = cost;
        info[u].mini_delay.delay = delay;
        flag = true;
    }
    if (!flag && p > 0.5)   // if not meet the requirements above, update the random replace path
    {
        info[u].random_rep.clear();
        for (int i = 0; i < cnt; ++i)
        {
            info[u].random_rep.push_back(path[i]);
        }
        info[u].random_rep.push_back(u);
        info[u].random_rep.cost = cost;
        info[u].random_rep.delay = delay;
        flag = true;
    }
    if (flag)   // update the recorded partial path
    {
        path[cnt++] = u;
    }
    return flag;
}


// dfs from start to end, use recursion
void Pulse::dfs(int u, int *path, int &cnt, int cost, int delay)   
{
    if (u == end)
    {
        ++t;
        if (delay > upper_bound || delay < lower_bound)
            return;
        if (cost > total_cost)
            return;
        total_cost = cost;
        Path tmp;
        for(int i = 0; i < cnt; ++i)
            tmp.push_back(path[i]);
        tmp.push_back(u);
        tmp.cost = cost;
        tmp.delay = delay;
        res.push(tmp);
        unsigned seed = time(0);
        srand(seed);
        double x = rand() % 100;
        double p = x / 100;
        if (update(u, path, cnt, p, cost, delay))
            --cnt;
        return;
    }

    if (check(u, cost, delay))  // prune
    {
        unsigned seed = time(0);
        srand(seed);
        double x = rand() % 100;
        double p = x / 100;
        if (!update(u, path, cnt, p, cost, delay))
        {
            return;
        }
    }
    else
        return;

    for (EdgeNode *i = graph.get_vn()[u].firstEdge; i != nullptr; i = i->next)
    {
        int ter = i->ter_id;
        if (visited[ter])
        {
            continue;
        }
        visited[ter] = true;
        dfs(i->ter_id, path, cnt, cost + i->cost, delay + i->delay);
        visited[ter] = false;
    }
    --cnt;
}

void Pulse::pulse_algorithm()
{
    std::queue<int> que;
    que.push(start);
    int *path = new int[num];
    int cnt = 0;
    int cost = 0;
    int delay = 0;
    for (int i = 0; i < num; ++i)
        visited[i] = false;
    visited[start] = true;
    dfs(start, path, cnt, cost, delay);
    int x = 0;
}

void Pulse::print() // print the result
{
    std::cout << "Path: ";
    for (int i = 0; i < info[end].mini_cost.size(); ++i)
        std::cout << info[end].mini_cost.path_info[i] << " ";
    std::cout << "\n" << "Cost is: ";
    std::cout << info[end].mini_cost.cost << "\n";
    std::cout << "Delay is: ";
    std::cout << info[end].mini_cost.delay << "\n";
    Path tmp = res.top();
    for(int i = 0; i < tmp.size(); ++i)
        std::cout << tmp.path_info[i] << " ";
        std::cout << "\n" << "Cost is: ";
    std::cout << tmp.cost << "\n";
    std::cout << "Delay is: ";
    std::cout << tmp.delay << "\n";
}
