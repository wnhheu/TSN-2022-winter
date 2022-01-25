#include "Readin.h"
#include <bits/stdc++.h>
#include <iostream>
void ReadIn::read()
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
    while(getline(in, line) && in.good())
    {
        ++cnt;
        if(cnt == 1)
            continue;
        split(links, line);  //把line里的单元格数字字符提取出来，“,”为单元格分隔符
    }
    in.close();
}