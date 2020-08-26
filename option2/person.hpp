#ifndef SIR_PERSON_HPP
#define SIR_PERSON_HPP

#include <random>
#include <cassert>

namespace SIR {
enum class State { Susceptible, Infectious, Recovered };
constexpr int probabilityToInfect = 50;
assert (probabilityToInfect >= 0 && probabilityToInfect <= 100);

class Person {
private:
  int days_;
  State state_;

public:
  Person() : days_{0}, state_{State::Susceptible} {}

  State getState() const { return state_; }
  int getDays() const { return days_; }

  void update() {
    if (state_ == State::Infectious) {
      --days_;
      if (days_ == 0) {
        state_ = State::Recovered;
      }
    }
  }

  void infect() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(14, 20);
    int days = distrib(gen);
      
    std::uniform_int_distribution<> distrib2(0, 100);
    int chance = distrib2(gen);

    if ((state_ == State::Susceptible)&&(chance <= probabilityToInfect)) {
      days_ = days;
      state_ = State::Infectious;
    }
  }
    void infectSure() {
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> distrib(14, 20);
      int days = distrib(gen);

      if (state_ == State::Susceptible) {
        days_ = days;
        state_ = State::Infectious;
      }
    }

  bool is_S() const { return state_ == State::Susceptible; }

  bool is_I() const { return state_ == State::Infectious; }

  bool is_R() const { return state_ == State::Recovered; }
};

inline bool operator==(Person const &l, Person const &r) {
  return l.getState() == r.getState() && l.getDays() == r.getDays();
}

inline bool operator!=(Person const &l, Person const &r) {
  return !(l.getState() == r.getState() && l.getDays() == r.getDays());
}

} // namespace SIR

#endif
