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
sf::Vector2f ballMotion;
sf::Vector2f lpaddlePos;
sf::Vector2f rpaddlePos;
sf::Vector2f paddleDown;
sf::Vector2f paddleUp;
bool qKeyPressed;
bool aKeyPressed;

// Function area

void frameUpdate(sf::RenderWindow& window,sf::CircleShape& shape,sf::RectangleShape& lpaddle)
{
  window.clear();
  window.draw(shape);
  window.draw(lpaddle);
  window.display();
}

int main()
{
  // Create window
  sf::RenderWindow window(sf::VideoMode(WindowX, WindowY), "Pong v0.3");

  // Initialize ball
  sf::CircleShape shape(ballRadius);
  shape.setFillColor(sf::Color::White);
  ballPos.x = CenterX-ballRadius;
  ballPos.y = CenterY-ballRadius;
  shape.setPosition(ballPos);

  // Initialize left paddle
  sf::RectangleShape lpaddle(sf::Vector2f(10.f,100.f));
  lpaddle.setFillColor(sf::Color::White);
  lpaddlePos.x = WindowX/16;
  lpaddlePos.y = WindowY/2;
  lpaddle.setPosition(lpaddlePos);
  
  // Initialize motion vector
  ballMotion.x = -.1;
  ballMotion.y = .05;
  // Initialize paddle movement vectors
  paddleDown.x = 0;
  paddleDown.y = 5;
  paddleUp.x = 0;
  paddleUp.y = -5;

  
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
      
      // Event handler loop
      while (window.pollEvent(event))
        {
	  aKeyPressed = false;
	  qKeyPressed = false;
	  // lpaddle movement
	  if (event.type == sf::Event::KeyPressed)
	    {
	      if (event.key.code == sf::Keyboard::Q) {qKeyPressed = true;}
	      if (event.key.code == sf::Keyboard::A) {aKeyPressed = true;}
	      if (qKeyPressed == true)
		{
		  lpaddle.move(paddleUp);
		  if (event.type == sf::Event::KeyReleased) {qKeyPressed = false;}
		}
	      if (aKeyPressed == true)
		{
		  lpaddle.move(paddleDown);
		  if (event.type == sf::Event::KeyReleased) {aKeyPressed = false;}
		}
	    }

	  
	  // Check for window closure
	  if (event.type == sf::Event::Closed)
	    window.close();
        }

      // Frame update
      frameUpdate(window,shape,lpaddle);
    }
  return 0;
}
