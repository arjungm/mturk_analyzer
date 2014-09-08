#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <boost/functional/hash.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;

bool check_answer(const string& url, const string& ans)
{
  if(url=="R74AZ5nJ0Bw" && ans=="Yellow")
    return true;
  else if(url=="_4prmWQVXOQ" && ans=="Green")
    return true;
  else if(url=="WMwGQhpxRDE" && ans=="Red")
    return true;
  else
    return false;
}

void tokenize_string(const string& str, const string& delim, vector<string>& tokens)
{
  tokens.clear();
  istringstream input_line(str);
  string token;
  while(getline(input_line, token, delim))
    tokens.push_back(token);
}

struct Worker
{
  typedef boost::shared_ptr<Worker> Ptr;

  string id;

  bool is_gamer;
  bool is_robotics;
  enum ages{ YOUNG_ADULT, ADULT, OLD_ADULT, SENIOR } age;
  enum educations{ HIGHSCHOOL, ASSOCIATES, BACHELORS, PHDMASTERS } education;

  bool is_consistent;
};

struct Response
{
  typedef boost::shared_ptr<Response> Ptr;

  int efficient_rating;
  int elegant_rating;
  int smooth_rating;
  int overall_rating;

  string submitted;
  int time;

  bool control_correct;
};


int main(int argc, char** argv)
{
  unordered_map<string, Worker::Ptr> workers;
  unordered_map<string, Response::Ptr> responses;
  // read data
  ifstream infile("GroupedData.csv");
  string fields_line;
  getline(ifstream, fields_line);

  vector<string> fields;
  tokenize_string( fields_line, ",", fields );

  string data_line;
  while(getline(ifstream, data_line))
  {
    vector<string> entries;
    tokenize_string(data_line, ",", entries);
    assert( fields.size() == entries.size() );
    
    Worker::Ptr new_worker = boost::make_shared<Worker>();
    Response::Ptr new_response = boost::make_shared<Response>();

    for(size_t i=0; i<fields.size(); ++i)
    {
      string control_url="", control_ans="";

      if(fields[i]=="WorkerId")
        new_worker->id = entries[i];
      else if(fields[i]=="SubmitTime")
        new_response.submitted = entries[i];
      else if(fields[i]=="Answer.rating1")
        new_reponse->efficient_rating = stoi(entries[i]);
      else if(fields[i]=="Answer.rating2")
        new_response->elegant_rating = stoi(entries[i]);
      else if(fields[i]=="Answer.rating3")
        new_response->smooth_rating = stoi(entries[i]);
      else if(fields[i]=="Answer.rating4")
        new_response->overall_rating = stoi(entries[i]);
      else if(fields[i]=="Answer.survey_age")
      {
        switch(*(entries[i].rbegin()))
        {
          case '1':
            new_worker->age = Worker::ages::YOUNG_ADULT; break;
          case '2':
            new_worker->age = Worker::ages::ADULT; break;
          case '3':
            new_worker->age = Worker::ages::OLD_ADULT; break;
          case '4':
            new_worker->age = Worker::ages::SENIOR; break;
        }
      }
      else if(fields[i]=="Input.testurl")
      {
        // need answer key
        if(!control_ans.empty())
          new_response->control_correct = check_answer(entries[i], control_ans);
        else
          control_url = entries[i];
      }
      else if(fields[i]=="Answer.colorcube")
      {
        // need answer key
        if(!control_url.empty())
          new_response->control_correct = check_answer(control_url, entries[i]);
        else
          control_ans = entries[i];
      }
      else if(fields[i]=="WorkTimeInSeconds")
        new_response->time = stoi(entries[i]);
    }
  }

  // summarize
  

  return 0;
}
