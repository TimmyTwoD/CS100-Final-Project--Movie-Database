#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <string>

class Select {
public:
  virtual ~Select() = default;

  // Return true if the specified row should be selected.
  virtual bool select(const MovieList* sheet, int row) const = 0;
};

class Select_Column: public Select {
protected:
  int column;
public:
  Select_Column() {}
  Select_Column(const MovieList* sheet, const string& name) {
    column = sheet->getColumnByName(name);
  }

  virtual bool select(const MovieList* sheet, int row) const {
    return select(sheet->cell_data(row, column));
  }

  virtual bool select(string s) const = 0;
};

#endif //__SELECT_HPP__