#pragma once
#include <exception>
class Node
{
public:
    Node(unsigned char cost, int left_parent_index, int right_parent_index);
    unsigned int GetLeftParentIndex();
    unsigned int GetRightParentIndex();
    const unsigned char GetCost() const;
private:
    int left_parent_i;
    int right_parent_i;
    const unsigned char cost;
};