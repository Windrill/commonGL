#pragma  once
#include <csignal>
// start debugger subject to the compiler...
// in msvc the breakpoint command is __debugbreak, in gcc i'll have to see if this works
#define ASSERT(x) if (!(x)) std::raise(SIGINT);
#define GLCall(x) GLCheckError(__FILE__, __LINE__);\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#define CLOG(x) \
std::cout << __FILE__ << " L:" <<  __LINE__ << " " << x << "\n"

void GLClearError();
void GLCheckError(const char* file, int line);
bool GLLogCall(const char* function, const char* file, int line);
