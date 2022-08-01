#include "MainWindow.h"
#include "Graphics.h"
#include "IDrawable.h"
#include "RenderTarget.h"

class RenderWindow
{
public:
	MainWindow* window;
	Graphics* graphics;
	Camera* boundCamera;

	RenderWindow();
	~RenderWindow();
	void Draw(IDrawable* object);
	void display();
	void setCamera(Camera* camera);
};