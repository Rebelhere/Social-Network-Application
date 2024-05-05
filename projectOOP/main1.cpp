#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"account.h"
using namespace std;
void readusers(vector<Account*>&acc)
{
	ifstream file;
	file.open("Users.txt");
	int totaluser;
	file >> totaluser;
	string id,name1,name2,fullname;
	vector<string>frnd;
	vector<string>pageslike;
	for (int i = 0; i < totaluser; i++)
	{
		file >> id;
		file >> name1;
		file >> name2;
		fullname = name1 +" "+ name2;
		string check;
		file >> check;
		for (int i = 0;check!="-1"; i++)
		{
			frnd.push_back(check);
			file >> check;
		}
		file >> check;
		for (int i = 0; check != "-1"; i++)
		{
			pageslike.push_back(check);
			file >> check;
		}
		User* u = new User (id,fullname,frnd,pageslike);
		acc.push_back(u);
	}
}
void readpages(vector<Account*>& acc)
{
	ifstream file;
	file.open("Pages.txt");
	int totalpages;
	file >> totalpages;
	string id, fullname;
	for (int i = 0; i < totalpages; i++)
	{
		file >> id;
		file.ignore();
		getline(file,fullname);
	}
	Page* p = new Page(id, fullname);
	acc.push_back(p);
}
void readpost(vector<Post*>&poo)
{
	ifstream file;
	file.open("Posts.txt");
	int totalposts;
	file >> totalposts;
	string postid,description, activitycontent, postedby;
	int d, m, y,activitytype;
	for (int i = 0; i < totalposts; i++)
	{
		int checker;
		vector<string>likedby = {};
		file >> checker;
		if (checker == 2)
		{
			file >> postid;
			file >> d;
			file >> m;
			file >> y;
			file.ignore();
			getline(file, description);
			file >> activitytype;
			file.ignore();
			getline(file, activitycontent);
			file >> postedby;
			string checker2;
			file >> checker2;
			for (int i = 0;checker2!="-1"; i++)
			{
				likedby.push_back(checker2);
				file >> checker2;
			}
		}
		else
		{
			file >> postid;
			file >> d;
			file >> m;
			file >> y;
			file.ignore();
			getline(file, description);
			activitytype = 0;
			activitycontent = "";
			file >> postedby;
			string checker2;
			file >> checker2;
			for (int i = 0; checker2 != "-1"; i++)
			{
				likedby.push_back(checker2);
				file >> checker2;
			}
		}
		Time* t = new Time(d, m, y);
		Activity* a = new Activity(activitycontent, activitytype);
		Post* p = new Post(postid, description, postedby, t, likedby, {},a);
		poo.push_back(p);
	}
	
}
void readcomment(vector<Comment*>&cmnt)
{
	ifstream file;
	file.open("Comments.txt");
	int totalcomments;
	file >> totalcomments;
	string commentid, postid, userid, description;
	for (int i = 0; i < totalcomments; i++)
	{
		file >> commentid;
		file >> postid;
		file >> userid;
		file.ignore();
		file >> description;
		Comment* c = new Comment(commentid, postid, userid, description);
		cmnt.push_back(c);
	}
}
void likepost(Account*&user,vector<Post*>&p)
{
	string selectedpost;
	cout << "enter the post you want to like :";
	cin >> selectedpost;
	for (int i = 0; i <p.size() ; i++)
	{
		if (selectedpost==p[i]->getpostid())
		{
			if(p[i]->getlike().size()<=10) 
			{
				p[i]->setlikes(user->getid());
			}
			else
			{
				cout << "the likes are exceeding 10 therefore no more likes possible.";
			}
		}
	}
}
void peoplewholikes(vector<Post*>& p)
{
	string selectedpost;
	cout << "enter the post you want to see likes on :";
	cin >> selectedpost;
	for (int j = 0; j < p.size(); j++)
	{
		if (selectedpost == p[j]->getpostid())
		{
			
			for (int i = 0; i < p[j]->getlike().size(); i++)
			{
				cout << p[j]->getlike()[i]<<endl;
			}
			if (p[j]->getlike().size()==0)
			{
				cout << " NO LIKES ";
			}
		}
	}
}
void addcomment(Account*& user,vector<Comment*>&cmnt, vector<Post*>& p)
{
	string selectedpost;
	cout << "enter the post you want to comment on : ";
	cin >> selectedpost;
	for (int i = 0; i < p.size(); i++)
	{
		if (selectedpost == p[i]->getpostid())
		{
			string description;
			cout << "enter the comment:";
			cin >> description;
			string commentid = "";
			Comment* c = new Comment(commentid, user->getid(), selectedpost, description);
			cmnt.push_back(c);
		}
	}
}
int main()
{
	vector<Account*>account;
	readusers(account);
	readpages(account);
	vector<Post*>post;
	readpost(post);
	vector<Comment*>comment;
	readcomment(comment);
	string id;
	cout << "Enter your user id:";
	cin >> id;
	Account* currentuser=nullptr;
	for (int i = 0; currentuser==nullptr ; i++)
	{
		for (int i = 0; i < account.size(); i++)
		{
			if (id == account[i]->getid())
			{
				currentuser = account[i];
			}
		}
		if (currentuser==nullptr)
		{
			cout << "user id doesnot exist \n enter again : ";
			cin >> id;
		}
	}
	char check;
	/*cout << "Do you want to view your home page(y/n)";
	cin >> check;
	if (check=='y')
	{

	}*/
	cout << "do you want to like a post (y/n)";
	cin >> check;
	if (check=='y')
	{
		likepost(currentuser, post);
		cout << "you have liked the post successfully\n";
	}
	peoplewholikes(post);
	addcomment(currentuser, comment, post);

}


//commentid= "c"+"comment.size()"