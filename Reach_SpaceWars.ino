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
//changes to be added
const int NUM_BULLETS = 50;
int p1Choice = 1, p2Choice = 1  ;
long int GameTime = 0;

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
      erase();
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
    void p1move() {
      erase() ;
      if (x >= 1 && x <= 31)
      {
        fired = true ;
        x++ ;
      }

      else {
        reset() ;
      }
    }

    void p2move() {
      erase() ;
      if (x >= 0 && x <= 31)
      {
        fired = true ;
        x-- ;
      }

      else {
        reset() ;
      }
    }

    // resets private data members to initial values
    void hit() {
      reset();
    }

    // draws the Cannonball, if it is fired
    void draw()
    {
      draw_with_RGB();
      if (x > 31 || x < 0)
      {
        reset();
      }
    }

    void draw_with_RGB() {

      if (fired && (x <= 31 && x >= 0))
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
      initialize(0, 7);
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
      matrix.drawPixel(0, y, BLACK.to_333()) ;
      matrix.drawPixel(0, y + 1, BLACK.to_333()) ;
      //drawing second column with PURPLE color
      matrix.drawPixel(1, y, BLACK.to_333()) ;
      matrix.drawPixel(1, y + 1, BLACK.to_333()) ;
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

      if (y <= 0)
      {
        draw_WRT_lives(0, 0, color);
      }

      else if (y >= 14)
      {
        draw_WRT_lives(0, 14, color);
      }

      else if (y >= 0 && y <= 14)
      {
        draw_WRT_lives(0, y, color);
      }

    }
    void draw_WRT_lives(int x_arg, int y_arg, Color color)
    {
      int xC1 = 0, xC2 = 1;
      int yR1 = y_arg, yR2 = y_arg + 1;
      matrix.setCursor(0, y_arg);



      if (lives == 5)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(1, yR1, PURPLE.to_333()) ;
        matrix.drawPixel(1, yR2, PURPLE.to_333()) ;

      }
      else if (lives == 4)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        //drawing second column with BLUE color
        matrix.drawPixel(1, yR1, BLUE.to_333()) ;
        matrix.drawPixel(1, yR2, BLUE.to_333()) ;

      }
      else if (lives == 3)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        //drawing second column with LIME color
        matrix.drawPixel(1, yR1, LIME.to_333()) ;
        matrix.drawPixel(1, yR2, LIME.to_333()) ;

      }
      else if (lives == 2)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        //drawing second column with ORANGE color
        matrix.drawPixel(1, yR1, ORANGE.to_333()) ;
        matrix.drawPixel(1, yR2, ORANGE.to_333()) ;

      }
      else if (lives == 1)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, color.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        //drawing second column with RED color
        matrix.drawPixel(1, yR1, RED.to_333()) ;
        matrix.drawPixel(1, yR2, RED.to_333()) ;

      }

      //If Slim shady shoots crate
      else if (lives == 6)
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
      initialize(31, 7);
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
      //change made
      matrix.drawPixel(31, y, BLACK.to_333()) ;
      matrix.drawPixel(31, y + 1, BLACK.to_333()) ;
      //drawing second column with BLACK color
      matrix.drawPixel(30, y, BLACK.to_333()) ;
      matrix.drawPixel(30, y + 1, BLACK.to_333()) ;
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




      if (y <= 0)
      {
        draw_WRT_lives(30, 0, color);
      }

      else if (y >= 14)
      {
        draw_WRT_lives(30, 14, color);
      }

      else if (y >= 0 && y <= 14)
      {
        draw_WRT_lives(30, y, color);
      }
    }
    void draw_WRT_lives(int x_arg, int y_arg, Color color)
    {
      int xC1 = 30, xC2 = 31;
      int yR1 = y_arg, yR2 = y_arg + 1;
      matrix.setCursor(30, y_arg);
      if (lives == 5)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(30, yR1, PURPLE.to_333()) ;
        matrix.drawPixel(30, yR2, PURPLE.to_333()) ;

      }
      else if (lives == 4)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        //drawing second column with BLUE color
        matrix.drawPixel(30, yR1, BLUE.to_333()) ;
        matrix.drawPixel(30, yR2, BLUE.to_333()) ;

      }
      else if (lives == 3)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        //drawing second column with LIME color
        matrix.drawPixel(30, yR1, LIME.to_333()) ;
        matrix.drawPixel(30, yR2, LIME.to_333()) ;

      }
      else if (lives == 2)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        //drawing second column with ORANGE color
        matrix.drawPixel(30, yR1, ORANGE.to_333()) ;
        matrix.drawPixel(30, yR2, ORANGE.to_333()) ;

      }
      else if (lives == 1)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        //drawing second column with RED color
        matrix.drawPixel(30, yR1, RED.to_333()) ;
        matrix.drawPixel(30, yR2, RED.to_333()) ;

      }

      //Will happen only if slim shady hits the crate
      else if (lives == 6)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, color.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        //drawing second column with RED color
        matrix.drawPixel(30, yR1, WHITE.to_333()) ;
        matrix.drawPixel(30, yR2, WHITE.to_333()) ;
      }
    }
};



//*****************************************************************************************************

class BigShaq_Player1 {
  public:

    /*Setting player variables to their default values in context
      of the game*/
    BigShaq_Player1() {
      x = 0;
      y = 0;
      lives = 5;
      initialize(0, 7);
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
      //change made
      matrix.drawPixel(0, y, BLACK.to_333()) ;
      matrix.drawPixel(0, y + 1, BLACK.to_333()) ;
      matrix.drawPixel(0, y + 2, BLACK.to_333()) ;
      matrix.drawPixel(0, y + 3, BLACK.to_333()) ;
      //drawing second column with BLACK color
      matrix.drawPixel(1, y, BLACK.to_333()) ;
      matrix.drawPixel(1, y + 3, BLACK.to_333()) ;
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

      if (y <= 0)
      {
        draw_WRT_lives(0, 0, color);
      }

      else if (y >= 12)
      {
        draw_WRT_lives(0, 12, color);
      }

      else if (y >= 0 && y <= 12)
      {
        draw_WRT_lives(0, y, color);
      }
    }
    void draw_WRT_lives(int x_arg, int y_arg, Color color)
    {
      int xC1 = 0, xC2 = 1;
      int yR1 = y_arg, yR2 = y_arg + 1, yR3 = y_arg + 2, yR4 = y_arg + 3;
      matrix.setCursor(0, y_arg);
      if (lives == 5)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, PURPLE.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
        matrix.drawPixel(0, yR4, PURPLE.to_333()) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(1, yR1, PURPLE.to_333()) ;
        matrix.drawPixel(1, yR4, PURPLE.to_333()) ;

      }
      else if (lives == 4)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, BLUE.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
        matrix.drawPixel(0, yR4, BLUE.to_333()) ;
        //drawing second column with BLUE color
        matrix.drawPixel(1, yR1, BLUE.to_333()) ;
        matrix.drawPixel(1, yR4, BLUE.to_333()) ;

      }
      else if (lives == 3)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, LIME.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
        matrix.drawPixel(0, yR4, LIME.to_333()) ;
        //drawing second column with LIME color
        matrix.drawPixel(1, yR1, LIME.to_333()) ;
        matrix.drawPixel(1, yR4, LIME.to_333()) ;

      }
      else if (lives == 2)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, ORANGE.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
        matrix.drawPixel(0, yR4, ORANGE.to_333()) ;
        //drawing second column with ORANGE color
        matrix.drawPixel(1, yR1, ORANGE.to_333()) ;
        matrix.drawPixel(1, yR4, ORANGE.to_333()) ;

      }
      else if (lives == 1)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, RED.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
        matrix.drawPixel(0, yR4, RED.to_333()) ;
        //drawing second column with RED color
        matrix.drawPixel(1, yR1, RED.to_333()) ;
        matrix.drawPixel(1, yR4, RED.to_333()) ;

      }

      //attaining WHITE form after hitting the crate
      else if (lives == 6)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, WHITE.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, color.to_333()) ;
        matrix.drawPixel(0, yR4, WHITE.to_333()) ;
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
      initialize(31, 7);
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

      //change made
      matrix.drawPixel(31, y, BLACK.to_333()) ;
      matrix.drawPixel(31, y + 1, BLACK.to_333()) ;
      matrix.drawPixel(31, y + 2, BLACK.to_333()) ;
      matrix.drawPixel(31, y + 3, BLACK.to_333()) ;
      //drawing second column with BLACK color
      matrix.drawPixel(30, y, BLACK.to_333()) ;
      matrix.drawPixel(30, y + 3, BLACK.to_333()) ;
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


      int xC1 = 31, xC2 = 30;
      int yR1 = y, yR2 = y + 1, yR3 = y + 2, yR4 = y + 3;

      if (y <= 0)
      {
        draw_WRT_lives(31, 0, color);
      }

      else if (y >= 12)
      {
        draw_WRT_lives(31, 12, color);
      }

      else if (y >= 0 && y <= 12)
      {
        draw_WRT_lives(31, y, color);
      }
    }
    void draw_WRT_lives(int x_arg, int y_arg, Color color)
    {
      int xC1 = 31, xC2 = 30;
      int yR1 = y_arg, yR2 = y_arg + 1, yR3 = y_arg + 2, yR4 = y_arg + 3;
      matrix.setCursor(0, y_arg);
      if (lives == 5)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, PURPLE.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
        matrix.drawPixel(31, yR4, PURPLE.to_333()) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(30, yR1, PURPLE.to_333()) ;
        matrix.drawPixel(30, yR4, PURPLE.to_333()) ;

      }
      else if (lives == 4)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, BLUE.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
        matrix.drawPixel(31, yR4, BLUE.to_333()) ;
        //drawing second column with BLUE color
        matrix.drawPixel(30, yR1, BLUE.to_333()) ;
        matrix.drawPixel(30, yR4, BLUE.to_333()) ;

      }
      else if (lives == 3)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, LIME.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
        matrix.drawPixel(31, yR4, LIME.to_333()) ;
        //drawing second column with LIME color
        matrix.drawPixel(30, yR1, LIME.to_333()) ;
        matrix.drawPixel(30, yR4, LIME.to_333()) ;

      }
      else if (lives == 2)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, ORANGE.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
        matrix.drawPixel(31, yR4, ORANGE.to_333()) ;
        //drawing second column with ORANGE color
        matrix.drawPixel(30, yR1, ORANGE.to_333()) ;
        matrix.drawPixel(30, yR4, ORANGE.to_333()) ;

      }
      else if (lives == 1)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, RED.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
        matrix.drawPixel(31, yR4, RED.to_333()) ;
        //drawing second column with RED color
        matrix.drawPixel(30, yR1, RED.to_333()) ;
        matrix.drawPixel(30, yR4, RED.to_333()) ;

      }

      //attaining WHITE form after hitting the crate
      else if (lives == 6)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, WHITE.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, color.to_333()) ;
        matrix.drawPixel(31, yR4, WHITE.to_333()) ;
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
      initialize(0, 7);
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
      //change made
      matrix.drawPixel(0, y, BLACK.to_333()) ;
      matrix.drawPixel(0, y + 1, BLACK.to_333()) ;
      matrix.drawPixel(0, y + 2, BLACK.to_333()) ;
      //drawing second column with BLACK color
      matrix.drawPixel(1, y + 1, BLACK.to_333()) ;
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

      if (y <= 0)
      {
        draw_WRT_lives(0, 0, color);
      }

      else if (y >= 13)
      {
        draw_WRT_lives(0, 13, color);
      }

      else if (y >= 0 && y <= 13)
      {
        draw_WRT_lives(0, y, color);
      }
    }
    void draw_WRT_lives(int x_arg, int y_arg, Color color)
    {
      int xC1 = 0, xC2 = 1;
      int yR1 = y_arg, yR2 = y_arg + 1, yR3 = y_arg + 2 ;
      matrix.setCursor(0, y_arg);
      if (lives == 5)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, PURPLE.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, PURPLE.to_333()) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(1, yR2, PURPLE.to_333()) ;

      }
      else if (lives == 4)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, BLUE.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, BLUE.to_333()) ;

        //drawing second column with BLUE color
        matrix.drawPixel(1, yR2, BLUE.to_333()) ;


      }
      else if (lives == 3)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, LIME.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, LIME.to_333()) ;

        //drawing second column with LIME color
        matrix.drawPixel(1, yR2, LIME.to_333()) ;


      }
      else if (lives == 2)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, ORANGE.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, ORANGE.to_333()) ;

        //drawing second column with ORANGE color
        matrix.drawPixel(1, yR2, ORANGE.to_333()) ;


      }
      else if (lives == 1)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, RED.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, RED.to_333()) ;

        //drawing second column with RED color
        matrix.drawPixel(1, yR2, RED.to_333()) ;


      }

      //Impossible case scenario of attaining WHITE form
      else if (lives == 6)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(0, yR1, WHITE.to_333()) ;
        matrix.drawPixel(0, yR2, color.to_333()) ;
        matrix.drawPixel(0, yR3, WHITE.to_333()) ;

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
      initialize(30, 7);
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
      matrix.drawPixel(31, y, BLACK.to_333()) ;
      matrix.drawPixel(31, y + 1, BLACK.to_333()) ;
      matrix.drawPixel(31, y + 2, BLACK.to_333()) ;
      //drawing second column with BLACK color
      matrix.drawPixel(30, y + 1, BLACK.to_333()) ;
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

      if (y <= 0)
      {
        draw_WRT_lives(0, 0, color);
      }

      else if (y >= 13)
      {
        draw_WRT_lives(0, 13, color);
      }

      else if (y >= 0 && y <= 13)
      {
        draw_WRT_lives(0, y, color);
      }
    }
    void draw_WRT_lives(int x_arg, int y_arg, Color color)
    {
      int xC1 = 31, xC2 = 30;
      int yR1 = y_arg, yR2 = y_arg + 1, yR3 = y_arg + 2 ;
      matrix.setCursor(30, y_arg);
      if (lives == 5)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, PURPLE.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, PURPLE.to_333()) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(30, yR2, PURPLE.to_333()) ;

      }
      else if (lives == 4)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, BLUE.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, BLUE.to_333()) ;

        //drawing second column with BLUE color
        matrix.drawPixel(30, yR2, BLUE.to_333()) ;


      }
      else if (lives == 3)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, LIME.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, LIME.to_333()) ;

        //drawing second column with LIME color
        matrix.drawPixel(30, yR2, LIME.to_333()) ;


      }
      else if (lives == 2)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, ORANGE.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, ORANGE.to_333()) ;

        //drawing second column with ORANGE color
        matrix.drawPixel(30, yR2, ORANGE.to_333()) ;


      }
      else if (lives == 1)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, RED.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, RED.to_333()) ;

        //drawing second column with RED color
        matrix.drawPixel(30, yR2, RED.to_333()) ;


      }

      //Impossible case scenario of attaining WHITE form
      else if (lives == 6)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(31, yR1, WHITE.to_333()) ;
        matrix.drawPixel(31, yR2, color.to_333()) ;
        matrix.drawPixel(31, yR3, WHITE.to_333()) ;

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
    Crate() {
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

    bool is_activated()
    {
      return active;
    }

    // sets x and y private members
    Crate(int x_arg, int y_arg) {
      x = x_arg;
      y = y_arg;
    }

    // draws the crate (3x3 grid w/ white cross + red corners)
    void draw() {
      draw_with_rgb();
    }

    //moves the crate forward
    void move() {
      y-- ;
    }

    //checks if the crate has been hit
    void hit() {
      reset() ;
    }

    void activate() {
      //should be called at the 1.5 minute mark
      active = true ;
      x = 14;
      y = 13;
    }


    void reset() {
      x = 0;
      y = 0;
      active = false ;
    }

    // draws black where crate used to be
    void erase() {
      erase_with_rgb();
    }

  private:
    int x;
    int y;
    bool active = false;

    void initialize()
    {
      x = 14 ;
      y = 6 ;
      active = false;

    }

    void draw_with_rgb() {

      matrix.setCursor(14, 6);



      // draws first row of crate
      matrix.drawPixel(14, 6, WHITE.to_333());
      matrix.drawPixel(14, 9, WHITE.to_333());
      matrix.drawPixel(14, 7, RED.to_333());
      matrix.drawPixel(14, 8, RED.to_333());

      // draws second row of crate
      matrix.drawPixel(15, 6, RED.to_333());
      matrix.drawPixel(15, 7, RED.to_333());
      matrix.drawPixel(15, 8, RED.to_333());
      matrix.drawPixel(15, 9, RED.to_333());

      matrix.drawPixel(16, 6, RED.to_333());
      matrix.drawPixel(16, 7, RED.to_333());
      matrix.drawPixel(16, 8, RED.to_333());
      matrix.drawPixel(16, 9, RED.to_333());


      // draws third row of crate
      matrix.drawPixel(17, 6, WHITE.to_333());
      matrix.drawPixel(17, 9, WHITE.to_333());
      matrix.drawPixel(17, 7, RED.to_333());
      matrix.drawPixel(17, 8, RED.to_333());
    }

    void erase_with_rgb() {

      matrix.setCursor(14, 6);



      // draws first row of crate
      matrix.drawPixel(14, 6, BLACK.to_333());
      matrix.drawPixel(14, 9, BLACK.to_333());
      matrix.drawPixel(14, 7, BLACK.to_333());
      matrix.drawPixel(14, 8, BLACK.to_333());

      // draws second row of crate
      matrix.drawPixel(15, 6, BLACK.to_333());
      matrix.drawPixel(15, 7, BLACK.to_333());
      matrix.drawPixel(15, 8, BLACK.to_333());
      matrix.drawPixel(15, 9, BLACK.to_333());

      matrix.drawPixel(16, 6, BLACK.to_333());
      matrix.drawPixel(16, 7, BLACK.to_333());
      matrix.drawPixel(16, 8, BLACK.to_333());
      matrix.drawPixel(16, 9, BLACK.to_333());


      // draws third row of crate
      matrix.drawPixel(17, 6, BLACK.to_333());
      matrix.drawPixel(17, 9, BLACK.to_333());
      matrix.drawPixel(17, 7, BLACK.to_333());
      matrix.drawPixel(17, 8, BLACK.to_333());
    }

};

int Round( int input)
{
  double roundHelper ;
  int rounder ;
  roundHelper = double(double(input) / 3.0) ;
  rounder = roundHelper ;
  if ( double(roundHelper - rounder) >= 0.5 )
  {
    rounder++ ;
  }
  rounder -- ;
  if (rounder <= 114)
    return 1;
  else if (rounder > 114 && rounder <= 228)
    return 2;
  else if (rounder > 228 && rounder < 342)
    return 3;
}


//************************************************************************************************************************



class Game {

  public:

    void setup()
    {
      //drawing player 1 based on the type of player
      if (p1Choice == 1)
        //drawing classic for player 1
      {
        cp1.set_y(6);
        cp1.draw();
      }
      else if (p1Choice == 2)
        //drawing Slim Shady for player 1
      {
        ssp1.set_y(6);
        ssp1.draw();
      }
      else if (p1Choice == 3)
        //drawing Big Shaq for player 1
      {
        bsp1.set_y(5);
        bsp1.draw();
      }

      //drawing player 2 based on type of player
      if (p2Choice == 1)
        //drawing classic for player 2
      {
        cp2.set_y(6);
        cp2.draw();
      }
      else if (p2Choice == 2)
        //drawing Slim Shady for player 2
      {
        ssp2.set_y(6);
        ssp2.draw();
      }
      else if (p2Choice == 3)
        //drawing Big Shaq for player 2
      {
        bsp2.set_y(5);
        bsp2.draw();
      }
    }
    int B1Checker = 0, B2Checker = 0;

    void update(int potentiometer_value_p1, bool button_pressed_p1, int potentiometer_value_p2, bool button_pressed_p2)
    {

      time = millis();
      time_crate = millis();
      
      //keeps track of time
      if(array_p1C >= NUM_BULLETS)
      {
        if(B1Checker <= 1)
        {
          array_p1C = 0;
          B1Checker ++;
        }
      }
      if(array_p2C >= NUM_BULLETS)
      {
        if(B2Checker <= 1)
        {
          array_p2C = 0;
          B2Checker ++;
        }
      }


      

      //erasing bullets if they reach the end of the board
      for (int i = 0; i < NUM_BULLETS; i ++)
      {
        if (p1[i].get_x() > 31 || p1[i].get_x() < 0 )
        {
          p1[i].erase();
          p1[i].reset();
        }
        if (p2[i].get_x() > 31 || p2[i].get_x() < 0)
        {
          p2[i].erase();
          p2[i].reset();
        }
      }

      matrix.drawLine(0, 0, 0, 15, matrix.Color333(0, 0, 0));
      matrix.drawLine(31, 0, 31, 15, matrix.Color333(0, 0, 0));


      //Moving the players
      // getting y coordinate from potentiometer
      int rounder = CodCalc(potentiometer_value_p1) ;

      //moving player 1
      if (p1Choice == 1)
      {
        cp1.erase() ;
        cp1.set_y(rounder) ;
        cp1.draw() ;
      }
      else if (p1Choice == 2)
      {
        ssp1.erase();
        ssp1.set_y(rounder);
        ssp1.draw();
      }
      else if (p1Choice == 3)
      {
        bsp1.erase();
        bsp1.set_y(rounder);
        bsp1.draw();
      }




      // moving player 2
      rounder = CodCalc(potentiometer_value_p2);

      if (p2Choice == 1)
      {
        cp2.erase() ;
        cp2.set_y(rounder) ;
        cp2.draw() ;
      }
      else if (p2Choice == 2)
      {
        ssp2.erase();
        ssp2.set_y(rounder);
        ssp2.draw();
      }
      else if (p2Choice == 3)
      {
        bsp2.erase();
        bsp2.set_y(rounder);
        bsp2.draw();
      }

      //*****************************************************
      BulletMovement_Player1(button_pressed_p1);
      //moves player1's bullet^
      BulletMovement_Player2(button_pressed_p2);
      //moves player2's bullet^

      //****************************************************************************************

      //crate management
      
      if((time_crate - GameTime >= 90000) && (time_crate - GameTime) <= 95000 && present)
      {
        health.activate();
        health.draw();

        //checking if player 1 shoots the crate

        for(int i = 0; i < NUM_BULLETS; i++)
        { 
          if(p1[i].has_been_fired())
          {
            int xpos = p1[i].get_x();
            int ypos = p1[i].get_y();

            if(xpos == 14)
            {
              if(ypos >= 6 && ypos <= 9)
              {
                //erasing the crate
                present = false;
                health.reset();
                health.erase();

                p1[i].reset();
                p1[i].erase();

                //increasing the life of the player
                if(p1Choice == 1)
                {
                  cp1.Increase_Life();
                }
                else if(p1Choice == 2)
                {
                  ssp1.Increase_Life();
                }
                else if(p1Choice == 3)
                {
                  bsp1.Increase_Life();
                }
                
                break;
              }
            }
            
          }
        }
        if(present)
        {
          //checking if player 1 shoots the crate

          for(int i = 0; i < NUM_BULLETS; i++)
          {
            if(p2[i].has_been_fired())
            {
              int xpos = p2[i].get_x();
              int ypos = p2[i].get_y();

              if(xpos == 17)
              {
                if(ypos >= 6 && ypos <= 9)
                {
                  //erasing the crate
                  present = false;
                  health.reset();
                  health.erase();

                  p2[i].reset();
                  p2[i].erase();

                  //increasing the life of the player
                  if(p2Choice == 1)
                  {
                    cp2.Increase_Life();
                  }
                  else if(p2Choice == 2)
                  {
                    ssp2.Increase_Life();
                  }
                  else if(p2Choice == 3)
                  {
                    bsp2.Increase_Life();
                  }
                
                break;
              }
            }
            
          }
        }
        }
      }
      else
      {
        health.reset();
        health.erase();
      }

      //****************************************************************************************
      // checking for collision of bullets

      for (int i = 0; i < NUM_BULLETS; i++)
        //runs the loop for all the bullets for player 1 starting from the first one
      {
        int x1 = p1[i].get_x();
        //gets position for x
        int y1 = p1[i].get_y();
        //gets position for y

        if (p1[i].has_been_fired())
          //will check to seee if the bullet  at index 'i' has been fired. If it hasn't or has already been erased, then it wont enter into the following segment
        {
          for (int j = 0; j < NUM_BULLETS; j++)
            //runs the loop for all the bullets for player 1 starting from the first one
          {
            //gets co-ordinates for the bullet pos of player 2
            int x2 = p2[j].get_x();
            int y2 = p2[j].get_y();
            if (p2[j].has_been_fired())
              //will check to seee if the bullet at index 'i' has been fired. If it hasn't or has already been erased, then it wont enter into the following segment
            {
              if ((x1 == x2) && (y1 == y2))
                //will compare positional co-ordinates to check for collisions
              {
                //resets both bullets
                p1[i].reset();
                p2[j].reset();
                //breaks since the bullet 1 is non-existential at that index anymore
                break;
              }
            }
          }
        }
      }

      //*******************************************************************************************



      //*******************************************************************************************
      //checks if the players are getting hit
      //checking if player 1 is getting hit
      for (int i = 0; i < NUM_BULLETS; i++)
      {
        if (p2[i].has_been_fired())
        {
          int ypos = p2[i].get_y();
          int xpos = p2[i].get_x();
          if (p1Choice == 1)
          {
            ClassicHit(1, xpos, ypos, i);
          }
          else if (p1Choice == 2)
          {
            SsHit(1, xpos, ypos, i);
          }
          else if (p1Choice == 3)
          {
            Bshit(1, xpos, ypos, i);
          }
        }
      }

      //checking if player 2 is getting hit

      for (int i = 0; i < NUM_BULLETS; i++)
      {
        if (p1[i].has_been_fired())
        {
          int ypos = p1[i].get_y();
          int xpos = p1[i].get_x();
          if (p2Choice == 1)
          {
            ClassicHit(2, xpos, ypos, i);
          }
          else if (p2Choice == 2)
          {
            SsHit(2, xpos, ypos, i);
          }
          else if (p2Choice == 3)
          {
            Bshit(2, xpos, ypos, i);
          }
        }
      }





    }

    void Print_Winner()
    {
      int P1_lives, P2_lives;
      //matrix fill screen  with black

      if(p1Choice == 1)
      //drawing classic for player 1
      {
        P1_lives = cp1.get_lives();
      }
      else if(p1Choice == 2)
      //drawing Slim Shady for player 1
      {
        P1_lives = ssp1.get_lives();
      }
      else if(p1Choice == 3)
      //drawing Big Shaq for player 1
      {
        P1_lives = bsp1.get_lives();
      }

      //drawing player 2 based on type of player
      if(p2Choice == 1)
      //drawing classic for player 2
      {
        P2_lives = cp2.get_lives();
      }
      else if(p2Choice == 2)
      //drawing Slim Shady for player 2
      {
        P2_lives = ssp2.get_lives();
      }
      else if(p2Choice == 3)
      //drawing Big Shaq for player 2
      {
        P2_lives = bsp2.get_lives();
      }


      if(P1_lives > P2_lives)
      {
        // print_P1wins();
        print_p1Winner();
      }
      else
      {
      // print_P2wins();
      print_p2Winner();
    }

  }




  private:
    Classic_Player1 cp1;
    Classic_Player2 cp2;

    SlimShady_Player1 ssp1;
    SlimShady_Player2 ssp2;
    //int NUM_BULLETS = 80;
    BigShaq_Player1 bsp1;
    BigShaq_Player2 bsp2;
    Crate health;
    bool present = true;

    unsigned long time;
    long int t1_move, t2_move, t1_fire, t2_fire;
    long int time_crate;
    

    Cannonball p1[NUM_BULLETS];
    Cannonball p2[NUM_BULLETS];

    int array_p1C = 0, array_p2C = 0;
    //^ used to keep track of number of bullets fired by Players
    
    int CodCalc(int potval)
    {
      double roundHelper ;
      int rounder = 0;
      roundHelper = double(potval / 64.0) ;
      rounder = roundHelper ;
      if ( double(roundHelper - rounder) >= 0.5 )
      {
        rounder++ ;
      }

      rounder -- ;

      return rounder;
    }

    


    void BulletMoving_Player1()
    {
      stadium();
      if (time - t1_move >= 100)
        // enters the loop if enough time has elapsed (1 second)
      {
        for (int i = 0; i < NUM_BULLETS; i++)
          //runs the loop to check the bullets
        {

          if (p1[i].has_been_fired())
            //only if the 'fired' member variable for that bullet object is true, then it will enter in the loop
          {

            if (p1[i].get_x() >= 0 && p1[i].get_x() <= 31)
              //if the bullet is in the board vicinity, then it willmove it
            {
              p1[i].erase();
              p1[i].p1move();
              p1[i].draw();
            }

            /*else
              //attempt to solve the bullet erasing sequence
            {
              p1[i].reset();
            }*/


          }

        }
        // assigns the current amount of time elapsed to t1_move, which will continue to be used to determine
        // whether enough time has elapsed to enter into the loop.
        // note: time is updated AFTER going through the ENTIRE loop.
        t1_move = time;
      }

    }




    void BulletMoving_Player2()
    {


      if (time - t2_move >= 100)
        //checks the time variable for movement on the outside
      {

        for (int i = 0; i < NUM_BULLETS; i++)
          //runs the loop to check the bullets
        {

          if (p2[i].has_been_fired())
            //only if the 'fired' member variable for that bullet object is true, then it will enter in the loop
          {

            if ((p2[i].get_x() >= 0) && (p2[i].get_x() <= 31))
              //if the bullet is in the board vicinity, then it willmove it
            {
              p2[i].erase();
              p2[i].p2move();
              p2[i].draw();
            }

            /*else
              //attempt to solve the bullet erasing sequence
            {
              p2[i].reset();
              //will reset the bullets
            }*/


          }

        }

        t2_move = time;
      }

    }












    void BulletMovement_Player1(bool button_pressed_p1)
    {
      //moving canon ball in CP vs CP
      //for player 1
      if (p1Choice == 1)
      {
        int x1, y1 ;
        //getting the x co-ordinates and then adding 1 so that it shoots from the nozzle
        x1 = cp1.get_x() + 1 ;
        //getting the y co-ordinate and adding 1 because the nozzle is centrally places
        y1 = cp1.get_y() + 1 ;
        //time manipulation going on


        BulletMoving_Player1();


        //code for firing the bullets
        if (array_p1C < NUM_BULLETS)
          //checks if the player has bullets left in his arsenal: if he has, then the time loop will have some significance, if not, there is no point in entering
        {
          if (time - t1_fire >= 1000)
            //time checking variable
          {
            if (button_pressed_p1)
              //if the button has been pressed, it will enter, if not, there is not point in entering
            {

              p1[array_p1C].fire(x1, y1);
              //fires it at the position
              p1[array_p1C].p1move();
              //this part will move the bullet
              array_p1C++ ;
              //increases the bullet index

            }

            t1_fire = time;
            //updates the time variable

          }

        }

        else
          //prevents the player from firing more bullets
        {
          return;
        }
      }


      //code for slim shady player 1
      else if (p1Choice == 2)
      {
        int x1, y1 ;
        if (array_p1C % 2 == 1)
        {
          //getting the x co-ordinates and then adding 1 so that it shoots from the nozzle
          x1 = ssp1.get_x() + 1 ;
          //getting the y co-ordinate and adding 1 because the nozzle is down for the next bullet
          y1 = ssp1.get_y() + 1 ;
        }
        else if (array_p1C % 2 == 0)
        {
          //getting the x co-ordinates and then adding 1 so that it shoots from the nozzle
          x1 = ssp1.get_x() + 1 ;
          //getting the y co-ordinate and adding 1 because the nozzle is up for the first bullet
          y1 = ssp1.get_y();
        }

        BulletMoving_Player1();


        //code for firing the bullets
        if (array_p1C < NUM_BULLETS)
          //checks if the player has bullets left in his arsenal: if he has, then the time loop will have some significance, if not, there is no point in entering
        {
          if (time - t1_fire >= 1000)
            //time checking variable
          {
            if (button_pressed_p1)
              //if the button has been pressed, it will enter, if not, there is not point in entering
            {

              p1[array_p1C].fire(x1, y1);
              //fires it at the position
              p1[array_p1C].p1move();
              //this part will move the bullet
              array_p1C++ ;
              //increases the bullet index

            }

            t1_fire = time;
            //updates the time variable

          }

        }

        else
          //prevents the player from firing more bullets
        {
          return;
        }

      }



      //code for Big Shaq player 1
      else if (p1Choice == 3)
      {
        int x1c1, y1c1, x1c2, y1c2 ;
        x1c1 = 1;
        x1c2 = 1;
        y1c1 = bsp1.get_y();
        y1c2 = bsp1.get_y() + 3;


        BulletMoving_Player1();



        //code for firing the bullets
        if (array_p1C < NUM_BULLETS)
          //checks if the player has bullets left in his arsenal: if he has, then the time loop will have some significance, if not, there is no point in entering
        {
          if (time - t1_fire >= 1000)
            //time checking variable
          {
            if (button_pressed_p1)
              //if the button has been pressed, it will enter, if not, there is not point in entering
            {

              p1[array_p1C].fire(x1c1, y1c1);
              //fires it at the position
              p1[array_p1C].p1move();
              //this part will move the bullet
              array_p1C++ ;
              //increases the bullet index

              p1[array_p1C].fire(x1c2, y1c2);
              //fires it at the position
              p1[array_p1C].p1move();
              //this part will move the bullet
              array_p1C++ ;
              //increases the bullet index

            }

            t1_fire = time;
            //updates the time variable

          }

        }

        else
          //prevents the player from firing more bullets
        {
          return;
        }



      }

    }



    void BulletMovement_Player2(bool button_pressed_p2)
    {
      if (p2Choice == 1)
      {
        //for player 2
        int x2, y2 ;
        //getting the x co-ordinates and then adding 1 so that it shoots from the nozzle
        x2 = 30 ;
        //getting the y co-ordinate and adding 1 because the nozzle is centrally places
        y2 = cp2.get_y() + 1 ;

        BulletMoving_Player2();

        //code for firing the bullets
        if (array_p2C < NUM_BULLETS)
          //checks if the player has bullets left in his arsenal: if he has, then the time loop will have some significance, if not, there is no point in entering
        {
          if (time - t2_fire >= 1000)
            //time checking variable
          {
            if (button_pressed_p2)
              //if the button has been pressed, it will enter, if not, there is not point in entering
            {

              p2[array_p2C].fire(x2, y2);
              //fires it at the position
              p2[array_p2C].p2move();
              //this part will move the bullet
              array_p2C++ ;
              //increases the bullet index

            }

            t2_fire = time;
            //updates the time variable

          }

        }

        else
          //prevents the player from firing more bullets
        {
          return;
        }

      }


      //code for slim shady player 2
      else if (p2Choice == 2)
      {

        int x2, y2 ;
        if (array_p2C % 2 == 1)
        {
          //getting the x co-ordinates and then adding 1 so that it shoots from the nozzle
          x2 = ssp2.get_x() -1 ;
          //getting the y co-ordinate and adding 1 because the nozzle is down for the next bullet
          y2 = ssp2.get_y() + 1 ;
        }
        else if (array_p2C % 2 == 0)
        {
          //getting the x co-ordinates and then adding 1 so that it shoots from the nozzle
          x2 = ssp2.get_x() - 1 ;
          //getting the y co-ordinate and adding 1 because the nozzle is up for the first bullet
          y2 = ssp2.get_y();
        }

        BulletMoving_Player2();



        //code for firing the bullets
        if (array_p2C < NUM_BULLETS)
          //checks if the player has bullets left in his arsenal: if he has, then the time loop will have some significance, if not, there is no point in entering
        {
          if (time - t2_fire >= 1000)
            //time checking variable
          {
            if (button_pressed_p2)
              //if the button has been pressed, it will enter, if not, there is not point in entering
            {

              p2[array_p2C].fire(x2, y2);
              //fires it at the position
              p2[array_p2C].p2move();
              //this part will move the bullet
              array_p2C++ ;
              //increases the bullet index

            }

            t2_fire = time;
            //updates the time variable

          }

        }

        else
          //prevents the player from firing more bullets
        {
          return;
        }


      }


      //big shaq code for player 2
      else if (p2Choice == 3)
      {
        int x2c1, y2c1, x2c2, y2c2 ;
        x2c1 = 30;
        x2c2 = 30;
        y2c1 = bsp2.get_y();
        y2c2 = bsp2.get_y() + 3;


        BulletMoving_Player2();


        //code for firing the bullets
        if (array_p2C < NUM_BULLETS)
          //checks if the player has bullets left in his arsenal: if he has, then the time loop will have some significance, if not, there is no point in entering
        {
          if (time - t2_fire >= 1000)
            //time checking variable
          {
            if (button_pressed_p2)
              //if the button has been pressed, it will enter, if not, there is not point in entering
            {

              p2[array_p2C].fire(x2c1, y2c1);
              //fires it at the position
              p2[array_p2C].p2move();
              //this part will move the bullet
              array_p2C++ ;
              //increases the bullet index

              p2[array_p2C].fire(x2c2, y2c2);
              //fires it at the position
              p2[array_p2C].p2move();
              //this part will move the bullet
              array_p2C++ ;
              //increases the bullet index

            }

            t2_fire = time;
            //updates the time variable

          }

        }

        else
          //prevents the player from firing more bullets
        {
          return;
        }


      }

    }

    void ClassicHit(int pnum, int xpos, int ypos, int cnum)
    //this function accepts the x and y coordinates of the bullet to check for collision with classic type player
    //pnum represents the player number;ie. which player has the ball, and cnum represents the index of the canon

    {

      if (pnum == 1)
        //checks if the bullet is moving towards player 1
      {
        int yr1 = cp1.get_y();
        //gets y coordinate of player 1
        int yr2 = yr1 + 1, yr3 = yr1 + 2;
        //Classic occupies 3 y pixels

        if (xpos == 1)
          //it checks to see if the bullet has reached the second last column(x = 1)
        {
          //checking if tip gets hit
          if (ypos == yr2)
          {
            p2[cnum].reset();
            //erases the bullet at index cnum
            if (cp1.get_lives() <= 1)
              //checks if the players has any lives left before reducing them
            {
              cp1.hit();
              //hit will reduce the life of the player by on e
              Print_Winner();
              game_over();
              //runs game over sequence
              return;
              //breaks out of the function
            }
            else
            {
              cp1.hit();
              //will enter into this segment only if the player has more than 0 lives left
            }
          }
        }
        else if (xpos == 0)
          //this else if segment is for the last column; it checks if the the other ends of the classic player are hit
        {
          if ((ypos == yr1) || (ypos == yr3))
            //will check for either
          {
            p2[cnum].reset();
            //resets the bullet

            cp1.hit();

            //the same segment as before to check for the amount of lives left
            if (cp1.get_lives() <= 1)
            {
              cp1.hit();
              Print_Winner();
              game_over();
              return;
            }
            /*else
            {
              cp1.hit();
            }*/

          }
          /*else
            //will enter into this segment only if the bullet has reached the end of the board and not hit the player
          {
            p2[cnum].reset();
            //resets the bullet since itll be going out of bounds
          }*/
        }
      }

      //checking if player 2 is getting hit
      else if (pnum == 2)
      {
        int yr1 = cp2.get_y();
        //gets y coordinate of player 2
        int yr2 = yr1 + 1, yr3 = yr1 + 2;
        //Classic occupies 3 y pixels

        if (xpos == 30)
          //it checks to see if the bullet has reached the second last column(x = 30) in player 2's domain
        {
          //checking if tip gets hit
          if (ypos == yr2)
            //checking if tip gets hit
          {
            p1[cnum].reset();
            //resets the bullet
            if (cp2.get_lives() <= 1)
              //this will get the amount of lives of cp2
              //similar code as the above incoming
            {
              cp2.hit();
              Print_Winner();
              game_over();
              return;
            }
            else
            {
              cp2.hit();
            }
          }
        }
        else if (xpos == 31)
          //checks to see if it hits either of the ends of the player
        {
          if ((ypos == yr1) || (ypos == yr3))
          {
            p1[cnum].reset();
            cp2.hit();
            if (cp2.get_lives() <= 1)
            {
              cp2.hit();
              Print_Winner();
              game_over();
              return;
            }
            /*else
            {
              cp2.hit();
            }*/
          }
          /*else
          {
            p1[cnum].reset();
          }*/
        }
      }
    }



    void SsHit(int pnum, int xpos, int ypos, int cnum)
    //this function accepts the x and y coordinates of the bullet to check for collision with slim shady type player
    //pnum represents the player number;ie. which player has the ball, and cnum represents the index of the canon
    {
      if (pnum == 1)
        //checks if player 1 is being shot at
      {
        int yr1 = ssp1.get_y();
        //gets y co-ordinates for player 1
        int yr2 = yr1 + 1;
        //creates another variable yr to hold y co-ordinates of the second row pixel of slim shady

        //checking if the top of slim shady is getting hit
        if ((xpos == 1) && (((ypos == yr1) || (ypos == yr2))))
          //will enter in this segment only if the y-coordinate is either one of the two column pixels and xpos is 1
        {

          p2[cnum].reset();
          //will reset the bullet
          //attached below is the coding segment for life checking for slim shady p1
          if (ssp1.get_lives() <= 1)
          {
            ssp1.hit();
            Print_Winner();
            game_over();
            return;
          }
          else
          {
            ssp1.hit();
          }
        }


        else if (xpos == 0)
          //resetting bullets if they reach end of the board
        {
          p2[cnum].reset();
        }
      }

      else if (pnum == 2)
        //checks if player 1 is being shot at
      {
        int yr1 = ssp2.get_y();
        //gets y co-ordinates for player 1
        int yr2 = yr1 + 1;
        //creates another variable yr to hold y co-ordinates of the second row pixel of slim shady

        //checking if the top of slim shady is getting hit
        if ((xpos == 30) && ((ypos == yr1) || (ypos == yr2)))
          //will enter in this segment only if the y-coordinate is either one of the two column pixels and xpos is 30
        {
          p1[cnum].reset();
          //resets the bullet
          //life segment below
          if (ssp2.get_lives() <= 1)
          {
            ssp2.hit();
            Print_Winner();
            game_over();
            return;
          }
          else
          {
            ssp2.hit();
          }
        }

        else if (xpos == 31)
          //resetting bullets if they reach end of the board
        {
          p1[cnum].reset();
        }
      }

    }


    void Bshit(int pnum, int xpos, int ypos, int cnum)
    //this function accepts the x and y coordinates of the bullet to check for collision with big shaq type player
    //pnum represents the player number;ie. which player has the ball, and cnum represents the index of the canon
    {
      if (pnum == 1)
        //checks if it is player 1
      {
        int yr1 = bsp1.get_y();
        int yr2 = yr1 + 1;
        int yr3 = yr1 + 2;
        int yr4 = yr1 + 3;
        //obtaining 4 co-ordinate y-related points of big shaq

        //checking if the cannonball is in the top row or bottom row of BS
        if ((xpos == 1) && ((ypos == yr1) || (ypos == yr4)))
        {
          p2[cnum].reset();
          //will reset the bullet

          //life checker segment
          if (bsp1.get_lives() <= 1)
          {
            bsp1.hit();
            Print_Winner();
            game_over();
            return;
          }
          else
          {
            bsp1.hit();
          }

        }

        
        else if (xpos == 0 && ((ypos == yr2) || (ypos == yr3)))
          //checks if the canonball reaches column x = 0 and checks if it hits y2 and y3
        {
          p2[cnum].reset();

          //life checker segment
          if (bsp1.get_lives() <= 1)
          {
            bsp1.hit();
            Print_Winner();
            game_over();
            return;
          }
          else
          {
            bsp1.hit();
          }

        }
        //resetting cannonball if it reaches end of board
        /*else if (xpos == 0 && !((ypos == yr2) || (ypos == yr3)))
          //checks if the canonball reaches column x = 0 and checks if it doesnt hits y2 and y3
        {
          p2[cnum].reset();
        }*/


      }

      else if (pnum == 2)
      {
        int yr1 = bsp2.get_y();
        int yr2 = yr1 + 1;
        int yr3 = yr1 + 2;
        int yr4 = yr1 + 3;
        //obtaining 4 co-ordinate y-related points of big shaq

        //checking if the cannonball is in the top row of BS
        if ((xpos == 30) && ((ypos == yr1) || (ypos == yr4)))
        {
          p1[cnum].reset();
          //will reset the bullet

          //life checker segment
          if (bsp2.get_lives() <= 1)
          {
            bsp2.hit();
            Print_Winner();
            game_over();
            return;
          }
          else
          {
            bsp2.hit();
          }

        }

        //resetting cannonball if it reaches end of board
        else if (xpos == 31 && ((ypos == yr2) || (ypos == yr3)))
          //checks if the canonball reaches column x = 31 and checks if it hits y2 and y3
        {
          p1[cnum].reset();

          //life checker segment
          if (bsp2.get_lives() <= 1)
          {
            bsp2.hit();
            Print_Winner();
            game_over();
            return;
          }
          else
          {
            bsp2.hit();
          }

        }
        /*else if (xpos == 31 && !((ypos == yr2) || (ypos == yr3)))
          //checks if the canonball reaches column x = 0 and checks if it doesnt hits y2 and y3
        {
          p1[cnum].reset();
        }*/
      }

    }
};

//************************************************************************************************************************












Game game;
//long int GameTime = 0;
// see http://arduino.cc/en/Reference/Setup

void setup() {
  Serial.begin(9600);
  pinMode(10, INPUT);//button of player 1
  //pinMode(10, INPUT);//button of player 2
  matrix.begin();

  int pot1, pot2;//readers for the potentiometer values for the selection
  int p1selection, p2selection;//variables relating to the pot1 and the pot2 values
  bool p1 = false , p2 = false;//checks if the button has been pressed

  IntroSequence_SpaceWars();
  
    Print_P1();
    delay(2000);

    do
    {
    pot1 = analogRead(5);
    p1selection = Round(pot1);
    if(p1selection <= 1)
    {
      Classic_Selection();
    }
    else if(p1selection == 2)
    {
      SlimShady_Selection();
    }
    else
    {
      BigShaq_Selection();
    }
    p1 = (digitalRead(10) == HIGH);

    }while(p1 != true);
    p1Choice = p1selection;

    Print_P2();
    delay(2000);

    do
    {
    pot2 = analogRead(4);
    p2selection = Round(pot2);
    if(p2selection <= 1)
    {
      Classic_Selection();
    }
    else if(p2selection == 2)
    {
      SlimShady_Selection();
    }
    else
    {
      BigShaq_Selection();
    }
    p2 = (digitalRead(11) == HIGH);

    }while(p2 != true);
    p2Choice = p2selection;
    print_ready_sequence();
  game.setup();

  GameTime = millis();
  stadium();
}


long int GameTimeManager = 0;

void loop() {
  //player 1 input below
  if (GAMEOVER)
  {
    exit(0) ;
  }
  GameTimeManager = millis();
  int potentiometer_value_player1 = analogRead(5);//for player 1
  int potentiometer_value_player2 = analogRead(4);//for player 2
  //player 2 input below
  bool button_pressed_player1 = (digitalRead(10) == HIGH);
  bool button_pressed_player2 = (digitalRead(11) == HIGH);


  game.update(potentiometer_value_player1, button_pressed_player1, potentiometer_value_player2, button_pressed_player2);



}



/*void time(int time)
  {

  matrix.setCursor(13,5);
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7,0,0));

  matrix.print(time);
  delay(1500);
  }*/

void stadium()
{
  if (GameTimeManager - GameTime < 60000)
  {
    //drawing timer lines
    matrix.drawLine(5, 0, 5, 15, matrix.Color333(2, 4, 0));
    matrix.drawLine(26, 0, 26, 15, matrix.Color333(2, 4, 0));
    matrix.drawLine(6, 0, 6, 15, matrix.Color333(0, 4, 4));
    matrix.drawLine(25, 0, 25, 15, matrix.Color333(0, 4, 4));

    matrix.drawLine(7, 0, 7, 15, matrix.Color333(4, 4, 4));
    matrix.drawLine(24, 0, 24, 15, matrix.Color333(4, 4, 4));
    // Draws the diagonal lines
    matrix.drawLine(8, 0, 13, 5, matrix.Color333(4, 4, 4));
    matrix.drawLine(23, 0, 18, 5, matrix.Color333(4, 4, 4));
    matrix.drawLine(8, 15, 13, 10, matrix.Color333(4, 4, 4));
    matrix.drawLine(23, 15, 18, 10, matrix.Color333(4, 4, 4));
    matrix.drawLine(8, 15, 13, 10, matrix.Color333(4, 4, 4));
    matrix.drawLine(13, 10, 18, 10, matrix.Color333(4, 4, 4));
    matrix.drawLine(13, 10, 13, 5, matrix.Color333(4, 4, 4));
    matrix.drawLine(18, 10, 18, 5, matrix.Color333(4, 4, 4));
    matrix.drawLine(13, 5, 18, 5, matrix.Color333(4, 4, 4));

  }

  if (GameTimeManager - GameTime >= 60000 && GameTimeManager - GameTime <= 120000)
  {
    matrix.drawLine(6, 0, 6, 15, matrix.Color333(0, 4, 4));
    matrix.drawLine(25, 0, 25, 15, matrix.Color333(0, 4, 4));
    matrix.drawLine(5, 0, 5, 15, matrix.Color333(0, 0, 0));
    matrix.drawLine(26, 0, 26, 15, matrix.Color333(0, 0, 0));

    matrix.drawLine(7, 0, 7, 15, matrix.Color333(4, 4, 4));
    matrix.drawLine(24, 0, 24, 15, matrix.Color333(4, 4, 4));
    // Draws the diagonal lines
    matrix.drawLine(8, 0, 13, 5, matrix.Color333(4, 4, 4));
    matrix.drawLine(23, 0, 18, 5, matrix.Color333(4, 4, 4));
    matrix.drawLine(8, 15, 13, 10, matrix.Color333(4, 4, 4));
    matrix.drawLine(23, 15, 18, 10, matrix.Color333(4, 4, 4));
    matrix.drawLine(8, 15, 13, 10, matrix.Color333(4, 4, 4));
    matrix.drawLine(13, 10, 18, 10, matrix.Color333(4, 4, 4));
    matrix.drawLine(13, 10, 13, 5, matrix.Color333(4, 4, 4));
    matrix.drawLine(18, 10, 18, 5, matrix.Color333(4, 4, 4));
    matrix.drawLine(13, 5, 18, 5, matrix.Color333(4, 4, 4));
  }

  else if (GameTimeManager - GameTime > 120000 && GameTimeManager - GameTime <= 160000)
  {
    matrix.drawLine(6, 0, 6, 15, matrix.Color333(0, 0, 0));
    matrix.drawLine(25, 0, 25, 15, matrix.Color333(0, 0, 0));
    matrix.drawLine(5, 0, 5, 15, matrix.Color333(0, 0, 0));
    matrix.drawLine(26, 0, 26, 15, matrix.Color333(0, 0, 0));
    matrix.drawLine(7, 0, 7, 15, matrix.Color333(4, 4, 4));
    matrix.drawLine(24, 0, 24, 15, matrix.Color333(4, 4, 4));
    // Draws the diagonal lines
    matrix.drawLine(8, 0, 13, 5, matrix.Color333(4, 4, 4));
    matrix.drawLine(23, 0, 18, 5, matrix.Color333(4, 4, 4));
    matrix.drawLine(8, 15, 13, 10, matrix.Color333(4, 4, 4));
    matrix.drawLine(23, 15, 18, 10, matrix.Color333(4, 4, 4));
    matrix.drawLine(8, 15, 13, 10, matrix.Color333(4, 4, 4));
    matrix.drawLine(13, 10, 18, 10, matrix.Color333(4, 4, 4));
    matrix.drawLine(13, 10, 13, 5, matrix.Color333(4, 4, 4));
    matrix.drawLine(18, 10, 18, 5, matrix.Color333(4, 4, 4));
    matrix.drawLine(13, 5, 18, 5, matrix.Color333(4, 4, 4));
  }
  else if (GameTimeManager - GameTime > 160000 && GameTimeManager - GameTime <= 180100)
  {
    matrix.drawLine(6, 0, 6, 15, matrix.Color333(0, 0, 0));
    matrix.drawLine(25, 0, 25, 15, matrix.Color333(0, 0, 0));
    matrix.drawLine(5, 0, 5, 15, matrix.Color333(0, 0, 0));
    matrix.drawLine(26, 0, 26, 15, matrix.Color333(0, 0, 0));
    matrix.drawLine(7, 0, 7, 15, matrix.Color333(7, 0, 0));
    matrix.drawLine(24, 0, 24, 15, matrix.Color333(7, 0, 0));
    // Draws the diagonal lines
    matrix.drawLine(8, 0, 13, 5, matrix.Color333(7, 0, 0));
    matrix.drawLine(23, 0, 18, 5, matrix.Color333(7, 0, 0));
    matrix.drawLine(8, 15, 13, 10, matrix.Color333(7, 0, 0));
    matrix.drawLine(23, 15, 18, 10, matrix.Color333(7, 0, 0));
    matrix.drawLine(8, 15, 13, 10, matrix.Color333(7, 0, 0));
    matrix.drawLine(13, 10, 18, 10, matrix.Color333(7, 0, 0));
    matrix.drawLine(13, 10, 13, 5, matrix.Color333(7, 0, 0));
    matrix.drawLine(18, 10, 18, 5, matrix.Color333(7, 0, 0));
    matrix.drawLine(13, 5, 18, 5, matrix.Color333(7, 0, 0));
  }
  else if (GameTimeManager - GameTime > 180000)
  {
    game.Print_Winner();
    game_over();
  }


}



void print_ready_sequence() {


  //fills screen with black
  matrix.fillScreen(matrix.Color333(0, 0, 0));

  matrix.setCursor(1, 0);
  matrix.setTextSize(1);

  // prints "READY" in blue one letter at a time
  matrix.setTextColor(matrix.Color333(0, 0, 4));
  matrix.print("R");
  delay(75);

  matrix.setTextColor(matrix.Color333(0, 0, 4));
  matrix.print("E");
  delay(75);

  matrix.setTextColor(matrix.Color333(0, 0, 4));
  matrix.print("A");
  delay(75);

  matrix.setTextColor(matrix.Color333(0, 0, 4));
  matrix.print("D");
  delay(75);

  matrix.setTextColor(matrix.Color333(0, 0, 4));
  matrix.print("Y");

  delay(500);

  // prints the outer slashes in yellow
  matrix.setCursor(1, 8);
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(4, 4, 0));
  matrix.print("\\");

  matrix.setCursor(25, 8);
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(4, 4, 0));
  matrix.print("/");

  delay(250);

  //prints the inner slashes in white
  matrix.setCursor(7, 8);
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7, 7, 7));
  matrix.print("\\");

  matrix.setCursor(19, 8);
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7, 7, 7));
  matrix.print("/");

  delay(250);

  //counts down from 3 in red
  matrix.setCursor(13, 8);
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print("3");

  delay(1250);

  // changes from 3 to 2
  matrix.setCursor(13, 8);
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(0, 0, 0));
  matrix.print("3");

  matrix.setCursor(13, 8);
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print("2");

  delay(1250);

  // changes from 2 to 1
  matrix.setCursor(13, 8);
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(0, 0, 0));
  matrix.print("2");

  matrix.setCursor(13, 8);
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print("1");

  delay(1250);

  // fills screen with black
  matrix.fillScreen(matrix.Color333(0, 0, 0));

  // fills screen with "GO"
  matrix.setCursor(5, 1);
  matrix.setTextSize(2);

  matrix.setTextColor(matrix.Color333(0, 4, 0));
  matrix.print("GO");

  // creates border along the left and right edges
  matrix.fillRect(0, 0, 3, 16, matrix.Color333(7, 0, 0));
  matrix.fillRect(29, 0, 31, 16, matrix.Color333(7, 0, 0));

  delay(300);

  // replaces the screen with black
  matrix.fillScreen(matrix.Color333(0, 0, 0));

}




void game_over() {

  GAMEOVER = true ;

  //clears up the screen
  matrix.fillScreen(matrix.Color333(0, 0, 0));

  matrix.setCursor(1, 0);
  matrix.setTextSize(1);

  /*Printing Game Over alphabet by alphabet and
    with a delay for a cool effect*/
  matrix.setTextColor(matrix.Color333(0, 0, 3));
  matrix.print("G");
  delay(250);

  matrix.setTextColor(matrix.Color333(0, 0, 3));
  matrix.print("A");
  delay(250);

  matrix.setTextColor(matrix.Color333(0, 0, 3));
  matrix.print("M");
  delay(250);

  matrix.setTextColor(matrix.Color333(0, 0, 3));
  matrix.print("E");
  delay(250);

  matrix.setTextColor(matrix.Color333(0, 0, 3));
  matrix.print("  O");
  delay(250);

  matrix.setTextColor(matrix.Color333(0, 0, 3));
  matrix.print("V");
  delay(250);

  matrix.setTextColor(matrix.Color333(0, 0, 3));
  matrix.print("E");
  delay(250);

  matrix.setTextColor(matrix.Color333(0, 0, 3));
  matrix.print("R");
  delay(250);

  matrix.setCursor(25, 0);
  matrix.setTextSize(1);

  //printing stars for aesthetics
  matrix.setTextColor(matrix.Color333(4, 4, 0));
  matrix.print("*");

  matrix.setCursor(0, 9);
  matrix.setTextSize(1);

  matrix.setTextColor(matrix.Color333(4, 4, 0));
  matrix.print("*");

  delay(1000);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
}

//*****************************************************************
void Classic_Selection()
{
  // Draws Classic Player and highlights the box showing
  // player chose the classic player
  matrix.fillScreen(BLACK.to_333());

  matrix.drawRect(0, 4, 7, 6, matrix.Color333(4, 4, 4));


  //Draws an arrow on the bottom

  matrix.drawPixel(3, 11, RED.to_333());
  matrix.drawLine(2, 12, 4, 12, matrix.Color333(4, 0, 0));
  matrix.drawLine(1, 13, 5, 13, matrix.Color333(4, 0, 0));
  matrix.drawLine(3, 14, 3, 15, matrix.Color333(4, 0, 0));

  // Draws Classic Player
  matrix.drawLine(2, 7, 4, 7, matrix.Color333(0, 4, 4));
  matrix.drawPixel(3, 6, YELLOW.to_333());
  matrix.drawPixel(3, 7, AQUA.to_333());

  // Draws Slim Shady

  matrix.drawLine(15, 7, 16, 7, matrix.Color333(0, 4, 4));
  matrix.drawLine(15, 6, 16, 6, matrix.Color333(4, 4, 0));


  // Draws Big Shaq

  matrix.drawLine(26, 7, 29, 7, matrix.Color333(4, 4, 0));
  matrix.drawPixel(26, 6, YELLOW.to_333());
  matrix.drawPixel(29, 6, YELLOW.to_333());
  matrix.drawPixel(27, 7, AQUA.to_333());
  matrix.drawPixel(28, 7, AQUA.to_333());

  //Draws roman numeral 1
  matrix.drawLine(2, 0, 4, 0, matrix.Color333(0, 0, 4));
  matrix.drawPixel(3, 1, BLUE.to_333());
  matrix.drawLine(2, 2, 4, 2, matrix.Color333(0, 0, 4));

  //Draws roman numeral 2
  matrix.drawLine(14, 0, 16, 0, matrix.Color333(0, 0, 4));
  matrix.drawPixel(15, 1, BLUE.to_333());
  matrix.drawLine(14, 2, 16, 2, matrix.Color333(0, 0, 4));
  matrix.drawPixel(16, 1, BLUE.to_333());
  matrix.drawPixel(17, 0, BLUE.to_333());
  matrix.drawPixel(17, 2, BLUE.to_333());

  //Draws roman numeral 3
  matrix.drawLine(25, 0, 27, 0, matrix.Color333(0, 0, 4));
  matrix.drawPixel(26, 1, BLUE.to_333());
  matrix.drawLine(25, 2, 27, 2, matrix.Color333(0, 0, 4));
  matrix.drawPixel(27, 1, BLUE.to_333());
  matrix.drawLine(28, 0, 28, 2, matrix.Color333(0, 0, 4));
  matrix.drawPixel(29, 0, BLUE.to_333());
  matrix.drawPixel(29, 2, BLUE.to_333());



  //Draws the line barriers between the options
  matrix.drawLine(9, 0, 9, 15, matrix.Color333(4, 0, 4));
  matrix.drawLine(22, 0, 22, 15, matrix.Color333(4, 0, 4));


}

void SlimShady_Selection()
{
  matrix.fillScreen(BLACK.to_333());
  // Draws slim shady player and highlights the box showing
  // player chose slim shady
  matrix.drawRect(12, 4, 8, 6, matrix.Color333(4, 4, 4));


  //Draws an arrow on the bottom

  matrix.drawPixel(15, 11, RED.to_333());
  matrix.drawLine(14, 12, 16, 12, matrix.Color333(4, 0, 0));
  matrix.drawLine(13, 13, 17, 13, matrix.Color333(4, 0, 0));
  matrix.drawLine(15, 14, 15, 15, matrix.Color333(4, 0, 0));



  // Draws Classic Player
  matrix.drawLine(2, 7, 4, 7, matrix.Color333(0, 4, 4));
  matrix.drawPixel(3, 6, YELLOW.to_333());
  matrix.drawPixel(3, 7, AQUA.to_333());

  // Draws Slim Shady

  matrix.drawLine(15, 7, 16, 7, matrix.Color333(0, 4, 4));
  matrix.drawLine(15, 6, 16, 6, matrix.Color333(4, 4, 0));


  // Draws Big Shaq

  matrix.drawLine(26, 7, 29, 7, matrix.Color333(4, 4, 0));
  matrix.drawPixel(26, 6, YELLOW.to_333());
  matrix.drawPixel(29, 6, YELLOW.to_333());
  matrix.drawPixel(27, 7, AQUA.to_333());
  matrix.drawPixel(28, 7, AQUA.to_333());

  //Draws roman numeral 1
  matrix.drawLine(2, 0, 4, 0, matrix.Color333(0, 0, 4));
  matrix.drawPixel(3, 1, BLUE.to_333());
  matrix.drawLine(2, 2, 4, 2, matrix.Color333(0, 0, 4));

  //Draws roman numeral 2
  matrix.drawLine(14, 0, 16, 0, matrix.Color333(0, 0, 4));
  matrix.drawPixel(15, 1, BLUE.to_333());
  matrix.drawLine(14, 2, 16, 2, matrix.Color333(0, 0, 4));
  matrix.drawPixel(16, 1, BLUE.to_333());
  matrix.drawPixel(17, 0, BLUE.to_333());
  matrix.drawPixel(17, 2, BLUE.to_333());

  //Draws roman numeral 3
  matrix.drawLine(25, 0, 27, 0, matrix.Color333(0, 0, 4));
  matrix.drawPixel(26, 1, BLUE.to_333());
  matrix.drawLine(25, 2, 27, 2, matrix.Color333(0, 0, 4));
  matrix.drawPixel(27, 1, BLUE.to_333());
  matrix.drawLine(28, 0, 28, 2, matrix.Color333(0, 0, 4));
  matrix.drawPixel(29, 0, BLUE.to_333());
  matrix.drawPixel(29, 2, BLUE.to_333());



  //Draws the line barriers between the options
  matrix.drawLine(9, 0, 9, 15, matrix.Color333(4, 0, 4));
  matrix.drawLine(22, 0, 22, 15, matrix.Color333(4, 0, 4));

}

void BigShaq_Selection()
{
  matrix.fillScreen(BLACK.to_333());

  // Draws Big Shaq player and highlights the box showing
  // player chose Big Shaq

  matrix.drawRect(24, 4, 8, 6, matrix.Color333(4, 4, 4));

  //Draws an arrow on the bottom

  matrix.drawPixel(27, 11, RED.to_333());
  matrix.drawLine(26, 12, 28, 12, matrix.Color333(4, 0, 0));
  matrix.drawLine(25, 13, 29, 13, matrix.Color333(4, 0, 0));
  matrix.drawLine(27, 14, 27, 15, matrix.Color333(4, 0, 0));


  // Draws Classic Player
  matrix.drawLine(2, 7, 4, 7, matrix.Color333(0, 4, 4));
  matrix.drawPixel(3, 6, YELLOW.to_333());
  matrix.drawPixel(3, 7, AQUA.to_333());

  // Draws Slim Shady

  matrix.drawLine(15, 7, 16, 7, matrix.Color333(0, 4, 4));
  matrix.drawLine(15, 6, 16, 6, matrix.Color333(4, 4, 0));


  // Draws Big Shaq

  matrix.drawLine(26, 7, 29, 7, matrix.Color333(4, 4, 0));
  matrix.drawPixel(26, 6, YELLOW.to_333());
  matrix.drawPixel(29, 6, YELLOW.to_333());
  matrix.drawPixel(27, 7, AQUA.to_333());
  matrix.drawPixel(28, 7, AQUA.to_333());

  //Draws roman numeral 1
  matrix.drawLine(2, 0, 4, 0, matrix.Color333(0, 0, 4));
  matrix.drawPixel(3, 1, BLUE.to_333());
  matrix.drawLine(2, 2, 4, 2, matrix.Color333(0, 0, 4));

  //Draws roman numeral 2
  matrix.drawLine(14, 0, 16, 0, matrix.Color333(0, 0, 4));
  matrix.drawPixel(15, 1, BLUE.to_333());
  matrix.drawLine(14, 2, 16, 2, matrix.Color333(0, 0, 4));
  matrix.drawPixel(16, 1, BLUE.to_333());
  matrix.drawPixel(17, 0, BLUE.to_333());
  matrix.drawPixel(17, 2, BLUE.to_333());

  //Draws roman numeral 3
  matrix.drawLine(25, 0, 27, 0, matrix.Color333(0, 0, 4));
  matrix.drawPixel(26, 1, BLUE.to_333());
  matrix.drawLine(25, 2, 27, 2, matrix.Color333(0, 0, 4));
  matrix.drawPixel(27, 1, BLUE.to_333());
  matrix.drawLine(28, 0, 28, 2, matrix.Color333(0, 0, 4));
  matrix.drawPixel(29, 0, BLUE.to_333());
  matrix.drawPixel(29, 2, BLUE.to_333());



  //Draws the line barriers between the options
  matrix.drawLine(9, 0, 9, 15, matrix.Color333(4, 0, 4));
  matrix.drawLine(22, 0, 22, 15, matrix.Color333(4, 0, 4));
}


void Print_P1()
{

  matrix.fillScreen(matrix.Color333(0, 0, 0));

  matrix.setCursor(7, 1);

  matrix.setTextSize(2);

  matrix.setTextColor(matrix.Color333(7, 7, 7));
  matrix.print("P");


  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print("1");


}

void Print_P2()
{

  matrix.fillScreen(matrix.Color333(0, 0, 0));

  matrix.setCursor(6, 1);

  matrix.setTextSize(2);

  matrix.setTextColor(matrix.Color333(7, 7, 7));
  matrix.print("P");


  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print("2");


}





void IntroSequence_SpaceWars()
{
  matrix.setCursor(1, 0);
  matrix.setTextSize(1);

  /*printing TEAM OMEGA alphabet by alphabet
    with a delay for an effect and also our team logo :)*/
  matrix.setTextColor(matrix.Color333(7, 7, 7));
  matrix.print("T");
  delay(80);

  matrix.setTextColor(matrix.Color333(7, 7, 7));
  matrix.print("E");
  delay(80);

  matrix.setTextColor(matrix.Color333(7, 7, 7));
  matrix.print("A");
  delay(80);

  matrix.setTextColor(matrix.Color333(7, 7, 7));
  matrix.print("M");
  delay(80);

  matrix.setCursor(1, 9);
  matrix.setTextSize(1);

  //Printing OMEGA
  matrix.setTextColor(matrix.Color333(4, 0, 4));
  matrix.print("O");
  delay(80);
  matrix.setTextColor(matrix.Color333(4, 0, 4));
  matrix.print("M");
  delay(80);
  matrix.setTextColor(matrix.Color333(4, 0, 4));
  matrix.print("E");
  delay(80);
  matrix.setTextColor(matrix.Color333(4, 0, 4));
  matrix.print("G");
  delay(80);
  matrix.setTextColor(matrix.Color333(4, 0, 4));
  matrix.print("A");
  delay(250);

  //places omega symbol
  matrix.drawPixel(25, 6, RED.to_333());
  matrix.drawPixel(31, 6, RED.to_333());
  delay(50);
  matrix.drawPixel(26, 6, ORANGE.to_333());
  matrix.drawPixel(30, 6, ORANGE.to_333());
  delay(50);
  matrix.drawPixel(27, 6, YELLOW.to_333());
  matrix.drawPixel(29, 6, YELLOW.to_333());
  delay(50);

  matrix.drawPixel(26, 5, LIME.to_333());
  matrix.drawPixel(30, 5, LIME.to_333());
  delay(50);
  matrix.drawPixel(25, 4, GREEN.to_333());
  matrix.drawPixel(31, 4, GREEN.to_333());
  delay(50);

  matrix.drawPixel(25, 3, AQUA.to_333());
  matrix.drawPixel(31, 3, AQUA.to_333());
  delay(50);

  matrix.drawPixel(26, 2, BLUE.to_333());
  matrix.drawPixel(30, 2, BLUE.to_333());
  delay(50);

  matrix.drawPixel(27, 1, PURPLE.to_333());
  matrix.drawPixel(29, 1, PURPLE.to_333());
  delay(50);
  matrix.drawPixel(28, 1, PURPLE.to_333());


  /*following code adds a color changing effect to the
     omega logo
  */
  matrix.drawPixel(30, 6, RED.to_333());
  delay(40);
  matrix.drawPixel(29, 6, RED.to_333());
  delay(40);
  matrix.drawPixel(30, 5, RED.to_333());
  delay(40);
  matrix.drawPixel(31, 4, RED.to_333());
  delay(40);
  matrix.drawPixel(31, 3, RED.to_333());
  delay(40);
  matrix.drawPixel(30, 2, RED.to_333());
  delay(40);
  matrix.drawPixel(29, 1, RED.to_333());
  delay(40);
  matrix.drawPixel(28, 1, RED.to_333());
  delay(40);
  matrix.drawPixel(27, 1, RED.to_333());
  delay(40);
  matrix.drawPixel(26, 2, RED.to_333());
  delay(40);
  matrix.drawPixel(25, 3, RED.to_333());
  delay(40);
  matrix.drawPixel(25, 4, RED.to_333());
  delay(40);
  matrix.drawPixel(26, 5, RED.to_333());
  delay(40);
  matrix.drawPixel(27, 6, RED.to_333());
  delay(40);
  matrix.drawPixel(26, 6, RED.to_333());


  matrix.drawPixel(25, 6, AQUA.to_333());
  matrix.drawPixel(26, 6, BLUE.to_333());
  delay(40);
  matrix.drawPixel(27, 6, AQUA.to_333());
  delay(40);
  matrix.drawPixel(26, 5, BLUE.to_333());
  delay(40);
  matrix.drawPixel(25, 4, AQUA.to_333());
  delay(40);
  matrix.drawPixel(25, 3, BLUE.to_333());
  delay(40);
  matrix.drawPixel(26, 2, AQUA.to_333());
  delay(40);
  matrix.drawPixel(27, 1, BLUE.to_333());
  delay(40);
  matrix.drawPixel(28, 1, AQUA.to_333());
  delay(40);
  matrix.drawPixel(29, 1, BLUE.to_333());
  delay(40);
  matrix.drawPixel(30, 2, AQUA.to_333());
  delay(40);
  matrix.drawPixel(31, 3, BLUE.to_333());
  delay(40);
  matrix.drawPixel(31, 4, AQUA.to_333());
  delay(40);
  matrix.drawPixel(30, 5, BLUE.to_333());
  delay(40);
  matrix.drawPixel(29, 6, AQUA.to_333());
  delay(40);
  matrix.drawPixel(30, 6, BLUE.to_333());
  delay(40);
  matrix.drawPixel(31, 6, AQUA.to_333());
  delay(40);

  delay(500);

  for (int i = 2; i <= 32; i++)
  {
    matrix.fillRect(1, 0, i, 16, BLACK.to_333());
    delay(22);
  }

  delay(100);

  matrix.fillScreen(matrix.Color333(0, 0, 0));






  matrix.fillScreen(matrix.Color333(0, 0, 0));

  matrix.fillRect(0, 0, 32, 9, WHITE.to_333());



  matrix.setCursor(1, 1);

  matrix.setTextColor(matrix.Color333(0, 0, 0));
  matrix.print("S");
  delay(200);

  matrix.setTextColor(matrix.Color333(0, 0, 0));
  matrix.print("P");
  delay(200);

  matrix.setTextColor(matrix.Color333(0, 0, 0));
  matrix.print("A");
  delay(200);

  matrix.setTextColor(matrix.Color333(0, 0, 0));
  matrix.print("C");
  delay(200);

  matrix.setTextColor(matrix.Color333(0, 0, 0));
  matrix.print("E");
  delay(200);


  matrix.setCursor(4, 9);
  matrix.setTextSize(1);



  //Printing BRAWL
  matrix.setTextColor(matrix.Color333(7, 7, 7));
  matrix.print("W");
  delay(150);
  matrix.setTextColor(matrix.Color333(7, 7, 7));
  matrix.print("A");
  delay(150);
  matrix.setTextColor(matrix.Color333(7, 7, 7));
  matrix.print("R");
  delay(150);
  matrix.setTextColor(matrix.Color333(7, 7, 7));
  matrix.print("S");
  delay(3000);


  for (int i = 1; i <= 32; i++)
  {
    matrix.fillRect(0, 0, i, 16, BLACK.to_333());
    delay(22);
  }

  delay(100);

  matrix.fillScreen(matrix.Color333(0, 0, 0));


  // matrix.fillScreen(matrix.Color333(0, 0, 0));
  //matrix.setTextColor(matrix.Color333(7, 7, 7));
  //matrix.print("L");
  //delay(550);


}

void print_p1Winner()
{
   matrix.fillScreen(matrix.Color333(0, 0, 0));
   matrix.setCursor(5, 1);
   matrix.setTextSize(1);
   matrix.setTextColor(matrix.Color333(4, 0, 0));
   matrix.print("P");
   matrix.setTextColor(matrix.Color333(4, 4, 4));
   delay(250);
   matrix.print(1);
   delay(250);

   matrix.setCursor(1, 9);
   matrix.setTextSize(1);
   matrix.setTextColor(matrix.Color333(0, 4, 4));
   matrix.print("W");
   delay(100);
   matrix.print("i");
   delay(100);
   matrix.print("n");
   delay(100);
   matrix.print("s");
   delay(100);
   matrix.print("!");
   delay(400);
  
   matrix.drawLine(20, 8, 25, 8, matrix.Color333(4, 4, 0));
   matrix.drawLine(21, 7, 24, 7, matrix.Color333(4, 4, 0));
   matrix.drawLine(22, 6, 23, 6, matrix.Color333(4, 4, 0));
   matrix.drawLine(22, 5, 23, 5, matrix.Color333(4, 4, 0));
   matrix.drawPixel(21, 4, YELLOW.to_333());
   matrix.drawPixel(24, 4, YELLOW.to_333());
   matrix.drawPixel(19, 3, YELLOW.to_333());
   matrix.drawPixel(26, 3, YELLOW.to_333());
   matrix.drawPixel(19, 2, YELLOW.to_333());
   matrix.drawPixel(26, 2, YELLOW.to_333());
   matrix.drawPixel(20, 0, YELLOW.to_333());
   matrix.drawPixel(25, 0, YELLOW.to_333());
   matrix.drawPixel(19, 1, YELLOW.to_333());
   matrix.drawPixel(26, 1, YELLOW.to_333());
   matrix.drawPixel(25, 4, YELLOW.to_333());
   matrix.drawPixel(20, 4, YELLOW.to_333());

 
   matrix.drawPixel(27, 1, YELLOW.to_333());
   matrix.drawLine(28, 2, 28, 3, matrix.Color333(4, 4, 0));
   matrix.drawPixel(27, 4, YELLOW.to_333());

   matrix.drawPixel(18, 1, YELLOW.to_333());
   matrix.drawLine(17, 2, 17, 3, matrix.Color333(4, 4, 0));
   matrix.drawPixel(18, 4, YELLOW.to_333());

   delay(3000);
  
}

void print_p2Winner()
{
  matrix.fillScreen(matrix.Color333(0, 0, 0));
   matrix.setCursor(4, 1);
   matrix.setTextSize(1);
   matrix.setTextColor(matrix.Color333(4, 0, 0));
   matrix.print("P");
   matrix.setTextColor(matrix.Color333(4, 4, 4));
   delay(250);
   matrix.print(2);
   delay(250);

   matrix.setCursor(1, 9);
   matrix.setTextSize(1);
   matrix.setTextColor(matrix.Color333(0, 4, 4));
   matrix.print("W");
   delay(100);
   matrix.print("i");
   delay(100);
   matrix.print("n");
   delay(100);
   matrix.print("s");
   delay(100);
   matrix.print("!");
   delay(450);
  
   matrix.drawLine(20, 8, 25, 8, matrix.Color333(4, 4, 0));
   matrix.drawLine(21, 7, 24, 7, matrix.Color333(4, 4, 0));
   matrix.drawLine(22, 6, 23, 6, matrix.Color333(4, 4, 0));
   matrix.drawLine(22, 5, 23, 5, matrix.Color333(4, 4, 0));
   matrix.drawPixel(21, 4, YELLOW.to_333());
   matrix.drawPixel(24, 4, YELLOW.to_333());
   matrix.drawPixel(19, 3, YELLOW.to_333());
   matrix.drawPixel(26, 3, YELLOW.to_333());
   matrix.drawPixel(19, 2, YELLOW.to_333());
   matrix.drawPixel(26, 2, YELLOW.to_333());
   matrix.drawPixel(20, 0, YELLOW.to_333());
   matrix.drawPixel(25, 0, YELLOW.to_333());
   matrix.drawPixel(19, 1, YELLOW.to_333());
   matrix.drawPixel(26, 1, YELLOW.to_333());
   matrix.drawPixel(25, 4, YELLOW.to_333());
   matrix.drawPixel(20, 4, YELLOW.to_333());

 
   matrix.drawPixel(27, 1, YELLOW.to_333());
   matrix.drawLine(28, 2, 28, 3, matrix.Color333(4, 4, 0));
   matrix.drawPixel(27, 4, YELLOW.to_333());

   matrix.drawPixel(18, 1, YELLOW.to_333());
   matrix.drawLine(17, 2, 17, 3, matrix.Color333(4, 4, 0));
   matrix.drawPixel(18, 4, YELLOW.to_333());

   delay(3000);
}
