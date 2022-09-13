#ifndef CONTAINSSPECS_HPP
#define CONTAINSSPECS_HPP

#include "select.hpp"
#include "MovieList.hpp"

class ContainsSpecs : public Select_Column {
  private:
    int column;
    string input;
    
  public:
    ContainsSpecs() {}
    ContainsSpecs(MovieList *sheet, const string &columnName, const string &inputToSearchFor) {
      column = sheet->getColumnByName(columnName); 
      input = inputToSearchFor;
    }
        
    virtual bool select(const MovieList *sheet, int row) const {
      return select(sheet->cell_data(row, column));
    } 

    virtual bool select(string s) const {
      char c;
        
      for (int i = 0; i < s.size(); i++) {
        c = s.at(i);
        s.at(i) = toupper(c);
      }
      return s.find(input) != string::npos;
    } 
};

#endif