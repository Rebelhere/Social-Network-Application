#include<iostream>
#include<vector>
#include<string>
#include<string.h>
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
		Page* p = new Page(id, fullname);
		acc.push_back(p);
	}
	
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
		getline(file, description);
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
void peoplewholikes(vector<Post*>& p, vector<Account*>acc)
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
				cout << p[j]->getlike()[i]<<" - ";
				for (Account* a:acc)
				{
					if (p[j]->getlike()[i]==a->getid())
					{
						cout << a->getname() << endl;;
					}
				}

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
			cin.ignore();
			getline(cin,description);
			cout << description<<endl;
			string commentid = "";
			Comment* c = new Comment(commentid, selectedpost, user->getid(), description);
			cmnt.push_back(c);
		}
	}
}
void viewpost(vector<Account*>acc,vector<Post*>p,vector<Comment*>cmnt,string selectedpost)
{
	for (Post* po : p)
	{
		if (selectedpost == po->getpostid())
		{
			if (po->getactivitynumber()!=0)
			{
				cout << "---";
				for (Account* a:acc)
				{
					if (a->getid()==po->getpostedby())
					{
						cout << a->getname()<<" is " << po->getactivitytype();
					}
				}
			}
			cout << "\n\t'" << po->getpostdescription() << "'...(" << po->getpostdate() << "/" << po->getpostmonth() << "/" << po->getpostyear() << ")\n";
			for (Comment* c : cmnt)
			{
				if (c->getpostid() == po->getpostid())
				{
					for (Account* ac : acc)
					{
						if (c->getuserid() == ac->getid())
						{
							cout << "\n\t\t" << ac->getname() << " wrote: '" << c->getdescription() << "'\n";
						}
					}
				}
			}
		}
	}
}
void displayprofile( Account*& user, vector<Account*>acc, vector<Post*>p, vector<Comment*>cmnt)
{
	cout << user->getname() << "-Time Line\n\n";
	int counter=0;
	for (Post* po : p)
	{
		if (po->getpostedby()==user->getid())
		{
			viewpost(acc, p, cmnt, po->getpostid());
			counter++;
		}
	}
	if (counter == 0)
	{
		cout << "There is no post\n";
	}
}
void viewpage(vector<Account*>acc, vector<Post*>p, vector<Comment*>cmnt,string selectedpage)
{
	for (Account* a:acc)
	{
		if (a->getid()==selectedpage)
		{
			cout << a->getname()<<"\n";
			int counter = 0;
			for (Post* po : p)
			{
				if (po->getpostedby() == a->getid())
				{
					viewpost(acc, p, cmnt, po->getpostid());
					counter++;
				}
			}
			if (counter == 0)
			{
				cout << "There is no post\n";
			}
		}
	}
}
//void viewfriends(Account*& user,vector<Account*> acc)
//{
//	
//}

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
	peoplewholikes(post,account);
	addcomment(currentuser, comment, post);
	string selectedpost;
	cout << "enter the post you want to see the comment on : ";
	cin >> selectedpost;
	viewpost(account, post, comment, selectedpost);
	/*string id;
	cout << "enter the id whose friends you want to check :";
	cin >> id;*/
	displayprofile(currentuser, account, post, comment);
	string selectpage;
	cout << "enter the page id of the page you want to view : ";
	cin >> selectpage;
	viewpage(account, post, comment, selectpage);
}


//commentid= "c"+"comment.size()"