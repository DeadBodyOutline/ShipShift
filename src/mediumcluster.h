#ifndef __MEDIUMCLUSTER_H__
#define __MEDIUMCLUSTER_H__

#include <vector>

#include "cluster.h"
#include "mediumenemy.h"
#include "player.h"

class MediumCluster : public Cluster
{
public:
    MediumCluster(sf::RenderWindow &renderWindow, Player &player);
    virtual void update(float dt);
    virtual void spawn();

};

#endif // __MEDIUMCLUSTER_H__
