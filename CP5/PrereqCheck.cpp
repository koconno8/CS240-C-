#include <bits/stdc++.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
bool isCyclicUtil(string dependency, unordered_set<string>& visited, unordered_set<string>& stack);

class PrereqCheck {
	private:
		unordered_map<string, vector<string>> uMap;

	public:
		void add(string key, string value, bool b) {
			if(b) {
				uMap[key].push_back(value);			
			} else {
				uMap[key];			
			}		
		}
		
		unordered_map<string, vector<string>>& returnMap(){
			return uMap;		
		}
		
		void printMap() {
			for (const auto& course_pair : uMap) {
        		const string& course_name = course_pair.first;
        		const vector<string>& prerequisites = course_pair.second;
        		cout << course_name << ": ";
        		for (const auto& prerequisite : prerequisites) {
            	cout << prerequisite << " ";
        		}
        		cout << endl;
    		}		
		}
		
		bool isCyclic() {
			unordered_set<string> visited;
			unordered_set<string> stack;
			
			for(auto& key: uMap){
				string dependency = key.first;
				if(isCyclicUtil(dependency, visited, stack)) {
					return true;				
				}			
			}
			return false;		
		}
		
		bool isCyclicUtil(string dependency, unordered_set<string>& visited, unordered_set<string>& stack) {
			if (stack.count(dependency)) {
      		return true; // Found a cycle
    		}

    		if (visited.count(dependency)) {
      		return false; // Already visited this node and found no cycle
    		}
			
			visited.insert(dependency);
			stack.insert(dependency);
			
			for(auto& course : uMap[dependency]){
				string loop = course;
				if(isCyclicUtil(loop, visited, stack)){
					return true;				
				}			
			}
			
			stack.erase(dependency);
    		return false;	
		}

		void readFile(string filename) {
			regex course_regex("[A-Z]{2,4}_[0-9]{3}");
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
				
				string currentindex;
				while(location >> cmds) {
					wordnum++;
					if(regex_match(cmds, course_regex)) {
						cout << "Valid course name: " << cmds << endl;
						
						if(wordnum == 1){
							currentindex = cmds;
							add(currentindex, cmds, false);			
						} else if(wordnum != 1) {
							add(currentindex, cmds, true);	
							if(isCyclic()){
								cout << "The prerequisite " << cmds << " is creating a cycle" << endl;
								exit(0);			
							}		
						}							
					} else {
						cout << "Invalid course name: " << cmds << endl << "Ending program..." << endl;
						exit(0);				
					}
				}
			}
			myfile.close();
		}
};
int main(){
	PrereqCheck P;
	string prereqfile;
	cin >> prereqfile;
	P.readFile(prereqfile);
	return 1;
}

