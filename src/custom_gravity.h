#ifndef CUSTOM_GRAVITY_H
#define CUSTOM_GRAVITY_H

#include <godot_cpp/classes/rigid_body2d.hpp>
#include <godot_cpp/classes/physics_direct_body_state2d.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {

class CustomGravity : public RigidBody2D {
    GDCLASS(CustomGravity, RigidBody2D);

protected:
    static void _bind_methods(); // Bind methods for Godot's editor

private:
    // === Gravity Properties ===
    float gravity_strength = 10.0f;  // Magnitude of gravity force
    Vector2 gravity_center = Vector2(0, 0);  // Gravity origin point
    int gravity_mode = 0;  // 0: Local, 1: Radial, 2: Point

public:
    // === Constructors / Destructor ===
    CustomGravity();
    ~CustomGravity();

    // === Gravity Configuration ===
    void set_gravity_strength(float strength);
    float get_gravity_strength() const;

    void set_gravity_center(const Vector2 &center);
    Vector2 get_gravity_center() const;

    void set_gravity_mode(int mode);
    int get_gravity_mode() const;

    // === Physics Integration ===
    void _integrate_forces(PhysicsDirectBodyState2D *state) override;

    // === Gravity Computation ===
    Vector2 compute_gravity_force(Vector2 position);
};

} // namespace godot

#endif // CUSTOM_GRAVITY_H

