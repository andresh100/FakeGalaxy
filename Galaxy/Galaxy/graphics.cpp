/*
 * graphics.cpp
 * Fake Galaga!
 */


#include "graphics.hpp"
#include "wormhole.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

// Different screens
enum screen_state { menu, leaderboard, fake_leaderboard, instructions, game_play, pause, game_over, high_first, high_second, high_third, thanks, thanks_high_first, thanks_high_second, thanks_high_third};

// Declaring variables

GLdouble width, height;

bool pmove = false;
bool moveDown = false;
bool moveUp = false;
bool moveLeft = false;
bool moveRight = false;
bool thridwave = false;

int wd;
int mouse_x, mouse_y;
int bossScore = 60;

screen_state screen;
Player p;
EnemyBoss boss;

vector<EnemyChill> enemy1;
vector<NormalBullet> normal;
vector<NormalBullet> normal2;

bool check_bull = false;
bool boss_check = false;

Rectangle_Coord r;
Rectangle_Coord r2;
Rectangle_Coord r3;
Rectangle_Coord r4;
Rectangle_Coord r5;
Rectangle_Coord r6;
Rectangle_Coord r7;
Rectangle_Coord r8;
vector<Rectangle_Coord> stars;

string nextLine;
int highscore1;
int highscore2;
int highscore3;



/* START HELPER DISPLAY FUNCTIONS */

// Menu screen
void display_menu() {
    
    // draw stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].draw();
    }
    
    // make stars move
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].set_top_left(stars[i].get_top_left_x(), stars[i].get_top_left_y()+1);
        if(stars[i].get_top_left_y() > 600 || stars[i].get_top_left_x() > 500){
            stars[i].set_top_left(rand() % 500 + 1, rand() % 10 + 1);
        }
    }
    
    // draw a string message
    string title = "FAKE GALAGA";
    glColor3f(.22, .93, .91);
    glRasterPos2i(170, 150);
    for (int i = 0; i < title.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, title[i]);
    }
    
    r.draw();
    // initialize rectangle fields
    r.set_width(130);
    r.set_length(30);
    r.set_top_left(190,226);
    
    // draw a string message
    string newgame = "New Game";
    glColor3f(1, 1, 0);
    glRasterPos2i(200, 250);
    for (int i = 0; i < newgame.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, newgame[i]);
    }
    
    r2.draw();
    // initialize rectangle fields
    r2.set_width(132);
    r2.set_length(30);
    r2.set_top_left(190,281);
    
    // draw a string message
    string leaderboard = "Leaderboard";
    glColor3f(1, 1, 0);
    glRasterPos2i(195, 305);
    for (int i = 0; i < leaderboard.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, leaderboard[i]);
    }
    
    r7.draw();
    // initialize rectangle fields
    r7.set_width(55);
    r7.set_length(30);
    r7.set_top_left(230,340);
    
    string quit = "Quit";
    glColor3f(1, 1, 0);
    glRasterPos2i(235, 360);
    for (int i = 0; i < quit.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, quit[i]);
    }
    
}

// Leaderboard screen
void display_leaderboard() {
    
    // draw stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].draw();
    }
    
    // move stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].set_top_left(stars[i].get_top_left_x(), stars[i].get_top_left_y()+1);
        if(stars[i].get_top_left_y() > 600 || stars[i].get_top_left_x() > 500){
            stars[i].set_top_left(rand() % 500 + 1, rand() % 10 + 1);
        }
    }
    
    // draw a string message
    string high_scores = "HIGH SCORES";
    glColor3f(.22, .93, .91);
    glRasterPos2i(180, 140);
    for (int i = 0; i < high_scores.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, high_scores[i]);
    }
    
    string first = "#1: " + to_string(highscore1);
    glColor3f(.22, .93, .91);
    glRasterPos2i(227, 200);
    for (int i = 0; i < first.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, first[i]);
    }
    
    string second = "#2: " + to_string(highscore2);
    glColor3f(.22, .93, .91);
    glRasterPos2i(227, 230);
    for (int i = 0; i < second.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, second[i]);
    }
    
    string third = "#3: " + to_string(highscore3);
    glColor3f(.22, .93, .91);
    glRasterPos2i(227, 260);
    for (int i = 0; i < third.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, third[i]);
    }
    
    r3.draw();
    // initialize rectangle fields
    r3.set_width(221);
    r3.set_length(30);
    r3.set_top_left(147,378);
    
    string mainmenu = "Return to Main Menu";
    glColor3f(1, 1, 0);
    glRasterPos2i(150, 400);
    for (int i = 0; i < mainmenu.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, mainmenu[i]);
    }
    
}

// Fake leaderboard screen
void display_fake_leaderboard() {
    
    // draw stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].draw();
    }
    
    // move stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].set_top_left(stars[i].get_top_left_x(), stars[i].get_top_left_y()+1);
        if(stars[i].get_top_left_y() > 600 || stars[i].get_top_left_x() > 500){
            stars[i].set_top_left(rand() % 500 + 1, rand() % 10 + 1);
        }
    }
    
    // draw a string message
    string high_scores = "HIGH SCORES";
    glColor3f(.22, .93, .91);
    glRasterPos2i(180, 140);
    for (int i = 0; i < high_scores.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, high_scores[i]);
    }
    
    string first = "#1: " + to_string(highscore1);
    glColor3f(.22, .93, .91);
    glRasterPos2i(227, 200);
    for (int i = 0; i < first.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, first[i]);
    }
    
    string second = "#2: " + to_string(highscore2);
    glColor3f(.22, .93, .91);
    glRasterPos2i(227, 230);
    for (int i = 0; i < second.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, second[i]);
    }
    
    string third = "#3: " + to_string(highscore3);
    glColor3f(.22, .93, .91);
    glRasterPos2i(227, 260);
    for (int i = 0; i < third.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, third[i]);
    }
    
    r6.draw();
    // initialize rectangle fields
    r6.set_width(55);
    r6.set_length(30);
    r6.set_top_left(225,298);
    
    string quit = "Quit";
    glColor3f(1, 1, 0);
    glRasterPos2i(230, 320);
    for (int i = 0; i < quit.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, quit[i]);
    }
    
}

// Instructions screen
void display_instructions() {
    
    // draw stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].draw();
    }
    
    // move stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].set_top_left(stars[i].get_top_left_x(), stars[i].get_top_left_y()+1);
        if(stars[i].get_top_left_y() > 600 || stars[i].get_top_left_x() > 500){
            stars[i].set_top_left(rand() % 500 + 1, rand() % 10 + 1);
        }
    }
    
    string title = "INSTRUCTIONS:";
    glColor3f(.22, .93, .91);
    glRasterPos2i(160, 150);
    for (int i = 0; i < title.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, title[i]);
    }
    
    string message = "Move with the arrow keys!";
    glColor3f(1, 1, 0);
    glRasterPos2i(144, 250);
    for (int i = 0; i < message.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]);
    }
    
    string message3 = "Pause with the spacebar!";
    glColor3f(1, 1, 0);
    glRasterPos2i(150, 280);
    for (int i = 0; i < message3.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message3[i]);
    }
    
    string message2 = "Click anywhere to begin";
    glColor3f(.22, .93, .91);
    glRasterPos2i(157, 350);
    for (int i = 0; i < message2.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message2[i]);
    }
    
}

// Game screen
void display_game() {
    
    // draw stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].draw();
    }
    
    // move stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].set_top_left(stars[i].get_top_left_x(), stars[i].get_top_left_y()+1);
        if(stars[i].get_top_left_y() > 600 || stars[i].get_top_left_x() > 500){
            stars[i].set_top_left(rand() % 500 + 1, rand() % 10 + 1);
        }
    }
    
    string score = "Score: " + to_string(p.getScore());
    glColor3f(1, 1, 0);
    glRasterPos2i(360, 20);
    for (int i = 0; i < score.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);
    }
    
    string life = "Player Life: " + to_string(p.getLife());
    glColor3f(1, 1, 0);
    glRasterPos2i(359, 40);
    for (int i = 0; i < life.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, life[i]);
    }
    
    // draw boss's life once it appears
    if (p.getScore() >= bossScore && boss.getLife() != 0){
        string bossLife = "Boss Life: " + to_string(boss.getLife());
        glColor3f(1, 0, 0);
        glRasterPos2i(360, 60);
        for (int i = 0; i < bossLife.length(); ++i) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, bossLife[i]);
        }
    }
    
    // draw the vector of enemies
    for (int i = 0; i < enemy1.size(); i++) {
        enemy1[i].draw();
    }
    // draw the player
    p.draw();
    
    // once the player reaches a certain score, draw the boss
    if (p.getScore() >= bossScore) {
        boss.draw();
    }
    
    // once the boss appears, draw the boss's bullets
    if (p.getScore() >= bossScore && boss.getLife() > 0) {
        for (int i = 0; i < normal2.size(); i++) {
            normal2[i].draw();
        }
    }
    
    // draw the player's bullets
    for (int i = 0; i < normal.size(); i++) {
        normal[i].draw();
    }
    
    // once the enemies go off the screen, erase them
    for (int i = 0; i < enemy1.size(); i++) {
        if (enemy1[i].getEnemyyLocation() > 600) {
            enemy1.erase(enemy1.begin() + i);
            i--;
            break;
        }
        // if the enemy hits the player, erase it and decrease player's life
        else if (enemy1[i].hitted(p)) {
            enemy1.erase(enemy1.begin() + i);
            p.setLife(p.getLife() - 2);
            i--;
            break;
        }
        // if a bullet hits the enemy, erase both and increase player's score
        for (int j = 0; j < normal.size(); j++) {
            if (enemy1[i].hitted(normal[j])) {
                enemy1.erase(enemy1.begin() + i);
                normal.erase(normal.begin() + j);
                p.setScore(p.getScore() + 2);
                i--;
                j--;
                break;
            }
        }
    }
    
    // if a bullet hits the boss, erase the bullet and decrease boss's life
    if (p.getScore() >= bossScore) {
        for (int i = 0; i < normal.size(); i++) {
            if (boss.hitted(normal[i])) {
                normal.erase(normal.begin() + i);
                boss.setLife(boss.getLife() - 2);
                i--;
                break;
            }
            // once the bullet goes off the screen, erase it
            else if (normal[i].getyLocation() < 0) {
                normal.erase(normal.begin() + i);
                i--;
                break;
            }
        }
    }
    
    // if the bullet goes off the screen, erase it
    for (int i = 0; i < normal.size(); i++) {
        if (normal[i].getyLocation() < 9){
            normal.erase(normal.begin() + i);
            i--;
            break;
        }
    }
    
    // create the first wave of enemies
    if (p.getScore() == 10 && enemy1.size() > 0 && enemy1[0].get_fill() == .33){
        enemy1.resize(0);
        for (int i = 0; i < 200; i++) {
            EnemyChill e;
            e.setEnemyxLocation(rand() % 400 + 1);
            e.setWidth(9);
            e.setHeight(3);
            e.set_color(.99, 0, 0);
            int m = -200;
            for (int n = 0; n < enemy1.size(); n++) {
                e.setEnemyyLocation(m);
                m -= 200;
            }
            enemy1.push_back(e);
        }
        
        // create the second wave of enemies
    } else if (p.getScore() == 20 && enemy1.size() > 0 && enemy1[0].get_fill() == .99){
        enemy1.resize(0);
        for (int i = 0; i < 200; i++) {
            EnemyChill e;
            e.setEnemyxLocation(rand() % 400 + 1);
            e.setWidth(9);
            e.setHeight(3);
            e.set_color(.98, .98, 0);
            int m = -100;
            for (int n = 0; n < enemy1.size(); n++) {
                e.setEnemyyLocation(m);
                m -= 100;
            }
            enemy1.push_back(e);
        }
        
        // create the third wave of enemies
    } else if (p.getScore() == 30 && enemy1.size() > 0 && enemy1[0].get_fill() == .98){
        enemy1.resize(0);
        for (int i = 0; i < 200; i++) {
            EnemyChill e;
            e.setEnemyxLocation(rand() % 400 + 1);
            e.setWidth(9);
            e.setHeight(3);
            e.set_color(.97, .97, .97);
            int m = -50;
            for (int n = 0; n < enemy1.size(); n++) {
                e.setEnemyyLocation(m);
                m -=50;
            }
            enemy1.push_back(e);
        }
    }
    
    // if the boss dies, erase all of its stats, end the game, and display the appropriate screen
    if (boss.getLife() == 0) {
        boss.setWidth(0);
        boss.setHeight(0);
        for (int i = 0; i < normal2.size(); i++) {
            normal2.erase(normal2.begin() + i);
        }
        if (p.getScore() > highscore1) {
            screen = thanks_high_first;
        }
        else if (p.getScore() > highscore2 && p.getScore() < highscore1) {
            screen = thanks_high_second;
        }
        else if (p.getScore() > highscore3 && p.getScore() < highscore2) {
            screen = thanks_high_third;
        }
        else {
            screen = thanks;
        }
    }
    
    // if the player dies, erase it, end the game, and display the appropriate screen
    if (p.getLife() == 0) {
        p.setWidth(0);
        p.setHeight(0);
        if (p.getScore() > highscore1) {
            screen = high_first;
        }
        else if (p.getScore() > highscore2 && p.getScore() < highscore1) {
            screen = high_second;
        }
        else if (p.getScore() > highscore3 && p.getScore() < highscore2) {
            screen = high_third;
        }
        else {
            screen = game_over;
        }
    }
    
    // if the player is hit by a boss's bullet, erase the bullet and decrease player's life
    for (int i = 0; i < normal2.size(); i++) {
        if (p.hitted(normal2[i])) {
            normal2.erase(normal2.begin() + i);
            p.setLife(p.getLife() - 2);
        }
    }
    
    // move stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].set_top_left(stars[i].get_top_left_x(), stars[i].get_top_left_y()+1);
        if(stars[i].get_top_left_y() > 600 || stars[i].get_top_left_x() > 500){
            stars[i].set_top_left(rand() % 500 + 1, rand() % 10 + 1);
        }
    }
}

// Game over screen
void display_game_over() {
    
    // draw stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].draw();
    }
    
    // move stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].set_top_left(stars[i].get_top_left_x(), stars[i].get_top_left_y()+1);
        if(stars[i].get_top_left_y() > 600 || stars[i].get_top_left_x() > 500){
            stars[i].set_top_left(rand() % 500 + 1, rand() % 10 + 1);
        }
    }
    
    // draw a string message
    string message = "You win!..JK. GAME OVER!";
    glColor3f(.22, .93, .91);
    glRasterPos2i(100, 250);
    for (int i = 0; i < message.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }
    
    string score = "Score:" + to_string(p.getScore());
    glColor3f(1, 1, 0);
    glRasterPos2i(360, 20);
    for (int i = 0; i < score.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);
    }
    
    r4.draw();
    // initialize rectangle fields
    r4.set_width(130);
    r4.set_length(30);
    r4.set_top_left(185,378);
    
    string leaderboard = "Leaderboard";
    glColor3f(1, 1, 0);
    glRasterPos2i(190, 400);
    for (int i = 0; i < leaderboard.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, leaderboard[i]);
    }
    
    r5.draw();
    // initialize rectangle fields
    r5.set_width(55);
    r5.set_length(30);
    r5.set_top_left(225,433);
    
    string quit = "Quit";
    glColor3f(1, 1, 0);
    glRasterPos2i(230, 455);
    for (int i = 0; i < quit.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, quit[i]);
    }
    
}

// Game over screen for if you beat the #1 high score
void display_high_first() {
    
    // draw stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].draw();
    }
    
    // move stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].set_top_left(stars[i].get_top_left_x(), stars[i].get_top_left_y()+1);
        if(stars[i].get_top_left_y() > 600 || stars[i].get_top_left_x() > 500){
            stars[i].set_top_left(rand() % 500 + 1, rand() % 10 + 1);
        }
    }
    
    // draw a string message
    string message = "You win!..JK. GAME OVER!";
    glColor3f(.22, .93, .91);
    glRasterPos2i(100, 250);
    for (int i = 0; i < message.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }
    
    string score = "Score:" + to_string(p.getScore());
    glColor3f(1, 1, 0);
    glRasterPos2i(360, 20);
    for (int i = 0; i < score.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);
    }
    
    string newFirst = "You beat the #1 high score!";
    glColor3f(1, 1, 0);
    glRasterPos2i(112, 100);
    for (int i = 0; i < newFirst.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, newFirst[i]);
    }
    highscore1 = p.getScore();
    
    r4.draw();
    // initialize rectangle fields
    r4.set_width(130);
    r4.set_length(30);
    r4.set_top_left(185,378);
    
    string leaderboard = "Leaderboard";
    glColor3f(1, 1, 0);
    glRasterPos2i(190, 400);
    for (int i = 0; i < leaderboard.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, leaderboard[i]);
    }
    
    r5.draw();
    // initialize rectangle fields
    r5.set_width(55);
    r5.set_length(30);
    r5.set_top_left(225,433);
    
    string quit = "Quit";
    glColor3f(1, 1, 0);
    glRasterPos2i(230, 455);
    for (int i = 0; i < quit.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, quit[i]);
    }
    
    // Writes high scores to output file
    ofstream out_file;
    out_file.open("high_scores.txt");
    
    if (out_file){
        out_file << highscore1 << "\n";
        out_file << highscore2 << "\n";
        out_file << highscore3 << "\n";
    }
    
    out_file.close();
    
}

// Game over screen for if you beat the #2 high score
void display_high_second() {
    
    // draw stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].draw();
    }
    
    // move stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].set_top_left(stars[i].get_top_left_x(), stars[i].get_top_left_y()+1);
        if(stars[i].get_top_left_y() > 600 || stars[i].get_top_left_x() > 500){
            stars[i].set_top_left(rand() % 500 + 1, rand() % 10 + 1);
        }
    }
    
    // draw a string message
    string message = "You win!..JK. GAME OVER!";
    glColor3f(.22, .93, .91);
    glRasterPos2i(100, 250);
    for (int i = 0; i < message.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }
    
    string score = "Score:" + to_string(p.getScore());
    glColor3f(1, 1, 0);
    glRasterPos2i(360, 20);
    for (int i = 0; i < score.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);
    }
    
    string newSecond = "You beat the #2 high score!";
    glColor3f(1, 1, 0);
    glRasterPos2i(112, 100);
    for (int i = 0; i < newSecond.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, newSecond[i]);
    }
    highscore2 = p.getScore();
    
    r4.draw();
    // initialize rectangle fields
    r4.set_width(130);
    r4.set_length(30);
    r4.set_top_left(185,378);
    
    string leaderboard = "Leaderboard";
    glColor3f(1, 1, 0);
    glRasterPos2i(190, 400);
    
    for (int i = 0; i < leaderboard.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, leaderboard[i]);
    }
    
    r5.draw();
    // initialize rectangle fields
    r5.set_width(55);
    r5.set_length(30);
    r5.set_top_left(225,433);
    
    string quit = "Quit";
    glColor3f(1, 1, 0);
    glRasterPos2i(230, 455);
    for (int i = 0; i < quit.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, quit[i]);
    }
    
    // Writes high scores to output file
    ofstream out_file;
    out_file.open("high_scores.txt");
    
    if (out_file){
        out_file << highscore1 << "\n";
        out_file << highscore2 << "\n";
        out_file << highscore3 << "\n";
    }
    
    out_file.close();
    
}

// Game over screen for if you beat the #3 high score
void display_high_third() {
    
    // draw stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].draw();
    }
    
    // move stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].set_top_left(stars[i].get_top_left_x(), stars[i].get_top_left_y()+1);
        if(stars[i].get_top_left_y() > 600 || stars[i].get_top_left_x() > 500){
            stars[i].set_top_left(rand() % 500 + 1, rand() % 10 + 1);
        }
    }
    
    // draw a string message
    string message = "You win!..JK. GAME OVER!";
    glColor3f(.22, .93, .91);
    glRasterPos2i(100, 250);
    for (int i = 0; i < message.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }
    
    string score = "Score:" + to_string(p.getScore());
    glColor3f(1, 1, 0);
    glRasterPos2i(360, 20);
    for (int i = 0; i < score.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);
    }
    
    string newThird = "You beat the #3 high score!";
    glColor3f(1, 1, 0);
    glRasterPos2i(112, 100);
    for (int i = 0; i < newThird.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, newThird[i]);
    }
    highscore3 = p.getScore();
    
    r4.draw();
    // initialize rectangle fields
    r4.set_width(130);
    r4.set_length(30);
    r4.set_top_left(185,378);
    
    string leaderboard = "Leaderboard";
    glColor3f(1, 1, 0);
    glRasterPos2i(190, 400);
    for (int i = 0; i < leaderboard.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, leaderboard[i]);
    }
    
    r5.draw();
    // initialize rectangle fields
    r5.set_width(55);
    r5.set_length(30);
    r5.set_top_left(225,433);
    
    string quit = "Quit";
    glColor3f(1, 1, 0);
    glRasterPos2i(230, 455);
    for (int i = 0; i < quit.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, quit[i]);
    }
    
    // Writes high scores to output file
    ofstream out_file;
    out_file.open("high_scores.txt");
    
    if (out_file){
        out_file << highscore1 << "\n";
        out_file << highscore2 << "\n";
        out_file << highscore3 << "\n";
    }
    
    out_file.close();
    
}

// Pause screen
void display_pause() {
    
    // draw stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].draw();
    }
    
    // move stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].set_top_left(stars[i].get_top_left_x(), stars[i].get_top_left_y()+1);
        if(stars[i].get_top_left_y() > 600 || stars[i].get_top_left_x() > 500){
            stars[i].set_top_left(rand() % 500 + 1, rand() % 10 + 1);
        }
    }
    
    // draw a string message
    string message4 = "Game Paused";
    glColor3f(.22, .93, .91);
    glRasterPos2i(200, 250);
    for (int i = 0; i < message4.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message4[i]);
    }
    
    string message5 = "(Press the spacebar to continue)";
    glColor3f(.22, .93, .91);
    glRasterPos2i(110, 290);
    for (int i = 0; i < message5.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message5[i]);
    }
    
    r8.draw();
    // initialize rectangle fields
    r8.set_width(55);
    r8.set_length(30);
    r8.set_top_left(240,340);
    
    string quit = "Quit";
    glColor3f(1, 1, 0);
    glRasterPos2i(245, 360);
    for (int i = 0; i < quit.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, quit[i]);
    }
    
}

// Game over screen for if you win
void display_thanks() {
    
    // draw stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].draw();
    }
    
    // move stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].set_top_left(stars[i].get_top_left_x(), stars[i].get_top_left_y()+1);
        if(stars[i].get_top_left_y() > 600 || stars[i].get_top_left_x() > 500){
            stars[i].set_top_left(rand() % 500 + 1, rand() % 10 + 1);
        }
    }
    
    string message = "Thanks For Playing!!!";
    glColor3f(.22, .93, .91);
    glRasterPos2i(150, 250);
    for (int i = 0; i < message.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }
    
    string score = "Score: " + to_string(p.getScore());
    glColor3f(1, 1, 0);
    glRasterPos2i(360, 20);
    for (int i = 0; i < score.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);
    }
    
    r4.draw();
    // initialize rectangle fields
    r4.set_width(130);
    r4.set_length(30);
    r4.set_top_left(185,378);
    
    string leaderboard = "Leaderboard";
    glColor3f(1, 1, 0);
    glRasterPos2i(190, 400);
    for (int i = 0; i < leaderboard.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, leaderboard[i]);
    }
    
    r5.draw();
    // initialize rectangle fields
    r5.set_width(55);
    r5.set_length(30);
    r5.set_top_left(225,433);
    
    string quit = "Quit";
    glColor3f(1, 1, 0);
    glRasterPos2i(230, 455);
    for (int i = 0; i < quit.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, quit[i]);
    }
    
}

// Game over screen for if you win and beat the #1 high score
void display_thanks_high_first() {
    
    // draw stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].draw();
    }
    
    // move stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].set_top_left(stars[i].get_top_left_x(), stars[i].get_top_left_y()+1);
        if(stars[i].get_top_left_y() > 600 || stars[i].get_top_left_x() > 500){
            stars[i].set_top_left(rand() % 500 + 1, rand() % 10 + 1);
        }
    }
    
    string message = "Thanks For Playing!!!";
    glColor3f(.22, .93, .91);
    glRasterPos2i(150, 250);
    for (int i = 0; i < message.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }
    
    string score = "Score: " + to_string(p.getScore());
    glColor3f(1, 1, 0);
    glRasterPos2i(360, 20);
    for (int i = 0; i < score.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);
    }
    
    string newFirst = "You beat the #1 high score!";
    glColor3f(1, 1, 0);
    glRasterPos2i(112, 100);
    for (int i = 0; i < newFirst.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, newFirst[i]);
    }
    highscore1 = p.getScore();
    
    r4.draw();
    // initialize rectangle fields
    r4.set_width(130);
    r4.set_length(30);
    r4.set_top_left(185,378);
    
    string leaderboard = "Leaderboard";
    glColor3f(1, 1, 0);
    glRasterPos2i(190, 400);
    for (int i = 0; i < leaderboard.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, leaderboard[i]);
    }
    
    r5.draw();
    // initialize rectangle fields
    r5.set_width(55);
    r5.set_length(30);
    r5.set_top_left(225,433);
    
    string quit = "Quit";
    glColor3f(1, 1, 0);
    glRasterPos2i(230, 455);
    for (int i = 0; i < quit.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, quit[i]);
    }
    
    // Writes high scores to output file
    ofstream out_file;
    out_file.open("high_scores.txt");
    
    if (out_file){
        out_file << highscore1 << "\n";
        out_file << highscore2 << "\n";
        out_file << highscore3 << "\n";
    }
    
    out_file.close();
    
}

// Game over screen for if you win and beat the #2 high score
void display_thanks_high_second() {
    
    // draw stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].draw();
    }
    
    // move stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].set_top_left(stars[i].get_top_left_x(), stars[i].get_top_left_y()+1);
        if(stars[i].get_top_left_y() > 600 || stars[i].get_top_left_x() > 500){
            stars[i].set_top_left(rand() % 500 + 1, rand() % 10 + 1);
        }
    }
    
    string message = "Thanks For Playing!!!";
    glColor3f(.22, .93, .91);
    glRasterPos2i(150, 250);
    for (int i = 0; i < message.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }
    
    string score = "Score: " + to_string(p.getScore());
    glColor3f(1, 1, 0);
    glRasterPos2i(360, 20);
    for (int i = 0; i < score.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);
    }
    
    string newSecond = "You beat the #2 high score!";
    glColor3f(1, 1, 0);
    glRasterPos2i(112, 100);
    for (int i = 0; i < newSecond.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, newSecond[i]);
    }
    highscore2 = p.getScore();
    
    r4.draw();
    // initialize rectangle fields
    r4.set_width(130);
    r4.set_length(30);
    r4.set_top_left(185,378);
    
    string leaderboard = "Leaderboard";
    glColor3f(1, 1, 0);
    glRasterPos2i(190, 400);
    for (int i = 0; i < leaderboard.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, leaderboard[i]);
    }
    
    r5.draw();
    // initialize rectangle fields
    r5.set_width(55);
    r5.set_length(30);
    r5.set_top_left(225,433);
    
    string quit = "Quit";
    glColor3f(1, 1, 0);
    glRasterPos2i(230, 455);
    for (int i = 0; i < quit.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, quit[i]);
    }
    
    // Writes high scores to output file
    ofstream out_file;
    out_file.open("high_scores.txt");
    
    if (out_file){
        out_file << highscore1 << "\n";
        out_file << highscore2 << "\n";
        out_file << highscore3 << "\n";
    }
    
    out_file.close();
    
}

// Game over screen for if you win and beat the #3 high score
void display_thanks_high_third() {
    
    // draw stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].draw();
    }
    
    // move stars
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].set_top_left(stars[i].get_top_left_x(), stars[i].get_top_left_y()+1);
        if(stars[i].get_top_left_y() > 600 || stars[i].get_top_left_x() > 500){
            stars[i].set_top_left(rand() % 500 + 1, rand() % 10 + 1);
        }
    }
    
    string message = "Thanks For Playing!!!";
    glColor3f(.22, .93, .91);
    glRasterPos2i(150, 250);
    for (int i = 0; i < message.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }
    
    string score = "Score: " + to_string(p.getScore());
    glColor3f(1, 1, 0);
    glRasterPos2i(360, 20);
    for (int i = 0; i < score.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);
    }
    
    string newThird = "You beat the #3 high score!";
    glColor3f(1, 1, 0);
    glRasterPos2i(112, 100);
    for (int i = 0; i < newThird.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, newThird[i]);
    }
    highscore3 = p.getScore();
    
    r4.draw();
    // initialize rectangle fields
    r4.set_width(130);
    r4.set_length(30);
    r4.set_top_left(185,378);
    
    string leaderboard = "Leaderboard";
    glColor3f(1, 1, 0);
    glRasterPos2i(190, 400);
    for (int i = 0; i < leaderboard.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, leaderboard[i]);
    }
    
    r5.draw();
    // initialize rectangle fields
    r5.set_width(55);
    r5.set_length(30);
    r5.set_top_left(225,433);
    
    string quit = "Quit";
    glColor3f(1, 1, 0);
    glRasterPos2i(230, 455);
    for (int i = 0; i < quit.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, quit[i]);
    }
    
    // Writes high scores to output file
    ofstream out_file;
    out_file.open("high_scores.txt");
    
    if (out_file){
        out_file << highscore1 << "\n";
        out_file << highscore2 << "\n";
        out_file << highscore3 << "\n";
    }
    
    out_file.close();
    
}

/* END HELPER DISPLAY FUNCTIONS */
void init() {
    
    srand (time(NULL));
    
    // push back 175 rectangle_coords into the vector
    for (int i = 0; i < 175; i++) {
        stars.push_back(Rectangle_Coord());
    }
    
    // initialize all of the rectangle_coords
    for (int i = 0; i < stars.size(); i++ ) {
        stars[i].set_width(1);
        stars[i].set_length(1);
        stars[i].set_color(1.0f, 1.0f, 1.0f);
        stars[i].set_top_left(rand() % 500 + 1, rand() % 600 + 1);
    }
    
    ifstream in_file;
    in_file.open("high_scores.txt");
    
    // Reads in high scores from text file
    if (in_file){
        getline(in_file, nextLine);
        highscore1 = atoi(nextLine.c_str());
        //highscore1 = nextLine;
        
        getline(in_file, nextLine);
        highscore2 = atoi(nextLine.c_str());
        //highscore2 = nextLine;
        
        getline(in_file, nextLine);
        highscore3 = atoi(nextLine.c_str());
        //highscore3 = nextLine;
    }
    
    // Close input file
    in_file.close();
    
    // initialize variables
    
    mouse_x = mouse_y = 0;
    
    width = 500;
    height = 600;
    
    screen = menu;
    
    p.setPlayerxLocation(230);
    p.setPlayeryLocation(500);
    p.setWidth(5);
    p.setHeight(2);
    p.set_color(0, 1, 1);
    
    boss.setEnemyxLocation(200);
    boss.setEnemyyLocation(100);
    boss.setWidth(10);
    boss.setHeight(5);
    boss.setLife(60);
    boss.set_color(1, 1, 1);
    
    // initialize enemy fields before boss appears
    if(p.getScore() < bossScore){
        for (int i = 0; i < 200; i++) {
            EnemyChill e;
            e.setEnemyxLocation(rand() % 400 + 1);
            e.setWidth(9);
            e.setHeight(3);
            e.set_color(.33, .086, .67);
            int m = -300;
            for (int n = 0; n < enemy1.size(); n++) {
                e.setEnemyyLocation(m);
                m -= 300;
            }
            enemy1.push_back(e);
        }
    }
}

/* Initialize OpenGL Graphics */
void initGL() {
    
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
    
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);
    
    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // display the appropriate screen
    switch (screen) {
        case menu:
            display_menu();
            break;
        case leaderboard:
            display_leaderboard();
            break;
        case fake_leaderboard:
            display_fake_leaderboard();
            break;
        case instructions:
            display_instructions();
            break;
        case game_play:
            display_game();
            break;
        case pause:
            display_pause();
            break;
        case game_over:
            display_game_over();
            break;
        case high_first:
            display_high_first();
            break;
        case high_second:
            display_high_second();
            break;
        case high_third:
            display_high_third();
            break;
        case thanks:
            display_thanks();
            break;
        case thanks_high_first:
            display_thanks_high_first();
            break;
        case thanks_high_second:
            display_thanks_high_second();
            break;
        case thanks_high_third:
            display_thanks_high_third();
            break;
    }
    
    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    
    // pause
    if (key == 32) {
        if (screen == game_play) {
            screen = pause;
        }
        else if (screen == pause) {
            screen = game_play;
        }
    }
    
    glutPostRedisplay();
    
    return;
}

void kbdS(int key, int x, int y) {
    
    // arrow key controls
    if (screen == game_play) {
        if (key == GLUT_KEY_DOWN) {
            moveLeft = false;
            moveRight = false;
            moveUp = false;
            if (p.getPlayeryLocation() + p.getHeight() * 8 < height) {
                moveDown = true;
                p.move("down");
            } else {
                p.move("");
                moveDown = false;
            }
        }
        else if (key == GLUT_KEY_LEFT) {
            moveDown = false;
            moveRight = false;
            moveUp = false;
            if (p.getPlayerxLocation() > 0) {
                moveLeft = true;
                p.move("left");
            } else {
                p.move("");
                moveLeft = false;
            }
        }
        else if (key == GLUT_KEY_RIGHT) {
            moveLeft = false;
            moveDown = false;
            moveUp = false;
            if (p.getPlayerxLocation() + p.getWidth() * 9 < width) {
                moveRight = true;
                p.move("right");
            } else {
                p.move("");
                moveRight = false;
            }
        }
        else if (key == GLUT_KEY_UP) {
            moveLeft = false;
            moveRight = false;
            moveDown = false;
            if (p.getPlayeryLocation() > 0) {
                moveUp = true;
                p.move("up");
            } else {
                p.move("");
                moveUp = false;
            }
        }
    } else {
        moveDown = false;
        moveLeft = false;
        moveRight = false;
        moveUp = false;
    }
    glutPostRedisplay();
    
    return;
}

void cursor(int x, int y) {
    
    mouse_x = x;
    mouse_y = y;
    
    if (screen == menu) {
        
        // change color of rectangle fill to off-white when mouse hovers over it
        if (r.is_overlapping(x, y)) {
            r.set_color(0.5f, 0.5f, 0.5f);
        } else {
            r.set_color(0.0f, 0.0f, 0.0f);
        }
        
        if (r2.is_overlapping(x, y)) {
            r2.set_color(0.5f, 0.5f, 0.5f);
        } else {
            r2.set_color(0.0f, 0.0f, 0.0f);
        }
        
        if (r7.is_overlapping(x, y)) {
            r7.set_color(0.5f, 0.5f, 0.5f);
        } else {
            r7.set_color(0.0f, 0.0f, 0.0f);
        }
        
    }
    
    if (screen == pause) {
        
        if (r8.is_overlapping(x, y)) {
            r8.set_color(0.5f, 0.5f, 0.5f);
        } else {
            r8.set_color(0.0f, 0.0f, 0.0f);
        }
        
    }
    
    if (screen == leaderboard) {
        
        if (r3.is_overlapping(x, y)) {
            r3.set_color(0.5f, 0.5f, 0.5f);
        } else {
            r3.set_color(0.0f, 0.0f, 0.0f);
        }
        
    }
    
    if (screen == fake_leaderboard) {
        
        if (r6.is_overlapping(x, y)) {
            r6.set_color(0.5f, 0.5f, 0.5f);
        } else {
            r6.set_color(0.0f, 0.0f, 0.0f);
        }
    }
    
    if (screen == game_over || screen == high_first || screen == high_second || screen == high_third || screen == thanks || screen == thanks_high_first || screen == thanks_high_second || screen == thanks_high_third) {
        
        if (r4.is_overlapping(x, y)) {
            r4.set_color(0.5f, 0.5f, 0.5f);
        } else {
            r4.set_color(0.0f, 0.0f, 0.0f);
        }
        
        if (r5.is_overlapping(x, y)) {
            r5.set_color(0.5f, 0.5f, 0.5f);
        } else {
            r5.set_color(0.0f, 0.0f, 0.0f);
        }
    }
    
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    
    mouse_x = x;
    mouse_y = y;
    
    // change the screen when the mouse clicks on buttons
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && screen == pause) {
        if (r8.is_overlapping(x, y)) {
            glutDestroyWindow(wd);
            exit(0);
        }
        else {
            return;
        }
    }
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && screen == menu) {
        if (r.is_overlapping(x,y)) {
            screen = instructions;
        }
        else if (r2.is_overlapping(x, y)) {
            screen = leaderboard;
        }
        else if (r7.is_overlapping(x, y)) {
            glutDestroyWindow(wd);
            exit(0);
        }
        else {
            return;
        }
    }
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && screen == leaderboard) {
        if (r3.is_overlapping(x, y)) {
            screen = menu;
        }
        else {
            return;
        }
    }
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && screen == fake_leaderboard) {
        if (r6.is_overlapping(x, y)) {
            glutDestroyWindow(wd);
            exit(0);
        }
    }
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && (screen == game_over || screen == high_first || screen == high_second || screen == high_third || screen == thanks || screen == thanks_high_first || screen == thanks_high_second || screen == thanks_high_third)) {
        if (r4.is_overlapping(x, y)) {
            screen = fake_leaderboard;
        }
        else if (r5.is_overlapping(x, y)) {
            glutDestroyWindow(wd);
            exit(0);
        }
    }
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && screen == instructions) {
        screen = game_play;
    }
    
    glutPostRedisplay();
}

void timer2(int extra2) {
    
    // initialize player's bullets
    if(p.getLife() > 0 && extra2 > 15){
        NormalBullet bull;
        bull.setWidth(5);
        bull.setHeight(5);
        bull.set_color(0, 1, 2);
        bull.setLocation(p.getPlayerxLocation() + p.getWidth() * 4, p.getPlayeryLocation() + p.getHeight() * 8 - 20);
        normal.push_back(bull);
        check_bull = true;
        extra2=0;
    }
    glutTimerFunc(30, timer2, ++extra2);
    glutPostRedisplay();
    
}

void timer(int extra) {
    
    static bool check_right = true;
    // move the boss back and forth across the screen
    if (check_right && boss.getEnemyxLocation() + boss.getWidth() * 9 < width && screen == game_play) {
        boss.move(5, 0);
    }
    else if (check_right && screen == game_play) {
        check_right = false;
    }
    
    if (check_right == false && boss.getEnemyxLocation() >= 0 && screen == game_play) {
        boss.move(-5, 0);
    }
    else if (check_right == false && screen == game_play) {
        check_right = true;
    }
    
    // move the player's bullets
    if (check_bull == true && screen == game_play) {
        for (int i = 0; i < normal.size(); i++) {
            normal[i].move(0, -5);
        }
    }
    
    // move the enemies
    if (screen == game_play) {
        for (int i = 0; i < enemy1.size(); i++) {
            enemy1[i].move(0, 3);
        }
    }
    
    // move the player with the arrow keys
    if (moveUp == true && p.getPlayeryLocation() > 0 && screen == game_play ) {
        p.move("up");
    }
    if (moveDown == true && p.getPlayeryLocation() + p.getHeight() * 8 < height && screen == game_play) {
        p.move("down");
    }
    if (moveLeft == true && p.getPlayerxLocation() > 0 && screen == game_play) {
        p.move("left");
    }
    if (moveRight == true && p.getPlayerxLocation() + p.getWidth() * 9 < width && screen == game_play) {
        p.move("right");
    }
    
    // initialize boss's bullets
    if (p.getScore() >= bossScore && screen == game_play && extra > 40 && boss.getLife() > 40) {
        NormalBullet bull2;
        bull2.setWidth(5);
        bull2.setHeight(5);
        bull2.set_color(0, 1, 0);
        bull2.setLocation(boss.getEnemyxLocation() + boss.getWidth() * 5, boss.getEnemyyLocation() + boss.getHeight() * 12 + 20);
        normal2.push_back(bull2);
        extra = 0;
    } else if (p.getScore() >= bossScore && screen == game_play && extra > 30 && boss.getLife() <= 40) {
        NormalBullet bull2;
        bull2.setWidth(5);
        bull2.setHeight(5);
        bull2.set_color(0, 1, 0);
        bull2.setLocation(boss.getEnemyxLocation() + boss.getWidth() * 5, boss.getEnemyyLocation() + boss.getHeight() * 12 + 20);
        normal2.push_back(bull2);
        extra = 0;
    }else if (p.getScore() >= bossScore && screen == game_play && extra > 20 && boss.getLife() <= 30) {
        NormalBullet bull2;
        bull2.setWidth(5);
        bull2.setHeight(5);
        bull2.set_color(0, 1, 0);
        bull2.setLocation(boss.getEnemyxLocation() + boss.getWidth() * 5, boss.getEnemyyLocation() + boss.getHeight() * 12 + 20);
        normal2.push_back(bull2);
        extra = 0;
    }else if (p.getScore() >= bossScore && screen == game_play && extra > 10 && boss.getLife() <= 20) {
        NormalBullet bull2;
        bull2.setWidth(5);
        bull2.setHeight(5);
        bull2.set_color(0, 1, 0);
        bull2.setLocation(boss.getEnemyxLocation() + boss.getWidth() * 5, boss.getEnemyyLocation() + boss.getHeight() * 12 + 20);
        normal2.push_back(bull2);
        extra = 0;
    }else if (p.getScore() >= bossScore && screen == game_play && extra > 0 && boss.getLife() <= 10) {
        NormalBullet bull2;
        bull2.setWidth(5);
        bull2.setHeight(5);
        bull2.set_color(0, 1, 0);
        bull2.setLocation(boss.getEnemyxLocation() + boss.getWidth() * 5, boss.getEnemyyLocation() + boss.getHeight() * 12 + 20);
        normal2.push_back(bull2);
        extra = 0;
    }
    
    // move boss's bullets
    if (screen == game_play && p.getScore() >= bossScore) {
        for (int i = 0; i < normal2.size(); i++) {
            normal2[i].move(0, 5);
        }
    }
    
    glutTimerFunc(30, timer, ++extra);
    glutPostRedisplay();
    
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(200, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Fake Galaga!" /* title */);
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();
    
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    
    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);
    
    // handles mouse movement
    glutPassiveMotionFunc(cursor);
    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer
    glutTimerFunc(0, timer, 0);
    glutTimerFunc(0, timer2, 0);
    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
