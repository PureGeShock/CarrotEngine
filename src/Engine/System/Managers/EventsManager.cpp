#include "EventsManager.h"

namespace Carrot
{

void EventsManager::Initialize()
{
    Run(ThreadRunMode::Detach, ThreadCallMode::LoopCall);
}

void EventsManager::Main_Loop()
{
    SDL_Event windowEvent;
    while (SDL_PollEvent(&windowEvent))
    {
        switch (windowEvent.type)
        {
        case SDL_QUIT:
            m_Quit.push_back(std::make_pair(windowEvent.type, windowEvent.quit));
            break;
        case SDL_WINDOWEVENT:
            m_Window.push_back(std::make_pair(windowEvent.type, windowEvent.window));
            break;
        case SDL_DISPLAYEVENT:
            m_Display.push_back(std::make_pair(windowEvent.type, windowEvent.display));
            break;
        case SDL_SYSWMEVENT:
            m_SysWM.push_back(std::make_pair(windowEvent.type, windowEvent.syswm));
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            m_Keyboard.push_back(std::make_pair(windowEvent.type, windowEvent.key));
            break;
        case SDL_MOUSEMOTION:
            m_MouseMotion.push_back(std::make_pair(windowEvent.type, windowEvent.motion));
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            m_MouseButton.push_back(std::make_pair(windowEvent.type, windowEvent.button));
            break;
        case SDL_MOUSEWHEEL:
            m_MouseWheel.push_back(std::make_pair(windowEvent.type, windowEvent.wheel));
            break;
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void EventsManager::Update(float dt)
{
    ProcessBroadcastEvents(OnCommonEvent, m_Common);
    ProcessBroadcastEvents(OnDisplayEvent, m_Display);
    ProcessBroadcastEvents(OnWindowEvent, m_Window);
    ProcessBroadcastEvents(OnKeyboardEvent, m_Keyboard);
    ProcessBroadcastEvents(OnEditEvent, m_Edit);
    ProcessBroadcastEvents(OnTextEvent, m_Text);
    ProcessBroadcastEvents(OnMouseMotionEvent, m_MouseMotion);
    ProcessBroadcastEvents(OnMouseButtonEvent, m_MouseButton);
    ProcessBroadcastEvents(OnMouseWheelEvent, m_MouseWheel);
    ProcessBroadcastEvents(OnJoystickAxisEvent, m_JoystickAxis);
    ProcessBroadcastEvents(OnJoystickBallEvent, m_JoystickBall);
    ProcessBroadcastEvents(OnJoystickHatEvent, m_JoystickHat);
    ProcessBroadcastEvents(OnJoystickButtonEvent, m_JoystickButton);
    ProcessBroadcastEvents(OnJoystickDeviceEvent, m_JoystickDevice);
    ProcessBroadcastEvents(OnControllerAxisEvent, m_ControllerAxis);
    ProcessBroadcastEvents(OnControllerButtonEvent, m_ControllerButton);
    ProcessBroadcastEvents(OnControllerDeviceEvent, m_ControllerDevice);
    ProcessBroadcastEvents(OnAudioDeviceEvent, m_AudioDevice);
    ProcessBroadcastEvents(OnSensorEvent, m_Sensor);
    ProcessBroadcastEvents(OnQuitEvent, m_Quit);
    ProcessBroadcastEvents(OnUserEvent, m_User);
    ProcessBroadcastEvents(OnSysWMEvent, m_SysWM);
    ProcessBroadcastEvents(OnTouchFingerEvent, m_TouchFinger);
    ProcessBroadcastEvents(OnMultiGestureEvent, m_MultiGesture);
    ProcessBroadcastEvents(OnDollarGestureEvent, m_DollarGesture);
    ProcessBroadcastEvents(OnDropEvent, m_Drop);
}

}