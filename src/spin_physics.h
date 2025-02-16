#ifndef SPIN_PHYSICS_H
#define SPIN_PHYSICS_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {

class SpinPhysics : public Node2D {
    GDCLASS(SpinPhysics, Node2D);

private:
    float angular_velocity = 2.0f; // Angular velocity in radians per second

protected:
    static void _bind_methods(); // Binding methods for Godot

public:
    SpinPhysics();  // Constructor
    ~SpinPhysics(); // Destructor

    void _process(double delta) override; // Use 'double' instead of 'float'

    // Setter and Getter for angular velocity
    void set_angular_velocity(float velocity);
    float get_angular_velocity() const;
};

} // namespace godot

#endif // SPIN_PHYSICS_H
