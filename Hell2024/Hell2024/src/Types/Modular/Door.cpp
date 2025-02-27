#include "Door.hpp"

#include "Core/AssetManager.hpp"
#include "Game/Player.hpp"
#include "Core/Audio.hpp"
#include "Utils/Util.hpp"

Door::Door(glm::vec3 position, float rotation, bool openOnStart)
{
    this->m_position = position;
    this->m_rotation = rotation;
    this->m_openOnStart = openOnStart;
    SetToInitialState();
}

void Door::SetToInitialState() 
{
    if (m_openOnStart)
    {
        m_currentOpenRotation = -m_maxOpenRotation;
        state = OPEN;
    }
    else
    {
        m_currentOpenRotation = 0;
        state = CLOSED;
    }
}

void Door::Interact()
{
    if (state == CLOSED) 
    {
        state = OPENING;
        Audio::PlayAudio("Door_Open.wav", Audio::DOOR_VOLUME);
    }
    else if (state == OPEN)
    {
        state = CLOSING;
        Audio::PlayAudio("Door_Open.wav", Audio::DOOR_VOLUME);
    }
}

void Door::Update(float deltaTime)
{
    float openSpeed = 5.208f;
    if (state == OPENING)
    {
        m_currentOpenRotation -= openSpeed * deltaTime;
        if (m_currentOpenRotation < -m_maxOpenRotation)
        {
            m_currentOpenRotation = -m_maxOpenRotation;
            state = OPEN;
        }
    }
    if (state == CLOSING) 
    {
        m_currentOpenRotation += openSpeed * deltaTime;
        if (m_currentOpenRotation > 0) 
        {
            m_currentOpenRotation = 0;
            state = CLOSED;
        }
    }
    glm::mat4 modelMatrix = GetDoorModelMatrix();
    if (collisionBody) 
    {
        Transform offset;
        offset.position.z = DOOR_WIDTH * -0.5f;
        offset.position.y = DOOR_HEIGHT * 0.5f;
        offset.position.x = DOOR_EDITOR_DEPTH * -0.5f;
        PxMat44 m = Util::GlmMat4ToPxMat44(modelMatrix * offset.to_mat4());
        PxTransform transform = PxTransform(m);
        collisionBody->setGlobalPose(transform);
    }
    if (raycastBody) 
    {
        PxMat44 m2 = Util::GlmMat4ToPxMat44(modelMatrix);
        PxTransform transform2 = PxTransform(m2);
        raycastBody->setGlobalPose(transform2);
    }

    // Door RenderItem AABB

    //glm::vec3 extents = Util::PxVec3toGlmVec3(raycastBody->getWorldBounds().getExtents());
    //glm::vec3 center = Util::PxVec3toGlmVec3(raycastBody->getWorldBounds().getCenter());
    //m_doorRenderItemAABB.boundsMin = center - extents;
    //m_doorRenderItemAABB.boundsMax = center + extents;

    /*
    glm::vec3 extents = Util::PxVec3toGlmVec3(doorFrameCastBody->getWorldBounds().getExtents());
    glm::vec3 center = Util::PxVec3toGlmVec3(doorFrameCastBody->getWorldBounds().getCenter());
    m_doorFrameRenderItemAABB.boundsMin = center - extents;
    m_doorFrameRenderItemAABB.boundsMax = center + extents;*/

    // AABB
    if (raycastBody) 
    {
        _aabbPreviousFrame = _aabb;
        glm::vec3 extents = Util::PxVec3toGlmVec3(raycastBody->getWorldBounds().getExtents());
        glm::vec3 center = Util::PxVec3toGlmVec3(raycastBody->getWorldBounds().getCenter());
        glm::vec3 minBounds = center - extents;
        glm::vec3 maxBounds = center + extents;
        _aabb = AABB(minBounds, maxBounds);
        //_aabb.extents = Util::PxVec3toGlmVec3(raycastBody->getWorldBounds().getExtents());
        //_aabb.position = Util::PxVec3toGlmVec3(raycastBody->getWorldBounds().getCenter());
    }
}

void Door::CleanUp() 
{
    if (collisionBody) 
    {
        collisionBody->release();
    }
    if (collisionShape) 
    {
        collisionShape->release();
    }
    if (raycastBody)
    {
        raycastBody->release();
    }
    if (raycastShape)
    {
        raycastShape->release();
    }
}

glm::mat4 Door::GetGizmoMatrix() 
{
    Transform frameTransform;
    frameTransform.position = m_position + glm::vec3(0, Door::DOOR_HEIGHT * 0.5f, 0);
    frameTransform.rotation.y = m_rotation;
    return frameTransform.to_mat4();
}

glm::mat4 Door::GetFrameModelMatrix()
{
    Transform frameTransform;
    frameTransform.position = m_position;
    frameTransform.rotation.y = m_rotation;
    return frameTransform.to_mat4();
}

glm::mat4 Door::GetDoorModelMatrix()
{
    Transform doorTransform;
    doorTransform.position = glm::vec3(0.058520, 0, 0.39550f);
    doorTransform.rotation.y = m_currentOpenRotation;
    return GetFrameModelMatrix() * doorTransform.to_mat4();
}

glm::vec3 Door::GetFloorplanVertFrontLeft(float padding)
{
    return GetFrameModelMatrix() * glm::vec4(DOOR_EDITOR_DEPTH + padding, 0, (-Door::DOOR_WIDTH / 2), 1.0f);
}

glm::vec3 Door::GetFloorplanVertFrontRight(float padding) 
{
    return GetFrameModelMatrix() * glm::vec4(DOOR_EDITOR_DEPTH + padding, 0, (Door::DOOR_WIDTH / 2), 1.0f);
}

glm::vec3 Door::GetFloorplanVertBackLeft(float padding)
{
    return GetFrameModelMatrix() * glm::vec4(-DOOR_EDITOR_DEPTH - padding, 0, (Door::DOOR_WIDTH / 2), 1.0f);
}

glm::vec3 Door::GetFloorplanVertBackRight(float padding)
{
    return GetFrameModelMatrix() * glm::vec4(-DOOR_EDITOR_DEPTH - padding, 0, (-Door::DOOR_WIDTH / 2), 1.0f);
}

glm::vec3 Door::GetFrontLeftCorner() 
{
    return GetDoorModelMatrix() * glm::vec4(0, 0, -Door::DOOR_WIDTH, 1.0f);
}

glm::vec3 Door::GetFrontRightCorner()
{
    return GetDoorModelMatrix() * glm::vec4(0, 0, 0, 1.0f);
}

glm::vec3 Door::GetBackLeftCorner() 
{
    return GetDoorModelMatrix() * glm::vec4(-DOOR_EDITOR_DEPTH, 0, -Door::DOOR_WIDTH, 1.0f);
}

glm::vec3 Door::GetBackRightCorner() 
{
    return GetDoorModelMatrix() * glm::vec4(-DOOR_EDITOR_DEPTH, 0, 0, 1.0f);
}

bool Door::IsInteractable(glm::vec3 playerPosition) 
{
    float distSqrd = Util::DistanceSquared(m_position, playerPosition);
    return distSqrd < (INTERACT_DISTANCE * INTERACT_DISTANCE);
}

void Door::CreatePhysicsObject() 
{
    Physics::Destroy(collisionBody);
    Physics::Destroy(raycastBody);
    Physics::Destroy(collisionShape);
    Physics::Destroy(raycastShape);

    PhysicsFilterData filterData;
    filterData.raycastGroup = RAYCAST_DISABLED;
    filterData.collisionGroup = CollisionGroup::ENVIROMENT_OBSTACLE;
    filterData.collidesWith = (CollisionGroup)(GENERIC_BOUNCEABLE | BULLET_CASING | RAGDOLL);
    collisionShape = Physics::CreateBoxShape(DOOR_EDITOR_DEPTH * 0.5f, DOOR_HEIGHT * 0.5f, DOOR_WIDTH * 0.5f);
    collisionBody = Physics::CreateRigidStatic(Transform(), filterData, collisionShape);

	PxShapeFlags shapeFlags(PxShapeFlag::eSCENE_QUERY_SHAPE); // Most importantly NOT eSIMULATION_SHAPE. PhysX does not allow for tri mesh.
    PhysicsFilterData filterData2;
    filterData2.raycastGroup = RaycastGroup::RAYCAST_ENABLED;
    filterData2.collisionGroup = GENERTIC_INTERACTBLE;
    filterData2.collidesWith = NO_COLLISION;
    PxTriangleMesh* triangleMesh = Physics::CreateTriangleMeshFromModelIndex(AssetManager::GetModelIndexByName("Door"));
    raycastShape = Physics::CreateShapeFromTriangleMesh(triangleMesh, shapeFlags);
    raycastBody = Physics::CreateRigidStatic(Transform(), filterData2, raycastShape);

    PhysicsObjectData* physicsObjectData = new PhysicsObjectData(ObjectType::DOOR, this);
    raycastBody->userData = physicsObjectData;

    /*
    // Door frame phyics object
    {
        Physics::Destroy(doorFrameCollisionShape);
        Physics::Destroy(doorFrameRaycastShape);

        PhysicsFilterData filterData;
        filterData.raycastGroup = RAYCAST_DISABLED;
        filterData.collisionGroup = CollisionGroup::ENVIROMENT_OBSTACLE;
        filterData.collidesWith = (CollisionGroup)(GENERIC_BOUNCEABLE | BULLET_CASING | RAGDOLL);
        collisionShape = Physics::CreateBoxShape(DOOR_EDITOR_DEPTH * 0.5f, DOOR_HEIGHT * 0.5f, DOOR_WIDTH * 0.5f);
        collisionBody = Physics::CreateRigidStatic(Transform(), filterData, collisionShape);

        PxShapeFlags shapeFlags(PxShapeFlag::eSCENE_QUERY_SHAPE); // Most importantly NOT eSIMULATION_SHAPE. PhysX does not allow for tri mesh.
        PhysicsFilterData filterData2;
        filterData2.raycastGroup = RaycastGroup::RAYCAST_ENABLED;
        filterData2.collisionGroup = NO_COLLISION;
        filterData2.collidesWith = NO_COLLISION;
        PxTriangleMesh* triangleMesh = Physics::CreateTriangleMeshFromModelIndex(AssetManager::GetModelIndexByName("DoorFrame"));
        raycastShape = Physics::CreateShapeFromTriangleMesh(triangleMesh, shapeFlags);
        raycastBody = Physics::CreateRigidStatic(Transform(), filterData2, raycastShape);

        PhysicsObjectData* physicsObjectData = new PhysicsObjectData(PhysicsObjectType::DOOR, this);
        raycastBody->userData = physicsObjectData;
    }*/
}

glm::vec3 Door::GetWorldDoorWayCenter() 
{
    return m_position + glm::vec3(0, 1.3f, 0);
}

bool Door::HasMovedSinceLastFrame()
{
    return (_aabb.boundsMin != _aabbPreviousFrame.boundsMin &&
        _aabb.boundsMax != _aabbPreviousFrame.boundsMax &&
        _aabb.GetCenter() != _aabbPreviousFrame.GetCenter());
}

void Door::UpdateRenderItems()
{
    static int materialIndex = AssetManager::GetMaterialIndex("Door");
    renderItems.clear();

    Model* doorModel = AssetManager::GetModelByIndex(AssetManager::GetModelIndexByName("Door"));
    for (uint32_t& meshIndex : doorModel->GetMeshIndices()) 
    {
        Mesh* mesh = AssetManager::GetMeshByIndex(meshIndex);
        RenderItem3D& renderItem = renderItems.emplace_back();
        renderItem.vertexOffset = mesh->baseVertex;
        renderItem.indexOffset = mesh->baseIndex;
        renderItem.modelMatrix = GetDoorModelMatrix();
        renderItem.inverseModelMatrix = inverse(renderItem.modelMatrix);
        renderItem.meshIndex = meshIndex;
        Material* material = AssetManager::GetMaterialByIndex(materialIndex);
        renderItem.baseColorTextureIndex = material->_basecolor;
        renderItem.rmaTextureIndex = material->_rma;
        renderItem.normalMapTextureIndex = material->_normal;
    }

    Model* frameModel = AssetManager::GetModelByIndex(AssetManager::GetModelIndexByName("DoorFrame"));
    for (uint32_t& meshIndex : frameModel->GetMeshIndices())
    {
        Mesh* mesh = AssetManager::GetMeshByIndex(meshIndex);
        RenderItem3D& renderItem = renderItems.emplace_back();
        renderItem.vertexOffset = mesh->baseVertex;
        renderItem.indexOffset = mesh->baseIndex;
        renderItem.modelMatrix = GetFrameModelMatrix();
        renderItem.inverseModelMatrix = inverse(renderItem.modelMatrix);
        renderItem.meshIndex = meshIndex;
        Material* material = AssetManager::GetMaterialByIndex(materialIndex);
        renderItem.baseColorTextureIndex = material->_basecolor;
        renderItem.rmaTextureIndex = material->_rma;
        renderItem.normalMapTextureIndex = material->_normal;
    }
}

std::vector<RenderItem3D>& Door::GetRenderItems()
{
    return renderItems;
}

void Door::Rotate90() 
{
    m_rotation += DARKOPS_PI * 0.5f;
    if (raycastBody) {
        PxMat44 worldMatrix = Util::GlmMat4ToPxMat44(GetFrameModelMatrix());
        PxTransform transform2 = PxTransform(worldMatrix);
        raycastBody->setGlobalPose(transform2);
    }
}

void Door::SetPosition(glm::vec3 position)
{
    m_position = position;
}

void Door::SetRotation(float rotation) 
{
    m_rotation = rotation;
}

// TODO
/*
std::vector<Vertex> Door::GetDoorAABBVertices()
{
    glm::vec3 color = YELLOW;
    return Util::GetAABBVertices(m_doorRenderItemAABB, color);
}*/

/*

std::vector<Vertex> Door::GetFrameAABBVertices()
{
    glm::vec3 color = YELLOW;
    return Util::GetAABBVertices(m_frameAABB, color);
}*/