#ifndef BOTHSPECS_H
#define BOTHSPECS_H

#include "select.hpp"
#include "MovieList.hpp"

class BothSpecs : public Select {
  private:
    Select* criteria1 = nullptr;
    Select* criteria2 = nullptr;
    
  public:
    BothSpecs() {}

    BothSpecs(Select* input1, Select* input2) {
      criteria1 = input1;
      criteria2 = input2;
    }

    ~BothSpecs() { delete criteria1; delete criteria2; }

    virtual bool select(const MovieList* sheet, int row) const {
      return (criteria1->select(sheet, row)) && (criteria2->select(sheet, row));
    } 
};

#endif