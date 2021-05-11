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
    struct folder *root=new folder();
    root->foldername="Root";
    root->count=0;
    root->lastfolder=NULL;
    struct folder *p=root;
    while(true){
        cout<<"=================================================================================\n";
        cout<<"=================== Folders inside <<"<< p->foldername<<"========================\n";
        for(int x=0;x<(p->nextfolder).size();x++){
            cout<<(x)<<" "<<p->nextfolder[x]->foldername<<endl;
        }
        cout<<"=================================================================================\n";
        cout<<"=================== Files inside <<"<< p->foldername<<"==========================\n";
        for(int x=0;x<(p->nextfile).size();x++){
            cout<<(x)<<" "<<p->nextfile[x]->filename<<endl;
        }
        cout<<"=================================================================================\n";
        cout<<"=================================================================================\n";
        cout<<"1: Create a new Folder"<<endl;
        cout<<"2: Create a new File"<<endl;
        cout<<"3 <x>: Go inside Folder"<<endl;
        cout<<"4 <x>: Open File"<<endl;
        cout<<"5 Go back"<<endl;
        int v,in;
        cin>>v;
        string nm,auth,content;
        switch(v){
            case 1:
                cout<<"Enter name\n";
                cin>>nm;
                (p->nextfolder).push_back(addFolder(p,nm));
                break;
            case 2:
                cout<<"Enter name\n";
                cin>>nm;
                cout<<"Enter author\n";
                cin>>auth;
                cout<<"What would you like to write in the file\n";
                cin>>content;
                (p->nextfile).push_back(addFile(p,nm,auth,content));
                break;
            case 3:
                cin>>in;
                p=p->nextfolder[in];
                break;
            case 4:
                cin>>in;
                cout<<"Showing File content...\n";
                cout<<p->nextfile[in]->author;
                break;
            case 5:
                p=p->lastfolder;
                break;
        } 
    }
}