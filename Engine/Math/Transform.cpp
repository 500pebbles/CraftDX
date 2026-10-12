#include "Transform.h"

Craft::Transform::Transform()
{
    Update();
}

void Craft::Transform::Update()
{
    worldMatrix = Matrix4::Scale(scale) * Matrix4::Rotation(rotation) * Matrix4::Translation(position);
}

Craft::Vector3 Craft::Transform::Right() const
{
    return Vector3::Right * Matrix4::Rotation(rotation);
}

Craft::Vector3 Craft::Transform::Up() const
{
    return Vector3::Up * Matrix4::Rotation(rotation);
}

Craft::Vector3 Craft::Transform::Forward() const
{
    return Vector3::Forward * Matrix4::Rotation(rotation);
}
