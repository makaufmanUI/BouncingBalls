#include <vector>
#include "src/sim/Utils.hpp"
#include "src/sim/Events.hpp"

const int W = 800;
const int H = 600;

const int FPS = 60;
float dt = 5.0f / FPS;



int main()
{
    sf::RenderWindow window(sf::VideoMode(W,H), "Bouncing Balls");
    window.setFramerateLimit(FPS);

    std::vector<Particle2D> particles;

    Particle2D testParticle = Particle2D("Test Particle 1", 1.0f, 10.0f, sf::Color::Blue, Vec2D(90.0f, 50.0f), Vec2D(60.0f, 50.0f), g, 0.99825f);
    Particle2D testParticle2 = Particle2D("Test Particle 2", 1.0f, 10.0f, sf::Color::Red, Vec2D(100.0f, 100.0f), Vec2D(0.0f, -50.0f), g, 0.99825f);
    Particle2D testParticle3 = Particle2D("Test Particle 3", 2.0f, 15.0f, sf::Color::Green, Vec2D(200.0f, 200.0f), Vec2D(30.0f, 0.0f), g, 0.99825f);
    Particle2D testParticle4 = Particle2D("Test Particle 4", 2.0f, 15.0f, sf::Color::Magenta, Vec2D(300.0f, 300.0f), Vec2D(0.0f, 0.0f), g, 0.99825f);
    Particle2D testParticle5 = Particle2D("Test Particle 5", 4.0f, 20.0f, sf::Color::Cyan, Vec2D(400.0f, 400.0f), Vec2D(0.0f, 0.0f), g, 0.99825f);
    Particle2D testParticle6 = Particle2D("Test Particle 6", 4.0f, 20.0f, sf::Color::Yellow, Vec2D(500.0f, 500.0f), Vec2D(0.0f, 0.0f), g, 0.99825f);
    Particle2D testParticle7 = Particle2D("Test Particle 7", 1.0f, 10.0f, sf::Color::Blue, Vec2D(90.0f, 50.0f), Vec2D(10.0f, 50.0f), g, 0.99825f);
    Particle2D testParticle8 = Particle2D("Test Particle 8", 1.0f, 10.0f, sf::Color::Red, Vec2D(100.0f, 100.0f), Vec2D(-5.0f, 0.0f), g, 0.99825f);
    Particle2D testParticle9 = Particle2D("Test Particle 9", 2.0f, 15.0f, sf::Color::Green, Vec2D(150.0f, 50.0f), Vec2D(42.0f, 0.0f), g, 0.99825f);
    Particle2D testParticle10 = Particle2D("Test Particle 10", 2.0f, 15.0f, sf::Color::Magenta, Vec2D(200.0f, 60.0f), Vec2D(0.0f, 0.0f), g, 0.99825f);
    // Particle2D testParticle11 = Particle2D("Test Particle 11", 4.0f, 20.0f, sf::Color::Cyan, Vec2D(250.0f, 150.0f), Vec2D(0.0f, 0.0f), g, 0.99825f);
    // Particle2D testParticle12 = Particle2D("Test Particle 12", 4.0f, 20.0f, sf::Color::Yellow, Vec2D(350.0f, 350.0f), Vec2D(0.0f, 0.0f), g, 0.99825f);
    Particle2D testParticle13 = Particle2D("Test Particle 13", 1.0f, 10.0f, sf::Color::Blue, Vec2D(90.0f, 50.0f), Vec2D(60.0f, 50.0f), g, 0.99825f);
    Particle2D testParticle14 = Particle2D("Test Particle 14", 1.0f, 10.0f, sf::Color::Red, Vec2D(125.0f, 100.0f), Vec2D(80.0f, -50.0f), g, 0.99825f);
    Particle2D testParticle15 = Particle2D("Test Particle 15", 2.0f, 15.0f, sf::Color::Green, Vec2D(215.0f, 200.0f), Vec2D(30.0f, 70.0f), g, 0.99825f);
    Particle2D testParticle16 = Particle2D("Test Particle 16", 2.0f, 15.0f, sf::Color::Magenta, Vec2D(540.0f, 300.0f), Vec2D(0.0f, 55.0f), g, 0.99825f);
    Particle2D testParticle17 = Particle2D("Test Particle 17", 1.0f, 10.0f, sf::Color::Blue, Vec2D(90.0f, 50.0f), Vec2D(10.0f, 50.0f), g, 0.99825f);
    Particle2D testParticle18 = Particle2D("Test Particle 18", 1.0f, 10.0f, sf::Color::Red, Vec2D(100.0f, 100.0f), Vec2D(-5.0f, 0.0f), g, 0.99825f);

    particles.push_back(testParticle);
    particles.push_back(testParticle2);
    particles.push_back(testParticle3);
    particles.push_back(testParticle4);
    particles.push_back(testParticle5);
    particles.push_back(testParticle6);
    particles.push_back(testParticle7);
    particles.push_back(testParticle8);
    particles.push_back(testParticle9);
    particles.push_back(testParticle10);
    // particles.push_back(testParticle11);
    // particles.push_back(testParticle12);
    particles.push_back(testParticle13);
    particles.push_back(testParticle14);
    particles.push_back(testParticle15);
    particles.push_back(testParticle16);
    particles.push_back(testParticle17);
    particles.push_back(testParticle18);

    int iter = 0;
    double t = 0.0;

    while (window.isOpen())
    {
        event::CheckForClose(window);
        window.clear();

        resolveCollisions(particles);
        // update(particles, dt, window, iter, FPS*5);
        updateRK(particles, t, dt, window, iter, FPS*50);

        window.display();
        t += dt;
        iter+=1;
    }


    return EXIT_SUCCESS;
}
