#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <ctime>
#include <vector>
#include <sstream>
#include <cstdlib>
#include "System.h"



using namespace std; 
/*constructor of system // store all the items from files in string vectors*/
System :: System()
{
    name = "BetAtzis";
    location.push_back(name); 
    cout << "Welcome to "<< name << endl; 
    string line;
   
    ifstream inputfile("users.csv");
    if (inputfile.is_open())
    {
        
        while(getline(inputfile,line))
        {
           
          //cout << line<< endl ;
          users_line.push_back(line);
          string tempm, temp, username,passw,bn,free,surname,bl;
          size_t pos,posit;
          if( line != "\n" )
          {
            pos = line.find("|");
        //    cout << pos <<  endl ; 
           for (int i = 0; i<pos; i++)
            {
              
                tempm += line[i];
              //  cout << tempm << endl ; 
            }
            users_id.push_back(tempm);
            
           }
        
            pos = line.find("|");
            line.erase(0,pos+1);
            pos = line.find("|");
            for (int i = 0; i<pos; i++)
            {
                username += line[i];
            }
            user_name.push_back(username);
            line.erase(0,pos+1);
            pos = line.find("|");
            for (int i = 0; i<pos; i++)
            {
                surname += line[i];
            }
            sur_name.push_back(surname);
            line.erase(0,pos+1);
            pos = line.find("|");
            for (int i = 0; i<pos; i++)
            {
                passw += line[i];
            }
            password.push_back(passw);
            line.erase(0,pos+1);
            pos = line.find("|");
           // cout << line << endl; 
            for (int i = 0; i<pos; i++)
            {
                temp += line[i];
                //cout << temp << endl;
            }
            users_type.push_back(temp);
            
            pos = line.find("|");
            line.erase(0,pos+1);
            pos = line.find("|");
           // cout << line << endl; 
            for (int i = 0; i<pos; i++)
            {
                bn += line[i];
                //cout << bn << endl;
            }
            blocked_users.push_back(bn);
            pos = line.find("|");
            line.erase(0,pos+1);
            pos = line.find("|");
            /**?*/
            for (int i =0; i<pos; i++)
            {
                bl += line[i];
            }
            balance.push_back(bl);
            line.erase(0,pos+1);
            pos = line.find("|");
           // pos = line.find("\n");
            for (int i = 0; i<pos; i++)
            {
                free += line[i];
                //cout << bn << endl;
            }
            freebets.push_back(free);
            
          
            
        
        } 
       
    }
    
    ifstream bfile("bet.csv");
    string lineb ;
    size_t posb;
    if (bfile.is_open())
    {
        
        while(getline(bfile,lineb))
        {
            lineb.erase(0,1); //// vgazei ta ""  apo  arxh 
            lineb.erase(lineb.length()-1,lineb.length()); // vgazei ta ""  apo  telos
            bet_line.push_back(lineb);
            string tm;
            posb = lineb.find("|");
            
            for (int i = 1; i < posb; i++)
            {
                tm += lineb[i];
            }
           
            bet_id.push_back(tm);
            
            lineb.erase(0,posb+1);
          
            string uid;
            for(int i = 0; i < lineb.find("|");i++)
            {
            	uid += lineb[i];
	    }
	    bet_userid.push_back(uid);
			
	    lineb.erase(0,lineb.find("|")+1);
            
	    string bnid;
	   for(int i = 0; i < lineb.find("|"); i++)
	   {
        	bnid += lineb[i];
	   }
	   bet_nodeid.push_back(bnid);
	   
			
	   lineb.erase(0,lineb.find("|")+1);
	   //cout << lineb << endl;
	   string stake;
	   for(int i = 0; i < lineb.find("|"); i++)
	   {
        	stake += lineb[i];
        	}
           bet_stake.push_back(stake);
           //cout << stake << endl;
           lineb.erase(0,lineb.find("|")+1);
           string result;
	   for(int i = 0; i < lineb.length()-1; i++)
	   {
               result += lineb[i];
	   }
           bet_result.push_back(result);
           //cout << result << endl;
			
    	}
    }
    
    length = users_id.size();
    
   
   
    ifstream hfile("hierarchy.dat");
    string lineh ;
    size_t poss;
     if (hfile.is_open())
    {
        
        while(getline(hfile,lineh))
        {
            string node;
            hierarchy_lines.push_back(lineh); //save all the lines
            
            poss = lineh.find(" ");
            //cout << "POS: " <<poss << endl; 
            for (int i = 0; i < poss; i++)
            {
                node += lineh[i];
            }
            lineh.erase(0,poss+1);
            nodes.push_back(node);
            
            
            name_of_nodes.push_back(lineh);
        }
    }
 
    
  
    
   Users **users = new Users*[length];
  //  cout << length << endl;  
    for (int i =0; i< length; i++)
    {
        if(users_type[i]=="0")
        {
          users[i] = new Guest(users_line[i]);
          guests.push_back(i);
         
        }
        if(users_type[i] == "3")
        {
            users[i] = new Director(users_line[i]);
            directors.push_back(i);
            
        }
        if(users_type[i] == "2")
        {
            users[i] = new Punter(users_line[i]);
            punters.push_back(i);
        }
        if(users_type[i]== "1")
        {
            users[i] = new Trader(users_line[i]);
            traders.push_back(i);
        }
       
    }
   
     //guest = new Guest*[guests.size()];
    

     
   
    
}

System :: System(const System& orig)
{
    
}


System :: ~System()
{
    
}

/*check username and pass for sign in */

int System :: check_us_pass(string us, string pass)
{
    int res = 10; 
    //cout << "BLA" << endl ; 
    for ( int i =0; i < length; i++)
    {
       // cout << users_type[i] << endl ; 
        if ((user_name[i] == us )&&(password[i] == pass) )
        {
            if(users_type[i]=="0")
            {
                //cout << "hoi" << endl;
                res = 0;
            }
            else if(users_type[i]=="1")
            {
                //cout << "hoi2" << endl;
                res = 1;
            }
            else if(users_type[i]=="2")
            {
                //cout << "h3oi" << endl;
                res = 2;
            }
            else if(users_type[i]=="3")
            {
                //cout << "ho4i" << endl;
                res = 3;
            }
        }
        
            
     }
        
    
    return res;
}

/*check if user is blocked*/
int System :: check_ban(string us)
{
    int res = 0;
    string ban_string;
    for (int i =0; i < length; i++)
    {
        if(user_name[i] == us)
        {
            ban_string = blocked_users[i];
            if(ban_string[0] == 'L')
            {
                res = 1; 
            }
        }
    }
    
    return res; 
}


/*select type of user and print their menu*/
void System :: select_user(string type, string username, string pass)
{
    Users u;
    string id = type; 
    string choice ;
    //cout << "hello" << endl; 
    if(type == "1" || type == "2" || type == "3")
    {
      //  cout << "hello1" << endl;
        for(int i =0 ; i< length; i++ )
        {
           // cout << "hello3" << endl;
            if((user_name[i] == username) && (password[i] == pass) )
            {
                print_Location("Menu", 0);
                u.print_menu(type, users_line[i]);
                cin >> choice;
                if( type == "1")
                {
                    
                        if (choice =="ID" || choice == "Id users") 
                        {
                            print_Sel_Nodes();
                          //cout << "Your choice is id" << endl ;
                         /* string betplacement;
                        do
                        { 
                            ifstream inpf2("hierarchy.dat");
                            string choicepa;
                                if(inpf2.is_open())
                                {
                                            vector<string> location;
                                            location.push_back(name);
                                            string levelname, choicepath, choice, oddstype;	int pr, i = 0, stop = 0;
                                            levelname = name;
                                            oddstype = "fractional";
                                            do
                                            {
                                                    cout << "Location:";
                                                    for(int ii = 0 ; ii < location.size(); ii++)
                                                    cout << "/" << location[ii];
                                                            cout << endl;
                                                    cout << "Type of odds:" << oddstype << endl;
                                                    cout << "Available choices at " << location[i++] << endl;
                                                    nav(location,choicepath,i);
                                                    locationpath(location,choicepath,i);
                                                    stop++;
                                            }while(stop < 5);
                                            choicepa = choicepath;
                                    }
                                    if(betplacement == "Y")
                                    {

                                            string bp;
                                            cout << "Do you want to bet on this?" << endl
                                                     << "Press P,to place bet or cancel to cancel your selection:";
                                            cin >> bp;
                                            if(bp == "cancel")
                                                    betplacement = "cancel";
                                            else if(bp == "P")
                                            {
                                                    int coup =0;
                                                    int fb = freebets[i].size();
                                                    string fbc = freebets[i];
                                                    string ucoupstr;
                                                    vector<string> userscoupons;
                                                    char couponpref = 'a';
                                                    if(freebets[i].size() > 1)
                                                    {
                                                            cout << "Available coupons:" << endl;
                                                            for(int jk = 0; jk < freebets[i].size();jk++)
                                                            {
                                                                    char sep = fbc[jk];
                                                                    if(!jk)
                                                                    {
                                                                            coup++;
                                                                            cout << couponpref << ". ";
                                                                    }
                                                                    if(sep != ',')
                                                                    {
                                                                            ucoupstr += sep;
                                                                            cout << sep;
                                                                    }
                                                                    if(sep == ',')
                                                                    {
                                                                            userscoupons.push_back(ucoupstr);
                                                                            ucoupstr.clear();
                                                                            couponpref++;
                                                                            cout << endl;
                                                                            cout << couponpref << ". ";
                                                                            coup++; 
                                                                    }
                                                                    //EXEI MIKRO LATHOS K EMFANIZEI ENA GRAMMA PARAPANW
                                                            }
                                                            userscoupons.push_back(ucoupstr);
                                                    }
                                                    else 
                                                            cout << "No available coupons" << endl;
                                                    cout << endl;
                                                    int pauseit = 1;
                                                    string betmoney;
                                                    double betm, bal;
                                                    do
                                                    {
                                                            int coupconf = 0;
                                                            cout << "Enter the amount of money you want to bet or the letter of the coupon:";
                                                            cin >> betmoney;
                                                            int usecoup = 0;
                                                            for(int c = 97; c < 97+coup; c++)
                                                            {
                                                                    char onec = c;
                                                                    string checkin;
                                                                    checkin += onec;
                                                                    usecoup++;
                                                                    if(betmoney == checkin)
                                                                    {
                                                                            coupconf = 1;
                                                                            break;
                                                                    }
                                                            }
                                                            double btmconv = atof(betmoney.c_str());
                                                            double blncmconv = atof(balance[i].c_str());
                                                            if(coupconf)
                                                            {
                                                                    pauseit = 1;
                                                                    cout << "You are going to use coupon " << betmoney << " with value of " << userscoupons[usecoup-1] << endl;
                                                                    //cout << coup << endl;
                                                                    string couponsleft;
                                                                    for(int cc = 0; cc < userscoupons.size(); cc++)
                                                                    {
                                                                            if(userscoupons[cc] != userscoupons[usecoup-1])
                                                                            {
                                                                                    if(userscoupons.size() == 1)
                                                                                            couponsleft += userscoupons[cc];
                                                                                    else if(cc == userscoupons.size() - 1)
                                                                                            couponsleft += userscoupons[cc];
                                                                                    else
                                                                                            couponsleft += userscoupons[cc] + ",";
                                                                            }
                                                                    }
                                                                    /*
                                                                    cout << couponsleft << endl;
                                                                    freebets[i] = couponsleft;
                                                                    string inpon;
                                                                    inpon += balance[i];
                                                                    users_line[i] = users_id[i] + "|" + user_name[i]  + "|" + sur_name[i] + "|" +  password[i] + "|" +  users_type[i] + "|" + blocked_users[i] + "|"  + inpon + "| " + freebets[i] + "|";
                                        remove("users.csv");
                                        ofstream myfileu;
                                        myfileu.open("users.csv");

                                        for (int k =0; k < users_line.size(); k++ )
                                        {
                                            myfileu << users_line[k] << endl;
                                        }
                                        */
                                        //grapse sto telos tou arxeiou bet
                                                         /*   }
                                                            else if(btmconv > blncmconv)
                                                            {
                                                                    pauseit = 0;
                                                                    cout << "The amount can't be bigger than your balance.Try again!" << endl;
                                                            }
                                                            else if(blncmconv == 0)
                                                            {
                                                                    pauseit = 1;
                                                                    cout << "You have no balance.Please go at 'My Account' and deposit into your account." << endl;
                                                            }
                                                            else if(btmconv < blncmconv)
                                                            {


                                                                    double newbalance = blncmconv - btmconv;

                                                                    ostringstream strs;
                                                                    strs << newbalance;
                                                                    string inpon = strs.str();
                                                                    cout << inpon << endl;
                                                                    balance[i] = inpon;
                                        users_line[i] = users_id[i] + "|" + user_name[i]  + "|" + sur_name[i] + "|" +  password[i] + "|" +  users_type[i] + "|" + blocked_users[i] + "|"  + balance[i] + "| " + freebets[i] + "|";
                                        remove("users.csv");
                                        ofstream myfileu;
                                        myfileu.open("users.csv");

                                        for (int k =0; k < users_line.size(); k++ )
                                        {
                                            myfileu << users_line[k] << endl;
                                        }


                                        int bidconv = atoi(bet_id[bet_id.size()-1].c_str()) + 1;
                                        ostringstream rewid;
                                                                    rewid << bidconv;
                                                                    string nbid = rewid.str();
                                        bet_id.push_back(nbid);
                                                                    bet_userid.push_back(users_id[i]);
                                                                    bet_nodeid.push_back(choicepa);
                                                                    bet_stake.push_back(betmoney);
                                                                    bet_result.push_back("-");
                                                                    int posbp = bet_id.size() -1;
                                                                    //vale to kainourgio pontarisma sto arxeio bet
                                                                    remove("bet.csv");
                                        ofstream mybetfile;
                                        mybetfile.open("bet.csv");
                                        bet_line.push_back(bet_id[posbp] + "|" + bet_userid[posbp] + "|" + bet_nodeid[posbp] + "|" + bet_stake[posbp] + "|" + bet_result[posbp]);
                                        for (int k =0; k < bet_id.size(); k++ )
                                        {
                                            myfileu << bet_line[k] << endl;
                                        }
                                                            }



                                                    }while(!pauseit);
                                            }
                                    }
                                    cout << "Do you want to place any bet?" << endl
                                             << "Press Y if you want or any other button to exit:";
                                    cin >> betplacement;
                                    if(betplacement == "Y")
                                            cout << "Your available balance is " << balance[i] << endl;
                            }
                            while(betplacement == "Y");*/
                          cout << "Choose again what you want to do " << endl ;
                          Log_History(username,"ID", 0);
                          select_user("1", username, pass);

                        }
                        else if (choice =="H" || choice == "Home") 
                        {
                            cout << "Your choice is H" << endl ; 
                            Home(type,username,pass);
                            Log_History(username,"Home", 0);
                        }
                        else if (choice == "T")
                        {
                            cout << "Your choice is T" << endl;
                            Log_History(username,"T", 0);
                        }
                        else if (choice == "A")
                        {
                            print_Location("My Account",0);
                            cout << "Your choice is A" << endl;
                            Log_History(username,"My Account", 0);
                            ifstream ufile("users.csv");
                            if(ufile.is_open())
                            {
                                int br1,br2,br3;
                                string uline;


                                        while(getline(ufile,uline))
                                        {
                                                cout << uline << endl;
                                        }
                                }
                            cout << "Your choice is A" << endl;
                            cout << "Player:" << user_name[i] << endl
                                         << "Available balance:" << endl
                                         << "Available coupons:" << endl << endl;

                                cout << "Pick one of the available choices below" << endl
                                         << "R(Rename), to change username" << endl
                                         << "P(Password), to change password" << endl
                                         << "B(Bets), to see your bet history" << endl
                                         << "D(Deposit), to update your balance" << endl
                                         << "Select:";
                            string choi;	
                                cin >> choi;
                                if(choi == "P")
                                {
                                         print_Location("Password",0);
                                         Log_History(username,"Reset Password", 0);
                                        int correct = 0;
                                        string passw;
                                        do
                                        {
                                                string newpass, newpasscheck;
                                                cout << "Enter your new password:";
                                                cin >> newpass;
                                                cout << "Confirm your new password:";
                                                cin >> newpasscheck;
                                                if(newpass.length() == newpasscheck.length())
                                                {
                                                        for(int ii = 0; ii < newpass.length(); ii++)
                                                        {
                                                                if(newpass[ii] == newpasscheck[ii])
                                                                {
                                                                    
                                                                        correct = 1;
                                                                        
                                                                }
                                                                else
                                                                {
                                                                        correct = 0;
                                                                        break;
                                                                }
                                                        }											
                                                }
                                                else
                                                        correct = 0;
                                                if(!correct)
                                                        cout << "Passwords don't match.Please try again!" << endl;
                                                else
                                                {
                                                    passw = newpass;
                                                }
                                        }while(!correct);
                                        password[i] = passw;
                                        users_line[i] = users_id[i] + "|" + user_name[i]  + "|" + sur_name[i] + "|" + password[i] + "|" +  users_type[i] + "|" + blocked_users[i] + "|" + balance[i]  + "| " + freebets[i] +  "|";
                                        remove("users.csv");
                                        ofstream myfileu;
                                        myfileu.open("users.csv");
                                        
                                        for (int k =0; k < users_line.size(); k++ )
                                        {
                                            myfileu << users_line[k] << endl;
                                        }
                                        select_user("1", username, password[i]);
                                        
                                }
                                else if(choi == "R")
                                {
                                        print_Location("Rename",0);
                                         Log_History(username,"Reset name", 0);
                                        int nexists = 0;
                                        string newusername;
                                        do
                                        {
                                                cout << "Enter your new username:";
                                                cin >> newusername;
                                                for(int fus = 0; fus < user_name.size() ; fus++)
                                                {
                                                        string ncomp = user_name[fus];
                                                        if(ncomp == newusername)
                                                        {
                                                                cout << "This username already exists.Please try again." << endl;
                                                                nexists = 1;
                                                                break;
                                                        }
                                                        else
                                                                nexists = 0;
                                                }
                                        }while(nexists == 1);
                                        user_name[i] = newusername;
                                        users_line[i] = users_id[i] + "|" + user_name[i]  + "|" + sur_name[i] + "|" +  pass + "|" +  users_type[i] + "|"+ blocked_users[i] + "|" + balance[i]  + "| " + freebets[i] +  "|";
                                        remove("users.csv");
                                        ofstream myfileu;
                                        myfileu.open("users.csv");
                                        
                                        for (int k =0; k < users_line.size(); k++ )
                                        {
                                            myfileu << users_line[k] << endl;
                                        }
                                        select_user("1", user_name[i], pass);
                                }
                                else if(choi == "D")
                                {
                                        print_Location("Deposit",0);
                                         Log_History(username,"Update Balance", 0);
                                        string balanceup;
                                        cout << "Enter the amount of money you want to update your balance with:";
                                        cin >> balanceup;
                                        //pros8ese sto palio balance to kainourgio
                                }
                                else if(choi == "B")
                                {
                                        print_Location("Bet",0);
                                        vector<string> userbets,userbetbids,userbetres;
                                         Log_History(username,"Bet", 0);
                                        ifstream betfile("bet.csv");
                                    if(betfile.is_open())
                                    {
                                        int br1,br2,br3;
                                        string betline;


                                                while(getline(betfile,betline))
                                                {
                                                        string tmpstr,gtusrid,gtusrbetid,bid,betbidtemp,betbid,betres;
                                                        br1 = betline.find("|");
                                                        for(int ii = br1+1; ii < betline.length(); ii++)
                                                                tmpstr += betline[ii];
                                                        br2 = tmpstr.find("|");

                                                        for(int ii = 0; ii < br2; ii++)
                                                                gtusrid += tmpstr[ii];
                                                        if(gtusrid == users_id[i])
                                                        {
                                                                //cout << tmpstr << endl;
                                                                for(int ii = br2+1; ii < tmpstr.length(); ii++)
                                                                        gtusrbetid += tmpstr[ii];
                                                                for(int ii = 0; ii < gtusrbetid.find("|"); ii++)
                                                                {
                                                                        if(gtusrbetid.find(" ") == 0 && ii > 0)				//ena bet id exei keno kai svhnoume parakamptoume to keno me auto
                                                                                bid += gtusrbetid[ii];
                                                                        if(gtusrbetid.find(" ") != 0)
                                                                                bid += gtusrbetid[ii];
                                                                }
                                                                for(int ii = gtusrbetid.find("|")+1; ii < gtusrbetid.length(); ii++)
                                                                        betbidtemp += gtusrbetid[ii];
                                                                for(int ii = 0; ii < betbidtemp.find("|"); ii++)
                                                                        betbid += betbidtemp[ii];
                                                                for(int ii = betbidtemp.find("|")+1; ii < betbidtemp.find("|")+2; ii++)
                                                                        betres += betbidtemp[ii];
                                                                //cout << betbid  << " " << betres << endl;
                                                                userbetbids.push_back(betbid);
                                                                userbetres.push_back(betres);
                                                                userbets.push_back(bid);
                                                                //cout << gtusrbetid << endl;	
                                                        }
                                                }

                                        }
                                        vector <string> showusersbets;
                                        for(int x = 0; x < userbets.size() ; x++)
                                        {
                                                string usrstrip = userbets[x];
                                                ifstream hfile("hierarchy.dat");
                                            if(hfile.is_open())
                                            {
                                                string hline;
                                                        while(getline(hfile,hline))
                                                        {
                                                                int fsp = hline.find(" ");

                                                                int xfound = 0;
                                                                for(int xi = 0; xi < fsp; xi++)
                                                                {
                                                                        if(usrstrip[xi] == hline[xi])
                                                                                xfound = 1;
                                                                        else
                                                                        {
                                                                                xfound = 0;
                                                                                break;
                                                                        }
                                                                }
                                                                //cout << fsp << " " << usrstrip.size() << " " << xfound << " " << hline << endl;
                                                                if(xfound)
                                                                {
                                                                        string showbet;
                                                                        for(int xi = hline.find(" ")+1; xi < hline.length(); xi++)
                                                                                showbet += hline[xi];
                                                                        showusersbets.push_back(showbet);
                                                                }
                                                        }
                                                }
                                        }
                                        cout << "++++++++++++++++BET HISTORY++++++++++++++++" << endl;
                                        for(int iii = 0 ; iii < showusersbets.size(); iii++)
                                        {
                                                for(int beutify = 0; beutify < iii; beutify++)
                                                        cout << " ";
                                                cout << showusersbets[iii] << endl;
                                        }
                                        for(int iii = 0 ; iii < userbetbids.size(); iii++)
                                        {
                                                for(int iiii = 0 ; iiii < showusersbets.size()+1;iiii++)
                                                        cout << " ";
                                                cout << "You have bid: " << userbetbids[iii] << " on this one." << endl;
                                                for(int iiii = 0 ; iiii < showusersbets.size()+2;iiii++)
                                                        cout << " ";
                                                cout << "And the result is: " << userbetres[iii] << endl;
                                        }
                                         select_user("1", username, pass);
                                }
                           }
                           else if (choice == "X")
                           {
                            cout << "Your choise is X" << endl;
                            exit; 
                           }
                           else
                           {
                            choice = "F";
                            cout << "You hace entered wrong choice. Please try again"<< endl ;
                            select_user("1", username, pass);
                           }

                     
                 }
                
                else if (type == "2")
                {
                      
                        if (choice =="ID") 
                        {
                             Log_History(username,"ID", 0);
                          print_Sel_Nodes();
                          cout << "Choose again what you want to do " << endl ;

                          select_user("2", username, pass);

                        }
                        else if (choice =="H" || choice == "Home")  
                        {
                             Log_History(username,"Home", 0);
                            cout << "Your choice is H" << endl ; 
                             Home(type,username,pass);
                        }
                        else if (choice == "T")
                        {
                            Log_History(username,"T", 0);
                            cout << "Your choice is T" << endl;
                        }
                        else if (choice == "B")
                        {
                            Log_History(username,"Bet", 0);
                            print_Location("Bet",0);
                            cout << "Your choice is B" << endl;                               
                            int BETAMOUNT = 10;												//posa stoixhmata 8es na dei3ei.Default 20,oso 8es gia testing
                            ifstream bfl("bet.csv");
                            if(bfl.is_open())
                            {
                                vector<string> betlines;
                                vector<string> userbets,userbetbids,userbetres,useridb;
                                string btln;
                                int remove = 0;
                                while(getline(bfl,btln))
                                {
                                        if(remove)
                                                betlines.push_back(btln);
                                        remove++;
                                        }
                                        if(betlines.size() >= BETAMOUNT)
                                        {
                                                for(int bi = betlines.size()-BETAMOUNT ; bi < betlines.size(); bi++)
                                                {
                                                        //cout << betlines[bi] << endl;

                                                        string tmpstr,gtusrid,gtusrbetid,bid,betbidtemp,betbid,betres,betline;
                                                        betline = betlines[bi];
                                                        for(int ii = betline.find("|")+1; ii < betline.length(); ii++)
                                                                tmpstr += betline[ii];
                                                        for(int ii = 0; ii < tmpstr.find("|"); ii++)
                                                                gtusrid += tmpstr[ii];

                                                        for(int ii = tmpstr.find("|")+1; ii < tmpstr.length(); ii++)
                                                                gtusrbetid += tmpstr[ii];
                                                        for(int ii = 0; ii < gtusrbetid.find("|"); ii++)
                                                        {
                                                                if(gtusrbetid.find(" ") == 0 && ii > 0)				//ena bet id exei keno kai svhnoume parakamptoume to keno me auto
                                                                        bid += gtusrbetid[ii];
                                                                if(gtusrbetid.find(" ") != 0)
                                                                        bid += gtusrbetid[ii];
                                                        }
                                                        for(int ii = gtusrbetid.find("|")+1; ii < gtusrbetid.length(); ii++)
                                                                betbidtemp += gtusrbetid[ii];
                                                        for(int ii = 0; ii < betbidtemp.find("|"); ii++)
                                                                betbid += betbidtemp[ii];
                                                        for(int ii = betbidtemp.find("|")+1; ii < betbidtemp.find("|")+2; ii++)
                                                                betres += betbidtemp[ii];
                                                        //cout << betbid  << " " << betres << " " << bid << " " << gtusrid << endl;
                                                        useridb.push_back(gtusrid);
                                                        userbetbids.push_back(betbid);
                                                        userbetres.push_back(betres);
                                                        userbets.push_back(bid);

                                                }

                                                cout << "++++++++++++++++++LAST " << BETAMOUNT << " BETS++++++++++++++++++" << endl;
                                                for(int sho = 0 , ii = 0; sho < userbetbids.size(); sho++,ii+=5)
                                                {
                                                        cout << "User:" << useridb[sho] << " bid " << userbetbids[sho] << " on this bet,with result " << userbetres[sho] << endl;

                                                        string usrstrip = userbets[sho];
                                                        ifstream hfile("hierarchy.dat");
                                                    if(hfile.is_open())
                                                    {
                                                        string hline;
                                                                while(getline(hfile,hline))
                                                                {
                                                                        int fsp = hline.find(" ");

                                                                        int xfound = 0;
                                                                        for(int xi = 0; xi < fsp; xi++)
                                                                        {
                                                                                if(usrstrip[xi] == hline[xi])
                                                                                        xfound = 1;
                                                                                else
                                                                                {
                                                                                        xfound = 0;
                                                                                        break;
                                                                                }
                                                                        }
                                                                        //cout << fsp << " " << usrstrip.size() << " " << xfound << " " << hline << endl;
                                                                        if(xfound)
                                                                        {
                                                                                string showbet;
                                                                                for(int xi = hline.find(" ")+1; xi < hline.length(); xi++)
                                                                                {
                                                                                        showbet += hline[xi];
                                                                                }
                                                                                for(int xi = 0; xi < hline.find(" "); xi++)	
                                                                                        cout << " ";
                                                                                cout << showbet << endl;
                                                                        }
                                                                }
                                                        }
                                                        //	cout << userbets[sho] << endl;
                                                }
                                        }
                                }
                                select_user("2", username, pass);
                        }
                        else if (choice == "F")
                        {
                            Log_History(username,"Freebets", 0);
                            cout << "Your choise is F" << endl;
                            FreeBets(username,pass);
                            cout << "Choose again what you want to do " << endl ;
                            select_user("2", username, pass);
                        }
                        else if (choice == "X")
                        {
                             cout << "Your choise is X" << endl;
                             exit; 
                        }
                        else
                        {
                            choice = "N";
                            
                            cout << "You hace entered wrong choice. Please try again"<< endl ;
                            select_user("2", username, pass);
                        }

                  
                }
                else if (type == "3")
                {
                   
                    
                        if (choice =="ID") 
                        {
                          //cout << "Your choice is id" << endl ;
                          print_Sel_Nodes();
                          cout << "Choose again what you want to do " << endl ;
                         Log_History(username,"ID", 0);
                         select_user("3", username, pass);

                        }
                        else if (choice =="H" || choice == "Home") 
                        {
                            cout << "Your choice is H" << endl ; 
                            Log_History(username,"Home", 0);
                            Home(type,username,pass);
                        }
                        else if (choice == "T")
                        {
                            cout << "Your choice is T" << endl;
                            Log_History(username,"T", 0);
                        }
                        else if (choice == "B")
                        {
                            
                        }
                        else if (choice == "F")
                        {
                            cout << "Your choise is F" << endl;
                            FreeBets( username,  pass);
                            Log_History(username,"Freebets", 0);
                            cout << "Choose again what you want to do " << endl ;
                            select_user("3", username, pass);
                        }
                        else if (choice == "S")
                        {
                            cout << "Your choice is S" << endl;
                        }
                        else if (choice == "L"|| choice == "Logs")
                        {
                            cout << "Your choice is L" << endl;
                            Log_History(username,"Logs", 1);
                            select_user("3", username, pass);
                        }
                        else if (choice == "U" || choice == "Users")
                        {
                            cout << "Your choise is U" << endl;
                            Log_History(username, "UsersSupport", 0);
                            string useradmc;
                            cout << "Select one of the choices below" << endl
                            	 << "V(View),to show the array of users" << endl
                            	 << "S(Search),to search for a user" << endl
                            	 << "L(Lock),to change the ban state of a user" << endl
                            	 << "Select:";
                            cin >> useradmc;
                            cout << endl;
                           
                            if(useradmc == "V")
                            {
                            	for(int i=0; i < users_line.size(); i++)
                                {
                                    cout << users_line[i] << endl; 
                                }
                            }
                             else if(useradmc == "S")
                            {
                                string un;
				cout << "Search for a user." << endl;
			        cout << "Enter user's username:" << endl;
				cin >> un;
								
                                for(int ii = 0; ii < user_name.size(); ii++)
                                {
                                        string convus = user_name[ii];
                                        if(convus == un)
                                        {
                                                cout << convus << endl;
                                        }
                                        else
                                        {
                                                int foundit = 0;
                                                for(int j = 0; j < (convus.length() - un.length())+1; j++)
                                                {
                                                        int gotit = 0;
                                                        for(int jj = j; jj < un.length()+j; jj++)
                                                        {
                                                                if(convus[jj] == un[jj-j])
                                                                        gotit++;
                                                                else
                                                                        break;
                                                        }
                                                        if(gotit == un.length())
                                                        {
                                                                foundit = 1;
                                                                break;
                                                        }											
                                                }
                                                if(foundit)
                                                        cout << convus << endl;
                                        }
                                }
                        }
                        else if(useradmc == "L")
                        {
                                string banun,lockus;
                                int wrinp = 0;;
                                do
                                {
                                        cout << "Enter the username of the user that you want to lock the acount of:";
                                        cin >> banun;
                                        for(int ii = 0; ii < user_name.size(); ii++)
                                        {
                                                string strun = user_name[ii];
                                                if(banun == user_name[ii])
                                                {
                                                        string struid = users_type[ii];
                                                        if(struid == "3")
                                                        {
                                                                wrinp = 1;
                                                                cout << "You can't lock the account of an admin!" << endl;
                                                                break;
                                                        }
                                                        else
                                                        {
                                                                wrinp = 0;
                                                                lockus = strun;
                                                                cout << "Account " << strun << " is now locked." << endl;
                                                                blocked_users[ii] = "L";
                                                                users_line[ii] = users_id[ii] + "|" + user_name[ii]  + "|" + sur_name[ii] + "|" +  password[ii] + "|" +  users_type[ii] + "|"+ blocked_users[ii] + "|" + balance[ii]  + "| " + freebets[ii] +  "|";
                                                                remove("users.csv");
                                                                ofstream myfile;
                                                                myfile.open("users.csv");
                                                                for(int k=0; k < users_line.size(); k++)
                                                                { 
                                                                    myfile << users_line[k] << endl;
                                                                }
                                                                
                                                              
                                                        }
                                                        select_user("3", username, pass);
                                                }
                                                else
                                                {
                                                        wrinp = 2;
                                                }
                                        }
                                        if(wrinp == 2)
                                        {
                                                cout << "You have entered a wrong username." << endl
                                                                 << "Please try again!" << endl;
                                        }
                                }while(wrinp);
                                

                        }
                            
                            select_user("3", username, pass);
                        }
                        else if (choice == "V"|| choice == "Visibility")
                        {
                            int flag;
                            Log_History(username,"Visibility", 0);
                            cout << "Your choice is V" << endl;
                            cout << "If you want to make a node visible again pess 1 else press 0"<< endl;
                            cin >> flag;
                            Visibility(flag);
                            select_user("3", username, pass);
                        }
                        else if (choice == "R" || choice == "Rename")
                        {
                            cout << "Your choice is R" << endl;
                            Log_History(username,"Rename", 0);
                            Rename();
                            select_user("3", username, pass);
                            
                        }
                        else if (choice == "N")
                        {
                            cout << "Your choise is N" << endl;
                            Log_History(username,"NewNode", 0);
                            New();
                            select_user("3", username, pass);
                        }
                        else if (choice == "C")
                        {
                            cout << "Your choise is C" << endl;
                        }
                        else if (choice == "D")
                        {
                            cout << "Your choise is D" << endl;
                            Log_History(username,"Delete", 0);
                            Delete();
                            select_user("3", username, pass);
                        }
                        else if (choice == "X")
                        {
                            cout << "Your choise is X" << endl;
                            exit;
                        }
                        else
                        {
                            choice = "J";
                            cout << "You hace entered wrong choice. Please try again"<< endl ;
                            select_user("3", username, pass);
                        }

                    
                }
                
            }
        }
    
    }
    else if( type == "0")
    {
        print_Location("Menu", 0);
        u.print_menu(type, "0");
        string choice; 
        cin >> choice; 
        
          if (choice =="ID") 
          {
            print_Sel_Nodes();
            cout << "Choose again what you want to do " << endl ;
            
            select_user("0", "0", "0");
            
          }
          else if (choice =="H" || choice == "Home") 
          {
            cout << "Your choice is H" << endl ;
            Home("0","guest", "guest");
            
            
          }
          else if (choice == "T" || choice == "Toggle")
          {
            cout << "Your choice is T" << endl;
          }
          else if (choice == "X")
          {
            cout << "Your choise is X" << endl;
            exit;
          }
          else
          {
            choice = "F";
            cout << "You hace entered wrong choice. Please try again"<< endl ;
            select_user("0", "0" , "0");
          }
        
        
    }
}



void System :: FreeBets(string username, string pass)
{
    print_Location("Freebets", 0);
    string user, fb;
    fstream inputfile;
    inputfile.open("users.csv", fstream::in | fstream::out | fstream::app);
       
    cout << "Give us the name of user you want to give him a freebet" << endl;
    cin >> user; 
    
    for ( int i =0; i < user_name.size(); i++)
    {
        
            if(user_name[i] == user)
            {
                cout << "We found your user!" << endl;
                //cout << users_line[i] << endl;
                cout << "Give us the freebet you want" << endl; 
                cin >> fb;
                if(freebets[i] != " ")
                {
                    fb = freebets[i] + "," + fb;
                }
                freebets[i] = fb; 
                users_line[i] = users_id[i] + "|" + user_name[i]  + "|" + sur_name[i] + "|" +  password[i] + "|" +  users_type[i] + "|" + blocked_users[i] + "|"+ balance[i]  + "|" + freebets[i] +  "|";
                //inputfile << users_id[i] << "|" <<  user_name[i] << "|" << sur_name[i] <<"|" <<  pass << "|" <<  users_type[i] << "| " << "| "  << "| " << freebets[i] <<   "|" << endl ;
            }
           /* else
            {
                string bla;
                cout << "the username is not in our list! try again or press exit " << endl;
                cin >> bla;
                if(bla == "exit")
                {
                    return;
                }
                FreeBets( username,  pass);
                
            }*/
       
    }
    
    remove("users.csv");
    ofstream myfile;
    myfile.open("users.csv");
    for ( int i =0 ; i < users_line.size(); i++)
    {
        //cout << users_line[i] << endl; 
        myfile << users_line[i] << endl;
    }
    myfile.close();
    
}

/*Admin managment*/

void System :: read_file() // read log file and store it
{
    //ifstream myfile;
    string line1;
    ifstream myfile("log.csv");
    if (myfile.is_open())
    {
        
        while(getline(myfile,line1))
        {
            log_line.push_back(line1);
        }
        
    }
    
  
            
}

void System ::Log_History(string user, string line, int flag)
{
    fstream myfile;
    string linel;
    myfile.open("log.csv", fstream::in | fstream::out | fstream::app);
    if (flag == 0)
    {
        myfile << "User " << user << "has been in " << line << endl;
        read_file();
    }
    else if(flag == 1)
    {
        int size, s;
        vector <string> help;
        myfile << "Admin " << user << "has been in " << line << endl;
        read_file();
        for (int k = 0 ; k < log_line.size(); k++)
        {
            help.push_back(log_line[k]);
        }
        
        size = log_line.size();
        //cout << log_line.size() << endl ; 
        if(log_line.size() < 25)
        {
            for(int i= 0; i < log_line.size(); i++)
            {
                cout << log_line[i] << endl;
            }
        }
        else if (log_line.size() >= 25) //print 25 last actions from log file
        {
            s = size - 25; 
            help.erase(help.begin(),help.begin()+ s);
            for ( int l; l < help.size(); l++)
            {
                cout << help[l] << endl ; 
            }
            
                
        }
        
    }
    
    myfile.close();
}


void System :: Visibility(int flag)
{
    if (flag == 0)
    {
        string choice;
        cout << "Choose what node you want to make invisible" << endl;
        cout << "the hierarchy is: " << endl; 
        print_Location("Visibility", 0);


        for(int i =0; i < hierarchy_lines.size(); i++)
        {
          cout <<  hierarchy_lines[i]  << endl ; 
        }

        cin >> choice;
        for(int i =0; i< nodes.size(); i++)
        {   
             if (choice == nodes[i])
             {
                 remove("hierarchy.dat");
                 ofstream myfile;
                 myfile.open("hierarchy.dat");
                 for ( int k =0 ; k < nodes.size(); k++)
                 {
                     if(k ==i)
                     {
                         invisible_nodes.push_back(nodes[i]);
                     }
                     else
                     {
                         cout << "hello" << endl;
                         myfile << hierarchy_lines[k]<< endl;
                     }
                 }


             }
        }
    }
    else if(flag ==1)
    {
        string choice;
        cout << "your invisible nodes are " << endl;
        if (invisible_nodes.size() == 0)
        {
            cout << "OOps you have not any invisible node" << endl;
            return;
        }
        else
        {
            for(int i =0; i < invisible_nodes.size(); i++)
            {
                cout << invisible_nodes[i] << endl;
            }
        }
        
        cout << "choose from above" << endl;
        cin >> choice;
        int size = invisible_nodes.size();
        for (int j=0; j <size ; j++ )
        {
            if(choice == invisible_nodes[j])
            {
                invisible_nodes[j] = " ";
            }
        }
        
        for(int i =0; i< nodes.size(); i++)
        {   
             if (choice == nodes[i])
             {
                 remove("hierarchy.dat");
                 ofstream myfile;
                 myfile.open("hierarchy.dat");
                 for ( int j=0; j < invisible_nodes.size(); j++)
                 {
                     for(int k=0; k <nodes.size(); k++)
                     {
                         if (nodes[k] == invisible_nodes[j])
                         {
                             
                         }
                         else
                         {
                             myfile << hierarchy_lines[k] << endl; 
                         }
                     }
                 }


             }
        }
        
           
    }
   
    
}


void System :: Rename()
{
    string choice, name, cancel;
    print_Location("RenameNode", 0);
    cout << "Choose the node you want to rename" << endl;
    cout << "the hierarchy is: " << endl; 
    


    for(int i =0; i < hierarchy_lines.size(); i++)
    {
     cout <<  hierarchy_lines[i]  << endl ; 
    }

    cin >> choice;
    for(int i = 0; i < nodes.size(); i++)
    {
        if(choice == nodes[i])
        {
            cout << "write the name you want to give in the node" << endl;
            cin >> name;
            cout << "If you want to cancel, press cancel" << endl;
            cin >> cancel ; 
            if(cancel == "cancel")
            {
                return;
            }
            name_of_nodes[i] = name; 
            hierarchy_lines[i] = nodes[i] +" " + name_of_nodes[i];
            remove("hierarchy.dat");
            ofstream myfile;
            myfile.open("hierarchy.dat");
            for(int k=0; k < hierarchy_lines.size(); k++)
            {
                myfile << hierarchy_lines[k] << endl;
            }
            
            
        }
       
    }
    
}

void System :: New()
{
    string choice, cancel, namen, line, name;
    print_Location("NewNode", 0);
    cout << "Choose the previous node of the new you want to write" << endl;
    cout << "the hierarchy is: " << endl; 
    


    for(int i =0; i < hierarchy_lines.size(); i++)
    {
     cout <<  hierarchy_lines[i]  << endl ; 
    }

    cin >> choice;
    
    
    for (int i =0; i < hierarchy_lines.size(); i++)
    {
        if(nodes[i] == choice)
        {
           cout<<"Enter he name of node you want to create"<<endl;
           cin >> namen; 
           
           
           return; 
            
        }
    }
    
}

void System :: Delete()
{
    string choice, name , yn, cancel;
    print_Location("DeleteNode", 0);
    cout << "Choose the node you want to delete" << endl;
    cout << "the hierarchy is: " << endl;
    
    for(int i =0; i < hierarchy_lines.size(); i++)
    {
     cout <<  hierarchy_lines[i]  << endl ; 
    }

    cin >> choice;
    cout << "Are you sure you want to delete node " << choice << "?" << endl ;
    cout << "Y/N ? " << endl; 
    cin >> yn;
    if(yn == "N")
    {
        cout << "OK , go back to menu" << endl; 
        return;
    }
    
    for ( int i = 0 ; i < hierarchy_lines.size(); i++)
    {
        if(choice == nodes[i])
        {
            cout << "if you want to cancel, press cancel"<< endl ; 
            cin >> cancel; 
            if(cancel == "cancel")
            {
                return;
            }
            hierarchy_lines.erase(hierarchy_lines.begin()+ i);
            name_of_nodes.erase(name_of_nodes.begin()+i);
            nodes.pop_back();
            
            
            remove("hierarchy.dat");
            ofstream myfile;
            myfile.open("hierarchy.dat");
            for(int k=0; k < hierarchy_lines.size(); k++)
            {
                hierarchy_lines[k] = nodes[k] + " " + name_of_nodes[k]; 
                myfile << hierarchy_lines[k] << endl;
            }
            
            
        }
    }
    
}



/* registry of new user */

void System :: signup_user(string username, string pass)
{
    int id; 
    string ids , name, surname = " " ; 
    fstream inputfile;
    inputfile.open("users.csv", fstream::in | fstream::out | fstream::app); // read and write file
    for(int i; i < user_name.size(); i++)
    {
        do
        {
            if(user_name[i] == username)
            {
                cout << "The username is already used" << endl;
                cout << "Try again " << endl; 
                cout << "username: " <<  endl ; 
                cin >> username;

            }
        }while(user_name[i] == username);
    }
    
    cout << "Please give us your name" << endl ; 
    cin >> name ; 
    cout << "Please give us your surname else press 0" << endl ; 
    cin >> surname ; 
    if(surname == "0")
    {
        surname = " ";
    }
    name = name + " " + surname; 
    
    std :: ostringstream convert; 
    id = rand() % 100;  // random id
    convert << id; 
    ids = convert.str();  // convert to string 
    srand (time(NULL));
    
    for(int i; i < users_id.size(); i++)
    {
        if(users_id[i] == ids)
        {
            do
            {
                std :: ostringstream convert; 
                id = rand() % 100; 
                convert << id; 
                ids = convert.str();
            }while(users_id[i] == ids);
        }
    }
    
    user_name.push_back(username);
    password.push_back(pass);
    users_id.push_back(ids);
    inputfile << ids << "|" <<  username << "|" << name <<"|" <<  pass << "|" <<  "1" << "| " << "| "  << "| " << "|" << endl ; //write it on file
    inputfile.close();
    
}


/*path location */
void System :: print_Location(string loc, int h)
{
    string locat;
    int size; 
    size = location.size();
    for (int j=0; j < size; j++)
    {
        if (location[j] == loc )
        {
            for(int i =size; i > j ; i--)
            {
               location.pop_back(); //if the place is already in path then delete all until this place
            }
            h=1;
        }
       
    }
        
        
    if ( h == 0)
    {
        location.push_back(loc);
        for(int i = 0; i < location.size(); i++)
        { 
            locat += "/" + location[i]; 
           
        }
        cout << locat << endl ; 
    }
    else if (h ==1)
    {
        string locat;
        location.push_back(loc);
        for(int i = 0; i < location.size(); i++)
        {
            locat += "/" + location[i]; 
            
        }
         cout << locat << endl ;
    }
    //cout << locat << endl ; 
}



/*print the Hierarchy */
void System::nav(vector<string> &loc, string &choicep, int &ii)
{
	ifstream myfile("hierarchy.dat");
	if(myfile.is_open())
	{
		string line, mychoo;
		int space;
		string corinput;
		while(getline(myfile,line))
		{
			string tmps;
			space = line.find(" ");
			//cout << choicep << endl;
			////pare olh th grammh me tis epiloges////
			for(int i = space-1; i < line.length(); i++)
				tmps += line[i];
			//////////////////////////////////////////
			if((choicep.length() == 0)&&(space == 2))
			{
				corinput += line[space-2];
				cout << line << endl;
			}	
			else if((choicep.length()+1) == line.find(" "))
			{
				int found = 0;
				for(int i = 0 ; i < choicep.length()-1;i++)
				{
					//cout << choicep[i];
					if(line[i] == choicep[i])
						found++;
				}
				//cout << endl;
				if(found == choicep.length()-1)
				{
					corinput += line[space-1];
					cout << tmps << endl;
				}			
			}
		}
			cout << "Select:";
			cin >> mychoo;
		
		choicep += mychoo + ".";
		//cout << choicep << endl;
	}
}


/* print Hierarchy*/

void System :: print_Sel_Nodes()
{
    print_Location("Hierarchy", 0);
    ifstream inpf2("hierarchy.dat");
    if(inpf2.is_open())
    {
            vector<string> location;
            location.push_back(name);
            string levelname, choicepath, choice, oddstype;	int pr, i = 0, stop = 0;
            levelname = name;
            oddstype = "fractional";
            do
            {
                    /*cout << "Location:";
                    for(int ii = 0 ; ii < location.size(); ii++)
                    cout << "/" << location[ii];
                            cout << endl;*/
                    cout << "Type of odds:" << oddstype << endl;
                    cout << "Available choices at " << location[i++] << endl;
                    nav(location,choicepath,i);
                    locationpath(location,choicepath,i);


                    stop++;
            ifstream inpf2("hierarchy.dat");}while(stop < 5);
    }
}

void System::locationpath(vector<string> &locpath, string &chcpath,int &myi)
{
	ifstream onefile("hierarchy.dat");
	if(onefile.is_open())
	{
		
		string xline;
		int spacer;
		while(getline(onefile,xline))
		{
			string tempstring;
			int f = 0, in =0;
			int trigger;
			for(int i = 0 ; i < chcpath.length()-1;i++)
			{
				if(xline[i] == chcpath[i])
					f++;
			}
			if((f == chcpath.length()-1))
			{
				trigger = xline.find(" ");
				for(int i = xline.find(" ")+1;i < xline.length();i++)
					tempstring += xline[i];
				if((chcpath.length() - 1) == xline.find(" "))
					locpath.push_back(tempstring);
				else if((chcpath.length() == xline.find(" "))&&(myi == 1))
				{
					trigger = xline.find(" ");
					locpath.push_back(tempstring);
				}
					
				//cout << f << " " << in << " " << chcpath.length() << " " << xline.find(" ") << " " << xline << endl;					//debug
			}
		//	cout << xline.find(" ") << " " << trigger << " " << xline << endl;
		}
	}
}



/*Home page*/
void System ::  Home(string type, string username, string pass)
{
    System S;
    string choice ; 
    print_Location("Home", 1);
    cout << "You have already signed in" << endl;
    cout << "username : " <<  username <<  endl; 
    cout << "If you want to see the menu please press menu"  << endl;
    cout << "if you want to sign in wiith different account press diff" << endl ; 
    cout << "if you want to exit please press exit" << endl ; 
    cin >> choice ; 
    if (choice == "exit")
    {
        exit;
    }
    else if(choice == "menu")
    {
        select_user(type, username, pass);
    }
    else if(choice == "diff")
    {
        int res, ban;
        //string rpsYou, rpvYou;
        S.print_Location("Home", 1);
        cout << "Please give us your username and password for entrance.If you dont have an account press enter or guest: for entrance like a guest"<< endl;
        cout << "user name: " ;
        cin  >> username;
        cout << "password: " ;
        cin >> pass;
        if(username == "\n")
        {
            if (pass == "\n")
            {
                cout << "you dont have an account" <<  endl;
            }
            else 
            {
                cout << "you did something wrong" << endl; 
            }
        }
        else if (username == "guest" && pass == "guest")
        {
            cout << "you are a guest " << endl;
            S.select_user("0", "0", "0");
            
        }
        else
        {
            int type; 
            res = S.check_us_pass(username,pass);
            ban = S.check_ban(username);
            cout << res << endl ; 
            while(res == 10)
            {
              cout << "you entered wrong password or username. Try again" << endl ;
              cout << "user name: " ;
              cin  >> username;
              cout << "password: " ;
              cin >> pass;
              res = S.check_us_pass(username,pass);
              ban = S.check_ban(username);

            }
            if(ban == 1)
            {
                cout << "You are blocked" << endl ; 
                
                exit; 
            }
            else 
            {
                type = res; 
                if(type == 1)
                {
                    cout << "You are a Punter" << endl ;
                    S.select_user("1", username, pass);
                    
                }
                else if(type == 2)
                {
                    cout << "You are a Trader" << endl ; 
                    S.select_user("2", username, pass);
                }
                else if(type == 3 )
                {
                  cout << "You are a Director"<< endl ; 
                  S.select_user("3", username, pass);
                }
             
            }
        }
    
    
        }
}

Users :: Users(string lineu, int l,int i )
{
       
}


Users :: Users()
{
    
}

Users :: ~Users()
{
    
}

Users :: Users(const Users& orig)
{
    
};

string Users :: get_id()
{
    
}

/*select menu for diff type of users*/
void Users :: print_menu(string type, string line)
{
    string type_us;
    type_us = type;
    if(type == "0")
    {
        Guest g; 
        g.print_menu();
    }
    else if(type == "1")
    {
        Punter p;
        p.print_menu();
    }
    else if (type == "2")
    {
        Trader t;
        t.print_menu();
    }
    else if (type == "3")
    {
        Director d;
        d.print_menu();
    }
    
}


Guest :: Guest(string line)
{
    lineg = line;
   // cout << "line: " << line << endl ;
    guest_line.push_back(line);
    
    
    
}

Guest :: Guest(const Guest& orig)
{
    return ;
}

string Guest :: get_line()
{
   return lineg;
}

void Guest :: print_menu()
{
    cout << "ID -  Choose the node's ID you want to visit  " << endl ;
    cout << "H (Home), to return to Home Page" << endl; 
    cout  << "T (Toggle), display view rates" << endl; 
    cout << "X (Exit) " << endl ;
    
}

Director :: Director(string line)
{
    linea = line; 
    //cout << "line: " << line << endl; 
    directors_line.push_back(line);
    
}

Director :: Director()
{
    
}

Director :: Director(const Director& orig)
{
    return ; 
}

void Director :: print_menu()
{
    cout << " Choose the node's ID you want to visit :  " << endl ;
    cout << "H (Home), to return to Home Page" << endl; 
    cout  << "T (Toggle), display view rates" << endl; 
    cout << "B (Bets), show the last 20 bets" << endl ; 
    cout << "F Freebets" << endl; 
    cout << "S (Save)" << endl; 
    cout << "L (Logs)" << endl ; 
    cout << "U (Users)"<< endl ;
    cout << "V (Visibility)"<< endl ;
    cout << "R (Rename)"<< endl ;
    cout << "N (New)"<< endl ;
    cout << "C (Copy)"<< endl ;
    cout << "D (Delete)"<< endl ;
    cout << "X (Exit) " << endl ;
}


Punter :: Punter(string line)
{
    linep = line; 
    //cout << "line: " << line << endl; 
}

Punter :: Punter()
{
    
}

void Punter :: print_menu()
{
    cout << " Choose the node's ID you want to visit :  " << endl ;
    cout << "H (Home), to return to Home Page" << endl; 
    cout  << "T (Toggle), display view rates" << endl; 
    cout << "A ( My Account ) " << endl ; 
    cout << "X (Exit) " << endl ;
}

Punter :: Punter(const Punter& orig)
{
    return ; 
}

Trader :: Trader(string line)
{
    linet = line; 
    //cout << "line: " << line << endl; 
}

Trader :: Trader()
{
    
}

Trader :: Trader(const Trader& orig)
{
    return ; 
}

void Trader :: print_menu()
{
    cout << " Choose the node's ID you want to visit :  " << endl ;
    cout << "H (Home), to return to Home Page" << endl; 
    cout  << "T (Toggle), display view rates" << endl; 
    cout << "B (Bets), show the last 20 bets" << endl ; 
    cout << "F Freebets" << endl; 
    cout << "X (Exit) " << endl ;
}