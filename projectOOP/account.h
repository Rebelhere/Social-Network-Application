#include<iostream>
#include<vector>
#include"post.h"
using namespace std;

class Account
{
private:
	string id;
	string name;
public:
	Account(string i="",string n="")
	{
		id = i;
		name = n;
	}
	~Account() {}
	string getid()
	{
		return id;
	}
	string getname()
	{
		return name;
	}
//	virtual void likepost() = 0;
	virtual vector<string> getfriends() = 0;
	virtual vector<string> getlikedpages() = 0;
//	virtual void addcomment() = 0;
	virtual string check() = 0;
};
class User :public Account
{
private:
	vector<string> friends;
	vector<string> pages_liked;
	vector<string> post_liked;
	vector<Comment*> comment;
	string a;
public:
	User(string i = "", string n = "", vector<string> f = {}, vector<string> pl = {},vector<string> pol={},vector<Comment*> c={}):Account(i,n)
	{
		friends = f;
		pages_liked = pl;
		post_liked = pol;
		comment = c;
		a = "user";
	}
	~User() 
	{

	}
	vector<string> getfriends()
	{
		return friends;
	}
	vector<string> getlikedpages()
	{
		return pages_liked;
	}
	string check()
	{	
		return a;
	}
};
class Page :public Account
{
private:
	int likes;
	vector<string> post_liked;
	vector<Comment*> comment;
	string a;
public:
	Page(string i = "", string n = "", int l = 0, vector<string>pl = {}, vector<Comment*>c = {}):Account(i, n)
	{
		likes = l;
		post_liked = pl;
		comment = c;
		a = "page";
	}
	~Page() {}
	vector<string> getfriends()
	{
		return post_liked;
	}
	vector<string> getlikedpages()
	{
		return post_liked;
	}
	string check()
	{
		return a;
	}
}; 
