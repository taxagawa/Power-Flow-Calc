#ifndef __NETWORKBUILDER_H__
#define __NETWORKBUILDER_H__

#include "Node.h"
#include <vector>

class NetworkBuilder
{
public:
    std::vector<Node*> getNodes() const;

private:
    std::vector<Node*> _nodes;
};

#endif //__NETWORKBUILDER_H__
