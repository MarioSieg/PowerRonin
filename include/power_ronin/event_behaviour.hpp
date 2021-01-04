#pragma once

namespace power_ronin
{
	class IEventBehaviour
	{
	public:
		IEventBehaviour() noexcept = default;
		IEventBehaviour(const IEventBehaviour&) noexcept = default;
		IEventBehaviour(IEventBehaviour&&) noexcept = default;
		auto operator=(const IEventBehaviour&) noexcept -> IEventBehaviour& = default ;
		auto operator=(IEventBehaviour&&) noexcept -> IEventBehaviour& = default;
		virtual ~IEventBehaviour() = default;

		virtual void start();
		virtual void update();
		virtual void end();
	};
} // namespace power_ronin // namespace power_ronin
