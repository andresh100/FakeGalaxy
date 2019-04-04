//
//  wormhole.cpp
//  Wormhole
//
//  Created by andre anh alissa on 4/11/17.
//  Copyright Â© 2017 HoleCorp. All rights reserved.
//

#include "wormhole.hpp"
#include "graphics.hpp"


int lowerWidth = 0;
int upperWidth = 600;
int lowerHeight = 0;
int upperHeight = 400;

Player::Player() {
    name = "Player";
    playerxLocation = 4;
    playeryLocation = 4;
    life = 10;
    width = 4;
    height = 4;
    fill.red = fill.blue = fill.green = 0;
    score = 0;
}

Player::Player(string n, int playerxLoc, int playeryLoc, int w, int h, int li, color c){
    name = n;
    playerxLocation = playerxLoc;
    playeryLocation = playeryLoc;
    life = li;
    width = w;
    height = h;
    fill = c;
    score = 0;
}

void Player::move(string direction) {
    if (direction == "left") {
        playerxLocation = playerxLocation - 5;
    }
    else if (direction == "right") {
        playerxLocation = playerxLocation + 5;
    }
    else if (direction == "up") {
        playeryLocation = playeryLocation - 5;
    }
    else if (direction == "down") {
        playeryLocation = playeryLocation + 5;
    }
}

void Player::NormalShoot() {
    normal.push_back(NormalBullet());
    normal.back().setLocation(getPlayerxLocation(), getPlayeryLocation());
    
}

void Player::setName(string n) {
    name = n;
}

string Player::getName() const {
    return name;
}

void Player::setPlayerxLocation(int playerxLoc) {
    playerxLocation = playerxLoc;
}
void Player::setPlayeryLocation(int playeryLoc) {
    playeryLocation = playeryLoc;
}

int Player::getPlayerxLocation() const {
    return playerxLocation;
}

int Player::getPlayeryLocation() const {
    return playeryLocation;
}

void Player::setLife(int l) {
    life = l;
}

int Player::getLife() const {
    return life;
}

void Player::setScore(int s) {
    score = s;
}

int Player::getScore() const {
    return score;
}

void Player::setWidth(int w) {
    width = w;
}

int Player::getWidth() const {
    return width;
}

void Player::setHeight(int h) {
    height = h;
}

int Player::getHeight() const {
    return height;
}

void Player::set_color(color c) {
    fill = c;
}

void Player::set_color(double r, double g, double b) {
    fill = { r, g, b };
}

void Player::draw() {
    int row2 = 8;
    int col2 = 9;
    
    vector< vector <bool> > spaceShip(row2, vector <bool>(col2, false));
    spaceShip[0][4] = true;
    spaceShip[1][4] = true;
    spaceShip[2][0] = true;
    spaceShip[2][4] = true;
    spaceShip[2][8] = true;
    spaceShip[3][0] = true;
    spaceShip[3][3] = true;
    spaceShip[3][4] = true;
    spaceShip[3][5] = true;
    spaceShip[3][8] = true;
    spaceShip[4][0] = true;
    spaceShip[4][1] = true;
    spaceShip[4][3] = true;
    spaceShip[4][4] = true;
    spaceShip[4][5] = true;
    spaceShip[4][7] = true;
    spaceShip[4][8] = true;
    spaceShip[5][0] = true;
    spaceShip[5][1] = true;
    spaceShip[5][2] = true;
    spaceShip[5][3] = true;
    spaceShip[5][4] = true;
    spaceShip[5][5] = true;
    spaceShip[5][6] = true;
    spaceShip[5][7] = true;
    spaceShip[5][8] = true;
    spaceShip[6][0] = true;
    spaceShip[6][1] = true;
    spaceShip[6][2] = true;
    spaceShip[6][3] = true;
    spaceShip[6][4] = true;
    spaceShip[6][5] = true;
    spaceShip[6][6] = true;
    spaceShip[6][7] = true;
    spaceShip[6][8] = true;
    spaceShip[7][0] = true;
    spaceShip[7][1] = true;
    spaceShip[7][4] = true;
    spaceShip[7][7] = true;
    spaceShip[7][8] = true;
    
    glBegin(GL_QUADS);
    glColor3f(fill.red, fill.green, fill.blue);
    for (int i = 0; i < col2; i++) {
        for (int j = 0; j < row2; j++) {
            if (spaceShip[j][i]) {
                glVertex2i(Player::getPlayerxLocation() + i * Player::getWidth(), Player::getPlayeryLocation() + j * Player::getHeight());
                glVertex2i(Player::getPlayerxLocation() + (i + 1) * Player::getWidth(), Player::getPlayeryLocation() + j * Player::getHeight());
                glVertex2i(Player::getPlayerxLocation() + (i + 1) * Player::getWidth(), Player::getPlayeryLocation() + (j + 1) * Player::getHeight());
                glVertex2i(Player::getPlayerxLocation() + i * Player::getWidth(), Player::getPlayeryLocation() + (j + 1) * Player::getHeight());
            }
        }
    }
    glEnd();
}

bool Player::hitted(int x_in, int y_in) const {
    return (x_in >= Player::getPlayerxLocation() &&
            x_in <= Player::getPlayerxLocation() + Player::getWidth() * 9 &&
            y_in >= Player::getPlayeryLocation() &&
            y_in <= Player::getPlayeryLocation() + Player::getHeight() * 8);
}

bool Player::hitted(const Bullet &b) const {
    if (hitted(b.getxLocation(), b.getyLocation()) ||
        hitted(b.getxLocation() + b.getWidth(), b.getyLocation()) ||
        hitted(b.getxLocation(), b.getyLocation() + b.getHeight() * 2) ||
        hitted(b.getxLocation() + b.getWidth(), b.getyLocation() + b.getHeight() * 2)) {
        return true;
    }
    else {
        return false;
    }
}

void Player::plus_score(int x) {
    score += x;
}

void Player::minus_life(int x) {
    life -= x;
}

Bullet::Bullet() {
    width = 4;
    height = 4;
    xLocation = 4;
    yLocation = 4;
    speed = 4;
    fill.red = fill.blue = fill.green = 0;
}

Bullet::Bullet(int xLoc, int yLoc, int sp, int w, int h, color c) {
    xLocation = xLoc;
    yLocation = yLoc;
    speed = sp;
    width = w;
    height = h;
    fill = c;
}

Bullet::~Bullet() {
}

void Bullet::setLocation(int xLoc, int yLoc) {
    xLocation = xLoc;
    yLocation = yLoc;
}

int Bullet::getxLocation() const {
    return xLocation;
}

int Bullet::getyLocation() const {
    return yLocation;
}

void Bullet::setSpeed(int sp) {
    speed = sp;
}

int Bullet::getSpeed() const {
    return speed;
}

void Bullet::setWidth(int w) {
    width = w;
}

int Bullet::getWidth() const {
    return width;
}

void Bullet::setHeight(int h) {
    height = h;
}

int Bullet::getHeight() const {
    return height;
}

void Bullet::set_color(color c) {
    fill = c;
}

void Bullet::set_color(double r, double g, double b) {
    fill = { r, g, b };
}

void Bullet::move(int x_in, int y_in) {
    xLocation += x_in;
    yLocation += y_in;
}

NormalBullet::NormalBullet() : Bullet() {
}

bool NormalBullet::hit(EnemyChill e) const {
    if (getxLocation() == e.getEnemyxLocation() && getyLocation() == e.getEnemyyLocation()) {
        return true;
    }
    return false;
}

bool NormalBullet::enemyHit(Player p) const {
    if (getxLocation() == p.getPlayerxLocation() && getyLocation() == p.getPlayeryLocation()) {
        return true;
    }
    return false;
    
}

void NormalBullet::draw() const {
    int col = 1;
    int row = 2;
    
    vector< vector <bool> > normal_bul(row, vector <bool>(col, true));
    
    glBegin(GL_QUADS);
    glColor3f(fill.red, fill.green, fill.blue);
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (normal_bul[j][i]) {
                glVertex2i(NormalBullet::getxLocation() + i * NormalBullet::getWidth(), NormalBullet::getyLocation() + j * NormalBullet::getHeight());
                glVertex2i(NormalBullet::getxLocation() + (i + 1) * NormalBullet::getWidth(), NormalBullet::getyLocation() + j * NormalBullet::getHeight());
                glVertex2i(NormalBullet::getxLocation() + (i + 1) * NormalBullet::getWidth(), NormalBullet::getyLocation() + (j + 1) * NormalBullet::getHeight());
                glVertex2i(NormalBullet::getxLocation() + i * NormalBullet::getWidth(), NormalBullet::getyLocation() + (j + 1) * NormalBullet::getHeight());
            }
        }
    }
    glEnd();
}

Enemy::Enemy() {
    width = 4;
    height = 4;
    life = 10;
    enemyxLocation = 4;
    enemyyLocation = 4;
    speed = 4;
    fill.red = fill.blue = fill.green = 0;
}

void Enemy::setLife(int l) {
    life = l;
}

int Enemy::getLife() const {
    return life;
}

void Enemy::setEnemyxLocation(int enemyxLoc) {
    enemyxLocation = enemyxLoc;
}

void Enemy::setEnemyyLocation(int enemyyLoc) {
    enemyyLocation = enemyyLoc;
}

int Enemy::getEnemyxLocation() const {
    return enemyxLocation;
}

int Enemy::getEnemyyLocation() const {
    return enemyyLocation;
}

void Enemy::setSpeed(int s) {
    speed = s;
}

int Enemy::getSpeed() const {
    return speed;
}

void Enemy::setWidth(int w) {
    width = w;
}

int Enemy::getWidth() const {
    return width;
}

void Enemy::setHeight(int h) {
    height = h;
}

int Enemy::getHeight() const {
    return height;
}

double Enemy:: get_fill() const{
    return fill.red;
}

void Enemy::set_color(color c) {
    fill = c;
}

void Enemy::set_color(double r, double g, double b) {
    fill = { r, g, b };
}

bool Enemy::touch(Player player1) {
    if ((getEnemyxLocation() == player1.getPlayerxLocation()) && (getEnemyyLocation() == player1.getPlayeryLocation())) {
        return true;
    }
    return false;
}

void Enemy::move(int x_off, int y_off) {
    enemyxLocation += x_off;
    enemyyLocation += y_off;
    
}

EnemyChill::EnemyChill() : Enemy() {
    life = 1;
}

void EnemyChill::draw() const {
    int row = 4;
    int col = 5;
    vector< vector <bool> > enemy(row, vector <bool>(col, false));
    
    enemy[0][2] = true;
    enemy[1][1] = true;
    enemy[1][2] = true;
    enemy[1][3] = true;
    enemy[2][0] = true;
    enemy[2][1] = true;
    enemy[2][2] = true;
    enemy[2][3] = true;
    enemy[2][4] = true;
    enemy[3][0] = true;
    enemy[3][2] = true;
    enemy[3][4] = true;
    
    glBegin(GL_QUADS);
    glColor3f(fill.red, fill.green, fill.blue);
    //Draw Enemy
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (enemy[j][i]) {
                glVertex2i(EnemyChill::getEnemyxLocation() + i * EnemyChill::getWidth(), EnemyChill::getEnemyyLocation() + j * EnemyChill::getHeight());
                glVertex2i(EnemyChill::getEnemyxLocation() + (i + 1) * EnemyChill::getWidth(), EnemyChill::getEnemyyLocation() + j * EnemyChill::getHeight());
                glVertex2i(EnemyChill::getEnemyxLocation() + (i + 1) *  EnemyChill::getWidth(), EnemyChill::getEnemyyLocation() + (j + 1) * EnemyChill::getHeight());
                glVertex2i(EnemyChill::getEnemyxLocation() + i *  EnemyChill::getWidth(), EnemyChill::getEnemyyLocation() + (j + 1) * EnemyChill::getHeight());
                
            }
        }
    }
    glEnd();
}

bool EnemyChill::hitted(int x_in, int y_in) const {
    return (x_in >= EnemyChill::getEnemyxLocation() &&
            x_in <= EnemyChill::getEnemyxLocation() + EnemyChill::getWidth() * 5 &&
            y_in >= EnemyChill::getEnemyyLocation() &&
            y_in <= EnemyChill::getEnemyyLocation() + EnemyChill::getHeight() * 4);
}

bool EnemyChill::hitted(const Player &p) const {
    if (hitted(p.getPlayerxLocation(), p.getPlayeryLocation()) ||
        hitted(p.getPlayerxLocation() + p.getWidth() * 9, p.getPlayeryLocation()) ||
        hitted(p.getPlayerxLocation(), p.getPlayeryLocation() + p.getHeight() * 8) ||
        hitted(p.getPlayerxLocation() + p.getWidth() * 9, p.getPlayeryLocation() + p.getHeight() * 8)) {
        return true;
    }
    return false;
}

bool EnemyChill::hitted(const Bullet &b) const {
    if (hitted(b.getxLocation(), b.getyLocation()) ||
        hitted(b.getxLocation() + b.getWidth(), b.getyLocation()) ||
        hitted(b.getxLocation(), b.getyLocation() + b.getHeight() * 2) ||
        hitted(b.getxLocation() + b.getWidth(), b.getyLocation() + b.getHeight() * 2)) {
        return true;
    }
    return false;
}

EnemyBoss::EnemyBoss() : Enemy() {
    life = 10;
}

void EnemyBoss::draw() const{
    int row3 = 12;
    int col3 = 9;
    
    vector< vector <bool> > marshmello(row3, vector <bool>(col3, true));
    marshmello[2][1] = false;
    marshmello[2][3] = false;
    marshmello[2][5] = false;
    marshmello[2][7] = false;
    marshmello[3][2] = false;
    marshmello[3][6] = false;
    marshmello[4][1] = false;
    marshmello[4][3] = false;
    marshmello[4][5] = false;
    marshmello[4][7] = false;
    marshmello[8][1] = false;
    marshmello[8][7] = false;
    marshmello[9][2] = false;
    marshmello[9][6] = false;
    marshmello[10][3] = false;
    marshmello[10][4] = false;
    marshmello[10][5] = false;
    
    glBegin(GL_QUADS);
    glColor3f(fill.red, fill.green, fill.blue);
    for (int i = 0; i < col3; i++) {
        for (int j = 0; j < row3; j++) {
            if (marshmello[j][i]) {
                glVertex2i(EnemyBoss::getEnemyxLocation() + i * EnemyBoss::getWidth(), EnemyBoss::getEnemyyLocation() + j *EnemyBoss::getHeight());
                glVertex2i(EnemyBoss::getEnemyxLocation() + (i + 1) * EnemyBoss::getWidth(), EnemyBoss::getEnemyyLocation() + j * EnemyBoss::getHeight());
                glVertex2i(EnemyBoss::getEnemyxLocation() + (i + 1) * EnemyBoss::getWidth(), EnemyBoss::getEnemyyLocation() + (j + 1) * EnemyBoss::getHeight());
                glVertex2i(EnemyBoss::getEnemyxLocation() + i * EnemyBoss::getWidth(), EnemyBoss::getEnemyyLocation() + (j + 1) * EnemyBoss::getHeight());
            }
        }
    }
    glEnd();
}

bool EnemyBoss::hitted(int x_in, int y_in) const {
    return (x_in >= EnemyBoss::getEnemyxLocation() &&
            x_in <= EnemyBoss::getEnemyxLocation() + EnemyBoss::getWidth() * 9 &&
            y_in >= EnemyBoss::getEnemyyLocation() &&
            y_in <= EnemyBoss::getEnemyyLocation() + EnemyBoss::getHeight() * 12);
}

bool EnemyBoss::hitted(const Player &p) const {
    if (hitted(p.getPlayerxLocation(), p.getPlayeryLocation()) ||
        hitted(p.getPlayerxLocation() + p.getWidth() * 9, p.getPlayeryLocation()) ||
        hitted(p.getPlayerxLocation(), p.getPlayeryLocation() + p.getHeight() * 8) ||
        hitted(p.getPlayerxLocation() + p.getWidth() * 9, p.getPlayeryLocation() + p.getHeight() * 8)) {
        return true;
    }
    else {
        return false;
    }
}

bool EnemyBoss::hitted(const Bullet &b) const {
    if (hitted(b.getxLocation(), b.getyLocation()) ||
        hitted(b.getxLocation() + b.getWidth(), b.getyLocation()) ||
        hitted(b.getxLocation(), b.getyLocation() + b.getHeight() * 2) ||
        hitted(b.getxLocation() + b.getWidth(), b.getyLocation() + b.getHeight() * 2)) {
        return true;
    }
    else {
        return false;
    }
}

Shape::Shape(): area(0), perimeter(0) {
    fill.red = fill.green = fill.blue = 0;
}

Shape::Shape(double a, double p, color f): area(a), perimeter(p), fill(f) {
}

Shape::Shape(color f) : area(0), perimeter(0), fill(f) {
}

double Shape::get_area() const {
    return area;
}

double Shape::get_perimeter() const {
    return perimeter;
}

color Shape::get_fill() const {
    return fill;
}

void Shape::set_color(color c) {
    fill = c;
}

void Shape::set_color(double r, double g, double b) {
    fill = {r, g, b};
}

Point2D::Point2D() : x(0), y(0) {
}

Point2D::Point2D(int x_in, int y_in) : x(x_in), y(y_in) {
}

int Point2D::get_x() const {
    return x;
}

int Point2D::get_y() const {
    return y;
}

void Point2D::set_x(int x_in) {
    x = x_in;
}

void Point2D::set_y(int y_in) {
    y = y_in;
}

void Point2D::set_point(int x_in, int y_in) {
    x = x_in;
    y = y_in;
}

void Point2D::move_point(int x_offset, int y_offset) {
    x += x_offset;
    y += y_offset;
}

double Point2D::distance_between(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

Rectangle::Rectangle(): Shape(), length(0), width(0) {
}

Rectangle::Rectangle(double l, double w): Shape() {
    set_width(w);
    set_length(l);
}

Rectangle::Rectangle(double l, double w, color c): Shape(c) {
    set_width(w);
    set_length(l);
}

Rectangle::Rectangle(color c): Rectangle(0, 0, c) {
}

double Rectangle::get_length() const {
    return length;
}

double Rectangle::get_width() const {
    return width;
}

void Rectangle::set_length(double l) {
    length = l;
    if (l < 0) {
        length = 0;
    }
    calc_area_peri();
}

void Rectangle::set_width(double w) {
    width = w;
    if (w < 0) {
        width = 0;
    }
    calc_area_peri();
}

// This method is to be completed.
void Rectangle::draw() const {
    cout << "Drawing a rectangle" << endl;
}

void Rectangle::calc_area_peri() {
    area = length * width;
    perimeter = 2 * length + 2 * width;
}

Rectangle_Coord::Rectangle_Coord() {
    top_left = Point2D();
}

Point2D Rectangle_Coord::get_top_left() const {
    return top_left;
}

int Rectangle_Coord::get_top_left_x() const {
    return top_left.get_x();
}

int Rectangle_Coord::get_top_left_y() const {
    return top_left.get_y();
}

Point2D Rectangle_Coord::get_top_right() const {
    return Point2D(get_top_left_x()+width, get_top_left_y());
}

int Rectangle_Coord::get_top_right_x() const {
    return get_top_left_x()+width;
}

int Rectangle_Coord::get_top_right_y() const {
    return get_top_left_y();
}

Point2D Rectangle_Coord::get_bottom_left() const {
    return Point2D(get_top_left_x(), get_top_left_y()+length);
}

int Rectangle_Coord::get_bottom_left_x() const {
    return get_top_left_x();
}

int Rectangle_Coord::get_bottom_left_y() const {
    return get_top_left_y()+length;
}

Point2D Rectangle_Coord::get_bottom_right() const {
    return Point2D(get_top_left_x()+width, get_top_left_y()+length);
}
int Rectangle_Coord::get_bottom_right_x() const {
    return get_top_left_x()+width;
}

int Rectangle_Coord::get_bottom_right_y() const {
    return get_top_left_y()+length;
}

void Rectangle_Coord::set_top_left(int x_in, int y_in) {
    top_left = Point2D(x_in, y_in);
}

void Rectangle_Coord::move(int x_offset, int y_offset) {
    top_left.move_point(x_offset, y_offset);
}

void Rectangle_Coord::draw() const {
    glBegin(GL_QUADS);
    glColor3f(fill.red, fill.green, fill.blue);
    glVertex2i(top_left.get_x(), top_left.get_y());
    glVertex2i(top_left.get_x() + width, top_left.get_y());
    glVertex2i(top_left.get_x() + width, top_left.get_y() + length);
    glVertex2i(top_left.get_x(), top_left.get_y() + length);
    glEnd();
}

bool Rectangle_Coord::is_overlapping(int x_in, int y_in) const {
    return (x_in >= get_top_left_x() &&
            x_in <= get_top_left_x() + width &&
            y_in >= get_top_left_y() &&
            y_in <= get_top_left_y() + length);
}

bool Rectangle_Coord::is_overlapping(const Rectangle_Coord &r) const {
    return (is_overlapping(r.get_top_left_x(),
                           r.get_top_left_y()) ||
            is_overlapping(r.get_top_right_x(),
                           r.get_top_right_y()) ||
            is_overlapping(r.get_bottom_left_x(),
                           r.get_bottom_left_y()) ||
            is_overlapping(r.get_bottom_right_x(),
                           r.get_bottom_right_y())
            );
}
