//------------------------------------------------------------------------
// Project     : SDK Base
// Version     : 1.0
// 
// Category    : Helpers
// Filename    : base/source/timer.h
// Created by  : Steinberg, 05/2006
// Description : Timer class for receiving tiggers at regular intervals
// 
//-----------------------------------------------------------------------------
// LICENSE
// (c) 2013, Steinberg Media Technologies GmbH, All Rights Reserved
//-----------------------------------------------------------------------------
// This Software Development Kit may not be distributed in parts or its entirety  
// without prior written agreement by Steinberg Media Technologies GmbH. 
// This SDK must not be used to re-engineer or manipulate any technology used  
// in any Steinberg or Third-party application or software module, 
// unless permitted by law.
// Neither the name of the Steinberg Media Technologies nor the names of its
// contributors may be used to endorse or promote products derived from this 
// software without specific prior written permission.
// 
// THIS SDK IS PROVIDED BY STEINBERG MEDIA TECHNOLOGIES GMBH "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL STEINBERG MEDIA TECHNOLOGIES GMBH BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//----------------------------------------------------------------------------------

#ifndef __timer__
#define __timer__

#include "fobject.h"

namespace Steinberg {

namespace SystemTime {
	int32 getTicks ();	///< Retrieves the number of milliseconds that have elapsed since the system was started
}

class Timer;

//------------------------------------------------------------------------
/** @class ITimerCallback 
	
	Implement this callback interface to receive triggers from a timer. 
	Note: This interface is intended as a mix-in class and therefore does not provide refcounting.
	
	@see Timer */
//------------------------------------------------------------------------
class ITimerCallback
{
public:
	/** This method is called at the end of each interval. 
		
		\param timer The timer which calls. 
	*/
	virtual void onTimer (Timer* timer) = 0;	
};

// -----------------------------------------------------------------
/** @class Timer

	Timer is a class that allows you to receive triggers at regular intervals.

	Note: The timer class is an abstract base class with (hidden) platform specific subclasses.



	Usage:
	@code
	class TimerReceiver : public FObject, public ITimerCallback
	{
		...
		virtual void onTimer (Timer* timer)
		{
			// do stuff
		}
		...
	};

	TimerReceiver* receiver =  new TimerReceiver ();
	Timer* myTimer = Timer::create (receiver, 100); // interval: every 100ms
	
	...
	...

	if (myTimer)
		myTimer->release ();
	if (receiver)
		receiver->release ();
	@endcode

	@see ITimerCallback
	*/
// -----------------------------------------------------------------
class Timer : public FObject
{
public:
	/** Create a timer with a given interval
		\param callback The receiver of the timer calls.
		\param intervalMilliseconds The timer interval in milliseconds.
		\return The created timer if any, callers owns the timer. The timer starts immediately. 
	*/
	static Timer* create (ITimerCallback* callback, uint32 intervalMilliseconds);

	virtual void stop () = 0;  ///< Stop the timer.
};

// -----------------------------------------------------------------
/** @class DisableDispatchingTimers

	Disables dispatching of timers for the live time of this object

	*/
// -----------------------------------------------------------------
class DisableDispatchingTimers
{
public:
	DisableDispatchingTimers ();
	~DisableDispatchingTimers ();
private:
	bool oldState;
};

} // namespace Steinberg

#endif
