#pragma once

#include <vector>
#include <string>
#include "../Physics/Physics.hpp"

struct RigidComponent 
{
public:
    int ID;
    //const char* name;
    //const char* shapeType;
    //const char* correspondingJointName;
    std::string name;
    std::string shapeType;
    std::string correspondingJointName;
    float capsuleLength, capsuleRadius;
    float mass, friction, restitution, linearDamping, angularDamping, sleepThreshold;
    PxRigidDynamic* pxRigidBody = nullptr;
    PxVec3 angularMass;
    PxQuat rotation;
    glm::mat4 restMatrix;
    glm::vec3 scaleAbsoluteVector;
    glm::vec3 boxExtents, offset;
};

struct JointComponent 
{
public:
    //const char* name;
    std::string name;
    int parentID, childID;
    PxMat44 parentFrame, childFrame;
    PxD6Joint* pxD6 = nullptr;
    // Drive component
    float drive_angularDamping, drive_angularStiffness, drive_linearDampening, drive_linearStiffness;
    glm::mat4 target;
    bool drive_enabled;
    // Limit component
    float twist, swing1, swing2, limit_angularStiffness, limit_angularDampening, limit_linearStiffness, limit_linearDampening;

    glm::vec3 limit;
    bool joint_enabled;
};

struct Ragdoll
{
    std::vector<RigidComponent> _rigidComponents;
    std::vector<JointComponent> _jointComponents;

    void LoadFromJSON(std::string filename, PxU32 collisionGroup);
    RigidComponent* GetRigidByName(std::string& name);

    void EnableVisualization();
    void DisableVisualization();
    void EnableCollision();
    void DisableCollision();
};