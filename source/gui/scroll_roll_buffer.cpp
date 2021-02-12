#include "scroll_roll_buffer.hpp"
#include <cmath>

namespace PowerRonin::Interface
{
	ScrollingBuffer::ScrollingBuffer()
	{
		max_size = 2000;
		offset = 0;
		data.reserve(max_size);
	}

	void ScrollingBuffer::add_point(const float _x, const float _y)
	{
		if (data.size() < max_size)
		{
			data.push_back(ImVec2(_x, _y));
		}
		else
		{
			data[offset] = ImVec2(_x, _y);
			offset = (offset + 1) % max_size;
		}
	}

	void ScrollingBuffer::erase()
	{
		if (!data.empty())
		{
			data.shrink(0);
			offset = 0;
		}
	}

	RollingBuffer::RollingBuffer()
	{
		span = 10.0F;
		data.reserve(2000);
	}

	void RollingBuffer::add_point(const float _x, const float _y)
	{
		const float xmod = std::fmodf(_x, span);
		if (!data.empty() && xmod < data.back().x)
		{
			data.shrink(0);
		}
		data.push_back(ImVec2(xmod, _y));
	}
}
