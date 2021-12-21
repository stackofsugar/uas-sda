#include "include/pch.h"
using namespace std;

void stripSpaces(string &str) {
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == ' ') {
            str.erase(str.begin() + i--);
        }
    }
}

// [start, end]
string substringRange(string &str, size_t start, size_t end) {
    return str.substr(start, end - start + 1);
}

bool stringParser(string &msg, vector<int> &result) {
    if (msg[0] != '[') {
        throw invalid_argument("Karakter pertama harus '['!");
    }

    vector<int> ret;
    string token_str;
    int token;
    stringstream ss("");
    const char br_open = '[', br_close = ']';
    size_t pos_found_br_open = 0, pos_found_br_close = 0;

    stripSpaces(msg);

    while ((pos_found_br_open = msg.find(br_open, pos_found_br_open)) != string::npos) {
        if (pos_found_br_close != 0) {
            if (pos_found_br_open < (pos_found_br_close - 1)) {
                throw invalid_argument("Kurung siku tidak dapat nested!");
            }
        }
        pos_found_br_open++;
        if ((pos_found_br_close = msg.find(br_close, pos_found_br_close)) != string::npos) {
            if (pos_found_br_close < (pos_found_br_open - 1)) {
                throw invalid_argument("Kurung siku tidak dapat nested!");
            }
            pos_found_br_close++;
        }
        ss << substringRange(msg, pos_found_br_open, pos_found_br_close - 2) << ',';
    }

    while (getline(ss, token_str, ',')) {
        if (!token_str.empty()) {
            token = stoi(token_str);
        }
        ret.push_back(token);
    }

    result = ret;
    return true;
}

/*
    0123456789*123
    [],[],[],[],[]
    o[0]c[1]o[3]c[4]o[6]c[7]o[9]c[10]o[12]c[13]

    0123456789*123456
    [1        ,2 ,    3    ,4 ],   [   5  ,3   , 4]
    0-8 10-16

    [1    ,2 ,3  ,4],   [5  ,  ,3  ,  4]
*/