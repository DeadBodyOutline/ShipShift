#ifndef __LARGECLUSTER_H__
#define __LARGECLUSTER_H__

#include "cluster.h"

class LargeCluster : public Cluster
{
public:
    virtual void update(float dt) = 0;
};

#endif // __LARGECLUSTER_H__
