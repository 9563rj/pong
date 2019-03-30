#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


int WindowX = 1280;
int WindowY = 720;
int ballRadius = 25;
int CenterX = WindowX/2;
int CenterY = WindowY/2;

int main()
{
  sf::RenderWindow window(sf::VideoMode(WindowX, WindowY), "Pong v0");
  sf::CircleShape shape(ballRadius);
  shape.setFillColor(sf::Color::White);
  shape.setPosition(CenterX-ballRadius,CenterY-ballRadius);
    while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
        {
	  if (event.type == sf::Event::Closed)
	    window.close();
        }

      window.clear();
      window.draw(shape);
      window.display();
    }

  return 0;
}
