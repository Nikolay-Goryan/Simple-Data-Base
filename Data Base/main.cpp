//
//  main.cpp
//  FinalProblem
//
//  Created by Nikolay Goryan on 02/01/2019.
//  Copyright © 2019 Nikolay Goryan. All rights reserved.
//

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <iomanip>
#include <sstream>


using namespace std;


class Date {
public:
    Date() {
        day = 0;
        month = 0;
        year = 0;
    }
    Date(int d, int m, int y) {
        this->day = d;
        this->month = m;
        this->year = y;
    }
    void ChangeDay(int new_day){
        day = new_day;
    }
    void ChangeMonth(int new_month){
        month = new_month;
    }
    void ChangeYear(int new_year){
        year = new_year;
    }
    int GetYear() const {
        return year;
    };
    int GetMonth() const {
        return month;
    }
    int GetDay() const {
        return day;
    }
private:
    int day, month, year;
};

ostream& operator << (ostream& output, Date date) {
    output << setw(4) << setfill('0') << date.GetYear() << "-" << setw(2) << setfill('0') << date.GetMonth() << "-" << setw(2) << setfill('0') << date.GetDay();
    return output;
}

bool operator<(const Date& lhs, const Date& rhs) {
    if(lhs.GetYear() < rhs.GetYear()) {
        return true;
    } else if(lhs.GetYear() == rhs.GetYear()) {
        if(lhs.GetMonth() < rhs.GetMonth()) {
            return true;
        } else if(lhs.GetMonth() == rhs.GetMonth()) {
            if(lhs.GetDay() < rhs.GetDay()) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    return false;
}

class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        
        database[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event) {
        try {
            database.at(date);
        } catch(out_of_range&) {
            cout << "Event not found" << endl;
            return false;
        }
        if(database.at(date).find(event) == database.at(date).end()) {
            cout << "Event not found" << endl;
            return false;
        } else {
            database.at(date).erase(event);
            cout << "Deleted successfully" << endl;
            return true;
        }
        
        
        
    }
    int  DeleteDate(const Date& date) {
        int N = int(database[date].size());
        if(N == 0) {
            database.erase(date);
        } else {
            database[date].clear();
        }
        cout << "Deleted" << " " <<  N << " " << "events" << endl;
        return N;
    }
    
    set<string> Find(const Date& date) const {
        set<string> set;
        try {
            database.at(date);
        } catch(out_of_range&) {
            return set;
        }
        for(auto event: database.at(date)) {
            cout << event << endl;
        }
        return database.at(date);
        
    }
    
    void Print() const {
        for(auto db: database) {
            for(auto event: db.second) {
                cout << db.first << " " << event << endl;
            }
        }
    }
private:
    map<Date, set<string>> database;
};


bool checkCorrectDate(const string& date, Date& current_date)
{
    
    stringstream sstr(date);
    int year, month, day;
    month = -1;
    day = -1;
    sstr >> year;
    sstr.ignore(1);
    sstr >> month;
    if(sstr.fail())
    {
        cout << "Wrong date format: " << date << endl;
        return false;
    }
    if(month < 1 || month > 12)
    {
        cout << "Month value is invalid: " << month << endl;
        return false;
    }
    
    
    sstr.ignore(1);
    sstr >> day;
    
    if(sstr.fail()) 
    {
        cout << "Wrong date format: " << date << endl;
        return false;
        
    }
    if(day < 1 || day > 31)
    {
        cout << "Day value is invalid: " << day << endl;
        return false;
        
    }
    string buffer;
    sstr >> buffer;
    
    if(!buffer.empty())
    {
        cout << "Wrong date format: " << date << endl;
        return false;
        
    }
    
    current_date.ChangeDay(day);
    current_date.ChangeMonth(month);
    current_date.ChangeYear(year);
    
    return true;
}

bool DataValidation(string date, Date& command_date) {
    stringstream si(date);
    string s_day, s_month, s_year;
    int day, month, year;
    si >> year;
    si.ignore(1);
    si >> month;
    si.ignore(1);
    si >> day;
    
    
    string true_date = to_string(year) + '-' + to_string(month) + '-' + to_string(day);
    if(date == true_date) {
        if(month > 12 || month < 1) {
            cout << "Month value is invalid: " << month << endl;
            return false;
        }
        if(day > 31 || day < 1) {
            cout << "Day value is invalid: " << day << endl;
            return false;
        } else {
            command_date.ChangeDay(day);
            command_date.ChangeMonth(month);
            command_date.ChangeYear(year);
            return true;
        }
        
        
    } else {
        cout << "Wrong date format: " << date << endl;
        return false;
    }
}


int main() {
    Database db;
    
    string command;
    while (getline(cin, command)) {
        stringstream ss(command);
        string command_part;
        ss >> command_part;
        if(command_part == "") continue;
        if(command_part == "Add") {
            Date date;
            ss >> command_part;
            if(checkCorrectDate(command_part, date) == true){
                ss >> command_part;
                db.AddEvent(date, command_part);
            } else {
                continue;
            }
        } else if(command_part == "Del") {
            Date date;
            ss >> command_part;
            if(checkCorrectDate(command_part, date) == true){
                if(ss >> command_part) {
                    db.DeleteEvent(date, command_part);
                } else {
                    db.DeleteDate(date);
                }
            } else {
                continue;
            }
            
        } else if(command_part == "Find") {
            Date date;
            ss >> command_part;
            if(checkCorrectDate(command_part, date) == true){
                db.Find(date);
            } else {
                continue;
            }
            
        } else if(command_part == "Print") {
            db.Print();
        } else {
            cout << "Unknown command: " << command_part;
        }
    }
    
    return 0;
}
