#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "Node.h"
#include "Link.h"
#include <string>
#include <vector>

class Network
{
public:
    Network(std::vector< std::vector<std::string> > _linkInfo, std::vector< std::vector<std::string> > _initPower);

    ~Network();

    std::vector<Node*> getNodes() const;

    std::vector<Link*> getLinks() const;

    void buildNetwork();
    
private:
    std::vector< std::vector<std::string> > _link;

    std::vector< std::vector<std::string> > _power;

    std::vector<Node*> _nodes;

    std::vector<Link*> _links;
};

#endif //__NETWORK_H__
