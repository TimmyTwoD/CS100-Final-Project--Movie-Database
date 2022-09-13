#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ostream>
#include <cctype>
#include <vector>
using namespace std; 

#include "GetRecommendation.hpp"
#include "MovieList.hpp"
#include "select.hpp"
#include "ContainsSpecs.hpp"
#include "EitherSpec.hpp"
#include "BothSpecs.hpp"

void printMenu();

int main() {
  MovieList movieDatabase;
  string one;
  char user_choice;
  bool valid;

  ifstream inFS("output.txt");

  if (!inFS.is_open()) {
    cout << "The file could not be opened." << endl;
    exit(1);
  }

  string line, title, time, score, tag;
  stringstream inS;
  
  while(inFS.ignore(), getline(inFS, line)) {
    title = "";
    time = "";
    score = "";
    tag = "";
    int i = 0;
      if(line.at(i) == '\"') {
        ++i;
        while((i < line.size()) && !(line.at(i) == '\"')) { // title
          title += line.at(i);
          i++;
        }
        i += 4;
        while((i < line.size()) && !(line.at(i) == '\"')) { // time
          time += line.at(i);
          i++;
        }
        i += 4;
        while((i < line.size()) && !(line.at(i) == '\"')) { // score
          score += line.at(i);
          i++;
        }
        i += 4;
        while((i < line.size()) && !(line.at(i) == '\"')) { // tag
          tag += line.at(i);
          i++;
        }
      }

    movieDatabase.addRow({title, time, score, tag});
  }


  movieDatabase.setColumnNames({"Title", "Time", "Score", "Tags"});

  cout << "Hi. Welcome to the movie database. Please choose an option from the menu." << endl << endl;

  do {
    printMenu();
    getline(cin, one);

    while (one.size() > 1) {
      cout << "'" << one << "'" << " is not a valid option." << endl << endl;
      printMenu();
      cin >> one;
      cin.ignore();
    }

    user_choice = one[0];
    cout << endl;

    switch (user_choice) {
      case 'a' : 
      {  
          string title;

          cout << "ADDING MOVIE" << endl;
          cout << "Input movie title: ";
          getline(cin, title);
          
          // checks if movie title is already in database
          if(movieDatabase.findTitle(title)) 
          {
            cout << "The movie you wish to add already exists in the database." << endl;
          }
          else
          {
            string score, tag, time;
            int score_dec;
            int time_dec;

            cout << "Input score (out of 10) to the movie: ";
            do 
            {
                cin >> score;
                cin.ignore();
                if ((score.size() > 1 && score != "10") || isalpha(score[0])) {
                  cout << "Invalid input, please input a valid score: ";
                }
            }
            while ((score.size() > 1 && score != "10") || isalpha(score[0]));

            do {
              valid = true; 
              cout << "Input tag (only 1) to the movie: ";
              cin >> tag;
              cin.ignore();
              tag.at(0) = toupper(tag.at(0)); 

              if (tag != "Action" && 
                tag != "Adventure" && 
                tag != "Biography" &&
                tag != "Animation" &&
                tag != "Comedy" &&
                tag != "Crime" &&
                tag != "Drama" &&
                tag != "Family" &&
                tag != "Fantasy" &&
                tag != "Film-Noir" &&
                tag != "History" &&
                tag != "Horror" &&
                tag != "Music" &&
                tag != "Musical" &&
                tag != "Mystery" &&
                tag != "Romance" &&
                tag != "Sci-Fi" &&
                tag != "Sport" &&
                tag != "Thriller" &&
                tag != "War" &&
                tag != "Western") {
                cout << "Invalid tag." << endl;  
                valid = false;      
              }
            } while (!valid);

            cout << "Input time watched (in minutes): ";
            valid = true;
            do 
            {
                valid = true;
                cin >> time;
                cin.ignore();
                
                for (int i = 0; (i < time.size()) && valid; i++) {
                  if (!isdigit(time.at(i))) {
                    cout << "Invalid input, please input a valid time: ";
                    valid = false;
                  }
                }
            }
            while (!valid);
            movieDatabase.addRow({title, time, score, tag});
          }
          
          cout << endl;
          break;
      }
      case 'h' : 
      { 
          movieDatabase.set_selection(nullptr);
          movieDatabase.PrintMovieList(cout);

          cout << endl;
          break;    
      }
      case 'r' : 
      { 
          GetRecommendation recommendation;
          recommendation.CallSpecs(movieDatabase);
          break;
      }
      case 'd' : 
      { 
        string title;

        cout << "Enter the name of the movie you wish to see the stats for: ";
        getline(cin, title);

        if (!movieDatabase.findTitle(title)) 
        {
            cout << "The movie you wish to see stats for does not exist in the list. Please select 'a' to add the movie first." << endl;
        }
        else {
          movieDatabase.MovieObjectWriter(title);
          movieDatabase.PrintMovieStats(title);
        }

        break;
      }
      case 'm' :
      {
        string user_c, movie, m;

        do {
          valid = true; 
          cout << "OPTIONS" << endl;
          cout << "0 - Delete the movie" << endl
            << "1 - Delete time" << endl
            << "2 - Delete the score" << endl
            << "3 - Delete the tag" << endl 
            << "4 - Cancel" << endl << endl
            << "Choose an option: ";
          cin >> user_c;
          cin.ignore();

          if (user_c == "0") {
            cout << endl << "DELETING MOVIE" << endl; 
            cout << "Enter the name of the movie you wish to delete: ";
            getline(cin, movie);
            
            do {
              cout << endl << "Movie not found, please input an existing movie: ";
              getline(cin, movie);
            }
            while(!movieDatabase.findTitle(movie));

            movieDatabase.delMovie(movie);
            cout << "Removed " << movie << endl;
          }
          else if (user_c == "1") {
            cout << endl << "DELETING TIME" << endl; 

            do {
              valid = true;
              cout << "Enter the name of the movie you wish to delete time for: ";
              getline(cin, movie);

              if (!movieDatabase.findTitle(movie)) {
                cout << endl << "Movie is not in database." << endl << endl;
                valid = false; 
              }
            } while (!valid);

            movieDatabase.delTime(movie);
            cout << endl << "Time removed for " << movie << endl;
          }
          else if (user_c == "2") {
            cout << endl << "DELETING SCORE" << endl;

            do {
              valid = true;
              cout << "Enter the name of the movie you wish to delete score for: ";
              getline(cin, movie);

              if (!movieDatabase.findTitle(movie)) {
                cout << endl << "Movie is not in database." << endl << endl;
                valid = false; 
              }
            } while (!valid);

            movieDatabase.delScore(movie);
            cout << endl << "Score removed for " << movie << endl;
          }
          else if (user_c == "3") {
            cout << endl << "DELETING TAG" << endl; 

            do {
              valid = true;
              cout << "Enter the name of the movie you wish to delete tag for: ";
              getline(cin, movie);

              if (!movieDatabase.findTitle(movie)) {
                cout << endl << "Movie is not in database." << endl << endl;
                valid = false; 
              }
            } while (!valid);
           
            movieDatabase.delTag(movie);
            cout << endl << "Tag removed for " << movie << endl;
          }
          else if (user_c == "4") {
            cout << endl << "Returning to menu." << endl;
            break; 
          }
          else {
            cout << endl << "Invalid choice." << endl << endl;
            valid = false;
          }
        } while (!valid);

        cout << endl; 
        break;
      }
      case 'e' : 
      {
        string user_c, movie;

        do {
          valid = true; 
          cout << "OPTIONS" << endl;
          cout << "0 - Edit the movie title" << endl
            << "1 - Edit time" << endl
            << "2 - Edit the score" << endl
            << "3 - Edit the tag" << endl
            << "4 - Cancel" << endl << endl
            << "Choose an option: ";
          cin >> user_c;
          cin.ignore();

          string newMovie, newTime, newTag, newScore;

          if (user_c == "0") {
            cout << endl << "EDITING MOVIE TITLE" << endl; 

            do {
              valid = true;
              cout << "Enter the name of the movie title you wish to edit: ";
              getline(cin, movie);

              if (!movieDatabase.findTitle(movie)) {
                cout << endl << "Movie is not in database." << endl << endl;
                valid = false; 
              }
            } while (!valid);

            cout << "Enter the edit you wish to make: ";
            getline(cin, newMovie);

            movieDatabase.editMovie(movie, newMovie);
            cout << endl << movie << " was edited" << endl;
          }
          else if (user_c == "1") {
            cout << endl << "EDITING TIME" << endl; 

            do {
              valid = true;
              cout << "Enter the name of the movie you wish to edit time for: ";
              getline(cin, movie);

              if (!movieDatabase.findTitle(movie)) {
                cout << endl << "Movie is not in database." << endl << endl;
                valid = false; 
              }
            } while (!valid);

            cout << "Enter the edit you wish to make: ";
            getline(cin, newTime);

            movieDatabase.editTime(movie, newTime);
            cout << endl << "Time was edited for " << movie << endl;
          }
          else if (user_c == "2") {
            cout << endl << "EDITING SCORE" << endl;

            do {
              valid = true;
               cout << "Enter the name of the movie you wish to edit score for: ";
              getline(cin, movie);

              if (!movieDatabase.findTitle(movie)) {
                cout << endl << "Movie is not in database." << endl << endl;
                valid = false; 
              }
            } while (!valid);

            cout << "Enter the edit you wish to make: ";
            getline(cin, newScore);

            movieDatabase.editScore(movie, newScore);
            cout << endl << "Score edited for " << movie << endl;
          }
          else if (user_c == "3") {
            cout << endl << "EDITING TAG" << endl; 

             do {
              valid = true;
              cout << "Enter the name of the movie you wish to edit tag for: ";
              getline(cin, movie);

              if (!movieDatabase.findTitle(movie)) {
                cout << endl << "Movie is not in database." << endl << endl;
                valid = false; 
              }
            } while (!valid);

            cout << "Enter the edit you wish to make: ";
            getline(cin, newTag);

            movieDatabase.editTag(movie, newTag);
            cout << endl << "Tag edited for " << movie << endl;
          }
          else if (user_c == "4") {
            cout << endl << "Returning to menu." << endl;
            break;
          }
          else {
            cout << endl << "Invalid choice." << endl << endl; 
            valid = false;
          }
        } while (!valid);

        cout << endl; 
        break;
      }
      case 'q' :
      { 
        break;
      }
      default :
      {
        cout << "'" << user_choice << "'" << " is not a valid option." << endl << endl;
      }
    }
  } while (user_choice != 'q');
  
    ofstream outFS("output.txt");
    
    if (!outFS.is_open()) {
      cout << "The file could not be opened." << endl;
      exit(1);
    }

    movieDatabase.set_selection(nullptr);
    movieDatabase.printToOutput(outFS);
    
    outFS.close();
    
  return 0;
}

//template for menu printing
void printMenu()
{
  cout << "MENU" << endl
    << "a - Add movie to the database" << endl
    << "h - See the history of movies added" << endl
    << "r - Get recommendations" << endl
    << "d - See the stats of a specific movie" << endl
    << "m - Delete history" << endl
    << "e - Edit movie information" << endl
    << "q - Quit" << endl << endl
    << "Choose an option: ";
}



