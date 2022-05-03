#include "inverted_index.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 3 || argc == 1) return 0;

    string line1;
    string line2;
    string line3;
    vector<Article> database_of_article;

    //file from 1st argument
    ifstream articles;
    articles.open(argv[1]);
    if (!articles.good()) return 0;

    //file from 2nd argument if it exists 
    ifstream questions;
    if (argc == 3) {
        questions.open(argv[2]);
        if (!questions.good()) return 0;
    }

    //make database of articles from 1st file
    while (getline(articles, line1)) {
        if (line1.empty()) break;
        getline(articles, line2);
        getline(articles, line3);
        database_of_article.push_back(Article(line1, line2, line3));
    }

    //make inverted index of all words from articles
    Inverted_index inverted_index(database_of_article);

    //write answers to questions from file or cin
    if (argc== 3) {
        inverted_index.read_questions(questions, line1);
    }
    else {
        inverted_index.read_questions(cin, line1);
    }
}
