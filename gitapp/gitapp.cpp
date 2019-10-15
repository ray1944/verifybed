#include <iostream>
#include <git2.h>
#include "gitappconfig.h"
using namespace std;

int main(int argc, const char* argv[]) {
   git_repository * repo;
   int error;
   
   error = git_libgit2_init();
   if (error == 0) {
      cout << "libgit2 init failed." << endl;
   }
   error = git_repository_open(&repo, "./");

   
   if (error < 0) {
      const git_error *e = giterr_last();
      cout << "Error "<< error << ": "<< e->klass << ". " << e->message << endl;
      exit(error);
   }

   return 0;
}