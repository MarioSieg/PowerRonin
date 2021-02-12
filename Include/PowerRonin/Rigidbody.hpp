#pragma once

namespace PowerRonin
{
	/* 3D physics rigidbody */
	class Rigidbody final
	{
	public:
		float Mass = 1.f;
		bool IsKinematic = false;
	};
}
