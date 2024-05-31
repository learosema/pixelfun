#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <string>
#include <vector>

#include "Core/Window.hpp"
#include "Core/GLTex.hpp"
#include "Core/PixelFunEngine.hpp"

namespace App
{

    enum class ExitStatus : std::uint8_t
    {
        SUCCESS = 0,
        FAILURE = 1
    };

    class Application
    {
    public:
        explicit Application(const std::string &title);
        ~Application();

        Application(const Application &) = delete;
        Application(Application &&) = delete;
        Application &operator=(Application other) = delete;
        Application &operator=(Application &&other) = delete;

        ExitStatus run();
        void stop();

        void on_event(const SDL_WindowEvent &event);
        void on_minimize();
        void on_shown();
        void on_close();

    private:
        ExitStatus m_exit_status{ExitStatus::SUCCESS};
        std::unique_ptr<Window> m_window{nullptr};
        std::unique_ptr<PixelFunEngine> m_engine{nullptr};

        bool m_running{true};
        bool m_minimized{false};
        bool m_show_some_panel{true};
        bool m_show_code{true};
        bool m_show_debug_panel{false};
        bool m_show_demo_panel{false};

        std::string m_filename{"new.js"};
        std::string m_code{"function pixelfun(x,y,t) { return [255, 0, 255]; }"};
    };

} // namespace App
