#include "MovieList.hpp"
#include <iostream>
#include <vector>
#include "select.hpp"
#include <algorithm>

MovieList::MovieList(){
  _time = "";
  _tag = "";
  _score = "";
  _title = "";
}

MovieList::~MovieList() {
  delete select;
}

void MovieList::set_selection(Select* new_select) {
    delete select;
    select = new_select;
}

void MovieList::setColumnNames(const vector<string> &names) {
  columnNames = names;
}

void MovieList::addRow(const vector<string> &rowData) {
  movieData.push_back(rowData);
}

int MovieList::getColumnByName(const string &name) const {
  for (int i = 0; i < columnNames.size(); ++i) {
    if (columnNames.at(i) == name) {
      return i;
    }
  }
  
  return -1;
}

void MovieList::PrintMovieList(ostream &out) const {
  if (select == nullptr) {
    // print all rows
    for (int i = 0; i < movieData.size(); ++i) {
      for (int j = 0; j < movieData.at(i).size(); ++j) {
        out << movieData.at(i).at(j) << ' ';
      }
      out << endl; 
    }
  }
  else {
    // only print desired rows 
    for (int i = 0; i < movieData.size(); ++i) {
      if (select->select(this, i)) {
        for (int j = 0; j < movieData.at(i).size(); ++j) {
          out << movieData.at(i).at(j) << ' ';
        }

        out << endl; 
      }
    }
  }

}

void MovieList::printToOutput(ostream &out) const {
  if (select == nullptr) {
    // print all rows
    for (int i = 0; i < movieData.size(); ++i) {
      out << "{";
      out << "\""  << movieData.at(i).at(0) << "\"";
      for (int j = 1; j < movieData.at(i).size(); ++j) {
        out << ", \""  << movieData.at(i).at(j) << "\"";
      }
      out << "}";
      out << endl; 
    }
  }
}

bool MovieList::findTitle(const string& movieName) {
  for(int i = 0; i < movieData.size(); ++i)
  {
    for(int j = 0; j < movieData.at(i).size(); ++j)
    {
      // non-case sensitive
      string temp = movieData.at(i).at(j);
      string temp1 = movieName;

      convertToUpper(temp);
      convertToUpper(temp1);
      
      if (temp == temp1)
      {
        return true;
      }
    }
  }
  return false;
}

int MovieList::RowSetter(const string& movieName)
{
  for(int i = 0; i < movieData.size(); ++i)
  {
    for(int j = 0; j < movieData.at(i).size(); ++j)
    {
      // non-case sensitive
      string temp = movieData.at(i).at(j);
      string temp1 = movieName;

      convertToUpper(temp);
      convertToUpper(temp1);
      
      if (temp == temp1)
      {
        return i;
      }
    }
  }
  return 0;
}

void MovieList::ScoreSetter(const string& movieName, const string& score)
{
  for(int i = 0; i < movieData.size(); ++i)
  {
    for(int j = 0; j < movieData.at(i).size(); ++j)
    {
      // non-case sensitive
      string temp = movieData.at(i).at(j);
      string temp1 = movieName;

      convertToUpper(temp);
      convertToUpper(temp1);
      
      if (temp == temp1)
      {
          movieData.at(i).at(2) = score;
      }
    }
  }
}

void MovieList::TagSetter(const string& movieName, const string& tag)
{
  for(int i = 0; i < movieData.size(); ++i)
  {
    for(int j = 0; j < movieData.at(i).size(); ++j)
    {
      // non-case sensitive
      string temp = movieData.at(i).at(j);
      string temp1 = movieName;

      convertToUpper(temp);
      convertToUpper(temp1);
      
      if (temp == temp1)
      {
        movieData.at(i).at(3) = tag;
      }
    }
  }
}

void MovieList::TimeSetter(const string &movieName, const string& time)
{
  for(int i = 0; i < movieData.size(); ++i)
  {
    for(int j = 0; j < movieData.at(i).size(); ++j)
    {
      // non-case sensitive
      string temp = movieData.at(i).at(j);
      string temp1 = movieName;

      convertToUpper(temp);
      convertToUpper(temp1);
      
      if (temp == temp1)
      {
        movieData.at(i).at(1) = time;
      }
    }
  }
}

void MovieList::clear() {
  columnNames.clear();
  movieData.clear();
  delete select;
  select = nullptr;
}

string MovieList::GetTime()
{
  return _time;
}

string MovieList::GetTag()
{
  return _tag;
}

string MovieList::GetScore()
{
  return _score;
}

string MovieList::GetTitle()
{
  return _title;
}

void MovieList::MovieObjectWriter(const string& movieName)
{
  _title = movieName;

  for(int i = 0; i < movieData.size(); ++i)
  {
    for(int j = 0; j < movieData.at(i).size(); ++j)
    {
      // non-case sensitive
      string temp = movieData.at(i).at(j);
      string temp1 = movieName;

      convertToUpper(temp);
      convertToUpper(temp1);
      
      if (temp == temp1)
      {
        _time = movieData.at(i).at(1);
        _score = movieData.at(i).at(2);
        _tag = movieData.at(i).at(3);
      }
    }
  }
}

void MovieList::PrintMovieStats(const string& movieName)
{
  cout << endl << movieName <<endl;
  cout << "You have spent "<< _time <<" minutes watching "<< movieName << "." << endl;
  cout <<"Score: "<< _score << endl;
  cout <<"Related Tags: "<< _tag << endl << endl;
}

// i = row
// j = column
void MovieList::delMovie(string movieName)
{
 for(int i = 0; i < movieData.size(); ++i)
  {
    for(int j = 0; j < movieData.at(i).size(); ++j)
    {
      // non-case sensitive
      string temp = movieData.at(i).at(j);
      string temp1 = movieName;

      convertToUpper(temp);
      convertToUpper(temp1);
      
      if (temp == temp1)
      {
        for(int k = 0; k < movieData.size() - 1; ++k)
        {
          if(k >= i)
          {
            movieData.at(k) = movieData.at(k+1);
          }
        }
      }
    }
  }
  movieData.pop_back();
}

void MovieList::delTag(const string &movieName)
{
 for(int i = 0; i < movieData.size(); ++i)
  {
    for(int j = 0; j < movieData.at(i).size(); ++j)
    {
      // non-case sensitive
      string temp = movieData.at(i).at(j);
      string temp1 = movieName;

      convertToUpper(temp);
      convertToUpper(temp1);
      
      if (temp == temp1)
      {
        movieData.at(i).at(3) = "";
      }
    }
  }
}
void MovieList::delTime(const string &movieName)
{
 for(int i = 0; i < movieData.size(); ++i)
  {
    for(int j = 0; j < movieData.at(i).size(); ++j)
    {
      // non-case sensitive
      string temp = movieData.at(i).at(j);
      string temp1 = movieName;

      convertToUpper(temp);
      convertToUpper(temp1);
      
      if (temp == temp1)
      {
        movieData.at(i).at(1) = "";
      }
    }
  }
}
void MovieList::delScore(const string &movieName)
{
  for(int i = 0; i < movieData.size(); ++i)
  {
    for(int j = 0; j < movieData.at(i).size(); ++j)
    {
      // non-case sensitive
      string temp = movieData.at(i).at(j);
      string temp1 = movieName;

      convertToUpper(temp);
      convertToUpper(temp1);
      
      if (temp == temp1)
      {
        movieData.at(i).at(2) = "";
      }
    }
  }
}

void MovieList::editMovie(const string &movieName, const string& newName)
{
for(int i = 0; i < movieData.size(); ++i)
  {
    for(int j = 0; j < movieData.at(i).size(); ++j)
    {
      // non-case sensitive
      string temp = movieData.at(i).at(j);
      string temp1 = movieName;

      convertToUpper(temp);
      convertToUpper(temp1);
      
      if (temp == temp1)
      {
        movieData.at(i).at(0) = newName;
      }
    }
  }
}
 void MovieList::editTag(const string &movieName, const string &tag)
 {
  for(int i = 0; i < movieData.size(); ++i)
  {
    for(int j = 0; j < movieData.at(i).size(); ++j)
    {
      // non-case sensitive
      string temp = movieData.at(i).at(j);
      string temp1 = movieName;

      convertToUpper(temp);
      convertToUpper(temp1);
      
      if (temp == temp1)
      {
        movieData.at(i).at(3) = tag;
      }
    }
  }
 }

 void MovieList::editTime(const string &movieName, const string &time)
 {
 for(int i = 0; i < movieData.size(); ++i)
  {
    for(int j = 0; j < movieData.at(i).size(); ++j)
    {
      // non-case sensitive
      string temp = movieData.at(i).at(j);
      string temp1 = movieName;

      convertToUpper(temp);
      convertToUpper(temp1);
      
      if (temp == temp1)
      {
        movieData.at(i).at(1) = time;
      }
    }
  }
 }
  void MovieList::editScore(const string &movieName, const string &score)
{
  for(int i = 0; i < movieData.size(); ++i)
  {
    for(int j = 0; j < movieData.at(i).size(); ++j)
    {
      // non-case sensitive
      string temp = movieData.at(i).at(j);
      string temp1 = movieName;

      convertToUpper(temp);
      convertToUpper(temp1);
      
      if (temp == temp1)
      {
        movieData.at(i).at(2) = score;
      }
    }
  }
}

void MovieList::convertToUpper(string &str) const {
  char c;
      
  for (int i = 0; i < str.size(); i++) {
    c = str.at(i);
    str.at(i) = toupper(c);
  }
}