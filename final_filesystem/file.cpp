#include <bits/stdc++.h>
#include "aes-new/decrypt.cpp"

using namespace std;
struct file{
    string filename;
    string date;
    string type;
    string content;
    string author;
    string permission;


    struct folder* lastfolder;
};

struct folder{
    string foldername;
    string date;
	string password;

    int count;
    vector<folder *> nextfolder;
    vector<file *> nextfile;
    struct folder* lastfolder;
};

folder *addFolder(struct folder *f1,string name,string pass){
    folder *f2=new folder;
    f2->foldername=name;
    f2->count=0;
    f2->lastfolder=f1;
	f2->password=pass;

    time_t t;
    struct tm * tt;
    time (&t);
    tt = localtime(&t);
    f2->date=asctime(tt);

    return f2;
}

file *addFile(struct folder *f1,string name,string auth,string cont,string tp,string perm){
    file *f2=new file;
    f2->filename=name;
    f2->author=auth;
    f2->lastfolder=f1;
    f2->content=cont;
    f2->type=tp;
    f2->permission=perm;

    time_t t;
    struct tm * tt;
    time (&t);
    tt = localtime(&t);
    f2->date=asctime(tt);

    return f2;
}


int main(){
    
    
    cout<<"*************************************************"<<endl;
    cout<<"****** Welcome to Secure File System (SFS) ******"<<endl;
    cout<<"*************************************************"<<endl;
    
    //changing color to light cyan
   
    string perm = " -rwx------";


    printf("\033[0;96m");
    
    vector<string> dir;
    int in,x;
    string qt;
    string nm,auth,content,type;
    string enc_auth,enc_content,enc_type,enc_perm;
    string new_content,enc_new_content;
    string v,cont;
    
    string newname,newauth,newtype,newperm,newcontent;
    string enc_newname,enc_newauth,enc_newtype,enc_newperm,enc_newcontent;
    
    struct folder *root=new folder();
    //cout<<"\nEnter the name of the root folder\n";
    //cin>>nm;
    nm="root";
    root->foldername=nm;
    root->count=0;
    root->lastfolder=NULL;
    struct folder *p=root;
	
    //changing text to yellow, bold
    
    printf("\033[0;33m");
    printf("\033[1m");
	
    cout<<endl;		        
    cout<<setw(20)<<left<<"help"<<"to display all the functions\n";
    cout<<setw(20)<<left<<"mkdir"<<"to create a directory\n";
    cout<<setw(20)<<left<<"create"<<"to create a new file\n";
    cout<<setw(20)<<left<<"cd .."<<"to go back\n";
    cout<<setw(20)<<left<<"ls"<<"to list all the contents of the directory\n";
    cout<<setw(20)<<left<<"read"<<"to read the contents of the file\n";
	cout<<setw(20)<<left<<"fileinfo"<<"to display the details of the file\n";
    cout<<setw(20)<<left<<"rename "<<"to rename a file\n";
    cout<<setw(20)<<left<<"update"<<"to update /overwrite the file\n";
    cout<<setw(20)<<left<<"rm -rf"<<"to remove the folder\n";
    cout<<setw(20)<<left<<"del"<<"to delete the file\n";
    cout<<setw(20)<<left<<"exit"<<"to exit the file system\n";

    //changing color to white, normal
    
    printf("\033[0;39m");
    printf("\033[0m");
    
    dir.push_back(nm);
    while(true){
        cout<<endl;
        for(x=0;x<dir.size();x++)
            cout<<dir[x]<<":\\> ";
        
        cin>>v;
        
            
            //1. mkdir: used for making a new directory at the current path
            
            if(v=="mkdir"){
                
		        //cout<<"Enter directory name:";
				string pass;
		        cin>>nm;
				
				cout<<"Would you like to protect the directory using a password ? y/n\n";
				cin>>pass;

				if(pass=="YES" || pass=="Yes" || pass=="yes" || pass=="Y"){
					cout<<"Enter password\n";
					cin.ignore();
                	getline(cin,pass);
					(p->nextfolder).push_back(addFolder(p,nm,pass));
				}else{
					(p->nextfolder).push_back(addFolder(p,nm,""));
				}
            }
                
            //2. create file: creates a new file takes in author name and enables to write content
            
            else if(v=="create"){
                
                	
		        cin>>nm;
		        
		        string key;
		        printf("\033[0;92m");
                	cout<<"\n*******This is a secure file system*****\n"<<endl;
                	cout<<"Please enter the 16-bit key: ";
                	cin.ignore();
                	getline(cin,key);
                	printf("\033[0;39m");
		        
		        cout<<"Enter file type: \n";
		        cin.ignore(0);
		        getline(cin,type);
		        enc_type=encryptString(type,key);
		        
		        cout<<"Enter author\n";
		        cin.ignore();
		        getline(cin,auth);
		        enc_auth=encryptString(auth,key);
		        
		        cout<<"What would you like to write in the file? \n";
		        cin.ignore();
		        getline(cin,content);
		        enc_content=encryptString(content,key);
		        
		        enc_perm = encryptString(perm,key);
		        
		        (p->nextfile).push_back(addFile(p,nm,enc_auth,enc_content,enc_type,enc_perm));
		        

            }
                
            //3. cd .. to go back in path
            
            else if(v=="cd"){
                
		        cin>>qt;
		        if(qt==".."){
		        
		            p=p->lastfolder;
		            dir.pop_back();
		        }
		  
		        else{
					string pass;
		            for(x=0;x<(p->nextfolder).size();x++){
		                if(qt==(p->nextfolder[x])->foldername && p->nextfolder[x]->password!=""){
							cout<<"The folder is protected using a password.\n Please enter the password to go inside it\n";
							cin.ignore();
                			getline(cin,pass);
							if(pass==p->nextfolder[x]->password){
								p=p->nextfolder[x];
								dir.push_back(p->foldername);
								break;
							}else{
								cout<<"Wrong Password entered\n";
								break;
							}
						}
						else if(qt==(p->nextfolder[x])->foldername && p->nextfolder[x]->password==""){
							p=p->nextfolder[x];
		                	dir.push_back(p->foldername);
		                	break;
						}
						if(x==(p->nextfolder).size())
							cout<<"Directory not found\n";
					}
		                    
		        }
		    }
                
            //4. ls command to display all content present in the current folder
            
            else if(v=="ls"){
            	
            	//changing color to red bold
            	
            	printf("\033[0;34m");
    			printf("\033[1m");
    		
		        for(x=0;x<(p->nextfolder).size();x++)
		            cout<<setw(10)<<left<<" "<<p->nextfolder[x]->foldername<<endl;
				printf("\033[0;31m");
    			printf("\033[1m");
    		            
		        for(x=0;x<(p->nextfile).size();x++)
		            cout<<setw(10)<<left<<" "<<p->nextfile[x]->filename<<endl;
		            
				printf("\033[0;39m");
    			printf("\033[0m");
            
            }
                
            //5. read command to read the contents of the file
            
            else if(v=="fileinfo"){
                	
		        cin>>qt;
		        cout<<"Showing File info\n\n";
		        
		        string keytodecrypt;
                	printf("\033[0;92m");
                	cout<<"\n*******This is a secure file system*****\n"<<endl;
                	cout<<"Please enter the 16-bit key: ";
                	cin.ignore();
                	getline(cin,keytodecrypt);
                	printf("\033[0;39m");
		        
		        
		        for(x=0;x<(p->nextfile).size();x++){
		        
		            if(p->nextfile[x]->filename==qt){
		            
		                cout<<setw(10)<<left<<"Author: "<<decryptString(p->nextfile[x]->author,keytodecrypt)<<endl;
		                cout<<setw(10)<<left<<"Permissions: "<<decryptString(p->nextfile[x]->permission,keytodecrypt)<<endl;
		                cout<<setw(10)<<left<<"Type: "<<decryptString(p->nextfile[x]->type,keytodecrypt)<<endl;
		                break;
		            }
		        }
		        
            }
			
            //rename
            else if (v=="rename"){
            
            	cin>>qt;
            	string newname;
            	for(x=0;x<(p->nextfile).size();x++){
		        
		            if(p->nextfile[x]->filename==qt){
		            
		            	string keytoread;
		        	printf("\033[0;92m");
                		cout<<"\n*******This is a secure file system*****\n"<<endl;
		        	cout<<"Please enter the 16-bit key: ";
		        	cin.ignore();
		        	getline(cin,keytoread);
		        	printf("\033[0;39m");
		            
		                //cout<<"Author: "<<p->nextfile[x]->author<<endl;
		                cout<<"Current file name: "<<p->nextfile[x]->filename<<endl;
		                cout<<"Enter new file name: \n";
		                cin.ignore();
		                getline(cin,newname);
		                p->nextfile[x]->filename = newname;
		                break;
		            }
		        }
            }
            else if(v=="copy"){
            	
            	cin>>qt;
            	for(x=0;x<(p->nextfile).size();x++){
		        
		            if(p->nextfile[x]->filename==qt){
		            	
		            		
		            		string keytocopy;
					printf("\033[0;92m");
                			cout<<"\n*******This is a secure file system*****\n"<<endl;
					cout<<"Please enter the 16-bit key of file to be copied: ";
					cin.ignore();
					getline(cin,keytocopy);
					printf("\033[0;39m");
					
					cout<<"New filename: ";
					cin.ignore();
					getline(cin,newname);
					
					string newkey;
					printf("\033[0;92m");
               		 	cout<<"\n*******This is a secure file system*****\n"<<endl;
					cout<<"Please enter the 16-bit key of newfile: ";
					cin.ignore();
					getline(cin,newkey);
					printf("\033[0;39m");
					
					newauth = decryptString(p->nextfile[x]->author,keytocopy);
					enc_newauth = encryptString(newauth,newkey);
					
					newperm = decryptString(p->nextfile[x]->permission,keytocopy);
					enc_newperm = encryptString(newperm,newkey);
					
					newcontent= decryptString(p->nextfile[x]->content,keytocopy);
					enc_newcontent = encryptString(newcontent,newkey);
					
					newtype = decryptString(p->nextfile[x]->type,keytocopy);
					enc_newtype = encryptString(newtype,newkey);
					
					(p->nextfile).push_back(addFile(p,newname,enc_newauth,enc_newcontent,enc_newtype,enc_newperm));
					break;
		        
		            	}
		}
            }
            
            //edit file contents
            else if(v=="update"){
            	
            	cin>>qt;
            	
            	for(x=0;x<(p->nextfile).size();x++){
		        
		            if(p->nextfile[x]->filename==qt){
		            	
		            	string keytoupdate;
		        	printf("\033[0;92m");
                		cout<<"\n*******This is a secure file system*****\n"<<endl;
		        	cout<<"Please enter the 16-bit key: ";
		        	cin.ignore();
		        	getline(cin,keytoupdate);
		        	printf("\033[0;39m");
		            
		                //cout<<"Author: "<<p->nextfile[x]->author<<endl;
		                string cont = decryptString(p->nextfile[x]->content,keytoupdate);
		                cout<<"Current file content: "<<cont<<endl;
		                cout<<"Enter the new content: \n";
		
		                cin.ignore();
		                getline(cin,new_content);
		                //newcontent = cont + " " + newcontent;
		                
		                cout<<"File content: \n"<<new_content;
		                enc_new_content = encryptString(new_content,keytoupdate);

		                p->nextfile[x]->content = enc_new_content;
		                break;
		            }
		        }
            
            }/*
            else if(v=="append"){
            	
            	cin>>qt;
            	string appendcontent, enc_appendcontent;
            	for(x=0;x<(p->nextfile).size();x++){
		        
		            if(p->nextfile[x]->filename==qt){
		            	
		            	string keytoupdate;
		        	cout<<"*******This is a secure file system*****\n"<<endl;
		        	cout<<"Please enter the 16-bit key: ";
		        	cin.ignore();
		        	getline(cin,keytoupdate);
		            
		                //cout<<"Author: "<<p->nextfile[x]->author<<endl;
		                cont = decryptString(p->nextfile[x]->content,keytoupdate);
		                cout<<"Current file content: "<<cont<<endl;
		                cout<<"Enter content to append: \n";
		
		                cin.ignore();
		                getline(cin,new_content);
		                appendcontent = cont+appendcontent;
		                
		                cout<<"File content: \n"<<appendcontent;
		                enc_appendcontent = encryptString(appendcontent,keytoupdate);

		                p->nextfile[x]->content = enc_appendcontent;
		                break;
		            }
		        }
            
            }*/
            else if(v=="read"){
                
		        cin>>qt;
		        cout<<"Showing File content...\n";
		        
		        string keytoread;
                	printf("\033[0;92m");
                	cout<<"\n*******This is a secure file system*****\n"<<endl;
                	cout<<"Please enter the 16-bit key: ";
                	cin.ignore();
                	getline(cin,keytoread);
                	printf("\033[0;39m");
		        
		        
		        for(x=0;x<(p->nextfile).size();x++){
		        
		            if(p->nextfile[x]->filename==qt){
		            
		                //cout<<"Author: "<<p->nextfile[x]->author<<endl;
		                cout<<"Content:\n\n"<<decryptString(p->nextfile[x]->content,keytoread)<<endl;
		                break;
		            }
		        }
		        
            }
                
            //6. rm -rf command to remove the folder 
            
            else if(v=="rm"){
                
		        cin>>qt;
		        
		        if(qt!="-rf"){
		            cin>>qt;
		            cout<<"Please check your command and try again\n";
		            break;
		        }
		        
		        cin>>qt;
		        for(x=0;x<(p->nextfolder).size();x++){
		        
		        	if(qt==p->nextfolder[x]->foldername && p->nextfolder[x]->password==""){
		        		
		        		(p->nextfolder).erase((p->nextfolder).begin()+x);
		                	break;
		        		
		        	}
		        	else{
					cout<<"Enter password: ";
					string pass;
					cin.ignore();
					getline(cin,pass);
					
					if(pass==p->nextfolder[x]->password){
						
						(p->nextfolder).erase((p->nextfolder).begin()+x);
					}
					else{
						cout<<"Operation failed!!! wrong password!!!\n";
					}
					break;
				}
			}
            }
                
            //7. del command to delete the given file
            
            else if(v=="del"){
                
	
		        cin>>qt;
		        
		        for(x=0;x<(p->nextfile).size();x++){
		        
		            if(qt==p->nextfile[x]->filename){
		            
		                (p->nextfile).erase((p->nextfile).begin()+x);
		                break;
		            }
		        }
            }
                
            //help command lists all the available commands
            
            else if(v=="help"){
                	
                printf("\033[0;96m");
     			printf("\033[1m");
		        
		        cout<<setw(20)<<left<<"help"<<"to display all the functions\n";
		        cout<<setw(20)<<left<<"mkdir"<<"to create a directory\n";
		        cout<<setw(20)<<left<<"create"<<"to create a new file\n";
		        cout<<setw(20)<<left<<"cd .."<<"to go back\n";
		        cout<<setw(20)<<left<<"ls"<<"to list all the contents of the directory\n";
		        cout<<setw(20)<<left<<"read"<<"to read the contents of the file\n";
		        cout<<setw(20)<<left<<"fileinfo"<<"to show the info of the file\n";
		        cout<<setw(20)<<left<<"rm -rf"<<"to remove the folder\n";
		        cout<<setw(20)<<left<<"del"<<"to delete the file\n";
		        cout<<setw(20)<<left<<"exit"<<"to exit the file system\n";
		        
		                   
				printf("\033[0;39m");
	    		printf("\033[0m");
		 	}
                
            else if(v=="exit"){
            	break;
            }
                
            else{
            
		cout<<"Command match not found\n";
            	cout<<"Try 'help' command\n";
            }
               
        } 
}
