/**
 * 
 */
#include <physfs.h>
#include "libfileaccess.h"

struct RecursiveCallbackData {
	RecursiveCallbackData(FileList &ref, const std::string &pat, bool useRecursion)
		: fileList(ref), pattern(pat), useRecursion(useRecursion)
		{}
	
	FileList &fileList;
	const std::string pattern;
	bool useRecursion;
};

static void directory_recursive_callback(void *d, const char *origdir, const char *fname)
{
	RecursiveCallbackData *data = (RecursiveCallbackData*)d;
	
	// Intermediary variables
	std::string dir = std::string(origdir)+std::string("/");
	std::string filename = dir+std::string(fname);
	
	// Recursively iterate subdirectories
	if(PHYSFS_isDirectory(filename.c_str())) {
		if(data->useRecursion)
			PHYSFS_enumerateFilesCallback( filename.c_str(), directory_recursive_callback, d);
	}
	
	else {
		// Find the string position where the filename extension starts
		size_t dotPos = filename.rfind('.');
		
		// If no extension pattern, or the extension of the filename matches,
		// append the file to the file list.
		if( data->pattern.size()==0  || (dotPos!=std::string::npos && std::string(filename, dotPos+1)==data->pattern) )
			data->fileList.push_back(filename);
	}
}

/**
 * Generates a \c FileList based on the given parameters.
 * 
 * \param topDir The top-level directory to generate a file list from.
 * \param extension The file extension to limit the file list to, if empty allow all files.
 * \param useRecursion If true, will recursively traverse all subdirectories.
 * \return A \c FileList of full PHYSFS-local filenames.
 * \sa FileList
 */
FileList directory_file_list ( const std::string& topDir, const std::string& extension, bool useRecursion )
{
	FileList list;
	RecursiveCallbackData data(list,extension, useRecursion);
	
	PHYSFS_enumerateFilesCallback( topDir.c_str(), directory_recursive_callback, &data);
	
	return list;
}
