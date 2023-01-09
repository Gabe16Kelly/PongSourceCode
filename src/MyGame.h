#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>
#include <SDL_ttf.h>
#include <sstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace std;

const int PADDLE_HEIGHT = 60;
const int PADDLE_WIDTH = 20;
const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;

static struct GameData {
    int player1Y = 0;
    int player2Y = 0;
    int ballX = 0;
    int ballY = 0;
    int player1X = 0;
    int player2X = 0;
} game_data;

static struct Score {
    int oldPlayer1Score = 0;
    int oldPlayer2Score = 0;  
    int newPlayer1Score = 0;
    int newPlayer2Score = 0;
} score;

class Particle {

public:
    //Location
    double x;
    double y;
    //Movement
    //double velX;
    //double velY;
    double t = 0.0;
};

class MyGame {

private:
    //Players, Ball and Score
    SDL_Rect player1 = { game_data.player1X, 0, PADDLE_WIDTH, PADDLE_HEIGHT };
    SDL_Rect player2 = { game_data.player2X, 0, PADDLE_WIDTH, PADDLE_HEIGHT };
    SDL_Rect ball = { 0, 0, 10, 10 };
    SDL_Rect playerScore1Rect = { 50, 50, 100, 100 };
    SDL_Rect playerScore2Rect = { 650, 50, 100, 100 };
    //Parallaz Background
    SDL_Rect back = { 0, 0, 800, 600 };
    SDL_Rect cloudFar = { -800, 0, 1600, 600 };
    SDL_Rect cloudNear = { -800, 0, 1600, 600 };
    SDL_Rect mountFar = { -800, 0, 1600, 600 };
    SDL_Rect mountNear = { -800, 0, 1600, 600 };
    SDL_Rect treeNear = { -800, 0, 1600, 600 };
    //Fonts
    TTF_Font* font;
    SDL_Color colour = { 255, 255, 255 };
    //Textures
    SDL_Surface* surface1;
    SDL_Surface* surface2;
    SDL_Surface* surface3;
    SDL_Surface* text;
    SDL_Surface* text2;
    //Players and Ball
    SDL_Texture* bat1;
    SDL_Texture* bat2;
    SDL_Texture* ball1;
    //Parallax Background
    SDL_Texture* background;
    SDL_Texture* farClouds;
    SDL_Texture* nearClouds;
    SDL_Texture* farMountains;
    SDL_Texture* nearMountains;
    SDL_Texture* trees;
    //Score
    SDL_Texture* player1ScoreTexture;
    SDL_Texture* player2ScoreTexture;
    //Sound Effects
    Mix_Chunk* scorePoint;
    Mix_Chunk* hitBat;
    Mix_Chunk* hitWall;
    Mix_Music* backgroundMusic;
    //Strings
    string NewPlayer1ScoreString;
    string NewPlayer2ScoreString;
    //Particles
    SDL_Texture* particle1;
    SDL_Texture* particle2;
    std::vector<Particle*> particles;
public:
    std::vector<std::string> messages;
    void init(SDL_Renderer* renderer);
    void on_receive(std::string message, std::vector<std::string>& args);
    void send(std::string message);
    void input(SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);
    void playBatSound();
    void playWallSound();
    void playScoreSound();
};

#endif