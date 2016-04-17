#ifndef __SMALLCLUSTER_H__
#define __SMALLCLUSTER_H__

#include "cluster.h"
#include "player.h"

class SmallCluster : public Cluster
{
public:
    SmallCluster(sf::RenderWindow &renderWindow, Player &player);
    virtual void update(float dt);
    virtual void spawn();
};

#endif // __SMALLCLUSTER_H__
