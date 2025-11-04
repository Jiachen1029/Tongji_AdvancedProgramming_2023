#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

struct Record 
{
    string version;
    string username;
    int score;
    string timestamp;

    Record(const string& version, const string& username, int score, const string& timestamp)
        : version(version), username(username), score(score), timestamp(timestamp)
    {   }
};

class History 
{
public:
    History(const string& username) : filename(username + "_history.txt")
    {
        loadRecords();
    }
    void addRecord(const Record& record)
    {
        records.push_back(record);
        saveRecords();
    }
    const vector<Record>& getRecords() const 
    {
        return records;
    }
    void displayRecords() const
    {
        for (const auto& record : records)
        {
            cout << "版本: " << record.version << " 用户名: " << record.username << " 得分: " << record.score << " 时间: " << record.timestamp << endl;
        }
    }
    void deleteRecord(const string& username) 
    {
        records.erase(remove_if(records.begin(), records.end(),
            [&username](const Record& record) { return record.username == username; }), records.end());
        saveRecords();
    }
    void updateRecord(const string& username, const Record& newRecord) 
    {
        for (auto& record : records) 
        {
            if (record.username == username) 
            {
                record = newRecord;
                break;
            }
        }
        saveRecords();
    }
    Record getRecord(const string& username) const 
    {
        for (const auto& record : records) 
        {
            if (record.username == username) 
            {
                return record;
            }
        }
        throw runtime_error("Record not found");
    }
    void resetRecords() 
    {
        records.clear();
        saveRecords();
    }
private:
    string filename;
    vector<Record> records;
    void loadRecords()
    {
        ifstream file(filename);
        if (file.is_open())
        {
            string line;
            while (getline(file, line)) 
            {
                istringstream iss(line);
                string version, username, timestamp;
                int score;
                if (iss >> version >> username >> score >> timestamp) 
                {
                    records.emplace_back(version, username, score, timestamp);
                }
            }
            file.close();
        }
    }
    void saveRecords() const 
    {
        ofstream file(filename);
        if (file.is_open()) 
        {
            for (const auto& record : records) 
            {
                file << record.version << " " << record.username << " " << record.score << " " << record.timestamp << endl;
            }
            file.close();
        }
    }
};