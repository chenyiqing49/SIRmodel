#ifndef SIR_H_INCLUDED
#define SIR_H_INCLUDED

#include <vector>

struct SIR {
  double susceptible;
  double infectious;
  double recovered;
};

class Epidemy {
private:
  SIR init_;
  int n_day_;

public:
  Epidemy(SIR init, int n_day) : init_{init}, n_day_{n_day} { }
  
  // declarations of the member functions
  SIR getInit();
  int getNday();
  
  std::vector<SIR> create_model(double const &beta, double const &gamma, int const &N);
};

#endif
