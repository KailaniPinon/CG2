#include "Init.h"

GLFWwindow* window = NULL;

int InitWindowFailed() {
	if (glfwInit() == GLFW_FAIL) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return EXIT_WITH_ERROR;
	}

	glfwWindowHint(GLFW_SAMPLES, ANTIALIASING);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPEN_GL_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPEN_GL_VERSION);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Gets working on mac...
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old open gl...

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME, NULL, NULL);

	if (window == NULL) {
		fprintf(stderr, "Failed to create/open GLFW window.\n");
		glfwTerminate();
		return EXIT_WITH_ERROR;
	}

	//Initialize GLEW.
	glfwMakeContextCurrent(window);

	//Ensure we can capture the escape key being pressed below.
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	return EXIT_WITH_SUCCESS;
}

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path) {
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//Read in shader code here...
	string vertexShaderCode = "";
	ifstream vertexShaderStream(vertex_file_path, ios::in);
	if (vertexShaderStream.is_open()) {
		string line = "";
		while (getline(vertexShaderStream, line)) {
			vertexShaderCode += "\n" + line;
		}
		vertexShaderStream.close();
	}

	string fragmentShaderCode = "";
	ifstream fragmentShaderStream(fragment_file_path, ios::in);
	if (fragmentShaderStream.is_open()) {
		string line = "";
		while (getline(fragmentShaderStream, line)) {
			fragmentShaderCode += "\n" + line;
		}
		fragmentShaderStream.close();
	}

	GLint result = GL_FALSE;
	int infoLogLength = 0;

	//Compile shaders here...
	printf("Compiling vertex shader: %s\n", vertex_file_path);
	char const *vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	//Check Vertex Shader...
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

	char* vertexShaderErrorMessage = new char[infoLogLength];
	glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &vertexShaderErrorMessage[0]);

	//Compile Fragment Shader...
	printf("Compiling fragment shader: %s\n", fragment_file_path);
	char const *fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderID);

	//Check Vertex Shader...
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

	char* fragmentShaderErrorMessage = new char[infoLogLength];
	glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &fragmentShaderErrorMessage[0]);

	//Link Program...
	fprintf(stdout, "Linking program\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	//Check the progam...
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	char *programErrorMessage = new char[glm::max(infoLogLength, int(1))];
	glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
	fprintf(stdout, "%s\n", &programErrorMessage[0]);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	delete(programErrorMessage);
	programErrorMessage = NULL;

	delete(vertexShaderErrorMessage);
	vertexShaderErrorMessage = NULL;

	delete(fragmentShaderErrorMessage);
	fragmentShaderErrorMessage = NULL;

	return programID;
}

int InitGlewFailed() {
	glewExperimental = true;	//Has to do with core profile.
	int init = (int)glewInit();
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return EXIT_WITH_ERROR;
	}

	return EXIT_WITH_SUCCESS;
}

GLuint& LoadQuad() {

	static GLfloat g_vertex_buffer_data[] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	for (int i = 0, size = 18; i < size; ++i) {
		g_vertex_buffer_data[i] -= 0.5f;
	}

	GLuint vertexBuffer = 0;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	return vertexBuffer;
}

GLuint& LoadTriangle() {
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	GLuint vertexBuffer = 0;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	return vertexBuffer;
}

GLuint& LoadCustomQuad() {
	static GLfloat g_vertex_buffer_data[] = {
		// positions			// colors
		0.0f, 0.0f, 0.0f,		1.0f, 0.0f, 0.5f,  // bottom right
		1.0f, 0.0f, 0.0f,		0.0f, 1.0f, 1.0f,  // bottom left
		0.0f, 1.0f, 0.0f,		1.0f, 1.0f, 0.0f   // top left	
		
	,	0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 0.0f,  // bottom right
		0.5f, 0.5f, 0.0f,		0.0f, 1.0f, 1.0f,  // top right
		-0.5f, 0.5f, 0.0f,		0.5f, 0.0f, 0.5f   // top left

		//0.0f, 0.0f, 0.0f,	// x , y , z		|	right tri, lower left
		//1.0f, 0.0f, 0.0f,	// x , y , z		|	right tri, lower right
		//1.0f, 1.0f, 0.0f,	// x , y , z		|	right tri, upper right

		//0.0f, 0.0f, 0.0f,	// x , y , z		|	left tri, lower left
		//1.0f, 1.0f, 0.0f,	// x , y , z		|	left tri, upper right
		//0.0f, 1.0f, 0.0f	// x , y , z		|	left tri, upper left
	};

	for (int i = 0, size = 18; i < size; ++i) {
		g_vertex_buffer_data[i] -= 0.5f;
	}

	GLuint vertexBuffer = 0;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	return vertexBuffer;
}

GLuint& LoadCube() {

	static GLfloat g_vertex_buffer_data[] = {
		//front face		
		// x , y , z
		0.0f, 0.0f, 0.0f,		
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		//top face
		// x , y , z
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		//right face
		// x , y , z
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f,

		//back face
		// x , y , z
		1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,

		1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,

		//bottom face
		// x , y , z
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,

		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,

		//left face
		// x , y , z
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f
	};

	int numbPoints = 6 * 3 * 6;
	for (int i = 0; i < numbPoints; ++i) {
		g_vertex_buffer_data[i] -= 0.5f;
	}

	GLuint vertexBuffer = 0;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	return vertexBuffer;
}
//mvp model view projection
