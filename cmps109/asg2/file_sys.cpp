// $Id: file_sys.cpp,v 1.6 2018-06-27 14:44:57-07 - - $

#include <iostream>
#include <stdexcept>
#include <unordered_map>

using namespace std;

#include "debug.h"
#include "file_sys.h"

int inode::next_inode_nr {1};

struct file_type_hash {
   size_t operator() (file_type type) const {
      return static_cast<size_t> (type);
   }
};

ostream& operator<< (ostream& out, file_type type) {
   static unordered_map<file_type,string,file_type_hash> hash {
      {file_type::PLAIN_TYPE, "PLAIN_TYPE"},
      {file_type::DIRECTORY_TYPE, "DIRECTORY_TYPE"},
   };
   return out << hash[type];
}

/*The default constructor for inode state has been modified*/ 
inode_state::inode_state() {
   DEBUGF ('i', "root = " << root << ", cwd = " << cwd
          << ", prompt = \"" << prompt() << "\"");
   /*Since we have only one state it makes sense that we should 
    *immediately initialize our root file, which will always be a 
    *directory, with an empty name*/    
   inode rootFile(file_type::DIRECTORY_TYPE);
   root = make_shared<inode>(rootFile);
   /*This allows it so that if we keep doing "cd .." at our root file
    *it won't give any segmentation faults, it'll just keep on 
    *pointing to itself*/    
   parentDir = root;  
   /*Also our initial current working directory is set ot the root 
    *when we have our initial state*/   
   cwd = root;
   /*We want our root directory to simply be a forward slash*/ 
   root->setName("/"); 
   /*For our root file we want to give it the dot and the dot dot 
    *fields that all initially empty directories should have. This
    *is just the special case where the root and the parent are the
    *same*/    
   rootFile.addDirent(".", root); 
   rootFile.addDirent("..", parentDir);    
}

void inode_state::setParentDir(inode_ptr p)
{
  parentDir = p; 
}

void inode_state::changeDir(inode_ptr newCwd) 
{
   cwd = newCwd; 
}

const string& inode_state::prompt() const { return prompt_; }

ostream& operator<< (ostream& out, const inode_state& state) {
   out << "inode_state: root = " << state.root
       << ", cwd = " << state.cwd;
   return out;
}

inode::inode(file_type type): inode_nr (next_inode_nr++) {
   switch (type) {
      case file_type::PLAIN_TYPE:
           contents = make_shared<plain_file>();
           isDirectory = 0; 
           break;
      case file_type::DIRECTORY_TYPE:
           /*Boolean operator is modified to be set in the inode 
            *constructor*/  
           isDirectory = 1; 
           contents = make_shared<directory>();
           break;
   }
   DEBUGF ('i', "inode " << inode_nr << ", type = " << type);
}

int inode::get_inode_nr() const {
   DEBUGF ('i', "inode = " << inode_nr);
   return inode_nr;
}

/*Added function to get an inode's parent directory*/
inode_ptr inode:: getParent()
{
   return dynamic_pointer_cast<directory>(contents)->getDirent(".."); 
}

void inode:: addDirent(string str, inode_ptr toAdd)
{
   dynamic_pointer_cast<directory>(contents)->setDirent(str, toAdd); 
}

file_error::file_error (const string& what):
            runtime_error (what) {
}

size_t plain_file::size() const {
   size_t size {0};
   size = data.size(); 
   for( auto word = data.begin(); word!=data.end();word++)
   {
      size+=word->size(); 
   }
   if(size>1)size-=1; 
   DEBUGF ('i', "size = " << size);
   return size;
}

/*Returns the wordvec*/ 
const wordvec& plain_file::readfile() const {
   DEBUGF ('i', data);
   return data;
}

/*Simply sets the file's data to the words argument, used in make*/
void plain_file::writefile (const wordvec& words) {
   DEBUGF ('i', words);
   data=words;  
}

void plain_file::remove (const string&) {
   throw file_error ("is a plain file");
}

inode_ptr plain_file::mkdir (const string&) {
   throw file_error ("is a plain file");
}

inode_ptr plain_file::mkfile (const string&) {
   throw file_error ("is a plain file");
}

directory::directory() {

}

/*Directories have their sizes determined by dirents.size() so this
 *method is easier*/ 
size_t directory::size() const {
   size_t size {0};
   DEBUGF ('i', "size = " << size);
   size=dirents.size(); 
   return size;
}

/*directories cannot create r/w so these two functions are good by
 *just throwing errors*/ 
const wordvec& directory::readfile() const {
   throw file_error ("is a directory");
}

void directory::writefile (const wordvec&) {
   throw file_error ("is a directory");
}

/*Removes a file or directory used in fn_rm it first tests to see if
 *it is a directory with children and throw an error so that non-
 *empty directories can't simply be destroyed*/ 
void directory::remove (const string& filename) {
   DEBUGF ('i', filename);
   map<string,inode_ptr>::iterator i = dirents.find(filename);
   if(i == dirents.end())
   {
      throw file_error("Error: removing file not found in dirents\n");
   }
   inode_ptr toRemove = dirents.at(filename); 
   /*Test to see if the file is a directory w/ more than root and self*/
   if(toRemove->isDirectory==1 and toRemove->getContents()->size()>2)
   {
      throw file_error("Error: cannot remove non-empty directory\n"); 
   }
   /*Make sure that the node doesn't point to anything to avoid memory
    *leaks and seg faults*/  
   toRemove->setContents(nullptr); 
   /*Make sure the base_file isn't visible from the parent directory 
    *either */  
   dirents.erase(i);  
}

/*Creates a new dir and add it to dirents*/ 
inode_ptr directory::mkdir (const string& dirname) {
   DEBUGF ('i', dirname);
   inode_ptr newDir = make_shared<inode>(file_type::DIRECTORY_TYPE);
   newDir->setName(dirname); 
   newDir->isDirectory = 1; 
   return newDir; 
}

/*Added code for a directory to make a plain file. Almost the same
 *as make dir, it just shuts the isDirectory boolean off. */ 
inode_ptr directory::mkfile (const string& filename) {
   inode_ptr newFile = make_shared<inode>(file_type::PLAIN_TYPE);
   newFile->setName(filename);
   newFile->isDirectory = 0; 
   DEBUGF ('i', filename);
   return newFile;
}

/*Consider MODIFYING this*/ 
void directory:: setDirent(string str, inode_ptr p)
{
   map<string, inode_ptr>:: iterator i = dirents.find(str);
   if(i!=dirents.end()) dirents.erase(str); 
   dirents.insert(pair<string, inode_ptr>(str, p));
}
