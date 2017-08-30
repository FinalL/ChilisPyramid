#include <iostream>
#include "NodeTree.h"

int main(int argc, char* argv[])
{
    NodeTree graph{ "pyramid.txt" };
    graph.SetHighestCosts();
    std::cout << "The length of the longest path is: " << graph.GetLongestPath() << std::endl;
    system("pause");
    return 0;
}