#include <bits/stdc++.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include "PrereqCheck.cpp"

using namespace std;

void printPMap();
void printMap();
bool canTake();
bool compareChrono();
vector<string> sort_seasons(vector<string> seasons);
bool canTakeUtil(string course, unordered_set<string>& totake, unordered_set<string>& taken, const unordered_map<string, vector<string>>& uMap);
void readFile(string filename);


class ScheduleCheck {
	private:
		unordered_map<string, unordered_map<string, vector<string>>> splan;
		unordered_map<string, vector<string>> courses;
		unordered_set<string> visited;
		PrereqCheck test;
		
	public:
		ScheduleCheck(string prereq) {
			test = PrereqCheck();
			test.readFile(prereq);
		}
		
		void printPMap() {
			test.printMap();		
		}
		
		void reset() {
			courses.clear();
			splan.clear();	
			visited.clear();	
		}

		void printMap(){
			for (const auto& year_course : splan) {
        		const string& year = year_course.first;
				const unordered_map<string, vector<string>>& terms = year_course.second;         		
        		cout << year << ":\n";
        		for(const auto& term : terms) {
					const string& season = term.first;
					const vector<string>& courses = term.second;
					cout << season << "| ";
					for(const auto& course : courses) {
						cout << course << " ";
					}
					cout << endl;
        		}
        		cout << endl;
    		}
		}		
		
		void canTake() {			
			compareChrono();
		}
		
		void compareChrono() {
			vector<string> years;
			for(auto& year : splan) {
				string y = year.first;
				//cout << y << endl;			
				years.push_back(y);
			}
			for(int i = 0; i < (int)(years.size()); i++) {
				int pos = i;				
				for(int j = i+1; j < (int)(years.size()); j++) {
					if(years[j].compare(years[i]) < 0) {
						pos = j;				
					}
				}
				if(pos != i){
					string temp = years[i];
					years[i] = years[pos];
					years[pos] = temp;				
				}
			}
			
			unordered_set<string> totake;
			unordered_set<string> taken;
			for(int i = 0; i < (int)(years.size()); i++) {
				vector<string> inOrder;
				for(auto& maps: splan[years.at(i)]) {
					const string& temp = maps.first.substr(4);
					//cout << temp << endl;				
					inOrder.push_back(temp);
				}
				vector<string> sorted_seasons = sort_seasons(inOrder);
				for(string zz: sorted_seasons){
					//cout << zz << endl;				
				}

				for(int m = 0; m < (int)(sorted_seasons.size()); m++) {
					//cout << sorted_seasons.size() << endl << m << endl;					
					string season = sorted_seasons.at(m);
					string s = years.at(i)+season;
					//cout << s << endl;
					//cout << m <<endl;
					if(season.compare("Spring") == 0) {
						for(auto& C : splan[years.at(i)][s]){
							const string& c = C;
							//cout << c << " " << "Spring" << endl;
							//cout << canTakeUtil(c, totake, taken, test.returnMap()) << endl;
							//return canTakeUtil(c, totake, taken, test.returnMap());
							//cout << "Spring"<<endl;
							if(!canTakeUtil(c, totake, taken, test.returnMap())) {
								cout << "Your semester: " << s << " is an invalid plan\nEnding program...";
								exit(0);
							}
						}
					} else if(season.compare("Summer") == 0) {
						for(auto& C : splan[years.at(i)][s]){
							const string& c = C;
							//cout << c << " " << "Summer" << endl;
							//cout << canTakeUtil(c, totake, taken, test.returnMap()) << endl;
							//canTakeUtil(c, totake, taken, test.returnMap());
							if(!canTakeUtil(c, totake, taken, test.returnMap())) {
								cout << "Your semester: " << s << " is an invalid plan\nEnding program...";
								exit(0);
							}
						}
					} else {
						for(auto& C : splan[years.at(i)][s]){
							const string& c = C;
							//cout << c << " " << "Fall" << " ";
							//cout << canTakeUtil(c, totake, taken, test.returnMap()) << endl;
							//canTakeUtil(c, totake, taken, test.returnMap());
							if(!canTakeUtil(c, totake, taken, test.returnMap())) {
								cout << "Your semester: " << s << " is an invalid plan\nEnding program...";
								exit(0);
							}
						}
					}
				}
			}
			//return true;
		}
		
		vector<string> sort_seasons(vector<string> seasons) {
    		vector<string> sorted_seasons;
    		int n = seasons.size();

    		int i = 0;
    		int j = n - 1;
    		int k = 0;

    		while (k <= j) {
        		if (seasons[k] == "Spring") {
            	swap(seasons[i], seasons[k]);
            	i++;
            	k++;
        		} else if (seasons[k] == "Summer") {
            	k++;
        		} else if (seasons[k] == "Fall") {
            	swap(seasons[k], seasons[j]);
            	j--;
        		}
    		}
    		return seasons;
		}

		bool canTakeUtil(string course, unordered_set<string>& totake, unordered_set<string>& taken, const unordered_map<string, vector<string>>& uMap) {		

			if (taken.count(course)) {
        		return true;
    		}

    		if (totake.count(course)) {
        		totake.erase(course);
        		return false;
    		}

    		taken.insert(course);

			if(uMap.find(course) == uMap.end()) {
				cout << "Course: " << course << " is not in the prerequisites" << endl;				
				return false;		    
		   }
		    
		    if (uMap.at(course).size() == 0) {
      		  return true;
		    }

		    for (auto& uc : uMap.at(course)) {
      		string u = uc;
        		totake.insert(u);
        		if (!canTakeUtil(u, totake, taken, uMap)) {
            		// If the prerequisite cannot be taken, remove it from the set of courses to take and return false.
            		totake.erase(u);
            		return false;
        		}
    		}
    		//taken.erase(course);
    		return true;

			/*if(taken.count(course)) {
				return true;			
			}
			cout << course << endl;
			if(totake.count(course)) {
				totake.erase(course);				
				return false;			
			}
			
			taken.insert(course);
			
			if(uMap.at(course).size() == 0) {
				return true;			
			}			
			
			for(auto& uc : uMap.at(course)) {
				string u = uc;
				cout << "This is recurive: ";				
				cout << u << endl;
				totake.insert(u);
				if(canTakeUtil(u, totake, taken, uMap)) {
					return true;				
				}
				taken.erase(course);
				return false;			
			}
			
			//taken.erase(course);
			return false;*/
		}
		
		void readFile(string filename) {			
			regex course_regex("[A-Z]{2,4}_[0-9]{3}");
			regex time_regex("\\d{4}(Spring|Summer|Fall)");
			
	  		ifstream myfile(filename);
	
	  		if (!myfile.is_open()) {
  		  		cout << "Failed to open file: " << filename << endl;
  		  		return;
  			}
			
			string line;
			
			int linenum, wordnum = 0;			
			
			while(getline(myfile, line)) {
				linenum++;
				wordnum = 0;
				stringstream location(line);
				string cmds;
				
				string coursename;
				string year;
				//string term;
				string combined;
				while(location >> cmds) {
					wordnum++;
					if(wordnum == 1) {
						coursename = cmds;
						if(visited.count(coursename)) {
							cout << "Already added course: " << coursename << endl << "Ending program..." << endl;
							exit(0);
						} else {
							visited.insert(coursename);						
						}
					} else if (wordnum == 2) {
						combined = cmds;						
						year = cmds.substr(0, 4);
						//term = cmds.substr(4);
					} else {
						cout << "Too many arguments" << endl;
						break;					
					}
				}
				if(regex_match(coursename, course_regex)) {				
					if(regex_match(combined, time_regex)) {
						courses[combined].push_back(coursename);
						//cout << year << term << ": " << coursename << " ";
						if(courses[combined].size() > 3) {
							//cout << courses[term].at(0) << courses[term].at(1) << courses[term].at(2) << endl;
							cout << "Too many courses for the term: " << combined << endl << "Ending program..." << endl;
							exit(0);	
						}
						//splan[year][year+term] = courses[year+term];
						splan[year][combined] = courses[combined];
					} else {
						cout << "Invalid term name: " << combined << endl << "Ending program..." << endl;
						exit(0);				
					}
				} else {
					cout << "Invalid course name: " << coursename << endl << "Ending program..." << endl;
					exit(0);			
				}
			}
			canTake();
			cout << "Your course plan seems to be good!\n";
			//if(canTake()) {
				//cout << "Student can take the classes they are choosing" << endl;
			//} else {
				//cout << "Prerequisites not satisfied.\nEnding program...\n";
				//exit(0);	
			//}
			myfile.close();
		}
};