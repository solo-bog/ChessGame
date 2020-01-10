#ifndef CHESSGAME_H
#define CHESSGAME_H

using namespace std;



class Player
{
public:
	Player(string name, int color);
	string getName();
	int getColor();

private:
	string name;
	int color;
};


class ChessBoard {
private:
	float WIDTH = 650;
    float HEIGTH = 650;
	Board* realBoard;
	sf::RenderWindow* window;
public:
	ChessBoard(Board* board);
	void loadtextures(sf::Texture texture[64]);
	void loadboard(sf::Texture texture[64], sf::RectangleShape rectangle[64], sf::Sprite sprite[64]);
	vector<int>  EnterMove(int color);
	void RefreshBoard();
	void close();
	void waitClose();

};

class Command {
protected:
	int x;
	int y;
	int nextX;
	int nextY;
	Board* board;
public:
	Command(Board* board, int x, int y, int nextX, int nextY);
	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual string getMove();
	int getX();
	int getY();
};

class MakeMove :public Command {
private:
	char deletedPiece;
	bool PawnToQueen;
	bool casting;
public:
	MakeMove(Board* board, int x, int y, int nextX, int nextY);
	void Execute();
	string getMove() override;

	void Undo();

};

class Rules {
private:
	Board* board;
	Piece* whiteKing;
	Piece* blackKing;
	bool GameOver;
	bool Pat;
	vector<Command*> journal;
	Command* command;

public:
	Rules(Board* inputBoard);
	~Rules();
	bool isGameOver();
	vector<Command*>* getJournal();
	void checkMove(int x, int y, int nextX, int nextY);

	void undoMove();
	void checkShachMate(int colorOfNextMove);
	vector<int> checkShach(int color);

	bool canCasting(int x, int y, int nextX, int nextY);


	bool canMoveFromTo(int x, int y, int nextX, int nextY, int color);
	bool checkMate(int color);

	vector<vector<int>> genereteMoves(int color);


};




//Абстрактний клас гра
class Game {
protected:
	Player* player1;
	Board* board;
	int colorOfNextMove;
	Rules* chessRules;
	vector<Command*>* journal;
	ChessBoard* gui;

public:
	Game(string PlayerName, int color);
	~Game();
	virtual void getWinner();
	void showMove();
	bool isGameOver();
	Board* getBoard();
	void Move();
	void showBoard();
	void Undo();
	void close();

};

//Клас одиночна гра(з комп*ютером)
class SinglePlayer : public Game {
private:
	double minimax(int depth, double alpha, double beta, int color);

public:
	SinglePlayer(string Player1Name);
	void getWinner()override;

	void GenereteMove();

	void genereteBestMove();
	void minMaxRoot(int depth);
};

//Клас мультиплеєр (гра з людиною)
class MultiPlayer :public Game {
private:
	Player* player2;
public:
	void getWinner()override;
	MultiPlayer(string Player1Name, string Player2Name, int colorPlayer1);
	~MultiPlayer();
};



#endif // CHESSGAME_H
