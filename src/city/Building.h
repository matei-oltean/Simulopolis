#pragma once

#include <vector>
#include "city/Tile.h"

class Person;
class Company;

class Building : public Tile
{
public:
    struct Owner
    {
        enum class Type{CITY, PERSON, COMPANY};

        Type type;
        union
        {
            Person* person;
            Company* company;
        };

        std::string toString() const;
    };

    static constexpr int STAIR_HEIGHT = 33;
    static constexpr int OFFSET_Y = 27;

    Building(const std::string& name, Type type, unsigned int nbStairs);
    virtual ~Building();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual bool intersect(const sf::Vector2f& position) const override;

    virtual std::unique_ptr<Tile> clone() const override;

    virtual bool updateVariant(const Tile* neighbors[3][3]) override;

    sf::Vector2f getPosition() const;
    virtual void setPosition(sf::Vector2i coordinates, sf::Vector2f position) override;
    const Owner& getOwner() const;
    void setOwner(Owner owner);
    virtual sf::FloatRect getBounds() const override;

protected:
    unsigned int mNbStairs;
    Owner mOwner;
};
