#include <string>

class Shader
{
	static void load_shader_code(const char* vshaderPath, const char* fshaderPath, std::string& vcode, std::string& fcode);

public:
	unsigned int id;

	Shader(const char* vshaderPath, const char* fshaderPath);
	~Shader();
};