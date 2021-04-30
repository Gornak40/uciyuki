#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

const int INF = 1e9;
const int N = 4;
int board = 0;
int cache[1 << 16];


inline int get_color() {
	return ((__builtin_popcount(board) & 1) ? -1 : 1);
}

inline int get_cell(int row, int col) {
	return (board >> ((row << 2) | col)) & 1;
}

inline void set_cell(int row, int col) {
	board ^= 1 << ((row << 2) | col);
}

inline bool is_game_over() {
	return (
		// rows
		(get_cell(0, 0) + get_cell(0, 1) + get_cell(0, 2) + get_cell(0, 3) == N) || 
		(get_cell(1, 0) + get_cell(1, 1) + get_cell(1, 2) + get_cell(1, 3) == N) || 
		(get_cell(2, 0) + get_cell(2, 1) + get_cell(2, 2) + get_cell(2, 3) == N) || 
		(get_cell(3, 0) + get_cell(3, 1) + get_cell(3, 2) + get_cell(3, 3) == N) || 
		// cols
		(get_cell(0, 0) + get_cell(1, 0) + get_cell(2, 0) + get_cell(3, 0) == N) || 
		(get_cell(0, 1) + get_cell(1, 1) + get_cell(2, 1) + get_cell(3, 1) == N) || 
		(get_cell(0, 2) + get_cell(1, 2) + get_cell(2, 2) + get_cell(3, 2) == N) || 
		(get_cell(0, 3) + get_cell(1, 3) + get_cell(2, 3) + get_cell(3, 3) == N) || 
		// diags
		(get_cell(0, 0) + get_cell(1, 1) + get_cell(2, 2) + get_cell(3, 3) == N) || 
		(get_cell(0, 3) + get_cell(1, 2) + get_cell(2, 1) + get_cell(3, 0) == N)
	);
}

int negamax(int color, int alpha, int beta, bool is_root, int &nodes, int &bestmove) {
	if (!is_root && cache[board]) return cache[board];
	++nodes;
	if (is_game_over()) return cache[board] = 100 - __builtin_popcount(board);
	int cp = -INF;
	for (int row = 0; row < N; ++row) {
		for (int col = 0; col < N; ++col) {
			if (get_cell(row, col)) continue;
			set_cell(row, col);
			int cur = -negamax(-color, -beta, -alpha, false, nodes, bestmove);
			set_cell(row, col);
			if (cur > cp) {
				cp = cur;
				if (is_root) bestmove = (row << 2) | col;
			}
			alpha = max(alpha, cur);
		//	if (alpha >= beta) break;
		}
	}
	return cache[board] = cp;
}

void display() {
	for (int row = 0; row < N; ++row) {
		for (int col = 0; col < N; ++col) {
			cout << (get_cell(row, col) ? 'x' : '-') << ' ';
		}
		cout << endl;
	}
	cout << "is game over: " << is_game_over() << endl;
}

namespace UCI {
	void uci() {
		cout << "id name UCIYuki" << endl;
		cout << "id author Gornak40" << endl;
		cout << "uciok" << endl;
	}

	void isready() {
		cout << "readyok" << endl;
	}

	void ucinewgame() {
		board = 0;
		memset(cache, 0, sizeof(cache));
	}

	void position() {
		string str_moves;
		getline(cin, str_moves);
		stringstream moves(str_moves);
		for (string move; moves >> move;) {
			if (move == "moves") continue;
			if (move == "startpos") board = 0;
			else set_cell(move[0] - '1', move[1] - '1');
		}
		display();
	}

	void go() {
		int color = get_color(), nodes = 0, bestmove;
		int cp = negamax(color, -INF, INF, true, nodes, bestmove) * color;
		cout << "info nodes " << nodes << endl;
		cout << "info score cp " << cp << endl;
		int row = bestmove >> 2;
		int col = bestmove & 3;
		cout << "bestmove " << ++row << ++col << endl;
	}

	void setoption() {
		string options;
		getline(cin, options);
	}

	void start() {
		cout << "UCIYuki by Gornak40" << endl;
		ucinewgame();
		for (string command; cin >> command;) {
			if (command == "uci") {
				uci();
			}
			else if (command == "isready") {
				isready();
			}
			else if (command == "ucinewgame") {
				ucinewgame();
			}
			else if (command == "position") {
				position();
			}
			else if (command == "go") {
				go();
			}
			else if (command == "setoption") {
				setoption();
			}
			else {
				cout << "Unknown option: " << command << endl;
			}
		}
	}
}

int main() {
	UCI::start();
}