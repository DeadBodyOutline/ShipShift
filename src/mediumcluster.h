#ifndef __MEDIUMCLUSTER_H__
#define __MEDIUMCLUSTER_H__

#include "cluster.h"

class MediumCluster : public Cluster
{
public:
    virtual void update(float dt);
};

#endif // __MEDIUMCLUSTER_H__
