// CGT-215-Lab-07.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
    // Create the game window.
    RenderWindow window(VideoMode(800, 600), "Lab 07");
    window.setFramerateLimit(60);

    // Use no gravity so the ball moves horizontally.
    World world(Vector2f(0, 0));

    // Count wall hits and center hits separately.
    int thudCount = 0;
    int bang = 0;

    // Change to 2 if your TA requires two center hits.
    const int hitsToExit = 2;

    // Create the ball.
    PhysicsCircle ball;
    ball.setRadius(20);
    ball.setCenter(Vector2f(150, 300));
    world.AddPhysicsBody(ball);

    // Push the ball to the right.
    ball.applyImpulse(Vector2f(0.2f, 0.0f));

    // Create the bottom wall.
    PhysicsRectangle floor;
    floor.setSize(Vector2f(800, 20));
    floor.setCenter(Vector2f(400, 590));
    floor.setStatic(true);
    world.AddPhysicsBody(floor);

    // Create the top wall.
    PhysicsRectangle ceiling;
    ceiling.setSize(Vector2f(800, 20));
    ceiling.setCenter(Vector2f(400, 10));
    ceiling.setStatic(true);
    world.AddPhysicsBody(ceiling);

    // Create the left wall.
    PhysicsRectangle leftWall;
    leftWall.setSize(Vector2f(20, 560));
    leftWall.setCenter(Vector2f(10, 300));
    leftWall.setStatic(true);
    world.AddPhysicsBody(leftWall);

    // Create the right wall.
    PhysicsRectangle rightWall;
    rightWall.setSize(Vector2f(20, 560));
    rightWall.setCenter(Vector2f(790, 300));
    rightWall.setStatic(true);
    world.AddPhysicsBody(rightWall);

    // Create the center block.
    PhysicsRectangle centerBlock;
    centerBlock.setSize(Vector2f(100, 100));
    centerBlock.setCenter(Vector2f(400, 300));
    centerBlock.setStatic(true);
    world.AddPhysicsBody(centerBlock);

    // Count bottom wall collisions.
    floor.onCollision =
        [&thudCount](PhysicsBodyCollisionResult result)
        {
            thudCount++;
            cout << "thud " << thudCount << endl;
        };

    // Count top wall collisions.
    ceiling.onCollision =
        [&thudCount](PhysicsBodyCollisionResult result)
        {
            thudCount++;
            cout << "thud " << thudCount << endl;
        };

    // Count left wall collisions.
    leftWall.onCollision =
        [&thudCount](PhysicsBodyCollisionResult result)
        {
            thudCount++;
            cout << "thud " << thudCount << endl;
        };

    // Count right wall collisions.
    rightWall.onCollision =
        [&thudCount](PhysicsBodyCollisionResult result)
        {
            thudCount++;
            cout << "thud " << thudCount << endl;
        };

    // Count center block collisions.
    centerBlock.onCollision =
        [&bang, &window, hitsToExit](PhysicsBodyCollisionResult result)
        {
            bang++;
            cout << "bang " << bang << endl;

            // Close the window after the required number of hits.
            if (bang >= hitsToExit)
            {
                cout << "Center hit limit reached!" << endl;
                window.close();
            }
        };

    // Start a clock to measure time between updates.
    Clock clock;
    Time lastTime = clock.getElapsedTime();

    // Run the game while the window is open.
    while (window.isOpen())
    {
        // Handle window events.
        Event event;

        while (window.pollEvent(event))
        {
            // Close the window when the X button is clicked.
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        if (!window.isOpen())
        {
            break;
        }

        // Calculate milliseconds since the last update.
        Time currentTime = clock.getElapsedTime();
        Time deltaTime = currentTime - lastTime;
        int deltaTimeMS = deltaTime.asMilliseconds();

        if (deltaTimeMS > 0)
        {
            lastTime = currentTime;

            // Prevent large physics jumps after a pause.
            if (deltaTimeMS > 20)
            {
                deltaTimeMS = 20;
            }

            // Update movement and collisions.
            world.UpdatePhysics(deltaTimeMS);
        }

        // Stop drawing if a collision closed the window.
        if (!window.isOpen())
        {
            break;
        }

        // Clear the screen.
        window.clear(Color::Black);

        // Draw the ball, walls, and center block.
        window.draw(ball);
        window.draw(floor);
        window.draw(ceiling);
        window.draw(leftWall);
        window.draw(rightWall);
        window.draw(centerBlock);

        // Show the completed frame.
        window.display();
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
