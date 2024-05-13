#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<fstream>
#include"account.h"
using namespace std;
class Runner
{
private:
	vector<Account*>account;
	vector<Post*>post;
	vector<Comment*>comment;
	vector<Memory*>memory = {};
	int d , m , y ;
public:
	Runner()
	{
		account = {};
		post = {};
		comment = {};
		memory = {};
		d = 0;
		m = 0;
		y = 0;
	}
	~Runner()
	{
		if (memory.size() != 0)
		{
			for (int i = 0; i < memory.size(); i++)
			{
				delete memory[i]->gettime();
				delete memory[i];
			}
		}
		if (post.size() != 0)
		{
			for (int i = 0; i < post.size(); i++)
			{
				delete post[i]->gettime();
				delete post[i]->getactivity();
				delete post[i];
			}
		}
		if (account.size() != 0)
		{
			for (int i = 0; i < account.size(); i++)
			{
				delete account[i];
			}
		}
		if (comment.size() != 0)
		{
			for (int i = 0; i < comment.size(); i++)
			{
				delete comment[i];
			}
		}
		memory = {};
		post = {};
		account = {};
		comment = {};
	}
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
	void readusers(vector<Account*>& acc)
	{
		ifstream file;
		file.open("Users.txt");
		if (file.is_open())
		{
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
			file.close();
		}
		else
		{
			cout << "could not open user file\n";
		}
	}
	void readpages(vector<Account*>& acc)
	{
		ifstream file;
		file.open("Pages.txt");
		if (file.is_open())
		{
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
			file.close();
		}
		else
		{
			cout << "could not open page file\n";
		}
	}
	void readpost(vector<Post*>& poo, int date, int month, int year)
	{
		ifstream file;
		file.open("Posts.txt");
		if (file.is_open())
		{
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
			file.close();
		}
		else
		{
			cout << "could not open post file\n";
		}
	}
	void readcomment(vector<Comment*>& cmnt, vector<Post*>& poo)
	{
		ifstream file;
		file.open("Comments.txt");
		if (file.is_open())
		{
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
			file.close();
		}
		else
		{
			cout << "could not open comment file\n";
		}
	}
	void likepost(Account*& user, vector<Post*>& p)
	{
		bool check = 0,already=0;
		string selectedpost;
		cout << "enter the post you want to like :";
		cin >> selectedpost;
		for (Post* po:p)
		{
			if (selectedpost == po->getpostid())
			{
				if (po->getlike().size() <= 10)
				{
					for (int j = 0;j<po->getlike().size() ; j++)
					{
						if(po->getlike()[j] == user->getid())
						{
							already = 1;
						}
					}
					if (!already)
					{
						po->setlikes(user->getid());
						cout << "you have liked the post successfully\n";
					}
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
		int limit = 0;
		string selectedpost;
		cout << "enter the post you want to comment on : ";
		cin >> selectedpost;
		for (int i = 0; i < p.size(); i++)
		{
			if (selectedpost == p[i]->getpostid())
			{
				for (Comment* c:cmnt)
				{
					if (c->getpostid()==selectedpost)
					{
						limit++;
					}
				}
				if (limit<10)
				{
					string description;
					cout << "enter the comment:";
					cin.ignore();
					getline(cin, description);
					cout << description << endl;
					string commentid = "";
					Comment* c = new Comment(commentid, selectedpost, user->getid(), description);
					cmnt.push_back(c);
				}
				else
				{
					cout << "the number of comments at this post have exceeded 10";
				}
				check = 1;
			}
		}
		if (!check)
		{
			cout << "there is no such post with this id\n";
		}
	}
	void viewpost(vector<Account*>acc, vector<Post*>p, vector<Comment*>cmnt, string selectedpost,bool memorypresent=0)
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
				cout << "\n\t'" << po->getpostdescription() << "'...(" << po->getpostdate() << "/" << po->getpostmonth() << "/" << po->getpostyear() << ")\n";
				check = 1;
				if (memorypresent==0)
				{
					cout << "totallikes:" << po->getlike().size() << "\n\n";
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
						cout << m->getdescription() << endl << "\t\t" << m->getgap() << endl<<"\tlikes:"<<m->getlike().size();
						viewpost(acc, p, cmnt, m->getprevpost()->getpostid(),1);
						cout << "\n\n";
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
		bool check = 0,ispage = 0;
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
				if (a->check() == "page")
				{
					ispage = 1;
				}
			}
		}
		if (ispage)
		{
			cout << "pages donot have friends";
		}
		else if (!check)
		{
			cout << "there is no one friend with this id\n";
		}
	}
	void addfriends(Account*& user, vector<Account*> acc)
	{
		bool check = 0, ispage = 0;
		string addfriend;
		cout << "enter the id you want to add as friend:";
		cin >> addfriend;
		for (int i = 0; i < user->getfriends().size(); i++)
		{
			if (addfriend == user->getfriends()[i] || addfriend==user->getid())
			{
				check = 1;
			}
		}
		for (Account*a:acc)
		{
			if (a->getid()==addfriend&&a->check()=="page")
			{
				ispage = 1;
			}
		}
		if (ispage)
		{
			cout << "cannot add page as a friend\n";
		}
		if (check)
		{
			cout << "you can not enter yourself or an already friend to the friendlist again";
		}
		if (!check && !ispage)
		{
			user->setfriends(addfriend);
			cout << "friend added successfully\n";
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
		bool checkmemory = 0;
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
						checkmemory = 1;
					}
				}
			}
		}
		if (checkmemory==0)
		{
			cout << "There is no memory\n";
		}
	}
	void viewlikesonpages(vector<Account*> acc)
	{
		string pageid;
		cout << "enter the id of page whose users you want to view:";
		cin >> pageid;
		bool check = 0, isuser = 0;
		for (Account* a : acc)
		{
			for (int i = 0; i < a->getlikedpages().size(); i++)
			{
				if (a->getlikedpages()[i] == pageid )
				{
					check = 1;
					cout << a->getid() << " - " << a->getname() << endl;
					break;
				}
			}
		}
		if (!check)
		{
			cout << "user donot have followers\n";
		}
	}
	void likepage(Account*& user, vector<Account*> acc)
	{
		bool check = 0, ispage = 0;
		string likepage;
		cout << "enter the id of page you want to follow:";
		cin >> likepage;
		for (int i = 0; i < user->getlikedpages().size(); i++)
		{
			if (likepage == user->getfriends()[i])
			{
				check = 1;
			}
		}
		for (Account* a : acc)
		{
			if (a->getid() == likepage && a->check() == "page")
			{
				ispage = 1;
			}
		}
		if (ispage)
		{
			user->setlikepages(likepage);
			cout << "followed the page successfully\n";
		}
		if (check)
		{
			cout << "already added in folloed list\n";
		}
		if (!check && !ispage)
		{
			cout << "cannot follow a user\n";
		}
	}
	//
	void likememory(Account*& user, vector<Memory*> me)
	{
		bool check = 0, already = 0;
		string selectedpost;
		cout << "enter the id of post of the memory you want to like :";
		cin >> selectedpost;
		for (Memory* m: me)
		{
			if (selectedpost == m->getprevpost()->getpostid())
			{
				if (m->getlike().size() <= 10)
				{
					for (int j = 0; j < m->getlike().size(); j++)
					{
						if (m->getlike()[j] == user->getid())
						{
							already = 1;
						}
					}
					if (!already)
					{
						m->setlikes(user->getid());
						cout << "you have liked the memory successfully\n";
					}
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
			cout << "there is no such post of memory with this id\n";
		}
	}
	void adduser(vector<Account*>& acc)
	{
		string id, name1, name2, fullname;
		id = "u" + to_string(acc.size() + 1);
		cout << "enter the first name of the user:";
		cin >> name1;
		cout << "enter the second name of the user:";
		cin >> name2;
		fullname = name1 + " " + name2;
		User* a = new User(id, fullname);
		acc.push_back(a);
		cout << "new user added with an id:" << id << "\n";
	}
	void addpage(vector<Account*>& acc)
	{
		string id, fullname;
		id = "p" + to_string(acc.size() + 1);
		cin.ignore();
		getline(cin,fullname);
		User* a = new User(id, fullname);
		acc.push_back(a);
		cout << "a new page is added with id:" << id << "\n";
	}
	void addpost(Account*& user,vector<Post*>& poo)
	{
		string postid, description, activitycontent, postedby;
		int activitytype;
		int checker;
		cout << "enter 1 if you want to have an activity\n else type any other number\ntype here:";
		cin >> checker;
		if (checker == 1)
		{
			postid = "post" + to_string(poo.size() + 1);
			cin.ignore();
			cout << "enter the description of the post:";
			getline(cin, description);
			cout<<"enter the activity number:\n 1  feeling\n2  thinking about\n3  Making\n4  celebrating\nenter here:";
			cin >> activitytype;
			cin.ignore();
			cout << "enter the content of activity:";
			getline(cin, activitycontent);
			postedby = user->getid();
		}
		else
		{
			postid = "post" + to_string(poo.size() + 1);
			cin.ignore();
			cout << "enter the description of the post:";
			getline(cin, description);
			activitytype = 0;
			activitycontent = "";
			postedby = user->getid();
		}
		Time* t = new Time(d, m, y);
		Activity* a = new Activity(activitycontent, activitytype);
		Post* p = new Post(postid, description, postedby, t, {}, a);
		poo.push_back(p);
	}
	void checkfunctionalities()
	{
		cout << "\nPress 1 to like a post \npress 2 to see the likes of a post\npress 3 to add a comment on a post\npress 4 to view a post\npress 5 to view a page\n";
		cout << "press 6 to view friends\npress 7 to view someones profile\npress 8 to view your own profile\npress 9 to view your home page\n";
		cout << "press 10 to check for a memory\npress 11 to change user\npress 12 to view followers on a page\npress 13 to add a friend\n";
		cout << "press 14 to follow/like a page\npress 15 to like a memory\npress 16 to add a new user\npress 17 to add a new page\n";
		cout<< "press 18 to add a new post\npress any other number to exit the program:";
	}
	void kunfayakoon()
	{
		const string ANSI_RESET = "\033[0m";
		const string ANSI_RED = "\033[31m";
		const string ANSI_GREEN = "\033[32m";
		const string ANSI_YELLOW = "\033[33m";
		const string ANSI_BLUE = "\033[34m";
		const string ANSI_MAGENTA = "\033[35m";
		const string ANSI_CYAN = "\033[36m";
		const string ANSI_BRIGHT_RED = "\033[91m";
		const string ANSI_BRIGHT_GREEN = "\033[92m";
		const string ANSI_BRIGHT_BLUE = "\033[94m";
		const string ANSI_BRIGHT_CYAN = "\033[96m";
		const string ANSI_BRIGHT_MAGENTA = "\033[95m";
		cout << ANSI_BRIGHT_CYAN;
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
		cout << "Welcome"<<currentuser->getname()<<"!\nEnter the functionality you want to check :";
		checkfunctionalities();
		int functionality;
		cin >> functionality;
		cout << ANSI_RESET;
		while (functionality < 19)
		{

			switch (functionality)
			{
			case 1:
				system("cls");
				cout << ANSI_BRIGHT_RED;
				cin.ignore();
				likepost(currentuser, post);
				system("pause");
				cout << ANSI_RESET;
				break;
			case 2:
				system("cls");
				cout << ANSI_CYAN;
				cin.ignore();
				peoplewholikes(post, account);
				cout << ANSI_RESET;
				system("pause");
				break;
			case 3:
				system("cls");
				cin.ignore();
				cout << ANSI_MAGENTA;
				addcomment(currentuser, comment, post);
				system("pause");
				cout << ANSI_RESET;
				break;
			case 4:
				system("cls");
				cin.ignore();
				cout << ANSI_BRIGHT_MAGENTA;
				cout << "enter the post you want to see the comment on : ";
				cin >> selectedpost;
				viewpost(account, post, comment, selectedpost);
				cout << ANSI_RESET;
				system("pause");
				break;
			case 5:
				system("cls");
				cin.ignore();
				cout << ANSI_BRIGHT_CYAN;
				cout << "enter the page id of the page you want to view : ";
				cin >> selectpage;
				viewpage(account, post, comment, selectpage);
				cout << ANSI_RESET;
				system("pause");
				break;
			case 6:
				system("cls");
				cin.ignore();
				cout << ANSI_GREEN;
				viewfriends(currentuser, account);
				system("pause");
				cout << ANSI_RESET;
				break;
			case 7:
				system("cls");
				cin.ignore();
				cout << ANSI_BRIGHT_GREEN;
				cout << "enter the id whose profile you want to check :";
				cin >> id;
				displayprofile(id, account, post, comment, memory);
				system("pause");
				cout << ANSI_RESET;
				break;
			case 8:
				system("cls");
				cin.ignore();
				cout << ANSI_BRIGHT_RED;
				displayprofile(currentuser->getid(), account, post, comment, memory);
				system("pause");
				cout << ANSI_RESET;
				break;
			case 9:
				system("cls");
				cout << ANSI_BRIGHT_CYAN;
				cin.ignore();
				viewhome(account, post, comment, d, m, y, currentuser);
				system("pause");
				cout << ANSI_RESET;
				break;
			case 10:
				system("cls");
				cin.ignore();
				cout << ANSI_BRIGHT_MAGENTA;
				viewmemory(currentuser, account, comment, post, memory, d, m, y);
				system("pause");
				cout << ANSI_RESET;
				break;
			case 11:
				system("cls");
				cout << ANSI_MAGENTA;
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
				cout<<"Welcome" << currentuser->getname() << "!\n";
				system("pause");
				cout << ANSI_RESET;
				break;
			case 12:
				system("cls");
				cin.ignore();
				cout << ANSI_BRIGHT_MAGENTA;
				viewlikesonpages(account);
				system("pause");
				cout << ANSI_RESET;
				break;
			case 13:
				system("cls");
				cout << ANSI_BRIGHT_CYAN;
				cin.ignore();
				addfriends(currentuser, account);
				system("pause");
				cout << ANSI_RESET;
				break;
			case 14:
				system("cls");
				cin.ignore();
				cout << ANSI_BRIGHT_GREEN;
				likepage(currentuser, account);
				system("pause");
				cout << ANSI_RESET;
				break;
			case 15:
				system("cls");
				cin.ignore();
				cout << ANSI_GREEN;
				likememory(currentuser, memory);
				system("pause");
				cout << ANSI_RESET;
				break;
			case 16:
				system("cls");
				cin.ignore();
				cout << ANSI_BRIGHT_MAGENTA;
				adduser(account);
				cout << ANSI_RESET;
				system("pause");
				break;
			case 17:
				system("cls");
				cout << ANSI_BRIGHT_RED;
				cin.ignore();
				addpage(account);
				system("pause");
				cout << ANSI_RESET;
				break;
			case 18:
				system("cls");
				cin.ignore();
				cout << ANSI_BRIGHT_MAGENTA;
				addpost(currentuser, post);
				system("pause");
				cout << ANSI_RESET;
				break;
			default:
				break;
			}
			if (functionality < 19)
			{
				cout << ANSI_BRIGHT_GREEN;
				system("cls");
				cin.ignore();
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
				cout << ANSI_RESET;
			}
		}
	}
};

