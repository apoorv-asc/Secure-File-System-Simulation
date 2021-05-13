#include <bits/stdc++.h>
using namespace std;
struct file{
    string filename;
    string date;
    string content;
    string author;

    struct folder* lastfolder;
};
struct folder{
    string foldername;
    string date;

    int count;
    vector<folder *> nextfolder;
    vector<file *> nextfile;
    struct folder* lastfolder;
};
folder *addFolder(struct folder *f1,string name){
    folder *f2=new folder;
    f2->foldername=name;
    f2->count=0;
    f2->lastfolder=f1;

    time_t t;
    struct tm * tt;
    time (&t);
    tt = localtime(&t);
    f2->date=asctime(tt);

    return f2;
}
file *addFile(struct folder *f1,string name,string auth,string cont){
    file *f2=new file;
    f2->filename=name;
    f2->author=auth;
    f2->lastfolder=f1;
    f2->content=cont;

    time_t t;
    struct tm * tt;
    time (&t);
    tt = localtime(&t);
    f2->date=asctime(tt);

    return f2;
}
int main(){
    vector<string> dir;
    int in,x;
    string qt;
    string nm,auth,content;
    int v;
    
    struct folder *root=new folder();
    cout<<"Enter the name of the root folder\n";
    cin>>nm;
    root->foldername=nm;
    root->count=0;
    root->lastfolder=NULL;
    struct folder *p=root;

    cout<<"1 mkdir disk : Creates a new Folder named disk "<<endl;
    cout<<"2 new doc : Create a new File named doc"<<endl;
    cout<<"3 cd .. 7 Go back"<<endl;
    cout<<"3 cd <x>: Go inside Folder"<<endl;
    cout<<"4 ls : Lists all the files inside the present directory"<<endl;
    cout<<"5 read <x>: Open File"<<endl;
    cout<<"6 rm -rf <x> Deleting a folder"<<endl;
    cout<<"7 del <x> Deleting a file"<<endl;

    dir.push_back(nm);
    while(true){
        cout<<endl;
        for(x=0;x<dir.size();x++)
            cout<<dir[x]<<":\\> ";
        
        cin>>v;
        switch(v){
            case 1:
                cin>>nm;
                (p->nextfolder).push_back(addFolder(p,nm));
                break;
            case 2:
                cin.ignore();
                cin>>nm;
                cout<<"Enter author\n";
                cin.ignore();
                getline(cin,auth);
                cout<<"What would you like to write in the file\n";
                cin.ignore();
                getline(cin,content);
                (p->nextfile).push_back(addFile(p,nm,auth,content));
                break;
            case 3:
                cin>>qt;
                if(qt==".."){
                    p=p->lastfolder;
                    dir.pop_back();
                }
                else{
                    for(x=0;x<(p->nextfolder).size();x++){
                        if(qt==(p->nextfolder[x])->foldername){
                            p=p->nextfolder[x];
                            dir.push_back(p->foldername);
                            break;
                        }
                    }
                }
                break;
            case 4:
                for(x=0;x<(p->nextfolder).size();x++)
                    cout<<(x)<<" "<<p->nextfolder[x]->foldername<<endl;
                for(x=0;x<(p->nextfile).size();x++)
                    cout<<(x)<<" "<<p->nextfile[x]->filename<<endl;
                break;
            case 5:
                cin>>qt;
                cout<<"Showing File content...\n";
                for(x=0;x<(p->nextfile).size();x++){
                    if(p->nextfile[x]->filename==qt){
                        cout<<"Author: "<<p->nextfile[x]->author<<endl;
                        cout<<"Content: "<<p->nextfile[x]->content<<endl;
                        break;
                    }
                }
                break;
            case 6:
                cin>>qt;
                if(qt!="-rf"){
                    cin>>qt;
                    cout<<"Please check your command and try again\n";
                    break;
                }
                cin>>qt;
                for(x=0;x<(p->nextfolder).size();x++){
                    if(qt==p->nextfolder[x]->foldername){
                        (p->nextfolder).erase((p->nextfolder).begin()+x);
                        break;
                    }
                }
                break;
            case 7:
                cin>>qt;
                for(x=0;x<(p->nextfile).size();x++){
                    if(qt==p->nextfile[x]->filename){
                        (p->nextfile).erase((p->nextfile).begin()+x);
                        break;
                    }
                }
                break;
            default:
                cout<<"Command match not found\n";
                break;
        } 
    }
}