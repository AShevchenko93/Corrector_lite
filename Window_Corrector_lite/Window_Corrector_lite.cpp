#include "Window_Corrector_lite.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Window_Corrector_lite::Window_Corrector_lite form;
	Application::Run(%form);
}
