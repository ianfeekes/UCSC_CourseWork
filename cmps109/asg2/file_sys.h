// $Id: file_sys.h,v 1.6 2018-06-27 14:44:57-07 - - $

#ifndef __INODE_H__
#define __INODE_H__

#include <exception>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
using namespace std;

#include "util.h"

// inode_t -
//    An inode is either a directory or a plain file.

enum class file_type {PLAIN_TYPE, DIRECTORY_TYPE};
class inode;
class base_file;
class plain_file;
class directory;
using inode_ptr = shared_ptr<inode>;
using base_file_ptr = shared_ptr<base_file>;
ostream& operator<< (ostream&, file_type);

// inode_state -
//    A small convenient class to maintain the state of the simulated
//    process:  the root (/), the current directory (.), and the
//    prompt.

class inode_state {
   friend class inode;
   friend ostream& operator<< (ostream& out, const inode_state&);
   private:
      inode_ptr root {nullptr};
      inode_ptr cwd {nullptr};
      inode_ptr parentDir {nullptr};
      string prompt_ {"% "};
   public:
      inode_state (const inode_state&) = delete; // copy ctor
      inode_state& operator= (const inode_state&) = delete; // op=
      inode_state();
      const string& prompt() const;
      void setParentDir(inode_ptr); 
      /*Added function that allows us to see the parent directory*/ 
      inode_ptr getParentDir(){return parentDir;}
      /*Added function for our state to allos us to change prompt*/
      void newPrompt(const string& promptName){prompt_ = promptName;}
      /*Added function to return the current working directory for use
       *of pwd type commands*/  
      inode_ptr getCwd(){return cwd;}
      /*Added function to return the root for use of any commands*/ 
      inode_ptr getRoot(){return root;}
      /*Another added function for cd*/ 
      void changeDir(inode_ptr); 
};

// class inode -
// inode ctor -
//    Create a new inode of the given type.
// get_inode_nr -
//    Retrieves the serial number of the inode.  Inode numbers are
//    allocated in sequence by small integer.
// size -
//    Returns the size of an inode.  For a directory, this is the
//    number of dirents.  For a text file, the number of characters
//    when printed (the sum of the lengths of each word, plus the
//    number of words.
//    

class inode {
   friend class inode_state;
   private:
      static int next_inode_nr;
      int inode_nr;
      base_file_ptr contents;
      /*Added field name to hold the file's name. This could be done
       *in the base_file class but it is easier to just hold it here*/
      string name; 
   public:
      bool isDirectory; 
      inode (file_type);
      int get_inode_nr() const;
      /*Added function to retreive the base file the inode is pointing
       *to*/   
      base_file_ptr getContents(){return contents;}
      /*Largely used for removal and setting contents null */ 
      void setContents(base_file_ptr newContent){contents=newContent;}
      /*Retreives the private name field*/ 
      string getName(){return name;} 
      /*Allows us to manipulate the name of a file if needed*/ 
      /*CONSIDER MODIFYING OR DELETING SETNAME*/ 
      void setName(string str){name = str;}  
      /*Added method to allow us to add dirents to an inode thatpoints
       *to a base file of directory type*/   
      void addDirent(string str, inode_ptr toAdd);
      inode_ptr getParent();  
};

// class base_file -
// Just a base class at which an inode can point.  No data or
// functions.  Makes the synthesized members useable only from
// the derived classes.

class file_error: public runtime_error {
   public:
      explicit file_error (const string& what);
};

class base_file {
   protected:
      base_file() = default;
   public:
      virtual ~base_file() = default;
      base_file (const base_file&) = delete;
      base_file& operator= (const base_file&) = delete;
      virtual size_t size() const = 0;
      virtual const wordvec& readfile() const = 0;
      virtual void writefile (const wordvec& newdata) = 0;
      virtual void remove (const string& filename) = 0;
      virtual inode_ptr mkdir (const string& dirname) = 0;
      virtual inode_ptr mkfile (const string& filename) = 0;
      /*getDirents purely for the use of directories, I am just adding
       *this to base_file to be overridden by the directory class 
       *because inodes point to base_files and not necessarily 
       *directories*/  
      virtual map<string, inode_ptr>& getDirents() = 0;
};

// class plain_file -
// Used to hold data.
// synthesized default ctor -
//    Default vector<string> is a an empty vector.
// readfile -
//    Returns a copy of the contents of the wordvec in the file.
// writefile -
//    Replaces the contents of a file with new contents.

class plain_file: public base_file {
   private:
      wordvec data;
   public:
      virtual size_t size() const override;
      virtual const wordvec& readfile() const override;
      virtual void writefile (const wordvec& newdata) override;
      virtual void remove (const string& filename) override;
      virtual inode_ptr mkdir (const string& dirname) override;
      virtual inode_ptr mkfile (const string& filename) override;
      /*Added here to avoid compilation errors. Does nothing*/ 
      virtual map<string, inode_ptr>& getDirents() override{};
};

// class directory -
// Used to map filenames onto inode pointers.
// default ctor -
//    Creates a new map with keys "." and "..".
// remove -
//    Removes the file or subdirectory from the current inode.
//    Throws an file_error if this is not a directory, the file
//    does not exist, or the subdirectory is not empty.
//    Here empty means the only entries are dot (.) and dotdot (..).
// mkdir -
//    Creates a new directory under the current directory and 
//    immediately adds the directories dot (.) and dotdot (..) to it.
//    Note that the parent (..) of / is / itself.  It is an error
//    if the entry already exists.
// mkfile -
//    Create a new empty text file with the given name.  Error if
//    a dirent with that name exists.

class directory: public base_file {
   private:
      // Must be a map, not unordered_map, so printing is lexicographic
      map<string,inode_ptr> dirents;
   public:
      /*Default constructor for a directory*/ 
      directory();
      virtual size_t size() const override;
      virtual const wordvec& readfile() const override;
      virtual void writefile (const wordvec& newdata) override;
      virtual void remove (const string& filename) override;
      virtual inode_ptr mkdir (const string& dirname) override;
      virtual inode_ptr mkfile (const string& filename) override;
      /*Added function to get the dirent of a given name*/ 
      inode_ptr getDirent(string name){return dirents.at(name);}
      /*Added function to get all dirents, used in most commands*/
      virtual map<string, inode_ptr>& getDirents() override 
         {return dirents;} 
      /*Added method setDirent takes in a string and an inode pointer
       *erases dirent members with keys that have the same string so 
       *we don't have extra unwanted dirents, and then we insert the
       *new pair passed in by the arguments*/
     virtual void setDirent(string str, inode_ptr p); 
};

#endif

