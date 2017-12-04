void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

class BigShaq_Player1 {
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
      int yR1 = y, yR2 = y + 1, yR3 = y + 2, yR4 = y + 3;

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
      int yR1 = y, yR2 = y + 1, yR3 = y + 2, yR4 = y + 3;
      matrix.setCursor(0, y);
      if(lives == 5)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color.to_333()) ;
        matrix.drawPixel(xC1, yR2, color.to_333()) ;
        matrix.drawPixel(xC1, yR3, color.to_333()) ;
        matrix.drawPixel(xC1, yR4, color.to_333()) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(xC2, yR1, PURPLE.to_333()) ;
        matrix.drawPixel(xC2, yR4, PURPLE.to_333()) ;
        
      }
      else if(lives == 4)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color.to_333()) ;
        matrix.drawPixel(xC1, yR2, color.to_333()) ;
        matrix.drawPixel(xC1, yR3, color.to_333()) ;
        matrix.drawPixel(xC1, yR4, color.to_333()) ;
        //drawing second column with BLUE color
        matrix.drawPixel(xC2, yR1, BLUE.to_333()) ;
        matrix.drawPixel(xC2, yR4, BLUE.to_333()) ;
        
      }
      else if(lives == 3)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color.to_333()) ;
        matrix.drawPixel(xC1, yR2, color.to_333()) ;
        matrix.drawPixel(xC1, yR3, color.to_333()) ;
        matrix.drawPixel(xC1, yR4, color.to_333()) ;
        //drawing second column with LIME color
        matrix.drawPixel(xC2, yR1, LIME.to_333()) ;
        matrix.drawPixel(xC2, yR4, LIME.to_333()) ;
        
      }
      else if(lives == 2)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color.to_333()) ;
        matrix.drawPixel(xC1, yR2, color.to_333()) ;
        matrix.drawPixel(xC1, yR3, color.to_333()) ;
        matrix.drawPixel(xC1, yR4, color.to_333()) ;
        //drawing second column with ORANGE color
        matrix.drawPixel(xC2, yR1, ORANGE.to_333()) ;
        matrix.drawPixel(xC2, yR4, ORANGE.to_333()) ;
        
      }
      else if(lives == 1)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color.to_333()) ;
        matrix.drawPixel(xC1, yR2, color.to_333()) ;
        matrix.drawPixel(xC1, yR3, color.to_333()) ;
        matrix.drawPixel(xC1, yR4, color.to_333()) ;
        //drawing second column with RED color
        matrix.drawPixel(xC2, yR1, RED.to_333()) ;
        matrix.drawPixel(xC2, yR4, RED.to_333()) ;
        
      }

      //Impossible case scenario of attaining WHITE form
     else if(lives == 6)
     {
      //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color.to_333()) ;
        matrix.drawPixel(xC1, yR2, color.to_333()) ;
        matrix.drawPixel(xC1, yR3, color.to_333()) ;
        matrix.drawPixel(xC1, yR4, color.to_333()) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(xC2, yR1, WHITE.to_333()) ;
        matrix.drawPixel(xC2, yR4, WHITE.to_333()) ;
     }
    }
};

class Classic_Player1 {
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
      int yR1 = y, yR2 = y + 1, yR3 = y + 2 ;
      matrix.setCursor(0, y);
      if(lives == 5)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color.to_333()) ;
        matrix.drawPixel(xC1, yR2, color.to_333()) ;
        matrix.drawPixel(xC1, yR3, color.to_333()) ;
        //drawing second column with PURPLE color
        matrix.drawPixel(xC2, yR2, PURPLE.to_333()) ;
       
      }
      else if(lives == 4)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color.to_333()) ;
        matrix.drawPixel(xC1, yR2, color.to_333()) ;
        matrix.drawPixel(xC1, yR3, color.to_333()) ;
        
        //drawing second column with BLUE color
        matrix.drawPixel(xC2, yR2, BLUE.to_333()) ;
        
        
      }
      else if(lives == 3)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color.to_333()) ;
        matrix.drawPixel(xC1, yR2, color.to_333()) ;
        matrix.drawPixel(xC1, yR3, color.to_333()) ;
        
        //drawing second column with LIME color
        matrix.drawPixel(xC2, yR2, LIME.to_333()) ;
       
        
      }
      else if(lives == 2)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color.to_333()) ;
        matrix.drawPixel(xC1, yR2, color.to_333()) ;
        matrix.drawPixel(xC1, yR3, color.to_333()) ;
        
        //drawing second column with ORANGE color
        matrix.drawPixel(xC2, yR2, ORANGE.to_333()) ;
        
        
      }
      else if(lives == 1)
      {
        //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color.to_333()) ;
        matrix.drawPixel(xC1, yR2, color.to_333()) ;
        matrix.drawPixel(xC1, yR3, color.to_333()) ;
       
        //drawing second column with RED color
        matrix.drawPixel(xC2, yR2, RED.to_333()) ;
        
        
      }

      //Impossible case scenario of attaining WHITE form
     else if(lives == 6)
     {
      //drawing first column with the AQUA argument
        matrix.drawPixel(xC1, yR1, color.to_333()) ;
        matrix.drawPixel(xC1, yR2, color.to_333()) ;
        matrix.drawPixel(xC1, yR3, color.to_333()) ;
        
        //drawing second column with PURPLE color
        matrix.drawPixel(xC2, yR2, WHITE.to_333()) ;
        
     }
    }
};
