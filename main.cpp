#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// Initialize/declare global variables
int WindowX = 1280;
int WindowY = 720;
int ballRadius = 25;
int CenterX = WindowX/2;
int CenterY = WindowY/2;
sf::Vector2f ballPos;

int main()
{
  // Create window
  sf::RenderWindow window(sf::VideoMode(WindowX, WindowY), "Pong v0.2.1");

  // Initialize ball
  sf::CircleShape shape(ballRadius);
  shape.setFillColor(sf::Color::White);
  ballPos.x = CenterX-ballRadius;
  ballPos.y = CenterY-ballRadius;
  shape.setPosition(ballPos);

  // Initialize motion vector
  sf::Vector2f ballMotion;
  ballMotion.x = -.1;
  ballMotion.y = .05;

  // Main game loop
  while (window.isOpen())
    {
      // Initialize event
      sf::Event event;

      // Move ball left, then when it hits the left side, bounce it right, when it hits right bounce left, etc
      // Update the ball
      ballPos+=ballMotion;
      shape.setPosition(ballPos);

      // Invert motion vector when it hits LEFT edge
      if (ballPos.x <= 0.f)
	{
	  ballPos.x = 0;
	  shape.setPosition(ballPos);
	  std::cout << "Reversing velocity. Postion is " << ballPos.x << std::endl;
	  ballMotion.x = -ballMotion.x;
	}
      // Invert motion vector when it hits RIGHT edge
      if (ballPos.x >= 1280.f-ballRadius*2)
	{
	  ballPos.x = 1280-ballRadius*2;
	  shape.setPosition(ballPos);
	  std::cout << "Reversing velocity. Postion is " << ballPos.x << std::endl;
	  ballMotion.x = -ballMotion.x;
	}
      // Invert motion vector when it hits BOTTOM
      if (ballPos.y >= 720-ballRadius*2)
	{
	  ballPos.y = 720-ballRadius*2;
	  shape.setPosition(ballPos);
	  std::cout << "Reversing velocity. Position is " << ballPos.y << std::endl;
	  ballMotion.y = -ballMotion.y;
	}
      // Invert motion vector when it hits TOP
      if (ballPos.y <= 0)
	{
	  ballPos.y = 0;
	  shape.setPosition(ballPos);
	  std::cout << "Reversing velocity Position is " << ballPos.y << std::endl;
	  ballMotion.y = -ballMotion.y;
	}

      
      
      // Check for window closure
      while (window.pollEvent(event))
        {
	  if (event.type == sf::Event::Closed)
	    window.close();
        }

      // Frame update
      window.clear();
      window.draw(shape);
      window.display();
    }
  return 0;
}
