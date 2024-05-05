#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Comment
{
private:
	string comment_id;
	string user_id;
	string post_id;
	string description;
public:
	Comment(string ci="", string ui = "", string pi = "", string d = "") 
	{
		comment_id = ci;
		user_id = ui;
		post_id = pi;
		description = d;
	}
	~Comment() {}
	
};
class Activity
{
private:
	string activity_type;
	int activity_number;
public:
	Activity(string at="", int an = 0)
	{
		activity_number = an;
		string temp;
		if (an==1)
		{
			temp = "feeling ";
		}
		else if (an==2)
		{
			temp = "thinking about ";
		}
		else if (an==3)
		{
			temp = "making ";
		}
		else if (an == 4)
		{
			temp = "celebrating ";
		}
		else
		{
			temp = "";
		}
		activity_type = temp + " " + at;
	}
	~Activity() {}

};
class Time
{
private:
	int date, month, year;
public:
	Time(int d=0,int m=0, int y=0)
	{
		date = d;
		month = m;
		year = y;
	}
	~Time() {}
};
class Post
{
private:
	string post_id;
	string post_description;
	string posted_by;
	Time* post_date;
	vector<string> like;
	vector<Comment*> comment;
	Activity* activity;
public:
	Post(string pi = "", string pd = "", string pb = "", Time* pod = nullptr, vector<string>l = {}, vector<Comment*>c = {}, Activity* a = {})
	{
		post_id = pi;
		post_description = pd;
		posted_by = pb;
		post_date = pod;
		like = l;
		comment = c;
		activity = a;
	}
	~Post() {}
	string getpostid()
	{
		return post_id;
	}
	void setlikes(string a)
	{
		like.push_back(a);
	}
	vector<string> getlike()
	{
		return like;
	}
};
