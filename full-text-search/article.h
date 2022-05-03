#ifndef ARTICLE_H_
#define ARTICLE_H_
#include <iostream>
#include <string>

class Article {
public:
	std::string id_;
	std::string title_;
	std::string text_;

	Article(std::string a, std::string b, std::string c) : id_(a), title_(b), text_(c) {}

	bool operator<(const Article& x) const
	{
		return this->id_ < x.id_;
	}
};

//each word in inverted index have set of objects, each object contains article and position in text of this word
class Occur_of_word {
public:
	size_t occurance_;
	const Article& article_;

	Occur_of_word(size_t occurance, const Article& article) : occurance_(occurance), article_(article) {}

	bool operator<(const Occur_of_word& x) const
	{
		return this->article_.id_ < x.article_.id_;
	}
};
#endif