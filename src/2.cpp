/**
 * Benjamin Michael Taylor
 * 2022
 */

#include <fstream>
#include <iostream>
#include <map>
#include <set>

enum Move { rock = 1, paper = 2, scissors = 3 };
enum WinState { lost = 0, draw = 3, won = 6 };

const std::map<char, Move> OPPONENT_MOVES {{'A', Move::rock},
                                           {'B', Move::paper},
                                           {'C', Move::scissors}};

const std::map<char, WinState> WIN_STATES {{'X', WinState::lost},
                                           {'Y', WinState::draw},
                                           {'Z', WinState::won}};

WinState player_win_state(Move player_move, Move opponent_move)
{
    if (player_move == opponent_move) {
        return WinState::draw;
    }

    std::set<Move> moves;
    moves.insert(player_move);
    moves.insert(opponent_move);

    WinState win_state;
    if (moves.contains(Move::rock) && moves.contains(Move::scissors)) {
        if (player_move < opponent_move) {
            win_state = WinState::won;
        }
        else {
            win_state = WinState::lost;
        }
    }
    else {
        if (player_move > opponent_move) {
            win_state = WinState::won;
        }
        else {
            win_state = WinState::lost;
        }
    }
    return win_state;
}

Move what_move(Move opponent_move, WinState win_state)
{
    if (win_state == WinState::draw) {
        return opponent_move;
    }

    int player_move;

    if (win_state == WinState::won) {
        player_move = opponent_move + 1;
        if (player_move > 3) {
            player_move = 1;
        }
    } else {
        player_move = opponent_move - 1;
        if (player_move < 1) {
            player_move = 3;
        }
    }

    return (Move)player_move;
}

int main(int argc, char * argv[])
{
    std::ifstream file(INPUT_FILENAME);
    std::string line;

    int sum = 0;

    while (std::getline(file, line)) {
        Move opponent_move = OPPONENT_MOVES.at(line.at(0));
        WinState win_state = WIN_STATES.at(line.at(2));

        Move player_move = what_move(opponent_move, win_state);

        sum += (int) win_state + (int) player_move;
    }

    printf("%d\n", sum);
    return EXIT_SUCCESS;
}