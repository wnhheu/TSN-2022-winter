#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct link
{
    int link_id;
    int source_id;
    int ter_id;
    int cost;
    int bandwidth;
    int delay;
    int srlgNum; -+
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

int str_to_int(std::string &str)
{
    int res = 0;
    for(int i = 0; i < str.size(); ++i)
    {
        res *= 10;
        res += str[i] - '0';
    }
    return res;
}

void split(std::vector<link> &links, std::string &line)
{
    std::vector<std::string> buffer;
    int cnt = 0;
    std::string str;
    for(int i = 0; i < line.size(); ++i)
    {
        if(line[i] == ',')
        {
            buffer.push_back(str);
            str.clear();
            ++cnt;
            continue;
        }
        str.push_back(line[i]);
    }
    link tmp;
    for(int i = 0; i < cnt; ++i)
    {
        if(i == 0)
            tmp.link_id = str_to_int(buffer[i]);
        if(i == 1)
            tmp.source_id = str_to_int(buffer[i]);
        if(i == 2)
            tmp.ter_id = str_to_int(buffer[i]);
        if(i == 4)
            tmp.cost = str_to_int(buffer[i]);
        if(i == 5)
            tmp.bandwidth = str_to_int(buffer[i]);
        if(i == 6)
            tmp.delay = str_to_int(buffer[i]);
        if(i == 7)
        {
            tmp.srlgNum = str_to_int(buffer[i]);
            tmp.srlgs = new int[tmp.srlgNum];
        }
        if(i == 8) // to be completed
            continue;
    }
    links.push_back(tmp);
}



void read()
{
    std::vector<link> links;
    std::string line;
    std::string filename;
    std::ifstream in("D:\\documents\\GitHub\\TSN-2022-winter\\Output\\DelayRange\\dc2\\topo.csv");
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
    return ;
}




int main() {
    read();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
