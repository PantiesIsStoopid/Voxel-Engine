#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <chrono>

float vertices[] = {
    // Positions         // Colors
    // Front face (Brown)
    -0.5f, -0.5f, 0.5f, 0.6f, 0.3f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.6f, 0.3f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.6f, 0.3f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.6f, 0.3f, 0.0f,

    // Back face (Brown)
    -0.5f, -0.5f, -0.5f, 0.6f, 0.3f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.6f, 0.3f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.6f, 0.3f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.6f, 0.3f, 0.0f,

    // Left face (Brown)
    -0.5f, -0.5f, -0.5f, 0.6f, 0.3f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.6f, 0.3f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.6f, 0.3f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.6f, 0.3f, 0.0f,

    // Right face (Brown)
    0.5f, -0.5f, -0.5f, 0.6f, 0.3f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.6f, 0.3f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.6f, 0.3f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.6f, 0.3f, 0.0f,

    // Top face (Green)
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,

    // Bottom face (Brown)
    -0.5f, -0.5f, -0.5f, 0.6f, 0.3f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.6f, 0.3f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.6f, 0.3f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.6f, 0.3f, 0.0f};

unsigned int indices[] = {
    0, 1, 2, 2, 3, 0,       // Front face
    4, 5, 6, 6, 7, 4,       // Back face
    8, 9, 10, 10, 11, 8,    // Left face
    12, 13, 14, 14, 15, 12, // Right face
    16, 17, 18, 18, 19, 16, // Top face
    20, 21, 22, 22, 23, 20  // Bottom face
};

const char *vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
out vec3 ourColor;
uniform mat4 model;
void main() {
    gl_Position = model * vec4(aPos, 1.0);
    ourColor = aColor;
})";

const char *fragmentShaderSource = R"(
#version 330 core
in vec3 ourColor;
out vec4 FragColor;
void main() {
    FragColor = vec4(ourColor, 1.0);
})";

// Handles input
void processInput(GLFWwindow *window, float &rotationX, float &rotationY)
{
  const float rotationSpeed = 1.0f;

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    std::cout << "A Pressed! Rotating left.\n";
    rotationY -= rotationSpeed;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    std::cout << "D Pressed! Rotating right.\n";
    rotationY += rotationSpeed;
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    std::cout << "W Pressed! Rotating down.\n";
    rotationX -= rotationSpeed;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    std::cout << "S Pressed! Rotating up.\n";
    rotationX += rotationSpeed;
  }
}

int main()
{
  if (!glfwInit())
  {
    std::cerr << "GLFW Initialization Failed!\n";
    return -1;
  }

  GLFWwindow *window = glfwCreateWindow(800, 600, "Rotating Cube", NULL, NULL);
  if (!window)
  {
    std::cerr << "Window Creation Failed!\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cerr << "GLAD Initialization Failed!\n";
    return -1;
  }

  glEnable(GL_DEPTH_TEST);

  GLuint VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  float rotationX = 0.0f, rotationY = 0.0f;

  using Clock = std::chrono::high_resolution_clock;
  auto lastTime = Clock::now();
  const double frameTime = 1.0 / 90.0;

  while (!glfwWindowShouldClose(window))
  {
    auto currentTime = Clock::now();
    std::chrono::duration<double> elapsed = currentTime - lastTime;
    if (elapsed.count() < frameTime)
      continue;
    lastTime = currentTime;

    processInput(window, rotationX, rotationY);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));

    glUseProgram(shaderProgram);
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}
