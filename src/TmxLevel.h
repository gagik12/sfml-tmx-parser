#pragma once

#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

// В картах TMX объект - это область на карте, имеющая имя, тип,
//  границы, набор пользовательских свойств (в формате ключ-значение)
//  и текстурные координаты.
// Текстурные координаты позволяют связать с объектом спрайт,
//  использующий основную текстуру карты как источник данных.
struct TmxObject
{
    int GetPropertyInt(std::string name);
    float GetPropertyFloat(std::string name);
    std::string GetPropertyString(std::string name);

    void MoveBy(const sf::Vector2f &movement);
    void MoveTo(const sf::Vector2f &position);

    std::string name;
    std::string type;
    sf::IntRect rect;
    std::map<std::string, std::string> properties;

	sf::Sprite sprite;
};

// В картах TMX слой - это набор тайлов (спрайтов),
//  из которых складывается ландшафт карты.
// Слоёв может быть несколько, что позволяет нарисовать,
//  например, слой травы поверх слоя земли.
struct TmxLayer
{
    int opacity = 0;
    std::vector<sf::Sprite> tiles;
};

class TmxLevel
{
public:
    bool LoadFromFile(const std::string &filepath);

    TmxObject GetObject(const std::string &name)const;
    std::vector<TmxObject> GetObjects(const std::string &name)const;
    sf::Vector2i GetTileSize()const;

    // Принимает любую цель для рисования, например, sf::RenderWindow.
    void Draw(sf::RenderTarget &target)const;

private:
    int m_width = 0;
    int m_height = 0;
    int m_tileWidth = 0;
    int m_tileHeight = 0;
    int m_firstTileID = 0;
    sf::Texture m_tilesetImage;
    std::vector<TmxObject> m_objects;
    std::vector<TmxLayer> m_layers;
};
