#include <iostream>
#include "help.h"
#include <cstdlib>
#include <ctime>
#include <cmath> 
#include <random>
#include <conio.h> 
#include <fstream>

using namespace std;

// Global variables (Instead of passing to every function make it global (modern perablemss requires modern solution))

int Score = 0, Lives = 3;
char game_difficulty = 'm'; // Game difficulty e=> easy, m=> medieum, h => hard


// Struct for enemies 
struct Enemy {
	int uid;  //unique id for each enemy.
	int x;
	int y;
	bool state; //alive or dead.
	int score;
	char direction;
};

struct scores {
	int score;
	char name[100];
};



int uniform_random(int l_limit, int r_limit) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distribution(l_limit, r_limit);
	return distribution(gen);
}

int random(int r_limit)
{
	srand(time(0));
	return (rand() % r_limit + 1); // creates a random number between 0 and r_limit (+1 because else it will not return r_limit)

}

void remove(int box_x, int box_y, int width, int height, char type)
{
	myRect(box_x, box_y, box_x + width, box_y + height, 0, 0, 0);
	switch (type)
	{
	case 'c': // case c means the character or player
		myRect(box_x + 5, box_y - height + 8, box_x + width - 5, box_y - height + 15 + height, 0, 0, 0);
		myRect(box_x + 19, box_y - height - 5, box_x + width - 19, box_y - height + 15 + height, 0, 0, 0);
		myRect(box_x + 15, box_y - height + 2, box_x + width - 15, box_y - height + 15 + height, 0, 0, 0);
		break;
	case 'h':// Draw a gray filled rectangle to  remove something of type 'h'
		myRect(box_x, box_y, box_x + width, box_y + height, 12, 12, 12, 12, 12, 12);
		break;
	case 'm':
		myRect(box_x, box_y, box_x + width, box_y + height, 128, 128, 128, 41, 64, 82);
		break;
	}
}

void draw(int box_x, int box_y, int width, int height, int color, char type)
{
	int r, g, b, fillR, fillG, fillB;
	switch (color)
	{
	case 0: // COLOR CODING SCHEME
		// red
		fillR = 255;
		fillG = 0;
		fillB = 0;
		r = 255;
		g = 0;
		b = 0;
		break;
	case 1:
		// white
		fillR = 255;
		fillG = 255;
		fillB = 255;
		r = 255;
		g = 255;
		b = 255;
		break;
	case 2:
		// enemy
		fillR = 69;
		fillG = 69;
		fillB = 69;
		r = 105;
		g = 105;
		b = 105;
		break;
	case 3:
		// enemy
		fillR = 0;
		fillG = 0;
		fillB = 255;
		r = 0;
		g = 0;
		b = 255;
		break;
		//case 4:
		//	// player prototype (lives)
		//	fillR = 0;
		//	fillG = 128;
		//	fillB = 0;
		//	r = 0;
		//	g = 128;
		//	b = 0;
		//	break;
	case 4:
		//black
		fillR = 0;
		fillG = 0;
		fillB = 0;
		r = 0;
		g = 0;
		b = 0;
		break;
	case 5:
		// Green
		fillR = 0;
		fillG = 255;
		fillB = 0;
		r = 0;
		g = 255;
		b = 0;
		break;
	default:
		// white
		fillR = 255;
		fillG = 255;
		fillB = 255;
		r = 255;
		g = 255;
		b = 255;
		break;
	}
	myRect(box_x, box_y, box_x + width, box_y + height, r, g, b, fillR, fillG, fillB); //bottom spaceship
	switch (type)
	{
	case 'c': //player
		myRect(box_x + 5, box_y - height + 8, box_x + width - 5, box_y - height + 15, r, g, b, fillR, fillG, fillB); // spaceship 2nd part
		myRect(box_x + 15, box_y - height + 2, box_x + width - 15, box_y - height + 15, r, g, b, fillR, fillG, fillB); // spaceship shooter part
		myRect(box_x + 19, box_y - height - 5, box_x + width - 19, box_y - height + 15, r, g, b, fillR, fillG, fillB); // spaceship gun part
		break;
	case 'p': // player prototype (used to display lives in form of player)
		myRect(box_x + 5, box_y - height + 7, box_x + width - 5, box_y - height + 15, r, g, b, fillR, fillG, fillB); // spaceship 2nd part
		myRect(box_x + 14, box_y - height + 2, box_x + width - 14, box_y - height + 15, r, g, b, fillR, fillG, fillB); // spaceship shooter part
		myRect(box_x + 18, box_y - height - 5, box_x + width - 18, box_y - height + 15, r, g, b, fillR, fillG, fillB); // spaceship gun part
		break;
	case 'e':
		myRect(box_x, box_y, box_x + 30, box_y + 30, 0, 0, 255, 255, 0, 0);
		myEllipse(box_x + 12, box_y + 12, box_x + 2, box_y + 5, 0, 0, 0, 255, 255, 255);
		myEllipse(box_x + 27, box_y + 12, box_x + 17, box_y + 5, 0, 0, 0, 255, 255, 255);
		myLine(box_x + 5, box_y + 23, box_x + 25, box_y + 24, 255, 255, 255);
		myLine(box_x + 5, box_y + 25, box_x + 25, box_y + 25, 255, 255, 255);
		break;
	}


}

//----------------------------------------------------------------------------------- File Handling ---------------------------------------------------------------------------------

void load_save_game(int& box_x, int& box_y, Enemy e[]) {
	ifstream save("saveGame.txt");

	for (int i = 0; i < 50; i++) {
		save >> e[i].x;
	}
	for (int i = 0; i < 50; i++) {
		save >> e[i].y;
	}
	for (int i = 0; i < 50; i++) {
		save >> e[i].state;
	}
	for (int i = 0; i < 50; i++) {
		save >> e[i].direction;
	}
	for (int i = 0; i < 50; i++) {
		save >> e[i].uid;
	}
	for (int i = 0; i < 50; i++) {
		save >> e[i].score;
	}
	save >> box_x >> box_y;
	save >> Lives >> Score;
	save >> game_difficulty;
}

void save_game(int box_x, int box_y, Enemy e[]) {
	ofstream save("saveGame.txt");

	for (int i = 0; i < 50; i++) {
		save << e[i].x << " ";
	}
	save << endl;
	for (int i = 0; i < 50; i++) {
		save << e[i].y << " ";
	}
	save << endl;
	for (int i = 0; i < 50; i++) {
		save << e[i].state << " ";
	}
	save << endl;
	for (int i = 0; i < 50; i++) {
		save << e[i].direction << " ";
	}
	save << endl;
	for (int i = 0; i < 50; i++) {
		save << e[i].uid << " ";
	}
	save << endl;
	for (int i = 0; i < 50; i++) {
		save << e[i].score << " ";
	}
	save << endl;
	save << box_x << endl << box_y << endl;
	save << Lives << endl << Score << endl;
	save << game_difficulty;

}

void load_highScore(scores highscores[]) {
	ifstream scoresFile("highScores.txt");
	for (int i = 0; i < 11; i++) {
		scoresFile >> highscores[i].score;
	}
	for (int i = 0; i < 11; i++) {
		scoresFile >> highscores[i].name;
	}

	scores temp;
	// bubble sort on the score to make it in an order 
	for (int i = 0; i < 10; i++) { // where size is 10 so size-1 => 9
		for (int j = 0; j < 10 - i; j++) {
			if (highscores[j].score < highscores[j + 1].score) {
				temp = highscores[j];
				highscores[j] = highscores[j + 1];
				highscores[j + 1] = temp;
			}
		}
	}
}

// ----------------------------------------------------------------------------------- Screen Animations and GUI("Graphical User Interface.") -----------------------------------------------------------------------------------


void generate_stars() {
	int star_x, star_y;
	for (int i = 0; i < 700; i++)//Control No of stars.
	{
		star_x = uniform_random(0, 1000);
		star_y = uniform_random(0, 700);
		myEllipse(star_x, star_y, star_x + 2, star_y + 2, 255, 255, 255);
	}
}

void circle_animation() {
	// going back animation
	int size = 2;
	int mid_screen = -1;
	while (size < 1200) {
		myEllipse(mid_screen - size, mid_screen - size, mid_screen + size, mid_screen + size, 255, 255, 255);
		size++;
	}
}

void screen_animation(int duration = 5, int colorA = 1, int colorB = 4) {    //for Game end screen
	int anim_x = 0;
	for (int j = 0; j < 50; j++) {
		Sleep(duration);
		draw(anim_x, 0, 50, 800, colorA, 'g');
		anim_x += 20;
	}
	anim_x = 0;
	for (int j = 0; j < 50; j++) {
		Sleep(duration);
		draw(anim_x, 0, 50, 800, colorB, 'g');
		anim_x += 20;
	}
}


int drawMenu() {
	// Draw background and stars
	myRect(0, 0, 1000, 1000, 0, 0, 0);
	generate_stars();
	
	int current_choice = 1;
	// Title
	drawText(22, 318, 20, 255, 234, 0, "Space Invaders");
	//Sleep(100);
	int r = 57, g = 255, b = 32;
	int x_ax = 390;
	// Menu options
	drawText(18, x_ax, 100, r, g,b, "Play");
	drawText(18, x_ax, 180, r, g, b, "CONTINUE");
	drawText(18, x_ax, 260, r, g, b, "Instructions");
	drawText(18, x_ax, 340, r, g, b, "SCORES");
	drawText(18, x_ax, 420, r, g, b, "Exit");
	//drawText(18, 50, 600, 255, 0, 0, "Use arrow keys to move. Press space to shoot.");
	//gotoxy(0, 0);
	int whichKey = 0;

		while (true) {
			if (isKeyPressed(whichKey)) {
				switch (whichKey)
				{
				case 2://Up arrow key
					//PlaySound(TEXT("fastinvader2.wav"), NULL, SND_FILENAME | SND_ASYNC);
					if (current_choice == 1) {
						current_choice = 5;
					}
					else {
						current_choice--;
					}
					break;
				case 4://Down arrow key
					//PlaySound(TEXT("fastinvader2.wav"), NULL, SND_FILENAME | SND_ASYNC);
					if (current_choice == 5) {
						current_choice = 1;
					}
					else {
						current_choice++;
					}
					break;
				case 5://Enter key

					PlaySound(TEXT("ufo_highpitch.wav"), NULL, SND_FILENAME | SND_ASYNC);
					return current_choice;
				}
			}
			Sleep(25);
			myRect(x_ax - 45, 110, x_ax - 23, 460, 0, 0, 0);
			r = 0, g = 128, b = 255;
			switch (current_choice) {
			case 1:
				myPointingTriangle(x_ax - 35, 119, 15, 17, r, g, b, r, g, b);
				break;
			case 2:
				myPointingTriangle(x_ax - 35, 199, 15, 17, r, g, b, r, g, b);
				break;
			case 3:
				myPointingTriangle(x_ax - 35, 279, 15, 17, r, g, b, r, g, b);
				break;
			case 4:
				myPointingTriangle(x_ax - 35, 359, 15, 17, r, g, b, r, g, b);
				break;
			case 5:
				myPointingTriangle(x_ax - 35, 439, 15, 17, r, g, b, r, g, b);
				break;
			}
		}
	
	return -1;
}

void display_lives(int width, int height) {
	int live_x = 965, live_y = 22;
	for (int i = 0; i < Lives; i++) {

		live_x -= width + 20;//For Creating Space between life
		draw(live_x, live_y, width, height, 5, 'p');
	}
}

void live_lost_animation(int& x_ax, int& y_ax, int width, int height) { // animation of player losing live
	for (int i = 0; i < 3; i++) {
		remove(x_ax, y_ax, width, height, 'c');
		Sleep(100);
		draw(x_ax, y_ax, width, height, 1, 'c');
		Sleep(100);
	}
}

int drawPauseMenu() {
	int whichKey = 0;
	int current_choice = 1;
	int r = 255, g = 255, b = 255;
	int x_ax = 400;

	remove(x_ax - 80, 95, 350, 290, 'm');

	drawText(20, x_ax - 20, 100, 215, 255, 0, "PAUSE MENU");
	drawText(18, x_ax + 30, 180, r, g, b, "RESUME");
	drawText(18, x_ax + 30, 260, r, g, b, "SAVE GAME");
	drawText(18, x_ax + 30, 340, r, g, b, "EXIT");

	while (true) {
		if (isKeyPressed(whichKey)) {
			switch (whichKey) {
			case 2:
				PlaySound(TEXT("fastinvader2.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (current_choice == 1) {
					current_choice = 3;
				}
				else {
					current_choice--;
				}
				break;
			case 4:
				PlaySound(TEXT("fastinvader2.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (current_choice == 3) {
					current_choice = 1;
				}
				else {
					current_choice++;
				}
				break;
			case 5://Enter key
				PlaySound(TEXT("ufo_highpitch.wav"), NULL, SND_FILENAME | SND_ASYNC);

				return current_choice;
			}
		}
		Sleep(25);
		myRect(x_ax - 45, 150, x_ax - 23, 384, 41, 64, 82, 41, 64, 82);
		r = 0, g = 215, b = 255;
		switch (current_choice) {
		case 1:
			myPointingTriangle(x_ax - 35, 199, 15, 17, r, g, b, r, g, b);
			break;
		case 2:
			myPointingTriangle(x_ax - 35, 279, 15, 17, r, g, b, r, g, b);
			break;
		case 3:
			myPointingTriangle(x_ax - 35, 359, 15, 17, r, g, b, r, g, b);
			break;
		}
	}
}

void displayInstructions() {
	// Display instructions
	system("cls");
	generate_stars();
	//myRect(40, 90, 870, 395, 12, 12, 12, 12, 12, 12);
	drawText(20, 350, 20, 65, 105, 255, " Instructions:");
	drawText(15, 50, 100, 123, 104, 238, " 1");
	drawText(15, 65, 100, 138, 43, 226, "  Use arrows key to move and space to shoot");
	drawText(15, 50, 150, 123, 104, 238, " 2");
	drawText(15, 65, 150, 138, 43, 226, "  Press p anytime to pause game");
	drawText(15, 50, 200, 123, 104, 238, " 3 ");
	drawText(15, 65, 200, 138, 43, 226, "  shoot aliens to score points.");
	drawText(15, 50, 250, 123, 104, 238, " 4 ");
	drawText(15, 65, 250, 138, 43, 226, "  For better experience right click on terminal top ");
	drawText(15, 65, 300, 138, 43, 226, "  go to layout and select win height 137 and width 35");
	drawText(15, 50, 350, 123, 104, 238, " 5 ");
	drawText(15, 65, 350, 138, 43, 226, "  press Space key to go back to menu");
	int key = 0;
	while (key != 8) {
		isKeyPressed(key);
	}
	PlaySound(TEXT("ufo_highpitch.wav"), NULL, SND_FILENAME | SND_ASYNC);
	circle_animation();//if space key is pressed it shows circle animation
}

int drawGameOverScreen(scores highScores[]) {
	generate_stars();
	int highScore = -1;

	for (int i = 0; i < 10; i++) {
		if (highScore < highScores[i].score) {
			highScore = highScores[i].score;
		}
	} // find the high score among the 10 high scores to display in the game 
	drawText(30, 330, 160, 255, 0, 0, "G");
	drawText(30, 360, 160, 255, 255, 255, "AME OVE");
	drawText(30, 570, 160, 0, 255, 0, "R");
	drawText(17, 300, 240, 255, 255, 255, "Your Score: ");
	drawText(17, 570, 240, 0, 255, 215, "", true, Score);
	drawText(17, 300, 290, 255, 255, 255, "HighScore: ");
	drawText(17, 570, 290, 215, 255, 0, "", true, highScore);
	if (Score >= highScore) {
		drawText(30, 260, 50, 255, 215, 0, "New High Score");
	}
	bool list_player = false; // checks if the player score is greater than any highscore listed in the file or struct we stored

	for (int i = 0; i < 10; i++) {
		if (Score > highScores[i].score) {
			list_player = true; // list player truer means to list the player now 
		}
	}
	if (list_player) {
		scores player;
		cout << "Enter your name";
		cin >> player.name;
		player.score = Score;

		highScores[10] = player;
		ofstream oFile("highScores.txt");
		for (int i = 0; i < 11; i++) {
			oFile << highScores[i].score << " ";
		}
		oFile << endl;
		for (int i = 0; i < 11; i++) {
			oFile << highScores[i].name << " ";
		}
	}
	return 0;
}

void display_scores(scores highscore[]) {
	system("cls");
	generate_stars();
	drawText(25, 300, 40, 0, 50, 255, " high  ");
	drawText(25, 400, 40, 0, 120, 255, " scores ");

	int y_axis = 150;
	for (int i = 0; i < 5; i++) {
		drawText(15, 30, y_axis, 150, 43, 226, "", true, i + 1);
		drawText(15, 80, y_axis, 123, 104, 238, highscore[i].name);
		drawText(15, 350, y_axis, 255, 215, 0, "", true, highscore[i].score);
		y_axis += 70;
	}
	y_axis = 150;
	for (int i = 5; i < 10; i++) {
		drawText(15, 530, y_axis, 150, 43, 226, "", true, i + 1);
		drawText(15, 580, y_axis, 123, 104, 238, highscore[i].name);
		drawText(15, 850, y_axis, 255, 215, 0, "", true, highscore[i].score);
		y_axis += 70;
	}
	int whicKey = 0;
	while (whicKey != 8)
	{
		isKeyPressed(whicKey);
	}
	PlaySound(TEXT("ufo_highpitch.wav"), NULL, SND_FILENAME | SND_ASYNC);
	circle_animation();//if space key is pressed it shows circle animation


}

int select_difficulty() {
	system("cls");
	generate_stars();
	int current_choice = 1;
	int key = 0;
	drawText(20, 310, 40, 215, 255, 0, "Select difficulty");
	while (key != 5) {
		isKeyPressed(key);
		switch (current_choice) {
		case 1:
			drawText(20, 80, 300, 0, 255, 0, "easy");
			drawText(20, 400, 300, 255, 255, 255, "medieum");
			drawText(20, 800, 300, 255, 255, 255, "hard");
			break;
		case 2:
			drawText(20, 80, 300, 255, 255, 255, "easy");
			drawText(20, 400, 300, 0, 255, 0, "medieum");
			drawText(20, 800, 300, 255, 255, 255, "hard");
			break;
		case 3:
			drawText(20, 80, 300, 255, 255, 255, "easy");
			drawText(20, 400, 300, 255, 255, 255, "medieum");
			drawText(20, 800, 300, 0, 255, 0, "hard");
			break;
		}
		if (key == 1) {
			PlaySound(TEXT("fastinvader2.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (current_choice == 1) {
				current_choice = 3;
			}
			else {
				current_choice--;
			}
			key = 0;
		}
		else if (key == 3) {
			PlaySound(TEXT("fastinvader2.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (current_choice == 3) {
				current_choice = 1;
			}
			else {
				current_choice++;
			}
			key = 0;
		}

	}
	circle_animation();
	return current_choice;
}
//  ----------------------------------------------------------------------------------- Collisions Section -----------------------------------------------------------------------------------

bool checkPlayerEnemyCollision(int x, int y, int width, int height, Enemy enemies[], int total) {
	for (int i = 0; i < total; i++) {
		if (enemies[i].state) {
			if (x + width > enemies[i].x && x < enemies[i].x + 30 && y + height > enemies[i].y && y - 30 < enemies[i].y + 30) {
				remove(enemies[i].x, enemies[i].y, 30, 30, 'e');
				enemies[i].state = false;
				Lives--;
				return true;
			}
		}
	}
	return false;
}
bool checkBullet(int b_x, int b_y, Enemy e[], int total, bool enemyPrespective = false, int box_x = 0, int box_y = 0, int width = 0, int height = 0) {

	// check bullet is a function made for both checking collision wrt enemy and player (just like draw number in help.h) it checks for Enemy collison with bullet if Enemy prespective is off and if true it checks for player collision with bullet
	if (enemyPrespective == false) {


		for (int i = 0; i < total; i++) {
			if (e[i].state) {
				if (b_x >= e[i].x - 20 && b_x <= e[i].x + 15 && b_y >= e[i].y && b_y <= e[i].y + 70) {// 30 is width of enemy
					remove(e[i].x, e[i].y, 30, 30, 'e');
					Score += e[i].score;
					e[i].state = false;
					return true;
					
					
				}
			}
		}
		return false;
	}//if (enemyPerspective==true){
	else {
	
		if (b_x >= box_x - width / 2 && b_x <= box_x + width - 12 && b_y >= box_y + 12 && b_y <= box_y + height / 2 + 24) {
			Lives -= 1;
			PlaySound(TEXT("explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);
			live_lost_animation(box_x, box_y, width, height);
			return true;
		}
		else {
			return false;
		}
	}
}


//  ----------------------------------------------------------------------------------- Movement Section -----------------------------------------------------------------------------------



void move_enemies(Enemy e[], int total, int r_limit, int l_limit, int b_limit, char& update_direction) {
	Sleep(2);
	int step_horizontal, step_vertical;
	//char previous_direction = ' '; // to keep track of previous direction before moving down so after moving down we can change position to this (updated: now declared in  main function)
	switch (game_difficulty) {
	case 'e':
	{
		step_horizontal = 3;
		step_vertical = 13;
		break;
	}
	case 'm':
	{
		step_horizontal = 5;
		step_vertical = 16;
		break;
	}
	case 'h':
	{
		step_horizontal = 7;
		step_vertical = 19;
		break;
	}
	}
	for (int i = 0; i < total; i++) {
		if (e[i].state) {
			if (e[i].direction == 'r') {
				if (e[i].x + 35 >= r_limit) {
					for (int j = 0; j < total; j++) {
						e[j].direction = 'd'; // Move Down
						update_direction = 'l';
					}
					break;
				}
			}
			else if (e[i].direction == 'l') {
				if (e[i].x - 5 <= l_limit) {
					for (int j = 0; j < total; j++) {
						e[j].direction = 'd'; // Move Down
						update_direction = 'r';
					}
					break;
				}
			}
		}
	}
	for (int i = 0; i < total; i++) {
		if (e[i].state) {
			if (e[i].direction == 'r') {
				remove(e[i].x, e[i].y, 30, 30, 'e'); // 30 is the width and height
				e[i].x += step_horizontal;
				draw(e[i].x, e[i].y, 30, 30, 2, 'e'); // 2 is enemy color coding sceheme
			}
			else if (e[i].direction == 'l') {
				remove(e[i].x, e[i].y, 30, 30, 'e'); // 30 is the width and height
				e[i].x -= step_horizontal;
				draw(e[i].x, e[i].y, 30, 30, 2, 'e'); // 2 is enemy color coding sceheme
			}
			else if (e[i].direction == 'd') {
				remove(e[i].x, e[i].y, 30, 30, 'e'); // 30 is the width and height
				e[i].y += step_vertical;
				draw(e[i].x, e[i].y, 30, 30, 2, 'e'); // 2 is enemy color coding sceheme
				e[i].direction = update_direction;
			}
		}
	}
}


//  ----------------------------------------------------------------------------------- Bullet Section  -----------------------------------------------------------------------------------


void shoot_bullet_player(int& bullet_x, int& bullet_y, Enemy enemies[], int number_of_enemies, int top_limit, bool& shoot, bool& state_bullet) {
	Sleep(5);
	int step_bullet;
	switch (game_difficulty) {
	case 'e':
		step_bullet = 20;
		break;
	case 'm':
		step_bullet = 25;
		break;
	case 'h':
		step_bullet = 30;
		break;
	}
	
	remove(bullet_x + 19, bullet_y - 35, 2, 15, 'b');
	bullet_y -= step_bullet;
	draw(bullet_x + 19, bullet_y - 35, 2, 15, 0, 'b');
	if (checkBullet(bullet_x, bullet_y, enemies, number_of_enemies) || bullet_y < top_limit + 42) {
		PlaySound(TEXT("explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);
		shoot = false;
		remove(bullet_x + 19, bullet_y - 35, 2, 15, 'b');
		state_bullet = false;
	}
}



void shoot_bullet_enemy(int& bullet_x, int& bullet_y, int box_x, int box_y, int bottom_limit, bool& shoot, bool& state_bullet, int width_box, int height_box) {
	Enemy e[1]; // creating a prototype Enemies that I can pass to check bullet function
	Sleep(5);
	int step_bullet = 15;
	switch (game_difficulty) {
	case 'e':
		step_bullet = 15;
		break;
	case 'h':
		step_bullet = 20;
		break;
	}
	remove(bullet_x + 19, bullet_y - 35, 2, 15, 'b');
	bullet_y += step_bullet;
	draw(bullet_x + 19, bullet_y - 35, 2, 15, 3, 'b');
	if (bullet_y >= bottom_limit + 10 || checkBullet(bullet_x, bullet_y, e, 0, true, box_x, box_y, width_box, height_box)) {
		shoot = false;
		remove(bullet_x + 19, bullet_y - 35, 2, 15, 'b');
		state_bullet = false;
	}
}





//  ----------------------------------------------------------------------------------- MAIN FUNCTION  -----------------------------------------------------------------------------------

int main()
{

	int left_limit = 20, right_limit = 940, top_limit = 45, bottom_limit = 470; // defining limits
	int box_x = 400, box_y = 440, step_size = 7, height = 12, width = 40; // player
	char direction = ' ';
	bool game_state = true; //true while playing and false when lost
	int score_x = 20, score_y = 5; // score Axis for further reference



	// Bullet iniitialization (Player)

	bool shoot = false; // state of the bullet true => Shoot button is pressed is there and vice versa
	int bullet_x = 30, bullet_y = 0; // bullet
	bool state_bullet = false; //

	// Bullet iniitialization (Enemies)

	bool shoot_e = false; // state of the bullet true 
	int bullet_x_e = 30, bullet_y_e = 69; // bullet
	bool state_bullet_e = false;
	int shooter_index = 0; // stores the enemy who shot 


	// Enemy initialization
	int latest_x = 30, latest_y = top_limit + 10; // axis where you want to start putting your enemies 
	const int number_of_enemies = 50, rows = 5, columns = 10; // constant
	Enemy enemies[number_of_enemies]; // array of my created struct
	int index = 0; // uid
	char previous_direction = ' '; // instead of making this in moving enemies create it here and pasas it by reference to avoid loss of data


	// ---- Menu handling ---- Reason for not doing it above is if I did it above the enemies will be organized again like it is start of game 
	scores highscores[11];
	load_highScore(highscores); // load scores one time in the beginning once
	int menu_response = -1;
	int difficulty_response = -1; // stores the response of user on difficulty screen
	
	while ( menu_response != 1 && menu_response != 2) {  //to draw menu until user play or continue
		PlaySound(TEXT("spaceInvader.wav"), NULL, SND_FILENAME | SND_ASYNC);
		screen_animation();
		menu_response = drawMenu();
		switch (menu_response)
		{	
		case 1:
			circle_animation();
			difficulty_response = select_difficulty();
			switch (difficulty_response) {
			case 1:
				PlaySound(TEXT("ufo_highpitch.wav"), NULL, SND_FILENAME | SND_ASYNC);
				game_difficulty = 'e'; // selected difficulty
				break;
			case 2:
				PlaySound(TEXT("ufo_highpitch.wav"), NULL, SND_FILENAME | SND_ASYNC);
				game_difficulty = 'm'; // selected difficulty
				break;
			case 3:
				PlaySound(TEXT("ufo_highpitch.wav"), NULL, SND_FILENAME | SND_ASYNC);
				game_difficulty = 'h'; // selected difficulty
				break;
			}
			break;
		case 3:
			circle_animation();
			displayInstructions();
			break;
		case 2:
			circle_animation();
			load_save_game(box_x, box_y, enemies);
			break;
		case 4:
			circle_animation();
			display_scores(highscores);
			break;
		case 5:
			return 0;
		}
	}
	system("cls");


	int add_on_score = 0; // As score is different based on difficulty of game so we will add score of each enemy based on game difficulty (easy => 0 medieum => 30 hard => 60)
	int shoot_interval = 0; // shoot interval is the interval after which any random enemy will shoot we will set it on basis of difficulty of game
	switch (game_difficulty) {
	case 'e':
		add_on_score = 0;
		shoot_interval = 4;
		break;
	case 'm':
		shoot_interval = 3;
		add_on_score = 30;
		break;
	case 'h':
		shoot_interval = 2;
		add_on_score = 60;
		break;
	}

	if (menu_response != 2) { // only update player if user have not opt for continue game option
		for (int i = 0; i < rows; i++) {
			// handling rows of enemies
			for (int j = 0; j < columns; j++) {
				// handling columns of enemies

				switch (i) {
				case 4: // Assigning score based on the row number of the enemies // Lowest score to first row , more to second row and like that most to last (top) row 
					enemies[index].score = 20 + add_on_score;
					break;
				case 3:
				case 2: // same score distribution for both rows
					enemies[index].score = 30 + add_on_score;
					break;
				case 1:
					enemies[index].score = 40 + add_on_score;
					break;
				case 0:
					enemies[index].score = 50 + add_on_score;
					break;

				}
				enemies[index].x = latest_x;
				enemies[index].y = latest_y; // constant for each enemies of row
				enemies[index].state = true;
				enemies[index].direction = 'r';
				latest_x += 70; // creates a distance between the enemies of rows 
				index++;
			}
			latest_y += 40; // distance between rows of enemies 
			latest_x = 30;
		}
	}



	generate_stars();
	// drawText function draws text on the screen with arguments size, x, y, r, g, b, text
	myRect(left_limit - 2, top_limit - 2, right_limit + 2, bottom_limit + 2, 0, 0, 139); // myRect function draws a rectangle with arguments x1, y1, x2, y2, r, g, b, r2, g2, b2
	drawText(16, score_x, score_y, 25, 255, 255, "0"); // draw score as a string in the beginning because 0 doesn't show in thius function when passed as a integer
	drawText(16, right_limit / 2 - 110, score_y, 25, 255, 255, "SPACE INVADERS");
	draw(box_x, box_y, width, height, 1, 'c');//used for drawing spaceship

	for (int i = 0; i < number_of_enemies; i++) { // create enemies 
		if (enemies[i].state) {
			draw(enemies[i].x, enemies[i].y, 30, 30, 2, 'e');
		}
	}


	int whichKey = 0;
	int pause_menu_response = 0;
	while (whichKey != 7) // 7 is the code for ESC key
	{
		if (isKeyPressed(whichKey)) // isKeyPressed function returns true if a key is pressed and whichKey tells that which key was pressed
		{
			switch (whichKey)
			{
			case 1:
				direction = 'L';
				break;
			case 2:
				direction = 'U';
				break;
			case 3:
				direction = 'R';
				break;
			case 4:
				direction = 'D';
				
				break;
			case 8: // space key ADDED IN HELP.H

				shoot = true;
				//Beep(frequency, duration);
			


				break;
			case 9: // p key for Pause menu
				PlaySound(TEXT("ufo_highpitch.wav"), NULL, SND_FILENAME | SND_ASYNC);
				pause_menu_response = drawPauseMenu();
				switch (pause_menu_response) {
					
				case 3: //exit
					return 0;
				case 2://load game
					save_game(box_x, box_y, enemies); // avaoiding break here so case 1 also runs with it
				case 1:// Resume
					myRect(left_limit - 2, top_limit - 2, right_limit + 2, bottom_limit + 2, 0, 0, 139); // regenrate the gaming screen again
					for (int i = 0; i < number_of_enemies; i++) { // create enemies again
						if (enemies[i].state) {
							draw(enemies[i].x, enemies[i].y, 30, 30, 2, 'e');
						}
					}
					draw(box_x, box_y, width, height, 1, 'c'); //draw player again
					break;
				}
				break;
			}
		}

		// enemies shoot randomly logic is implemented here

		if (random(shoot_interval) == 2 && !shoot_e) { // on every run it will taka a random number from 0 to shoot_interval and will shoot if that random number is equal to 2
			shoot_e = true;
			PlaySound(TEXT("invaderkilled.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

		if (shoot_e && !state_bullet_e) { //for finding enemy that will shoot
			bool found_enemy = false; // assign a roll to random enemy if no enemy is in range of player
			for (int i = 0; i < number_of_enemies; i++) {
				int distance = abs(enemies[i].x - box_x);
				if (distance <= 30 && enemies[i].state) { // checks distance among box and enemy
					shooter_index = i;
					found_enemy = true;
					state_bullet_e = true;
					break;
				}
			}
			while (!found_enemy) {
				shooter_index = random(49);
				if (enemies[shooter_index].state) {
					found_enemy = true;
					state_bullet_e = true;
				}
			}
			if (state_bullet_e && enemies[shooter_index].state) {
				bullet_x_e = enemies[shooter_index].x - 5;
				bullet_y_e = enemies[shooter_index].y + 65;
				state_bullet_e = true;
			}
		}

		Sleep(10); 
		if (shoot && !state_bullet) { // For player shooting bulletand drawing bullet
			PlaySound(TEXT("shoot.wav"), NULL, SND_FILENAME | SND_ASYNC);
			bullet_x = box_x;
			bullet_y = box_y;
			draw(bullet_x + 19, bullet_y - 35, 2, 15, 0, 'b');
			state_bullet = true;
		}

		if (game_state == false) {
			myRect(left_limit - 2, top_limit - 2, right_limit + 2, bottom_limit + 2, 139, 0, 0); // change color when user lost the game
		}
		else {
			
			// bullet movement
			

			if (shoot && state_bullet) { // call a bullet function for player => parent
				shoot_bullet_player(bullet_x, bullet_y, enemies, number_of_enemies, top_limit, shoot, state_bullet);
			}
			if (shoot_e && state_bullet_e) {// call a bullet function for enemy[shoter_index] => parent
				
				shoot_bullet_enemy(bullet_x_e, bullet_y_e, box_x, box_y, bottom_limit, shoot_e, state_bullet_e, width, height); // parent is player 'p'
			}
			if (checkPlayerEnemyCollision(box_x, box_y, width, height, enemies, number_of_enemies)) {
				PlaySound(TEXT("explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);

				live_lost_animation(box_x, box_y, width, height);
				remove(box_x, box_y, width, height, 'c');  // remove the player
				box_x = 400, box_y = 440;// reset enemy coordinates
				draw(box_x, box_y, width, height, 1, 'c');// redraws player
			}
			move_enemies(enemies, number_of_enemies, right_limit, left_limit, bottom_limit, previous_direction);
			display_lives(width, height);

			// update header of game (includes game_score) except game name
			remove(score_x, score_y, 100, 31, 'h');  // basically removes the whole header of game to update game header before Game name
			remove(right_limit - 160, score_y - 5, right_limit, 40, 'h');  // basically removes the whole header of game to update game header before Game name
			if (Score == 0) {
				drawText(16, score_x, score_y, 25, 255, 255, "0"); // draw text doesn't display integer when int == 0 so display a "0" while score = 0
			}
			else {
				drawText(16, score_x, score_y, 25, 255, 255, "", true, Score);
			}
			display_lives(width, height);

			// checking if any of the enemy hit bottom line
			for (int i = 0; i < 50; i++) {
				if (enemies[i].y >= bottom_limit - 40) {
					Lives = -1;
				}
			}

			if (Lives <= 0) {
				PlaySound(TEXT("GameOver.wav"), NULL, SND_FILENAME | SND_ASYNC);
				screen_animation();
				drawGameOverScreen(highscores);
				return 0;
			}

			//For player (spaceship) movements:
			switch (direction)
			{
			case 'L':
				// Left
				step_size = 8;
				remove(box_x, box_y, width, height, 'c');
				if (box_x - 10 > left_limit)
					box_x -= step_size;
				draw(box_x, box_y, width, height, 1, 'c');
				direction = ' ';
				break;
			case 'U':
				// Up
				step_size = 4;
				remove(box_x, box_y, width, height, 'c');
				if (box_y - 20 > top_limit) // right_limit/2+90 if want to restrict movement half way of player
					box_y -= step_size;
				draw(box_x, box_y, width, height, 1, 'c');
				direction = ' ';
				break;
			case 'R':
				// Right
				step_size = 8;
				remove(box_x, box_y, width, height, 'c');
				if (box_x + 50 < right_limit)
					box_x += step_size;
				draw(box_x, box_y, width, height, 1, 'c');
				direction = ' ';
				break;
			case 'D':
				// Down
				step_size = 4;
				remove(box_x, box_y, width, height, 'c');
				if (box_y + 20 < bottom_limit)
					box_y += step_size;
				draw(box_x, box_y, width, height, 1, 'c');
				direction = ' ';
				break;
			}
		}
	}
	return 0;

}