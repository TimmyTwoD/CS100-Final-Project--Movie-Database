#ifndef GETRECOMMENDATION_H
#define GETRECOMMENDATION_H

#include "MovieList.hpp"
#include "select.hpp"
// BUILDER CLASS

class GetRecommendation : public MovieList {
  private:
    string time;
    string score;
    vector<string> tags;
  public:
    void CallSpecs(MovieList&);
  private:
    void Recommendation(const string&, const string&, const vector<string>&, MovieList &movieDatabase);
    string GetSpecs(vector<string>&, MovieList&);
    bool CheckDuplicates(vector<string>&, string) const; 
    void convertToUpper(string &) const;
};

#endif // GETRECOMMENDATION_H