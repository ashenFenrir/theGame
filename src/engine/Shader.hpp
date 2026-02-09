#include <string>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
	const unsigned int ID;
	static void load_shader_code(const char* vshaderPath, const char* fshaderPath, std::string& vcode, std::string& fcode);

public:
	Shader(const char* vshaderPath, const char* fshaderPath);
	~Shader();

	void use();
	void setUniform(const char* var, bool value);
	void setUniform(const char* var, int value);
	void setUniform(const char* var, float value);
	void setUniform(const char* var, glm::vec2 value);
	void setUniform(const char* var, glm::vec3 value);
	void setUniform(const char* var, glm::vec4 value);
	void setUniform(const char* var, glm::mat4 value);
};