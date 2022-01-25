# TSN-2022-winter
网络时延保障&amp;高可靠路由算法

- Readin.cpp
  - 负责对文件的读取、初步处理
- Graph.cpp
  - 利用Readin中得到的边信息建图
  - 通过邻接表（头结点、边界点）存图
- Algorithm.cpp
  - Algorithm 这个基类有一个成员Graph
  - 其余的几个算法类继承了Algorithm这个基类
  - 目前实现的主要就是Pulse算法
