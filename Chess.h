#pragma once
#include <vector>


class Piece {
protected:
	int x;
	int y;
	int color;






public:
	Piece(int color, int x, int y);
	virtual ~Piece();
	int getX();
	int getY();
	void setPositionXY(int x, int y);
	int getColor();
	virtual char getName();
	virtual bool canMove(int nextX, int nextY, Piece*** board);
	virtual double value();

};

class King : public Piece {
public:
	double KingTable[8][8];
	King(int color, int x, int y);
	char getName()override;
	double value()override;
	bool canMove(int nextX, int nextY, Piece*** board)override;
};

class Queen : public Piece {
public:
	Queen(int color, int x, int y);
	double QueenTable[8][8];
	char getName()override;
	bool canMove(int nextX, int nextY, Piece*** board) override;
	double value()override;
};

class Rook : public Piece {
public:
	double RookTable[8][8];
	char getName()override;
	Rook(int color, int x, int y);
	bool canMove(int nextX, int nextY, Piece*** board)override;
	double value()override;
};

class Bishop : public Piece {
public:
	char getName()override;
	Bishop(int color, int x, int y);
	double BishopTable[8][8];
	bool canMove(int nextX, int nextY, Piece*** board) override;
	double value()override;
};

class Knight : public Piece {
public:
	double KnightTable[8][8];
	char getName() override;
	Knight(int color, int x, int y);
	bool canMove(int nextX, int nextY, Piece*** board) override;
	double value()override;
};

class Pawn : public Piece {
public:
	double PawnTable[8][8];
	Pawn(int color, int x, int y);
	char getName() override;
	bool canMove(int nextX, int nextY, Piece*** board)override;
	double value()override;
};

class Board {
private:
	Piece*** board;
	std::vector<Piece*> blackPieces;
	std::vector<Piece*> whitePieces;



public:
	Board();
	~Board();

	Piece* createPiece(char name);
	void replacementPiece(char NameOfNewPiece, int x, int y);
	void deletePiece(int x, int y);
	void addPiece(char shortNameOfPiece, int x, int y);
	Piece* getPiece(int x, int y);
	void movePiece(int x, int y, int nextX, int nextY);
	Piece*** getBoard();
	std::vector<Piece*>* getBlackPieces();
	std::vector<Piece*>* getWhitePieces();
	double evaluateBoard();
	void casting(int x1, int y1, int x2, int y2);
};
