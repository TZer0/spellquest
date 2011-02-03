/**
 *
 */
#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

// Forward declarations
class GenericLoadHandler;

/**
 * Singleton class for the resource system.
 */
class sysResource
{
	public:
		static sysResource &instance();
		
		void load();
		void unload();
		
		/**
		 * Each load handler implements a specialized version of this method.
		 * The returned data type is \c const, to prevent modification of the object
		 * from external sources.
		 * 
		 * Example usage:
		 * \code
		 * const SpellcardData *spData = sysResource::instance().get<SpellcardData>("spellId");
		 * \endcode
		 */
		template <class Type>
		const Type *get(const std::string &id);
	private:
		sysResource();
		~sysResource();
		
		// Variables
		static const GenericLoadHandler *s_handlerArray[];
		int m_loadedCounter; ///< Counter for the number of load handlers loaded from #s_handlerArray
};

#endif
