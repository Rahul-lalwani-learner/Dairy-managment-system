#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
using namespace std;
class Dairy{
    protected: 
        string Date,Time,Note;
        virtual void menu()=0;
        virtual void addEntry()=0;
        virtual void viewEntry()=0;
        virtual void deleteEntry()=0;
        virtual void editEntry()=0;
    
};
void MainMenu();//Forward decleration
string encrpyt(string s){
    for(int i=0;i<s.length();i++){
        s[i]+=3;
    }
    return s;
}
string decrpyt(string s){
    for(int i=0;i<s.length();i++){
        s[i]-=3;
    }
    return s;
}
void addToList(string filename){
    std::ofstream outfile;
    outfile.open("Allfiles.txt", std::ios_base::app); // append instead of overwrite
    outfile << filename+"\n";
    outfile.close();
}
void Seeyou(){
    system("cls");
    cout<<"Thankyou for using Dairy Managment System"<<endl;
    cout<<"Made by : Rahul lalwani\nCollege : MITS , Gwalior\nBranch : AIML"<<endl;
    // cout<<"Enter any key to end...";
    // getch();
    exit(0);
}
bool DoesExist(string filename){
    ifstream file(filename+".txt");
    if(file.is_open()){
        file.close();
        return true;
    }
    else{
        return false;
    }
}

void login()
{
    static int count = 0;
    string pass = "";
    char ch;
    system("cls");
    cout<<"\n\n === Login Screen === "<<endl;
    cout<<"\n *** Enter Password: ";
    ch = _getch();
    while (ch != 13)
    { // character 13 is enter
        pass.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    if (pass == "1234")
    {
        cout<<" \n\n>>>>>> Correct Password <<<<<<"<<endl;
        // cout<<"Enter Any key to continue..."<<endl;
        system("PAUSE");
        system("CLS");
        int main();
    }
    else
    {
        cout<<"\n\n>>>>> Wrong Password <<<<<"<<endl;
        cout<<"\n you have only "<<3-count-1<<" turns "<<endl;
        count++;
        system("pause");
        system("CLS");
        if (count < 3)
        {
            login();
        }
        else
        {
            cout << "\nYOU HAVE ENTERED WRONG PASSWORD MORE THAN 3 TIMES" << endl;
            system("pause");
            exit(0);
        }
    }
}
class personalDairy:public Dairy{
    public:
        void menu(){
            cout<<"\n\n=== Personal Dairy Menu ==="<<endl;
            cout<<"1. Create Memories\n2. See Memories\n3. Delete Some Memories\n4. Edit existing Memories\n5. Goback to Mainmenu"<<endl;
            int choice;
            cout<<"Enter your choice: ";
            cin>>choice;
            switch(choice){
                case 1: 
                    addEntry();
                    break;
                case 2: 
                    viewEntry();
                    break;
                case 3: 
                    deleteEntry();
                    break;
                case 4: 
                    editEntry();
                    break;
                case 5:
                    MainMenu();
                    break;
                default: 
                    cout<<"___Wrong Choice___"<<endl;
                    cout<<"Enter Any key to continue..."<<endl;
                    getch();
                    break;
            }
        }
        void addEntry();
        void viewEntry();
        void deleteEntry();
        void editEntry();
};
void edit(string date,int num,string field){
    ofstream temp("temp.txt");
    ifstream file(date+".txt");
    string transfer;
    int count=0;
    while(!file.eof()){
        getline(file,transfer);
        if(count!=num){
            temp<<transfer+"\n";
        }
        else{
            temp<<encrpyt(field)+"\n";
        }
        count++;
    }
    temp.close();
    file.close();
    date=date+".txt";
    remove(date.c_str());
    rename("temp.txt",date.c_str());
}
void personalDairy::editEntry(){
    cout<<"\n\n1. Edit whole Entry\n2. Edit only a single field\n3. Goback to menu"<<endl;
    int choice;
    cout<<"Enter your choice: ";
    cin>>choice;
    if(choice==1){
        cout<<"Enter date[dd-mm-yyyy]: ";
        fflush(stdin);
        getline(cin,Date);
        if(DoesExist(Date)){
        ofstream temp("temp.txt");
        ifstream file("Allfiles.txt");
        string transfer;
        while(!file.eof()){
            getline(file,transfer);
            if((transfer!=Date) && (!transfer.empty())){//!transfer.empty() is remove blank space from Allfiles file
                temp<<transfer+"\n";
            }
        }
        temp.close();
        file.close();
        remove("Allfiles.txt");
        Date=Date+".txt";
        remove(Date.c_str());
        rename("temp.txt","Allfiles.txt");
        cout<<" *** Enter New values *** "<<endl;
        
        cout<<"\n\nEnter date in[dd-mm-yyyy] format: ";
        fflush(stdin);
        getline(cin,Date);
        cout<<"Enter Time [hh:mm] : ";
        cin>>Time;
        cout<<"Write any note: "<<endl;
        fflush(stdin);
        getline(cin,Note);
        // cout<<Note;
        // getch();
        ofstream user_input(Date+".txt");
        addToList(Date);
        user_input<<encrpyt(Date)+"\n";
        user_input<<encrpyt(Time)+"\n";
        user_input<<encrpyt(Note);
        user_input.close();
        
        cout<<"\n\nRecord Edited Successfully"<<endl;

        }
        else{
            cout<<"=== This record doesn't Exist ===="<<endl;
        }

    }
    else if(choice==2){
        system("cls");
        
        cout<<"\n\n\n------ Which Field you want to edit -------"<<endl;
        cout<<"1. Time\n2. Note\n3. Goback\n";
        int option;
        cout<<"Enter your choice: ";
        cin>>option;
        if(option==1){
            cout<<"Enter Date[dd-mm-yyyy] for which you want to edit Time: ";
            fflush(stdin);
            getline(cin,Date);
            if(DoesExist(Date)){

            cout<<"\nEnter time[hh:mm] : ";
            cin>>Time;

            edit(Date,1,Time);
            cout<<"Time Edited Successfully...."<<endl;
            }
            else{
                cout<<"Date doesn't Exist...."<<endl;
            }

        }
        else if(option==2){
            cout<<"Enter Date[dd-mm-yyyy] for which you want to edit Note: ";
            fflush(stdin);
            getline(cin,Date);
            if(DoesExist(Date)){

            cout<<"\nEnter Note : ";
            fflush(stdin);
            getline(cin,Note);
            edit(Date,2,Note);
            
            cout<<"Note Edited Successfully...."<<endl;
            // getch();
            }
            else{
                cout<<"Date doesn't Exist...."<<endl;
            }
            
        }
        else if(option==3){
            editEntry();
        }
        else{
            cout<<"Enterd Wrong choice"<<endl;
        }
        
    }
    else if(choice==3){
        menu();
    }
    else{
        cout<<"Entered Wrong choice"<<endl;
    }
    getch();
    // system("pause");
}
void personalDairy::addEntry(){
    char ch;
    do{
        
    cout<<"\n\nEnter date in[dd-mm-yyyy] format: ";
    fflush(stdin);
    getline(cin,Date);
    cout<<"Enter Time [hh:mm] : ";
    cin>>Time;
    cout<<"Write any note: "<<endl;
    fflush(stdin);
    getline(cin,Note);
    // cout<<Note;
    // getch();
    ofstream user_input(Date+".txt");
    addToList(Date);
    user_input<<encrpyt(Date)+"\n";
    user_input<<encrpyt(Time)+"\n";
    user_input<<encrpyt(Note);
    user_input.close();
    cout<<"Entry added Successfully"<<endl;
    cout<<"\nDo you want to add more Entries(y/n): ";
    cin>>ch;
    system("pause");
    }while(ch=='y' || ch=='Y');
    
}
void personalDairy::deleteEntry(){
    cout<<"\n\nEnter Date of Entry[dd-mm-yyyy]: ";
    fflush(stdin);
    getline(cin,Date);
    if(DoesExist(Date)){
        ofstream temp("temp.txt");
        ifstream file("Allfiles.txt");
        string transfer;
        while(!file.eof()){
            getline(file,transfer);
            if((transfer!=Date) && (!transfer.empty())){//!transfer.empty() is remove blank space from Allfiles file
                temp<<transfer+"\n";
            }
        }
        temp.close();
        file.close();
        remove("Allfiles.txt");
        Date=Date+".txt";
        remove(Date.c_str());
        rename("temp.txt","Allfiles.txt");
        cout<<"\nRecord sucessfully Deleted"<<endl;

    }
    else{
        cout<<"=== This record doesn't Exist ===="<<endl;
    }
    system("pause");

}
void personalDairy::viewEntry(){
    system("cls");
    cout<<"\n\n";
    cout<<"1. See all entries\n2. See According to Date"<<endl;
    int choice;
    cout<<"Enter your choice: ";
    cin>>choice;
    if(choice==1){
        cout<<"\n\n";
        ifstream file("Allfiles.txt");
        string temp;
        cout<<"You have records for following dates\n";
        while(!file.eof()){
            getline(file,temp);
            cout<<temp<<endl;
        }
        file.close();
        // system("pause");
    }
    else if(choice==2){
        cout<<"\n\n";
        cout<<"Enter Date [dd-mm-yyyy]: ";
        fflush(stdin);
        getline(cin,Date);
        if(DoesExist(Date)){
            string temp;
            ifstream file(Date+".txt");
            getline(file,temp);
            cout<<"Entry for following date as follow: "<<endl;
            cout<<"Date : "<<decrpyt(temp)<<endl;
            getline(file,temp);
            cout<<"Time : "<<decrpyt(temp)<<endl;
            getline(file,temp);
            cout<<"Note: "<<endl;
            cout<<decrpyt(temp)<<endl;
            file.close();
        }
        else{
            cout<<"This file doesn't Exist"<<endl;
        }
    }
    else{
        cout<<"Wrong Choice"<<endl;
    }
    system("pause");
}
class appointmentDairy:public Dairy{
    string place,person;
    public:
        void menu(){
            cout<<"\n\n=== Appointment Dairy Menu ==="<<endl;
            cout<<"1. Set Appointment\n2. See All Appointments\n3. Delete Some Appointments\n4. Edit Existing Appointments\n5. Goback to Mainmenu"<<endl;
            int choice;
            cout<<"Enter your choice: ";
            cin>>choice;
            switch(choice){
                case 1: 
                    addEntry();
                    break;
                case 2: 
                    viewEntry();
                    break;
                case 3: 
                    deleteEntry();
                    break;
                case 4: 
                    editEntry();
                    break;
                case 5:
                    MainMenu();
                    break;
                default: 
                    cout<<"___Wrong Choice___"<<endl;
                    cout<<"Enter Any key to continue..."<<endl;
                    getch();
                    break;
            }
        }
        void addEntry();
        void viewEntry();
        void deleteEntry();
        void editEntry();

};
void appointmentDairy::editEntry(){
    cout<<"\n\n1. Edit whole Entry\n2. Edit only a single field\n3. Goback to menu"<<endl;
    int choice;
    cout<<"Enter your choice: ";
    cin>>choice;
    if(choice==1){
        cout<<"Enter date[dd-mm-yyyy]: ";
        fflush(stdin);
        getline(cin,Date);
        if(DoesExist(Date)){
        ofstream temp("temp.txt");
        ifstream file("Allfiles.txt");
        string transfer;
        while(!file.eof()){
            getline(file,transfer);
            if((transfer!=Date) && (!transfer.empty())){//!transfer.empty() is remove blank space from Allfiles file
                temp<<transfer+"\n";
            }
        }
        temp.close();
        file.close();
        remove("Allfiles.txt");
        Date=Date+".txt";
        remove(Date.c_str());
        rename("temp.txt","Allfiles.txt");
        cout<<" *** Enter New values *** "<<endl;
        
        cout<<"\n\nEnter date in[dd-mm-yyyy] format: ";
        fflush(stdin);
        getline(cin,Date);
        cout<<"Enter Time [hh:mm] : ";
        cin>>Time;
        cout<<"Enter venue: ";
        fflush(stdin);
        getline(cin,place);
        cout<<"Enter name of person : ";
        fflush(stdin);
        getline(cin,person);
        cout<<"Write any note: "<<endl;
        fflush(stdin);
        getline(cin,Note);
        // cout<<Note;
        // getch();
        ofstream user_input(Date+".txt");
        addToList(Date);
        user_input<<encrpyt(Date)+"\n";
        user_input<<encrpyt(Time)+"\n";
        user_input<<encrpyt(place)+"\n";
        user_input<<encrpyt(person)+"\n";
        user_input<<encrpyt(Note);
        user_input.close();
        
        cout<<"\n\nRecord Edited Successfully"<<endl;

        }
        else{
            cout<<"=== This record doesn't Exist ===="<<endl;
        }

    }
    else if(choice==2){
        system("cls");
        
        cout<<"\n\n\n------ Which Field you want to edit -------"<<endl;
        cout<<"1. Time\n2. Place\n3. Person\n4. Note\n5. Goback\n";
        int option;
        cout<<"Enter your choice: ";
        cin>>option;
        if(option==1){
            cout<<"Enter Date[dd-mm-yyyy] for which you want to edit Time: ";
            fflush(stdin);
            getline(cin,Date);
            if(DoesExist(Date)){

            cout<<"\nEnter time[hh:mm] : ";
            cin>>Time;

            edit(Date,1,Time);
            cout<<"Time Edited Successfully...."<<endl;
            }
            else{
                cout<<"Date doesn't Exist...."<<endl;
            }

        }
        else if(option==2){
            cout<<"Enter Date[dd-mm-yyyy] for which you want to edit place's name: ";
            fflush(stdin);
            getline(cin,Date);
            if(DoesExist(Date)){

            cout<<"\nEnter Place: ";
            cin>>place;

            edit(Date,2,place);
            cout<<"Place Edited Successfully...."<<endl;
            }
            else{
                cout<<"Date doesn't Exist...."<<endl;
            }
        }
        else if(option==3){
            cout<<"Enter Date[dd-mm-yyyy] for which you want to edit person's name: ";
            fflush(stdin);
            getline(cin,Date);
            if(DoesExist(Date)){

            cout<<"\nName of person: ";
            cin>>person;

            edit(Date,3,person);
            cout<<"person Edited Successfully...."<<endl;
            }
            else{
                cout<<"Date doesn't Exist...."<<endl;
            }
        }
        else if(option==4){
            cout<<"Enter Date[dd-mm-yyyy] for which you want to edit Note: ";
            fflush(stdin);
            getline(cin,Date);
            if(DoesExist(Date)){

            cout<<"\nEnter Note : ";
            fflush(stdin);
            getline(cin,Note);
            edit(Date,2,Note);
            
            cout<<"Note Edited Successfully...."<<endl;
            // getch();
            }
            else{
                cout<<"Date doesn't Exist...."<<endl;
            }
            
        }
        else if(option==5){
            editEntry();
        }
        else{
            cout<<"Enterd Wrong choice"<<endl;
        }
        
    }
    else if(choice==3){
        menu();
    }
    else{
        cout<<"Entered Wrong choice"<<endl;
    }
    getch();
    // system("pause");
}
void appointmentDairy::addEntry(){
    char ch;
    do{
        
    cout<<"\n\nEnter date in[dd-mm-yyyy] format: ";
    fflush(stdin);
    getline(cin,Date);
    cout<<"Enter Time [hh:mm] : ";
    cin>>Time;
    cout<<"Enter venue: ";
    fflush(stdin);
    getline(cin,place);
    cout<<"Enter name of person : ";
    fflush(stdin);
    getline(cin,person);
    cout<<"Write any note: "<<endl;
    fflush(stdin);
    getline(cin,Note);
    // cout<<Note;
    // getch();
    ofstream user_input(Date+".txt");
    addToList(Date);
    user_input<<encrpyt(Date)+"\n";
    user_input<<encrpyt(Time)+"\n";
    user_input<<encrpyt(place)+"\n";
    user_input<<encrpyt(person)+"\n";
    user_input<<encrpyt(Note);
    user_input.close();
    cout<<"Entry added Successfully"<<endl;
    cout<<"\nDo you want to add more Entries(y/n): ";
    cin>>ch;
    system("pause");
    }while(ch=='y' || ch=='Y');
}
void appointmentDairy::viewEntry(){
        system("cls");
    cout<<"\n\n";
    cout<<"1. See all entries\n2. See According to Date"<<endl;
    int choice;
    cout<<"Enter your choice: ";
    cin>>choice;
    if(choice==1){
        cout<<"\n\n";
        ifstream file("Allfiles.txt");
        string temp;
        cout<<"You have records for following dates\n";
        while(!file.eof()){
            getline(file,temp);
            cout<<temp<<endl;
        }
        file.close();
        // system("pause");
    }
    else if(choice==2){
        cout<<"\n\n";
        cout<<"Enter Date [dd-mm-yyyy]: ";
        fflush(stdin);
        getline(cin,Date);
        if(DoesExist(Date)){
            string temp;
            ifstream file(Date+".txt");
            getline(file,temp);
            cout<<"Entry for following date as follow: "<<endl;
            cout<<"Date : "<<decrpyt(temp)<<endl;
            getline(file,temp);
            cout<<"Time : "<<decrpyt(temp)<<endl;
            getline(file,temp);
            cout<<"Place : "<<decrpyt(temp)<<endl;
            getline(file,temp);
            cout<<"Person : "<<decrpyt(temp)<<endl;
            getline(file,temp);
            cout<<"Note: "<<endl;
            cout<<decrpyt(temp)<<endl;
            file.close();
        }
        else{
            cout<<"This file doesn't Exist"<<endl;
        }
    }
    else{
        cout<<"Wrong Choice"<<endl;
    }
    system("pause");
}
void appointmentDairy::deleteEntry(){
    cout<<"\n\nEnter Date of Entry[dd-mm-yyyy]: ";
    fflush(stdin);
    getline(cin,Date);
    if(DoesExist(Date)){
        ofstream temp("temp.txt");
        ifstream file("Allfiles.txt");
        string transfer;
        while(!file.eof()){
            getline(file,transfer);
            if((transfer!=Date) && (!transfer.empty())){//!transfer.empty() is remove blank space from Allfiles file
                temp<<transfer+"\n";
            }
        }
        temp.close();
        file.close();
        remove("Allfiles.txt");
        Date=Date+".txt";
        remove(Date.c_str());
        rename("temp.txt","Allfiles.txt");
        cout<<"\nRecord Successfully Deleted"<<endl;

    }
    else{
        cout<<"=== This record doesn't Exist ===="<<endl;
    }
    system("pause");
}
void MainMenu(){
    system("cls");
    cout<<"\n\n********** Welcome to Dairy Management System ***********"<<endl;
    cout<<"\n ======= MainMenu ========"<<endl;
    cout<<"[1] Personal Dairy\n[2] Appointment Dairy\n[3] Exit"<<endl;
    int choice;
    fflush(stdin);
    cout<<"Enter your Choice: ";
    cin>>choice;
    if(choice==1){
        personalDairy PD;
        PD.menu();
    }
    else if(choice==2){
        appointmentDairy AD;
        AD.menu();
    }
    else if(choice==3){
        Seeyou();
    }
    else{
        cout<<"You Entered Wrong Choice"<<endl;
        cout<<"Enter Any key to continue..."<<endl;
        getch();
    }
}
int main(){
    login();
    if(!DoesExist("Allfiles")){
        ofstream file("Allfiles.txt");
        file.close();
    }
    while(true){
        MainMenu();
    }
    return 0;
}
