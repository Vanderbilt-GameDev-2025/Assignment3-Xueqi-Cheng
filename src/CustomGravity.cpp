#include <../../game/godot-jolt/Jolt.h>


void CustomGravity::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_gravity_center", "center"), &CustomGravity::set_gravity_center);
    ClassDB::bind_method(D_METHOD("get_gravity_center"), &CustomGravity::get_gravity_center);
    ClassDB::bind_method(D_METHOD("set_gravity_strength", "strength"), &CustomGravity::set_gravity_strength);
    ClassDB::bind_method(D_METHOD("get_gravity_strength"), &CustomGravity::get_gravity_strength);
    ClassDB::bind_method(D_METHOD("set_gravity_type", "type"), &CustomGravity::set_gravity_type);
    ClassDB::bind_method(D_METHOD("get_gravity_type"), &CustomGravity::get_gravity_type);

    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "gravity_center"), "set_gravity_center", "get_gravity_center");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gravity_strength"), "set_gravity_strength", "get_gravity_strength");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "gravity_type"), "set_gravity_type", "get_gravity_type");
}

void CustomGravity::set_gravity_center(Vector3 center) { gravity_center = center; }
Vector3 CustomGravity::get_gravity_center() const { return gravity_center; }

void CustomGravity::set_gravity_strength(float strength) { gravity_strength = strength; }
float CustomGravity::get_gravity_strength() const { return gravity_strength; }

void CustomGravity::set_gravity_type(int type) { gravity_type = type; }
int CustomGravity::get_gravity_type() const { return gravity_type; }

void CustomGravity::apply_custom_gravity(JPH::PhysicsSystem* physics_system) {
    JPH::BodyInterface& body_interface = physics_system->GetBodyInterface();

    JPH::BodyIDVector active_bodies;
    physics_system->GetActiveBodies(active_bodies);

    for (JPH::BodyID id : active_bodies) {
        JPH::Body* body = body_interface.GetBody(id);
        if (!body || body->IsStatic())
            continue;

        Vector3 body_position = Vector3(body->GetPosition().GetX(), body->GetPosition().GetY(), body->GetPosition().GetZ());
        Vector3 gravity_force = compute_gravity_force(body_position);

        body_interface.AddForce(id, JPH::Vec3(gravity_force.x, gravity_force.y, gravity_force.z));
    }
}

Vector3 CustomGravity::compute_gravity_force(Vector3 position) {
    switch (gravity_type) {
        case 0: // Point Gravity (objects pulled toward center)
            return (gravity_center - position).normalized() * gravity_strength;
        case 1: // Directional Gravity (side-scroller style)
            return Vector3(0, -gravity_strength, 0);
        case 2: // Local Zones (different gravity rules)
            return (position.x > 0) ? Vector3(0, -gravity_strength, 0) : Vector3(0, gravity_strength, 0);
        default:
            return Vector3(0, -gravity_strength, 0);
    }
}
