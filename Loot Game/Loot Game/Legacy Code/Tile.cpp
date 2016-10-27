#include "tile.h"

void Tile::initialise(Game* _game, Scene* _scene, unsigned int _handle, sf::Vector2f _position){
    game = _game;
    scene = _scene;
    handle = _handle;
    position = _position;
    hitbox.dimensions = sf::Vector2f(150, 150);
    hitbox.update(position, 45, sf::Vector2f(0, 0));
    tags = OBJECT_TERRAIN;
}


void Tile::draw(sf::RenderTarget& target){
    sf::RectangleShape rect;
    rect.setPosition(position);
    rect.setRotation(-45);
    rect.setSize(hitbox.dimensions);
    target.draw(rect);
}
