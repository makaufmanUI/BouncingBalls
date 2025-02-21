#include <iostream>
#include "Particle2D.hpp"



void print(Particle2D& particle)
{
    std::cout << particle;
    particle.state.print();
}

void print(Particle2D& particle, int n, const int fps)
{
    if (n % fps == 0)
        print(particle);
}



// Loops through all particles and calls their resolveCollision() function to resolve their collisions.
void resolveCollisions(std::vector<Particle2D>& particles)
{
    for (int i = 0; i < particles.size(); i++)
        for (int j = 0; j < particles.size(); j++)
            if (i != j)
                particles[i].resolveCollision(particles[j]);
}



// Loops through all particles and calls their update() and draw() methods.
void update(std::vector<Particle2D>& particles, const float dt, sf::RenderWindow& window, int n, const int fps)
{
    float completeEnergy = 0.0f;
    for (auto& particle : particles)
    {
        particle.update(dt);
        particle.draw(window);
        print(particle, n, fps);
        completeEnergy += particle.state.totalEnergy;
    }
    if (n % fps == 0)
        std::cout << std::endl << std::endl << "Total Energy: " << completeEnergy << std::endl << std::endl << std::endl;
}






// Advances the physics state ahead from t to t+dt using one set of derivatives,
// and once there, recalculates the derivatives at this new state.
Particle2D::Derivative evaluate(const Particle2D::State& initial, double t, float dt, const Particle2D::Derivative& d)
{
    Particle2D::State state;
    state.position = initial.position - d.dpos * dt;
    state.velocity = initial.velocity - d.dvel * dt;

    Particle2D::Derivative output;
    output.dpos = state.velocity;
    output.dvel = g;

    return output;
}


// Samples the derivative at four points to detect curvative,
// then the best overall derivative is calculated as a weighted sum derived from the Taylor Series expansion.
void integrate(Particle2D::State& state, double t, float dt, Particle2D& particle)
{
    Particle2D::Derivative a, b, c, d;

    a = evaluate(state, t, 0.0f, Particle2D::Derivative());
    b = evaluate(state, t, dt*0.5f, a);
    c = evaluate(state, t, dt*0.5f, b);
    d = evaluate(state, t, dt, c);

    float w = 1.0f/6.0f;
    Vec2D x = 2.0f * (b.dpos + c.dpos);
    Vec2D z = a.dpos + x + d.dpos;
    Vec2D dposdt = w * z;

    Vec2D h = 2.0f * (b.dvel + c.dvel);
    Vec2D j = a.dvel + h + d.dvel;
    Vec2D dveldt = w * j;

    state.position = state.position + dposdt * dt;

    if (state.position.y > (600.0f - particle.diameter)) {
        state.position.y = 600.0f - particle.diameter - 0.1f;
        particle.height = 600 - state.position.y - particle.diameter;
        state.velocity.y = -state.velocity.y;
    }
    if (state.position.y < 0.0f) {
        state.position.y = 0.1f;
        particle.height = 600 - state.position.y - particle.diameter;
        state.velocity.y = -state.velocity.y;
    }
    if (particle.left.x < 0.0f) {
        state.position.x = 0.1f;
        state.velocity.x = -state.velocity.x;
    }
    if (particle.right.x > 800.0f) {
        state.position.x = 799.9f - particle.diameter;
        state.velocity.x = -state.velocity.x;
    }

    state.velocity = state.velocity + dveldt * dt;
}



void updateRK(Particle2D::State& state, double t, float dt, Particle2D& particle)
{
    integrate(state, t, dt, particle);
    particle.height = 600 - state.position.y - particle.diameter;
    state.momentum = particle.mass * state.velocity;
    state.kineticEnergy = (particle.mass/2) * (state.velocity.magnitude() * state.velocity.magnitude());
    state.potentialEnergy = particle.mass * g.y * particle.height;
    state.totalEnergy = state.kineticEnergy + state.potentialEnergy;

    // Update the image
    particle.image.setPosition(state.position);

    // Update the particle's location parameters
    particle.left = Vec2D(state.position.x, state.position.y + particle.radius);
    particle.right = Vec2D(state.position.x + particle.diameter, state.position.y + particle.radius);
    particle.center = Vec2D(state.position.x + particle.radius, state.position.y + particle.radius);
    particle.top = Vec2D(state.position.x + particle.radius, state.position.y);
    particle.bottom = Vec2D(state.position.x + particle.radius, state.position.y + particle.diameter);
}



// Loops through all particles and calls the updateRK() function to update their states via the Runge-Kutta method.
void updateRK(std::vector<Particle2D>& particles, double t, float dt, sf::RenderWindow& window, int n, const int fps)
{
    float completeEnergy = 0.0f;
    for (auto& particle : particles)
    {
        updateRK(particle.state, t, dt, particle);
        particle.draw(window);
        print(particle, n, fps);
        completeEnergy += particle.state.totalEnergy;
    }
    if (n % fps == 0)
        std::cout << std::endl << std::endl << "Total Energy: " << completeEnergy << std::endl << std::endl << std::endl;
}