#include "Readin.h"
#include <bits/stdc++.h>
#include <iostream>
void ReadIn::read_topo()
{
    std::string line;
    std::string filename;
    std::ifstream in("D:\\Users\\Documents\\GitHub\\data\\DelayRange\\dc2\\topo.csv");
    // std::ifstream in("D:\\Users\\Documents\\GitHub\\data\\functioncase\\topo.csv");
    if (in.fail())
    {
        std::cout << "File not found" << std::endl;
        return;
    }
    int cnt = 0;
    while (getline(in, line) && in.good())
    {
        ++cnt;
        if (cnt == 1)
            continue;
        split_topo(links, line); //把line里的单元格数字字符提取出来，“,”为单元格分隔符
    }
    in.close();
}

void ReadIn::split_topo(std::vector<link> &links, std::string &line)
{
    std::vector<std::string> buffer;
    int cnt = 0;
    std::string str;
    for (int i = 0; i < line.size(); ++i)
    {
        if (line[i] == ',')
        {
            buffer.push_back(str);
            str.clear();
            ++cnt;
            continue;
        }
        str.push_back(line[i]);
    }
    link tmp;
    for (int i = 0; i < cnt; ++i)
    {
        if (i == 0)
            tmp.link_id = atoi(buffer[i].c_str());
        if (i == 1)
            tmp.source_id = atoi(buffer[i].c_str());
        if (i == 2)
            tmp.ter_id = atoi(buffer[i].c_str());
        if (i == 4)
            tmp.cost = atoi(buffer[i].c_str());
        if (i == 5)
            tmp.bandwidth = atoi(buffer[i].c_str());
        if (i == 6)
            tmp.delay = atoi(buffer[i].c_str());
        if (i == 7)
        {
            tmp.srlgNum = atoi(buffer[i].c_str());
            tmp.srlgs = new int[tmp.srlgNum];
        }
        if (i == 8) // to be completed
            continue;
    }
    links.push_back(tmp);
}

void ReadIn::split_tunnel(std::vector<link> &links, std::string &line)
{
    std::vector<std::string> buffer;
    int cnt = 0;
    std::string str;
    for (int i = 0; i < line.size(); ++i)
    {
        if (line[i] == ',')
        {
            buffer.push_back(str);
            str.clear();
            ++cnt;
            continue;
        }
        str.push_back(line[i]);
    }
    tunnel tmp;
    for (int i = 0; i < cnt; ++i)
    {
        if (i == 0)
            tmp.demand_id = atoi(buffer[i].c_str());
        if (i == 1)
            tmp.source_id = atoi(buffer[i].c_str());
        if (i == 2)
            tmp.ter_id = atoi(buffer[i].c_str());
        if (i == 3)
            tmp.min_delay = atof(buffer[i].c_str());
        if (i == 4)
            tmp.max_delay = atof(buffer[i].c_str());
        if (i == 5)
            tmp.bandwidth = atoi(buffer[i].c_str());
        if (i == 6) // to be completed
            continue;
    }
    tunnels.push_back(tmp);
}

void ReadIn::read_tunnel()
{
    std::string line;
    std::string filename;
    std::ifstream in("D:\\Users\\Documents\\GitHub\\data\\DelayRange\\dc2\\tunnel.csv");
    // std::ifstream in("D:\\Users\\Documents\\GitHub\\data\\functioncase\\topo.csv");
    if (in.fail())
    {
        std::cout << "File not found" << std::endl;
        return;
    }
    int cnt = 0;
    while (getline(in, line) && in.good())
    {
        ++cnt;
        if (cnt == 1)
            continue;
        split_tunnel(links, line); //把line里的单元格数字字符提取出来，“,”为单元格分隔符
    }
    in.close();
}
