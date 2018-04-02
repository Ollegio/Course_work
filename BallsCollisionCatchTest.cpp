#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "BallsCollision.h" 
#include "Particle.h"
#include "Event.h"


TEST_CASE("Reverse test") {
	SECTION("Moving particles") {
		test(5);
		initVariables();
		catchTest();
		for (int i = 0; i < PARTICLES_COUNT; i++) {
			REQUIRE(fabs(particles[i].getPos().x() - particlesTest[i].getPos().x()) < 1e-5);
			REQUIRE(fabs(particles[i].getPos().y() - particlesTest[i].getPos().y()) < 1e-5);
			REQUIRE(fabs(particles[i].getPos().z() - particlesTest[i].getPos().z()) < 1e-5);
		}
	}
}

GLvoid resizeGLScene(GLsizei width, GLsizei height) {
	if (height == 0) // Предотвращение деления на ноль 
		height = 1;

	glViewport(0, 0, width, height); // Сброс текущей области вывода 
	glMatrixMode(GL_PROJECTION); // Выбор матрицы проекций 
	glLoadIdentity(); // Сброс матрицы проекции 
					  // Вычисление соотношения геометрических размеров для окна 
	gluPerspective(50.0f, (GLfloat)width / (GLfloat)height, 10.f, 1700.0f);
	glMatrixMode(GL_MODELVIEW); // Выбор матрицы вида модели 
	glLoadIdentity(); // Сброс матрицы вида модели 
}

GLboolean initGLScene(GLvoid) {
	glClearDepth(1.0f); // Разрешить очистку буфера глубины 
	glEnable(GL_DEPTH_TEST); // Разрешить тест глубины 
	glDepthFunc(GL_LEQUAL); // Тип теста глубины 
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Улучшение в вычислении перспективы 

	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_TEXTURE_2D);
	if (!loadTexture(L"s.bmp", texture[0]))
		return false;

	return true;
}

GLint drawGLScene(GLvoid) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Очистить экран и буфер глубины 
	glLoadIdentity(); // Сбросить текущую матрицу 

	double a = 1000.0 * sin(0.017453 * (cameraTilt));
	double b = 1000.0 * cos(0.017453 * (cameraTilt));

	gluLookAt(camPosition.x(), camPosition.y() + a, camPosition.z() + b, camPosition.x() + camDirection.x(), camPosition.y() + camDirection.y(), camPosition.z() + camDirection.z(), 0, 1.0, 0.0);
	glRotatef(cameraRotation, 0, 1, 0);

	for (int i = 0; i < PARTICLES_COUNT; i++) {
		if (velocityColor == true)
			glColor3f(particles[i].getVel().length(), 0.0, 1.0 / particles[i].getVel().length());
		else
			glColor3fv(particles[i].getColor());
		glPushMatrix();
		glTranslated(particles[i].getPos().x(), particles[i].getPos().y(), particles[i].getPos().z());
		gluSphere(cylinderObj, particles[i].getR(), 20, 20);
		glPopMatrix();
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(300, 300, 300);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(300, -300, 300);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-300, -300, 300);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-300, 300, 300);

		glTexCoord2f(1.0f, 0.0f); glVertex3f(-300, 300, -300);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-300, -300, -300);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(300, -300, -300);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(300, 300, -300);

		glTexCoord2f(1.0f, 0.0f); glVertex3f(300, 300, -300);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(300, -300, -300);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(300, -300, 300);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(300, 300, 300);

		glTexCoord2f(1.0f, 0.0f); glVertex3f(-300, 300, 300);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-300, -300, 300);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-300, -300, -300);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-300, 300, -300);

		glTexCoord2f(1.0f, 0.0f); glVertex3f(-300, -300, 300);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(300, -300, 300);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(300, -300, -300);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-300, -300, -300);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	return true;
}

GLvoid createWin(char* title, GLfloat winWidth, GLfloat winHeight) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(200, 200);
	wnd = glutCreateWindow(title);
}

GLvoid renderScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	drawGLScene();
	glutPostRedisplay();
	glutSwapBuffers();
}

GLvoid keyPressed(unsigned char key, int x, int y) {
	if (key == VK_ESCAPE) {
		glutDestroyWindow(wnd);
		exit(0);
	}

	if (key == 'd')
		cameraRotation -= 5;

	if (key == 'a')
		cameraRotation += 5;

	if (key == 'w')
		cameraTilt = cameraTilt == 90 ? 90 : cameraTilt + 5;

	if (key == 's')
		cameraTilt = cameraTilt == -20 ? -20 : cameraTilt - 5;

}

/*int main() {
	setlocale(LC_ALL, "Russian");
	printf("Введите количество шаров (0 - тестовый режим)\n");
	int n;
	scanf("%d", &n);
	if (n == 0) {
		printf("Тесты:\n0. Обычная симуляция, 27 частиц\n");
		printf("1. Диффузия. 500 + 500 частиц\n");
		printf("2. Броуновское движение, 63 частицы + 1 макрочастица\n");
		printf("Введите номер теста: ");
		scanf("%d", &n);
		test(n);
		initVariables();

	}
	else {
		printf("Введите параметры каждого из N шаров через пробел:\n");
		printf("Координаты X, Y, Z, Компоненты скорости по X, Y, Z, радиус, масса\n");
		for (int i = 0; i < n; i++) {
			double x, y, z, vx, vy, vz, r, m;
			scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &x, &y, &z, &vx, &vy, &vz, &r, &m);
			particles[i] = Particle(x, y, z, vx, vy, vz, r, m);
		}
	}
	currentTime = 0.0;
	createWin("Balls Collision", 800, 600);
	initGLScene();
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);
	glutReshapeFunc(resizeGLScene);
	glutKeyboardFunc(keyPressed);
	glutMainLoop();
}*/

int main() {
	currentTime = 0.0;
	Catch::Session().run();
}

void catchTest() {
	double targetTime;
	for (;;) {
		//glutDisplayFunc(renderScene);
		static bool flag = true;
		static bool cycle = true;
		for (; cycle;) {
			Event currentEvent = !ct.empty() ? ct.top() : dummy;
			if (currentEvent.wasSuperveningEvent()) {
				ct.pop();
				continue;
			}
			for (int i = 0; i < PARTICLES_COUNT; i++) {
				particles[i].move(currentEvent.getTime() - currentTime);
			}
			currentTime = currentEvent.getTime();
			if (currentTime > 1000) {
				if (flag) {
					for (int i = 0; i < PARTICLES_COUNT; i++) {
						particles[i].setVel(-particles[i].getVel());
					}
					targetTime = currentTime;
					currentTime = 0.0;
					ct = std::priority_queue<Event>();
					initVariables();
					flag = false;
					
				}
			}
			if (!flag && fabs(currentTime - targetTime) < 1e-8)
				return;
			if (currentEvent.getType() == 4) {
				currentEvent.getParticle1()->bounce(currentEvent.getParticle2());
				currentEvent.getParticle1()->updateEvents();
				currentEvent.getParticle2()->updateEvents();
			}
			if (currentEvent.getType() == 1) {
				currentEvent.getParticle1()->bounceX();
				currentEvent.getParticle1()->updateEvents();
			}
			if (currentEvent.getType() == 2) {
				currentEvent.getParticle1()->bounceY();
				currentEvent.getParticle1()->updateEvents();
			}
			if (currentEvent.getType() == 3) {
				currentEvent.getParticle1()->bounceZ();
				currentEvent.getParticle1()->updateEvents();
			}
			if (currentEvent.getType() == 0) {
				ct.pop();
				ct.push(Event(currentTime + timeStep, nullptr, nullptr, 0));
				break;
			}
			continue;
		}
		//glutReshapeFunc(resizeGLScene);
		//glutKeyboardFunc(keyPressed);
	}
}

/*void idle() {
	for (;cycle;) {
		Event currentEvent = !ct.empty() ? ct.top() : dummy;
		if (currentEvent.wasSuperveningEvent()) {
			ct.pop();
			continue;
		}
		for (int i = 0; i < PARTICLES_COUNT; i++) {
			particles[i].move(currentEvent.getTime() - currentTime);
		}
		currentTime = currentEvent.getTime();
		if (currentTime > 1000) {
			if (flag) {
				for (int i = 0; i < PARTICLES_COUNT; i++) {
					particles[i].setVel(-particles[i].getVel());
				}
				currentTime = 0.0;
				ct = std::priority_queue<Event>();
				initVariables();
				flag = false;
			}
			else
				cycle = false;
		}
		if (currentEvent.getType() == 4) {
			currentEvent.getParticle1()->bounce(currentEvent.getParticle2());
			currentEvent.getParticle1()->updateEvents();
			currentEvent.getParticle2()->updateEvents();
		}
		if (currentEvent.getType() == 1) {
			currentEvent.getParticle1()->bounceX();
			currentEvent.getParticle1()->updateEvents();
		}
		if (currentEvent.getType() == 2) {
			currentEvent.getParticle1()->bounceY();
			currentEvent.getParticle1()->updateEvents();
		}
		if (currentEvent.getType() == 3) {
			currentEvent.getParticle1()->bounceZ();
			currentEvent.getParticle1()->updateEvents();
		}
		if (currentEvent.getType() == 0) {
			ct.pop();
			ct.push(Event(currentTime + timeStep, nullptr, nullptr, 0));
			break;
		}
		continue;
	}
}*/

GLvoid initVariables() {
	for (int i = 0; i < PARTICLES_COUNT; i++) {
		particles[i].updateEvents();
	}
	ct.push(Event(currentTime + timeStep, nullptr, nullptr, 0));
	cylinderObj = gluNewQuadric(); //объект для сферы 
	gluQuadricTexture(cylinderObj, GL_TRUE);
}


GLboolean loadTexture(LPTSTR szFileName, GLuint &texid) {
	HBITMAP hBMP;
	BITMAP BMP;
	glGenTextures(1, &texid);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), szFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	if (!hBMP)
		return FALSE;

	GetObject(hBMP, sizeof(BMP), &BMP);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	DeleteObject(hBMP);
	return true;
}

void test(int i) {
	int lattice_x, lattice_y, lattice_z;
	switch (i) {
	case 0:
		PARTICLES_COUNT = 27;
		lattice_x = 3, lattice_y = 3, lattice_z = 3;
		for (int z = 0; z < lattice_z; z++) {
			for (int y = 0; y < lattice_y; y++) {
				for (int x = 0; x < lattice_x; x++) {
					particles[x + z * lattice_y * lattice_x + y * lattice_x] = 
						Particle(-250.0 + x * 100.0, y * 100.0 - 200.0, -250.0 + z * 100.0, 0.0, 0.0, 0.0, 1.0, 20.0);
				}
			}
		}
		particles[0] = 
			Particle(0.0, 0.0, 0.0, -7.0, -5.0, -2.0, 1.0, 20.0);
		break;
	case 1:
		PARTICLES_COUNT = 1000;
		velocityColor = false;
		lattice_x = 10, lattice_y = 10, lattice_z = 10;
		for (int z = 0; z < lattice_z; z++) {
			for (int y = 0; y < lattice_y; y++) {
				for (int x = 0; x < lattice_x; x++) {
					Particle ball = Particle(-270.0 + x * 45, y * 45 - 270.0, -250.0 + z * 50,
						((rand() % 50) - 5) / 10.0, ((rand() % 50) - 5) / 10.0, ((rand() % 50) - 5) / 10.0,
						1.0, 15);
					x < 5 ? ball.setColor(1, 1, 1) : ball.setColor(0, 0, 0); 
					particles[x + z * lattice_y * lattice_x + y * lattice_x] =
						ball;
				}
			}
		}
		particles[0] =
			Particle(-250.0, -200.0, -150.0,
				10.0, 10.0, 10.0,
				1.0, 15);
		break;
	case 2:
		PARTICLES_COUNT = 64;
		lattice_x = 8, lattice_y = 8, lattice_z = 1;
		for (int z = 0; z < lattice_z; z++) {
			for (int y = 0; y < lattice_y; y++) {
				for (int x = 0; x < lattice_x; x++) {
					particles[x + z * lattice_y * lattice_x + y * lattice_x] =
						Particle(-250.0 + x * 50, y * 50 - 200.0, -250.0 + z * 100,
							rand() % 10 / 2.0, rand() % 10 / 2.0, rand() % 10 / 2.0,
							1.0, 10);
				}
			}
		}
		particles[0] =
			Particle(0.0,0.0,0.0,
				0.0,0.0,0.0, 
				100.0, 65);

		break;
	case 3:
		
		velocityColor = false;
		lattice_x = 2;
		PARTICLES_COUNT = lattice_x * lattice_x * lattice_x;
		for (int z = 0; z < lattice_z; z++) {
			for (int y = 0; y < lattice_y; y++) {
				for (int x = 0; x < lattice_x; x++) {
					Particle ball = Particle(-270.0 + x * 45, y * 45 - 270.0, -250.0 + z * 50,
						((rand() % 50) - 5) / 10.0, ((rand() % 50) - 5) / 10.0, ((rand() % 50) - 5) / 10.0,
						1.0, 15);
					x < 5 ? ball.setColor(1, 1, 1) : ball.setColor(0, 0, 0);
					particles[x + z * lattice_y * lattice_x + y * lattice_x] =
						ball;
				}
			}
		}
		break;
	case 4:
		PARTICLES_COUNT = 2;
		particles[0] =
			Particle(5.0, 0.0, 100.0,
				0.0, 0.0, -1.0,
				1.0, 20);
		particles[1] =
			Particle(-5.0, 0.0, -100.0,
				0.0, 0.0, 1.0,
				1.0, 20);
		break;
	case 5:
		PARTICLES_COUNT = 27;
		lattice_x = 3, lattice_y = 3, lattice_z = 3;
		for (int z = 0; z < lattice_z; z++) {
			for (int y = 0; y < lattice_y; y++) {
				for (int x = 0; x < lattice_x; x++) {
					particles[x + z * lattice_y * lattice_x + y * lattice_x] =
						Particle(-250.0 + x * 100.0, y * 100.0 - 200.0, -250.0 + z * 100.0, 0.0, 0.0, 0.0, 1.0, 20.0);
					particlesTest[x + z * lattice_y * lattice_x + y * lattice_x] =
						Particle(-250.0 + x * 100.0, y * 100.0 - 200.0, -250.0 + z * 100.0, 0.0, 0.0, 0.0, 1.0, 20.0);
				}
			}
		}
		particles[0] =
			Particle(0.0, 0.0, 0.0, -7.0, -5.0, -2.0, 1.0, 20.0);
		particlesTest[0] =
			Particle(0.0, 0.0, 0.0, -7.0, -5.0, -2.0, 1.0, 20.0);
		break;
		break;
	}
}