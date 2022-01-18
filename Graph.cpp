EdgeNode::EdgeNode(const link &oth) {
    next = nullptr;
    cost = oth.cost;
    ter_id = oth.ter_id;
    bandwidth = oth.bandwidth;
    delay = oth.delay;
    srlgNum = oth.srlgNum;
    srlgs = new int[srlgNum];
    for(int i = 0; i < srlgNum; ++i)
    {
        srlgs[i] = oth.srlgs[i];
    }
}

EdgeNode::EdgeNode(const EdgeNode &oth) {
    next = oth.next;
    cost = oth.cost;
    ter_id = oth.ter_id;
    bandwidth = oth.bandwidth;
    delay = oth.delay;
    srlgNum = oth.srlgNum;
    srlgs = new int[srlgNum];
    for(int i = 0; i < srlgNum; ++i)
    {
        srlgs[i] = oth.srlgs[i];
    }
}

EdgeNode::EdgeNode &operator=(const EdgeNode &oth) {
    next = oth.next;
    cost = oth.cost;
    ter_id = oth.ter_id;
    bandwidth = oth.bandwidth;
    delay = oth.delay;
    srlgNum = oth.srlgNum;
    srlgs = new int[srlgNum];
    for(int i = 0; i < srlgNum; ++i)
    {
        srlgs[i] = oth.srlgs[i];
    }
}

Graph::Graph()
{
    link_size = -1;
    vn = new VertexNode [node_num];
    vnr = new VertexNode [node_num];
    dis = new int [node_num];
    // std::memset(dis, 0, sizeof dis);
}
Graph::void initialize(std::vector<link> &my_link)
{
    links = my_link;
    link_size = links.size();
}

Graph::int createGraph() { //构造图
    int source_id, ter_id;
    int cost;
    for (int i = 0; i < link_size; i++) {
        source_id = links[i].source_id;
        ter_id = links[i].ter_id;
        cost = links[i].cost;
        if (vn[source_id].id == -1) vn[source_id].id = source_id;
        if (vn[ter_id].id == 'Z') vn[ter_id].id = ter_id;
        EdgeNode *edge_new = new EdgeNode(links[i]);
        edge_new->ter_id = links[i].ter_id;
        EdgeNode *p = vn[source_id].firstEdge;
        if (vn[source_id].firstEdge == NULL) {
            vn[source_id].firstEdge = edge_new;
        } else {
            while (p->next != NULL)
                p = p->next;
            p->next = edge_new;//一个边有两个边表节点， 添加第一个边表节点

        }
        EdgeNode *edge_new2 = new EdgeNode(links[i]);
        edge_new2->ter_id = source_id;
        p = vn[ter_id].firstEdge;
        if (vn[ter_id].firstEdge == NULL)
            vn[ter_id].firstEdge = edge_new2;
        else {
            while (p->next != NULL)
                p = p->next;
            p->next = edge_new2;//一条边有两个边表节点，添加第二个边表节点
        }
    }

    for (int i = 0; i < node_num; i++) //无向图的复制
        vnr[i] = vn[i];

    return 1;
}
