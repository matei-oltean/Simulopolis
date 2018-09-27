/* Simulopolis
 * Copyright (C) 2018 Pierre Vigier
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "render/RenderEngine.h"

RenderEngine::RenderEngine() : mWindow(sf::VideoMode(800, 600), "Simulopolis",
    sf::Style::Default, sf::ContextSettings(0, 0, 4))
{
    mWindow.setFramerateLimit(60);
}

RenderEngine::~RenderEngine()
{

}

sf::RenderWindow& RenderEngine::getWindow()
{
    return mWindow;
}

bool RenderEngine::isWindowOpen() const
{
    return mWindow.isOpen();
}

void RenderEngine::setIcon(const sf::Image& image)
{
    mWindow.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}

void RenderEngine::setFullscreen(bool fullscreen)
{
    mWindow.close();
    if (fullscreen)
        mWindow.create(sf::VideoMode::getFullscreenModes()[0], "Simulopolis",
            sf::Style::Fullscreen, sf::ContextSettings(0, 0, 4));
    else
        mWindow.create(sf::VideoMode(800, 600), "Simulopolis",
            sf::Style::Default, sf::ContextSettings(0, 0, 4));
}

void RenderEngine::closeWindow()
{
    mWindow.close();
}

sf::Vector2u RenderEngine::getViewportSize() const
{
    return mWindow.getSize();
}

const sf::View& RenderEngine::getView() const
{
    return mWindow.getView();
}

void RenderEngine::setView(const sf::View& view)
{
    mWindow.setView(view);
}

sf::Vector2f RenderEngine::mapPixelToCoords(const sf::Vector2i &point, const sf::View &view) const
{
    return mWindow.mapPixelToCoords(point, view);
}

void RenderEngine::clear()
{
    mWindow.clear();
}

void RenderEngine::draw(const sf::Drawable& drawable)
{
    mWindow.draw(drawable);
}

void RenderEngine::display()
{
    mWindow.display();
}
