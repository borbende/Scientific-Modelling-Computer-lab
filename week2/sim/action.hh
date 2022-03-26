//Run action header file.

#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "generator.hh"

class MyActionInitialization : public G4VUserActionInitialization
{
public:
	MyActionInitialization();
	~MyActionInitialization();
	
	virtual void Build() const; //Runs particles and does the computing.


};


#endif
