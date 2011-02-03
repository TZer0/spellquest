/**
 * Implements the resource system, and its external interface.
 */
#include "resource.h"
#include "loadhandgeneric.h"


/**
 * Keeps a single static instance of the resource system which is returned upon calling.
 * \return The resource system singleton
 */
sysResource& sysResource::instance()
{
	static sysResource singleton;
	return singleton;
}

/**
 * Resource system constructor
 */
sysResource::sysResource() : m_loadedCounter(0)
{
}


/**
 * Resource system destructor
 */
sysResource::~sysResource()
{
}


/**
 * List of all existing load handlers.
 * They will be loaded in sequence.
 * When unloaded they are executed in reverse sequence.
 */
const GenericLoadHandler *sysResource::s_handlerArray[] =
{	NULL };


/**
 * Loads all load handlers.
 */
void sysResource::load()
{
	for( ;s_handlerArray[m_loadedCounter]; m_loadedCounter++) {
		s_handlerArray[m_loadedCounter]->load();
	}
}


/**
 * Unloads all load handlers, in reverse order that they were loaded
 */
void sysResource::unload()
{
	m_loadedCounter--; // Have to do this to make sure it points over a valid array member
	for( ;m_loadedCounter>=0; m_loadedCounter--) {
		s_handlerArray[m_loadedCounter]->unload();
	}
}
