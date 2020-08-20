#ifndef SIR_PERSON_HPP
#define SIR_PERSON_HPP

#include <random>

namespace SIR {
enum class State : char { Susceptible, Infectious, Recovered };

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

  void infect() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(7, 14);
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
  return l.getState() != r.getState() && l.getDays() != r.getDays();
}
} // namespace SIR

#endif
