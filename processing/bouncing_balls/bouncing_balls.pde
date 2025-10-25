
int highX = 1000;
int highY = 500;
int lowX = 0;
int lowY = 0;
int n = int(random(3, 10));


Ball[] balls = new Ball[n];

void setup() {
  size(1000, 500);
  for(int i = 0; i < balls.length; i++) {
    balls[i] = new Ball(random(highX), random(highY), random(1, 10), random(30, 50), color(random(255), random(255), random(255)));
  }
}

void draw() {
  background(255);
  for(Ball b : balls) {
    b.movementUpdate();
    b.display();
  }
  
  saveFrame("frames/frame-#########.png");
  
  if(keyPressed && key == 'q') exit();
  
}

class Ball {
  float x, y;
  float speed;
  float dirX = random(-1, 1);
  float dirY = random(-1, 1);
  float d;
  color c;
  
  Ball(float x, float y, float speed, float d, color c) {
    this.x = x;
    this.y = y;
    this.speed = speed;
    this.d = d;
    this.c = c;
    float len = sqrt(dirX * dirX + dirY * dirY);
    dirX /= len;
    dirY /= len;

  }
  
  void movementUpdate() {
    x += dirX * speed;
    y += dirY * speed;
    
    if (x < lowX + d/2 - d/4 || x > highX - d/2 + d/4) {
      dirX *= -1;
      x = constrain(x, lowX + d/2 - d/4, highX - d/2 + d/4);
    }
    if (y < lowY + d/2 - d/4 || y > highY - d/2 + d/4) {
      dirY *= -1;
      y = constrain(y, lowY + d/2 - d/4, highY - d/2 + d/4);
    }

    
  }
  
  void display() {
    float squishX = 1;
    float squishY = 1;
  
    if (x < lowX + d/2) squishX = map(x, lowX, lowX + d/2, 0.5, 1);
    else if (x > highX - d/2) squishX = map(x, highX, highX - d/2, 0.5, 1);
    
    if (y < lowY + d/2) squishY = map(y, lowY, lowY + d/2, 0.5, 1);
    else if (y > highY - d/2) squishY = map(y, highY, highY - d/2, 0.5, 1);
    
    fill(c);
    ellipse(x, y, d * squishX, d * squishY);
  }

}
