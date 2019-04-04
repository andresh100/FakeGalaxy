//
//  wormhole.hpp
//  Wormhole
//
//  Created by andre anh alissa on 4/11/17.
//  Copyright Â¬Â© 2017 HoleCorp. All rights reserved.
//

#ifndef wormhole_hpp
#define wormhole_hpp
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Bullet;
class NormalBullet;
class Enemy;
class EnemyChill;
class EnemyBoss;

struct color {
    double red;
    double green;
    double blue;
};

class Player {
public:
    // Default constructor
    /**
     * Requires: nothing
     * Modifies: player's name, xlocation, ylocation, life, width, height, life, and color
     * Effects: sets default values for the variables it modifies
     */
    Player();
    
    // Parameter constructor
    /**
     * Requires: player's name, xlocation, ylocation, life, width, height, life, and color
     * Modifies: player's name, xlocation, ylocation, life, width, height, life, and color
     * Effects: sets values for the variables it modifies
     */
    Player(string n, int playerxLoc, int playeryLoc, int w, int h, int li, color c);
    
    // Move method
    /**
     *  Requires: string
     *  Modifies: player's xlocation and ylocation
     *  Effects: change values of player's xlocation and ylocation
     */
    void move(string direction);
    
    // Shoot method
    /**
     *  Requires: nothing
     *  Modifies: NormalBullet vector and the last bullet in it
     *  Effects: pushes back a NormalBullet in the NormalBullet vector and
     *            sets the bullet's location to the player's location
     */
    void NormalShoot();
    
    // Setters and getters
    /**
     * Requires: nothing for getters
     *           a value for setters
     * Modifies: nothing for getters
     *           a value for setters
     * Effects: returns a value for getters
     *          changes a value for setters
     */
    void setName(string n);
    string getName() const;
    void setPlayerxLocation(int playerxLoc);
    void setPlayeryLocation(int playeryLoc);
    int getPlayerxLocation() const;
    int getPlayeryLocation() const;
    void setLife(int l);
    int getLife() const;
    void setScore(int s);
    int getScore() const;
    void setWidth(int w);
    int getWidth() const;
    void setHeight(int h);
    int getHeight() const;
    void set_color(color c);
    virtual void set_color(double r, double g, double b);
    
    // Draw method
    /**
     *  Requires: nothing
     *  Modifies: player's spaceship
     *  Effects: draws player's spaceship
     */
    void draw();
    
    // Hitted method
    /**
     *  Requires: two ints
     *  Modifies: nothing
     *  Effects: checks if player has been hit by the x and y coords passed in and returns true or false
     */
    bool hitted(int x_in, int y_in) const;
    
    // Hitted method
    /**
     *  Requires: bullet
     *  Modifies: nothing
     *  Effects: checks if player has been hit by the bullet passed in and returns true or false
     */
    bool hitted(const Bullet &b) const;
    
    // Plus_score method
    /**
     *  Requires: int
     *  Modifies: player's score
     *  Effects: increases player's score
     */
    void plus_score(int x);
    
    // Minus_life method
    /**
     *  Requires: int
     *  Modifies: player's life
     *  Effects: decreases player's life
     */
    void minus_life(int x);
    
    // Vector of NormalBullets
    vector<NormalBullet> normal;
    
private:
    
    //Fields
    int life; // Player's life
    string name; // Player's name
    int score; // Player's score
    int playerxLocation; // Player's xlocation
    int playeryLocation; // Player's ylocation
    int width; // Player's width
    int height; // Player's height
    color fill; // Player's color
};

class Bullet {
public:
    // Default constructor
    /**
     *  Requires: nothing
     *  Modifies: bullet's width, height, xlocation, ylocation, speed, and color
     *  Effects: sets default values for bullet's width, height, xlocation, ylocation, speed, and color
     */
    Bullet();
    
    // Parameter constructor
    /**
     *  Requires: bullet's width, height, xlocation, ylocation, speed, and color
     *  Modifies: bullet's width, height, xlocation, ylocation, speed, and color
     *  Effects: sets values for bullet's width, height, xlocation, ylocation, speed, and color
     */
    Bullet(int xLoc, int yLoc, int sp, int w, int h, color c);
    
    // Destructor
    ~Bullet();
    
    // Setters and getters
    /**
     * Requires: nothing for getters
     *           a value for setters
     * Modifies: nothing for getters
     *           a value for setters
     * Effects: returns a value for getters
     *          changes a value for setters
     */
    void setLocation(int xLoc, int yLoc);
    int getxLocation() const;
    int getyLocation() const;
    void setSpeed(int sp);
    int getSpeed() const;
    void setWidth(int w);
    int getWidth() const;
    void setHeight(int h);
    int getHeight() const;
    void set_color(color c);
    virtual void set_color(double r, double g, double b);
    
    // Pure virtual Hit method
    /**
     *  Requires: EnemyChill
     *  Modifies : nothing
     *  Effects : overridden by child class
     */
    virtual bool hit(EnemyChill e) const = 0;
    
    // Move method
    /**
     *  Requires: two ints
     *  Modifies: bullet's xlocation and ylocation
     *  Effects: changes values of bullet's xlocation and ylocation
     */
    void move(int x, int y);
    
    // Pure virtual Draw method
    /**
     *  Requires: nothing
     *  Modifies: nothing
     *  Effects: overridden by child class
     */
    virtual void draw() const = 0;
    
protected:
    
    // Fields
    int width; // Bullet's width
    int height; // Bullet's height
    int xLocation; // Bullet's xlocation
    int yLocation; // Bullet's ylocation
    int speed; // Bullet's speed
    color fill; // Bullet's color
};

class NormalBullet : public Bullet {
public:
    // Default constructor
    /**
     *  Requires: nothing
     *  Modifies: bullet's width, height, xlocation, ylocation, speed, and color
     *  Effects: sets default values for bullet's width, height, xlocation, ylocation, speed, and color by calling Bullet constructor
     */
    NormalBullet();
    
    // Hit method
    /**
     *  Requires: EnemyChill
     *  Modifies: nothing
     *  Effects: checks if the bullet hits an enemy and returns true or false
     */
    virtual bool hit(EnemyChill e) const override;
    
    // EnemyHit method
    /**
     *  Requires: player
     *  Modifies: nothing
     *  Effects: checks if the bullet hits the player and returns true or false
     */
    bool enemyHit(Player p) const;
    
    // Draw method
    /**
     *  Requires: nothing
     *  Modifies: bullet
     *  Effects: draws the bullet
     */
    virtual void draw() const override;
    
};

class Enemy {
public:
    // Default constructor
    /**
     *  Requires: nothing
     *  Modifies: enemy's width, height, life, xlocation, ylocation, speed, and color
     *  Effects: sets default values for enemy's width, height, life, xlocation, ylocation, speed, and color
     */
    Enemy();
    
    // Setters and getters
    /**
     * Requires: nothing for getters
     *           a value for setters
     * Modifies: nothing for getters
     *           a value for setters
     * Effects: returns a value for getters
     *          changes a value for setters
     */
    void setLife(int l);
    int getLife() const;
    void setEnemyxLocation(int enemyxLoc);
    void setEnemyyLocation(int enemyyLoc);
    int getEnemyxLocation() const;
    int getEnemyyLocation() const;
    void setSpeed(int s);
    int getSpeed() const;
    void setWidth(int w);
    int getWidth() const;
    void setHeight(int h);
    int getHeight() const;
    double get_fill() const;
    void set_color(color c);
    virtual void set_color(double r, double g, double b);
    
    // Pure virtual Hitted method
    /**
     *  Requires: two ints
     *  Modifies: nothing
     *  Effects: overridden by child class
     */
    virtual bool hitted(int x_in, int y_in) const = 0;
    
    // Pure virtual Hitted method
    /**
     *  Requires: player
     *  Modifies: nothing
     *  Effects: overridden by child class
     */
    virtual bool hitted(const Player &p) const = 0;
    
    // Pure virtual Hitted method
    /**
     *  Requires: bullet
     *  Modifies: nothing
     *  Effects: overridden by child class
     */
    virtual bool hitted(const Bullet &b) const = 0;
    
    // Touch method
    /**
     *  Requires: player
     *  Modifies: nothing
     *  Effects: checks if the enemy touches the player and returns true or false
     */
    bool touch(Player player1);
    
    // Move method
    /**
     *  Requires: two ints
     *  Modifies: enemy's xlocation and ylocation
     *  Effects: changes enemy's xlocation and ylocation
     */
    void move(int x_off, int y_off);
    
    // Pure virtual Draw method
    /**
     *  Requires: nothing
     *  Modifies: nothing
     *  Effects: overridden by child class
     */
    virtual void draw() const = 0;
    
protected:
    
    // Fields
    int life; // Enemy's life
    int enemyxLocation; // Enemy's xlocation
    int enemyyLocation; // Enemy's ylocation
    int speed; // Enemy's speed
    int width; // Enemy's width
    int height; // Enemy's height
    color fill; // Enemy's color
};

class EnemyChill : public Enemy {
public:
    // Default constructor
    /**
     *  Requires: nothing
     *  Modifies: enemy's width, height, life, xlocation, ylocation, speed, and color
     *  Effects: sets default values for enemy's width, height, life, xlocation, ylocation, speed, and color by calling enemy's constructor, but sets life to 1
     */
    EnemyChill();
    
    // Vector of EnemyChills
    vector<EnemyChill> enemy1;
    
    // Draw method
    /**
     *  Requires: nothing
     *  Modifies: EnemyChill's spaceship
     *  Effects: draws EnemyChill's spaceship
     */
    virtual void draw() const override;
    
    // Hitted method
    /**
     *  Requires: two ints
     *  Modifies: nothing
     *  Effects: checks if EnemyChill hits the x and y coords passed in and returns true or false
     */
    virtual bool hitted(int x_in, int y_in) const override;
    
    // Hitted method
    /**
     *  Requires: player
     *  Modifies: nothing
     *  Effects: checks if EnemyChill hits the player and returns true or false
     */
    virtual bool hitted(const Player &p) const override;
    
    // Hitted method
    /**
     *  Requires: bullet
     *  Modifies: nothing
     *  Effects: checks if EnemyChill hits the bullet and returns true or false
     */
    virtual bool hitted(const Bullet &b) const override;
};

class EnemyBoss : public Enemy {
public:
    // Default constructor
    /**
     *  Requires: nothing
     *  Modifies: enemy's width, height, life, xlocation, ylocation, speed, and color
     *  Effects: sets default values for enemy's width, height, life, xlocation, ylocation, speed, and color by calling enemy's constructor, but sets life to 10
     */
    EnemyBoss();
    
    // Vector of EnemyBosses
    vector<EnemyBoss> enemy2;
    
    // Draw method
    /**
     *  Requires: nothing
     *  Modifies: EnemyBoss
     *  Effects: draws EnemyBoss
     */
    virtual void draw() const override;
    
    // Hitted method
    /**
     *  Requires: two ints
     *  Modifies: nothing
     *  Effects: checks if EnemyBoss hits the x and y coords passed in and returns true or false
     */
    virtual bool hitted(int x_in, int y_in) const override;
    
    // Hitted method
    /**
     *  Requires: player
     *  Modifies: nothing
     *  Effects: checks if EnemyBoss hits the player and returns true or false
     */
    virtual bool hitted(const Player &p) const override;
    
    // Hitted method
    /**
     *  Requires: bullet
     *  Modifies: nothing
     *  Effects: checks if EnemyBoss hits the bullet and returns true or false
     */
    virtual bool hitted(const Bullet &b) const override;
    
private:
    
    // Fields
    vector<NormalBullet> enemyBullet; // Vector of NormalBullets
};

class Shape {
public:
    // Constructors
    Shape();
    Shape(double a, double p, color f);
    Shape(color f);
    
    // Getters and setters
    virtual double get_area() const;
    virtual double get_perimeter() const;
    virtual color get_fill() const;
    
    virtual void set_color(color c);
    virtual void set_color(double r, double g, double b);
    
    /**
     * Requires: nothing
     * Modifies: nothing (canvas to be drawn on)
     * Effects: draws the shape on the canvas
     */
    virtual void draw() const = 0;
    
protected:
    
    // Fields
    double area;
    double perimeter;
    
    virtual void calc_area_peri() = 0;
    color fill;
};

class Point2D {
public:
    //Constructors
    Point2D();
    Point2D(int x_in, int y_in);
    
    // Getters and setters
    int get_x() const;
    int get_y() const;
    
    void set_x(int x_in);
    void set_y(int y_in);
    void set_point(int x_in, int y_in);
    
    // Move method
    void move_point(int x_offset, int y_offset);
    
    // returns the distance between two points
    static double distance_between(int x1, int y1, int x2, int y2);
private:
    
    // Fields
    int x;
    int y;
};

class Rectangle : public Shape {
public:
    
    // Constructors
    Rectangle();
    Rectangle(double l, double w);
    Rectangle(double l, double w, color c);
    Rectangle(color c);
    
    // Getters and setters
    double get_length() const;
    double get_width() const;
    
    void set_length(double l);
    void set_width(double w);
    
    // override draw method from Shape
    virtual void draw() const override;
protected:
    // Modifies: area and perimeter
    // Will access length and width directly
    virtual void calc_area_peri() override;
    
    // Fields
    double length;
    double width;
};

class Rectangle_Coord : public Rectangle {
public:
    // Constructor
    Rectangle_Coord();
    
    // Getters and setters
    Point2D get_top_left() const;
    int get_top_left_x() const;
    int get_top_left_y() const;
    
    Point2D get_top_right() const;
    int get_top_right_x() const;
    int get_top_right_y() const;
    
    Point2D get_bottom_left() const;
    int get_bottom_left_x() const;
    int get_bottom_left_y() const;
    
    Point2D get_bottom_right() const;
    int get_bottom_right_x() const;
    int get_bottom_right_y() const;
    
    void set_top_left(int x_in, int y_in);
    
    // Move method
    void move(int x_offset, int y_offset);
    
    // Draw method
    virtual void draw() const override;
    
    // returns true if rectangle overlaps with point
    // returns false otherwise
    bool is_overlapping(int x_in, int y_in) const;
    
    // Requires: width and height of r are <= width and height of self
    // returns true if rectangle overlaps with parameter
    // returns false otherwise
    
    // if any of r's four corners overlap, return true
    // of all four of r's corners do not overlap, return false
    // call is_overlapping(int, int)
    bool is_overlapping(const Rectangle_Coord &r) const;
private:
    
    // Fields
    Point2D top_left;
};


#endif /* wormhole_hpp */



