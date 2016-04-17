#ifndef __LARGECLUSTER_H__
#define __LARGECLUSTER_H__

#include "cluster.h"
#include "player.h"

class LargeCluster : public Cluster
{
public:
    LargeCluster(sf::RenderWindow &renderWindow, Player &player);
    virtual void update(float dt) = 0;
    virtual void spawn();
};

#endif // __LARGECLUSTER_H__
