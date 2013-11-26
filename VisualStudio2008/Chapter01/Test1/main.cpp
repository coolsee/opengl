#include "Application.h"

GLTriangleBatch torusBatch;

class testApp : public APP::application
{
public:
	testApp()
	{
	}

	void init()
	{
		// Black background
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f );
		glEnable(GL_DEPTH_TEST);

		m_shaderManager->InitializeStockShaders();
		// This makes a torus
		gltMakeTorus(torusBatch, 0.4f, 0.15f, 30, 30);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void onShutdown()
	{
	}

	void onResize(int w, int h)
	{
		if(h == 0)
			h = 1;
		glViewport(0, 0, w, h);
		m_viewFrustum->SetPerspective(35.0f, float(w)/float(h), 1.0f, 1000.0f);
	}

	void onKey(int key, int x, int y)
	{

	}
	void onRender()
	{
		static CStopWatch rotTimer;
		float yRot = rotTimer.GetElapsedSeconds() * 60.0f;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		M3DMatrix44f mTranslate, mRotate, mModelview, mModelViewProjection;
		m3dTranslationMatrix44(mTranslate, 0.0f, 0.0f, -2.5f);
		m3dRotationMatrix44(mRotate, m3dDegToRad(yRot), 0.0f, 1.0f, 0.0f);
		m3dMatrixMultiply44(mModelview, mTranslate, mRotate);
		m3dMatrixMultiply44(mModelViewProjection, m_viewFrustum->GetProjectionMatrix(),mModelview);

		// Pass this completed matrix to the shader, and render the torus
		GLfloat vBlack[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_shaderManager->UseStockShader(GLT_SHADER_FLAT, mModelViewProjection, vBlack);  
		torusBatch.Draw();

		// Swap buffers, and immediately refresh
		glutSwapBuffers();
		glutPostRedisplay();

	}

};


DECLARE_MAIN(testApp);
