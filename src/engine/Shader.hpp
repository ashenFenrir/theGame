#include <exception>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glad/glad.h>



class Shader
{
    static void load_shader(std::string vertex_shader_file, std::string fragment_shader_file, std::string& vcode, std::string& fcode)
    {


        // Reading Files
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        
        vShaderFile.exceptions(std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::badbit);
        try {
            vShaderFile.open(vertex_shader_file);
            fShaderFile.open(fragment_shader_file);
            std::stringstream vShaderStream, fShaderStream;
        
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
        
            vShaderFile.close();
            fShaderFile.close();
        
            vcode = vShaderStream.str();
            fcode = fShaderStream.str();
        }
        catch(std::ifstream::failure& e) {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }


    }
public:
    unsigned int id;
    Shader(const char* vcode, const char* fcode)
    {
        //create vertex buffer object(VBO) and vertex array object(VBO)
        unsigned int vertexShader, fragmentShader, id;


        int  success;
        char infoLog[512];

        std::string vshadercode;
        std::string fshadercode;

        load_shader(vcode, fcode, vshadercode, fshadercode);

        //the vertex shader code
        const char *vertexShaderSource = vshadercode.c_str();
        //the vertex shader code
        const char *fragmentShaderSource = fshadercode.c_str();

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s \n", infoLog);
        }


        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s \n", infoLog);
        }


        id = glCreateProgram();
        glAttachShader(id, vertexShader);
        glAttachShader(id, fragmentShader);

        glLinkProgram(id);
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s \n", infoLog);
        }
        glUseProgram(id);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader); 
    }
    ~Shader()
    {
        glDeleteProgram(id);
    }
};