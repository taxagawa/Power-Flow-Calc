#include "Network.h"
#include "Node.h"
#include "Link.h"
#include <string>
#include <vector>

using namespace std;

//======================================================================
Network::Network(std::vector< std::vector<std::string> > _linkInfo, std::vector< std::vector<std::string> > _initPower)
{
    _link  = _linkInfo;
    _power = _initPower;
}

//======================================================================
Network::~Network()

//======================================================================
vector<Node*> Network::getNodes() const
{
    return _nodes;
}

//======================================================================
vector<Node*> Network::getLinks() const
{
    return _links;
}

//======================================================================
void Network::buildNetwork()
{
    
}
