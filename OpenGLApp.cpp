//
// Created by User on 23/03/2023.
//

#include "OpenGLApp.h"

// The constructor (default)
OpenGLApp::OpenGLApp() {

}

bool OpenGLApp::OnInit() {

    // Initialise GLFW
    glewExperimental = true; // Needed for core profile
    if( !glfwInit() ) {

        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    // Create the OpenGL Window
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( wWidth, wHeight, "Advanced Voxel Engine", NULL, NULL);
    if( window == NULL ){

        fprintf( stderr, "Failed to open GLFW window. Invalid support for OpenGL 4.\n" );
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {

        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Disables VSync
    glfwSwapInterval(0);

    // Output the current version of opengl
    std::cout << glGetString(GL_VERSION) << std::endl;

    // Create the Vertex Array Object (VAO)
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Set Z-Buffer on
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); // Accept fragment if it is closer to the camera than the former one

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Create a program handler
    shaderProgramHandler = new TestingShaderProgramHandler();

    // Create a new Scene Manager
    sceneManager = new SceneManager(&deltaTime);

    // Add a new scene to the scene manager
    Scene* scene = new VoxelWorldScene("Voxel World Scene", window, *shaderProgramHandler->GetProgramMap());
    sceneManager->AddScene(scene);

    // Set the current scene
    sceneManager->SetCurrentScene(scene);

    return true;
}

int OpenGLApp::OnExecute(int width, int height) {

    wWidth = width;
    wHeight = height;

    // Initialize the app
    if(OnInit()){

        while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 ){

            OnLoop();
            OnRender();
        }
    }

    return 0;
}

void OpenGLApp::OnLoop() {

    // Time Management
    double currentTime = glfwGetTime();
    deltaTime = DeltaTime(time_);
    time_ = currentTime;
    std::string fpsStr = std::to_string((int)(1.0/deltaTime)) + "fps";
    glfwSetWindowTitle(window, ("VoxelEngine " + fpsStr).c_str());

    // Call OnLoop inside scene
    sceneManager->UpdateCurrentScene(&deltaTime);

}

void OpenGLApp::OnRender() {

    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render the current scene
    sceneManager->RenderScene(sceneManager->GetCurrentScene());

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void OpenGLApp::OnExit() {

    // Exit the App Here
}