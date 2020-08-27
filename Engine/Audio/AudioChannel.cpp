#include "pch.h"
#include "AudioChannel.h"

namespace nc
{
bool AudioChannel::IsPlaying()
{
	bool isPlaying = false;
	if (m_channel == nullptr )
	{
		m_channel->isPlaying(&isPlaying);
		//<call the method isPlaying() on m_channel, pass in the address of the bool isPlaying>

	} 
	return isPlaying;
}
	

void AudioChannel::Stop()
{
	if (IsPlaying())
	{
		//<call the method stop() on m_channel>
		m_channel->stop();
	}
}

}
