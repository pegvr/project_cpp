/* 
 * File:   System.h
 * Author: peggyvourou
 *
 * Created on 15 Φεβρουάριος 2017, 9:35 μμ
 */

#ifndef SYSTEM_H
#define	SYSTEM_H
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

class System{
public: 
    System();
    System(const System& orig);
    ~System();
    int check_us_pass(string us, string pass);
    int check_ban(string us);
    void select_user( string type, string username, string passn);
    void Home(string type, string username, string pass);
    void signup_user(string username, string pass);
    void nav(vector<string> &loc, string &choicep, int& ii);
    void FreeBets(string username, string pass);
    void print_Sel_Nodes();
    void locationpath(vector<string> &locpath, string &chcpath,int &myi);
    void Log_History(string user, string line, int flag);
    void Visibility(int flag);
    void Rename();
    void Delete();
    void New();
    void read_file();
    vector <int> guests;
    vector <string> users_line;
    vector <int> directors;
    vector <int> punters;
    vector <int> traders;
    vector <string> users_id;
    vector <string> users_type;
    vector <string> user_name;
    vector <string> password;
    vector <string> blocked_users; 
    vector <string> location; 
    vector <string> freebets;
    vector <string> sur_name;
    vector <string> log_line;
    vector <string> hierarchy_lines;
    vector <string> nodes;
    vector <string> invisible_nodes;
    vector <string> balance;
    vector <string> name_of_nodes;
    vector <string> bet_id;
    vector <string> bet_userid;
    vector <string> bet_nodeid;
    vector <string> bet_stake;
    vector <string> bet_result;
    vector <string> bet_line;
    void print_Location(string loc, int h );
private:
    int total_cost;
    float per;
    string name;
    string data;
    int length;
    
  
   
};



class Users{
public :
    Users (string lineu,int l, int i);
    Users();
    Users(const Users& orig);
    virtual ~Users();
    string get_id();
    string get_type();
    string get_balance();
    string get_freebets();
    void print_menu(string type, string line);
    void choose_Node();
    
    
private:
    string line;
    int length;
    
};

class Guest : public Users{
public :
    Guest(){};
    Guest(string line);
    Guest(const Guest& orig);
    void print_menu();
    string get_line();
    vector <string> guest_line; 
private:
    string id;
    string lineg; 
    
};

class Director : public Users{
public : 
    Director(string line);
    Director();
    Director(const Director& orig);
    vector <string> directors_line;
    void print_menu();
private:
    string id;
    string linea;
};


class Punter : public Users{
public : 
    Punter(string line);
    Punter();
    Punter(const Punter& orig);
    void print_menu();
private:
    string id;
    string linep;
};

class Trader : public Users{
public : 
    Trader(string line);
    Trader();
    Trader(const Trader& orig);
    void print_menu();
private:
    string id;
    string linet;
};

class Wallet {
public :
    Wallet();
    ~Wallet();
private:
    int cost; 
};
#endif	/* SYSTEM_H */

