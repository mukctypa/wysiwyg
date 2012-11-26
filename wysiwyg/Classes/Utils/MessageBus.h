#ifndef MESSAGEBUS_H_
#define MESSAGEBUS_H_

#include <queue>
#include <list>
#include <assert.h>
#include "pthread.h"

template < typename _sndMsg, typename _rcvMsg > class MessageBus
{
protected:

	std::queue< _sndMsg > _sndQueue;
	std::queue< _rcvMsg > _rcvQueue;
	pthread_mutex_t _mymutex;
	unsigned long _counter;

public:
	typedef std::list< _rcvMsg > reciveMsgContainer;
	typedef std::list< _sndMsg > sendMsgContainer;

	/*
	 * returns size of rcvQueue
	 */
	size_t rcvSize()
	{
		pthread_mutex_lock( &this->_mymutex );
		size_t result = _rcvQueue.size();
		pthread_mutex_unlock( &this->_mymutex );
		return result;
	}


	/*
	 * returns size of sndQueue
	 */
	unsigned long sndSize()
	{
		pthread_mutex_lock( &this->_mymutex );
		size_t result = _sndQueue.size();
		pthread_mutex_unlock( &this->_mymutex );
		return result;
	}


	bool rcvEmpty()
	{
		pthread_mutex_lock( &this->_mymutex );
		bool result = _rcvQueue.empty();
		pthread_mutex_unlock( &this->_mymutex );
		return result;
	}


	bool sndEmpty()
	{
		pthread_mutex_lock( &this->_mymutex );
		bool result = _sndQueue.empty();
		pthread_mutex_unlock( &this->_mymutex );
		return result;
	}


	/*
	 * returns last message from rcvQueue and removes it
	 */
	_rcvMsg getRcv()
	{
		pthread_mutex_lock( &this->_mymutex );
		_rcvMsg msg =  _rcvQueue.front();
		_rcvQueue.pop();
		pthread_mutex_unlock( &this->_mymutex );
		return msg;
	}


	/*
	 * puts a message to rcvQueue
	 */
	unsigned long putRcv( const _rcvMsg & _msg )
	{
		pthread_mutex_lock( &this->_mymutex );
		_rcvQueue.push( _msg );
		_counter++;
		pthread_mutex_unlock( &this->_mymutex );
		return _counter;
	}


	/*
	 * returns all messages from rcvQueue
	 */
	reciveMsgContainer * bulkGetRcv()
	{
		pthread_mutex_lock( &this->_mymutex );
		if ( this->_rcvQueue.empty() )
		{
			pthread_mutex_unlock( &this->_mymutex );
			return NULL;
		}
		reciveMsgContainer * result = new reciveMsgContainer();
		while ( !this->_rcvQueue.empty() )
		{
			result->push_back( *this->_rcvQueue.front() );
			this->_rcvQueue.pop();
		}
		pthread_mutex_unlock( &this->_mymutex );
		return result;
	}


	_sndMsg getSnd( )
	{
		pthread_mutex_lock( &this->_mymutex );
		_sndMsg msg = this->_sndQueue.front();
		_sndQueue.pop();
		pthread_mutex_unlock( &this->_mymutex );
		return msg;
	}

	_rcvMsg * getRcvAtomic()
	{
		_rcvMsg * result = NULL;
		pthread_mutex_lock( &this->_mymutex );
		if ( !this->_rcvQueue.empty() )
		{
			result = new _rcvMsg();
			*result = _rcvQueue.front();
			_rcvQueue.pop();
		}
		pthread_mutex_unlock( &this->_mymutex );
		return result;
	}

	_sndMsg * getSndAtomic()
	{
		_sndMsg * result = NULL;
		pthread_mutex_lock( &this->_mymutex );
		if ( !this->_sndQueue.empty() )
		{
			result = new _sndMsg();
			*result = _sndQueue.front();
			_sndQueue.pop();
		}
		pthread_mutex_unlock( &this->_mymutex );
		return result;
	}


	/*
	* puts a message to sndQueue
	*/
	unsigned long putSnd( const _sndMsg & _msg )
	{
		pthread_mutex_lock( &this->_mymutex );
		_sndQueue.push( _msg );
		_counter++;
		pthread_mutex_unlock( &this->_mymutex );
		return _counter;
	}


	/*
	 * returns all messages from sndQueue
	*/
	sendMsgContainer * bulkGetSnd()
	{
		pthread_mutex_lock( &this->_mymutex );
		if ( this->_sndQueue.empty() )
		{
			pthread_mutex_unlock( &this->_mymutex );
			return NULL;
		}
		sendMsgContainer * result = new sendMsgContainer();
		while ( !this->_sndQueue.empty() )
		{
			result->push_back( *this->_sndQueue.front() );
			this->_sndQueue.pop();
		}
		pthread_mutex_unlock( &this->_mymutex );
		return result;
	}


	MessageBus() : _sndQueue(), _rcvQueue()
	{
		pthread_mutex_init( &this->_mymutex, NULL );
	}


	~MessageBus()
	{
		pthread_mutex_destroy( &this->_mymutex );
	}

};

#endif
