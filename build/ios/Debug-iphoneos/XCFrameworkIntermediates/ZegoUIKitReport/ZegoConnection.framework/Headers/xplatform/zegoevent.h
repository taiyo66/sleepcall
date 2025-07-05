#if !defined(_ZEGOEVENT_INC_)
#define _ZEGOEVENT_INC_
#pragma once

#include "zegotypes.h"
#include "zegoexcept.h"

typedef	void* hzegoevent;

#ifdef __cplusplus
extern "C" {
#endif
	
	/**
	 create a event.
	 
	 @manual_reset - indicate type of event. 
	 If this parameter is TRUE, the function creates a manual-reset event object, 
	 which requires the use of the zegoevent_reset function to set the event state to nonsignaled. 
	 If this parameter is FALSE, the function creates an auto-reset event object, 
	 and system automatically resets the event state to nonsignaled after a single waiting thread has been released.
	 
	 @init_state- initialized state of event.
	 If this parameter is TRUE, the initial state of the event object is signaled; otherwise, it is nonsignaled.
	 
	 @return	- return a event handle if success, otherwise return NULL.
	 */
	_ZEGO_API hzegoevent zegoevent_create(boolean manual_reset, boolean init_state);
	
	/**
	 destroy a event.
	 
	 @handle	- event handle created by zegoevent_create.
	 
	 @return	- return 0 if success, otherwise return error code.
	 */
	_ZEGO_API int32	zegoevent_destory(hzegoevent handle);
	
	/**
	 sets the specified event to the signaled state.
	 
	 @handle	- event handle.
	 
	 @return	- return 0 if success, otherwise return error code.
	 */
	_ZEGO_API int32	zegoevent_signal(hzegoevent handle);
	
	/**
	 determines the specified event is signaled or not. 
	 
	 @handle	- event handle.
	 
	 @return	- return true the event is in the signaled state, otherwise return false.
	 */
	_ZEGO_API boolean	zegoevent_issignaled(hzegoevent handle);
	
	/**
	 sets the specified event to the nonsignaled state.
	 
	 @handle	- event handle.
	 
	 @return	- return 0 if success, otherwise return error code.
	 */
	_ZEGO_API int32	zegoevent_reset(hzegoevent handle);
	
	/**
	 wait indefinitely for the event to be signaled.
	 
	 @handle	- event handle.
	 
	 @return	- return 0 if success, otherwise return error code.
	 */
	_ZEGO_API int32	zegoevent_wait(hzegoevent handle);
	
	/**
	 wait up until timeout has passed for the event to be signaled.
	 
	 @handle	- event handle.
	 @timeout   - the time-out interval, in milliseconds.
	 If a nonzero value is specified, the function waits until the event is signaled or the interval elapses. 
	 If @timeout is zero, the function does not enter a wait state if the object is not signaled; it always returns immediately.
	 If @timeout is -1, the function will return only when the object is signaled. 
	 
	 @return	- return 0 if success, otherwise return error code.
	 */
	_ZEGO_API int32	zegoevent_timedwait(hzegoevent handle, int64 timeout /*in miliseconds*/);
	
#ifdef __cplusplus
};
#endif

#ifdef __cplusplus

class _ZEGO_CLS CZEGOEvent {
public:
	CZEGOEvent(boolean manual_reset = false, boolean init_state = false) { 
		m_hEvent = zegoevent_create(manual_reset, init_state); 
	}
	
	virtual ~ CZEGOEvent(void) {
		if(m_hEvent) {
			zegoevent_destory(m_hEvent); 
			m_hEvent = NULL;
		}
	}
	
	inline boolean Wait(int64 millisesonds = -1) const {
		return zegoevent_timedwait(m_hEvent, millisesonds) == 0;
	}
	
	inline void Post(void) const {
		zegoevent_signal(m_hEvent);
	}
	
	inline void Reset(void) {
		zegoevent_reset(m_hEvent);
	}
	
	inline boolean IsSignaled(void) const {
		return zegoevent_issignaled(m_hEvent);
	}
	
private:
	hzegoevent	m_hEvent;
};
#endif

#endif /* _ZEGOEVENT_INC_ */
