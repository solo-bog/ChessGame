#include <iostream>
#include "Chess.h"
using namespace std;



Piece::Piece(int color, int x, int y) :color(color), x(x), y(y) {

}
Piece:: ~Piece() = default;
void Piece::setPositionXY(int x, int y) {
	this->x = x;
	this->y = y;
}

int Piece::getX() {
	return x;
}
int Piece::getY() {
	return y;
}

int Piece::getColor() {
	return color;
}
char Piece::getName() {
	return '*';
}
bool Piece::canMove(int nextX, int nextY, Piece*** board) {
	return false;
}

double Piece::value() {
	return 0;
}


King::King(int color, int x, int y) :Piece(color, x, y) {
	double KingTable[8][8] = { {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0} ,
					{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
					{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0 },
					{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
					{-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0 },
					{-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
					{2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0 },
					{2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0 }
	};
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			this->KingTable[i][j] = KingTable[i][j];
		}
	}
}
char King::getName() {
	if (color) {
		return 'k';
	}
	else {
		return 'K';
	}

}
bool King::canMove(int nextX, int nextY, Piece*** board) {
	bool freeMove = false;
	if ((0 <= abs(x - nextX) && abs(x - nextX) <= 1) && (0 <= abs(y - nextY) && abs(y - nextY) <= 1)) {
		freeMove = true;
	}
	else {
		return false;
	}
	if (board[nextX][nextY] != nullptr) {
		if (board[nextX][nextY]->getColor() == color) {
			return false;
		}
	}
	return freeMove;
}
double King::value() {
	if (color) {
		return -900 - KingTable[7 - x][7 - y];
	}
	else {
		return 900 + KingTable[x][y];
	}
}

Queen::Queen(int color, int x, int y) :Piece(color, x, y) {
	double QueenTable[8][8] = {
	{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
		{-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
		{-1.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
		{-0.5, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
		{0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
		{-1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
		{-1.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, -1.0},
		{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0}
	};
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			this->QueenTable[i][j] = QueenTable[i][j];
		}
	}

}
char Queen::getName() {
	if (color) {
		return 'q';
	}
	else {
		return 'Q';
	}

}

double Queen::value() {
	if (color) {
		return -90 - QueenTable[7 - x][7 - y];
	}
	else {
		return 90 + QueenTable[x][y];
	}
}
bool Queen::canMove(int nextX, int nextY, Piece*** board) {
	bool RookCanMove = false;
	bool BishopCanMove = true;
	if (x == nextX && y == nextY) {
		return false;
	}
	if ((x - y) != (nextX - nextY) && (x + y) != (nextX + nextY)) {
		BishopCanMove = false;
	}

	else {
		if (nextX > x && nextY > y) {
			for (int i = x + 1, j = y + 1; (i < nextX && j < nextY); i++, j++) {
				if (board[i][j] != nullptr) {
					BishopCanMove = false;
				}
			}
		}
		else if (nextX < x && nextY < y) {
			for (int i = x - 1, j = y - 1; (i > nextX && j > nextY); i--, j--) {
				if (board[i][j] != nullptr) {
					BishopCanMove = false;
				}
			}
		}
		else if (nextY > y && nextX < x) {
			for (int i = x - 1, j = y + 1; (i > nextX && j < nextY); i--, j++) {
				if (board[i][j] != nullptr) {
					BishopCanMove = false;
				}
			}
		}
		else if (nextY < y && nextX>x) {
			for (int i = x + 1, j = y - 1; (i < nextX && j > nextY); i++, j--) {
				if (board[i][j] != nullptr) {
					BishopCanMove = false;
				}
			}
		}
	}

	bool freeMove = false;
	bool notObctacle = true;
	if (x == nextX || y == nextY) {
		freeMove = true;
		if (nextX > x) {
			for (int i = x + 1; i < nextX; i++) {
				if (board[i][y] != nullptr) {
					notObctacle = false;
				}
			}
		}
		else if (nextX < x) {
			for (int i = (x)-1; i > nextX; i--) {
				if (board[i][y] != nullptr) {
					notObctacle = false;
				}
			}
		}
		else if (nextY > y) {
			for (int i = (y)+1; i < nextY; i++) {
				if (board[x][i] != nullptr) {
					notObctacle = false;
				}
			}
		}
		else if (nextY < y) {
			for (int i = (y)-1; i > nextY; i--) {
				if (board[x][i] != nullptr) {
					notObctacle = false;
				}
			}
		}
	}


	bool attack = true;
	if (board[nextX][nextY] != nullptr) {
		if (board[nextX][nextY]->getColor() == color) {
			attack = false;
		}
	}
	RookCanMove = freeMove && notObctacle && attack;
	return RookCanMove || (BishopCanMove && attack);

}

char Rook::getName() {
	if (color) {
		return 'r';
	}
	else {
		return 'R';
	}

}

double Rook::value() {
	if (color) {
		return -50 - RookTable[7 - x][7 - y];
	}
	else {
		return 50 + RookTable[x][y];
	}
}


Rook::Rook(int color, int x, int y) :Piece(color, x, y) {
	double RookTable[8][8] = {
	{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,},
		{0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0}
	};
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			this->RookTable[i][j] = RookTable[i][j];

		}
	}
}
bool  Rook::canMove(int nextX, int nextY, Piece*** board) {
	bool freeMove = false;
	if (x == nextX || y == nextY) {
		freeMove = true;
	}
	else {
		return false;
	}
	bool notObctacle = false;
	if (nextX > x) {
		for (int i = x + 1; i < nextX; i++) {
			if (board[i][y] != nullptr) {
				return false;
			}
		}
	}
	else if (nextX < x) {
		for (int i = (x)-1; i > nextX; i--) {
			if (board[i][y] != nullptr) {
				return false;
			}
		}
	}
	else if (nextY > y) {
		for (int i = (y)+1; i < nextY; i++) {
			if (board[x][i] != nullptr) {
				return false;
			}
		}
	}
	else if (nextY < y) {
		for (int i = (y)-1; i > nextY; i--) {
			if (board[x][i] != nullptr) {
				return false;
			}
		}
	}
	notObctacle = true;
	bool attack = true;
	if (board[nextX][nextY] != nullptr) {
		if (board[nextX][nextY]->getColor() == color) {
			attack = false;
		}
	}
	return freeMove && notObctacle&& attack;
}


char Bishop::getName() {
	if (color) {
		return 'b';
	}
	else {
		return 'B';
	}

}

Bishop::Bishop(int color, int x, int y) :Piece(color, x, y) {
	double BishopTable[8][8] = {
{ -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
	{-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
	{-1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0},
	{-1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0},
	{-1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0},
	{-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0},
	{-1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0},
	{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}
	};
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			this->BishopTable[i][j] = BishopTable[i][j];
		}
	}
}

double Bishop::value() {
	if (color) {
		return -30 - BishopTable[7 - x][7 - y];
	}
	else {
		return 30 + BishopTable[x][y];
	}
}

bool Bishop::canMove(int nextX, int nextY, Piece*** board) {
	if ((x - y) != (nextX - nextY) && (x + y) != (nextX + nextY)) {
		return false;
	}
	if (nextX > x && nextY > y) {
		for (int i = x + 1, j = y + 1; (i < nextX && j < nextY); i++, j++) {
			if (board[i][j] != nullptr) {
				return false;
			}
		}
	}
	else if (nextX < x && nextY < y) {
		for (int i = x - 1, j = y - 1; (i > nextX && j > nextY); i--, j--) {
			if (board[i][j] != nullptr) {
				return false;
			}
		}
	}
	else if (nextY > y && nextX < x) {
		for (int i = x - 1, j = y + 1; (i > nextX && j < nextY); i--, j++) {
			if (board[i][j] != nullptr) {
				return false;
			}
		}
	}
	else if (nextY < y && nextX>x) {
		for (int i = x + 1, j = y - 1; (i < nextX && j > nextY); i++, j--) {
			if (board[i][j] != nullptr) {
				return false;
			}
		}
	}
	if (board[nextX][nextY] != nullptr) {
		if (board[nextX][nextY]->getColor() == color) {
			return false;
		}
	}
	return true;
}

char Knight::getName() {
	if (color) {
		return 'n';
	}
	else {
		return 'N';
	}

}

Knight::Knight(int color, int x, int y) :Piece(color, x, y) {
	double KnightTable[8][8] = { {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
{-4.0, -2.0, 0.0, 0.0, 0.0, 0.0, -2.0, -4.0},
{-3.0, 0.0, 1.0, 1.5, 1.5, 1.0, 0.0, -3.0},
{-3.0, 0.5, 1.5, 2.0, 2.0, 1.5, 0.5, -3.0},
{-3.0, 0.0, 1.5, 2.0, 2.0, 1.5, 0.0, -3.0},
{-3.0, 0.5, 1.0, 1.5, 1.5, 1.0, 0.5, -3.0},
{-4.0, -2.0, 0.0, 0.5, 0.5, 0.0, -2.0, -4.0},
{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0} };
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			this->KnightTable[i][j] = KnightTable[i][j];
		}
	}
}
bool Knight::canMove(int nextX, int nextY, Piece*** board) {
	bool freeMove = ((abs(x - nextX) == 2) && (abs(y - nextY) == 1)) || ((abs(x - nextX) == 1) && (abs(y - nextY) == 2));
	if (board[nextX][nextY] != nullptr) {
		if (board[nextX][nextY]->getColor() == color) {
			return false;
		}
	}

	return freeMove;
}

double Knight::value() {
	if (color) {
		return -30 - KnightTable[7 - x][7 - y];
	}
	else {
		return 30 + KnightTable[x][y];
	}
}

Pawn::Pawn(int color, int x, int y) :Piece(color, x, y) {
	double PawnTable[8][8] = { {0,0,0,0,0,0,0,0},
				  {5,5,5,5,5,5,5,5},
					 {1,1,2,3,3,2,1,1},
			  {0.5,0.5,1,2.5,2.5,1,0.5,0.5},
				 {0,0,0,2,2,0,0,0},
				{0.5,-0.5,-1,0,0,-1,-0.5,0.5},
				 {0.5,1,1,-2,-2,1,1,0.5},
				 {0,0,0,0,0,0,0,0} };
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			this->PawnTable[i][j] = PawnTable[i][j];
		}
	}
}
char Pawn::getName() {
	if (color) {
		return 'p';
	}
	else {
		return 'P';
	}

}
double Pawn::value() {
	if (color) {
		return -10 - PawnTable[7 - x][7 - y];
	}
	else {
		return 10 + PawnTable[x][y];
	}
}

bool Pawn::canMove(int nextX, int nextY, Piece*** board) {
	if (color == 1) {
		if (nextX - 1 == x && nextY == y) {
			if (board[nextX][nextY] != nullptr) {
				return false;
			}
			else {
				return true;
			}

		}
		else if (nextX - 2 == x && nextY == y && x == 1) {
			if (board[nextX][nextY] != nullptr || board[nextX - 1][nextY] != nullptr) {
				return false;
			}
			else {
				return true;
			}

		}
		else if (nextX - 1 == x && abs(nextY - y) == 1) {
			if (board[nextX][nextY] != nullptr) {
				if (board[nextX][nextY]->getColor() == color) {
					return false;
				}
				else {
					return true;
				}
			}
			else {
				return false;
			}

		}
		else {
			return false;
		}

	}
	else {
		if (nextX + 1 == x && nextY == y) {
			if (board[nextX][nextY] != nullptr) {
				return false;
			}
			else {
				return  true;
			}

		}
		else if (nextX + 2 == x && nextY == y && x == 6) {
			if (board[nextX][nextY] != nullptr || board[nextX + 1][nextY] != nullptr) {
				return false;
			}
			else {
				return true;
			}

		}
		else if (nextX + 1 == x && abs(nextY - y) == 1) {
			if (board[nextX][nextY] != nullptr) {
				if (board[nextX][nextY]->getColor() == color) {
					return false;
				}
				else {
					return true;
				}
			}
			else {
				return false;
			}

		}
		else {
			return false;
		}
	}

}


Board::Board() {
	board = new Piece * *[8];
	for (int i = 0; i < 8; i++) {
		board[i] = new Piece * [8];
	}
	board[0][0] = new Rook(1, 0, 0);
	board[0][1] = new Knight(1, 0, 1);
	board[0][2] = new Bishop(1, 0, 2);
	board[0][3] = new Queen(1, 0, 3);
	board[0][4] = new King(1, 0, 4);
	board[0][5] = new Bishop(1, 0, 5);
	board[0][6] = new Knight(1, 0, 6);
	board[0][7] = new Rook(1, 0, 7);
	board[7][0] = new Rook(0, 7, 0);
	board[7][1] = new Knight(0, 7, 1);
	board[7][2] = new Bishop(0, 7, 2);
	board[7][3] = new Queen(0, 7, 3);
	board[7][4] = new King(0, 7, 4);
	board[7][5] = new Bishop(0, 7, 5);
	board[7][6] = new Knight(0, 7, 6);
	board[7][7] = new Rook(0, 7, 7);
	for (int j = 0; j < 8; j++) {
		board[1][j] = new Pawn(1, 1, j);
		blackPieces.push_back(board[1][j]);
	}
	for (int j = 0; j < 8; j++) {
		board[6][j] = new Pawn(0, 6, j);
		whitePieces.push_back(board[6][j]);
	}
	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = nullptr;
		}
	}
	for (int i = 0; i < 8; i++) {
		blackPieces.push_back(board[0][i]);
		whitePieces.push_back(board[7][i]);
	}




}

Board:: ~Board() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != nullptr) {
				delete board[i][j];
			}
		}
	}
	for (int j = 0; j < 8; j++) {
		delete[] board[j];
	}
	delete[] board;
}

void Board::movePiece(int x, int y, int nextX, int nextY) {
	if (board[nextX][nextY] != nullptr) {
		this->deletePiece(nextX, nextY);
	}


	board[nextX][nextY] = board[x][y];
	board[x][y] = nullptr;
	board[nextX][nextY]->setPositionXY(nextX, nextY);

}
void Board::deletePiece(int x, int y) {
	if (board[x][y] != nullptr) {
		if (board[x][y]->getColor() == 0) {
			for (int i = 0; i < whitePieces.size(); i++) {
				if (board[x][y] == whitePieces[i]) {
					whitePieces.erase(whitePieces.begin() + i);
					break;
				}
			}
		}
		else {
			for (int i = 0; i < blackPieces.size(); i++) {
				if (board[x][y] == blackPieces[i]) {
					blackPieces.erase(blackPieces.begin() + i);
					break;
				}
			}
		}
		delete board[x][y];
		board[x][y] = nullptr;
	}


}
Piece* Board::createPiece(char name) {
	Piece* newPiece = nullptr;
	if (name == 'p') {
		newPiece = new Pawn(1, -1, -1);

	}
	else if (name == 'P') {

		newPiece = new Pawn(0, -1, -1);

	}
	else if (name == 'K') {
		newPiece = new King(0, -1, -1);
	}
	else if (name == 'k') {
		newPiece = new King(1, -1, -1);
	}
	else if (name == 'N') {
		newPiece = new Knight(0, -1, -1);
	}
	else if (name == 'n') {
		newPiece = new Knight(1, -1, -1);
	}
	else if (name == 'B') {
		newPiece = new Bishop(0, -1, -1);
	}
	else if (name == 'b') {
		newPiece = new Bishop(1, -1, -1);
	}
	else if (name == 'R') {
		newPiece = new Rook(0, -1, -1);
	}
	else if (name == 'r') {
		newPiece = new Rook(1, -1, -1);
	}
	else if (name == 'Q') {
		newPiece = new Queen(0, -1, -1);
	}
	else if (name == 'q') {
		newPiece = new Queen(1, -1, -1);
	}
	return newPiece;
}
void Board::addPiece(char shortNameOfPiece, int x, int y) {
	this->deletePiece(x, y);
	board[x][y] = this->createPiece(shortNameOfPiece);
	board[x][y]->setPositionXY(x, y);
	if (board[x][y]->getColor() == 0) {
		whitePieces.push_back(board[x][y]);
	}
	else {
		blackPieces.push_back(board[x][y]);

	}
}

Piece* Board::getPiece(int x, int y) {
	if (x < 0 || x>7 || y < 0 || y>7) {
		return nullptr;
	}
	return board[x][y];
}

Piece*** Board::getBoard() {
	return board;
}

std::vector<Piece*>* Board::getBlackPieces() {
	return &blackPieces;
}

std::vector<Piece*>* Board::getWhitePieces() {
	return &whitePieces;
}
void Board::replacementPiece(char NameOfNewPiece, int x, int y) {
	Piece* newPiece = this->createPiece(NameOfNewPiece);
	newPiece->setPositionXY(x, y);
	if (board[x][y]->getColor()) {
		for (int i = 0; i < blackPieces.size(); i++) {
			if (blackPieces[i] == board[x][y]) {
				blackPieces[i] = newPiece;
				break;
			}
		}
	}
	else {
		for (int i = 0; i < whitePieces.size(); i++) {
			if (whitePieces[i] == board[x][y]) {
				whitePieces[i] = newPiece;
				break;
			}
		}
	}
	delete board[x][y];
	board[x][y] = newPiece;


}

double Board::evaluateBoard() {
	double result = 0;

	for (int i = 0; i < blackPieces.size(); i++) {
		result = result + blackPieces[i]->value();
	}

	for (int i = 0; i < whitePieces.size(); i++) {
		result = result + whitePieces[i]->value();
	}

	return result;
}

void Board::casting(int x1, int y1, int x2, int y2) {
	if (y2 > y1) {
		this->movePiece(x1, y1, x1, 6);
		this->movePiece(x1, 7, x1, 5);
	}
	else {
		this->movePiece(x1, y1, x1, 2);
		this->movePiece(x1, 0, x1, 3);
	}
}