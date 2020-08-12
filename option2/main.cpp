#include<iostream>
#include<vector>
#include<thread>
#include<random>
#include<chrono>
#include<cassert>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(1, 14);
int a = distrib(gen);

enum class State : char {Susceptible, Infectious, Recovered};

class Person {
private:
    int days_;
    State state_;

public:
    Person() : days_{0}, state_{State::Susceptible} {}
    
    State getState() { return state_; }
    int getDays() { return days_; }

    void update() {
        if (state_ == State::Infectious) {
            --days_;
            if (days_ == 0) {
                state_ = State::Recovered;
            }
        }   
    }

    void infect(int const &days) {
        if(state_ == State::Susceptible) {
            days_ = days;
            state_ = State::Infectious;
        }
    }

    bool is_S() const {
        return state_ == State::Susceptible;
    }

    bool is_I() const {
        return state_ == State::Infectious;
    }

    bool is_R() const {
        return state_ == State::Recovered;
    }
};

class Board{
private:
    int n_;
    std::vector<Person> board_;

public:
    Board(int n) : n_{n} , board_(n * n) {}

    auto getPopulation() { return board_; }

    Person operator()(int i, int j) const {
        Person p;
        return (i >= 0 && i < n_ && j >= 0 && j < n_) ? board_[i * n_ + j] : p;
    }

    Person& operator()(int i, int j) {
        assert(i >= 0 && i < n_ && j >= 0 && j < n_);
        return board_[i * n_ + j];
    }

    int size() const {
        return n_;
    }

    void print(){ 
        std::cout << "\033c";
        for(int i = 0; i != n_; ++i){
            for(int j = 0; j != n_; ++j){
                char c;

                if(board_[i * n_ + j].is_S()){
                    c = '-';
                } else if (board_[i * n_ + j].is_I()){
                    c = '+';
                } else if (board_[i * n_ + j].is_R()){
                    c = '*';
                }
                std::cout << c << ' ';
            }
        std::cout << '\n';
        }
    }
};

int neigh_count(Board const& board, int const r, int const c) {
  int result = - static_cast<int>(board(r, c).getState());
  for (int i = r - 1; i != r + 2; ++i) {
    for (int j = c - 1; j != c + 2; ++j) {
      result += static_cast<int>(board(i, j).getState());
    }
  }
  return result;
}

Board evolve(Board const& current){
    int const N = current.size();
    Board next {N};

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
           int const c = neigh_count(current, i, j);
           if(c == 3){
               next(i, j) = current(i, j);
               next(i, j).infect(a);
           } else {
               next(i, j) = current(i, j);
               next(i, j).update();
           }    
        }
    }
    return next;
}


int main(){
    int dim = 50;
    Board board {dim};

    board(5, 4).infect(a);
    board(4, 5).infect(a);
    board(6, 4).infect(a);
    board(6, 5).infect(a);

    for(int i = 0; i != 200; ++i){
        board = evolve(board);
        board.print();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
