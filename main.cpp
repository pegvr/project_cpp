/* 
 * File:   main.cpp
 * Author: peggyvourou,chrischris
 *
 * Created on 15 Φεβρουάριος 2017, 7:57 μμ
 */
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <ctime>
#include <vector>
#include "System.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    System S;
    string choice  ; //choice 
    string username;
    string password;
    //int M  ; //number of particles
   // M = atoi(argv[1]);
    choice = argv[1];
    cout << "your choice: " << choice << endl; 
    /*registry */
    if (choice == "R")
    {
        S.print_Location("Home", 0);
        string choice_cont; 
        cout << "Username: " << endl ; 
        cin >> username;
        cout << "Password: " << endl; 
        cin >> password ; 
        S.signup_user(username,password);
        cout << "Your registry has been done successfully" << endl ; 
        cout << "If you want to continue press yes else press exit " << endl; 
        cin >> choice_cont ;
        if( choice_cont == "yes" )
        {
            choice = "0"; 
        }
        else
        {
            exit; 
        }
        
    }
    /*sign in */
    if (choice == "0")
    {
        S.print_Location("Home", 0);
        int res, ban;
        //string rpsYou, rpvYou;
        
        cout << "Please give us your username and password for entrance.If you dont have an account press enter or guest: for entrance like a guest"<< endl;
        cout << "user name: " ;
        cin  >> username;
        cout << "password: " ;
        cin >> password;
        if(username == "\n")
        {
            if (password == "\n")
            {
                cout << "you dont have an account" <<  endl;
            }
            else 
            {
                cout << "you did something wrong" << endl; 
            }
        }
        else if (username == "guest" && password == "guest")
        {
            cout << "you are a guest " << endl;
            
            S.select_user("0", "0", "0");
            
        }
        else
        {
            int type; 
            res = S.check_us_pass(username,password);
            ban = S.check_ban(username);
           // cout << res << endl ; 
            while(res == 10)
            {
              cout << "you entered wrong password or username. Try again" << endl ;
              cout << "user name: " ;
              cin  >> username;
              cout << "password: " ;
              cin >> password;
              res = S.check_us_pass(username,password);
              ban = S.check_ban(username);

            }
            if(ban == 1)
            {
                cout << "You are blocked" << endl ; 
                
                return 0; 
            }
            else 
            {
                type = res; 
                if(type == 1)
                {
                    cout << "You are a Punter" << endl ;
                    S.select_user("1", username, password);
                    
                }
                else if(type == 2)
                {
                    cout << "You are a Trader" << endl ; 
                    S.select_user("2", username, password);
                }
                else if(type == 3 )
                {
                  cout << "You are a Director"<< endl ; 
                  S.select_user("3", username, password);
                }
             
            }
            
        }
    }
    //cout << "hello" << endl; 
    return 0;
}

