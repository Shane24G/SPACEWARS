

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


//***************************************************************************************************
//canon ball code 
class Cannonball {
  //same class will be used for all three types of players
  public:

    //default constructor for cannonball class
    Cannonball() {
      x = 0;
      y = 0;
      fired = false;
    }
    
    // resets private data members to initial values
    void reset() {
      x = 0;
      y = 0;
      fired = false;
    }
    
    // getters
    int get_x() const {
     return x;
    }
    int get_y() const {
     return y;
    }
    bool has_been_fired() const {
     return fired;
    }
    
    // sets private data members
    void fire(int x_arg, int y_arg) {
     x = x_arg;
     y = y_arg;
     fired = true ;
    }
    
    // moves the Cannonball and detects if it goes off the screen
    // Modifies: y, fired
    void move() {
     erase() ;
     if(x >= 0 && x < 32)
       {
        fired = true ;
         x++ ;
       }
  
      else{
        reset() ;
      }
    }
    
    // resets private data members to initial values
    void hit() {
      reset();
    }
    
    // draws the Cannonball, if it is fired
    void draw() {
     
       if(fired)
     
      {
        matrix.setCursor(x, y);
        matrix.drawPixel(x, y, YELLOW.to_333()); 
      }
  
    }
    
    // draws black where the Cannonball used to be
    void erase() {
     matrix.drawPixel(x, y, BLACK.to_333());
    }

  private:
    int x;
    int y;
    bool fired;
};


//*****************************************************************************************************
//Slim Shady code incoming
class SlimShady_Player1 {
  //slim shady will have alternating gun firing
   public:

    /*Setting player variables to their default values in context
    of the game*/
    SlimShady_Player1() {
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

    void Increase_Life()
    {
      lives += 1 ;
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

      else if(y >= 15)
      {
        draw_WRT_lives(0,15, color);
      }

      else if(y >= 0 && y <= 15)
      {
        draw_WRT_lives(0,y, color);
      }
      
    }
    void draw_WRT_lives(int x_arg,int y_arg, Color color)
    {
      int xC1 = 0, xC2 = 1;
      int yR1 = y_arg, yR2 = y_arg + 1;
      matrix.setCursor(0, y_arg);
      if(lives == 5)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(1, yR1, PURPLE.to_333()) ;
        matrix.drawPixel(1, yR2, PURPLE.to_333()) ;
        
      }
      else if(lives == 4)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        //drawing second column with BLUE color
        matrix.drawPixel(1, yR1, BLUE.to_333()) ;
        matrix.drawPixel(1, yR2, BLUE.to_333()) ;
        
      }
      else if(lives == 3)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        //drawing second column with LIME color
        matrix.drawPixel(1, yR1, LIME.to_333()) ;
        matrix.drawPixel(1, yR2, LIME.to_333()) ;
        
      }
      else if(lives == 2)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        //drawing second column with ORANGE color
        matrix.drawPixel(1, yR1, ORANGE.to_333()) ;
        matrix.drawPixel(1, yR2, ORANGE.to_333()) ;
        
      }
      else if(lives == 1)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        //drawing second column with RED color
        matrix.drawPixel(1, yR1, RED.to_333()) ;
        matrix.drawPixel(1, yR2, RED.to_333()) ;
        
      }

      //If Slim shady shoots crate 
     else if(lives == 6)
     {
      //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        //drawing second column with RED color
        matrix.drawPixel(1, yR1, WHITE.to_333()) ;
        matrix.drawPixel(1, yR2, WHITE.to_333()) ;
     }
    }
};


//Creating Player 2 class
class SlimShady_Player2 {
   public:

    /*Setting player variables to their default values in context
    of the game*/
    SlimShady_Player2() {
      x = 0;
      y = 0;
      lives = 5;
      initialize(31,7);
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
    
    void Increase_Life()
    {
      lives += 1 ;
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


      

      if(y <= 0)
      {
        draw_WRT_lives(30, 0, color);
      }

      else if(y >= 15)
      {
        draw_WRT_lives(30, 15, color);
      }

      else if(y >= 0 && y <= 15)
      {
        draw_WRT_lives(30, y, color);
      }
    }
    void draw_WRT_lives(int x_arg,int y_arg, Color color)
    {
      int xC1 = 30, xC2 = 31;
      int yR1 = y_arg, yR2 = y_arg + 1;
      matrix.setCursor(30, y_arg);
      if(lives == 5)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(1, yR1, PURPLE.to_333()) ;
        matrix.drawPixel(1, yR2, PURPLE.to_333()) ;
        
      }
      else if(lives == 4)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        //drawing second column with BLUE color
        matrix.drawPixel(1, yR1, BLUE.to_333()) ;
        matrix.drawPixel(1, yR2, BLUE.to_333()) ;
        
      }
      else if(lives == 3)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        //drawing second column with LIME color
        matrix.drawPixel(1, yR1, LIME.to_333()) ;
        matrix.drawPixel(1, yR2, LIME.to_333()) ;
        
      }
      else if(lives == 2)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        //drawing second column with ORANGE color
        matrix.drawPixel(1, yR1, ORANGE.to_333()) ;
        matrix.drawPixel(1, yR2, ORANGE.to_333()) ;
        
      }
      else if(lives == 1)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        //drawing second column with RED color
        matrix.drawPixel(1, yR1, RED.to_333()) ;
        matrix.drawPixel(1, yR2, RED.to_333()) ;
        
      }

      //Will happen only if slim shady hits the crate
     else if(lives == 6)
     {
      //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        //drawing second column with RED color
        matrix.drawPixel(1, yR1, WHITE.to_333()) ;
        matrix.drawPixel(1, yR2, WHITE.to_333()) ;
     }
    }
};



//*****************************************************************************************************
//BigShaq code incoming
class BigShaq_Player1 {
   public:

    /*Setting player variables to their default values in context
    of the game*/
    BigShaq_Player1() {
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
    
    void Increase_Life()
    //if player hits the crate and is at full life at that time
    {
      lives += 1 ;
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


      /*int xC1 = 0, xC2 = 1;
      int yR1 = y, yR2 = y + 1, yR3 = y + 2, yR4 = y + 3;*/

      if(y <= 0)
      {
        draw_WRT_lives(0,0, color);
      }

      else if(y >= 12)
      {
        draw_WRT_lives(0,12, color);
      }

      else if(y >= 0 && y <= 12)
      {
        draw_WRT_lives(0,y, color);
      }
    }
    void draw_WRT_lives(int x_arg,int y_arg, Color color)
    {
      int xC1 = 0, xC2 = 1;
      int yR1 = y_arg, yR2 = y_arg + 1, yR3 = y_arg + 2, yR4 = y_arg + 3;
      matrix.setCursor(0, y_arg);
      if(lives == 5)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
        matrix.drawPixel(0, yR4, color.to_333()) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(1, yR1, PURPLE.to_333()) ;
        matrix.drawPixel(1, yR4, PURPLE.to_333()) ;
        
      }
      else if(lives == 4)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
        matrix.drawPixel(0, yR4, color.to_333()) ;
        //drawing second column with BLUE color
        matrix.drawPixel(1, yR1, BLUE.to_333()) ;
        matrix.drawPixel(1, yR4, BLUE.to_333()) ;
        
      }
      else if(lives == 3)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
        matrix.drawPixel(0, yR4, color.to_333()) ;
        //drawing second column with LIME color
        matrix.drawPixel(1, yR1, LIME.to_333()) ;
        matrix.drawPixel(1, yR4, LIME.to_333()) ;
        
      }
      else if(lives == 2)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
        matrix.drawPixel(0, yR4, color.to_333()) ;
        //drawing second column with ORANGE color
        matrix.drawPixel(1, yR1, ORANGE.to_333()) ;
        matrix.drawPixel(1, yR4, ORANGE.to_333()) ;
        
      }
      else if(lives == 1)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
        matrix.drawPixel(0, yR4, color.to_333()) ;
        //drawing second column with RED color
        matrix.drawPixel(1, yR1, RED.to_333()) ;
        matrix.drawPixel(1, yR4, RED.to_333()) ;
        
      }

      //attaining WHITE form after hitting the crate
     else if(lives == 6)
     {
      //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
        matrix.drawPixel(0, yR4, color.to_333()) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(1, yR1, WHITE.to_333()) ;
        matrix.drawPixel(1, yR4, WHITE.to_333()) ;
     }
    }
};

class BigShaq_Player2 {
   public:

    /*Setting player variables to their default values in context
    of the game*/
    BigShaq_Player2() {
      x = 0;
      y = 0;
      lives = 5;
      initialize(31,7);
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
    
    void Increase_Life()
    {
      lives += 1 ;
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
      int yR1 = y, yR2 = y + 1, yR3 = y + 2, yR4 = y + 3;

      if(y <= 0)
      {
        draw_WRT_lives(31,0, color);
      }

      else if(y >= 12)
      {
        draw_WRT_lives(31,12, color);
      }

      else if(y >= 0 && y <= 12)
      {
        draw_WRT_lives(31,y, color);
      }
    }
    void draw_WRT_lives(int x_arg,int y_arg, Color color)
    {
      int xC1 = 0, xC2 = 1;
      int yR1 = y_arg, yR2 = y_arg + 1, yR3 = y_arg + 2, yR4 = y_arg + 3;
      matrix.setCursor(0, y_arg);
      if(lives == 5)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
        matrix.drawPixel(31, yR4, color.to_333()) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(30, yR1, PURPLE.to_333()) ;
        matrix.drawPixel(30, yR4, PURPLE.to_333()) ;
        
      }
      else if(lives == 4)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
        matrix.drawPixel(31, yR4, color.to_333()) ;
        //drawing second column with BLUE color
        matrix.drawPixel(30, yR1, BLUE.to_333()) ;
        matrix.drawPixel(30, yR4, BLUE.to_333()) ;
        
      }
      else if(lives == 3)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
        matrix.drawPixel(31, yR4, color.to_333()) ;
        //drawing second column with LIME color
        matrix.drawPixel(30, yR1, LIME.to_333()) ;
        matrix.drawPixel(30, yR4, LIME.to_333()) ;
        
      }
      else if(lives == 2)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
        matrix.drawPixel(31, yR4, color.to_333()) ;
        //drawing second column with ORANGE color
        matrix.drawPixel(30, yR1, ORANGE.to_333()) ;
        matrix.drawPixel(30, yR4, ORANGE.to_333()) ;
        
      }
      else if(lives == 1)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
        matrix.drawPixel(31, yR4, color.to_333()) ;
        //drawing second column with RED color
        matrix.drawPixel(30, yR1, RED.to_333()) ;
        matrix.drawPixel(30, yR4, RED.to_333()) ;
        
      }

      //attaining WHITE form after hitting the crate
     else if(lives == 6)
     {
      //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
        matrix.drawPixel(31, yR4, color.to_333()) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(30, yR1, WHITE.to_333()) ;
        matrix.drawPixel(30, yR4, WHITE.to_333()) ;
     }
    }
};



//*****************************************************************************************************
//Classic Player code incoming 

class Classic_Player1 {
   public:

    /*Setting player variables to their default values in context
    of the game*/
    Classic_Player1() {
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
    
    void Increase_Life()
    {
      lives += 1 ;
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
      int yR1 = y, yR2 = y + 1, yR3 = y + 2 ;

      if(y <= 0)
      {
        draw_WRT_lives(0,0, color);
      }

      else if(y >= 13)
      {
        draw_WRT_lives(0,13, color);
      }

      else if(y >= 0 && y <= 13)
      {
        draw_WRT_lives(0,y, color);
      }
    }
    void draw_WRT_lives(int x_arg,int y_arg, Color color)
    {
      int xC1 = 0, xC2 = 1;
      int yR1 = y_arg, yR2 = y_arg + 1, yR3 = y_arg + 2 ;
      matrix.setCursor(0, y_arg);
      if(lives == 5)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(1, yR2, PURPLE.to_333()) ;
       
      }
      else if(lives == 4)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
        
        //drawing second column with BLUE color
        matrix.drawPixel(1, yR2, BLUE.to_333()) ;
        
        
      }
      else if(lives == 3)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
        
        //drawing second column with LIME color
        matrix.drawPixel(1, yR2, LIME.to_333()) ;
       
        
      }
      else if(lives == 2)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
        
        //drawing second column with ORANGE color
        matrix.drawPixel(1, yR2, ORANGE.to_333()) ;
        
        
      }
      else if(lives == 1)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
       
        //drawing second column with RED color
        matrix.drawPixel(1, yR2, RED.to_333()) ;
        
        
      }

      //Impossible case scenario of attaining WHITE form
     else if(lives == 6)
     {
      //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
        
        //drawing second column with PURPLE color
        matrix.drawPixel(1, yR2, WHITE.to_333()) ;
        
     }
    }
};


class Classic_Player2 {
   public:

    /*Setting player variables to their default values in context
    of the game*/
    Classic_Player2() {
      x = 0;
      y = 0;
      lives = 5;
      initialize(30,7);
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
    
    void Increase_Life()
    {
      lives += 1 ;
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


      /*int xC1 = 0, xC2 = 1;
      int yR1 = y, yR2 = y + 1, yR3 = y + 2 ;*/

      if(y <= 0)
      {
        draw_WRT_lives(0,0, color);
      }

      else if(y >= 13)
      {
        draw_WRT_lives(0,13, color);
      }

      else if(y >= 0 && y <= 13)
      {
        draw_WRT_lives(0,y, color);
      }
    }
    void draw_WRT_lives(int x_arg,int y_arg, Color color)
    {
      int xC1 = 31, xC2 = 30;
      int yR1 = y_arg, yR2 = y_arg + 1, yR3 = y_arg + 2 ;
      matrix.setCursor(30, y_arg);
      if(lives == 5)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(30, yR2, PURPLE.to_333()) ;
       
      }
      else if(lives == 4)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
        
        //drawing second column with BLUE color
        matrix.drawPixel(30, yR2, BLUE.to_333()) ;
        
        
      }
      else if(lives == 3)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
        
        //drawing second column with LIME color
        matrix.drawPixel(30, yR2, LIME.to_333()) ;
       
        
      }
      else if(lives == 2)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
        
        //drawing second column with ORANGE color
        matrix.drawPixel(30, yR2, ORANGE.to_333()) ;
        
        
      }
      else if(lives == 1)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
       
        //drawing second column with RED color
        matrix.drawPixel(30, yR2, RED.to_333()) ;
        
        
      }

      //Impossible case scenario of attaining WHITE form
     else if(lives == 6)
     {
      //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
        
        //drawing second column with PURPLE color
        matrix.drawPixel(30, yR2, WHITE.to_333()) ;
        
     }
    }
};

//Current issues/questions/things to add:
//Shouldn't the crate be of an even number size to give each side an fair chance of reaching it?
//I'd imagine the crate will be randomly placed along the center line, but how do we randomly determine the position?
//Am I right to assume that the crate won't be placed so that a row/column is cut off? (i.e. the 3rd row of the crate being placed on the 33rd row, meaning it is cut off)
//Theoretically, if the crate were to not be hit and somehow remained throughout the entire game, should we account for a crate overlapping with it. I presume it's so unlikely that it's not worth considering, though.

class Crate {
  
  public: 
  Crate(){
    x = 0;
    y = 0;
  }
  
  // getters

   int get_x() const {
    return x;
   }
   int get_y() const {
    return y;
   }
   
  // sets x and y private members 
  Crate(int x_arg, int y_arg) {
    x = x_arg;
    y = y_arg;
  }

  // draws the crate (3x3 grid w/ white cross + red corners)
  void draw(){
    draw_with_rgb();
  }

  //moves the crate forward
  void move(){
    y-- ;
  }

  //checks if the crate has been hit
  void hit(){
    reset() ;
  }

  void activate(){
    //should be called at the 1.5 minute mark
    active = true ;
    x = 14;
    y = 13;
  }


  void reset(){
    x = 0;
    y = 0;
    active = false ;
  }

  // draws black where crate used to be 
  void erase(){
    erase_with_rgb();
  }

  private: 
  int x;
  int y;
  bool active = false; 

  void initialize()
  {
    x = 14 ;
    y = 13 ;
    active = false;
    
  }
  
  void draw_with_rgb() {

    matrix.setCursor(x,y);

    int xC1 = x, xC2 = x + 1, xC3 = x + 2;
    int yR1 = y, yR2 = y + 1, yR3 = y + 2;
    
    // draws first row of crate
    matrix.drawPixel(xC1, yR1, WHITE.to_333());
    matrix.drawPixel(xC2, yR1, RED.to_333());
    matrix.drawPixel(xC3, yR1, WHITE.to_333());

    // draws second row of crate
    matrix.drawPixel(xC1, yR2, RED.to_333());
    matrix.drawPixel(xC2, yR2, RED.to_333());
    matrix.drawPixel(xC3, yR2, RED.to_333());

    // draws third row of crate 
    matrix.drawPixel(xC1, yR3, WHITE.to_333());
    matrix.drawPixel(xC2, yR3, RED.to_333());
    matrix.drawPixel(xC3, yR3, WHITE.to_333());
  }

  void erase_with_rgb() {
    
    matrix.setCursor(x,y);

    int xC1 = x, xC2 = x + 1, xC3 = x + 2;
    int yR1 = y, yR2 = y + 1, yR3 = y + 2;
    
    // draws first row of crate
    matrix.drawPixel(xC1, yR1, BLACK.to_333());
    matrix.drawPixel(xC2, yR1, BLACK.to_333());
    matrix.drawPixel(xC3, yR1, BLACK.to_333());

    // draws second row of crate
    matrix.drawPixel(xC1, yR2, BLACK.to_333());
    matrix.drawPixel(xC2, yR2, BLACK.to_333());
    matrix.drawPixel(xC3, yR2, BLACK.to_333());

    // draws third row of crate 
    matrix.drawPixel(xC1, yR3, BLACK.to_333());
    matrix.drawPixel(xC2, yR3, BLACK.to_333());
    matrix.drawPixel(xC3, yR3, BLACK.to_333());
  }
};





void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}


//making changes from adarsh's laptop down below
void print_player1()
{
  matrix.fillScreen(matrix.Color333(0, 0, 0));
 
  matrix.setCursor(7, 14);

  matrix.setTextSize(2);

  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print("P");
  delay(75);

  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print("1");
  delay(500);

  matrix.setCursor(7,14);
  matrix.setTextSize(2);
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print("P1");
  

   
}

void print_player2()
{
  matrix.fillScreen(matrix.Color333(0, 0, 0));
 
  matrix.setCursor(7, 14);

  matrix.setTextSize(2);

  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print("P");
  delay(75);

  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print("2");
  delay(500);

  matrix.setCursor(7,14);
  matrix.setTextSize(2);
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print("P2");
  

   
}


  
void print_Screen()
{  // Draws the classic player
  matrix.drawPixel(2,7,RED.to_333());
  delay(50);
  matrix.drawPixel(3,7,RED.to_333());
  delay(50);
  matrix.drawPixel(4,7,RED.to_333());
  delay(50);
  matrix.drawPixel(3,8,RED.to_333());

  // Draws Slim Shady
  delay(50);
  matrix.drawPixel(13,7,RED.to_333());
  delay(50);
  matrix.drawPixel(14,7,RED.to_333());
  delay(50);
  matrix.drawPixel(13,8,RED.to_333());
  delay(50);
  matrix.drawPixel(14,8,RED.to_333());

  // Draws Big Shaq
  delay(50);
  matrix.drawPixel(25,7,RED.to_333());
  delay(50);
  matrix.drawPixel(26,7,RED.to_333());
  delay(50);
  matrix.drawPixel(27,7,RED.to_333());
  delay(50);
  matrix.drawPixel(28,7,RED.to_333());
  delay(50);
  matrix.drawPixel(25,8,RED.to_333());
  delay(50);
  matrix.drawPixel(28,8,RED.to_333());


 }

 void classic_Player_Selection()
 { 
   // Draws Classic Player and highlights the box showing
   // player chose the classic player
   printScreen();
   matrix.fillRect(0,4,7,10, WHITE.to_333());
   matrix.fillRect(1,3,6,9, YELLOW.to_333());
 }

 void slimShady_Player_Selection()
 {
  // Draws slim shady player and highlights the box showing
  // player chose slim shady
  printScreen();
  matrix.fillRect(11,4,17,10, WHITE.to_333());
  matrix.fillRect(10,3,16,9, YELLOW.to_333());
 }

 void bigShaq_Player_Selection()
 {

  // Draws Big Shaq player and highlights the box showing
   // player chose Big Shaq
  printScreen();
   matrix.fillRect(23,4,31,10, WHITE.to_333());
  matrix.fillRect(22,3,30,9, YELLOW.to_333());
 }





