#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <sstream>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

bool replayed = false;

void EditArray(int (&Array)[4], int xmin, int xmax, int ymin, int ymax) {
	Array[0] = xmin;
	Array[1] = xmax;
	Array[2] = ymin;
	Array[3] = ymax;
}

void PlayAgain(sf::RenderWindow& window, bool& GameStarted, bool& GameOver, bool& GameWin, bool& player1Turn, char *Region, int& nbTurn, int& nbTurnDisplay, std::vector<sf::RectangleShape>& crosses, std::vector<sf::CircleShape>& circles, sf::Text& text, sf::Text& txtWin) {
	// -- Rejouer la partie
	if (MessageBox(nullptr, TEXT("Do you want to play again ?"), TEXT("Tic Tac Toe"), MB_YESNO) == IDYES)
	{
		// Initialize Variables
		replayed = false;
		GameStarted = false;
		GameOver = false;
		GameWin = true;
		player1Turn = !player1Turn;

		for (int i = 0; i < 9; i++)
		{
			Region[i] = '0';
		}

		nbTurn = 0;
		nbTurnDisplay = 1;

		std::ostringstream ss;
		ss << "Turn " << nbTurnDisplay << ": ";

		if (player1Turn)
		{
			ss << "Player1's move.";
		}
		else
		{
			ss << "Player2's move.";
			nbTurnDisplay++;
		}
		text.setString(ss.str());
		txtWin.setString("");

		// Reset shapes positsion
		for (unsigned int i = 0; i < circles.size(); i++)
		{
			circles[i].setPosition(-1000, 0);
		}

		for (int i = 0; i < crosses.size() / 2; i++)
		{
			crosses[2 * i].setPosition(-1000, 0);
			crosses[2 * i + 1].setPosition(-1000, 0);
		}
	}
	else
	{
		window.close();
	}
}

int main()
{
	// Creation of the window
	sf::RenderWindow window(sf::VideoMode(750, 700), "Tic Tac Toe");

	// Variable declaration
	bool GameStarted = false;
	bool GameOver = false;
	bool GameWin = true;
	bool player1Turn = true;

	int nbTurn = 0;
	int nbTurnDisplay = 1;
	int Player1Score = 0;
	int Player2Score = 0;

	char Region[9] = {'0', '0', '0', '0', '0', '0', '0', '0', '0'};
	char playerMark = 'O';

	// Music
	sf::Music music;
	music.openFromFile("Sounds/Background.wav");
	music.setVolume(30);
	music.setLoop(true);	
	music.play();

	// Sounds
	sf::SoundBuffer buffer1;
	buffer1.loadFromFile("Sounds/Victory.wav");
	sf::Sound sndVictory;
	sndVictory.setBuffer(buffer1);
	sndVictory.setVolume(70);

	sf::SoundBuffer buffer2;
	buffer2.loadFromFile("Sounds/Draw.wav");
	sf::Sound sndDraw;
	sndDraw.setBuffer(buffer2);
	sndDraw.setVolume(70);

	sf::SoundBuffer buffer3;
	buffer3.loadFromFile("Sounds/Hit.wav");
	sf::Sound sndHit;
	sndHit.setBuffer(buffer3);
	sndHit.setVolume(100);
	
	// Text
	sf::Font font;
	font.loadFromFile("Font/TheBrooklynSmooth.otf");
	
	sf::Text text;
	text.setFont(font);
	text.setString("Turn 1: Player1's move");
	text.setCharacterSize(30);
	text.setPosition(172, 605);
	text.setFillColor(sf::Color::Black);

	sf::Text txtWin;
	txtWin.setFont(font);
	txtWin.setString("");
	txtWin.setCharacterSize(45);
	txtWin.setPosition(195, 610);

	sf::Text invalidMove;
	invalidMove.setFont(font);
	invalidMove.setCharacterSize(35);
	invalidMove.setPosition(110, 640);
	invalidMove.setFillColor(sf::Color::Red);

	sf::Text txtScores;
	txtScores.setFont(font);
	txtScores.setString("Scores");
	txtScores.setCharacterSize(40);
	txtScores.setPosition(620, 15);
	txtScores.setFillColor(sf::Color::Black);

	sf::Text txtPlayer1;
	txtPlayer1.setFont(font);
	txtPlayer1.setString("Player1");
	txtPlayer1.setCharacterSize(30);
	txtPlayer1.setPosition(632, 80);
	txtPlayer1.setFillColor(sf::Color::Red);

	sf::Text txtPlayer1Score;
	txtPlayer1Score.setFont(font);
	txtPlayer1Score.setString("0");
	txtPlayer1Score.setCharacterSize(30);
	txtPlayer1Score.setPosition(665, 110);
	txtPlayer1Score.setFillColor(sf::Color::Black);

	sf::Text txtPlayer2;
	txtPlayer2.setFont(font);
	txtPlayer2.setString("Player2");
	txtPlayer2.setCharacterSize(30);
	txtPlayer2.setPosition(632, 180);
	txtPlayer2.setFillColor(sf::Color::Blue);

	sf::Text txtPlayer2Score;
	txtPlayer2Score.setFont(font);
	txtPlayer2Score.setString("0");
	txtPlayer2Score.setCharacterSize(30);
	txtPlayer2Score.setPosition(665, 210);
	txtPlayer2Score.setFillColor(sf::Color::Black);

	// Creation of Grid
	sf::RectangleShape line1(sf::Vector2f(590,5));
	line1.setFillColor(sf::Color::Black);
	line1.rotate(90);
	line1.setPosition(200, 5);

	sf::RectangleShape line2(sf::Vector2f(590, 5));
	line2.setFillColor(sf::Color::Black);
	line2.rotate(90);
	line2.setPosition(400, 5);

	sf::RectangleShape line3(sf::Vector2f(590, 5));
	line3.setFillColor(sf::Color::Black);
	line3.setPosition(5, 200);
	
	sf::RectangleShape line4(sf::Vector2f(590, 5));
	line4.setFillColor(sf::Color::Black);
	line4.setPosition(5, 400);

	sf::RectangleShape border1(sf::Vector2f(590, 5));
	border1.setFillColor(sf::Color::Black);
	border1.setPosition(5, 0);

	sf::RectangleShape border2(sf::Vector2f(590, 5));
	border2.setFillColor(sf::Color::Black);
	border2.setPosition(5, 595);

	sf::RectangleShape border3(sf::Vector2f(600, 5));
	border3.setFillColor(sf::Color::Black);
	border3.rotate(90);
	border3.setPosition(5, 0);

	sf::RectangleShape border4(sf::Vector2f(600, 5));
	border4.setFillColor(sf::Color::Black);
	border4.rotate(90);
	border4.setPosition(600, 0);

	// -- Creation of Shapes
	//Cross
	std::vector<sf::RectangleShape> crosses;

	sf::RectangleShape cross1(sf::Vector2f(264, 5));
	cross1.rotate(45);
	cross1.setFillColor(sf::Color::Blue);
	cross1.setPosition(-600,0);
	crosses.push_back(cross1);

	sf::RectangleShape cross2(sf::Vector2f(264, 5));
	cross2.rotate(135);
	cross2.setFillColor(sf::Color::Blue);
	cross2.setPosition(-600, 0);
	crosses.push_back(cross2);

	sf::RectangleShape cross3(sf::Vector2f(264, 5));
	cross3.rotate(45);
	cross3.setFillColor(sf::Color::Blue);
	cross3.setPosition(-600, 0);
	crosses.push_back(cross3);

	sf::RectangleShape cross4(sf::Vector2f(264, 5));
	cross4.rotate(135);
	cross4.setFillColor(sf::Color::Blue);
	cross4.setPosition(-600, 0);
	crosses.push_back(cross4);

	sf::RectangleShape cross5(sf::Vector2f(264, 5));
	cross5.rotate(45);
	cross5.setFillColor(sf::Color::Blue);
	cross5.setPosition(-600, 0);
	crosses.push_back(cross5);

	sf::RectangleShape cross6(sf::Vector2f(264, 5));
	cross6.rotate(135);
	cross6.setFillColor(sf::Color::Blue);
	cross6.setPosition(-600, 0);
	crosses.push_back(cross6);

	sf::RectangleShape cross7(sf::Vector2f(264, 5));
	cross7.rotate(45);
	cross7.setFillColor(sf::Color::Blue);
	cross7.setPosition(-600, 0);
	crosses.push_back(cross7);

	sf::RectangleShape cross8(sf::Vector2f(264, 5));
	cross8.rotate(135);
	cross8.setFillColor(sf::Color::Blue);
	cross8.setPosition(-600, 0);
	crosses.push_back(cross8);

	sf::RectangleShape cross9(sf::Vector2f(264, 5));
	cross9.rotate(45);
	cross9.setFillColor(sf::Color::Blue);
	cross9.setPosition(-600, 0);
	crosses.push_back(cross9);

	sf::RectangleShape cross10(sf::Vector2f(264, 5));
	cross10.rotate(135);
	cross10.setFillColor(sf::Color::Blue);
	cross10.setPosition(-600, 0);
	crosses.push_back(cross10);

	//Circle
	std::vector<sf::CircleShape> circles;
	
	sf::CircleShape circle1(92, 30);
	circle1.setFillColor(sf::Color::White);
	circle1.setOutlineThickness(5);
	circle1.setOutlineColor(sf::Color::Red);
	circles.push_back(circle1);

	sf::CircleShape circle2(92, 30);
	circle2.setFillColor(sf::Color::White);
	circle2.setOutlineThickness(5);
	circle2.setOutlineColor(sf::Color::Red);
	circles.push_back(circle2);

	sf::CircleShape circle3(92, 30);
	circle3.setFillColor(sf::Color::White);
	circle3.setOutlineThickness(5);
	circle3.setOutlineColor(sf::Color::Red);
	circles.push_back(circle3);

	sf::CircleShape circle4(92, 30);
	circle4.setFillColor(sf::Color::White);
	circle4.setOutlineThickness(5);
	circle4.setOutlineColor(sf::Color::Red);
	circles.push_back(circle4);

	sf::CircleShape circle5(92, 30);
	circle5.setFillColor(sf::Color::White);
	circle5.setOutlineThickness(5);
	circle5.setOutlineColor(sf::Color::Red);
	circles.push_back(circle5);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left && !replayed)
				{	
					if (player1Turn)
					{
						playerMark = 'O';
					}
					else
					{
						playerMark = 'X';
					}

					int zoneDetected[4] = { -600, 0, 0, 0 };
					bool validMove = true;

					if (Region[0] == '0' && event.mouseButton.x > 0 && event.mouseButton.x < 200 && event.mouseButton.y > 0 && event.mouseButton.y < 200) {
						EditArray(zoneDetected, 0, 200, 0, 200);
						Region[0] = playerMark;
					}
					else if (Region[1] == '0' && event.mouseButton.x > 200 && event.mouseButton.x < 400 && event.mouseButton.y > 0 && event.mouseButton.y < 200) {
						EditArray(zoneDetected, 200, 400, 0, 200);
						Region[1] = playerMark;
					}
					else if (Region[2] == '0' && event.mouseButton.x > 400 && event.mouseButton.x < 600 && event.mouseButton.y > 0 && event.mouseButton.y < 200) {
						EditArray(zoneDetected, 400, 600, 0, 200);
						Region[2] = playerMark;
					}
					else if (Region[3] == '0' && event.mouseButton.x > 0 && event.mouseButton.x < 200 && event.mouseButton.y > 200 && event.mouseButton.y < 400) {
						EditArray(zoneDetected, 0, 200, 200, 400);
						Region[3] = playerMark;
					}
					else if (Region[4] == '0' && event.mouseButton.x > 200 && event.mouseButton.x < 400 && event.mouseButton.y > 200 && event.mouseButton.y < 400) {
						EditArray(zoneDetected, 200, 400, 200, 400);
						Region[4] = playerMark;
					}
					else if (Region[5] == '0' && event.mouseButton.x > 400 && event.mouseButton.x < 600 && event.mouseButton.y > 200 && event.mouseButton.y < 400) {
						EditArray(zoneDetected, 400, 600, 200, 400);
						Region[5] = playerMark;
					}
					else if (Region[6] == '0' && event.mouseButton.x > 0 && event.mouseButton.x < 200 && event.mouseButton.y > 400 && event.mouseButton.y < 600) {
						EditArray(zoneDetected, 0, 200, 400, 600);
						Region[6] = playerMark;
					}
					else if (Region[7] == '0' && event.mouseButton.x > 200 && event.mouseButton.x < 400 && event.mouseButton.y > 400 && event.mouseButton.y < 600) {
						EditArray(zoneDetected, 200, 400, 400, 600);
						Region[7] = playerMark;
					}
					else if (Region[8] == '0' && event.mouseButton.x > 400 && event.mouseButton.x < 600 && event.mouseButton.y > 400 && event.mouseButton.y < 600) {
						EditArray(zoneDetected, 400, 600, 400, 600);
						Region[8] = playerMark;
					}
					else {
						//std::cout << "Selection unvalid, please retry." << std::endl;
						invalidMove.setString("Selection unvalid, please retry.");
						validMove = false;
					}

					if (validMove)
					{
						// Update Text
						std::ostringstream ss; 
						ss << "Turn " << nbTurnDisplay << ": ";

						if (!player1Turn)
						{
							ss << "Player1's move.";
						}
						else
						{
							ss << "Player2's move.";
							nbTurnDisplay++;
						}
						text.setString(ss.str());
						invalidMove.setString("");

						// Play Hit sound
						sndHit.play();

						// Incremente NbTurn
						if (GameStarted && player1Turn)
						{
							nbTurn++;
						}

						// Game Started
						if (!GameStarted)
						{
							GameStarted = true;
						}
						
						// Set position for the shape
						if (player1Turn) {
							circles[nbTurn].setPosition(zoneDetected[0] + 5, zoneDetected[2] + 10);
						}
						else {
							crosses[2 * nbTurn].setPosition(zoneDetected[0] + 8, zoneDetected[2] + 7);
							crosses[2 * nbTurn + 1].setPosition(zoneDetected[1] - 5, zoneDetected[2] + 10);
						}
						
						// Verify combinaisons
						if (Region[0] != '0') {
							if (Region[0] == Region[1] && Region[0] == Region[2])
							{
								GameOver = true;
							}

							if (Region[0] == Region[3] && Region[0] == Region[6])
							{
								GameOver = true;
							}
						}

						if (Region[4] != '0') {
							if (Region[1] == Region[4] && Region[1] == Region[7])
							{
								GameOver = true;
							}

							if (Region[3] == Region[4] && Region[4] == Region[5])
							{
								GameOver = true;
							}

							if (Region[0] == Region[4] && Region[4] == Region[8])
							{
								GameOver = true;
							}

							if (Region[2] == Region[4] && Region[4] == Region[6])
							{
								GameOver = true;
							}
						}

						if (Region[8] != '0')
						{
							if (Region[2] == Region[5] && Region[5] == Region[8])
							{
								GameOver = true;
							}

							if (Region[6] == Region[7] && Region[7] == Region[8])
							{
								GameOver = true;
							}
						}

						if (!GameOver && Region[0] != '0' && Region[1] != '0' && Region[2] != '0' && Region[3] != '0' && Region[4] != '0' && Region[5] != '0' && Region[6] != '0' && Region[7] != '0' && Region[8] != '0')
						{
							GameOver = true;
							GameWin = false;
						}

						if (GameOver)
						{
							text.setString("");

							if (GameWin)
							{	
								if (player1Turn)
								{
									// Joueur 1 gagne
									Player1Score++;
									std::ostringstream ss;
									ss << Player1Score;
									txtPlayer1Score.setString(ss.str());

									txtWin.setFillColor(sf::Color::Red);
									txtWin.setString("Player1 won !");
								}
								else
								{
									// Joueur 2 gagne
									Player2Score++;
									std::ostringstream ss;
									ss << Player2Score;
									txtPlayer2Score.setString(ss.str());

									txtWin.setFillColor(sf::Color::Blue);
									txtWin.setString("Player2 won !");
								}

								// Sound
								sndVictory.play();

							} else {
								// Macth nul
								txtWin.setFillColor(sf::Color::Black);
								txtWin.setString("Draw !");

								// Sound
								sndDraw.play();
							}
						}
						else
						{
							player1Turn = !player1Turn;
						}
					}
				}
			}
		}
		
		window.clear(sf::Color::White);

		if (GameStarted)
		{
			for (unsigned int i = 0; i < nbTurn + 1; i++)
			{
				window.draw(circles[i]);
			}

			for (int i = 0; i < nbTurn + 1; i++)
			{
				window.draw(crosses[2 * i]);
				window.draw(crosses[2 * i + 1]);
			}
		}

		//Draw the Grid
		window.draw(line1);
		window.draw(line2);
		window.draw(line3);
		window.draw(line4);

		window.draw(border1);
		window.draw(border2);
		window.draw(border3);
		window.draw(border4);

		//Draw Texts
		window.draw(text);
		window.draw(txtWin);
		window.draw(invalidMove);
		window.draw(txtScores);
		window.draw(txtPlayer1);
		window.draw(txtPlayer1Score);
		window.draw(txtPlayer2);
		window.draw(txtPlayer2Score);

		window.display();

		//If play again
		if (GameOver)
		{
			replayed = true;
			Sleep(2000);
			PlayAgain(window, GameStarted, GameOver, GameWin, player1Turn, Region, nbTurn, nbTurnDisplay, crosses, circles, text, txtWin);
		}
	}

	return 0;
}

