#ifndef __SMALLCLUSTER_H__
#define __SMALLCLUSTER_H__

#include "cluster.h"

class SmallCluster : public Cluster
{
public:
    SmallCluster(sf::RenderWindow &renderWindow);
    virtual void update(float dt) = 0;
    virtual void spawn();
};

#endif // __SMALLCLUSTER_H__
