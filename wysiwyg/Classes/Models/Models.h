#ifndef __MODELS__H__
#define __MODELS__H__

#include <list>

class AbstractLetter;

typedef std::list<AbstractLetter> LetterSequence;

//TODO: tmp part. move all settings and defines to separate header file
#define SPECIAL_LETTER_CHARACTER	'*'
#define DEFAULT_POINTS_FOR_LETTER	10
class AbstractLetter
{

protected:
	char m_symbol; 
	AbstractLetter( char symbol ) : m_symbol( symbol ) {}

public:

	//returns true if rhs mathces current letter
	virtual bool validate( const AbstractLetter & rhs ) = 0;

	char getRepresentation() const
	{
		return this->m_symbol;
	}

	virtual unsigned int getPoints() const
	{
		return DEFAULT_POINTS_FOR_LETTER;
	}
};


class NormalLetter : public AbstractLetter
{
public: 
	NormalLetter( char symbol ) : AbstractLetter( symbol ) {}

	virtual bool validate( const AbstractLetter & rhs )
	{
		if ( this->m_symbol == rhs.getRepresentation() )
			return true;
		else
			return false;
	}

};


class SpecialLetter : public AbstractLetter
{
public:
	SpecialLetter() : AbstractLetter( SPECIAL_LETTER_CHARACTER ) {}

	virtual bool validate( const AbstractLetter & rhs )
	{
		return true;	//our special letter matches everything!
	}
};


class Word
{
protected:
	LetterSequence * m_letters;
public:
	virtual bool validate( const Word & rhs )
	{
		LetterSequence * rhs_letters = rhs.getLetters();
		if ( this->m_letters->size() != rhs_letters->size() )
			return false;	
		//TODO
		return true;
	}

	LetterSequence * getLetters() const
	{
		return this->m_letters;
	}
};

#endif