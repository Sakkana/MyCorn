#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_m.h"
#include "camera.h"
#include "model.h"
// #include "transform_to_image.h"

#include <iostream>

#define CORNLOG(x) std::cout << x << std::endl;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// 鼠标拖拽事件
void mouse_drag_callback(GLFWwindow* window, int button, int action, int modes);
double click_pos_X, click_pos_Y;
double release_pos_X, release_pos_Y;

// 界面尺寸
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 定义相机
Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main(int argc, char * argv[])
{
    // 初始化 glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // 注册 glfw 图形界面
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 设置当前上下文
    glfwMakeContextCurrent(window);
    
    // 注册回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_drag_callback);

    // 注册捕捉鼠标事件
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR);

    // 通过 glad 注册函数指针
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model). 反转 y 轴
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // 构建、编译着色器
    Shader ourShader("1.model_loading.vs", "1.model_loading.fs");

    // 定义，加载模型
    Model ourModel("MODELS/clippedModel1/clipped1.obj");

    // 线框图模式
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 二维映射
    // TransformToImage two_d_image(ourModel.meshes);

    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        // 优化帧率
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // 监听设备输入
        processInput(window);

        // 渲染背景
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 开启着色器
        ourShader.use();

        // 定义投影矩阵、视图矩阵
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        // 定义模型矩阵
        glm::mat4 model = glm::mat4(1.0f);
        // 平移
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        // 缩放
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        // 旋转
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        // 转换矩阵传入着色器
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        ourShader.setMat4("model", model);

        // 渲染
        ourModel.Draw(ourShader);

        // 交换帧缓冲
        glfwSwapBuffers(window);

        // 事件轮询
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// 键盘输入事件
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}


// 帧缓冲
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// 鼠标滚轮回调函数
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


// 鼠标移动回调函数
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

 
    camera.ProcessMouseMovement(xoffset, yoffset);
}

void mouse_drag_callback(GLFWwindow* window, int button, int action, int modes)
{
    if (action == GLFW_PRESS) 
    {
        // 获取鼠标位置
        glfwGetCursorPos(window, &click_pos_X, &click_pos_Y);
        lastX = static_cast<float>(click_pos_X);
        lastY = static_cast<float>(click_pos_Y);
#if 0
        CORNLOG("PRESS");
        CORNLOG(click_pos_X);
        CORNLOG(click_pos_Y);
        CORNLOG("==========");
#endif
    }
    else if (action == GLFW_RELEASE) 
    {
        // 获取鼠标位置
        glfwGetCursorPos(window, &release_pos_X, &release_pos_Y);
        mouse_callback(window, static_cast<float>(release_pos_X), static_cast<float>(release_pos_Y));
#if 0
        CORNLOG("RELEASE");
        CORNLOG(release_pos_X);
        CORNLOG(release_pos_Y);
        CORNLOG("==========");
#endif
    }
}