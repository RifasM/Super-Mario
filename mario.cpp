// Steps to run
// g++ mario.cpp -lGL -lGLU -lglut -lm -lSDL -lSDL_image
// ./a.out
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <iostream>
#include <GL/freeglut.h>
#include<string.h>

using namespace std;

// Variable Declarations
GLfloat x = 0;
int marioPosX = 0, marioPosY = 0, runR = 0, runL = 0, jump = 0, game_over = 0, alive = 1;
int b1 = 1, b2 = 1, b3 = 1, up = 0, mushroom = 0, score = 0, time_left = 1000;
int show = 1, down = 0, ques = 0, q1 = 0, q2 = 0, world = 1, h = 0;
float grow = 1, init_lev = 0;
string game_status = "Game Over!!";

GLvoid * font_style = GLUT_STROKE_ROMAN;
void renderStrokeFont(int p, int q, int r, const char * str) {
    glPushMatrix();

    glTranslatef(p, q, r);
    glLineWidth(5);
    glScalef(0.2, 0.2, 0.2);
    const char * c;
    for (c = str;* c != '\0'; c++)
        glutStrokeCharacter(font_style, * c);

    glPopMatrix();
}

unsigned int loadTexture(const char * filename) {
    SDL_Surface * img = SDL_LoadBMP(filename);
    unsigned int id;
    glGenTextures(1, & id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img -> w, img -> h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img -> pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(img);
    return id;
}

// common textures
unsigned int pipe, question, block;
unsigned int cloud, bush, hill, nill;

// world 1 testures
unsigned int basewall_1, enemy_1, coin_1;
unsigned int brick_1, mario_1, back_1;

// world 2 textures
unsigned int basewall_2, enemy_2, coin_2;
unsigned int brick_2, mario_2, back_2;

void init() {
    glClearColor(0.48, 0.47, 1.0, 1.0); //background color and alpha
    glOrtho(0.0, 1360.0, 0.0, 760.0, -10.0, 10.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    // world 1 textures
    basewall_1 = loadTexture("./bmps/newbase_1.bmp");
    brick_1 = loadTexture("./bmps/brick_1.bmp");
    enemy_1 = loadTexture("./bmps/owl.bmp");
    coin_1 = loadTexture("./bmps/coin_1.bmp");
    mario_1 = loadTexture("./bmps/mario_1.bmp");
    back_1 = loadTexture("./bmps/blue.bmp");

    //world 2 textures
    basewall_2 = loadTexture("./bmps/newbase_2.bmp");
    brick_2 = loadTexture("./bmps/brick_2.bmp");
    enemy_2 = loadTexture("./bmps/bird.bmp");
    coin_2 = loadTexture("./bmps/coin_2.bmp");
    mario_2 = loadTexture("./bmps/mario_2.bmp");
    back_2 = loadTexture("./bmps/black.bmp");

    // common textures
    question = loadTexture("./bmps/question.bmp");
    cloud = loadTexture("./bmps/cloud.bmp");
    bush = loadTexture("./bmps/bush.bmp");
    hill = loadTexture("./bmps/hill.bmp");
    pipe = loadTexture("./bmps/pipe.bmp");
    block = loadTexture("./bmps/block.bmp");
}

void display() {
    // Display White as default color
    glColor3f(1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLint startx = 0, starty = 0;

    // If game not over, or time left, continue game
    if (game_over != 1 && game_over != 2 && time_left != 0) {
        if (world == 1) {

            glClearColor(0.48, 0.47, 1.0, 1.0);
            for (int i = 0; i < 22; i++) {

                glBindTexture(GL_TEXTURE_2D, basewall_1);
                glBegin(GL_QUADS);
                    glTexCoord2f(0.0, 1.0);
                    glVertex3f(startx, starty, 0.0);
                    glTexCoord2f(0.0, 0.0);
                    glVertex3f(startx, starty + 128, 0.0);
                    glTexCoord2f(1.0, 0.0);
                    glVertex3f(startx + 64, starty + 128, 0.0);
                    glTexCoord2f(1.0, 1.0);
                    glVertex3f(startx + 64, starty, 0.0);
                glEnd();

                if (i == 5) {
                    glBindTexture(GL_TEXTURE_2D, cloud);
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.0, 1.0);
                        glVertex3f(startx, starty + 512, 0.0);
                        glTexCoord2f(0.0, 0.0);
                        glVertex3f(startx, starty + 64 + 512, 0.0);
                        glTexCoord2f(1.0, 0.0);
                        glVertex3f(startx + 128, starty + 64 + 512, 0.0);
                        glTexCoord2f(1.0, 1.0);
                        glVertex3f(startx + 128, starty + 512, 0.0);
                    glEnd();

                    glBindTexture(GL_TEXTURE_2D, bush);
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.0, 1.0);
                        glVertex3f(startx, starty + 128, 0.0);
                        glTexCoord2f(0.0, 0.0);
                        glVertex3f(startx, starty + 64 + 128, 0.0);
                        glTexCoord2f(1.0, 0.0);
                        glVertex3f(startx + 256, starty + 64 + 128, 0.0);
                        glTexCoord2f(1.0, 1.0);
                        glVertex3f(startx + 256, starty + 128, 0.0);
                    glEnd();

                }

                if (i == 7) {
                    glBindTexture(GL_TEXTURE_2D, coin_1);
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.0, 1.0);
                        glVertex3f(startx, starty + 664, 0.0);
                        glTexCoord2f(0.0, 0.0);
                        glVertex3f(startx, starty + 32 + 664, 0.0);
                        glTexCoord2f(1.0, 0.0);
                        glVertex3f(startx + 32, starty + 32 + 664, 0.0);
                        glTexCoord2f(1.0, 1.0);
                        glVertex3f(startx + 32, starty + 664, 0.0);
                    glEnd();
                }

                glPushMatrix();
                if (i == 10 && alive == 1) {
                    glTranslatef(-x, 0, 1);
                    glBindTexture(GL_TEXTURE_2D, enemy_1);
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.0, 1.0);
                        glVertex3f(startx, starty + 128, 0.0);
                        glTexCoord2f(0.0, 0.0);
                        glVertex3f(startx, starty + 64 + 128, 0.0);
                        glTexCoord2f(1.0, 0.0);
                        glVertex3f(startx + 64, starty + 64 + 128, 0.0);
                        glTexCoord2f(1.0, 1.0);
                        glVertex3f(startx + 64, starty + 128, 0.0);
                    glEnd();
                }
                glPopMatrix();

                if (i == 13) {
                    glBindTexture(GL_TEXTURE_2D, hill);
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.0, 1.0);
                        glVertex3f(startx, starty + 128, 0.0);
                        glTexCoord2f(0.0, 0.0);
                        glVertex3f(startx, starty + 64 + 128, 0.0);
                        glTexCoord2f(1.0, 0.0);
                        glVertex3f(startx + 192, starty + 64 + 128, 0.0);
                        glTexCoord2f(1.0, 1.0);
                        glVertex3f(startx + 192, starty + 128, 0.0);
                    glEnd();
                }
                if (i == 16) {
                    glBindTexture(GL_TEXTURE_2D, pipe);
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.0, 1.0);
                        glVertex3f(startx, starty + 128, 0.0);
                        glTexCoord2f(0.0, 0.0);
                        glVertex3f(startx, starty + 192 + 128, 0.0);
                        glTexCoord2f(1.0, 0.0);
                        glVertex3f(startx + 128, starty + 192 + 128, 0.0);
                        glTexCoord2f(1.0, 1.0);
                        glVertex3f(startx + 128, starty + 128, 0.0);
                    glEnd();
                }

                if (i >= 9 && i <= 13) {
                    if (b1 == 0 || b1 == 2 && i == 9)
                        glBindTexture(GL_TEXTURE_2D, back_1);
                    else if (b2 == 0 || b2 == 2 && i == 11)
                        glBindTexture(GL_TEXTURE_2D, back_1);
                    else if (b3 == 0 || b3 == 2 && i == 13)
                        glBindTexture(GL_TEXTURE_2D, back_1);
                    else if (i % 2)
                        glBindTexture(GL_TEXTURE_2D, brick_1);
                    else if (i == 12 && q2 == 1)
                        glBindTexture(GL_TEXTURE_2D, block);
                    else
                        glBindTexture(GL_TEXTURE_2D, question);
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.0, 1.0);
                        glVertex3f(startx, starty + 320, 0.0);
                        glTexCoord2f(0.0, 0.0);
                        glVertex3f(startx, starty + 64 + 320, 0.0);
                        glTexCoord2f(1.0, 0.0);
                        glVertex3f(startx + 64, starty + 64 + 320, 0.0);
                        glTexCoord2f(1.0, 1.0);
                        glVertex3f(startx + 64, starty + 320, 0.0);
                    glEnd();
                }

                startx += 64;
            }
        } else if (world == 2) {
            if (init_lev >= 0 && init_lev < 100) {
                glClearColor(0, 0, 0, 1);
                string disp = "Level 1 Completed!";
                renderStrokeFont(600, 500, 1, disp.c_str());
                disp = "Level 2";
                renderStrokeFont(600, 400, 1, disp.c_str());
                init_lev += 1;
                time_left = 1000;
                marioPosX = 70;
                x = 0;
                show = 1;
                alive = b1 = b2 = b3 = 1;
                q2 = q1 = 0;
            }
            else if (init_lev >= 0) {
                if (marioPosY < 0)
                    marioPosY = 0;

                for (int i = 0; i < 22; i++) {
                    glBindTexture(GL_TEXTURE_2D, basewall_2);
                    glBegin(GL_QUADS);
                        glVertex3f(startx, starty, 0.0);
                        glTexCoord2f(0.0, 0.0);
                        glVertex3f(startx, starty + 128, 0.0);
                        glTexCoord2f(1.0, 0.0);
                        glVertex3f(startx + 64, starty + 128, 0.0);
                        glTexCoord2f(1.0, 1.0);
                        glVertex3f(startx + 64, starty, 0.0);
                    glEnd();

                    if (i == 0) {
                        for (int j = 0; j < 800; j += 64) {
                            glBindTexture(GL_TEXTURE_2D, brick_2);
                            glBegin(GL_QUADS);
                                glTexCoord2f(0.0, 1.0);
                                glVertex3f(startx, starty + j, 0.0);
                                glTexCoord2f(0.0, 0.0);
                                glVertex3f(startx, starty + 64 + j, 0.0);
                                glTexCoord2f(1.0, 0.0);
                                glVertex3f(startx + 64, starty + 64 + j, 0.0);
                                glTexCoord2f(1.0, 1.0);
                                glVertex3f(startx + 64, starty + j, 0.0);
                            glEnd();
                        }
                    }
                    glPushMatrix();
                    if (i == 10 && alive == 1) {
                        glTranslatef(-x, 0, 2);
                        glBindTexture(GL_TEXTURE_2D, enemy_2);
                        glBegin(GL_QUADS);
                            glTexCoord2f(0.0, 1.0);
                            glVertex3f(startx, starty + 128, 0.0);
                            glTexCoord2f(0.0, 0.0);
                            glVertex3f(startx, starty + 64 + 128, 0.0);
                            glTexCoord2f(1.0, 0.0);
                            glVertex3f(startx + 64, starty + 64 + 128, 0.0);
                            glTexCoord2f(1.0, 1.0);
                            glVertex3f(startx + 64, starty + 128, 0.0);
                        glEnd();
                    }
                    glPopMatrix();

                    if (i == 7) {
                        glBindTexture(GL_TEXTURE_2D, coin_2);
                        glBegin(GL_QUADS);
                            glTexCoord2f(0.0, 1.0);
                            glVertex3f(startx, starty + 664, 0.0);
                            glTexCoord2f(0.0, 0.0);
                            glVertex3f(startx, starty + 32 + 664, 0.0);
                            glTexCoord2f(1.0, 0.0);
                            glVertex3f(startx + 32, starty + 32 + 664, 0.0);
                            glTexCoord2f(1.0, 1.0);
                            glVertex3f(startx + 32, starty + 664, 0.0);
                        glEnd();
                    }

                    if (i >= 9 && i <= 13) {
                        if (i == 10 && q2 == 1)
                            glBindTexture(GL_TEXTURE_2D, block);
                        else if (i == 13 && q1 == 1)
                            glBindTexture(GL_TEXTURE_2D, block);
                        else
                            glBindTexture(GL_TEXTURE_2D, question);
                        glBegin(GL_QUADS);
                            glTexCoord2f(0.0, 1.0);
                            glVertex3f(startx, starty + 320, 0.0);
                            glTexCoord2f(0.0, 0.0);
                            glVertex3f(startx, starty + 64 + 320, 0.0);
                            glTexCoord2f(1.0, 0.0);
                            glVertex3f(startx + 64, starty + 64 + 320, 0.0);
                            glTexCoord2f(1.0, 1.0);
                            glVertex3f(startx + 64, starty + 320, 0.0);
                        glEnd();
                    }

                    if (i == 16 && b1 == 1) {
                        glBindTexture(GL_TEXTURE_2D, brick_2);
                        glBegin(GL_QUADS);
                            glTexCoord2f(0.0, 1.0);
                            glVertex3f(startx, starty + 320, 0.0);
                            glTexCoord2f(0.0, 0.0);
                            glVertex3f(startx, starty + 64 + 320, 0.0);
                            glTexCoord2f(1.0, 0.0);
                            glVertex3f(startx + 64, starty + 64 + 320, 0.0);
                            glTexCoord2f(1.0, 1.0);
                            glVertex3f(startx + 64, starty + 320, 0.0);
                        glEnd();
                    }

                    if (i > 2 && i < 22) {
                        glBindTexture(GL_TEXTURE_2D, brick_2);
                        glBegin(GL_QUADS);
                            glTexCoord2f(0.0, 1.0);
                            glVertex3f(startx, starty + 720, 0.0);
                            glTexCoord2f(0.0, 0.0);
                            glVertex3f(startx, starty + 64 + 720, 0.0);
                            glTexCoord2f(1.0, 0.0);
                            glVertex3f(startx + 64, starty + 64 + 720, 0.0);
                            glTexCoord2f(1.0, 1.0);
                            glVertex3f(startx + 64, starty + 720, 0.0);
                        glEnd();
                    }
                    startx += 64;
                }
            }
        }

        glPushMatrix();
        startx = starty = 0;
        glTranslated(marioPosX, marioPosY, show);
        if (world == 1)
            glBindTexture(GL_TEXTURE_2D, mario_1);
        else
            glBindTexture(GL_TEXTURE_2D, mario_2);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(startx, starty + 128, 0.0);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(startx, starty + (128 + 64) * grow, 0.0);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(startx + (64 * grow), starty + (128 + 64) * grow, 0.0);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(startx + (64 * grow), starty + 128, 0.0);
        glEnd();
        glPopMatrix();

        glBindTexture(GL_TEXTURE_2D, nill);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(0, 0, 0);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(0, 0, 0);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(0, 0, 0);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(0, 0, 0);
        glEnd();

        if (alive == 1)
            x += 1;
        if (init_lev == 0 || init_lev >= 100) {
            time_left -= 0.5;
            score++;
        }
    }

    if (world == 1) {
        // when world is 1 - 1
        // scoring part starts
        if (alive == 0) {
            score += 100;
            alive = 2;
        }

        if (grow >= 1.2 && mushroom == 1) {
            score += 100;
            mushroom = 2;
        }

        if (b1 == 0) {
            score += 100;
            b1 = 2;
        }

        if (b2 == 0) {
            score += 100;
            b2 = 2;
        }

        if (b3 == 0) {
            score += 100;
            b3 = 2;
        }

        if (q1 == 1)
            q1 = 2;
        else if (q1 == 2 && jump == 0) {
            q1 = 0;
            score += 100;
            ques++;
        }
        // scoring part ends

        // Pipe area, disable running
        if (marioPosX == 970 && marioPosY <= 150)
            runR = 0;
        else if (marioPosX == 1130 && marioPosY <= 150)
            runL = 0;

        // Make mario stand on pipe
        if (marioPosX >= 970 && marioPosX <= 1130 && marioPosY >= 150 && down == 0)
            marioPosY = 170;

        // Make mario grow when mushroom is hit
        if (mushroom == 1 && grow <= 1.2 && mushroom != 2 && world == 1) {
            grow += 0.01;
            q2 = 1;
        }

        // Brick and Question logic
        if (marioPosX >= 570 && marioPosX <= 590 && marioPosY >= 160 && b1 != 2)
            b1 = 0;             // set brick 1 to broken
        else if (marioPosX >= 690 && marioPosX <= 710 && marioPosY >= 160 && b2 != 2)
            b2 = 0;             // set brick 2 to broken
        else if (marioPosX >= 820 && marioPosX <= 840 && marioPosY >= 160 && b3 != 2)
            b3 = 0;             // set brick 3 to broken
        else if (marioPosX >= 620 && marioPosX <= 660 && marioPosY >= 160 && q1 != 2)
            q1 = 1;             // set question 1 to activated
        else if (marioPosX >= 760 && marioPosX <= 800 && marioPosY >= 160 && mushroom != 2)
            mushroom = 1;       // set mushroom to activated

        // If mario is at pipe, going to second level
        if (marioPosX >= 970 && marioPosX <= 1130 && marioPosY == 0 && down == 1)
            down = 0;
        else if (marioPosX >= 970 && marioPosX <= 1130 && marioPosY <= 170 && marioPosX >= 64 && down == 1) {
            marioPosX = 80;
            marioPosX = 0;
            show = 0;
            world = 2;
        }
    }
    else if(world == 2){
        // when world 1 - 2
        // Scoring starts
        if (q2 == 2) {
            q2 = 1;
            ques++;
        }
        else if (q1 == 2) {
            q1 = 1;
            ques++;
        }
        // scoring ends

        // Question and Brick Logic
        if (marioPosX >= 620 && marioPosX <= 660 && marioPosY >= 160 && q2 == 0)
            q2 = 2;     // Question 2 is activated
        if (marioPosX >= 820 && marioPosX <= 840 && marioPosY >= 160 && q1 == 0)
            q1 = 2;     // Question 1 is activated
        if (marioPosX >= 990 && marioPosX <= 1030 && marioPosY >= 160 && b1 == 1)
            b1 = 0;     // Brick 1 is broken
    }

    // Move mario around screen
    if (runR == 1)
        marioPosX += 10;
    else if (runL == 1)
        if (marioPosX != 0)
            marioPosX -= 10;

    // Mario Jumping Logic
    if (up == 1 && jump == 0) {
        jump = 1;           // start jumping
    } else if (up == 1 && jump == 1 && marioPosY < 200)
        marioPosY += 10;    // increase postion when jumping and going up
    else if (up == 1 && jump == 1 && marioPosY == 200)
        up = 0;             // Once max height is reached, set up to 0, indicating, mario is going down
    else if (up == 0 && jump == 1 && marioPosY > 0)
        marioPosY -= 10;    // Decrease mario position when in jump but going down
    else if (up == 0 && jump == 1 && marioPosY == 0)
        jump = 0;           // set jump to 0 when jump complete

    // Mario and enemy Logic
    if (600 - marioPosX == x && marioPosY == 0)
        game_over = 1;     // enemy hits mario - GAME OVER
    else if ((600 - marioPosX <= x + 10 || 600 - marioPosX <= x - 10) && marioPosY <= 64 && alive != 2)
        alive = 0;         // Mario Kills enemy
    else if (marioPosX >= 1200)
        game_over = 2;     // Mario Completes Level - LEVEL COMPLETED

    // Game Status and Display
    if (game_over == 1)
        game_status = "Game Over!";
    else if (game_over == 2)
        game_status = "Level Completed!";

    // If time up or killed, GAME OVER
    if (game_over != 0 || time_left == 0)
        renderStrokeFont(600, 400, 1, game_status.c_str());

    string line1_m = "MARIO";
    string line2_m = to_string(score);

    string line1_w = "WORLD";
    string line2_w = "1 - " + to_string(world);

    string line2_s = " x " + to_string(ques);

    string line1_t = "TIME";
    string line2_t = to_string(time_left);

    // Display Score, Points, World and Time
    renderStrokeFont(100, 700, 1, line1_m.c_str());
    renderStrokeFont(900, 700, 1, line1_w.c_str());
    renderStrokeFont(1150, 700, 1, line1_t.c_str());

    renderStrokeFont(100, 670, 1, line2_m.c_str());
    renderStrokeFont(480, 670, 1, line2_s.c_str());
    renderStrokeFont(900, 670, 1, line2_w.c_str());
    renderStrokeFont(1150, 670, 1, line2_t.c_str());

}

int main(int argc, char ** argv) {
    glutInit( & argc, argv);
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface * screen;
    screen = SDL_SetVideoMode(1200, 600, 32, SDL_SWSURFACE | SDL_OPENGL);
    bool running = true;
    const int FPS = 30;
    Uint32 start;
    SDL_Event event;

    init();

    // check if game is running
    while (running) {
        start = SDL_GetTicks();
        while (SDL_PollEvent( & event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = false;            // if ESC key is pressed, stop running game
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = false;        // if ESC key is pressed, stop running game
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    runL = 1;
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    runR = 1;
                    break;
                case SDLK_w:
                case SDLK_UP:
                case SDLK_SPACE:
                    if (jump == 0)
                        up = 1;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    down = 1;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                case SDLK_a:
                case SDLK_LEFT:
                    runL = 0;
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    runR = 0;
                    break;
                }
                break;
            }
        }

        display();
        SDL_GL_SwapBuffers();
        if (1000 / FPS > SDL_GetTicks() - start)
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
    }
    atexit(SDL_Quit);
    return 0;
}
