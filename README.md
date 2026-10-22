# CGT 215 - Lab 07
## Simple Game Physics

### Description
This program uses SFML and SFPhysics to simulate a bouncing ball inside four walls with a square obstacle in the center. The ball moves horizontally and the program ends after it hits the center obstacle twice.

### Features
- Creates a ball, four static walls, and a static center obstacle.
- Prints "thud" and updates a shared counter when the ball hits a wall.
- Prints "bang" and updates a separate counter when the ball hits the center obstacle.
- Uses lambda collision callbacks to count hits.
- Closes the game window after two center hits.

### Expected Output
bang 1
thud 1
bang 2
Center hit limit reached!
