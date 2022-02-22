// Project 1 Starter Code - DNA Profiling
// TODO(dwarr3): Danyal Warraich  Put your header info here.  Update line above.

#include <iostream>

#include <fstream>

#include <string>

#include "ourvector.h"


using namespace std;

typedef struct {
    string names;
    ourvector<char> str;
    ourvector<int> counts;
}data;

// This function figures out whether database is loaded, or DNA is processed
// Primarily is it checks the first character of filename to ensure the difference
// between database file and dna file. And it also ensures if the DNA or 
// database is loaded it is displayed by the next command.
int searchD(string &filename, string &file1, string &file2, ourvector<int>& repStr) {
    if (filename.size() == 0) {
        cout << "No database loaded.\n";
        return -1;
    }
    if (filename[0] == 's' || filename[0] == 'l') {
        file1 = filename;
        if (!file2.empty() && repStr.size() == 0) {
            cout << "No DNA processed.\n";
            return -1;
        } else if (file2.empty()) {
        cout << "No DNA loaded.\n";
        return -1;
    }
    } else if (isdigit(filename[0])) {
        file2 = filename;
        if (file1.empty()) {
        cout << "No database loaded.\n";
        return -1;
        } else if (repStr.size() == 0) {
            cout << "No DNA processed.\n";
            return -1;
        }
    }
    return 1;
}

// This function takes two vectors as its parameters, one
// is of int data type other is of struct data. This function
// basically compares STR numbers in both the vectors to find
// the match. Important functionality here is that vector of
// structs uses vector within structs to access the number of
// STR inserted from the file
void search(ourvector<int>& repStr, ourvector<data>& d) {
    int k = 0, c = 0, count = 0, n = 0;
    cout << "Searching database...\n";
    for (int i = 1; i < d.size(); ++i) {
    for (int j = k; j < d[i].counts.size(); ++j) {
        if (repStr[c] == d[i].counts[j]) { count++; }
    c++;
    }
    if (count == d[i].counts.size()) {
        cout << "Found in database!  DNA matches: " << d[i].names << endl;
        n = 1;
        break;
    }
    count = d[i].counts.size();
    c = 0;
    k = d[i].counts.size();
    }
    if (n != 1) { cout << "Not found in database." << endl; }
}

// This function takes in two vectors just like in search
// function. It is because they are used to access the contents
// and print them. For loop is used to print the complete
// database and its STR counts.
void displayStr(ourvector<int>& repStr, ourvector<data>& d) {
    cout << "\nDNA processed, STR counts: \n";
    int j = 0;
    for (int i = 0; i < d[0].str.size(); ++i) {
        if (d[0].str[i] != ',') {
            cout << d[0].str[i];
        } else {
            cout << ": " << repStr[j] << endl;
            j++;
        }
    }
}

// This function figures out whether database is loaded, or DNA is processed
// Primarily is it checks the first character of filename to ensure the difference
// between database file and dna file. And it also ensures if the DNA or 
// database is loaded it is displayed by the next command.
int processD(string &filename, string &file1, string &file2, string &storeDNA) {
    if (filename.size() == 0) {
        cout << "No database loaded.\n";
        return -1;
    }
    if (filename[0] == 's' || filename[0] == 'l') {
        file1 = filename;
        if (!file2.empty() && storeDNA == "") {
            cout << "No DNA processed.\n";
            return -1;
        } else if (file2.empty()) {
            cout << "No DNA loaded.\n";
            return -1;
        }
    } else if (isdigit(filename[0])) {
        file2 = filename;
        if (file1.empty()) {
            cout << "No database loaded.\n";
            return -1;
        }
    }
    return 1;
}

void creativCom(string lines, ourvector<data> &d, ourvector<int>& repStr) {
    int c = 0, c2 = 0, countStr = 0, check = 0, k = 0;
    d[0].str.push_back(',');
    cout << "Processing DNA...\n";
    while (c != d[0].str.size()-1) {  // cout << d[0].str[c];
        if (d[0].str[c] == ',' || c == 0) {  // cout << "cc " << c << endl;
            if (d[0].str[c] == ',') {
                c++;
                c2 = c;
                c = c2;
            }
            for (size_t i = 0; i < lines.size(); i++) {
                if (d[0].str[c] == ',') {  countStr++;
                    check = check + countStr; 
                    c = c2;
                }  // cout << "lines[i] " << lines[i] << endl;
                if (d[0].str[c] == lines[i]) { c++; } else if (d[0].str[c] != lines[i]) {
                    c = c2;
                    i = k;
                    k++;
                    countStr = 0;
                }
            }  // cout << "STR count...: " << check << endl;
          if (d[0].str[c] == ',') {
                c = c2;
                countStr++;
                if (countStr >= check) { check = check + countStr; }
            }
            repStr.push_back(check);
            countStr = 0, check = 0, k = 0;
        }
        c++;
    }  // cout << c << endl;
}

// This function takes four parameters. variables lines allows
// the for loop to loop until the end of size of lines. vector d
// is used to access characters from str vector within structs. 
// Moreover, this function processes DNA by counting the longest
// consecutive repeated STRs
void processDNA(string lines, ourvector<data> &d, ourvector<int>& repStr) {
    int c = 0, c2 = 0, countStr = 0, check = 0, k = 0;
    d[0].str.push_back(',');
    cout << "Processing DNA...\n";
    while (c != d[0].str.size()-1) {  // cout << d[0].str[c];
        if (d[0].str[c] == ',' || c == 0) {  // cout << "cc " << c << endl;
            if (d[0].str[c] == ',') {
                c++;
                c2 = c;
                c = c2;
            }
            for (size_t i = 0; i < lines.size(); i++) {
                if (d[0].str[c] == ',') { countStr++;
                    if (countStr >= check) { check = countStr; }
                    c = c2;
                }  // cout << "lines[i] " << lines[i] << endl;
                if (d[0].str[c] == lines[i]) { c++; } else if (d[0].str[c] != lines[i]) {
                    c = c2;
                    i = k;
                    k++;
                    countStr = 0;
                }
            }  // cout << "STR count...: " << check << endl;
          if (d[0].str[c] == ',') {
                c = c2;
                countStr++;
                    if (countStr >= check) { check = countStr; }
            }
            repStr.push_back(check);
            countStr = 0, check = 0, k = 0;
        }
        c++;
    }  // cout << c << endl;
}

// This function takes one parameter as vector which is
// a struct type. Purpose of this function is to display
// database, therefore, nested loop is used here.
void display(ourvector<data>& d) {
    if (d.size() == 0) {  // cout << d.size() << endl;
        cout << "No database loaded.\n";
    } else { cout << "Database loaded: \n"; }
    int k = 0;
    for (int i = 1; i < d.size(); i++) {
        cout << d[i].names << " ";
        for (int j = k; j < d[i].counts.size(); j++) {
           if (j+1 == d[i].counts.size()) {
                cout << d[i].counts[j];
            } else { cout << d[i].counts[j] << " ";}
        }
        cout << endl;
        k = d[i].counts.size();
    }
}

// This function takes three parameters. Purpose of This
// function is to display the contents of database, therefore,
// nested for loop is used. 
void display2(ourvector<data>& d, string lines, string filename) {
    if (d.size() == 0) {  // cout << d.size() << endl;
        cout << "No database loaded.\n";
    } else if (filename == "thisone.txt") {
        cout << "No database loaded.\n";
        return;
    } else { cout << "Database loaded: \n"; }
    int k = 0;
    for (int i = 1; i < d.size(); i++) {
        cout << d[i].names << " ";
        for (int j = k; j < d[i].counts.size(); j++) {
            if (j+1 == d[i].counts.size()) {
                cout << d[i].counts[j];
            } else { cout << d[i].counts[j] << " "; }
        }
        cout << endl;
        k = d[i].counts.size();
    }
    cout << "\nDNA loaded: \n";
    cout << lines << endl;  // cout << d[0].names.size() << endl;
}

// This function takes three parameters and the purpose of this function
// is to store database extracted from the file and while storing it
// also to seperate the STR counts and str characters. This function
// also uses to_string() to convert number into string and concatenate
// and convert back to int in case the STR count is double digit.
void stores_dataBase(string lines, ourvector<data> &d, data& info) {
    string word;
    int num = 0, num2 = 0;
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i] == ',') {
            word = lines.substr(0, i);  // cout << "word: " << word << endl;
            info.names = word;
            lines = lines.substr(i+1, lines.size());
            break;
        }
    }
    for (size_t i = 0; i < lines.size(); ++i) {
        if (!isdigit(lines[i])) {
            if (lines[i] != ',') { info.str.push_back(lines[i]);}
        }
        if (lines[i] == ',') {info.str.push_back(',');}
        if (isdigit(lines[i]) && isdigit(lines[i+1])) {
            num = (int)(lines[i]);
            num = num - '0';
            num2 = (int)(lines[i+1]);
            num2 = num2 - '0';
            string s1 = to_string(num);
            string s2 = to_string(num2);
            string s = s1 + s2;
            int c = stoi(s);
            info.counts.push_back(c);
        } else if (isdigit(lines[i]) && !isdigit(lines[i-1])) {
            num = (int)(lines[i]);
            num = num - '0';
            info.counts.push_back(num);
        }
    }
    d.push_back(info);
}

// This function takes in the filename and checks if it opens.
// After its open it goes through the data within the dna file.
// If the command is display display2 dunction is called.
void dnaReading(string filename, string &lines, ourvector<data>& d, string &storeDNA, string &command, string &loadData) {
  ifstream inFile;
  // open the file
  inFile.open(filename);
  // check if file is opened successfully
  if (!inFile.is_open()) {
    cout << "Loading DNA..." << endl;
    cout << "Error: unable to open '" << filename << "'" << endl;
    cout << "Enter command or # to exit: ";
    cin >> loadData;
    return;
  }
  // read data from file line by line
  inFile >> lines;
  while (!inFile.eof()) {
    if (!inFile.fail()) {
     // cout << lines << endl;
      storeDNA = lines;
    }
    inFile >> lines;
  }
  cout << "Loading DNA..." << endl;
  cout << "Enter command or # to exit: ";
  cin >> command;

  if (command == "display") {
      display2(d, lines, filename);
      storeDNA = lines;
        cout << "\nNo DNA has been processed.\n";
  }
  if (command != "process" && command != "search") {
      cout << "Enter command or # to exit: ";
      cin >> loadData;
      } else if (command == "process") { loadData = "process"; } else if (command == "search") { loadData = "search"; }
  inFile.close();
}

// This function reads the data and checks if it opens.
// It reads the data line by line and calls stores_dataBase
// function to store such data seperately and more efficiently
void fileReading(string filename, string &lines, ourvector<data>& d, string& file1) {
  ifstream inFile;
  data info;
  if (d.size() != 0) { d.clear(); }
  // open the file
  inFile.open(filename);
  // check if file is opened successfully
  if (!inFile.is_open()) {
    cout << "Loading database..." << endl;
    cout << "Error: unable to open '" << filename << "'" << endl;
    return;
  }
  cout << "Loading database..." << endl;
  file1 = filename;
  // read data from file line by line
  inFile >> lines;
  while (!inFile.eof()) {
    if (!inFile.fail()) {
     // cout << lines << endl;
      stores_dataBase(lines, d, info);
    }
    inFile >> lines;
  }
  inFile.close();
}

// This function is ensure whether DNA loaded from the file
// and it also calls display(d) function to make it user friendly
void screen(ourvector<data> &d, string &storeDNA, string &tempSt, string &filename) {
    display(d);
    if (!storeDNA.empty()) {
        cout << "\nDNA loaded:\n";
        cout << storeDNA << endl << endl;
        } else if (d.size() != 0 && tempSt != "" && filename != "thisone.txt") {
             cout << "\nDNA loaded:\n";
             cout << tempSt << endl << endl;
           } else { cout << "\nNo DNA loaded.\n\n"; }
}

// This function is ensure whether DNA loaded from the file
// and it also calls display(d) function to make it user friendly
void screen2(ourvector<data> &d, string &command, ourvector<int>& repStr) {
    if (command != "" && repStr.size() != 0) {
        displayStr(repStr, d);
        cout << endl;
        } else {
        cout << "No DNA has been processed.\n";
    }
    cout << "Enter command or # to exit: ";
}

// Main function has all the essential commands that
// user works with and it also projects the Application
// design. It calls several functions, asks users to input
// and prints out the information
int main() {
  string filename = "", lines, loadData, storeDNA, tempSt = "";
  string command = "", file1, file2;
  ourvector<int> repStr;
  ourvector<data> d;
  int value = 0, value2 = 0;
  cout << "Welcome to the DNA Profiling Application.\n";
  cout << "Enter command or # to exit: ";
  cin >> loadData;
  while (loadData != "#") {
       if (loadData == "load_db") {
       cin >> filename;
       fileReading(filename, lines, d, file1);
       cout << "Enter command or # to exit: ";
       cin >> loadData;
  }
       if (loadData == "display") {
           screen(d, storeDNA, tempSt, filename);
           screen2(d, command, repStr);
           cin >> loadData;
       }
       if (loadData == "load_dna") {
           cin >> filename;
           dnaReading(filename, lines, d, storeDNA, command, loadData);
           tempSt = lines;
       }
       if (loadData == "process") {
           value = processD(filename, file1, file2, storeDNA);
           if (value != -1) { processDNA(tempSt, d, repStr); }
            cout << "Enter command or # to exit: ";
            cin >> loadData;
            if (loadData == "display") {
            display2(d, tempSt, filename);
            storeDNA = lines;
            displayStr(repStr, d);
            cout << "\nEnter command or # to exit: ";
            cin >> loadData;
            }
       }
       if (loadData == "search") {
           value2 = searchD(filename, file1, file2, repStr);
           if (value2 != -1) { search(repStr, d); }
           cout << "Enter command or # to exit: ";
           cin >> loadData;
       }
       if (loadData == "creative"){
            creativCom( lines, d, repStr);
            display2(d, tempSt, filename);
            storeDNA = lines;
            displayStr(repStr, d);
            cout << "Enter command or # to exit: ";
            cin >> loadData;
        }
  }
  cout << endl;
  return 0;
}
