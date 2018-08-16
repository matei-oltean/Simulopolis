#pragma once

#include <regex>
#include <SFML/System/Clock.hpp>
#include "gui/GuiWidget.h"

class GuiText;

class GuiInput : public GuiWidget
{
public:
    GuiInput(unsigned int characterSize, const XmlDocument* style);
    GuiInput(const PropertyList& properties);
    virtual ~GuiInput();

    virtual void setUp() override;
    const sf::String& getString() const;
    bool setString(const sf::String& text);
    virtual void setPosition(sf::Vector2f position) override;

    void setRegex(const std::string& s);

protected:
    virtual void render(sf::RenderTarget& target, sf::RenderStates states) const override;

    virtual bool onPress(sf::Vector2f position, bool processed) override;
    virtual bool onKey(sf::Keyboard::Key key, bool processed) override;
    virtual bool onText(sf::Uint32 unicode, bool processed) override;

private:
    bool mFocus;
    unsigned int mCharacterSize;
    GuiText* mText;
    std::size_t mCursor;
    sf::RectangleShape mCursorShape;
    mutable sf::Int32 mElapsedTime;
    mutable sf::Clock mClock;
    std::regex mRegex;

    void resetClock() const;
    void setCursor(std::size_t cursor);
    bool updateText(const sf::String& text);
    std::size_t mousePositionToCursor(sf::Vector2f position);
};
