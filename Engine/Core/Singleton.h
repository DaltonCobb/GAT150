#pragma once

namespace nc
{
	template<typename T>
	class Singleton
	{
	public:
		Singleton(const Singleton&) = delete;//coppy constructor
		Singleton& operator = (const Singleton&) = delete;//assignment operator


		static T& Instance()
		{
			static T instance;
			return instance;
		}

	protected:
		Singleton() {}
	};
}