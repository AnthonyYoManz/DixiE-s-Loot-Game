#ifndef ANT_HITBOX

#include <SFML/Graphics.hpp>

struct Collision{
    bool colliding;
    bool willCollide;
    sf::Vector2f translation;
};

class Hitbox{
protected:
    void getMinMaxProjectionsOnAxis(sf::Vector2f axis,
                                    sf::Vector2f* verts, float& minPos, float& maxPos,
                                    sf::Vector2f* otherVerts, float& otherMinPos, float& otherMaxPos);
    float getMinMaxDistance(float minPos, float maxPos, float otherMinPos, float otherMaxPos);
public:
    sf::Vector2f position;
    sf::Vector2f origin;
    sf::Vector2f dimensions;
    sf::Vector2f velocity;
    float rotation;

    void update(sf::Vector2f _position, float rotation = 0, sf::Vector2f _velocity = sf::Vector2f(0, 0));
    bool checkAABB(Hitbox other);
    sf::Vector2f* getVertices();
    sf::Vector2f getCenter();
    bool checkSAT(Hitbox other);
    Collision checkSweptSAT(Hitbox other);
    void draw(sf::RenderTarget& target);
};

#define ANT_HITBOX
#endif // ANT_HITBOX
