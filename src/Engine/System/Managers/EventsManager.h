#pragma once

#include "src/Engine/System/Managers/Manager.h"
#include "src/Engine/Includes/STLIncludes.h"
#include "src/Engine/Includes/SDLIncludes.h"
#include "src/Engine/System/Other/Delegate/Delegate.h"
#include "src/Engine/System/Other/Multithreading/Thread.h"

namespace Carrot
{

PTR(EventsManager);

using EventType = uint32_t;

class EventsManager 
    : public Manager
    , public Thread
{
public:
    virtual void Initialize() override;

    virtual void Main_Loop() override;

    virtual void Update(float dt);

    EventDelegate<EventType, SDL_CommonEvent> OnCommonEvent;
    EventDelegate<EventType, SDL_DisplayEvent> OnDisplayEvent;
    EventDelegate<EventType, SDL_WindowEvent> OnWindowEvent;

    EventDelegate<EventType, SDL_KeyboardEvent> OnKeyboardEvent;

    EventDelegate<EventType, SDL_TextEditingEvent> OnEditEvent;
    EventDelegate<EventType, SDL_TextInputEvent> OnTextEvent;

    EventDelegate<EventType, SDL_MouseMotionEvent> OnMouseMotionEvent;
    EventDelegate<EventType, SDL_MouseButtonEvent> OnMouseButtonEvent;
    EventDelegate<EventType, SDL_MouseWheelEvent> OnMouseWheelEvent;

    EventDelegate<EventType, SDL_JoyAxisEvent> OnJoystickAxisEvent;
    EventDelegate<EventType, SDL_JoyBallEvent> OnJoystickBallEvent;
    EventDelegate<EventType, SDL_JoyHatEvent> OnJoystickHatEvent;
    EventDelegate<EventType, SDL_JoyButtonEvent> OnJoystickButtonEvent;
    EventDelegate<EventType, SDL_JoyDeviceEvent> OnJoystickDeviceEvent;

    EventDelegate<EventType, SDL_ControllerAxisEvent> OnControllerAxisEvent;
    EventDelegate<EventType, SDL_ControllerButtonEvent> OnControllerButtonEvent;
    EventDelegate<EventType, SDL_ControllerDeviceEvent> OnControllerDeviceEvent;

    EventDelegate<EventType, SDL_AudioDeviceEvent> OnAudioDeviceEvent;

    EventDelegate<EventType, SDL_SensorEvent> OnSensorEvent;

    EventDelegate<EventType, SDL_QuitEvent> OnQuitEvent;
    EventDelegate<EventType, SDL_UserEvent> OnUserEvent;
    EventDelegate<EventType, SDL_SysWMEvent> OnSysWMEvent;

    EventDelegate<EventType, SDL_TouchFingerEvent> OnTouchFingerEvent;
    EventDelegate<EventType, SDL_MultiGestureEvent> OnMultiGestureEvent;
    EventDelegate<EventType, SDL_DollarGestureEvent> OnDollarGestureEvent;
    EventDelegate<EventType, SDL_DropEvent> OnDropEvent;

private:

    std::list<std::pair<EventType, SDL_CommonEvent>> m_Common;         /**< Common event data */
    std::list<std::pair<EventType, SDL_DisplayEvent>> m_Display;       /**< Window event data */
    std::list<std::pair<EventType, SDL_WindowEvent>> m_Window;         /**< Window event data */
    std::list<std::pair<EventType, SDL_KeyboardEvent>> m_Keyboard;          /**< Keyboard event data */
    std::list<std::pair<EventType, SDL_TextEditingEvent>> m_Edit;      /**< Text editing event data */
    std::list<std::pair<EventType, SDL_TextInputEvent>> m_Text;        /**< Text input event data */
    std::list<std::pair<EventType, SDL_MouseMotionEvent>> m_MouseMotion;    /**< Mouse motion event data */
    std::list<std::pair<EventType, SDL_MouseButtonEvent>> m_MouseButton;    /**< Mouse button event data */
    std::list<std::pair<EventType, SDL_MouseWheelEvent>> m_MouseWheel;      /**< Mouse wheel event data */
    std::list<std::pair<EventType, SDL_JoyAxisEvent>> m_JoystickAxis;         /**< Joystick axis event data */
    std::list<std::pair<EventType, SDL_JoyBallEvent>> m_JoystickBall;         /**< Joystick ball event data */
    std::list<std::pair<EventType, SDL_JoyHatEvent>> m_JoystickHat;           /**< Joystick hat event data */
    std::list<std::pair<EventType, SDL_JoyButtonEvent>> m_JoystickButton;     /**< Joystick button event data */
    std::list<std::pair<EventType, SDL_JoyDeviceEvent>> m_JoystickDevice;     /**< Joystick device change event data */
    std::list<std::pair<EventType, SDL_ControllerAxisEvent>> m_ControllerAxis;      /**< Game Controller axis event data */
    std::list<std::pair<EventType, SDL_ControllerButtonEvent>> m_ControllerButton;  /**< Game Controller button event data */
    std::list<std::pair<EventType, SDL_ControllerDeviceEvent>> m_ControllerDevice;  /**< Game Controller device event data */
    std::list<std::pair<EventType, SDL_AudioDeviceEvent>> m_AudioDevice;   /**< Audio device event data */
    std::list<std::pair<EventType, SDL_SensorEvent>> m_Sensor;         /**< Sensor event data */
    std::list<std::pair<EventType, SDL_QuitEvent>> m_Quit;             /**< Quit request event data */
    std::list<std::pair<EventType, SDL_UserEvent>> m_User;             /**< Custom event data */
    std::list<std::pair<EventType, SDL_SysWMEvent>> m_SysWM;           /**< System dependent window event data */
    std::list<std::pair<EventType, SDL_TouchFingerEvent>> m_TouchFinger;   /**< Touch finger event data */
    std::list<std::pair<EventType, SDL_MultiGestureEvent>> m_MultiGesture; /**< Gesture event data */
    std::list<std::pair<EventType, SDL_DollarGestureEvent>> m_DollarGesture; /**< Gesture event data */
    std::list<std::pair<EventType, SDL_DropEvent>> m_Drop;             /**< Drag and drop event data */

    template<class TDelegate, class TEventsList>
    void ProcessBroadcastEvents(TDelegate& _Delegate, TEventsList& _List);
};

template<class TDelegate, class TEventsList>
void EventsManager::ProcessBroadcastEvents(TDelegate& _Delegate, TEventsList& _List)
{
    if (!_List.empty())
    {
        auto& EventPair = _List.front();
        _Delegate.Broadcast(EventPair.first, EventPair.second);
        _List.pop_front();
    }
}

} 
