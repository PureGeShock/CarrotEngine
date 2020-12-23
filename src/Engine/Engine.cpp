#include "Engine.h"
#include "System/LogSystem/Log.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Carrot
{

Engine* Engine::m_instance = new Engine();


/* TEST, REMOVE IT */
#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600
static GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

    // Создаем шейдеры
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Загружаем код Вершинного Шейдера из файла
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }
    else
    {
        std::cout << "vs shader is not opened" << "\n";
    }

    // Загружаем код Фрагментного шейдера из файла
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }
    else
    {
        std::cout << "fs shader is not opened" << "\n";
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Компилируем Вершинный шейдер
    printf("Компиляция шейдера: %sn", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Выполняем проверку Вершинного шейдера
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
      std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
      glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
      fprintf(stdout, "%sn", &VertexShaderErrorMessage[0]);
    }

    // Компилируем Фрагментный шейдер
    printf("Компиляция шейдера: %sn", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Проверяем Фрагментный шейдер
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
      std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
      glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
      fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Создаем шейдерную программу и привязываем шейдеры к ней
    fprintf(stdout, "Создаем шейдерную программу и привязываем шейдеры к нейn");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Проверяем шейдерную программу
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
      std::vector<char> ProgramErrorMessage(InfoLogLength+1);
      glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
      fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
    }

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

/* TEST, REMOVE IT */
static GLuint programID;
static SDL_Window* window;
static SDL_GLContext glContext;
// Это будет идентификатором нашего буфера вершин
static GLuint vertexbuffer;


void SomeTest::Update(float dt)
{
    static float Time = 0.0f;
    static bool IsTimeGone = false;

    if (Time > 0.03f && !IsTimeGone)
    {
        int x = 0;
    }

    Time += dt;
}

void Engine::Initialize()
{
    if (!EnsureMsg(!m_IsInitialized, "Attempt to initialize Engine again."))
    {
        return;
    }

    // RenderSystem Initialization
    // TODO: Create rendersystem for different OS


    /* TEST, REMOVE IT */
    //COMPILER_VERIFY(true);
    // ----- Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL could not initialize\n");
        return;
    }

    // ----- Create window
    window = SDL_CreateWindow("CarrotEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIZE_X, SCREEN_SIZE_Y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window)
    {
        fprintf(stderr, "Error creating window.\n");
        return; 
    }

    // ----- SDL OpenGL settings
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // ----- SDL OpenGL context
    glContext = SDL_GL_CreateContext(window);

    // ----- SDL v-sync
    SDL_GL_SetSwapInterval(1);

    // ----- GLEW
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Массив 3 векторов, которые являются вершинами треугольника
    static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
    };


    // Создадим 1 буфер и поместим в переменную vertexbuffer его идентификатор
    glGenBuffers(1, &vertexbuffer);

    // Сделаем только что созданный буфер текущим
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    // Передадим информацию о вершинах в OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Создать и откомпилировать нашу шейдерную программу
    programID = LoadShaders( "Data/TestShader.vs", "Data/TestShader.fs" );

    //glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    InitializeManagers();

    m_IsInitialized = m_IsRunning = true;

    m_TestObject = std::make_shared<SomeTest>();
    m_TestObject->SetUpdateActive(true);
}

void Engine::Loop()
{
    while (m_IsRunning)
    {
        const clock_t begin_time = clock();
        static float dt = 0.0f;

        for (auto&& Manager : m_Managers)
        {
            Manager->Update(dt);
        }

        dt = float(clock() - begin_time) / CLOCKS_PER_SEC;

        /* FPS count */
        m_CurrentFPS = 1.0f / dt;






        static float Time = 0.0f;
        static bool IsTimeGone = false;

        if (Time > 0.03f && !IsTimeGone)
        {
            CLog(LogType::Info, "TestObject deleted");
            m_TestObject.reset();
            IsTimeGone = true;
        }

        Time += dt;




        /* TEST, REMOVE IT */

        const auto before = std::chrono::system_clock::now();

        const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - before);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Устанавливаем наш шейдер текущим
        glUseProgram(programID);

        // Указываем, что первым буфером атрибутов будут вершины
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
        0,                  // Атрибут 0. Подробнее об этом будет рассказано в части, посвященной шейдерам.
        3,                  // Размер
        GL_FLOAT,           // Тип
        GL_FALSE,           // Указывает, что значения не нормализованы
        0,                  // Шаг
        (void*)0            // Смещение массива в буфере
        );

        // Вывести треугольник!
        glDrawArrays(GL_TRIANGLES, 0, 3); // Начиная с вершины 0, всего 3 вершины -> один треугольник

        glDisableVertexAttribArray(0);
        /*
            do drawing here
        */

        SDL_GL_SwapWindow(window);
    }
}

void Engine::InitializeManagers()
{
    EventsManager* EventMgr = InitializeManager<EventsManager>();
    EventMgr->OnQuitEvent.AddListener(this, &Engine::OnDestroy);

    // Other Managers

    InitializeManager<UpdateManager>();
}

void Engine::OnDestroy(EventType Type, SDL_QuitEvent Event)
{
    m_IsRunning = false;
    
    SDL_GL_DeleteContext(glContext);
}

}