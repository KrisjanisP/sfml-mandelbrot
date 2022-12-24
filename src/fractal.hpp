#include <SFML/Graphics.hpp>

class Fractal final : public sf::Drawable, public sf::Transformable
{
public:
    float getZoom();
    void setZoom(float zoom);
    
    float getPrecision();
    void setPrecision(float precision);

    void recenterView(float x, float y);
    sf::Vector2f getViewCenter();
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
