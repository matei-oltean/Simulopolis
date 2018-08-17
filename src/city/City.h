#pragma once

#include <vector>
#include <memory>
#include "message/Subject.h"
#include "pcg/PersonGenerator.h"
#include "pcg/CompanyGenerator.h"
#include "city/Map.h"
#include "city/Market.h"

class Building;

class City : public sf::Drawable, public Subject
{
public:
    static constexpr float NB_HOURS_PER_MONTH = 30.0f * 24.0f;

    struct Intersection
    {
        enum class Type{NONE, CAR, BUILDING};

        Type type;
        union
        {
            const Car* car;
            const Building* building;
        };

        Intersection();
        Intersection(const Car* car);
        Intersection(const Building* building);
    };

    struct Event
    {
        enum class Type{NEW_MONTH, NEW_YEAR, NEW_IMMIGRANT};

        Type type;
        union
        {
            unsigned int month;
            unsigned int year;
            Person* person;
        };
    };

    City();

    void load(const std::string& name);
    void save(const std::string& name);
    void createMap(const Array2<Tile::Type>& tiles);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Map
    void update(float dt);
    void bulldoze(Tile::Type type);
    Intersection intersect(const sf::Vector2f& position);
    Map& getMap();
    const Map& getMap() const;

    // Date
    unsigned int getMonth() const;
    unsigned int getYear() const;
    std::string getFormattedMonth() const;

    // Company
    Company& getCompany();
    unsigned int getFunds() const;
    void decreaseFunds(unsigned int amount);

    // Policy
    unsigned int getWeeklyStandardWorkingHours() const;
    void setWeeklyStandardWorkingHours(unsigned int weeklyStandardWorkingHours);
    Money getMinimumWage() const;
    void setMinimumWage(Money minimumWage);
    float getIncomeTax() const;
    void setIncomeTax(float incomeTax);
    float getCorporateTax() const;
    void setCorporateTax(float corporateTax);

    // Agents
    void eject(Person* person);
    void welcome(Person* person);
    unsigned int getPopulation() const;
    unsigned int getUnemployed() const;
    Person* getPerson(Id id);
    const std::vector<Person*>& getCitizens() const;
    const std::vector<Person*>& getImmigrants() const;
    Building* getBuilding(Id id);
    VMarket* getMarket(VMarket::Type type);

    // Util
    sf::Vector2i toTileIndices(const sf::Vector2f& position) const;
    float toHumanTime(float cityTime) const; // cityTime is expressed in hours
    float toCityTime(float humanTime) const;

private:
    // Generators
    PersonGenerator mPersonGenerator;
    CompanyGenerator mCompanyGenerator;

    // Map
    Map mMap;

    // Date
    float mCurrentTime;
    float mTimePerMonth;
    unsigned int mMonth;
    unsigned int mYear;

    // Company
    unsigned int mUnemployed;
    unsigned int mFunds;
    Company mCityCompany;

    // Policy
    unsigned int mWeeklyStandardWorkingHours;
    Money mMinimumWage;
    float mIncomeTax;
    float mCorporateTax;

    // Agents
    IdManager<std::unique_ptr<Person>> mPersons;
    std::vector<Person*> mCitizens;
    std::vector<Person*> mImmigrants;
    std::vector<std::unique_ptr<Company>> mCompanies;
    IdManager<Building*> mBuildings;
    std::vector<std::unique_ptr<VMarket>> mMarkets;
    Array2<std::vector<const Car*>> mCarsByTile;

    void generateImmigrant();
    void removeCitizen(Person* person);

    // Events
    void onNewMonth();
    void onNewYear();
};

