#ifndef __CLUSTER_H__
#define __CLUSTER_H__

class Cluster
{
public:
    enum ClusterType {
        SmallEnemies,
        MediumEnemies,
        LargeEnemies
    };

    virtual void update(float dt) = 0;
};

#endif // __CLUSTER_H__
