#include <string>
#include "Vec2D.hpp"

const Vec2D g = Vec2D(0.0f, 9.8f);



class Particle2D : public sf::CircleShape {
public:
    /* Particle properties */
    std::string name;
    float mass;
    float radius;
    float diameter;
    float restitution;
    sf::Color color;

    /* Particle location parameters */
    Vec2D left;     // leftmost point of the particle
    Vec2D right;    // rightmost point of the particle
    Vec2D center;   // center of the particle
    Vec2D top;      // topmost point of the particle
    Vec2D bottom;   // bottommost point of the particle
    float height;   // height of the particle from the ground (as measured from bottom of window to bottom of particle: height = 600 - bottom.y)

    /* Particle image */
    sf::CircleShape image;

    /* Particle state */
    struct State {
        Vec2D position;
        Vec2D velocity;
        Vec2D momentum;
        Vec2D acceleration;
        float kineticEnergy;
        float potentialEnergy;
        float totalEnergy;
        void print();
    };  State state;
    

    /* Particle derivative */
    struct Derivative {
        Vec2D dpos;
        Vec2D dvel;
        Vec2D dmom;
    };  Derivative derivative;
    

    /* Constructors */
    Particle2D(std::string name);
    Particle2D(std::string name, float mass, float radius, sf::Color color, Vec2D position);
    Particle2D(std::string name, float mass, float radius, sf::Color color, Vec2D position, Vec2D velocity, Vec2D acceleration, float restitution);


    /* Particle methods */
    void draw(sf::RenderWindow& window);
    void update(float dt);
    
    float distanceTo(Particle2D& particle);
    bool overlapping(Particle2D& particle);

    /* Collision methods */
    Vec2D rotate(Vec2D velocity, float angle);      // Collision helper method
    void resolveCollision(Particle2D& particle);
    void handleWallCollisions();
    void handleParticleCollision();


private:
    /* Overloaded << for printing particle information */
    friend std::ostream& operator<<(std::ostream& os, const Particle2D& p)
    {
        os << std::endl << std::endl;
        os << "Particle2D \"" << p.name << "\":" << std::endl;
        os << "------------"; for (int i = 0; i < p.name.length()+2; i++) os << "-"; os << std::endl;
        os << "   > Mass: " << p.mass << std::endl;
        os << "   > Radius: " << p.radius << std::endl;
        os << "   > Center: " << p.center << std::endl;
        return os;
    }
};



/* Default Constructor */
Particle2D::Particle2D(std::string name) : sf::CircleShape()
{
    this->name = name;
    mass = 1.0f;
    radius = 10.0f;
    diameter = radius * 2.0f;
    color = sf::Color::White;

    // Initialize the State
    state.position = Vec2D(0.0, 0.0);
    state.velocity = Vec2D(0.0, 0.0);
    state.momentum = Vec2D(0.0, 0.0);
    state.acceleration = Vec2D(0.0, 0.0);
    state.kineticEnergy = 0.0;
    state.potentialEnergy = mass * g.y * (600 - state.position.y - diameter);
    state.totalEnergy = state.kineticEnergy + state.potentialEnergy;

    // Initialize the Derivative
    derivative.dpos = Vec2D(0.0, 0.0);
    derivative.dvel = Vec2D(0.0, 0.0);
    derivative.dmom = Vec2D(0.0, 0.0);

    // Initialize the image
    image.setRadius(radius);
    image.setPosition(state.position);
    image.setFillColor(color);

    // Initialize the particle's location parameters
    left = Vec2D(state.position.x, state.position.y + radius);
    right = Vec2D(state.position.x + diameter, state.position.y + radius);
    center = Vec2D(state.position.x + radius, state.position.y + radius);
    top = Vec2D(state.position.x + radius, state.position.y);
    bottom = Vec2D(state.position.x + radius, state.position.y + diameter);
    height = 600 - state.position.y - diameter;
}




/* Second Constructor */
Particle2D::Particle2D(std::string name, float mass, float radius, sf::Color color, Vec2D position) : sf::CircleShape()
{
    this->name = name;
    this->mass = mass;
    this->radius = radius;
    diameter = radius * 2.0f;
    this->color = color;
    height = 600 - position.y - diameter;

    // Initialize the State struct
    state.position = position;
    state.velocity = Vec2D(0.0, 0.0);
    state.momentum = Vec2D(0.0, 0.0);
    state.acceleration = Vec2D(0.0, 0.0);
    state.kineticEnergy = 0.0;
    state.potentialEnergy = mass * g.y * height;
    state.totalEnergy = state.kineticEnergy + state.potentialEnergy;

    // Initialize the Derivative struct
    derivative.dpos = Vec2D(0.0, 0.0);
    derivative.dvel = Vec2D(0.0, 0.0);
    derivative.dmom = Vec2D(0.0, 0.0);

    // Initialize the image
    image.setRadius(radius);
    image.setPosition(state.position);
    image.setFillColor(color);

    // Initialize the particle's location parameters
    left = Vec2D(state.position.x, state.position.y + radius);
    right = Vec2D(state.position.x + diameter, state.position.y + radius);
    center = Vec2D(state.position.x + radius, state.position.y + radius);
    top = Vec2D(state.position.x + radius, state.position.y);
    bottom = Vec2D(state.position.x + radius, state.position.y + diameter);
    
}




/* Third Constructor */
Particle2D::Particle2D(std::string name, float mass, float radius, sf::Color color, Vec2D position, Vec2D velocity, Vec2D acceleration, float restitution) : sf::CircleShape()
{
    this->name = name;
    this->mass = mass;
    this->radius = radius;
    diameter = radius * 2.0f;
    this->color = color;
    height = 600 - position.y - diameter;
    this->restitution = restitution;

    // Initialize the State struct
    state.position = position;
    state.velocity = velocity;
    state.momentum = mass * velocity;
    state.acceleration = acceleration;
    state.kineticEnergy = (mass/2) * (velocity.magnitude() * velocity.magnitude());
    state.potentialEnergy = mass * g.y * height;
    state.totalEnergy = state.kineticEnergy + state.potentialEnergy;

    // Initialize the Derivative struct
    derivative.dpos = Vec2D(0.0, 0.0);
    derivative.dvel = Vec2D(0.0, 0.0);
    derivative.dmom = Vec2D(0.0, 0.0);

    // Initialize the image
    image.setRadius(radius);
    image.setPosition(state.position);
    image.setFillColor(color);

    // Initialize the particle's location parameters
    left = Vec2D(state.position.x, state.position.y + radius);
    right = Vec2D(state.position.x + diameter, state.position.y + radius);
    center = Vec2D(state.position.x + radius, state.position.y + radius);
    top = Vec2D(state.position.x + radius, state.position.y);
    bottom = Vec2D(state.position.x + radius, state.position.y + diameter);
}




/* draw() method */
void Particle2D::draw(sf::RenderWindow& window)
{
    window.draw(image);
}



// Returns the distance from the center of this particle to the center of another particle
float Particle2D::distanceTo(Particle2D& p)
{
    float distance = (center - p.center).magnitude();
    return distance;
}




// Returns true if this particle is overlapping another particle (colliding)
bool Particle2D::overlapping(Particle2D& p)
{
    if (distanceTo(p) < (radius + p.radius)) { return true; }
    else { return false; }
}




/* State print() method */
void Particle2D::State::print()
{
    std::cout << "   > Position: " << position << std::endl;
    std::cout << "   > Velocity: " << velocity << std::endl;
    std::cout << "   > Momentum: " << momentum << std::endl;
    std::cout << "   > Acceleration: " << acceleration << std::endl;
    std::cout << "   > Kinetic Energy: " << kineticEnergy << std::endl;
    std::cout << "   > Potential Energy: " << potentialEnergy << std::endl;
    std::cout << "   > Total Energy: " << totalEnergy << std::endl << std::endl << std::endl;
}




// Helper function - Rotates coordinate system for velocities. 
//  Takes velocities and alters them as if the coordinate system they're on was rotated.
//  @param velocity: A velocity vector to be rotated.
//  @param angle: The angle of collision between two objects, in radians.
Vec2D Particle2D::rotate(Vec2D velocity, float angle)
{
    float x = (velocity.x * cos(angle)) - (velocity.y * sin(angle));
    float y = (velocity.x * sin(angle)) + (velocity.y * cos(angle));
    return Vec2D(x, y);
}



// Swaps out two colliding particle's x and y velocities
// after running through an elastic collision reaction equation.
//  @param particle: The particle this is colliding with.
void Particle2D::resolveCollision(Particle2D& particle)
{
    float dvx = state.velocity.x - particle.state.velocity.x;
    float dvy = state.velocity.y - particle.state.velocity.y;
    float dx = particle.state.position.x - state.position.x;
    float dy = particle.state.position.y - state.position.y;
    
    if (overlapping(particle))
    {
    // std::cout << std::endl << std::endl << "Collision!" << std::endl << std::endl;
    // Prevent accidental overlap of particles
    if (dvx * dx + dvy * dy >= 0) {
        // Get the angle between the two colliding particles
        float angle = -atan2(particle.state.position.y - state.position.y, particle.state.position.x - state.position.x);
        // Store masses of the two particles
        float m1 = mass;
        float m2 = particle.mass;
        // Velocity before collision
        Vec2D u1 = rotate(state.velocity, angle);
        Vec2D u2 = rotate(particle.state.velocity, angle);
        // Velocity after collision
        Vec2D v1 = Vec2D( (u1.x * (m1 - m2) / (m1 + m2)) + (u2.x * 2 * m2 / (m1 + m2)), u1.y );
        // Vec2D v2 = Vec2D( (u2.x * (m1 - m2) / (m1 + m2)) + (u1.x * 2 * m2 / (m1 + m2)), u2.y );
        Vec2D v2 = Vec2D( (u2.x * (m2 - m1) / (m1 + m2)) + (u1.x * 2 * m1 / (m1 + m2)), u2.y );
        // Rotate the velocities back to their original positions
        Vec2D v1final = rotate(v1, -angle) * restitution;
        Vec2D v2final = rotate(v2, -angle) * restitution;
        // Swap the velocities
        state.velocity = v1final;
        particle.state.velocity = v2final;
    }
    }
    // Calculate the angle of collision
    // float angle = atan2(particle.state.position.y - state.position.y, particle.state.position.x - state.position.x);
}




/* Method for reacting to walls */
void Particle2D::handleWallCollisions()
{
    if (state.position.y > (600.0f - diameter)) {
        std::cout << "Collision with bottom wall! Object diameter = " << diameter << std::endl;
        state.position.y = 600.0f - diameter - 0.1f;
        height = 600 - state.position.y - diameter;
        state.velocity.y = -state.velocity.y;
    }
    if (state.position.y < 0.0f) {
        std::cout << "Collision with top wall! Object diameter = " << diameter << std::endl;
        state.position.y = 0.1f;
        height = 600 - state.position.y - diameter;
        state.velocity.y = -state.velocity.y;
    }
    if (left.x < 0.0f) {
        std::cout << "Collision with left wall! Object diameter = " << diameter << std::endl;
        state.position.x = 0.1f;
        state.velocity.x = -state.velocity.x;
    }
    if (right.x > 800.0f) {
        std::cout << "Collision with right wall! Object diameter = " << diameter << std::endl;
        state.position.x = 799.9f - diameter;
        state.velocity.x = -state.velocity.x;
    }
}




/* Particle update method */
void Particle2D::update(float dt)
{
    // Update the state
    state.position += state.velocity * dt;
    height = 600.0f - state.position.y - diameter;

    handleWallCollisions();

    state.velocity += state.acceleration * dt;
    state.momentum = mass * state.velocity;
    state.kineticEnergy = (mass/2) * (state.velocity.magnitude() * state.velocity.magnitude());
    state.potentialEnergy = mass * g.y * height;
    state.totalEnergy = state.kineticEnergy + state.potentialEnergy;

    // Update the image
    image.setPosition(state.position);

    // Update the particle's location parameters
    height = 600 - state.position.y - diameter;
    left = Vec2D(state.position.x, state.position.y + radius);
    right = Vec2D(state.position.x + diameter, state.position.y + radius);
    center = Vec2D(state.position.x + radius, state.position.y + radius);
    top = Vec2D(state.position.x + radius, state.position.y);
    bottom = Vec2D(state.position.x + radius, state.position.y + diameter);
}