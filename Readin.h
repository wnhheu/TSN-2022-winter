#ifndef READIN_H
#define READIN_H
class ReadIn
{
private:
    std::vector<link> links;
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
public:
    void read();

    std::vector<link> &get_data()
    {
        return links;
    }

};


#endif
