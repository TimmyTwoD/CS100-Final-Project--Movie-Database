#ifndef MOVIELIST_H
#define MOVIELIST_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Select;

class MovieList {
  protected:
    vector<vector<string> > movieData; // vector of a vector of strings which hold data
  private:
    vector<string> columnNames; // vector of strings that hold column names
    // vector<vector<string> > movieData; // vector of a vector of strings which hold data
    Select *select = nullptr;
    string _time;
    string _tag;
    string _score;
    string _title;
    void convertToUpper(string &) const;

  public:

    ~MovieList();

    /* returns the data at the certain row & column */
    const string& cell_data(int row, int column) const {
      return movieData.at(row).at(column);
    }

    /* isn't this the same as the above fct? */
    string& cell_data(int row, int column) {
      return movieData.at(row).at(column);
    }

    void set_selection(Select* new_select);
    void PrintMovieList(ostream &out) const;
    void printToOutput(ostream &out) const;
    void clear();
    void setColumnNames(const vector<string> &names);
    void addRow(const vector<string> &rowData);
    int getColumnByName(const string &name) const;
    bool findTitle(const string &);
    int RowSetter(const string &);
    void ScoreSetter(const string &, const string &);
    void TagSetter(const string &, const string &);
    void TimeSetter(const string &, const string &);
    string GetTime();
    string GetTag();
    string GetScore();
    string GetTitle();
    MovieList();
    void MovieObjectWriter (const string &);
    void PrintMovieStats (const string &);
    void delMovie(string);
    void delTag(const string &);
    void delTime(const string &);
    void delScore(const string &);
    void editMovie(const string &, const string &);
    void editTag(const string &, const string &);
    void editTime(const string &, const string &);
    void editScore(const string &, const string &);
};

#endif // MOVIELIST_H