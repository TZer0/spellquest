/**
 * 
 */
#ifndef LOADHANDGENERIC_H
#define LOADHANDGENERIC_H

/**
 * Generic data loading handler.
 * To implement more specific data loading routines
 * inherit this base class.
 */
class GenericLoadHandler
{
	public:
		virtual void load()=0;
		virtual void unload()=0;
		
	private:
		
};

#endif
