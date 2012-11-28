#ifndef __MODELS__H__
#define __MODELS__H__

#include <vector>

class AbstractLetter;

typedef std::vector<AbstractLetter*> LetterSequence;

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

	virtual unsigned int getPoints() const
	{
		return DEFAULT_POINTS_FOR_LETTER / 2;
	}
};


class Word
{
protected:
	LetterSequence * m_letters;
public:
	//TODO
	~Word() {}
	virtual bool validate( const Word & rhs )
	{
		LetterSequence * rhs_letters = rhs.getLetters();
		if ( this->m_letters->size() != rhs_letters->size() )
			return false;
		//now compare each letter
		for ( size_t i = 0; i < rhs_letters->size(); i++ )
			if ( rhs_letters->at( i )->validate( *this->m_letters->at( i ) ) != true )
				return false;
		return true;
	}

	LetterSequence * getLetters() const
	{
		return this->m_letters;
	}

	Word( const std::string str )
	{
		if ( str.size() > 0 )
			this->m_letters = new LetterSequence();
		else
			return;
		for ( size_t i = 0; i < str.size(); i++ )
			this->m_letters->push_back( new NormalLetter( str[i] ) );
	}

	Word( LetterSequence * seq )
	{
		this->m_letters = seq;
	}

	unsigned int getPoints()
	{
		unsigned int points = 0;

		for ( LetterSequence::iterator it = this->m_letters->begin(); it != this->m_letters->end(); ++it )
			points += (*it)->getPoints();

		return points;
	}
};

#endif