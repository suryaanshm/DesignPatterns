#include <iostream>
#include <string>
#include <unordered_map>

// Base class representing individual particles
class Particle {
public:
    Particle(const std::string& color, const std::string& sprite)
        : color_(color), sprite_(sprite) {}

    // Method to display particle information
    virtual void display(int x, int y) const {
        std::cout << "Particle: Color=" << color_ << ", Sprite=" << sprite_ << ", Position=(" << x << ", " << y << ")" << std::endl;
    }

protected:
    std::string color_;
    std::string sprite_;
};

// Derived classes for specific types of particles
class Bullet : public Particle {
public:
    Bullet() : Particle("Red", "BulletSprite") {}
};

class Missile : public Particle {
public:
    Missile() : Particle("Green", "MissileSprite") {}
};

class Shrapnel : public Particle {
public:
    Shrapnel() : Particle("Blue", "ShrapnelSprite") {}
};

// ParticleFactory class to manage creation and sharing of particles
class ParticleFactory {
public:
    // Get a particle of a specific type
    static Particle* getParticle(const std::string& type) {
        // Check if the particle type already exists in the cache
        auto it = particleCache_.find(type);
        if (it != particleCache_.end()) {
            // If found, return the cached particle
            return it->second;
        } else {
            // If not found, create a new particle of the specified type and cache it
            Particle* particle = nullptr;
            if (type == "Bullet") {
                particle = new Bullet();
            } else if (type == "Missile") {
                particle = new Missile();
            } else if (type == "Shrapnel") {
                particle = new Shrapnel();
            }
            particleCache_[type] = particle;
            return particle;
        }
    }

private:
    // Static cache to store shared particles
    static std::unordered_map<std::string, Particle*> particleCache_;
};

// Static initialization of particle cache
std::unordered_map<std::string, Particle*> ParticleFactory::particleCache_;

int main() {
    // Create some particles using the ParticleFactory
    Particle* bullet = ParticleFactory::getParticle("Bullet");
    Particle* missile = ParticleFactory::getParticle("Missile");
    Particle* shrapnel = ParticleFactory::getParticle("Shrapnel");

    // Display particle information with different coordinates
    bullet->display(10, 20);
    missile->display(30, 40);
    shrapnel->display(50, 60);

    // Clean up allocated memory
    delete bullet;
    delete missile;
    delete shrapnel;

    return 0;
}
