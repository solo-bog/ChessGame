#include <SFML/Graphics.hpp>
#include <iostream>
#include "Chess.h"
#include "ChessGame.h"
#include <string>
#include <iomanip>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace sf;
using namespace std;




Player::Player(string name, int color) :name(name), color(color) {

}
string Player::getName() {
	return name;
}
int Player::getColor() {
	return color;
}




void ChessBoard::close() {
	window->close();
}

ChessBoard::ChessBoard(Board* board) :realBoard(board) {
	window = new RenderWindow(sf::VideoMode(WIDTH, HEIGTH), "Chess The Game Of Kings!");
}

void ChessBoard::RefreshBoard() {
	sf::RectangleShape rectangle[64];
	sf::Texture texture[65];
	sf::Sprite sprite[65];
	loadtextures(texture);
	loadboard(texture, rectangle, sprite);
	window->clear();
	for (int j = 0; j < 64; ++j)
		window->draw(rectangle[j]);
	for (int j = 0; j < 65; j++) {
		window->draw(sprite[j]);
	}

	window->display();
}
void ChessBoard::waitClose() {
	sf::Event event;
	while(window->isOpen()){
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window->close();
				exit(1);
			}

		}
	}
	
}


void ChessBoard::loadtextures(Texture texture[64]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (realBoard->getPiece(i, j) == nullptr) {
				continue;
			}
			if (realBoard->getPiece(i, j)->getName() == 'r')
				texture[i*8+j].loadFromFile("images/blackRook.png");
			if (realBoard->getPiece(i, j)->getName() == 'n')
				texture[i * 8 + j].loadFromFile("images/blackKnight.png");
			if (realBoard->getPiece(i, j)->getName() == 'b')
				texture[i * 8 + j].loadFromFile("images/blackBishop.png");
			if (realBoard->getPiece(i, j)->getName() == 'q')
				texture[i * 8 + j].loadFromFile("images/blackQueen.png");
			if (realBoard->getPiece(i, j)->getName() == 'k')
				texture[i * 8 + j].loadFromFile("images/blackKing.png");
			if (realBoard->getPiece(i, j)->getName() == 'p')
				texture[i * 8 + j].loadFromFile("images/blackPawn.png");
			if (realBoard->getPiece(i, j)->getName() == 'R')
				texture[i * 8 + j].loadFromFile("images/whiteRook.png");
			if (realBoard->getPiece(i, j)->getName() == 'N')
				texture[i * 8 + j].loadFromFile("images/whiteKnight.png");
			if (realBoard->getPiece(i, j)->getName() == 'B')
				texture[i * 8 + j].loadFromFile("images/whiteBishop.png");
			if (realBoard->getPiece(i, j)->getName() == 'Q')
				texture[i * 8 + j].loadFromFile("images/whiteQueen.png");
			if (realBoard->getPiece(i, j)->getName() == 'K')
				texture[i * 8 + j].loadFromFile("images/whiteKing.png");
			if (realBoard->getPiece(i, j)->getName() == 'P')
				texture[i * 8 + j].loadFromFile("images/whitePawn.png");
		}

	}
}
void ChessBoard::loadboard(Texture texture[64], RectangleShape rectangle[64], Sprite sprite[64]) {
	for (int j = 0; j < 64; j++) {
		sprite[j].setTexture(texture[j]);
		sprite[j].setScale(1.7f, 1.7f);
		rectangle[j].setSize(sf::Vector2f(WIDTH / 8.0f, HEIGTH / 8.0f));
	}
	
	int counter = 0;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			rectangle[counter].setPosition(j * rectangle[counter].getSize().y, i * rectangle[counter].getSize().x);  ///x,y
			sprite[counter].setPosition(j * rectangle[counter].getSize().y, i * rectangle[counter].getSize().x);
			if ((i + j) % 2 == 0)
				rectangle[counter].setFillColor(sf::Color::White);
			else
				rectangle[counter].setFillColor(sf::Color::Blue);
			counter++;
		}
	}
}
vector<int> ChessBoard::EnterMove(int color)
{

	sf::RectangleShape rectangle[64];
	sf::Texture texture[65];
	sf::Sprite sprite[65];
	loadtextures(texture);
	loadboard(texture, rectangle, sprite);
	int n = -1, m = -1;
	while (n == -1 || m == -1)
	{
		Vector2i pos = Mouse::getPosition(*window);
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window->close();
				exit(1);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				for (int j = 0; j < 64; ++j) {
					if (rectangle[j].getGlobalBounds().contains(pos.x, pos.y))
					{
						

						if (realBoard->getPiece(j / 8, j % 8) != nullptr) {
							if (realBoard->getPiece(j / 8, j % 8)->getColor() == color) {
								n = j;
								if (rectangle[n].getFillColor() != sf::Color::Red) {
									int counter = 0;
									for (int i = 0; i < 8; ++i)
									{
										for (int k = 0; k < 8; ++k)
										{
											if ((i + k) % 2 == 0)
												rectangle[counter].setFillColor(sf::Color::White);
											else
												rectangle[counter].setFillColor(sf::Color::Blue);
											counter++;
										}
									}
									rectangle[n].setFillColor(sf::Color::Red);
									break;
								}
								else {
									int counter = 0;
									for (int i = 0; i < 8; ++i)
									{
										for (int k = 0; k < 8; ++k)
										{
											if ((i + k) % 2 == 0)
												rectangle[counter].setFillColor(sf::Color::White);
											else
												rectangle[counter].setFillColor(sf::Color::Blue);
											counter++;
										}
									}
								}
								
							}
							else {
								n = -1;
							}

						}
						else {
							n = -1;
						}


					}

				}


			}
			if (n != -1)
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					for (int j = 0; j < 64; ++j) {
						if (rectangle[j].getGlobalBounds().contains(pos.x, pos.y)) {
							m = j;
							break;
						}
					}

				}
		}

		window->clear();
		for (int j = 0; j < 64; ++j)
			
			window->draw(rectangle[j]);
		for (int j = 0; j < 65; j++) {
			window->draw(sprite[j]);
		}

		window->display();
	}
	vector<int> moves{ n / 8,n % 8,m / 8,m % 8 };
	return moves;
}



Command::Command(Board * board, int x, int y, int nextX, int nextY) :board(board), x(x), y(y), nextX(nextX), nextY(nextY) {

}

string Command::getMove() {
	return "-";
}

string MakeMove::getMove() {
	int A = 65 + y;
	int B = 8 - x;
	int C = 65 + nextY;
	int D = 8 - nextX;
	string outStr = (char)A + to_string(B) + "-" + (char)C + to_string(D);
	if (casting) {
		return outStr + " (Casting)";
	}
	else if (deletedPiece != '0') {
		return outStr +" (deleted "+ deletedPiece+")";
	}
	else {
		return outStr;
	}
	
}
int Command::getX() {
	return x;
}
int Command::getY() {
	return y;
}



MakeMove::MakeMove(Board * board, int x, int y, int nextX, int nextY) :Command(board, x, y, nextX, nextY), deletedPiece('0'), PawnToQueen(false), casting(false) {

}
void MakeMove::Execute() {
	if (board->getPiece(x, y)->getName() == 'k' && x == 0 && y == 4 && nextX == 0 && (nextY == 2 || nextY == 6)) {
		board->casting(x, y, nextX, nextY);
		casting = true;
		return;
	}
	else if (board->getPiece(x, y)->getName() == 'K' && x == 7 && y == 4 && nextX == 7 && (nextY == 2 || nextY == 6)) {
		board->casting(x, y, nextX, nextY);
		casting = true;
		return;
	}
	if (board->getPiece(nextX, nextY) != nullptr) {
		deletedPiece = board->getPiece(nextX, nextY)->getName();
	}
	board->movePiece(x, y, nextX, nextY);
	if (board->getPiece(nextX, nextY)->getName() == 'p' && nextX == 7) {
		board->replacementPiece('q', nextX, nextY);
		PawnToQueen = true;
	}
	else if (board->getPiece(nextX, nextY)->getName() == 'P' && nextX == 0) {
		board->replacementPiece('Q', nextX, nextY);
		PawnToQueen = true;
	}


}


void MakeMove::Undo() {

	board->movePiece(nextX, nextY, x, y);
	if (deletedPiece != '0') {
		board->addPiece(deletedPiece, nextX, nextY);
	}

	if (PawnToQueen) {
		if (board->getPiece(x, y)->getColor()) {
			board->replacementPiece('p', x, y);
		}
		else {
			board->replacementPiece('P', x, y);
		}
	}
	if (casting) {
		if (nextY > y) {
			board->movePiece(x, 5, x, 7);
		}
		else {
			board->movePiece(x, 3, x, 0);
		}
	}
	delete this;
}




Rules::Rules(Board * inputBoard) :board(inputBoard) {
	blackKing = board->getPiece(0, 4);
	whiteKing = board->getPiece(7, 4);
	command = nullptr;
	GameOver = false;
	Pat = false;

}
bool Rules::isGameOver() {

	return GameOver;
}
vector<Command*>* Rules::getJournal() {
	return &journal;
}
void Rules::checkMove(int x, int y, int nextX, int nextY) {
	command = new MakeMove(board, x, y, nextX, nextY);
	command->Execute();
	journal.push_back(command);
}

void Rules::undoMove() {
	command = journal.back();
	command->Undo();
	journal.pop_back();
}
void Rules::checkShachMate(int colorOfNextMove) {
	if (this->checkShach(colorOfNextMove)[0] != -1) {
		cout << "<-------------Shach!!!------------>" << endl;
		if (this->checkMate(colorOfNextMove)) {
			cout << "<-------------Mate!!!------------>" << endl;
			GameOver = true;
		}
	}
	else if (this->genereteMoves(abs(colorOfNextMove - 1)).size() == 0) {
		cout << "Pat" << endl;
		GameOver = true;
		Pat = true;
	}
}
vector<int> Rules::checkShach(int color) {
	vector<int> atackedPiece(2);
	atackedPiece[0] = -1;
	atackedPiece[1] = -1;
	Piece* ptrKing;
	vector<Piece*>* ptrPieces;
	if (color) {
		ptrKing = whiteKing;
		ptrPieces = board->getBlackPieces();
	}
	else {
		ptrKing = blackKing;

		ptrPieces = board->getWhitePieces();
	}
	for (int i = 0; i < ptrPieces->size(); i++) {
		if ((*ptrPieces)[i]->canMove(ptrKing->getX(), ptrKing->getY(), board->getBoard())) {
			atackedPiece[0] = (*ptrPieces)[i]->getX();
			atackedPiece[1] = (*ptrPieces)[i]->getY();
			return atackedPiece;

		}
	}

	return atackedPiece;
}

bool Rules::canCasting(int x, int y, int nextX, int nextY) {
	for (int i = 0; i < journal.size(); i++) {

		if (nextY > y) {
			if ((journal[i]->getX() == x && journal[i]->getY() == y) || (journal[i]->getX() == x && journal[i]->getY() == 7)) {
				return false;
			}
		}
		else {
			if ((journal[i]->getX() == x && journal[i]->getY() == y) || (journal[i]->getX() == x && journal[i]->getY() == 0)) {
				return false;
			}
		}
	}
	if (nextY > y) {
		for (int i = y + 1; i < 7; i++) {
			if (board->getPiece(x, i) != nullptr) {
				return false;
			}
		}
		if (board->getPiece(x, y)->getColor()) {
			for (int i = y; i < 7; i++) {
				for (int j = 0; j < board->getWhitePieces()->size(); j++) {
					Piece* tempPiece = (*board->getWhitePieces())[j];

					if (tempPiece->canMove(x, i, board->getBoard())) {
						return false;
					}
				}
			}
		}
		else {
			for (int i = y; i < 7; i++) {
				for (int j = 0; j < board->getBlackPieces()->size(); j++) {
					Piece* tempPiece = (*board->getBlackPieces())[j];
					if (tempPiece->canMove(x, i, board->getBoard())) {
						return false;
					}
				}
			}
		}
	}
	else if (nextY < y) {
		for (int i = y - 1; i > 0; i--) {
			if (board->getPiece(x, i) != nullptr) {
				return false;
			}
		}
		if (board->getPiece(x, y)->getColor()) {
			for (int i = y; i > 1; i--) {
				for (int j = 0; j < board->getWhitePieces()->size(); j++) {
					Piece* tempPiece = (*board->getWhitePieces())[j];
					if (tempPiece->canMove(x, i, board->getBoard())) {
						return false;
					}
				}
			}
		}
		else {
			for (int i = y; i > 1; i--) {
				for (int j = 0; j < board->getBlackPieces()->size(); j++) {
					Piece* tempPiece = (*board->getBlackPieces())[j];

					if (tempPiece->canMove(x, i, board->getBoard())) {
						return false;
					}
				}
			}
		}
	}
	else {
		return false;
	}
	return true;


}


bool Rules::canMoveFromTo(int x, int y, int nextX, int nextY, int color) {

	Piece* beginPiece = board->getPiece(x, y);
	Piece* endPiece = board->getPiece(nextX, nextY);
	bool answer = true;
	if (beginPiece != nullptr) {
		if (beginPiece->getName() == 'k' && x == 0 && y == 4 && nextX == 0 && (nextY == 2 || nextY == 6)) {
			return canCasting(x, y, nextX, nextY);
		}
		else if (beginPiece->getName() == 'K' && x == 7 && y == 4 && nextX == 7 && (nextY == 2 || nextY == 6)) {
			return canCasting(x, y, nextX, nextY);
		}
		else if ((beginPiece->getColor() == color) && beginPiece->canMove(nextX, nextY, board->getBoard())) {
			this->checkMove(x, y, nextX, nextY);
			if (this->checkShach(abs(color - 1))[0] != -1) {

				answer = false;
			}
			this->undoMove();
		}
		else {
			answer = false;
		}


	}
	else {
		answer = false;
	}
	return answer;

}

bool Rules::checkMate(int color) {
	vector<int> atackedPiece = checkShach(color);
	if (atackedPiece[0] == -1) {
		return false;
	}
	Piece* ptrKing;
	vector<Piece*>* ptrPieces;
	if (color) {
		ptrKing = whiteKing;
		ptrPieces = board->getWhitePieces();
	}
	else {
		ptrKing = blackKing;
		ptrPieces = board->getBlackPieces();
	}

	for (int x = ptrKing->getX() - 1; x < ptrKing->getX() + 2; x++) {
		for (int y = ptrKing->getY() - 1; y < ptrKing->getY() + 2; y++) {
			if ((0 <= x && x < 8) && (0 <= y && y < 8)) {
				if (this->canMoveFromTo(ptrKing->getX(), ptrKing->getY(), x, y, abs(color - 1))) {

					return false;

				}
			}
		}
	}

	for (int i = 0; i < (*ptrPieces).size(); i++) {
		if (canMoveFromTo((*ptrPieces)[i]->getX(), (*ptrPieces)[i]->getY(), atackedPiece[0], atackedPiece[1], abs(color - 1))) {
			return false;
		}
	}
	if (board->getPiece(atackedPiece[0], atackedPiece[1])->getName() == 'n' || board->getPiece(atackedPiece[0], atackedPiece[1])->getName() == 'N') {
		return true;
	}




	if (ptrKing->getX() < atackedPiece[0] && ptrKing->getY() < atackedPiece[1]) {
		for (int x = ptrKing->getX() + 1, y = ptrKing->getY() + 1; x < atackedPiece[0] && y < atackedPiece[1]; x++, y++) {
			for (int i = 0; i < (*ptrPieces).size(); i++) {
				if (canMoveFromTo((*ptrPieces)[i]->getX(), (*ptrPieces)[i]->getY(), x, y, abs(color - 1))) {
					return false;
				}
			}
		}
	}
	else if (ptrKing->getX() < atackedPiece[0] && ptrKing->getY() > atackedPiece[1]) {
		for (int x = ptrKing->getX() + 1, y = ptrKing->getY() - 1; x < atackedPiece[0] && y > atackedPiece[1]; x++, y--) {
			for (int i = 0; i < (*ptrPieces).size(); i++) {
				if (canMoveFromTo((*ptrPieces)[i]->getX(), (*ptrPieces)[i]->getY(), x, y, abs(color - 1))) {
					return false;
				}
			}
		}
	}
	else if (ptrKing->getX() > atackedPiece[0] && ptrKing->getY() > atackedPiece[1]) {
		for (int x = ptrKing->getX() - 1, y = ptrKing->getY() - 1; x > atackedPiece[0] && y > atackedPiece[1]; x--, y--) {
			for (int i = 0; i < (*ptrPieces).size(); i++) {
				if (canMoveFromTo((*ptrPieces)[i]->getX(), (*ptrPieces)[i]->getY(), x, y, abs(color - 1))) {
					return false;
				}
			}
		}
	}
	else if (ptrKing->getX() > atackedPiece[0] && ptrKing->getY() < atackedPiece[1]) {
		for (int x = ptrKing->getX() - 1, y = ptrKing->getY() + 1; x > atackedPiece[0] && y < atackedPiece[1]; x--, y++) {
			for (int i = 0; i < (*ptrPieces).size(); i++) {
				if (canMoveFromTo((*ptrPieces)[i]->getX(), (*ptrPieces)[i]->getY(), x, y, abs(color - 1))) {
					return false;
				}
			}
		}
	}
	else if (ptrKing->getX() == atackedPiece[0] && ptrKing->getY() < atackedPiece[1]) {
		for (int x = ptrKing->getX(), y = ptrKing->getY() + 1; y < atackedPiece[1]; y++) {
			for (int i = 0; i < (*ptrPieces).size(); i++) {
				if (canMoveFromTo((*ptrPieces)[i]->getX(), (*ptrPieces)[i]->getY(), x, y, abs(color - 1))) {
					return false;
				}
			}
		}
	}
	else if (ptrKing->getX() == atackedPiece[0] && ptrKing->getY() > atackedPiece[1]) {
		for (int x = ptrKing->getX(), y = ptrKing->getY() - 1; y > atackedPiece[1]; y--) {
			for (int i = 0; i < (*ptrPieces).size(); i++) {
				if (canMoveFromTo((*ptrPieces)[i]->getX(), (*ptrPieces)[i]->getY(), x, y, abs(color - 1))) {
					return false;
				}
			}
		}
	}
	else if (ptrKing->getX() < atackedPiece[0] && ptrKing->getY() == atackedPiece[1]) {
		for (int x = ptrKing->getX() + 1, y = ptrKing->getY(); x < atackedPiece[1]; x++) {
			for (int i = 0; i < (*ptrPieces).size(); i++) {
				if (canMoveFromTo((*ptrPieces)[i]->getX(), (*ptrPieces)[i]->getY(), x, y, abs(color - 1))) {
					return false;
				}
			}
		}
	}
	else if (ptrKing->getX() > atackedPiece[0] && ptrKing->getY() == atackedPiece[1]) {
		for (int x = ptrKing->getX() - 1, y = ptrKing->getY(); x > atackedPiece[1]; x--) {
			for (int i = 0; i < (*ptrPieces).size(); i++) {
				if (canMoveFromTo((*ptrPieces)[i]->getX(), (*ptrPieces)[i]->getY(), x, y, abs(color - 1))) {
					return false;
				}
			}
		}
	}
	return true;


}

vector<vector<int>> Rules::genereteMoves(int color) {
	vector<vector<int>> allMoves;
	vector<int> Coordinates;
	vector<Piece*>* ptrPieces;
	if (color) {
		ptrPieces = board->getBlackPieces();
	}
	else {
		ptrPieces = board->getWhitePieces();
	}
	for (int i = 0; i < (*ptrPieces).size(); i++) {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {

				if (this->canMoveFromTo((*ptrPieces)[i]->getX(), (*ptrPieces)[i]->getY(), x, y, color)) {
					Coordinates.push_back((*ptrPieces)[i]->getX());
					Coordinates.push_back((*ptrPieces)[i]->getY());
					Coordinates.push_back(x);
					Coordinates.push_back(y);
					allMoves.push_back(Coordinates);
					Coordinates.clear();
				}
			}
		}
	}
	return allMoves;
}







//Абстрактний клас гра

Game::Game(string PlayerName, int color) {
	board = new Board;
	chessRules = new Rules(board);
	player1 = new Player(PlayerName, color);
	colorOfNextMove = 0;
	journal = chessRules->getJournal();
	gui = new ChessBoard(board);
}
Game::~Game() {
	delete board;
	delete player1;
}

void Game::getWinner() {
	cout<< "none"<<endl;
}

bool Game::isGameOver() {

	return chessRules->isGameOver();
}

Board* Game::getBoard() {
	return board;
}

void Game::showMove() {
	cout << chessRules->getJournal()->back()->getMove() << endl;
}

void Game::showBoard() {
	gui->RefreshBoard();
}
void Game::close() {
	gui->waitClose();
}

void Game::Move() {
	vector<int> moves(4);
	bool incorrectInput = true;
	do {
		moves = gui->EnterMove(colorOfNextMove);
		//moves = console.EnterMove();


	} while (!chessRules->canMoveFromTo(moves[0], moves[1], moves[2], moves[3], colorOfNextMove));
	chessRules->checkMove(moves[0], moves[1], moves[2], moves[3]);
	chessRules->checkShachMate(colorOfNextMove);
	colorOfNextMove = abs(colorOfNextMove - 1);
}

void Game::Undo() {
	if ((*journal).size() == 0)
	{
		cout << "There is nothing to undo!" << endl;
	}
	else {
		chessRules->undoMove();
		colorOfNextMove = abs(colorOfNextMove - 1);
	}
}



//Клас одиночна гра(з комп*ютером)

double SinglePlayer::minimax(int depth, double alpha, double beta, int color) {
	if (depth == 0) {
		return -board->evaluateBoard();
	}
	vector<vector<int>> allMoves = chessRules->genereteMoves(color);

	if (color) {
		double bestMove = -9999;
		for (int i = 0; i < allMoves.size(); i++) {
			int x = allMoves[i][0];
			int y = allMoves[i][1];
			int nextX = allMoves[i][2];
			int nextY = allMoves[i][3];
			chessRules->checkMove(x, y, nextX, nextY);
			bestMove = max(bestMove, minimax(depth - 1, alpha, beta, abs(color - 1)));
			chessRules->undoMove();
			alpha = max(alpha, bestMove);
			if (beta <= alpha) {
				return bestMove;
			}
		}
		return bestMove;
	}
	else {
		double bestMove = 9999;
		for (int i = 0; i < allMoves.size(); i++) {
			int x = allMoves[i][0];
			int y = allMoves[i][1];
			int nextX = allMoves[i][2];
			int nextY = allMoves[i][3];
			chessRules->checkMove(x, y, nextX, nextY);
			bestMove = min(bestMove, minimax(depth - 1, alpha, beta, abs(color - 1)));
			chessRules->undoMove();
			beta = min(beta, bestMove);
			if (beta <= alpha) {
				return bestMove;
			}
		}
		return bestMove;
	}
}

SinglePlayer::SinglePlayer(string Player1Name) :Game(Player1Name, 0) {

}

void SinglePlayer::getWinner() {
	if(colorOfNextMove==player1->getColor()){
		cout << "Computer win!!!" << endl;
	}
	else {
		cout << player1->getName() << " win!!!" << endl;
	}
}

void SinglePlayer::GenereteMove() {
	vector<vector<int>> allMoves = chessRules->genereteMoves(colorOfNextMove);
	srand(time(0));
	int randomNumber = rand() % allMoves.size();
	int x = allMoves[randomNumber][0];
	int y = allMoves[randomNumber][1];
	int nextX = allMoves[randomNumber][2];
	int nextY = allMoves[randomNumber][3];
	chessRules->checkMove(x, y, nextX, nextY);
	chessRules->checkShachMate(colorOfNextMove);
	colorOfNextMove = abs(colorOfNextMove - 1);


}

void SinglePlayer::genereteBestMove() {
	vector<vector<int>> allMoves = chessRules->genereteMoves(colorOfNextMove);
	srand(time(0));
	int  IndexBestMove = rand() % allMoves.size();
	double WhiteSum = -999999, BlackSum = 999999, valueMove = 0;

	for (int i = 0; i < allMoves.size(); i++) {
		int x = allMoves[i][0];
		int y = allMoves[i][1];
		int nextX = allMoves[i][2];
		int nextY = allMoves[i][3];
		chessRules->checkMove(x, y, nextX, nextY);
		if (colorOfNextMove) {
			valueMove = board->evaluateBoard();
			if (valueMove < BlackSum) {
				BlackSum = valueMove;
				IndexBestMove = i;
			}
		}
		else {
			valueMove = board->evaluateBoard();
			if (valueMove > WhiteSum) {
				WhiteSum = valueMove;
				IndexBestMove = i;
			}
		}
		chessRules->undoMove();
	}
	chessRules->checkMove(allMoves[IndexBestMove][0], allMoves[IndexBestMove][1], allMoves[IndexBestMove][2], allMoves[IndexBestMove][3]);
	chessRules->checkShachMate(colorOfNextMove);
	colorOfNextMove = abs(colorOfNextMove - 1);
}

void SinglePlayer::minMaxRoot(int depth) {

	vector<vector<int>> allMoves = chessRules->genereteMoves(colorOfNextMove);
	double bestMove = -9999;
	int  bestMoveIndex;
	for (int i = 0; i < allMoves.size(); i++) {

		int x = allMoves[i][0];
		int y = allMoves[i][1];
		int nextX = allMoves[i][2];
		int nextY = allMoves[i][3];
		chessRules->checkMove(x, y, nextX, nextY);
		double value = minimax(depth - 1, -10000, 10000, abs(colorOfNextMove - 1));
		chessRules->undoMove();
		if (value >= bestMove) {
			bestMove = value;
			bestMoveIndex = i;
		}
	}

	chessRules->checkMove(allMoves[bestMoveIndex][0], allMoves[bestMoveIndex][1], allMoves[bestMoveIndex][2], allMoves[bestMoveIndex][3]);
	chessRules->checkShachMate(colorOfNextMove);
	colorOfNextMove = abs(colorOfNextMove - 1);

}


//Клас мультиплеєр (гра з людиною)

MultiPlayer::MultiPlayer(string Player1Name, string Player2Name, int colorPlayer1) :Game(Player1Name, colorPlayer1) {
	player2 = new Player(Player2Name, abs(colorPlayer1 - 1));
}
MultiPlayer ::~MultiPlayer() {
	delete player2;
}

void MultiPlayer::getWinner() {
	if (colorOfNextMove == player1->getColor()) {
		cout <<player2->getName() <<" win!!!" << endl;
	}
	else {
		cout << player1->getName() << " win!!!" << endl;
	}
}



