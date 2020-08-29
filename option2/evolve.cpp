// this function count how many rows and columns the (r, c) cell has in his neighborhood
int neigh_count(SIR::Board const &board, int const r, int const c) {
  int result = -static_cast<int>(board(r, c).getState());
  for (int i = r - 1; i != r + 2; ++i) {
    for (int j = c - 1; j != c + 2; ++j) {
      result += static_cast<int>(board(i, j).getState());
    }
  }
  return result;
}

// this function tells the board how to evolve
SIR::Board evolve(SIR::Board const &current) {
  int const N = current.size();
  SIR::Board next{N};

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      int const c = neigh_count(current, i, j);
      if (c == 3) {
        next(i, j) = current(i, j);
        next(i, j).infect();
      } else {
        next(i, j) = current(i, j);
        next(i, j).update();
      }
    }
  }
  return next;
}
