/**
 * 
 */
#ifndef LOADHANDALL_H
#define LOADHANDALL_H
#include <string>
#include <map>

#include "loadhandgeneric.h"
#include "libfileaccess.h"

/**
 * Macro to implement the sysResource::get for a data type.
 * \c handler is the \c LoadHandlerAll to implement the getter for.
 * \c dataType is the returned data type.
 */
#define IMPLEMENT_LHA_SYSRESOURCE_GET(handler, dataType) \
	template<> \
	const dataType *sysResource::get(const std::string &id) \
	{	return handler.get(id); }

/**
 * A load handler which loads all files from a given folder with
 * a specific file extension.
 */
template <class Data>
class LoadHandlerAll : public GenericLoadHandler {
	public:
		LoadHandlerAll(const std::string &baseDirectory, const std::string &extension="")
			: m_baseDirectory(baseDirectory), m_extension(extension)
			{}
		virtual ~LoadHandlerAll()
			{ unload(); }
		
		void load();
		void unload();
		
		const Data *get(const std::string &name) {
			MapIterator i = m_data.find(name);
			return (i!=m_data.end()) ? i->second : NULL;
		}
		
		virtual void load_file(const std::string &file)=0;
		
	protected:
		void insert(const std::string &name, Data *item)
		{ m_data[name] = item; }
		
	private:
		typedef typename std::map<std::string, Data*> MapType;
		typedef typename MapType::iterator MapIterator;
		
		MapType m_data;
		std::string m_baseDirectory;
		std::string m_extension;
};

template <class Data>
void LoadHandlerAll<Data>::load()
{
	FileList fileList = directory_file_list(m_baseDirectory, m_extension);
	
	for(FileList::iterator i=fileList.begin(); i!=fileList.end(); ++i) {
		load_file(*i);
	}
}

template <class Data>
void LoadHandlerAll<Data>::unload()
{
	for(MapIterator i=m_data.begin(); i!=m_data.end(); ++i) {
		delete i->second;
	}
	m_data.clear();
}

#endif
