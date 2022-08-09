#pragma once
#include <functional>
#include <array>
namespace GoodEngine
{
	enum class EventType
	{
		WindowResize = 0,
		WindowClose,

		KeyPressed,
		KeyReleased,

		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		EventsCount
	};

	struct BaseEvent
	{
		virtual ~BaseEvent() = default;
		virtual EventType get_type() const = 0;
	};

	class EventDispatcher
	{
	public:
		template <typename EventType>
		void add_event_listener(std::function<void(EventType&)> callback)
		{
			auto baseCallback = [func = std::move(callback)](BaseEvent& e)
			{
				if (e.get_type() == EventType::type)
				{
					func(static_cast<EventType&>(e));
				}
			};
			m_eventCallBacks[static_cast<size_t>(EventType::type)] = std::move(baseCallback);
		}

		void dispatch(BaseEvent& event) 
		{
			auto& callback = m_eventCallBacks[static_cast<size_t>(event.get_type())];
			if (callback)
			{
				callback(event);
			}
		};
	private:
		std::array<std::function<void(BaseEvent&)>, static_cast<size_t>(EventType::EventsCount)> m_eventCallBacks;
	};

	struct EventMouseMoved :public BaseEvent
	{
		EventMouseMoved(const double new_x, const double new_y) :x(new_x), y(new_y){};
		virtual EventType get_type() const override
		{
			return type;
		}
		double x, y;

		static const EventType type = EventType::MouseMoved;
	};

	struct EventWindowResize :public BaseEvent
	{
		EventWindowResize(const unsigned int new_x, const unsigned int new_y) :x(new_x), y(new_y) {};
		virtual EventType get_type() const override
		{
			return type;
		}
		unsigned int x, y;

		static const EventType type = EventType::WindowResize;
	};
	struct EventWindowClosed :public BaseEvent
	{
		EventWindowClosed(){};
		virtual EventType get_type() const override
		{
			return type;
		}
	
		static const EventType type = EventType::WindowClose;
	};
	
	struct Event
	{
		unsigned int width;
		unsigned int height;
	};
}