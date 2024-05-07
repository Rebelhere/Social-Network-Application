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
	virtual void likepost() = 0;
	//virtual void addpost() = 0;
	virtual void addcomment() = 0;
};
class User :public Account
{
private:
	vector<string> friends;
	vector<string> pages_liked;
	vector<string> post_liked;
	vector<Comment*> comment;
	//Post* post;
public:
	User(string i = "", string n = "", vector<string> f = {}, vector<string> pl = {},vector<string> pol={},vector<Comment*> c={}):Account(i,n)
	{
		friends = f;
		pages_liked = pl;
		post_liked = pol;
		comment = c;
	}
	~User() 
	{

	}
	vector<string> getfriends()
	{
		return friends;
	}
	void addfriend(User& a)
	{
		bool alreadyfriend = 0;
		for (int i = 0; i < friends.size(); i++)
		{

			if (a.getid() == friends[i])
			{
				alreadyfriend = 1;
			}
		}
		if (!alreadyfriend)
		{
			string temp;
			temp = a.Account::getid();
			friends.push_back(temp);
		}
	}
	void likepage()
	{
		bool alreadyliked = 0;
		string pageid;
		cout << "Enter the id of the page you want to like:";
		cin >> pageid;
		for (int i = 0; i < pages_liked.size(); i++)
		{
			if (pageid == pages_liked[i])
			{
				alreadyliked = 1;
			}
		}
		if (!alreadyliked)
		{
			pages_liked.push_back(pageid);
		}
	}
	void likepost()
	{
	}
	void addcomment(){}
};
class Page :public Account
{
private:
	int likes;
	vector<string> post_liked;
	vector<Comment*> comment;
	//Post* post;
public:
	Page(string i = "", string n = "", int l = 0, vector<string>pl = {}, vector<Comment*>c = {}):Account(i, n)
	{
		likes = l;
		post_liked = pl;
		comment = c;
	}
	~Page() {}
	void likepost() {}
	void addcomment() {}
}; 
