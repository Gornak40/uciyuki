#include <iostream>
#include <sstream>

using namespace std;

int board = 0;
const int N = 4;

inline int get_cell(int row, int col) {
	return (board >> ((row << 2) | col)) & 1;
}

inline void set_cell(int row, int col) {
	board ^= 1 << ((row << 2) | col);
}

inline bool is_game_over() {
	for (int row = 0; row < N; ++row) {
		int row_sum = 0, col_sum = 0;
		for (int col = 0; col < N; ++col) {
			row_sum += get_cell(row, col);
			col_sum += get_cell(col, row);
		}
		if (row_sum == N || col_sum == N)
			return true;
	}
	int main_diag = 0, rev_diag = 0;
	for (int row = 0; row < N; ++row) {
		main_diag += get_cell(row, row);
		rev_diag += get_cell(row, N - row - 1);
	}
	return (main_diag == N || rev_diag == N);
}

void display() {
	for (int row = 0; row < N; ++row) {
		for (int col = 0; col < N; ++col) {
			cout << (get_cell(row, col) ? 'x' : '-') << ' ';
		}
		cout << endl;
	}
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
		string times;
		getline(cin, times);
	}

	void setoption() {
		string options;
		getline(cin, options);
	}

	void start() {
		cout << "UCIYuki by Gornak40" << endl;
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