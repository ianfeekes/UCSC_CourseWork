//$Id: commands.cpp,v 1.17 2018-01-25 14:02:55-08 - - $
//

#include "commands.h"
#include "debug.h"

command_hash cmd_hash {
   {"#"     , fn_comm  }, 
   {"cat"   , fn_cat   },
   {"cd"    , fn_cd    },
   {"echo"  , fn_echo  },
   {"exit"  , fn_exit  },
   {"ls"    , fn_ls    },
   {"lsr"   , fn_lsr   },
   {"make"  , fn_make  },
   {"mkdir" , fn_mkdir },
   {"prompt", fn_prompt},
   {"pwd"   , fn_pwd   },
   {"rm"    , fn_rm    },
   {"rmr"   , fn_rmr   }
};

command_fn find_command_fn (const string& cmd) {
   // Note: value_type is pair<const key_type, mapped_type>
   // So: iterator->first is key_type (string)
   // So: iterator->second is mapped_type (command_fn)
   DEBUGF ('c', "[" << cmd << "]");
   const auto result = cmd_hash.find (cmd);
   if (result == cmd_hash.end()) {
      throw command_error (cmd + ": no such function");
   }
   return result->second;
}

command_error::command_error (const string& what):
            runtime_error (what) {
}

int exit_status_message() {
   int exit_status = exit_status::get();
   cout << execname() << ": exit(" << exit_status << ")" << endl;
   return exit_status;
}

/*Intentionally empty function to handle comments*/ 
void fn_comm(inode_state& state, const wordvec& words){}; 

/*Function to take in a filepath represented as a string andto find 
 *the corresponding inode that the path specifies. This was initially
 *catered to work well specifically for the make function assisting,
 *so some of the logic may be strange or a bit redundant in terms of
 *code density. I tried to document this well.*/ 
inode_ptr findPath(string path, inode_ptr p)
{
   /*tokenizedPath is a wordvec that contains all the names of the 
    *directories, so if the path passed into the arguments is 
    * /foo/bar/dir/fileName it will contain each of the names as its
    *elements*/  
   wordvec tokenizedPath = split(path, "/"); 
   /*For each base_file in the specified path we compare the directory
    *with the node's name to see if it is valid. If it isn't we throw
    *an error message*/  
   for(int i=0;i<tokenizedPath.size();i++)
   {
      /*currentDirents contains all the Dirents of the directory we are
       *currently iterating through while comparing with the path*/   
      map<string, inode_ptr> r;
      base_file_ptr b = p->getContents(); 
      r = dynamic_pointer_cast<directory>(b)->getDirents();
      /*We iterate through the dirents of the current directory until we
       *find an inode with the specified name*/  
      map<string, inode_ptr>:: iterator x = r.find(tokenizedPath.at(i));
      /*This largely is to check for if we are at the make command and 
       *to allos us to return one directory above the hierarchy*/  
      if(i<tokenizedPath.size()-1)
      {
     /*If we went through all the dirents without finding anything*/ 
         if(x==r.end())
         {
            throw command_error("Error: invalid path specified \n"); 
         }
      /*This is assuming that we have found a valid directory with the
       *name that works with the specified tokenized path*/     
         p = r.find(tokenizedPath.at(i))->second;
     }
     else
     {
        /*If we still found a directory*/ 
        if(x!=r.end())
        {
           p = r.find(tokenizedPath.at(i))->second;
        } 
     }
  }
  return p; 
}

/*Same logic as findPath except this is used largely for the rm and 
 *rmdir commands as we want to find a directory pointing to an inode
 *that we want to move, rather than iterating all the way through the 
 *file path, we keep a depth of 1*/ 
inode_ptr findPathrm(string path, inode_ptr p)
{
   wordvec tokenizedPath = split(path, "/");
   /*Largely the only code that is actually changed rather than simply
    *removed in this function is it goes to the size-1 rather than
    *size of the path*/ 
   for(int i=0;i<tokenizedPath.size()-1;i++)
   {
      map<string, inode_ptr> q;
      base_file_ptr b = p->getContents(); 
      q = dynamic_pointer_cast<directory>(b)->getDirents();
      map<string, inode_ptr>:: iterator x = q.find(tokenizedPath.at(i));
      if(x==q.end())
      {
         throw command_error("Error: invalid path specified \n");
      }
      p = q.find(tokenizedPath.at(i))->second;
   }
   return p;
}

/*This function iterates through all the filepath arguments, finding
 *and verifying their paths and then checks to make sure it is a plain
 *file, it will throw an error if a directory is specified, and sends
 *the contents to stdout*/ 
void fn_cat (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size()==1)
   {
      throw command_error("Error: incorrect usage no path given\n");
   }
   /*Since you can cat multiple files we want to cat out their 
    *contents one file at a time*/  
   for(int i=1;i<words.size();i++)
   {
      /*use find path function to get as close as we can to our file*/
      inode_ptr specifiedFile = findPathrm(words.at(i), state.getCwd());
      wordvec tokenizedPath = split(words.at(i), "/");
      string lastBaseFile = tokenizedPath.at(tokenizedPath.size()-1);
      /*Based on how the find path logic works we may need to move up 
       *one file forward in the path, which is fine*/  
      if(specifiedFile->getName()!=lastBaseFile)
      {
         map<string, inode_ptr> m;
         base_file_ptr b = specifiedFile->getContents();
         m = dynamic_pointer_cast<directory>(b)->getDirents();
         map<string, inode_ptr>:: iterator x = m.find(lastBaseFile);
         if(x==m.end())
         {
            throw command_error("Error: invalid path specified \n");
         }
         specifiedFile = m.find(lastBaseFile)->second; 
      }
      if(specifiedFile->isDirectory==1)
      {
         throw command_error("Error: No such file or directory"); 
      }
      /*Spit out the file's contents*/
      wordvec toPrint = specifiedFile->getContents()->readfile();
      for(int j=0;j<toPrint.size();j++)
      {
         cout << toPrint.at(j) << " "; 
      }
      cout << endl; 
   }
}

/*Possibly the most challenging function to implement. It finds the
 *path of the directory we want to cd to and calls on the changeDir
 *state method, which can be found in file_sys.cpp, it essentially
 *just sets all the private variables to be golden for a change of
 *current directory*/ 
void fn_cd (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size()==1 or words.at(1)=="/")
   {
      inode_ptr r = state.getRoot(); 
      state.changeDir(r); 
   }
   else if(words.at(1)=="..")
   {
      inode_ptr specifiedFile = findPath(words.at(1), state.getCwd()); 
      state.changeDir(specifiedFile); 
   }
   else if(words.at(1)==".")
   {
      int x = 0; 
   } 
   else
   {
      /*This should be the final directory given in the path*/ 
      inode_ptr specifiedFile = findPathrm(words.at(1),state.getCwd());
      wordvec tokenizedPath = split(words.at(1), "/");
      string lastBaseFile = tokenizedPath.at(tokenizedPath.size()-1);
      map<string, inode_ptr> c;
      base_file_ptr b = specifiedFile->getContents();
      c = dynamic_pointer_cast<directory>(b)->getDirents();      
      map<string, inode_ptr>:: iterator x = c.find(lastBaseFile);
      if(x==c.end())
      {
         throw command_error("Error: invalid path specified \n");
      } 
      /*Our parent directory is the file one directory above*/ 
      specifiedFile = c.find(lastBaseFile)->second;
      state.changeDir(specifiedFile); 
   }
}

/*Echo already works as is. No need to change this*/ 
void fn_echo (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   cout << word_range (words.cbegin() + 1, words.cend()) << endl;
}

/*Tests to see if there are arguments specifying the exit status. If
 *not we can simply throw a ysh_exit because the default value is
 *already set to zero. Else we must test the args to see if there are
 *any non-numerical chars. If so, set our exit value to 127 as 
 *specified, else we can just keep the string and convert it to an int
 *setting the status and throwing a ysh exit as given*/
void fn_exit (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size()==1) throw ysh_exit();
   string toExit = words.at(1);
   /*Initially we assume a numerical exit status*/
   bool isString = 0;
   int exitVal = 0;
   for(int i=0;i<words.at(1).size();i++)
   {
      if(toExit.at(i)>'9' or toExit.at(i)<0)
      {
         isString = 1;
         break;
      }
      /*If we already know it's a string then we can stop iterating.
       *Just to save on best and average-case run times*/
      if(isString) break;
   }
   /*If it's a string we assign it 127, else it must be an int so we
    *can simply keep whatever the user entered*/
   if(isString)exitVal = 127;
   else exitVal = stoi(toExit);
   /*Set the exit status to whatever we computed and throw a ysh exit*/
   exit_status::set(exitVal);
   throw ysh_exit();
}


/*Checks to see if a filepath is needed, this method has a little 
 *redundancy because it was largely implemented before findPath was
 *written. It simply finds the filepath if specified, finds its 
 *dirents and iterates through them, spitting out their names in the
 *desired format, where the number of whitespaces is six - the number
 *of digits required by the size() of the inode(whether directory or
 *plain file). */ 
void fn_ls (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size()==1 )
   {
      inode_ptr specifiedDir = state.getCwd();
      cout << state.getCwd()->getName() << ":" << endl;
      base_file_ptr s = specifiedDir->getContents();
      map<string, inode_ptr> allFiles = s->getDirents();
      /*Since dirents is a map we must use an auto iterator rather 
       *than an integer becuse the access functions are limited*/
      for(auto& i: allFiles)
      {
         string str = "";
         string elName = i.first;
         inode_ptr p = i.second;
         if(p->isDirectory and i.first!=".." and i.first!=".")
         {
            elName+="/";
         }
         int x = i.second->getContents()->size();
         int numDigits =0;
         while(x>0)
         { 
            x/=10;
            numDigits++;
         } 
         for(int j=0;j<7-numDigits;j++)str+=" ";
         cout<< "      "  << i.second->get_inode_nr() << str;
         cout<<i.second->getContents()->size()<<" "<<elName<<endl;
         }
      }
   else for(int k=1;k<words.size();k++)
   {
      /*Testing the case of ls / where we can just print out the roots
       *fields*/  
      string str = state.getRoot()->getName(); 
      if(words.size()==2 and words.at(k)==str)
      {
         inode_ptr specifiedDir = state.getRoot();
         cout << words.at(k) << ":" << endl;
         base_file_ptr p = specifiedDir->getContents(); 
         map<string, inode_ptr> allFiles = p->getDirents();
         for(auto& i: allFiles)
         {
            string str = ""; 
            /*Elenemt name is used to determine if we need to add a 
             *slash at the end to represent a directory name that is
             *not dot nor dot dot*/     
            string elName = i.first;
            if(i.second->isDirectory and i.first!=".." and i.first!=".")
            {
               elName+="/";
            }
            int x = i.second->getContents()->size(); 
            int numDigits =0; 
            while(x>0)
            { 
               x/=10; 
               numDigits++; 
            }
            /*We find the size of the digits for the inode number and
             *add an appropriate number of white space characters in
             *the for loop for formatting purposes*/   
            for(int j=0;j<7-numDigits;j++)str+=" "; 
            cout<<"      " << i.second->get_inode_nr() << str;
            cout<<i.second->getContents()->size()<<" "<<elName<<endl;
         }
      }
      /*If no path has been specified and we are just listing the files
       *in our current directory*/   
      else if(words.size()==1 )
      {
         inode_ptr specifiedDir = state.getCwd();
         cout << state.getCwd()->getName() << ":" << endl;
         base_file_ptr s = specifiedDir->getContents(); 
         map<string, inode_ptr> allFiles = s->getDirents();
         /*Since dirents is a map we must use an auto iterator rather 
          *than an integer becuse the access functions are limited*/  
         for(auto& i: allFiles)
         {
            string str = ""; 
            string elName = i.first; 
            inode_ptr p = i.second; 
            if(p->isDirectory and i.first!=".." and i.first!=".")
            {
               elName+="/";
            }
            int x = i.second->getContents()->size();
            int numDigits =0;
            while(x>0)
            {
               x/=10;
               numDigits++;
            }
            for(int j=0;j<7-numDigits;j++)str+=" ";
            cout<< "      "  << i.second->get_inode_nr() << str;
            cout<<i.second->getContents()->size()<<" "<<elName<<endl;
         }
      }
      else
      {
         inode_ptr specifiedDir=findPath(words.at(k),state.getRoot());
         if(words.at(k)=="..") specifiedDir = state.getParentDir(); 
         else if(words.at(k)==".")specifiedDir = state.getCwd(); 
         cout << words.at(k) << ":" << endl;
         base_file_ptr s = specifiedDir->getContents(); 
         map<string, inode_ptr> allFiles = s->getDirents();
         for(auto& i: allFiles)
         {
            string str = ""; 
            string elName = i.first;
            inode_ptr p = i.second; 
            if(p->isDirectory and i.first!=".." and i.first!=".")
            {
               elName+="/";
            }
            int x = i.second->getContents()->size();
            int numDigits =0;
            while(x>0)
            {
               x/=10;
               numDigits++;
            }
            for(int j=0;j<7-numDigits;j++)str+=" ";
            cout<< "      " << i.second->get_inode_nr() << str;
            cout << i.second->getContents()->size() << " " ;
            cout << elName  <<endl;
         }
      }
   }
}

/*Function that for each of its filepath arguments it finds the
 *appropriate path, gets the file's descendents, lists its contents,
 *and then jumps to its descendents to do the same until we're 
 *finished. */ 
void fn_lsr (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size()<=1)
   {
      throw command_error("Error: invalid usage of arguments lsr\n");
   }
  /*Multiple paths can be specified in lsr just as with ls*/ 
  for(int j=1;j<words.size();j++)
   {
      inode_ptr specifiedFile; 
      if(words.at(j)=="/") specifiedFile = state.getRoot(); 
      /*Create a specified file based on the root of the path*/ 
      else specifiedFile = findPath(words.at(j), state.getCwd());
      /*We now get its dirents so we can iterate through them*/ 
      base_file_ptr s = specifiedFile->getContents(); 
      map<string, inode_ptr> r;
      r = dynamic_pointer_cast<directory>(s)->getDirents();
      /*We want to create a tokenized path so we can have data to 
       *pass into the ls function so we don't have to redo a bunch of
       *code and can simply call it for each iteration*/  
      fn_ls(state, words); 
      wordvec tokenizedPath = split(words.at(j), "/");
      /*We want to iterate through all of the dirents*/ 
      for(auto& i: r)
      { 
         /*We want to make sure we aren't iterating upwards into the 
          *parent directories - only downward*/  
         if(i.first!=".." and i.first!=".")
         {
            /*If the dirent we are currently iterating through is an
             *inode descendant of type directory  we can call lsr*/
            if(i.second->isDirectory==1)
            {
               wordvec temp; 
               temp.push_back(words.at(0)); 
               string str = words.at(j); 
               /*We don't want redundancy of // after lsr / cases*/ 
               if(words.at(j)!="/")str+="/";
               str+=i.first; 
               temp.push_back(str); 
               fn_lsr(state, temp); 
            }      
         }
      }
   }
}

/*The file specified is created and the rest of the words are put in
 *the file. If a file of that name already exists, a new one is  not
 *created, but the contents are overwritten. It throws an error if a 
 *directory is specified by the path. If there are no more words than
 *the filename then it is empty*/ 
void fn_make (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   /*Checks to make sure that we have been given a proper path name or
    *file name to create*/     
   if(words.size()<=1)
   {
      throw command_error("Error: file/pathname not specified \n"); 
   }   
   inode_ptr specifiedFile = findPath(words.at(1), state.getCwd()); 
   /*if specified file is a directory and it is the final element of
    *filepath then we know that they want to override a directory
    *type base file, which should cause an error*/ 
   wordvec tokenizedPath = split(words.at(1), "/");
   string lastBaseFile = tokenizedPath.at(tokenizedPath.size()-1);
   if(specifiedFile->getName()==lastBaseFile
   and specifiedFile->isDirectory == 1)
   {
      throw command_error("Error: you cannot overwrite a directory \n");
   }
   /*Else we need to see if specifiedFile is a preexisting plain_file
    *in which case we want to overwrite its contents*/
   else if(specifiedFile->getName()==lastBaseFile)
   {  
      wordvec data;
      for(int i=2;i<words.size();i++)data.push_back(words.at(i));
      specifiedFile->getContents()->writefile(data);   
   } 
   /*Else we want to create a new inode of type plain_file and set
    *its contents to the rest of the arguments in words*/ 
   else
   {
      base_file_ptr b = specifiedFile->getContents(); 
      inode_ptr newFile = b->mkfile(lastBaseFile);
      wordvec data;
      for(int i=2;i<words.size();i++)data.push_back(words.at(i)); 
      newFile->getContents()->writefile(data);
      /*We want to add this file to the dirents of our directory found
       *at the end of the path*/  
      specifiedFile->addDirent(lastBaseFile, newFile); 
      /*For cat purposes we want to make sure that the file we just
       *created is processed as a plain_file and not as a directory*/ 
   }
}

void fn_mkdir (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   inode_ptr specifiedFile; 
   wordvec temp = split(words.at(1), "/"); 
   if(temp.size()==1)specifiedFile = state.getCwd(); 
   else specifiedFile = findPathrm(words.at(1), state.getRoot()); 
   /*We want to get the dirents of the file to check to see if there 
    *already exists a directory with the name of the final tokenized
    *string and if so throw an error*/  
   map<string, inode_ptr> r;
   base_file_ptr s = specifiedFile->getContents(); 
   r = dynamic_pointer_cast<directory>(s)->getDirents();
   /*We want ot have last base file as a key to dirents*/ 
   wordvec tokenizedPath = split(words.at(1), "/");
   string lastBaseFile = tokenizedPath.at(tokenizedPath.size()-1);
   map<string, inode_ptr>:: iterator x = r.find(lastBaseFile);
   /*If a directory of the same name as the one we want to create 
    *already exists we want to throw an error*/  
   if(x!=r.end())
   { 
      throw command_error("Error: directory name already exists\n");
   }
   /*Else we are ready to make a directory from our pointer*/ 
   inode_ptr newDir;  
   newDir = specifiedFile->getContents()->mkdir(lastBaseFile); 
   inode_ptr itself = newDir; 
   newDir->addDirent(".", itself); 
   newDir->addDirent("..", specifiedFile); 
   /*Add the new directory as a dirent of its parent as well*/ 
   specifiedFile->addDirent(lastBaseFile, newDir);  
}

/*Function to create a new prompt. Checks for valid arguments then it
 *Copies the relevant strings in words, adding spaces and sets the 
 *new prompt to the result of this*/
void fn_prompt (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size()<2)
   {
      throw command_error("Error: invalid new prompt specified \n"); 
   }
   string str = "";
   /*We want to add an empty whitespace character so that there is 
    *spacing between each of the words*/
   for(int i=1;i<words.size();i++)str+=words.at(i)+" ";
   state.newPrompt(str);
}

/*Checks to make sure there are no arguments. Gets the current working
 *directory and a string vector which we append the names of dirs to
 *while working upwards toward the root. At the end it iterates 
 *backwards through the array spitting out the results to output along
 *with backslash characters for outputting purposes*/
void fn_pwd (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size()>1) 
   {
      throw command_error("Error: pwd should not have arguments"); 
   }
   /*If we are at the root directory we can just print a slash and
    *end the line without having to do any work*/ 
   else if(state.getCwd()==state.getRoot()) cout<<"/"<<endl; 
   /*Else we have to compute an actual path*/ 
   else
   {
      inode_ptr p = state.getCwd(); 
      wordvec toReverse; 
      while(p != state.getRoot())
      {
         toReverse.push_back(p->getName()); 
         map<string, inode_ptr> s;
         base_file_ptr r = p->getContents(); 
         s = dynamic_pointer_cast<directory>(r)->getDirents();
         inode_ptr dad = s.at(".."); 
         p = dad; 
      }
      for(int i =toReverse.size()-1; i>=0; i--)
      {
         cout<<"/"<<toReverse.at(i); 
      }
      cout<<endl;
   } 
}

/*Simply checks to make sure that a filepath has been specified, if
 *so it finds the path and assigns an inode_ptr to the file that has
 *been specified. It removes its descendent node and all its 
 *connections with the tree*/ 
void fn_rm (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size()<=1)
   {
      throw command_error("Error: rm: no path specified \n");
   }
   inode_ptr specifiedFile = findPathrm(words.at(1), state.getCwd());
   wordvec tokenizedPath = split(words.at(1), "/");
   string lastBaseFile = tokenizedPath.at(tokenizedPath.size()-1);
   /*getContents because else we would need to do a special cast to
    *get back a directory or something that can remove files*/  
   specifiedFile->getContents()->remove(lastBaseFile);
}

/*This function finds the filepath first, then creates and copies 
 *the dirents of the file at the end of the path. It then iterates
 *through the dirents and checks to see whether or not they are a 
 *directory. If they are a directory and we are not looking at a 
 *parent or the current directory itself as dirent keys (all descendent
 *directories), it appends their name to the filepath to recursively
 *call itself on the lower directory with the new directory's name 
 *appended to its argument. If it is a file we can simply call the 
 *remove function on it, no need for recursion because in yshell files
 *only hold text. After doing this to all of its dirents, we remove
 *the specified file as well*/ 
void fn_rmr (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   /*It does this with arguments of multiple paths*/ 
   for(int j=1; j<words.size(); j++)
   {
       /*Apologies for the poorly descriptive variable names, I could
        *not find a way to make my code more concise to reduce 
        *character count per line for checksource other than just
        *making the variable names tiny*/   
       inode_ptr p; 
       p = findPath(words.at(j), state.getCwd());
       map<string, inode_ptr> q; 
       base_file_ptr r = p->getContents(); 
       q = dynamic_pointer_cast<directory>(r)->getDirents();
       for(auto& i: q) 
       {
          if(i.first!=".." and i.first!="." )
          {
             /*If we are currently looking at a directory*/ 
             if(i.second->isDirectory==1)
             {
                wordvec temp; 
                /*We want our arguments when we call recursive remove
                 *again to still contain the same function call just
                 *for syntactic purposes and to avoid strange errors*/  
                temp.push_back(words.at(0));
                string str = words.at(j);
                if(words.at(j)!="/")str+="/"; 
                str+=i.first; 
                temp.push_back(str); 
                fn_rmr(state, temp); 
             }
             else
             {
                wordvec temp;
                temp.push_back(words.at(0)); 
                string str = words.at(j); 
                if(words.at(j)!="/")str+="/";
                str+=i.first; 
                temp.push_back(str); 
                fn_rm(state,temp); 
             }
          }
       }
       /*The function must remove itself after going through all its
        *dirents and descendant nodes*/    
       fn_rm(state, words); 
   }
}

