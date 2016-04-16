#ifndef __LARGECLUSTER_H__
#define __LARGECLUSTER_H__

#include "cluster.h"

class LargeCluster : public Cluster
{
public:
    LargeCluster(sf::RenderWindow &renderWindow);
    virtual void update(float dt) = 0;
    virtual void spawn();
};

#endif // __LARGECLUSTER_H__
