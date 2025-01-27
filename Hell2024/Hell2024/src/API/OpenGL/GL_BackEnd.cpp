#include "GL_BackEnd.hpp"

#include "Types/GL_VertexBuffer.hpp"
#include "Core/AssetManager.hpp"
#include "Utils/Util.hpp"

#include <iostream>
#include <string>
#include <thread>
#include <array>
#include <memory>
#include <cstdio>
#include <string>
#include <filesystem>

namespace OpenGLBackEnd 
{
    GLuint _vertexDataVAO = 0;
    GLuint _vertexDataVBO = 0;
    GLuint _vertexDataEBO = 0;

    GLuint _weightedVertexDataVAO = 0;
    GLuint _weightedVertexDataVBO = 0;
    GLuint _weightedVertexDataEBO = 0;

    GLuint g_skinnedVertexDataVAO = 0;
    GLuint g_skinnedVertexDataVBO = 0;
    GLuint g_allocatedSkinnedVertexBufferSize = 0;

    GLuint g_pointCloudVAO = 0;
    GLuint g_pointCloudVBO = 0;

    GLuint g_constructiveSolidGeometryVAO = 0;
    GLuint g_constructiveSolidGeometryVBO = 0;
    GLuint g_constructiveSolidGeometryEBO = 0;

    GLuint g_triangle2DVAO = 0;
    GLuint g_triangle2DVBO = 0;

    // Non-weighted Vertex Data
    // - Represents static geometry
    // - Each vertex has a fixed position in 3D space
    // - Used for rigid objects that don't deform

    GLuint GetVertexDataVAO()
    {
        return _vertexDataVAO;
    }

    GLuint GetVertexDataVBO()
    {
        return _vertexDataVBO;
    }

    GLuint GetVertexDataEBO()
    {
        return _vertexDataEBO;
    }

    // Weighted Vertex Data
    // - Used for deformable geometry, often in sketetal animation
    // - Each vertex is influenced by one or more "bones" or influence points
    // - Vertices can move and deform based on the movement of these influences
    // - Includes additional attributes like bone indices and weights for each vertex

    // In skeletal animation, weighted vertices allow for smooth deformation of a mesh as the underlying skeleton moves. 
    // The vertex shader calculates a weighted average of bone trasforms to determine the final position of each vertex, creating fluid animations

    GLuint GetWeightedVertexDataVAO()
    {
        return _weightedVertexDataVAO;
    }

    GLuint GetWeightedVertexDataVBO()
    {
        return _weightedVertexDataVBO;
    }

    GLuint GetWeightedVertexDataEBO()
    {
        return _weightedVertexDataEBO;
    }

    GLuint GetSkinnedVertexDataVAO()
    {
        return g_skinnedVertexDataVAO;
    }

    GLuint GetSkinnedVertexDataVBO()
    {
        return g_skinnedVertexDataVBO;
    }

    GLuint GetPointCloudVAO()
    {
        return g_pointCloudVAO;
    }

    GLuint GetPointCloudVBO()
    {
        return g_pointCloudVBO;
    }

    GLuint GetCSGVAO()
    {
        return g_constructiveSolidGeometryVAO;
    }

    GLuint GetCSGVBO()
    {
        return g_constructiveSolidGeometryVBO;
    }

    GLuint GetCSGEBO()
    {
        return g_constructiveSolidGeometryEBO;
    }
}

static GLenum glCheckError_(const char* file, int line) 
{
    GLenum errorCode;

    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")\n";
    }
    return errorCode;
}

#define glCheckError() glCheckError_(__FILE__, __LINE__)

static void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei /*length*/, const char* message, const void* /*userParam*/) 
{
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
    {
        //std::cout << "Non-significant error code: " << id << "\n";
        return; // ignore these non-significant error codes
    }

    // 131185 = This code is associated with a message from NVIDIA drivers.
    // It's generated when a call to glBufferData is successful, which is more of an informational message than an actual error1
    // The message typically includes details about buffer object allocation and memory usage.

    std::cout << "---------------\n";
    std::cout << "Debug message (" << id << "): " << message << "\n";

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    }
    std::cout << "\n";

    switch (type) 
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    }
    std::cout << "\n";

    switch (severity) 
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
        }    std::cout << "\n\n\n";
}

static void QuerySizes() 
{
    GLint max_layers;

    glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &max_layers);

    std::cout << "Max texture array size is: " << max_layers << "\n";

    int max_compute_work_group_count[3];
    int max_compute_work_group_size[3];
    int max_compute_work_group_invocations;

    for (int idx = 0; idx < 3; idx++)
    {
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, idx, &max_compute_work_group_count[idx]);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, idx, &max_compute_work_group_size[idx]);
    }

    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &max_compute_work_group_invocations);

    std::cout << "Max number of work groups in X dimension " << max_compute_work_group_count[0] << "\n";
    std::cout << "Max number of work groups in Y dimension " << max_compute_work_group_count[1] << "\n";
    std::cout << "Max number of work groups in Z dimension " << max_compute_work_group_count[2] << "\n";
    std::cout << "Max size of a work group in X dimension " << max_compute_work_group_size[0] << "\n";
    std::cout << "Max size of a work group in Y dimension " << max_compute_work_group_size[1] << "\n";
    std::cout << "Max size of a work group in Z dimension " << max_compute_work_group_size[2] << "\n";
    std::cout << "Number of invocations in a single local work group that may be dispatched to a compute shader " << max_compute_work_group_invocations << "\n";
}

void OpenGLBackEnd::InitMinimum()
{
    // GLAD Initialization
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << "\n"; // Let us know if GLAD initialization fails
        return;
    }

    // GPU Information
    GLint major, minor;

    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);

    std::cout << "\n--- GPU Information ---\n";
    std::cout << "Vendor: " << vendor << "\n";
    std::cout << "Renderer: " << renderer << "\n";
    std::cout << "OpenGL Version: " << major << "." << minor << "\n";

    // CPU Information
    std::cout << "\n--- CPU Information ---\n";

    // Windows CPU info retrieval
    int cpuInfo[4];
    __cpuid(cpuInfo, 0x80000002);
    __cpuid(cpuInfo, 0x80000003);
    __cpuid(cpuInfo, 0x80000004);

    char cpuBrandString[0x40];
    memcpy(cpuBrandString, cpuInfo, sizeof(cpuInfo));
    //std::cout << "CPU: " << cpuBrandString << "\n";

    // Number of CPU Cores
    std::cout << "CPU Cores: " << std::thread::hardware_concurrency() << "\n";

    // Debug Context Check
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    std::cout << "\n--- Debug Information ---\n";
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(glDebugOutput, nullptr);
        std::cout << "Debug GL: Enabled" << "\n";
    }
    else
    {
        std::cout << "Debug GL: Disabled" << "\n";
    }

    //QuerySizes();

    // Clear screen to black
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLBackEnd::AllocateSkinnedVertexBufferSpace(int vertexCount)
{
    // Generate a new Vertex Array Object if `g_skinnedVertexDataVAO` does NOT exist
    if (g_skinnedVertexDataVAO == 0)
    {
        glGenVertexArrays(1, &g_skinnedVertexDataVAO);
    }

    // Check if there is enough space
    if (g_allocatedSkinnedVertexBufferSize < vertexCount * sizeof(Vertex)) 
    {
        // Destroy old VBO
        if (g_skinnedVertexDataVBO != 0)
        {
            glDeleteBuffers(1, &g_skinnedVertexDataVBO);
        }

        // Create new one
        glBindVertexArray(g_skinnedVertexDataVAO);
        glGenBuffers(1, &g_skinnedVertexDataVBO);

        // Bind the new Vertex Array Object and the new VBO
        glBindBuffer(GL_ARRAY_BUFFER, g_skinnedVertexDataVBO);
        // Allocates buffer data with `glBufferData`, setting the size to `vertexCount * sizeof(Vertex)`
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), nullptr, GL_STATIC_DRAW);

        // Set up the vertex attributes
        // Attribute 0: Position (3 Floats)
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        // Attribute 1: Normal (3 Floats)
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        // Attribute 2: UV (2 Floats)
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

        // Attribute 2: Tangent (3 Floats)
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

        // Unbind the array buffer
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Update `g_allocatedSkinnedVertexBufferSize` with the new buffer size
        g_allocatedSkinnedVertexBufferSize = vertexCount * sizeof(Vertex);
    }
}

void OpenGLBackEnd::UploadVertexData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
    // If the Vertex Array Object does exist, delete the buffers from the VBO and EBO, and vertex arrays from the VBO
    if (_vertexDataVAO != 0)
    {
        glDeleteVertexArrays(1, &_vertexDataVAO);
        glDeleteBuffers(1, &_vertexDataVBO);
        glDeleteBuffers(1, &_vertexDataEBO);
    }

    // Generate vertex arrays for `_vertexDataVAO`
    glGenVertexArrays(1, &_vertexDataVAO);
    // Generate buffers for `_vertexDataVBO` and `_vertexDataEBO`
    glGenBuffers(1, &_vertexDataVBO);
    glGenBuffers(1, &_vertexDataEBO);

    // Bind the vertex array to the Vertex Array Object
    glBindVertexArray(_vertexDataVAO);
    // Bind the buffer to the VBO
    glBindBuffer(GL_ARRAY_BUFFER, _vertexDataVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertexDataEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

    // Set up the vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

    // Cleanup
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //std::cout << "[LOADED] Vertex Data" << "\n";
}

void OpenGLBackEnd::UploadConstructiveSolidGeometry(std::vector<CSGVertex>& vertices, std::vector<uint32_t>& indices)
{
    if (vertices.empty()) // Assert?? or nah?
    {
        return;
    }

    if (g_constructiveSolidGeometryVAO != 0) 
    {
        glDeleteVertexArrays(1, &g_constructiveSolidGeometryVAO);
        glDeleteBuffers(1, &g_constructiveSolidGeometryVBO);
        glDeleteBuffers(1, &g_constructiveSolidGeometryEBO);
    }

    glGenVertexArrays(1, &g_constructiveSolidGeometryVAO);
    glGenBuffers(1, &g_constructiveSolidGeometryVBO);
    glGenBuffers(1, &g_constructiveSolidGeometryEBO);

    glBindVertexArray(g_constructiveSolidGeometryVAO);
    glBindBuffer(GL_ARRAY_BUFFER, g_constructiveSolidGeometryVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(CSGVertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_constructiveSolidGeometryEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CSGVertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CSGVertex), (void*)offsetof(CSGVertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(CSGVertex), (void*)offsetof(CSGVertex, uv));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(CSGVertex), (void*)offsetof(CSGVertex, tangent));
    glEnableVertexAttribArray(4);
    glVertexAttribIPointer(4, 1, GL_INT, sizeof(CSGVertex), (void*)offsetof(CSGVertex, materialIndex));

    glBindVertexArray(0);
    /*
    std::cout << "Uploaded constructive geometry to gpu\n";
    std::cout << "-vertices: " << vertices.size() << "\n";
    std::cout << "-indices: " << indices.size() << "\n";
    std::cout << "-vao: " << g_constructiveSolidGeometryVAO << "\n";
    std::cout << "-vbo: " << g_constructiveSolidGeometryVBO << "\n";
    std::cout << "-ebo: " << g_constructiveSolidGeometryEBO << "\n";*/
}

void OpenGLBackEnd::UploadWeightedVertexData(std::vector<WeightedVertex>& vertices, std::vector<uint32_t>& indices)
{
    std::cout << "UPLOADED UploadWeightedVertexData" << "\n";
    assert(!indices.empty());
    assert(!vertices.empty());
    //assert(_weightedVertexDataVAO != 0);

    if (_weightedVertexDataVAO != 0) // Assert?
    {
        glDeleteVertexArrays(1, &_weightedVertexDataVAO);
        glDeleteBuffers(1, &_weightedVertexDataVBO);
        glDeleteBuffers(1, &_weightedVertexDataEBO);
    }

    glGenVertexArrays(1, &_weightedVertexDataVAO);
    glGenBuffers(1, &_weightedVertexDataVBO);
    glGenBuffers(1, &_weightedVertexDataEBO);

    glBindVertexArray(_weightedVertexDataVAO);
    glBindBuffer(GL_ARRAY_BUFFER, _weightedVertexDataVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(WeightedVertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _weightedVertexDataEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(WeightedVertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(WeightedVertex), (void*)offsetof(WeightedVertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(WeightedVertex), (void*)offsetof(WeightedVertex, uv));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(WeightedVertex), (void*)offsetof(WeightedVertex, tangent));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_INT, sizeof(WeightedVertex), (void*)offsetof(WeightedVertex, boneID));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(WeightedVertex), (void*)offsetof(WeightedVertex, weight));

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void OpenGLBackEnd::CreatePointCloudVertexBuffer(std::vector<CloudPoint>& pointCloud)
{
    static int allocatedBufferSize = 0;

    if (g_pointCloudVAO == 0) // If the Vertex Array Object (VAO) does NOT exist, create a new VAO and VBO
    {
        glGenVertexArrays(1, &g_pointCloudVAO);
        glGenBuffers(1, &g_pointCloudVBO);
    }

    //assert(pointCloud.empty());
    if (pointCloud.empty())
    {
        return;
    }

    // Bind the Vertex Array Object (VAO) for the point cloud
    glBindVertexArray(g_pointCloudVAO);

    // Check if the current point cloud data fits within the previously allocated buffer
    if (pointCloud.size() * sizeof(CloudPoint) <= allocatedBufferSize)
    {
        // If it fits in the buffer, update the existing `glBufferSubData` 
        glBindBuffer(GL_ARRAY_BUFFER, g_pointCloudVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, (GLuint)pointCloud.size() * sizeof(CloudPoint), &pointCloud[0]);
    }
    else
    {
        // If it does NOT fit in the buffer, it deletes the old buffer, creates a new one, and uploads the data using `glBufferData`
        glDeleteBuffers(1, &g_pointCloudVBO);
        glGenBuffers(1, &g_pointCloudVBO);
        glBindBuffer(GL_ARRAY_BUFFER, g_pointCloudVBO);
        glBufferData(GL_ARRAY_BUFFER, pointCloud.size() * sizeof(CloudPoint), &pointCloud[0], GL_STATIC_DRAW);
    }

    // Set up three vertex attributes
    // Attribute 0: Position (3 Floats)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CloudPoint), (void*)0);

    // Attribute 1: Normal (3 Floats)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CloudPoint), (void*)offsetof(CloudPoint, normal));

    // Attribute 2: Direct Lighting (3 Floats)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(CloudPoint), (void*)offsetof(CloudPoint, directLighting));

    // Clean up
    // Unbinds the Vertex Array Object and VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Update the `allocatedBufferSize` to reflect the current buffer size
    allocatedBufferSize = pointCloud.size() * sizeof(CloudPoint);
}

void OpenGLBackEnd::UploadTriangle2DData(std::vector<glm::vec2>& vertices) // Not used currently
{
    static int allocatedBufferSize = 0;

    if (g_triangle2DVAO == 0)
    {
        glGenVertexArrays(1, &g_triangle2DVAO);
        glGenBuffers(1, &g_triangle2DVBO);
    }

    if (vertices.empty())
    {
        return;
    }

    glBindVertexArray(g_triangle2DVAO);

    if (vertices.size() * sizeof(glm::vec2) <= allocatedBufferSize)
    {
        glBindBuffer(GL_ARRAY_BUFFER, g_triangle2DVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, (GLuint)vertices.size() * sizeof(glm::vec2), &vertices[0]);
    }
    else
    {
        glDeleteBuffers(1, &g_triangle2DVBO);
        glGenBuffers(1, &g_triangle2DVBO);
        glBindBuffer(GL_ARRAY_BUFFER, g_triangle2DVBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
    }

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    allocatedBufferSize = vertices.size() * sizeof(glm::vec2);
}

GLuint OpenGLBackEnd::GetTriangles2DVAO()
{
    return g_triangle2DVAO;
}

GLuint OpenGLBackEnd::GetTriangles2DVBO() // Not used currently
{
    return g_triangle2DVBO;
}