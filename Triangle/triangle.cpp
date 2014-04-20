#include <GLTools.h>
#include <GLShaderManager.h>
#include <GL/glut.h>

GLBatch squareBatch;
GLShaderManager shaderManager;

GLfloat blockSize = 0.1f;
GLfloat vVerts[] = {
    -blockSize, -blockSize, 0.0f, 
	blockSize, -blockSize, 0.0f,
	blockSize,  blockSize, 0.0f,
	-blockSize,  blockSize, 0.0f
};

// �ı䴰���С����
void ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
}

// ��Ⱦ����
void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    squareBatch.Draw();

    glutSwapBuffers();
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

void SpecialKeys(int key, int x, int y)
{
    // ����
    GLfloat stepSize = 0.025f;

    GLfloat blockX = vVerts[0];     ///< ����X
    GLfloat blockY = vVerts[7];     ///< ����Y

    if(key == GLUT_KEY_UP)  blockY += stepSize;
    if(key == GLUT_KEY_DOWN) blockY -= stepSize;
    if(key == GLUT_KEY_LEFT) blockX -= stepSize;
    if(key == GLUT_KEY_RIGHT) blockX += stepSize;

    // ��ײ���
    if(blockX < -1.0f) blockX = -1.0f;
    if(blockX > (1.0f - blockSize * 2)) blockX = 1.0f - blockSize * 2;
    if(blockY < -1.0f + blockSize * 2) blockY = -1.0f + blockSize * 2;
    if(blockY > 1.0f) blockY = 1.0f;

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
    glutPostRedisplay();
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
    glutSpecialFunc(SpecialKeys);

    SetupRC();
    glutMainLoop();
    return 0;
}
