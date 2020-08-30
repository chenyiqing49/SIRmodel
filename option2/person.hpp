#ifndef SIR_PERSON_HPP
#define SIR_PERSON_HPP

#include "random.cpp"
#include <cassert>

namespace SIR {
enum class State { Susceptible, Infectious, Recovered };

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
    constexpr int probabilityToInfect = 100;
    static_assert(probabilityToInfect > 0,
                  "Probability <= 0");
    static_assert(probabilityToInfect <= 100, "Probability > 100%");

    int days = generateRandom(14, 20);
    int chance = generateRandom(1, 100);

    if (state_ == State::Susceptible && chance <= probabilityToInfect) {
      days_ = days;
      state_ = State::Infectious;
    }
  }

  void infectSure() {
    int days = generateRandom(14, 20);

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
