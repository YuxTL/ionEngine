
#pragma once

#include <ionCore.h>
#include <ionFramework.h>


class CTimeManager : public Singleton<CTimeManager>
{

public:

	class CUpdateTick : public IEventListener, public IEvent
	{

	public:
		
		f64 GetTick() const;
		f64 GetElapsedTime() const;
		f64 GetMaxDuration() const;
		f64 GetAccumulator() const;

	protected:

		friend class CTimeManager;
		CUpdateTick(f64 const Tick, f64 const MaxDuration);
		void Update(f64 const Elapsed);

		f64 Tick;
		f64 MaxDuration;
		f64 Accumulator;

	};

	void Init();
	void Update();

	void SkipElapsedTime();
	f64 GetElapsedTime() const;
	f64 GetRunTime() const;

	CUpdateTick * MakeUpdateTick(f64 const Tick, f32 const MaxDuration = 1.0);

protected:

	f64 ElapsedTime;
	f64 RunTime;
	f64 LastTime;

	vector<CUpdateTick *> UpdateTicks;

private:

	friend class Singleton<CTimeManager>;
	CTimeManager();

};
