#ifndef CUSTOM_GRAVITY_H
#define CUSTOM_GRAVITY_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/physics_server3d.hpp>
#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Body/BodyInterface.h>

using namespace godot;

class CustomGravity : public Node3D {
    GDCLASS(CustomGravity, Node3D);

private:
    Vector3 gravity_center = Vector3(0, 0, 0);
    float gravity_strength = 9.81f;
    int gravity_type = 0; // 0: Radial, 1: Directional, 2: Local Zones

public:
    static void _bind_methods();

    void set_gravity_center(Vector3 center);
    Vector3 get_gravity_center() const;

    void set_gravity_strength(float strength);
    float get_gravity_strength() const;

    void set_gravity_type(int type);
    int get_gravity_type() const;

    void apply_custom_gravity(JPH::PhysicsSystem* physics_system);
    Vector3 compute_gravity_force(Vector3 position);
};

#endif // CUSTOM_GRAVITY_H
