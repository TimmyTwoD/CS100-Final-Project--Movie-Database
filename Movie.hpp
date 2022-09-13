#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Movie {
  public:
    Movie() {}
    ~Movie() {} 
    virtual void EditMovieList(string) = 0;

  protected:
    string movieTitle = "";
    string movieTime = 0;
    string movieScore = 0;
    string movieTag = "";
};

#endif // MOVIE_H