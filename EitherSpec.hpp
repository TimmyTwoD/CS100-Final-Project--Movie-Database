#ifndef EITHERSPEC_H
#define EITHERSPEC_H

#include "select.hpp"
#include "MovieList.hpp"

class EitherSpec : public Select {
  private:
    Select* criteria1 = nullptr;
    Select* criteria2 = nullptr;

  public:
    EitherSpec() {}

    EitherSpec(Select* input1, Select* input2) {
      criteria1 = input1;
      criteria2 = input2;
    }   

    ~EitherSpec() { delete criteria1; delete criteria2; }

    virtual bool select(const MovieList* sheet, int row) const {
      return (criteria1->select(sheet, row)) || (criteria2->select(sheet, row));
    } 
};

#endif