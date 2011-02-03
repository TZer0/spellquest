/**
 * Library for file access functions.
 */
#ifndef LIBFILEACCESS_H
#define LIBFILEACCESS_H
#include <vector>
#include <string>

typedef std::vector<std::string> FileList; ///< A structure intented to point to a list of filenames.
FileList directory_file_list(const std::string &topDir, const std::string &extension="", bool useRecursion=true);

#endif
