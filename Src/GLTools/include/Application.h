#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>

#include <math.h>
#include <stdio.h>

#define FREEGLUT_STATIC
#include <GL/glut.h>

namespace APP
{
	class application
	{
	public:
		application() {}
		virtual ~application() {}
		virtual void run(APP::application* the_app)
		{
			bool running = true;
			app = the_app;

			app->m_viewFrame = new GLFrame;
			app->m_viewFrustum = new GLFrustum;
			app->m_modelViewMatix = new GLMatrixStack;
			app->m_projectionMatrix = new GLMatrixStack;
			app->m_shaderManager = new GLShaderManager;

			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
			glutInitWindowSize(800,600);
			glutCreateWindow("OpenGL SphereWorld");
			glutSpecialFunc(SpecialKeys);
			glutReshapeFunc(glfw_onResize);
			glutDisplayFunc(StaticRender);

			GLenum err = glewInit();
			if (GLEW_OK != err) {
				fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
				return;
			}
			init();

			glutMainLoop();    

			onShutdown();
		}

		virtual void init()
		{
		}

		virtual void onShutdown()
		{

		}

		virtual void onResize(int w, int h)
		{
		}

		virtual void onKey(int key, int x, int y)
		{

		}
		virtual void onRender()
		{

		}

		static APP::application * app;

		static void glfw_onResize(int w, int h)
		{
			app->onResize(w, h);
		}

		static void SpecialKeys(int key, int x, int y)
		{
			app->onKey(key, x, y);
		}

		static void StaticRender()
		{
			app->onRender();
		}

	protected:
		GLFrame*             m_viewFrame;
		GLFrustum*           m_viewFrustum;
		GLMatrixStack*       m_modelViewMatix;
		GLMatrixStack*       m_projectionMatrix;
		GLGeometryTransform* m_transformPipeline;
		GLShaderManager*     m_shaderManager;

	};

}
                      

#define DECLARE_MAIN(a)                             \
APP::application *APP::application::app = 0;        \
int main(int argc, char* argv[])					\
{                                                   \
	glutInit(&argc, argv);							\
    a *app = new a;                                 \
    app->run(app);									\
    delete app;                                     \
    return 0;                                       \
}

#endif /* __SB6_H__ */

