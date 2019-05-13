#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <cmath>

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
bool upKeyPressed;
bool downKeyPressed;
bool ballPaddleCollision;
bool ballPaddleCornerCollision;
bool doCollisionCheck;
int collisionCheckCounter;
int lpaddleFront;
int leftScoreCount;
int rightScoreCount;
bool gameRunning;

// Function area

void frameUpdate(sf::RenderWindow& window,sf::CircleShape& shape,sf::RectangleShape& lpaddle,sf::RectangleShape& rpaddle,sf::Text& leftScore,sf::Text& rightScore)
{
  window.clear();
  window.draw(shape);
  window.draw(lpaddle);
  window.draw(rpaddle);
  window.draw(rightScore);
  window.draw(leftScore);
  window.display();
}

int main()
{
  // Create window
  sf::RenderWindow window(sf::VideoMode(WindowX, WindowY), "Pong v1.0");

  // Initialize ball
  sf::CircleShape shape(ballRadius);
  shape.setFillColor(sf::Color::White);
  ballPos.x = CenterX-ballRadius;
  ballPos.y = CenterY-ballRadius;
  shape.setPosition(ballPos);

  // Initialize left paddle
  int paddleWidth = 10.f;
  int paddleHeight = 100.f;
  sf::RectangleShape lpaddle(sf::Vector2f(paddleWidth,paddleHeight));
  lpaddle.setFillColor(sf::Color::White);
  lpaddlePos.x = WindowX/16;
  lpaddlePos.y = WindowY/2;
  lpaddle.setPosition(lpaddlePos);
  // Initialize right paddle
  sf::RectangleShape rpaddle(sf::Vector2f(paddleWidth,paddleHeight));
  rpaddle.setFillColor(sf::Color::White);
  rpaddlePos.x = WindowX/16*15;
  rpaddlePos.y = WindowY/2;
  rpaddle.setPosition(rpaddlePos);

  // Initialize scores
  sf::Font font;
  font.loadFromFile("bit5x3.ttf");
  sf::Text leftScore;
  sf::Text rightScore;
  leftScore.setFont(font);
  rightScore.setFont(font);
  leftScore.setString("0");
  rightScore.setString("0");
  leftScore.setCharacterSize(180);
  rightScore.setCharacterSize(180);
  leftScore.setFillColor(sf::Color::White);
  rightScore.setFillColor(sf::Color::White);
  leftScore.setPosition(WindowX/4,10);
  rightScore.setPosition(WindowX/4*3,10);
  
  // Initialize motion vector
  ballMotion.x = -.2;
  ballMotion.y = .05;
  // Initialize paddle movement vectors
  paddleDown.x = 0;
  paddleDown.y = .1625;
  paddleUp.x = 0;
  paddleUp.y = -.1625;
  // Initialize other variables
  ballPaddleCollision = false;
  lpaddleFront = lpaddlePos.x+paddleWidth;
  doCollisionCheck = true;
  gameRunning = true;
  
  // Main game loop
  while (window.isOpen() && gameRunning)
    {
      // Initialize event
      sf::Event event;

      // Ball motion section
      // Update the ball
      ballPos+=ballMotion;
      shape.setPosition(ballPos);

      // Score up and reset when it hits LEFT edge
      if (ballPos.x <= 0.f)
	{
	  ballPos.x = WindowX/2;
	  ballPos.y = WindowY/2;
	  shape.setPosition(ballPos);
	  rightScoreCount++;
	  std::ostringstream stream;	  
	  stream << rightScoreCount;
	  rightScore.setString(stream.str());
	}
      // Invert motion vector when it hits RIGHT edge
      if (ballPos.x >= 1280.f-ballRadius*2)
	{
	  ballPos.x = WindowX/2;
	  ballPos.y = WindowY/2;
	  shape.setPosition(ballPos);
	  leftScoreCount++;
	  std::ostringstream stream;
	  stream << leftScoreCount;
	  leftScore.setString(stream.str());
 	}
      // Invert motion vector when it hits BOTTOM
      if (ballPos.y >= 720-ballRadius*2)
	{
	  ballPos.y = 720-ballRadius*2;
	  shape.setPosition(ballPos);
	  ballMotion.y = -ballMotion.y;
	}
      // Invert motion vector when it hits TOP
      if (ballPos.y <= 0)
	{
	  ballPos.y = 0;
	  shape.setPosition(ballPos);
	  ballMotion.y = -ballMotion.y;
	}
      
      // Paddle collision
      
      sf::Vector2f ballCenter;
      ballCenter.x = ballPos.x+ballRadius;
      ballCenter.y = ballPos.y+ballRadius;
      int lpaddleTop = lpaddle.getPosition().y;
      int lpaddleBottom = lpaddle.getPosition().y+paddleHeight;
      int rpaddleTop = rpaddle.getPosition().y;
      int rpaddleBottom = rpaddle.getPosition().y+paddleHeight;
      // Paddle collision with top of window
      if (lpaddleTop <= 0) {lpaddle.setPosition(lpaddle.getPosition().x,1);}
      if (lpaddleBottom >= WindowY) {lpaddle.setPosition(lpaddle.getPosition().x,WindowY-paddleHeight);}
      if (rpaddleTop <= 0) {rpaddle.setPosition(rpaddle.getPosition().x,1);}
      if (rpaddleBottom >= WindowY) {rpaddle.setPosition(rpaddle.getPosition().x,WindowY-paddleHeight);}
      
      // Reset ballPaddleCollision
      ballPaddleCollision = false;
      ballPaddleCornerCollision = false;

      // Main collision checks
      if (doCollisionCheck)
	{
	  // Ball escaped left
	  if (ballCenter.x <= lpaddle.getPosition().x) {goto SKIPCOLLISION;}
	  
	  // Left paddle front face collision check
	  if (ballCenter.y >= lpaddleTop && ballCenter.y <= lpaddleBottom && ballCenter.x-ballRadius <= lpaddleFront) {ballPaddleCollision = true;}

	  // Left paddle front top corner collision check
	  if (ballCenter.y+ballRadius >= lpaddleTop && ballCenter.y <= lpaddleTop)
	    {
	      int dx = ballCenter.x-lpaddleFront;
	      int dy = ballCenter.y-lpaddleTop;
	      double dist = sqrt(dx*dx+dy*dy);
	      if (dist < ballRadius)
		{
		  ballPaddleCollision = true;
		  ballPaddleCornerCollision = true;
		}
	    }
	  
	  // Left paddle top face collision check
	  if (ballCenter.y+ballRadius >= lpaddleTop && ballCenter.y <= lpaddleTop)
	    {
	      if (ballCenter.x >= lpaddle.getPosition().x && ballCenter.x <= lpaddleFront)
		{
		  ballPaddleCornerCollision = true;
		}
	    }
	  
	  // Left paddle front bottom corner collision check
	  if (ballCenter.y-ballRadius <= lpaddleBottom && ballCenter.y >= lpaddleBottom)
	    {
	      int dx = ballCenter.x-lpaddleFront;
	      int dy = ballCenter.y-lpaddleBottom;
	      double dist = sqrt(dx*dx+dy*dy);
	      if (dist < ballRadius)
		{
		  ballPaddleCollision = true;
		  ballPaddleCornerCollision = true;
		}
	    }
	  
	  // Left paddle bottom collision check
	  	  if (ballCenter.y+ballRadius <= lpaddleBottom && ballCenter.y >= lpaddleBottom)
	    {
	      if (ballCenter.x >= lpaddle.getPosition().x && ballCenter.x <= lpaddleFront)
	  	{
	  	  ballPaddleCollision = true;
	  	}
	    }
	  // Right paddle grabbing issue
	  if (ballCenter.x >= rpaddle.getPosition().x+paddleWidth) {goto SKIPCOLLISION;}
	  // Right paddle collision checks
	  if (ballCenter.y >= rpaddleTop && ballCenter.y <= rpaddleBottom && ballCenter.x+ballRadius >= rpaddle.getPosition().x) {ballPaddleCollision = true;}
	  // Right paddle top corner case
	  if (ballCenter.y+ballRadius >= rpaddleTop && ballCenter.y <= rpaddleTop)
	    {
	      int dx = ballCenter.x-rpaddle.getPosition().x;
	      int dy = ballCenter.y-rpaddleBottom;
	      double dist = sqrt(dx*dx+dy*dy);
	      if (dist < ballRadius)
		{
		  ballPaddleCollision = true;
		  ballPaddleCornerCollision = true;
		}
	    }
	  // Right paddle top face case
	  if (ballCenter.y+ballRadius >= rpaddleTop && ballCenter.y <= rpaddleTop)
	    {
	      if (ballCenter.x <= rpaddle.getPosition().x+paddleWidth && ballCenter.x >= rpaddle.getPosition().x)
		{
		  ballPaddleCornerCollision = true;
		}
	    }
	  // Right paddle bottom corner check
	  if (ballCenter.y-ballRadius <= rpaddleBottom && ballCenter.y >= rpaddleBottom)
	    {
	      int dx = ballCenter.x-rpaddle.getPosition().x;
	      int dy = ballCenter.y-rpaddleBottom;
	      double dist = sqrt(dx*dx+dy*dy);
	      if (dist < ballRadius)
		{
		  ballPaddleCollision = true;
		  ballPaddleCornerCollision = true;
		}
	    }
	  // Invert motion vectors for reflection
	  if (ballPaddleCollision == true)
	    {
	      ballMotion.x = -ballMotion.x;
	      doCollisionCheck = false;
	      collisionCheckCounter = 1000;
	    }
	  if (ballPaddleCornerCollision == true)
	    {
	      ballMotion.y = -ballMotion.y;
	      doCollisionCheck = false;
	      collisionCheckCounter = 1000;
	    }
	}
    SKIPCOLLISION:
      collisionCheckCounter--;
      if (collisionCheckCounter == 0) {doCollisionCheck = true;}
      
      // Event handler
      window.pollEvent(event);
      // Paddle movement
      if (event.type == sf::Event::KeyPressed)
	    {
	      if (event.key.code == sf::Keyboard::Down) {downKeyPressed = true;}
	      if (event.key.code == sf::Keyboard::Up) {upKeyPressed = true;}
	      if (event.key.code == sf::Keyboard::Q) {qKeyPressed = true;}
	      if (event.key.code == sf::Keyboard::A) {aKeyPressed = true;}
	    }
      if (event.type == sf::Event::KeyReleased)
	{
	  if (event.key.code == sf::Keyboard::Up) {upKeyPressed = false;}
	  if (event.key.code == sf::Keyboard::Down) {downKeyPressed = false;}
	  if (event.key.code == sf::Keyboard::A) {aKeyPressed = false;}
	  if (event.key.code == sf::Keyboard::Q) {qKeyPressed = false;}
	}
      if (qKeyPressed == true)
	{
	  lpaddle.move(paddleUp);	   
	}
      if (aKeyPressed == true)
	{
	  lpaddle.move(paddleDown);
	}
      if (upKeyPressed == true)
	{
	  rpaddle.move(paddleUp);
	}
      if (downKeyPressed == true)
	{
	  rpaddle.move(paddleDown);
	}
      // "You Win" screen
      if (leftScoreCount == 5) {gameRunning = false;}
      if (rightScoreCount == 5) {gameRunning = false;}
      
      // Check for window closure
      if (event.type == sf::Event::Closed) {window.close();}
      
      // Frame update
      frameUpdate(window,shape,lpaddle,rpaddle,leftScore,rightScore);
    }
  while (window.isOpen())
    {
      window.clear();
      sf::Text win;
      win.setFont(font);
      win.setString("You Win!");
      win.setCharacterSize(180);
      win.setFillColor(sf::Color::White);
      win.setPosition(WindowX/4,WindowY/4);
      window.draw(win);
      window.display();
      sf::Event winEvent;
      window.pollEvent(winEvent);
      if (winEvent.type == sf::Event::Closed) {window.close();}
    }
  return 0;
}
