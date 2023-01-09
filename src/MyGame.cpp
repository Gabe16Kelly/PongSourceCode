#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
#include <string>
#include <SDL_mixer.h>
#include <cstdlib>

#include "MyGame.h"
#include "TextureManager.h"

using namespace std;

void MyGame::init(SDL_Renderer* renderer) {
    //music
    backgroundMusic = TextureManager::loadMusic("resources/backgroundMusic.mp3");
    //Textures
    bat1 = TextureManager::loadTexture("resources/bat1.png", renderer);
    bat2 = TextureManager::loadTexture("resources/bat2.png", renderer);
    ball1 = TextureManager::loadTexture("resources/ball.png", renderer);
    //Backgrounds
    background = TextureManager::loadTexture("resources/background.png", renderer);
    //farClouds = TextureManager::loadTexture("resources/farClouds.png", renderer);
    nearClouds = TextureManager::loadTexture("resources/nearClouds.png", renderer);
    farMountains = TextureManager::loadTexture("resources/farMountains.png", renderer);
    nearMountains = TextureManager::loadTexture("resources/nearMountains.png", renderer);
    trees = TextureManager::loadTexture("resources/trees.png", renderer);
    //fonts
    font = TextureManager::loadFont("resources/minecraft.ttf", 24);
    //sound
    scorePoint = TextureManager::loadSound("resources/score.mp3");
    Mix_VolumeChunk(scorePoint, 70);
    hitBat = TextureManager::loadSound("resources/HitBat.wav");
    hitWall = TextureManager::loadSound("resources/hitWall.wav");
    //particles
    particle1 = TextureManager::loadTexture("resources/particle1.png", renderer);
    particle2 = TextureManager::loadTexture("resources/particle2.png", renderer);
    for (int i = 0; i < 1000; i++)
    {
        Particle* p = new Particle();

        particles.push_back(p);
    }
}

void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {

    if (cmd == "GAME_DATA") {
        // we should have exactly 4 arguments
        if (args.size() == 6) {
            game_data.player1Y = stoi(args.at(0));
            game_data.player2Y = stoi(args.at(1));
            game_data.ballX = stoi(args.at(2));
            game_data.ballY = stoi(args.at(3));
            game_data.player1X = stoi(args.at(4));
            game_data.player2X = stoi(args.at(5));
        }
    }
    else if (cmd == "SCORES") {

        if (args.size() == 2) {
            score.newPlayer1Score = stoi(args.at(0));
            score.newPlayer2Score = stoi(args.at(1));
        }
        playScoreSound();
    }
    else if (cmd == "BALL_HIT_BAT1" || cmd == "BALL_HIT_BAT2")
    {
        playBatSound();
        std::cout << cmd << std::endl;
    }
    else if (cmd == "HIT_WALL_UP" || cmd == "HIT_WALL_DOWN")
    {
        playWallSound();
        std::cout << cmd << std::endl;
    }
}
    void MyGame::playBatSound() {
        Mix_PlayChannel(-1, hitBat, 0);
    }

    void MyGame::playScoreSound() {
        Mix_PlayChannel(-1, scorePoint, 0);
    }

    void MyGame::playWallSound() {
        Mix_PlayChannel(-1, hitWall, 0);
    }


void MyGame::send(std::string message) {
    messages.push_back(message);
}

void MyGame::input(SDL_Event& event) {
    switch (event.key.keysym.sym) {
    case SDLK_w:
        send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
        break;
    case SDLK_s:
        send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
        break;
    case SDLK_i:
        send(event.type == SDL_KEYDOWN ? "I_DOWN" : "I_UP");
        break;
    case SDLK_k:
        send(event.type == SDL_KEYDOWN ? "K_DOWN" : "K_UP");
        break;
    }
}

void MyGame::update(){
    //Updating Player and Ball
    player1.y = game_data.player1Y;
    player2.y = game_data.player2Y;
    player1.x = game_data.player1X;
    player2.x = game_data.player2X;
    ball.y = game_data.ballY;
    ball.x = game_data.ballX;
    //Updating Moving Platforms
    cloudFar.x += 1;
    if (cloudFar.x >= 0) {
        cloudFar.x = -800;
    }

    cloudNear.x += 1;
    if (cloudNear.x >= 0) {
        cloudNear.x = -800;
    }

    mountFar.x += 2;
    if (mountFar.x >= 0) {
        mountFar.x = -800;
    }

    mountNear.x += 3;
    if (mountNear.x >= 0) {
        mountNear.x = -800;
    }

    treeNear.x += 4;
    if (treeNear.x >= 0) {
        treeNear.x = -800;
    }
    //Updating Score
    NewPlayer1ScoreString = to_string(score.newPlayer1Score).c_str();
    NewPlayer2ScoreString = to_string(score.newPlayer2Score).c_str();
    //Updating Particles Movement
    for (auto p : particles) {

        p->t += 0.016;
        // [0..1]
        double randomValue = rand() * 1.0  / RAND_MAX - 0.5;
    
            if (randomValue > 0) {
                    p->t = 0.00;
                    randomValue = rand() * 1.0 / RAND_MAX - 0.5;

                    p->x = game_data.ballX + 2 + randomValue;
                    p->y = game_data.ballY + randomValue;
            }
        
    }
    if (Mix_PlayingMusic() == 0) 
    {
        //Play the music
        Mix_PlayMusic(backgroundMusic, -1);

    }
}

void MyGame::render(SDL_Renderer* renderer) {
    //Rendering Background
    SDL_RenderCopy(renderer, background, NULL, &back);
    SDL_RenderCopy(renderer, farClouds, NULL, &cloudFar);
    SDL_RenderCopy(renderer, nearClouds, NULL, &cloudNear);
    SDL_RenderCopy(renderer, farMountains, NULL, &mountFar);
    SDL_RenderCopy(renderer, nearMountains, NULL, &mountNear);
    SDL_RenderCopy(renderer, trees, NULL, &treeNear);
    //Rendering Particles
    if (score.newPlayer1Score > score.newPlayer2Score) {

        for (auto p : particles) {
            SDL_Rect rect = { p->x + (rand() % 5), p->y + (rand() % 5), (rand() % 8), (rand() % 8) };

            SDL_RenderCopy(renderer, particle1, NULL, &rect);
        }

    }
    else {

        for (auto p : particles) {
            SDL_Rect rect = { p->x + (rand() % 5), p->y + (rand() % 5), (rand() % 8), (rand() % 8) };

            SDL_RenderCopy(renderer, particle2, NULL, &rect);
        }
    }
    //Rendering Players and Ball
    SDL_RenderCopy(renderer, bat1, NULL, &player1);
    SDL_RenderCopy(renderer, bat2, NULL, &player2);
    SDL_RenderCopy(renderer, ball1, NULL, &ball);
    //Rendering Score
    SDL_RenderCopy(renderer, player1ScoreTexture, NULL, &playerScore1Rect);
    SDL_RenderCopy(renderer, player2ScoreTexture, NULL, &playerScore2Rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //Rendering Score
    if (score.oldPlayer1Score != score.newPlayer1Score) {

        text = TTF_RenderText_Solid(font, NewPlayer1ScoreString.c_str(), colour);

        if (text != nullptr) {
            std::cout << "Rendered Font" << std::endl;
        }
        else {
            std::cout << "Failed To Render Font" << std::endl;
        }

        score.oldPlayer1Score = score.newPlayer1Score;
        player1ScoreTexture = SDL_CreateTextureFromSurface(renderer, text);
        SDL_FreeSurface(text);
    }

    if (score.oldPlayer2Score != score.newPlayer2Score) {

        text = TTF_RenderText_Solid(font, NewPlayer2ScoreString.c_str(), colour);

        if (text != nullptr) {
            std::cout << "Rendered Font" << std::endl;
        }
        else {
            std::cout << "Failed To Render Font" << std::endl;
        }

        score.oldPlayer2Score = score.newPlayer2Score;

        player2ScoreTexture = SDL_CreateTextureFromSurface(renderer, text);
        SDL_FreeSurface(text);
    }

    //Rendering Net
    for (int y = 0; y < WINDOW_HEIGHT; ++y)
    {
        if (y % 5)
        {
            SDL_RenderDrawPoint(renderer, WINDOW_WIDTH / 2, y);
        }
    }
    
}






