#include "GetRecommendation.hpp"
#include "MovieList.hpp"
#include "select.hpp"

#include "ContainsSpecs.hpp"
#include "EitherSpec.hpp"
#include "BothSpecs.hpp"

#include <cstring>

void GetRecommendation::CallSpecs(MovieList &movieDatabase) {
  vector<string> specs;
  string specChoice;
  int spec_count = 0;
  string user_choice;

  do {
    specChoice = GetSpecs(specs, movieDatabase);
    specs.push_back(specChoice);
    ++spec_count;

    if (spec_count != 3) {
      cout << "If you want to add another spec, press any key. Otherwise press 'q': ";
      cin >> user_choice;
      if (user_choice == "q") {
        Recommendation(time, score, tags, movieDatabase);
        break;
      }
    }

  } while (spec_count != 3 || user_choice != "q");

  if (user_choice != "q") {
    Recommendation(time, score, tags, movieDatabase);
  }

  cout << endl; 
}

// function outputs recommendation to the user
// use select classes 

void GetRecommendation::Recommendation(const string &movieTime, const string &movieScore, const vector<string> &movieTags, MovieList &movieDatabase) { 
    ContainsSpecs* time_spec = nullptr;
    ContainsSpecs* score_spec = nullptr;
    ContainsSpecs* tag_spec = nullptr;
    Select* allTags = nullptr;
    Select* allSpecs = nullptr;
    
  if (movieTime.size() != 0) {
    time_spec = new ContainsSpecs(&movieDatabase, "Time", movieTime);
    allSpecs = time_spec;
  }
 
  if (movieScore.size() != 0) {
    score_spec = new ContainsSpecs(&movieDatabase, "Score", movieScore);

    if (allSpecs == nullptr) {
      allSpecs = score_spec;
    }
    else {
      allSpecs = new BothSpecs(allSpecs, score_spec);
    }
  }
  
  if (movieTags.size() != 0) {
    EitherSpec* either_spec = nullptr;
    
    allTags = new ContainsSpecs(&movieDatabase, "Tags",  movieTags.at(0));
    for (int i = 1; i < movieTags.size(); ++i) {
      tag_spec = new ContainsSpecs(&movieDatabase, "Tags",  movieTags.at(i));
      allTags = new EitherSpec(allTags, tag_spec);
    }
    
    if (allSpecs == nullptr) {
      allSpecs = allTags;
    }
    else {
      allSpecs = new BothSpecs(allSpecs, allTags);
    }
  }

  movieDatabase.set_selection(allSpecs);
  cout << endl << "RECOMMENDATIONS" << endl;
  movieDatabase.PrintMovieList(cout);
  cin.clear();
  cin.ignore(256, '\n');
}

string GetRecommendation::GetSpecs(vector<string>& specs, MovieList &movieDatabase) {
  string user_choice;
  bool inSpecs;
  string movieTime = "";
  string movieScore = ""; 
  vector<string> movieTags;

  do {
    cout << "Choose a spec to base your recommendation off of (Time, Score, Tag): ";
    cin >> user_choice;
    user_choice.at(0) = toupper(user_choice.at(0));
    char c;
      
    convertToUpper(user_choice);
      
    inSpecs = CheckDuplicates(specs, user_choice);
    while (inSpecs == true && specs.size() != 3) {
      cout << "Spec already chosen. Please choose another criteria: ";
      cin >> user_choice;
      convertToUpper(user_choice);
      inSpecs = CheckDuplicates(specs, user_choice);
    }

    if (user_choice == "TIME") {
      cout << "Enter a time: ";

      bool valid = true;
      do 
      {
        valid = true;
        cin >> movieTime;
        cin.ignore();
        for (int i = 0; (i < movieTime.size()) && valid; i++) {
          if(!isdigit(movieTime.at(i))) {
            cout << "Invalid input, please input a valid time: ";
            valid = false;
          }
        }
      } while(!valid);

      time = movieTime; 
      break;
    }
    else if (user_choice == "SCORE") {
      cout << "Enter a score (whole number): ";

      do {
          cin >> movieScore;
          // cin.ignore();
          if ((movieScore.size() > 1 && movieScore != "10") || isalpha(movieScore[0])) {
            cout << "Invalid input, please input a valid score: ";
          }
              
             
      } while ((movieScore.size() > 1 && movieScore != "10") || isalpha(movieScore[0]));

      score = movieScore;
      cin.ignore(); 

      break;
    }
    else if (user_choice == "TAG") {
      int numTags;
      int counter = 0;
      string movieTag;
      bool CheckTag; 

      cout << "How many tags would you like to add (1-3): ";
      cin >> numTags;
      cin.ignore();

      while (numTags <= 0 || numTags > 3) {
        cout << "Invalid number of tags. Please re-enter: ";
        cin >> numTags;
        cin.ignore();
      }

      while (counter < numTags) {
        cout << "Enter a tag: ";
        cin >> movieTag;
        ++counter;
        convertToUpper(movieTag);

        CheckTag = CheckDuplicates(movieTags, movieTag);
        while (CheckTag == true) {
          cout << "Tag already chosen. Please choose another criteria: ";
          cin >> movieTag;
          convertToUpper(movieTag);
          CheckTag = CheckDuplicates(movieTags, movieTag);
        }

        movieTags.push_back(movieTag);
      }
      // cout << movieTags[0] << endl;
      tags = movieTags;

      break;
    }
    else {
      cout << "The spec you entered is not valid. Please re-enter." << endl; 
      }
    } while (user_choice != "TIME" || user_choice != "SCORE" || user_choice != "TAG" || specs.size() != 3);


    return user_choice;
}

bool GetRecommendation::CheckDuplicates(vector<string>& specs, string choice) const {
  for (int i = 0; i < specs.size(); ++i) {
    if (specs.at(i) == choice) {
      // spec is in vector
      return true; 
    }
  }

  // spec is not in vector
  return false; 
}

void GetRecommendation::convertToUpper(string &choice) const {
  char c;
      
  for (int i = 0; i < choice.size(); i++) {
    c = choice.at(i);
    choice.at(i) = toupper(c);
  }
}

