#include <SFML/Graphics.hpp>

class Fractal final : public sf::Drawable, public sf::Transformable
{
public:
    Fractal(int width, int height);

    float getZoom();
    void setZoom(float zoom);
    
    float getPrecision();
    void setPrecision(float precision);

    void setPlaneCenter(float x, float y);
    void getPixelCoords(int px, int py, float& x, float& y) const;

    void setViewSize(int width, int heihgt);
private:
    int viewWidth, viewHeight;
    float planeCenterX, planeCenterY;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
