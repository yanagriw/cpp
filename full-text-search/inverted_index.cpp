#include "inverted_index.h"
#include <algorithm>
using namespace std;

Inverted_index::Inverted_index(const vector<Article>& database_of_article) {
    for (auto itr = database_of_article.begin(); itr != database_of_article.end(); ++itr) {
        process_article(*itr);
    }
}

//structure that helps to find intersection of words' occurences
struct Inverted_index::Id_of_itr{
    string id_;
    set<Occur_of_word>::iterator itr_; //iterator to article with such id
    set<Occur_of_word>::const_iterator itr_end; //iterator to end of set of articles

    bool operator<(const Id_of_itr & x) const
    { return this->id_ < x.id_; }
    bool operator==(const Id_of_itr & x) const
    { return this->id_ == x.id_; }
};

//split text into words and add these words in "inverted index" map
void Inverted_index::process_article(const Article& a) {
    string temp = "";
    for (size_t i = 0; i < a.text_.size(); ++i) {
        if (isalpha(a.text_[i])) temp += a.text_[i];
        else {
            if (!temp.empty()) {
                add_to_map(temp, a, i - temp.size());
                temp = "";
            }
        }
    }
    if (!temp.empty())
        add_to_map(temp, a, a.text_.size() - temp.size() + 1);
}

void Inverted_index::add_to_map(string word, const Article& a, size_t position) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    auto itr = map_of_words.find(word);
    Occur_of_word occur(position, a); //objects with article in which we've find this word and position in text of word

    if (itr != map_of_words.end()) {
        itr->second.insert(occur);
    }
    else {
        map_of_words.insert(pair<string, set<Occur_of_word>>(word, set<Occur_of_word>{occur}));
    }
}

void Inverted_index::read_questions(istream& istr, string& str) {
    while (getline(istr, str)) {
        if (str.empty()) break;
        if (find_occur(str)) cout << endl;
        else cout << "No results" << endl << endl;
    }
}

//find articles that contain all words from question
bool Inverted_index::find_occur(const string& question) {
    bool flag = false; //to know if exists such article
    vector <Id_of_itr> v; //vector contains structures (id of article + iterator to this article) 

    //for each word in question add to vector id in which it contain (first) + itr to article with such id
    //if word was not found in map or question doesn't contain any word - return false
    if (!make_vector_of_itr(v, question)) return false;

    size_t v_size = v.size();
    while (true) {
        //if all id in vector are same, move all iterators to next article in set 
        if (equal(v.begin() + 1, v.end(), v.begin())) {
            print_occur(*(v[0].itr_)); 
            flag = true;
            for (size_t i = 0; i < v_size; ++i) {
                auto result_next = next(v[i].itr_, 1);
                if (result_next == v[i].itr_end) return flag;
                v[i].itr_ = result_next;
                v[i].id_ = (*result_next).article_.id_;
            }
        }
        // else move iterator of smallest id to next article
        else {
            auto result = min_element(begin(v), end(v));
            auto result_next = next((*result).itr_, 1);
            if (result_next == (*result).itr_end) return flag;
            (*result).itr_ = result_next;
            (*result).id_ = (*result_next).article_.id_;
        }
    }
}

bool Inverted_index::make_vector_of_itr(vector<Id_of_itr>& v, const string& question) {
    string temp = "";
    map <std::string, std::set <Occur_of_word>>::iterator itr_map;
    size_t question_size = question.size();
    for (size_t i = 0; i < question_size; ++i) {
        //split question into words 
        if (isalpha(question[i])) temp += question[i];
        else if (!temp.empty()) {
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            itr_map = map_of_words.find(temp);
            if (itr_map != map_of_words.end()) {
                /*add id of first article that contains word, iterator to this article
                and iterator to end of set of articles for this word*/
                v.push_back(Id_of_itr{ (*(itr_map->second).begin()).article_.id_ ,
                                        (itr_map->second).begin() ,
                                        (itr_map->second).end() });
            }
            else return false;
            temp = "";
        }
    } if (!temp.empty()) {
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        itr_map = map_of_words.find(temp);
        if (itr_map != map_of_words.end()) {
            v.push_back(Id_of_itr{ (*(itr_map->second).begin()).article_.id_ ,
                                    (itr_map->second).begin() ,
                                    (itr_map->second).end() });
        }
        else return false;
    }
    if (v.empty()) return false;
    return true;
}

void Inverted_index::print_occur(const Occur_of_word& occur) {
    cout << "[" << occur.article_.id_ << "] " << occur.article_.title_ << endl
         << occur.article_.text_.substr(occur.occurance_, 75) << "..." << endl;
}