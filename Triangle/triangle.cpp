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

// �ı䴰���С����
void ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
}

// �ƶ����ػ�
void BounceFunction()
{
    // ��������
    static GLfloat xDir = 1.0f;
	static GLfloat yDir = 1.0f;

    // ����
    GLfloat stepSize = 0.005f;

    GLfloat blockX = vVerts[0];     ///< ����X
    GLfloat blockY = vVerts[7];     ///< ����Y

    // �Է��������ƶ���׼��
    blockY += stepSize * yDir;
	blockX += stepSize * xDir;

    // ��ײ��Ⲣ�ҷ���
    if(blockX < -1.0f) blockX = -1.0f, xDir *= -1.0f;
    if(blockX > (1.0f - blockSize * 2)) blockX = 1.0f - blockSize * 2, xDir *= -1.0f;;
    if(blockY < -1.0f + blockSize * 2) blockY = -1.0f + blockSize * 2, yDir *= -1.0f;;
    if(blockY > 1.0f) blockY = 1.0f, yDir *= -1.0f;;

    // ��һ����
    vVerts[0] = blockX;
    vVerts[1] = blockY - blockSize * 2;

    // �ڶ�����
    vVerts[3] = blockX + blockSize * 2;
    vVerts[4] = blockY - blockSize * 2;

    // ��������
    vVerts[6] = blockX + blockSize * 2;
    vVerts[7] = blockY;

    // ���ĸ���
    vVerts[9] = blockX;
    vVerts[10] = blockY;

    squareBatch.CopyVertexData3f(vVerts);
}

// ��Ⱦ����
void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    squareBatch.Draw();

    glutSwapBuffers();

    // �ƶ����ػ�
    BounceFunction();
    glutPostRedisplay();
}

void SetupRC()
{
    // ���ñ���ɫ
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // ��ʼ����ɫ��ʵ��
    shaderManager.InitializeStockShaders();

    // �����ı�������
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
