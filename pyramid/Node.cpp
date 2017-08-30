#include "Node.h"

Node::Node(unsigned char cost, int left_parent_index, int right_parent_index)
    : cost(cost), left_parent_i(left_parent_index), right_parent_i(right_parent_index)
{
}

unsigned int Node::GetLeftParentIndex()
{
    return left_parent_i;
}

unsigned int Node::GetRightParentIndex()
{
    return right_parent_i;
}

const unsigned char Node::GetCost() const
{
    return cost;
}
