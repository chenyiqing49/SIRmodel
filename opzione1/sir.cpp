#include<iostream>
#include<cassert>
#include<vector>

constexpr int N = 1000; //population
constexpr double beta = 0.00035; // probability of infection
constexpr double gamma = 0.12; // probability of recover

struct SIR{
    double susceptible;
    double infectious;
    double recovered;
};

class Epidemy {
private:
    SIR init_;
    int n_day_;

public:
    Epidemy(SIR init, int n_day) : init_{init} , n_day_{n_day} {}
    
    std::vector<SIR> create_model (){
        assert(n_day_ > 0);
        
        std::vector<SIR> result {init_};

        for (int i = 1; i < n_day_; ++i) {
            auto const& prev = result.back();
            SIR s;
            s.susceptible = prev.susceptible - beta * prev.infectious * prev.susceptible;
            s.infectious = prev.infectious + beta * prev.infectious * prev.susceptible - gamma * prev.infectious;
            s.recovered = N - s.susceptible - s.infectious;
            result.push_back(s);
        }
        return result;
    }
};

void print_epidemy (std::vector<SIR> const &epidemy){
    std::cout << "S, I, R\n";
    
    for(auto &i : epidemy){
        std::cout << i.susceptible  << ", "  << i.infectious  << ", "  << i.recovered  << '\n';
    } 
}


int main() {
  SIR s0 {};
  s0.susceptible = N - 100;
  s0.infectious = 100;
  s0.recovered = 0.;
  Epidemy e1 {s0, 210};
  auto e = e1.create_model();
  print_epidemy(e);
}
