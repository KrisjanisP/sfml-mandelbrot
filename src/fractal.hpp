#include <SFML/Graphics.hpp>
#include <vector>

typedef unsigned int uint;

const uint COLORS = 64;

class Fractal final : public sf::Drawable
{
public:
    const uint WIDTH;
    const uint HEIGHT;

    explicit Fractal(uint width,uint height);
    void scale(int levels);
    void recenterView(float x, float y);
    void alterPrecision(float multiplier);
    void getViewCoords(int screenX, int screenY, float res[2]);
    void setSpriteOffset(int screenX, int screenY);
    float getViewZoom();
    int getPrecision();
private:
    float viewMaxWidth = 2, viewMaxHeight = 2;
    float viewZoom = 1;
    float viewX = -0.7, viewY = 0;
    float viewWidth = 2, viewHeight = 2;
    int precision = 16;
    std::vector<sf::Uint8> pixels;
    sf::Texture texture;
    sf::Sprite sprite;
    void generate(uint tl[2], uint br[2]);
    void regenerate();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void getColors(int iters, sf::Uint8 rgb[3], float x, float y);
    sf::Uint8 colors[COLORS][3];
    void precomputeColors();
};
