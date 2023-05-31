#include <vector>
#include <string>
#include <unordered_map>

using namespace std;


vector<string> replace_words(const vector<string>& prefixes, 
const vector<string>& sentence){

    unordered_map<string, string> words;
    vector<string> final;
    final.reserve(sentence.size());

    for(auto it = sentence.begin(); it != sentence.end(); it++){

        string current = *it;

        for(size_t i = 0; i < current.size(); i++){

            string substr = current.substr(0,i);
            for(auto it2 = prefixes.begin(); it2 != prefixes.end(); it2++){

                if(substr == *it2){
                    words[current] = *it2;
                }
            }
                
        }
    }

    for(auto it = sentence.begin(); it != sentence.end(); it++){
        if(words.find(*it) != words.end()){
            final.push_back(words[*it]);
        } else {
            final.push_back(*it);
        }
    }

    return final;



}