#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


int WindowX = 1280;
int WindowY = 720;
int ballRadius = 25;
int CenterX = WindowX/2;
int CenterY = WindowY/2;
sf::Vector2f ballPos;

int main()
{
  // Create window
  sf::RenderWindow window(sf::VideoMode(WindowX, WindowY), "Pong v0.1");

  // Initialize ball
  sf::CircleShape shape(ballRadius);
  shape.setFillColor(sf::Color::White);
  shape.setPosition(CenterX-ballRadius,CenterY-ballRadius);

  // Main game loop
  while (window.isOpen())
    {
      // Initialize event
      sf::Event event;

      // Move ball left 1 pixel every frame
      shape.move(-.1,0.f);
      
      // Check for window closure
      while (window.pollEvent(event))
        {
	  if (event.type == sf::Event::Closed)
	    window.close();
        }

      // Frame update, update ball position variable
      window.clear();
      window.draw(shape);
      window.display();
      ballPos = shape.getPosition();
    }
  return 0;
}
