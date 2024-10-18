#ifndef GameStartWidget_HPP
#define GameStartWidget_HPP

#include <QOpenGLWidget>
namespace ui
{
class GameStartWidget : public QOpenGLWidget
{
public:
  GameStartWidget(QWidget *parent) : QOpenGLWidget(parent) {};
protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
};
}

#endif // GameStartWidget_HPP