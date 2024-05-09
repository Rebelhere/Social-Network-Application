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
		frnd = {};
		pageslike = {};
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
void readpost(vector<Post*>&poo,int date,int month , int year)
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
		if (year > y || (year == y && month > m) || (date >= d && month == m && year == y))
		{

			Time* t = new Time(d, m, y);
			Activity* a = new Activity(activitycontent, activitytype);
			Post* p = new Post(postid, description, postedby, t, likedby, {}, a);
			poo.push_back(p);
		}
	}
}
void readcomment(vector<Comment*>&cmnt, vector<Post*>& poo)
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
		for (Post*p:poo)
		{
			if (p->getpostid()==postid)
			{
				Comment* c = new Comment(commentid, postid, userid, description);
				cmnt.push_back(c);
			}
		}
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
			else
			{
				cout << "---";
				for (Account* a : acc)
				{
					if (a->getid() == po->getpostedby())
					{
						cout << a->getname() << " shared ";
					}
				}
			}
			cout << "\n\t'" << po->getpostdescription() << "'...(" << po->getpostdate() << "/" << po->getpostmonth() << "/" << po->getpostyear() << ")\n\n";
			for (Comment* c : cmnt)
			{
				if (c->getpostid() == po->getpostid())
				{
					for (Account* ac : acc)
					{
						if (c->getuserid() == ac->getid())
						{
							cout << "\n\t\t" << ac->getname() << " wrote: '" << c->getdescription() << "'\n\n";
						}
					}
				}
			}
		}
	}
}
void displayprofile(string id, vector<Account*>acc, vector<Post*>p, vector<Comment*>cmnt, vector<Memory*>me)
{
	for (Account*a:acc)
	{
		if (id==a->getid())
		{
			cout << a->getname() << "-Time Line\n\n";
			int counter = 0;
			for (Memory*m:me)
			{
				if (m->getuserid()==a->getid())
				{
					cout << "~~~ " << a->getname() << "shared a memory ~~~...(" << m->getrepostdate() << "/" << m->getrepostmonth() << "/" << m->getrepostyear() << ")\n\t\t";
					cout << m->getdescription()<<endl<<"\t\t" << m->getgap()<<endl;
					viewpost(acc, p, cmnt, m->getprevpost()->getpostid());
				}
			}
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
void viewfriends(Account*& user,vector<Account*> acc)
{
	for (int i = 0;i<user->getfriends().size() ; i++)
	{
		for (Account* a:acc)
		{
			if (a->getid()==user->getfriends()[i])
			{
				cout << user->getfriends()[i]<< " - " << a->getname()<<endl;
				break;
			}
		}
	}
}
void viewhome(vector<Account*>acc, vector<Post*>p, vector<Comment*>cmnt,int d,int m,int y, Account*& user)
{
	for (Account* a:acc)
	{
		for (int i = 0; i < user->getfriends().size(); i++)
		{
			if (a->getid() == user->getfriends()[i])
			{
				for (Post* po : p)
				{
					if (po->getpostedby() == a->getid() && (d == po->getpostdate() || (d - 1) == po->getpostdate()) && (m == po->getpostmonth()) && (y = po->getpostyear()))
					{
						viewpost(acc, p, cmnt, po->getpostid());
					}
				}
			}
		}
		for (int i = 0; i < user->getlikedpages().size(); i++)
		{
			if (a->getid() == user->getlikedpages()[i])
			{
				for (Post* po : p)
				{
					if (po->getpostedby() == a->getid() && (d == po->getpostdate() || (d - 1) == po->getpostdate()) && (m == po->getpostmonth()) && (y = po->getpostyear()))
					{
						viewpost(acc, p, cmnt, po->getpostid());
					}
				}
			}
		}
	}
}
void viewmemory(Account*& user, vector<Account*>acc, vector<Comment*>cmnt, vector<Post*>p, vector<Memory*>& me, int d, int m, int y)
{
	for (Post*po:p)
	{
		if (user->getid()==po->getpostedby()&&(po->getpostdate()==d&&po->getpostmonth()==m&&po->getpostyear()<y))
		{
			cout << "on this day\n";
			int g;
			g = y - po->getpostyear();
			string gap = to_string(g) + " years ago ";
			cout << gap<<endl;
			viewpost(acc, p, cmnt, po->getpostid());
			char check;
			cout << "Do you want to share this memory (y/n):";
			cin >> check;
			if (check=='y')
			{
				string description;
				cin.ignore();
				cout << "enter the description :";
				getline(cin, description);
				int checker = 0;
				for (Memory*mem:me)
				{
					if (mem->getprevpost()->getpostid() == po->getpostid())
					{
						checker = 1;
					}
				}
				if (checker==0)
				{
					Time* t = new Time(d, m, y);
					Memory* memo = new Memory(user->getid(),t,description,gap,po);
					me.push_back(memo);
				}
			}
		}
	}
}

int main()
{
	int d, m, y;
	cout << "enter the date:";
	cin >> d;
	cout << "enter the month (in numbers):";
	cin >> m;
	cout << "enter the year:";
	cin >> y;
	vector<Account*>account;
	vector<Post*>post;
	vector<Comment*>comment;
	vector<Memory*>memory = {};
	readusers(account);
	readpages(account);
	readpost(post,d,m,y);
	readcomment(comment,post);
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
	cout << "enter the id whose profile you want to check :";
	cin >> id;
	//displayprofile(id, account, post, comment,memory);
	string selectpage;
	cout << "enter the page id of the page you want to view : ";
	cin >> selectpage;
	viewpage(account, post, comment, selectpage);
	viewfriends(currentuser, account);
	viewhome(account, post, comment, d, m, y, currentuser);
	viewmemory(currentuser, account, comment, post,memory, d, m, y);
	displayprofile(currentuser->getid(), account, post, comment, memory);
}