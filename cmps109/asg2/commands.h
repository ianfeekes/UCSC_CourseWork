// $Id: commands.h,v 1.11 2016-01-14 14:45:21-08 - - $

#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include <unordered_map>
using namespace std;

#include "file_sys.h"
#include "util.h"

// A couple of convenient usings to avoid verbosity.

using command_fn = void (*)(inode_state& state, const wordvec& words);
using command_hash = unordered_map<string,command_fn>;

// command_error -
//    Extend runtime_error for throwing exceptions related to this 
//    program.

class command_error: public runtime_error {
   public: 
      explicit command_error (const string& what);
};

// execution functions -

/*fn_comm added as an empty function to handle comments*/ 
void fn_comm   (inode_state& state, const wordvec& words);
void fn_cat    (inode_state& state, const wordvec& words);
void fn_cd     (inode_state& state, const wordvec& words);
void fn_echo   (inode_state& state, const wordvec& words);
void fn_exit   (inode_state& state, const wordvec& words);
void fn_ls     (inode_state& state, const wordvec& words);
void fn_lsr    (inode_state& state, const wordvec& words);
void fn_make   (inode_state& state, const wordvec& words);
void fn_mkdir  (inode_state& state, const wordvec& words);
void fn_prompt (inode_state& state, const wordvec& words);
void fn_pwd    (inode_state& state, const wordvec& words);
void fn_rm     (inode_state& state, const wordvec& words);
void fn_rmr    (inode_state& state, const wordvec& words);

/*Returns an inode that corresponds with the correct file
 *based on the path specified eg /thisDir/thatDir/file
 *would iterate from the root "/" to thisDir and then to
 *that Dir. It throws an error if the path given is not
 *valid*/ 
inode_ptr findPath(string path, inode_ptr currentDirectory);

/*Function that behaves similarly to findPath however it 
 *goes one file less deep because rmr and rm commands 
 *want to invoke a directory's remove command*/ 
inode_ptr findPathrm(string path, inode_ptr currentDirectory);

command_fn find_command_fn (const string& command);

// exit_status_message -
//    Prints an exit message and returns the exit status, as recorded
//    by any of the functions.

int exit_status_message();
class ysh_exit: public exception {};

#endif

