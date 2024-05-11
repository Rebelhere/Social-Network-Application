#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<fstream>
#include"account.h"
using namespace std;
class Runner
{
public:
	int d = 0, m = 0, y = 0;
	void setdate()
	{
		cout << "enter the date:";
		cin >> d;
		while (true)
		{
			if (d<=31&&d>0)
			{
				break;
			}
			else
			{
				cout << "date cannot exceed 31,neither be 0\nEnter date again:";
				cin >> d;
			}
		}
		cout << "enter the month (in numbers):";
		cin >> m;
		while (true)
		{
			if (m <= 12&&m>0)
			{
				break;
			}
			else
			{
				cout << "month cannot exceed 12,neither be 0\nEnter date again:";
				cin >> m;
			}
		}
		cout << "enter the year:";
		cin >> y;
		while (true)
		{
			if (y<=2024 && y>0)
			{
				break;
			}
			else
			{
				cout << "year cannot be more than 2024,neither be 0\nEnter date again:";
				cin >> y;
			}
		}
		cout << "system date: " << d << "/" << m << "/" << y << endl;
	}
	vector<Account*>account;
	vector<Post*>post;
	vector<Comment*>comment;
	vector<Memory*>memory = {};
	void readusers(vector<Account*>& acc)
	{
		ifstream file;
		file.open("Users.txt");
		int totaluser;
		file >> totaluser;
		string id, name1, name2, fullname;
		vector<string>frnd;
		vector<string>pageslike;
		for (int i = 0; i < totaluser; i++)
		{
			frnd = {};
			pageslike = {};
			file >> id;
			file >> name1;
			file >> name2;
			fullname = name1 + " " + name2;
			string check;
			file >> check;
			for (int i = 0; check != "-1"; i++)
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
			User* u = new User(id, fullname, frnd, pageslike);
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
			getline(file, fullname);
			Page* p = new Page(id, fullname);
			acc.push_back(p);
		}

	}
	void readpost(vector<Post*>& poo, int date, int month, int year)
	{
		ifstream file;
		file.open("Posts.txt");
		int totalposts;
		file >> totalposts;
		string postid, description, activitycontent, postedby;
		int d, m, y, activitytype;
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
				for (int i = 0; checker2 != "-1"; i++)
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
				Post* p = new Post(postid, description, postedby, t, likedby, a);
				poo.push_back(p);
			}
		}
	}
	void readcomment(vector<Comment*>& cmnt, vector<Post*>& poo)
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
			for (Post* p : poo)
			{
				if (p->getpostid() == postid)
				{
					Comment* c = new Comment(commentid, postid, userid, description);
					cmnt.push_back(c);
				}
			}
		}
	}
	void likepost(Account*& user, vector<Post*>& p)
	{
		bool check = 0;
		string selectedpost;
		cout << "enter the post you want to like :";
		cin >> selectedpost;
		for (int i = 0; i < p.size(); i++)
		{
			if (selectedpost == p[i]->getpostid())
			{
				if (p[i]->getlike().size() <= 10)
				{
					p[i]->setlikes(user->getid());
					cout << "you have liked the post successfully\n";
					check = 1;
				}
				else
				{
					cout << "the likes are exceeding 10 therefore no more likes possible.";
					check = 1;
				}
			}
		}
		if (!check)
		{
			cout << "there is no such post with this id\n";
		}
	}
	void peoplewholikes(vector<Post*>& p, vector<Account*>acc)
	{
		bool check = 0;
		string selectedpost;
		cout << "enter the post you want to see likes on :";
		cin >> selectedpost;
		for (int j = 0; j < p.size(); j++)
		{
			if (selectedpost == p[j]->getpostid())
			{

				for (int i = 0; i < p[j]->getlike().size(); i++)
				{
					cout << p[j]->getlike()[i] << " - ";
					for (Account* a : acc)
					{
						if (p[j]->getlike()[i] == a->getid())
						{
							cout << a->getname() << endl;
							check = 1;
						}
					}

				}
				if (p[j]->getlike().size() == 0)
				{
					cout << " NO LIKES ";
					check = 1;
				}
			}
		}
		if (!check)
		{
			cout << "there is no such post with this id\n";
		}
	}
	void addcomment(Account*& user, vector<Comment*>& cmnt, vector<Post*>& p)
	{
		bool check = 0;
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
				getline(cin, description);
				cout << description << endl;
				string commentid = "";
				Comment* c = new Comment(commentid, selectedpost, user->getid(), description);
				cmnt.push_back(c);
				check = 1;
			}
		}
		if (!check)
		{
			cout << "there is no such post with this id\n";
		}
	}
	void viewpost(vector<Account*>acc, vector<Post*>p, vector<Comment*>cmnt, string selectedpost)
	{
		bool check = 0;
		for (Post* po : p)
		{
			if (selectedpost == po->getpostid())
			{
				if (po->getactivitynumber() != 0)
				{
					cout << "---";
					for (Account* a : acc)
					{
						if (a->getid() == po->getpostedby())
						{
							cout << a->getname() << " is " << po->getactivitytype();
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
				cout << "\n\t'" << po->getpostdescription() << "'...(" << po->getpostdate() << "/" << po->getpostmonth() << "/" << po->getpostyear() << ")\n totallikes:" << po->getlike().size() << "\n\n";
				check = 1;
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
		if (!check)
		{
			cout << "there is no such post with this id\n";
		}
	}
	void displayprofile(string id, vector<Account*>acc, vector<Post*>p, vector<Comment*>cmnt, vector<Memory*>me)
	{
		bool check = 0;
		for (Account* a : acc)
		{
			if (id == a->getid() && a->check() == "user")
			{
				check = 1;
				cout << a->getname() << "-Time Line\n\n";
				int counter = 0;
				for (Memory* m : me)
				{
					if (m->getuserid() == a->getid())
					{
						cout << "~~~ " << a->getname() << "shared a memory ~~~...(" << m->getrepostdate() << "/" << m->getrepostmonth() << "/" << m->getrepostyear() << ")\n\t\t";
						cout << m->getdescription() << endl << "\t\t" << m->getgap() << endl;
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
					cout << "NO POST\n";
				}
			}
		}
		if (!check)
		{
			cout << "there is no such user with this id\n";
		}
	}
	void viewpage(vector<Account*>acc, vector<Post*>p, vector<Comment*>cmnt, string selectedpage)
	{
		bool check = 0;
		for (Account* a : acc)
		{
			if (a->getid() == selectedpage && a->check() == "page")
			{
				check = 1;
				cout << a->getname() << "\n";
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
		if (!check)
		{
			cout << "there is no such page with this id\n";
		}
	}
	void viewfriends(Account*& user, vector<Account*> acc)
	{
		bool check = 0;
		for (int i = 0; i < user->getfriends().size(); i++)
		{
			for (Account* a : acc)
			{
				if (a->getid() == user->getfriends()[i] && a->check() == "user")
				{
					check = 1;
					cout << user->getfriends()[i] << " - " << a->getname() << endl;
					break;
				}
			}
		}
		if (!check)
		{
			cout << "there is no one friend with this id\n";
		}
	}
	void viewhome(vector<Account*>acc, vector<Post*>p, vector<Comment*>cmnt, int d, int m, int y, Account*& user)
	{
		for (Account* a : acc)
		{
			for (int i = 0; i < user->getfriends().size(); i++)
			{
				if (a->getid() == user->getfriends()[i] && a->check() == "user")
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
				if (a->getid() == user->getlikedpages()[i] && a->check() == "page")
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
		for (Post* po : p)
		{
			if (user->getid() == po->getpostedby() && (po->getpostdate() == d && po->getpostmonth() == m && po->getpostyear() < y))
			{
				cout << "on this day\n";
				int g;
				g = y - po->getpostyear();
				string gap = to_string(g) + " years ago ";
				cout << gap << endl;
				viewpost(acc, p, cmnt, po->getpostid());
				char check;
				cout << "Do you want to share this memory (y/n):";
				cin >> check;
				if (check == 'y')
				{
					string description;
					cin.ignore();
					cout << "enter the description :";
					getline(cin, description);
					int checker = 0;
					for (Memory* mem : me)
					{
						if (mem->getprevpost()->getpostid() == po->getpostid())
						{
							checker = 1;
						}
					}
					if (checker == 0)
					{
						Time* t = new Time(d, m, y);
						Memory* memo = new Memory(user->getid(), t, description, gap, po);
						me.push_back(memo);
					}
				}
			}
			else
			{
				cout << "There is no memory\n";
			}
		}
	}
	void checkfunctionalities()
	{
		cout << "\nPress 1 to like a post \npress 2 tosee the likes of a post\npress 3 to add a comment on a post\npress 4 to view a post\npress 5 to view a page\n";
		cout << "press 6 to view friends\npress 7 to view someones profile\npress 8 to view your own profile\npress 9 to view your home page\n";
		cout << "press 10 to check for a memory\npress 11 to change user\npress any other number to exit the program:";
	}
	void releasememory(vector<Account*>& acc, vector<Comment*>& cmnt, vector<Post*>& poo, vector<Memory*>& me)
	{
		if (me.size() != 0)
		{
			for (int i = 0; i < me.size(); i++)
			{
				delete me[i]->gettime();
				delete me[i];
			}
		}
		if (poo.size() != 0 )
		{
			for (int i = 0; i < poo.size(); i++)
			{
				delete poo[i]->gettime();
				delete poo[i]->getactivity();
				delete poo[i];
			}
		}
		if (acc.size() != 0)
		{
			for (int i = 0; i < acc.size(); i++)
			{
				delete acc[i];
			}
		}
		if (cmnt.size() != 0)
		{
			for (int i = 0; i < acc.size(); i++)
			{
				delete cmnt[i];
			}
		}
		me = {};
		poo = {};
		acc = {};
		cmnt = {};
	}
	void kunfayakoon()
	{
		setdate();
		readusers(account);
		readpages(account);
		readpost(post, d, m, y);
		readcomment(comment, post);
		string selectedpost;
		string selectpage;
		char check;
		string id;
		cout << "Enter your user id:";
		cin >> id;
		Account* currentuser = nullptr;
		for (int i = 0; currentuser == nullptr; i++)
		{
			for (int i = 0; i < account.size(); i++)
			{
				if (id == account[i]->getid())
				{
					currentuser = account[i];
				}
			}
			if (currentuser == nullptr)
			{
				cout << "user id doesnot exist \n enter again : ";
				cin >> id;
			}
		}
		cout << "Enter the functionality you want to check :";
		checkfunctionalities();
		int functionality;
		cin >> functionality;
		while (functionality < 12)
		{

			switch (functionality)
			{
			case 1:
				likepost(currentuser, post);
				break;
			case 2:
				peoplewholikes(post, account);
				break;
			case 3:
				addcomment(currentuser, comment, post);
				break;
			case 4:
				cout << "enter the post you want to see the comment on : ";
				cin >> selectedpost;
				viewpost(account, post, comment, selectedpost);
				break;
			case 5:
				cout << "enter the page id of the page you want to view : ";
				cin >> selectpage;
				viewpage(account, post, comment, selectpage);
				break;
			case 6:
				viewfriends(currentuser, account);
				break;
			case 7:
				cout << "enter the id whose profile you want to check :";
				cin >> id;
				displayprofile(id, account, post, comment, memory);
				break;
			case 8:
				displayprofile(currentuser->getid(), account, post, comment, memory);
				break;
			case 9:
				viewhome(account, post, comment, d, m, y, currentuser);
				break;
			case 10:
				viewmemory(currentuser, account, comment, post, memory, d, m, y);
				break;
			case 11:
				cout << "logging out \n\nlogged out successfully\nEnter the new user id:";
				cin >> id;
				currentuser = nullptr;
				for (int i = 0; currentuser == nullptr; i++)
				{
					for (int i = 0; i < account.size(); i++)
					{
						if (id == account[i]->getid())
						{
							currentuser = account[i];
						}
					}
					if (currentuser == nullptr)
					{
						cout << "user id doesnot exist \n enter again : ";
						cin >> id;
					}
				}
				break;
			default:
				releasememory(account, comment, post, memory);
				break;
			}
			if (functionality < 12)
			{
				cout << "Do you know which functionality number to enter:(y/n)";
				cin >> check;
				while (true)
				{
					if (check == 'n')
					{
						checkfunctionalities();
						cin >> functionality;
						break;
					}
					else if (check == 'y')
					{
						cout << "enter the funtionality number:";
						cin >> functionality;
						break;
					}
					else
					{
						cout << "please answer in y or n:";
						cin >> check;
					}
				}
			}
		}
	}
};

