//
// Created by qwerty on 06.03.2024.
//


#include "toguz.h"

using namespace std;

Board::Board() {
    sockets.fill(N);
    tuzdeks.fill(-1);
    kaznas.fill(0);
}

Board::Board(std::array<int, 2 * K>& inSocket, std::array<int, 2>& inTuzdek, std::array<int, 2>& inKaznas) {
    sockets = inSocket;
    tuzdeks = inTuzdek;
    kaznas = inKaznas;
}

int Board::getSumOfOtausOfPlayer(const int p) {
    int sum = 0;
    for (int i = p * K; i < K * (1 + p); ++i) {
        sum += sockets[i];
    }
    return sum;
}

int Board::getNumOfOddCells(const int p){
    int sum = 0;
    for (int i = p * K; i < K * (1 + p); ++i) {
        if ((sockets[i] & 1) == 1) sum++;
    }
    return sum;
}

int Board::getNumOfEvenCells(const int p){
    int sum = 0;
    for (int i = p * K; i < K * (1 + p); ++i) {
        if ((sockets[i] & 1) == 0) sum++;
    }
    return sum;
}

float Board::heurestic1(const int p = 0) {
    return (kaznas[p] - kaznas[1 - p]) * 0.9f +
           (getSumOfOtausOfPlayer(p)) * 0.2f +
           (tuzdeks[p]) * 0.8f +
           (tuzdeks[1-p]) * -0.8f +
           (getNumOfOddCells(1-p)) * 0.6f +
           (getNumOfEvenCells(p)) * 0.6f;
}

int Board::playSocket(const int p) {
    if (sockets[p] == 1) {
        sockets[p] = 0;
        sockets[idx(p + 1)] += 1;
        return idx(p + 1);
    }
    int tempSocket = sockets[p];
    sockets[p] = 1;
    for (int i = p + 1; i < p + tempSocket; ++i) {
        int id = idx(i);
        sockets[id] += 1;
    }
    int result = idx(p + tempSocket - 1);
    return result;
}

bool Board::isMovePossible(const bool p) {
    for (int i = p * K; i < K * (1 + p); ++i) {
        if (sockets[i] != 0) {
            return true;
        }
    }
    return false;
}

int Board::atsyrauFunction(const int p) {
    for (int i = 0; i < K * 2 - 1; ++i) {
        kaznas[(int)i/K] += sockets[i];
        sockets[i] = 0;
    }
    return kaznas[p];
}

[[nodiscard]] bool Board::tuzdekPossible(const int s, const int player) const {
    return sockets[s] == 3
           && (s / K == (1 - player)) // opposite side
           && ((s + 1) % K) != 0 // not the last
           && tuzdeks[player] == -1 // not having tuzdek
           && (tuzdeks[1 - player] == -1 || tuzdeks[1 - player] % K != (s % K)); // not symmetrical tuzdek
}

void Board::accountSocket(const int s, const size_t player) {
    if (s / K == (1 - player) // correct side
        && sockets[s] % 2 == 0) { // and even
        kaznas[player] += sockets[s];
        sockets[s] = 0;
    }
    for (auto playerIt = 0; playerIt < 2; ++playerIt) {
        if (tuzdeks[playerIt] != -1) {
            kaznas[playerIt] += sockets[tuzdeks[playerIt]];
            sockets[tuzdeks[playerIt]] = 0;
        }
    }
}

void Board::pli(const int s, const bool tuzdek, const int player) {
    auto target = playSocket(s);
    if (tuzdek) {
        tuzdeks[player] = target;
    }
    accountSocket(target, player);
}

Board Board::rotate() const {
    Board result(*this);
    result.kaznas[0] = kaznas[1];
    result.kaznas[1] = kaznas[0];

    result.tuzdeks[0] = tuzdeks[1];
    result.tuzdeks[1] = tuzdeks[0];

    for (int i = 0; i < K; ++i) {
        result.sockets[i] = sockets[K + i];
        result.sockets[K + i] = sockets[i];
    }
    return result;
}


int Board::idx(const int s) {
    return s % (2 * K);
}

/**

player Bob thinking...
Bob's move: 9 (worst outcome: 23)
1:       4       4       1       0       0      Kazna: 18
0:       0       1       2       0       2      Kazna: 16
        -1-     -2-     -3-     -4-     -5-

 */



//struct moveFrom{
//    int move;
//    int tuzdek;
//    int player;
//};
//
//struct BasePlayer{
//    moveFrom playingLogic(){
//        return
//    }
//};
//
//struct Arena{
//public:
//    Arena(){
//
//    }
//};

ostream &operator<<(ostream &os, const Board &board) {
    for (int player = 1; player >= 0; --player) {
        os << static_cast<int> (player) << ":\t";
        for (int i = 0; i < K; ++i) {
            int idx = player ? (2 * K - i - 1) : i;
            os << " " << static_cast<int> (board.sockets[idx]);
            if (board.tuzdeks[(1-player)] == (idx)) {
                os << "*";
            }
            os << "\t";
        }
        os << "Kazna: " << static_cast<int> (board.kaznas[player]);
        os << endl;
    }
    os << "\t";
    for (auto i = 0; i < K; ++i) {
        os << "-" << (i + 1) << "-\t";
    }
    os << endl;
    return os;
}

int minimax(Board &board, int depth, int player, int &move, bool &tuzdek, bool isAtsyrau = false) {
    if (depth == 0 || board.kaznas[0] > K * N || board.kaznas[1] > K * N) {
        move = -1;
        return board.kaznas[0];
    }
    if (!board.isMovePossible(player)) {
        Board copyBoard(board);
        copyBoard.atsyrauFunction(!player);
        return board.kaznas[0] > K*K ? 10000000 : -1000000;
    }

    int dummyMove;
    bool dummyTuzdek;

    int sign = (player == 0) ? 1 : -1;
    int bestValue = -127 * sign;
    bool played = false;
    for (int i = player * K; i < player * K + K; ++i) {
        Board localBoard(board);
        if (localBoard.sockets[i] == 0) {
            continue;
        }
        played = true;
        auto target = localBoard.playSocket(i);


        int withTuzdek = -127 * sign;
        if (localBoard.tuzdekPossible(target, player)) {
            Board tuzdekBoard(localBoard);
            tuzdekBoard.tuzdeks[player] = target;
            tuzdekBoard.accountSocket(target, player);

            withTuzdek = minimax(tuzdekBoard, depth - 1, 1 - player, dummyMove, dummyTuzdek);
        }

        localBoard.accountSocket(target, player);
        int withoutTuzdek = minimax(localBoard, depth - 1, 1 - player, dummyMove, dummyTuzdek);


        if (sign * withoutTuzdek > sign * bestValue) {
            move = i;
            bestValue = withoutTuzdek;
        }
        if (sign * withTuzdek > sign * bestValue) {
            tuzdek = true;
            move = i;
            bestValue = withTuzdek;
        } else {
            tuzdek = false;
        }
    }

    if (played) {
        return bestValue;
    } else {
        move = -1;
        return board.kaznas[0];
    }
}


int minimaxWithAB(Board &board, int depth, int alpha, int beta, bool player, int &move, bool &tuzdek) {
    if (depth == 0 || board.kaznas[0] > K * N || board.kaznas[1] > K * N) {
        move = -1;
        return board.kaznas[0] - board.kaznas[1];
    }else if (board.kaznas[0] > K * N || board.kaznas[1] > K * N){
        move = -1;
        return 100000000;
    }

    int dummyMove;
    bool dummyTuzdek;

    int bestValue = (player == 0) ? INT_MIN : INT_MAX;
    bool played = false;
    if (!board.isMovePossible(player)) {
        Board copyBoard(board);
        copyBoard.atsyrauFunction(!player);
        return board.kaznas[0] > K*K ? 10000000 : -1000000;
    }
    for (int i = player * K; i < player * K + K; ++i) {
        if (board.sockets[i] == 0) continue;
        played = true;
        Board localBoard(board);
        auto target = localBoard.playSocket(i);
        bool isTuzdekPossible = localBoard.tuzdekPossible(target, player);

        int value = INT_MIN;
        if (isTuzdekPossible) {
            Board tuzdekBoard(localBoard);
            tuzdekBoard.tuzdeks[player] = target;
            tuzdekBoard.accountSocket(target, player);

            value = minimaxWithAB(tuzdekBoard, depth - 1, alpha, beta, !player, dummyMove, dummyTuzdek);
        } else {
            localBoard.accountSocket(target, player);
            value = minimaxWithAB(localBoard, depth - 1, alpha, beta, !player, dummyMove, dummyTuzdek);
        }

        if (player == 0 && value > bestValue) {  // Maximizing player
            bestValue = value;
            move = i;
            tuzdek = isTuzdekPossible;
            alpha = std::max(alpha, bestValue);
        } else if (player == 1 && value < bestValue) {  // Minimizing player
            bestValue = value;
            move = i;
            tuzdek = isTuzdekPossible;
            beta = std::min(beta, bestValue);
        }
        if (beta <= alpha) break;  // Alpha-beta pruning
    }

    if (played) {
        return bestValue;
    } else {
        move = -1;
        return board.kaznas[0];
    }
}


void busy(const string name) {
    cout << "player " << name << " thinking..." << endl;
    // cout.flush();
}

void unbusy() {
    //    cout << "Freeing the board...";
    //    cout.flush();
}

void withoutAB(const int d1, const int d2) {
    Board board;
    int move;
    bool tuzdek;

    int move2;
    bool tuzdek2;

//    char answer;
//    cout << "Do you want to begin (Y/N)? ";
//    cin >> answer;
//    bool firstComp = (answer != 'Y');

    bool atsyrauFor1 = false;
    bool atsyrauFor2 = false;

    while (true) {
        if (board.isMovePossible(0)) {
            busy("Alice");
            minimax(board, d1, 0, move, tuzdek);
            cout << "MOVE:\t" << move << " Tuzdek\t" << board.tuzdeks[0] << endl;
            board.pli(move, tuzdek, 0);
            if (atsyrauFor1) {
                atsyrauFor1 = false;
            }
        } else {
            if (!atsyrauFor1) {
                atsyrauFor1 = true;
            } else {
                board.atsyrauFunction(1);
                cout << board.rotate();
                break;
            }
        }

        cout << board.rotate() << endl;

        if (board.kaznas[1] > K * N) {
            cout << "p2 win." << endl;
            break;
        } else if (board.kaznas[0] > K * N) {
            cout << "p1 win." << endl;
            break;
        }


        if (board.isMovePossible(1)) {
            busy("Bob");
            int value = minimax(board, d2, 1, move2, tuzdek2);
            if (move == -1) {
                cout << "Game ended." << endl;
                // TODO determine winner from kaznas
                break;
            }
            cout << "MOVE2:\t" << move2 << " Tuzdek\t" << board.tuzdeks[1] << endl;
            board.pli(move2, tuzdek2, 1);
            // cout << "Opponent's move: " << (static_cast<int> (move) + 1) << " (worst outcome: " << value << ")" << endl;
            if (atsyrauFor2) {
                atsyrauFor2 = false;
            }
        } else {
            if (!atsyrauFor2) {
                atsyrauFor2 = true;
            } else {
                board.atsyrauFunction(0);
                cout << board.rotate();
                break;
            }
        }

        cout << board.rotate() << endl;
    }
}

