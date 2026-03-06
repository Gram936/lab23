#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &name ,vector<int> &score ,vector<char> &grade){
    string textline;
    ifstream file;
    file.open(filename);
    char nameP[100];
    int s1,s2,s3;
    int t;
     while (getline(file,textline)){
          char formate[] = "%[^:]: %d %d %d";
          sscanf(textline.c_str(),formate,&nameP,&s1,&s2,&s3);
          name.push_back(nameP);
          t = s1+s2+s3;
          score.push_back(t);
          grade.push_back(score2grade(t));
     }
     file.close();

}

void getCommand(string &command, string &key){
    string line;
    cout << "Please input your command:"<<endl;
    getline(cin, line);
    char cmd[100], k[100];
    char formate[] = "%s %[^\n]";
    sscanf(line.c_str(),formate,cmd,k);
    command = cmd;
    key = k;
}

void searchName(vector <string> name,vector<int> score,vector<char>grade,string key){
    int i =0;
    bool noname = true;
    for( i = 0; i < (int)name.size();i++){
        if(toUpperStr(key) ==toUpperStr(name[i])){
            cout <<"---------------------------------"<<endl;
             cout << name[i]<<"'s score = "<<score[i]<<endl;
             cout << name[i]<<"'s grade = "<<grade[i]<<endl;
             cout <<"---------------------------------"<<endl;
             noname = false;
        }
    }
    if(noname){
         cout <<"---------------------------------"<<endl;
        cout << "Cannot found."<<endl;
         cout <<"---------------------------------"<<endl;
    }
    

}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
     int i =0;
    bool nograde = true;
    char g = key[0];
    cout <<"---------------------------------"<<endl;
    for( i = 0; i < (int)scores.size();i++){
        if (g == grades[i] ){
            cout<<names[i]<<" ("<<scores[i]<<")"<<endl;
            nograde = false;
        }
        
    }
    if(nograde){
         cout << "Cannot found."<<endl;
    }
    cout <<"---------------------------------"<<endl;



}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
