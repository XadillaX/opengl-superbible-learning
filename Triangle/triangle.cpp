#include <GLTools.h>
#include <GLShaderManager.h>
#include <GL/glut.h>

GLBatch squareBatch;
GLShaderManager shaderManager;

GLfloat blockSize = 0.1f;
GLfloat vVerts[] = {
    -blockSize - 0.5f, -blockSize, 0.0f, 
    blockSize - 0.5f, -blockSize, 0.0f,
    blockSize - 0.5f,  blockSize, 0.0f,
    -blockSize - 0.5f,  blockSize, 0.0f
};

// 改变窗体大小函数
void ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
}

// 移动并重绘
void BounceFunction()
{
    // 方向向量
    static GLfloat xDir = 1.0f;
	static GLfloat yDir = 1.0f;

    // 步长
    GLfloat stepSize = 0.005f;

    GLfloat blockX = vVerts[0];     ///< 左下X
    GLfloat blockY = vVerts[7];     ///< 右上Y

    // 以方向向量移动基准点
    blockY += stepSize * yDir;
	blockX += stepSize * xDir;

    // 碰撞检测并且反向
    if(blockX < -1.0f) blockX = -1.0f, xDir *= -1.0f;
    if(blockX > (1.0f - blockSize * 2)) blockX = 1.0f - blockSize * 2, xDir *= -1.0f;;
    if(blockY < -1.0f + blockSize * 2) blockY = -1.0f + blockSize * 2, yDir *= -1.0f;;
    if(blockY > 1.0f) blockY = 1.0f, yDir *= -1.0f;;

    // 第一个点
    vVerts[0] = blockX;
    vVerts[1] = blockY - blockSize * 2;

    // 第二个点
    vVerts[3] = blockX + blockSize * 2;
    vVerts[4] = blockY - blockSize * 2;

    // 第三个点
    vVerts[6] = blockX + blockSize * 2;
    vVerts[7] = blockY;

    // 第四个点
    vVerts[9] = blockX;
    vVerts[10] = blockY;

    squareBatch.CopyVertexData3f(vVerts);
}

// 渲染函数
void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    squareBatch.Draw();

    glutSwapBuffers();

    // 移动并重绘
    BounceFunction();
    glutPostRedisplay();
}

void SetupRC()
{
    // 设置背景色
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // 初始化着色器实例
    shaderManager.InitializeStockShaders();

    // 建立四边形批次
    squareBatch.Begin(GL_TRIANGLE_FAN, 4);
    squareBatch.CopyVertexData3f(vVerts);
    squareBatch.End();
}

int main(int argc, char* argv[])
{
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Move Block with Arrow Keys");

    GLenum err = glewInit();
    if(GLEW_OK != err)
    {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }

    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);

    SetupRC();
    glutMainLoop();
    return 0;
}
