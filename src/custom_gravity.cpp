#include "custom_gravity.h"

#include <godot_cpp/classes/physics_direct_body_state2d.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

CustomGravity::CustomGravity() : gravity_strength(10.0f), gravity_mode(0) {}

CustomGravity::~CustomGravity() {}

void CustomGravity::set_gravity_strength(float p_strength) {
    gravity_strength = p_strength;
}

float CustomGravity::get_gravity_strength() const {
    return gravity_strength;
}

void CustomGravity::set_gravity_center(const Vector2 &p_center) {
    gravity_center = p_center;
}

Vector2 CustomGravity::get_gravity_center() const {
    return gravity_center;
}

void CustomGravity::set_gravity_mode(int mode) {
    gravity_mode = mode;
}

int CustomGravity::get_gravity_mode() const {
    return gravity_mode;
}

void CustomGravity::_integrate_forces(PhysicsDirectBodyState2D *state) {
    Vector2 position = state->get_transform().get_origin();
    Vector2 gravity_force = compute_gravity_force(position);

    state->apply_force(gravity_force);
}

Vector2 CustomGravity::compute_gravity_force(Vector2 position) {
    switch (gravity_mode) {
        case 0: return Vector2(0, gravity_strength * -1); // Local gravity (downward)
        case 1: return (gravity_center - position).normalized() * gravity_strength; // Radial gravity (toward center)
        case 2: return Vector2(gravity_strength * (position.x > 0 ? -1 : 1), 0); // Local Zones (left/right gravity)
        default: return Vector2(0, gravity_strength * -1);
    }
}

void CustomGravity::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_gravity_strength", "strength"), &CustomGravity::set_gravity_strength);
    ClassDB::bind_method(D_METHOD("get_gravity_strength"), &CustomGravity::get_gravity_strength);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gravity_strength"), "set_gravity_strength", "get_gravity_strength");

    ClassDB::bind_method(D_METHOD("set_gravity_center", "center"), &CustomGravity::set_gravity_center);
    ClassDB::bind_method(D_METHOD("get_gravity_center"), &CustomGravity::get_gravity_center);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "gravity_center"), "set_gravity_center", "get_gravity_center");

    ClassDB::bind_method(D_METHOD("set_gravity_mode", "mode"), &CustomGravity::set_gravity_mode);
    ClassDB::bind_method(D_METHOD("get_gravity_mode"), &CustomGravity::get_gravity_mode);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "gravity_mode", PROPERTY_HINT_ENUM, "Local,Radial,Point"), "set_gravity_mode", "get_gravity_mode");
}
