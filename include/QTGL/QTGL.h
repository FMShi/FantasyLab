#ifndef _QTGL_WINDOW_H_
#define _QTGL_WINDOW_H_

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>

namespace QTGL {

		//class Impl_RawAPI_OGLW;

		class QTGLWindow : public QOpenGLWidget
		{
		public:
			QTGLWindow(QWidget* parent = nullptr, ::Qt::WindowFlags f = ::Qt::WindowFlags())
			{

			}
			~QTGLWindow()
			{

			}

			//void SetPaintOp(Basic::Ptr<Basic::Operation> paintOp);

		protected:
			virtual void initializeGL()
			{}
			virtual void resizeGL(int w, int h)
			{}
			virtual void paintGL()
			{}

		private:
			//Basic::Ptr<Basic::Operation> paintOp;
			QOpenGLFunctions_4_5_Core* GL4Core;
		};
}

#endif 
