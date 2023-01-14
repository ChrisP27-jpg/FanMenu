#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include "Parser.h"
#include "Fans.h"
using namespace std;

void ReadIn(ifstream& fin, Node*& tail, string inFile, int& totalFans,BST<Phone>& PhoneSearch,BST<Email>& EmailSearch);
void Process(ifstream& process, ifstream& fin, ofstream& fout,Node* head, Node* tail, string& temp3, 
	string& inFile, int& totalFans, string outFile, BST<Phone>& PhoneSearch,BST<Email>& EmailSearch);
bool isPhone(string phone);
bool isEmail(string email);


int main(int argc, char *argv[]) {
	
	ifstream fin;
	ifstream process;
	ofstream fout;
	
	string line;
	string command = "";
	string temp3;
	string inFile="fans.in.txt";
	string outFile="fans.out.txt";
	int totalFans=0;
	
	Node* tail;
	Node* head;
	
	BST<Phone> PhoneSearch;
	BST<Email> EmailSearch;
	
	tail = new Node();
	head=tail;
	
	
	if (argc==1){
		fin.open("fans.in.txt");
		fout.open("fans.out.txt");
		
		
	}
	
	else if (argc == 3){
		line = argv[1];
	 	if (line== "-i"){
		   fin.open(argv[2]);
		   inFile=argv[2];
		   fout.open("fans.out.txt");	
	   }
	   else if (line=="-o"){
		   fout.open(argv[2]);
		   outFile=argv[2];
		   fin.open("fans.in.txt");
	   }
	   else{
			cout << "Maybe this an error maybe" << endl;	   
			return 0;
	   }
	}
	
	
	//Still not done with this
	else if (argc==5){
		line = argv[1];
		if (line== "-i"){
			fin.open(argv[2]);
			inFile=argv[2];	
			line = argv[3];
			if (line=="-o")
			{
				fout.open(argv[4]);
				outFile=argv[4];			
			}
			else{
				cout << "Only an input file" << endl;
				return 0;
			}
		}
		
		else if (line=="-o"){
			fout.open(argv[2]);
			outFile=argv[2];
			line = argv[3];
			if (line=="-i"){
				fin.open(argv[4]);
				inFile=argv[4];			
			}
			else{
				cout << "Only an output file" << endl;
				return 0;			
			}
		}
		else{
			cout << "There needs to be a \"-o\" or a \"-i\" somewhere" << endl;
			return 0;
		}
	}
	else {
		cout <<"There's an error here" << endl;
		return 0;	
	}
	
	if(fin){
		//read initial input file
		ReadIn(fin,tail, inFile, totalFans, PhoneSearch, EmailSearch);
	}
	else{
		cout << "Cannot open input file fans.in.txt. Ignoring." << endl;
	}
	
	
	
	
	while (command!="Quit"){
		
		cout << endl <<"Enter a command:" << endl;
   	cout << "Choose from" << endl;
   	cout << "   Load <input-filename>"<<endl;
   	cout << "   Show <fan-id>" << endl;
   	cout << "   Spend <fan-id> <dollars>" << endl;
   	cout << "   Remove <fan-id>" << endl;
   	cout << "   Process <commands-filename>" << endl;
   	cout << "   Quit" << endl << ": ";
   	getline(cin,command,'\n');
		Parser comm(command);
		
		//Quit
		if (comm.getArg1() == "Quit"){
			//send fan database to output file
			Node* dummy = head;
			while(dummy->next != NULL){
				dummy=dummy->next;
				dummy->fan.PrintFile(fout);
			}
			free(dummy);
			cout << "Stored " << totalFans << " fans into " << outFile<<endl;
		}	
		
		//Load
		if (comm.getArg1() == "Load"){
			
			if (comm.getArg2() != ""){
				fin.close();
				fin.open(comm.getArg2());
				if(fin){ReadIn(fin,tail,inFile, totalFans, PhoneSearch, EmailSearch);}
				
			}
		}
		
		//Show
		if (comm.getArg1() == "Show"){
			if (isPhone(comm.getArg2())){
				Node* find = PhoneSearch.search(comm.getArg2());
				if(find!=NULL){
					cout << "Fan data:   ";
					find->fan.PrintScreen();				
				}
			}
			else if (isEmail(comm.getArg2())){
				Node* find = EmailSearch.search(comm.getArg2());
				if(find!=NULL){
					cout << "Fan data:   ";
					find->fan.PrintScreen();				
				}
			}
			else{
				cout << "No matching fan found" << endl;
			}
		}
		
		//Spend
		if (comm.getArg1() == "Spend"){
			if (isPhone(comm.getArg2()) && comm.getArg3()!=""){
				Node* find = PhoneSearch.search(comm.getArg2());
				if(find!=NULL){
					bool fl = true;
					for(long unsigned int i=0; i<comm.getArg3().length();i++){if(!isdigit(comm.getArg3()[i])){fl=false;}}
					if (fl==true){
						find->fan.spend(stoi(comm.getArg3()));
						cout << find->fan.getName() << " now has $" << find->fan.getConcessions() << endl;
					}			
				}
			}
			else if (isEmail(comm.getArg2())){
				Node* find = EmailSearch.search(comm.getArg2());
				if(find!=NULL){
					bool fl = true;
					for(long unsigned int i=0; i<comm.getArg3().length();i++){if(!isdigit(comm.getArg3()[i])){fl=false;}}
					if (fl==true){
						find->fan.spend(stoi(comm.getArg3()));
						cout << find->fan.getName() << " now has $" << find->fan.getConcessions() << endl;
					}			
				}
			}
			else{
				cout << "No matching fan found" << endl;
			}
		}
		
		//Remove
		if (comm.getArg1() == "Remove"){
			if (isPhone(comm.getArg2())){
				Node* find = PhoneSearch.search(comm.getArg2());
				if(find!=NULL){
					PhoneSearch.remove(find->fan.getPhone());
					EmailSearch.remove(find->fan.getEmail());
					Node * dummy = head;
					while(dummy->next!=find){
						dummy =dummy->next;					
					}
					dummy->next = dummy->next->next;
					totalFans--;
				}
			}
			else if (isEmail(comm.getArg2())){
				Node* find = EmailSearch.search(comm.getArg2());
				if(find!=NULL){
					PhoneSearch.remove(find->fan.getPhone());
					EmailSearch.remove(find->fan.getEmail());
					Node * dummy = head;
					while(dummy->next!=find){
						dummy =dummy->next;					
					}
					dummy->next = dummy->next->next;
					totalFans--;
				}
			}
			else{
				cout << "No matching fan found" << endl;
			}
		}
		
		//Process
		if (comm.getArg1() == "Process"){
			if(comm.getArg2() != ""){
				process.close();
				process.open(comm.getArg2());
				Process(process,fin,fout,head, tail,temp3,inFile, totalFans, outFile, PhoneSearch, EmailSearch);
				command = temp3;
			}
			
		}
	
	}
	
	
	
	fin.close();
	fout.close();
	return 0;
}

void Process(ifstream& process, ifstream& fin, ofstream& fout,Node* head, Node* tail, string& temp3, 
	string& inFile, int& totalFans, string outFile, BST<Phone>& PhoneSearch,BST<Email>& EmailSearch){
	temp3 = "";
	string command;
	while(getline(process,command,'\n')){
		Parser comm(command);
		
		//Quit
		if (comm.getArg1() == "Quit"){
			//send fan database to output file
			temp3 = "Quit";
			Node* dummy = head;
			while(dummy->next != NULL){
				dummy=dummy->next;
				dummy->fan.PrintFile(fout);
			}
			free(dummy);
			cout << "Stored " << totalFans << " fans into " << outFile;
			break;
		}	
		
		//Load
		if (comm.getArg1() == "Load"){
			
			if (comm.getArg2() != ""){
				fin.close();
				fin.open(comm.getArg2());
				if(fin){ReadIn(fin,tail,inFile, totalFans, PhoneSearch, EmailSearch);}
			}
		}
		
		//Show
		if (comm.getArg1() == "Show"){
			if (isPhone(comm.getArg2())){
				Node* find = PhoneSearch.search(comm.getArg2());
				if(find!=NULL){
					cout << "Fan data:   ";
					find->fan.PrintScreen();				
				}
			}
			else if (isEmail(comm.getArg2())){
				Node* find = EmailSearch.search(comm.getArg2());
				if(find!=NULL){
					cout << "Fan data:   ";
					find->fan.PrintScreen();				
				}
			}
			else{
				cout << "No matching fan found" << endl;
			}
		}
		
		//Spend
		if (comm.getArg1() == "Spend"){
			if (isPhone(comm.getArg2()) && comm.getArg3()!=""){
				Node* find = PhoneSearch.search(comm.getArg2());
				if(find!=NULL){
					bool fl = true;
					for(long unsigned int i=0; i<comm.getArg3().length();i++){if(!isdigit(comm.getArg3()[i])){fl=false;}}
					if (fl==true){
						find->fan.spend(stoi(comm.getArg3()));
						cout << find->fan.getName() << " now has $" << find->fan.getConcessions() << endl;
					}			
				}
			}
			else if (isEmail(comm.getArg2())){
				Node* find = EmailSearch.search(comm.getArg2());
				if(find!=NULL){
					bool fl = true;
					for(long unsigned int i=0; i<comm.getArg3().length();i++){if(!isdigit(comm.getArg3()[i])){fl=false;}}
					if (fl==true){
						find->fan.spend(stoi(comm.getArg3()));
						cout << find->fan.getName() << " now has $" << find->fan.getConcessions() << endl;
					}			
				}
			}
			else{
				cout << "No matching fan found" << endl;
			}
		}
		
		//Remove
		if (comm.getArg1() == "Remove"){
			if (isPhone(comm.getArg2())){
				Node* find = PhoneSearch.search(comm.getArg2());
				if(find!=NULL){
					PhoneSearch.remove(find->fan.getPhone());
					EmailSearch.remove(find->fan.getEmail());
					Node * dummy = head;
					while(dummy->next!=find){
						dummy =dummy->next;					
					}
					dummy->next = dummy->next->next;
					totalFans--;
				}
			}
			else if (isEmail(comm.getArg2())){
				Node* find = EmailSearch.search(comm.getArg2());
				if(find!=NULL){
					PhoneSearch.remove(find->fan.getPhone());
					EmailSearch.remove(find->fan.getEmail());
					Node * dummy = head;
					while(dummy->next!=find){
						dummy =dummy->next;					
					}
					dummy->next = dummy->next->next;
					totalFans--;
				}
			}
			else{
				cout << "No matching fan found" << endl;
			}
		}
		
		//Process
		if (comm.getArg1() == "Process"){
			if(comm.getArg2() != ""){
				process.close();
				process.open(comm.getArg2());
				Process(process, fin, fout,head, tail,temp3, inFile, totalFans, outFile, PhoneSearch, EmailSearch);
			}
			
		}
	
	}
	
}

void ReadIn(ifstream& fin,Node*& tail, string inFile, int& totalFans,BST<Phone>& PhoneSearch,BST<Email>& EmailSearch){
	string line;
	bool flag, flag2;
	int count=0;
	int count2=0;
	string error;

	while (getline(fin, line, '\n')){
		Parser fan(line);
		Fan temp;
		flag = true;
		flag2=false;
		count++;
		error = "";
		cout << "Line   " << count << ": " << line << endl;
		
		//last name
		if (!isupper(fan.getArg1()[0])){
			flag = false;		
		}
		for (long unsigned int i =0; i < fan.getArg1().length(); i++){
			if (!isalpha(fan.getArg1()[i])){flag = false;}		
		}
		
		if (flag ==true){temp.setLast(fan.getArg1());}
		if (flag ==false && error==""){error = "invalid last name: " + fan.getArg1();}
		
		//first name
		if (!isupper(fan.getArg2()[0])){
			flag = false;		
		}
		for (long unsigned int i =0; i < fan.getArg2().length(); i++){
			if (!isalpha(fan.getArg2()[i])){flag = false;}		
		}
		if (flag ==true){temp.setFirst(fan.getArg2());}
		if (flag ==false && error==""){error = "invalid first name: " + fan.getArg2();}
		
		//phone number
		if (fan.getArg3()[0] != '('){flag = false;}
		if (fan.getArg3()[4] != ')'){flag = false;}
		if (fan.getArg3()[8] != '-'){flag = false;}
		for (int i =1; i <4; i++){
			if(!isdigit(fan.getArg3()[i])){flag = false;}		
		}
		for (int i =5; i <8; i++){
			if(!isdigit(fan.getArg3()[i])){flag = false;}		
		}
		for (int i =9; i <13; i++){
			if(!isdigit(fan.getArg3()[i])){flag = false;}		
		}
		if (flag==true){temp.setPhone(fan.getArg3());}
		
		if (flag ==false && error==""){error = "invalid phone number: " + fan.getArg3();}
		
		//email
		if (fan.getArg4()[0] != '<'){flag = false;}
		if (fan.getArg4()[fan.getArg4().length()-1] != '>'){flag = false;}
		for (long unsigned int i =fan.getArg4().find('@')+1; i< fan.getArg4().length(); i++){
			if(fan.getArg4()[i]=='@'){flag =false;}
			if(fan.getArg4()[i]=='.'){flag2 =true;}
		}
		
		if (flag2==false){flag =false;}
		if (flag==true) {temp.setEmail(fan.getArg4());}
		if (flag ==false && error==""){error = "invalid email: " + fan.getArg4();}
		
		//seat
		if (flag == true){temp.setSeat(fan.getArg5());}
		if (flag ==false && error==""){error = "invalid seat: " + fan.getArg5();}
		
		//concessions
		for (long unsigned int i=0; i<fan.getArg6().length(); i++){
			if(!isdigit(fan.getArg6()[i])){flag =false;}
		}
		if (flag ==false && error==""){error = "invalid concessions: " + fan.getArg6();}
		
		
		if (flag ==true){
			Node* tempy = new Node();
			tail->next= tempy;
			tail = tail->next;
			temp.setConc(stoi(fan.getArg6()));
			tail->fan = temp;
			PhoneSearch.insert(temp.getPhone(),tail, fan.getArg3());
			EmailSearch.insert(temp.getEmail(),tail, fan.getArg4());
			totalFans++;
		}
		
		//error
		if (flag==false){cout << "Fan file error: " << error << endl;count2++;}
		
		
	}
	cout << "Loaded " << count-count2 << " fans from " << inFile << endl;
}

bool isPhone(string phone){
	if (phone[0] != '('){return false;}
	if (phone[4] != ')'){return false;}
	if (phone[8] != '-'){return false;}
	for (int i =1; i <4; i++){
		if(!isdigit(phone[i])){return false;}		
	}
	for (int i =5; i <8; i++){
		if(!isdigit(phone[i])){return false;}		
	}
	for (int i =9; i <13; i++){
		if(!isdigit(phone[i])){return false;}		
	}
	return true;
}

bool isEmail(string email){
	if (email[0] != '<'){return false;}
	if (email[email.length()-1] != '>'){return false;}
	for (long unsigned int i =email.find('@')+1; i< email.length(); i++){
		if(email[i]=='@'){return false;}
		if(email[i]=='.'){return true;}
	}
	
	return true;
}



