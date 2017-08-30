#include "NodeTree.h"
#include <algorithm>

NodeTree::NodeTree(std::string file_name)
{
    std::ifstream input_file{ file_name };
    {
        unsigned short row = 0, column = 0;
        int index = 0;
        int index_of_prev_row = 0;
        while (!input_file.eof())
        {
            std::string str;
            input_file >> str;
            AddNode(Node{ 
                static_cast<unsigned char>(std::stoi(str)), 
                column == 0 ? -1 : index_of_prev_row + column - 1, 
                column == row ? -1 : index_of_prev_row + column
            });
            /* OLD
            AddNode(Node{ 
                static_cast<unsigned char>(std::stoi(str)), 
                column == 0 ? -1 : CalcIndex(row - 1, column - 1), 
                column == row ? -1 : CalcIndex(row - 1, column) 
            });
            */
            if (column == row)
            {
                row++;
                index_of_prev_row = index - column;
                column = 0;
            }
            else
                column++;
            index++;
        }
        rows = row;
        total_costs.resize(nodes.size());
        std::fill(total_costs.begin(), total_costs.end(), -1);
    }
    // End of NodeTree initialization
}

void NodeTree::AddNode(Node && node)
{
    nodes.emplace_back(node);
}

unsigned int NodeTree::GetLongestPath()
{
    // check for highest value from the bottom row
    // index of last row's first element
    int offset = NodeTree::CalcIndex(rows - 1, 0);
    auto max_iter = std::max_element(total_costs.begin() + offset, total_costs.end());
    return *max_iter;
}

void NodeTree::SetHighestCosts()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        auto& node = nodes[i];
        unsigned left_parent_index = node.GetLeftParentIndex();
        unsigned right_parent_index = node.GetRightParentIndex();
        if (left_parent_index == -1 && right_parent_index == -1)
            // root of the tree
            total_costs[i] = node.GetCost();
        else
        {
            // choose from bigger parent + own cost
            if (left_parent_index == -1) // its left border of the tree - only one way to this node
                total_costs[i] = total_costs[right_parent_index] + node.GetCost();
            else if (right_parent_index == -1) // right border of the tree - only one way to this node
                total_costs[i] = total_costs[left_parent_index] + node.GetCost();
            else
            {
                // choose from bigger parent + own cost
                int left_cost = total_costs[left_parent_index];
                int right_cost = total_costs[right_parent_index];
                if (left_cost >= right_cost) // if left_cost == right_cost it does not matter
                    total_costs[i] = left_cost + node.GetCost();
                else if (left_cost < right_cost)
                    total_costs[i] = right_cost + node.GetCost();
            }
        }
    }
}

