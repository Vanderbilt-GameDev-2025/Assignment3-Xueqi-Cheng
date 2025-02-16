#include "spin_physics.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>

using namespace godot;

// Constructor
SpinPhysics::SpinPhysics() {
    angular_velocity = 2.0f;
}

// Destructor
SpinPhysics::~SpinPhysics() {
}

// Bind methods to Godot
void SpinPhysics::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_angular_velocity", "velocity"), &SpinPhysics::set_angular_velocity);
    ClassDB::bind_method(D_METHOD("get_angular_velocity"), &SpinPhysics::get_angular_velocity);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_velocity"), "set_angular_velocity", "get_angular_velocity");
}

// Process method called every frame
void SpinPhysics::_process(double delta) { // Use 'double' instead of 'float'
    // Apply rotation based on angular velocity
    rotate(angular_velocity * delta);

    // Example: Adjust angular velocity dynamically via input (optional)
    if (Input::get_singleton()->is_action_pressed("ui_left")) {
        angular_velocity -= 1.0f * delta; // Spin counterclockwise
    }
    if (Input::get_singleton()->is_action_pressed("ui_right")) {
        angular_velocity += 1.0f * delta; // Spin clockwise
    }
}

// Setter for angular velocity
void SpinPhysics::set_angular_velocity(float velocity) {
    angular_velocity = velocity;
}

// Getter for angular velocity
float SpinPhysics::get_angular_velocity() const {
    return angular_velocity;
}
