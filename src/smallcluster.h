#ifndef __SMALLCLUSTER_H__
#define __SMALLCLUSTER_H__

#include "cluster.h"

class SmallCluster : public Cluster
{
public:
    virtual void update(float dt) = 0;
};

#endif // __SMALLCLUSTER_H__
