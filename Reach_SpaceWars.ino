

#include <gamma.h>
#include <RGBmatrixPanel.h>
#include <Adafruit_GFX.h> 

// define the wiring of the LED screen
const uint8_t CLK  = 8;
const uint8_t LAT = A3;
const uint8_t OE = 9;
const uint8_t A = A0;
const uint8_t B = A1;
const uint8_t C = A2;

// define the wiring of the inputs
const int POTENTIOMETER_PIN_NUMBER = 5;
const int BUTTON_PIN_NUMBER = 10;

// global constant for the number of Invaders in the game
const int NUM_ENEMIES = 16;
bool GAMEOVER ;

// a global variable that represents the LED screen
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

const Color BLACK(0, 0, 0);
const Color RED(4, 0, 0);
const Color ORANGE(4, 2, 0);
const Color YELLOW(4, 4, 0);
const Color GREEN(0, 4, 0);
const Color BLUE(0, 0, 4);
const Color PURPLE(4, 0, 4);
const Color WHITE(4, 4, 4);
const Color LIME(2, 4, 0);
const Color AQUA(0, 4, 4);


class Color {
  public:
    int red;
    int green;
    int blue;

    //default color constructor
    Color() {
      red = 0;
      green = 0;
      blue = 0;
    }

    //Parameterised color constructor
    Color(int r, int g, int b) {
      red = r;
      green = g;
      blue = b;
    }
    uint16_t to_333() const {
      return matrix.Color333(red, green, blue);
    }
};


class SlimShady_Player1 {
   public:

    /*Setting player variables to their default values in context
    of the game*/
    Player() {
      x = 0;
      y = 0;
      lives = 5;
      initialize(0,7);
    }
    
    // getters
    int get_x() const {
     return x;
    }
    int get_y() const {
     return y;
    }
    int get_lives() const {
     return lives;
    }
    
    // setter
    void set_y(int y_arg) {
       y = y_arg;
    }
    
    // Modifies: lives
    void hit() {
      // decrements number of lives by 1 
      lives -= 1;
    }
    
    // draws the Player
    // calls: draw_with_rgb
    void draw() {
      draw_with_rgb(AQUA);
    }
    
    // draws black where the Player used to be
    // calls: draw_with_rgb
    void erase() {
      draw_with_rgb(BLACK);
    }

  private:
    int x;
    int y;
    int lives;

    // sets private data members x and y to initial values
    void initialize(int x_arg, int y_arg) {
     x = x_arg;
     y = y_arg;
    }
    
    // draws the player
    void draw_with_rgb(Color color) {


      int xC1 = 0, xC2 = 1;
      int yR1 = y, yR2 = y + 1;

      if(y <= 0)
      {
        draw_WRT_lives(0,0, color);
      }

      else if(y >= 30)
      {
        draw_WRT_lives(0,30, color);
      }

      else if(x >= 0 && x <= 29)
      {
        draw_WRT_lives(0,y, color);
      }
    }
    void draw_WRT_lives(int x_arg,int y_arg, Color color)
    {
      int xC1 = 0, xC2 = 1;
      int yR1 = y, yR2 = y + 1;
      matrix.setCursor(0, y);
      if(lives == 5)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color) ;
        matrix.drawPixel(xC1, yR2, color) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(xC2, yR1, PURPLE) ;
        matrix.drawPixel(xC2, yR2, PURPLE) ;
        
      }
      else if(lives == 4)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color) ;
        matrix.drawPixel(xC1, yR2, color) ;
        //drawing second column with BLUE color
        matrix.drawPixel(xC2, yR1, BLUE) ;
        matrix.drawPixel(xC2, yR2, BLUE) ;
        
      }
      else if(lives == 3)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color) ;
        matrix.drawPixel(xC1, yR2, color) ;
        //drawing second column with LIME color
        matrix.drawPixel(xC2, yR1, LIME) ;
        matrix.drawPixel(xC2, yR2, LIME) ;
        
      }
      else if(lives == 2)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color) ;
        matrix.drawPixel(xC1, yR2, color) ;
        //drawing second column with ORANGE color
        matrix.drawPixel(xC2, yR1, ORANGE) ;
        matrix.drawPixel(xC2, yR2, ORANGE) ;
        
      }
      else if(lives == 1)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color) ;
        matrix.drawPixel(xC1, yR2, color) ;
        //drawing second column with RED color
        matrix.drawPixel(xC2, yR1, RED) ;
        matrix.drawPixel(xC2, yR2, RED) ;
        
      }

      //Impossible case scenario of attaining WHITE form
     else if(lives == 6)
     {
      //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color) ;
        matrix.drawPixel(xC1, yR2, color) ;
        //drawing second column with RED color
        matrix.drawPixel(xC2, yR1, WHITE) ;
        matrix.drawPixel(xC2, yR2, WHITE) ;
     }
    }
};


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}