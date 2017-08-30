#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include "Node.h"
#include <array>

class NodeTree
{
    template<class type>
    using vector = std::vector<type>;
public:
    NodeTree(std::string file_name);
    void AddNode(Node&& node);
    unsigned int GetLongestPath();
    static constexpr int CalcIndex(unsigned short row, unsigned short col)
    {
        return row == 0 ? 0 : SumToNum(row) + col;
    }
private:
    vector<Node> nodes;
    vector<int> total_costs;
    unsigned short rows;
    static constexpr int SumToNum(unsigned short i)
    {
        return i < 1 ?
            throw std::exception("Bad input into SumToNum() - lower than 1")
            : i == 1 ?
            1
            : i + SumToNum(i - 1);
    }
public:
    void SetHighestCosts();
};