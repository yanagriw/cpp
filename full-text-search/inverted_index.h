#ifndef INVERTED_INDEX_H_
#define INVERTED_INDEX_H_
#include <set>
#include <vector>
#include <map>
#include <iterator>
#include "article.h"

class Inverted_index {
public:
	Inverted_index(const std::vector<Article>& database_of_article);
	void read_questions(std::istream& istr, std::string& str);
	bool find_occur(const std::string& question);

private:
	struct Id_of_itr;
	std::map <std::string, std::set <Occur_of_word>> map_of_words; //inverted index
	void process_article(const Article& a);
	void add_to_map(std::string word, const Article& a, size_t position);
	bool make_vector_of_itr(std::vector<Id_of_itr>& v, const std::string& question);
	void print_occur(const Occur_of_word& occur);
};

#endif