#include <string>
#include <iostream>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "libim/im_color.h"
#include "Player.h"

Maze maze = Maze();
Player player = Player();
int xdim, ydim;
unsigned char *grass;
unsigned char *brick;
unsigned char *rock;
unsigned char *wood;

void block(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax)
{
	// Define 8 vertices
	float ax = xmin, ay = ymin, az = zmax;
	float bx = xmax, by = ymin, bz = zmax;
	float cx = xmax, cy = ymax, cz = zmax;
	float dx = xmin, dy = ymax, dz = zmax;
	float ex = xmin, ey = ymin, ez = zmin;
	float fx = xmax, fy = ymin, fz = zmin;
	float gx = xmax, gy = ymax, gz = zmin;
	float hx = xmin, hy = ymax, hz = zmin;

	// Draw 6 faces
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(ax, ay, az);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(bx, by, bz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(cx, cy, cz);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(dx, dy, dz);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(ax, ay, az);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(dx, dy, dz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(hx, hy, hz);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(ex, ey, ez);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(ax, ay, az);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(ex, ey, ez);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(fx, fy, fz);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(bx, by, bz);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(gx, gy, gz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(fx, fy, fz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(ex, ey, ez);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(hx, hy, hz);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(gx, gy, gz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(cx, cy, cz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(bx, by, bz);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(fx, fy, fz);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(gx, gy, gz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(hx, hy, hz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(dx, dy, dz);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(cx, cy, cz);
	glEnd();
}

void cube(float midx, float midy, float midz, float size, float r, float g, float b)
{
	// Define 8 vertices
	float ax = midx - size / 2;
	float ay = midy - size / 2;
	float az = midz + size / 2;
	float bx = midx + size / 2;
	float by = midy - size / 2;
	float bz = midz + size / 2;
	float cx = midx + size / 2;
	float cy = midy + size / 2;
	float cz = midz + size / 2;
	float dx = midx - size / 2;
	float dy = midy + size / 2;
	float dz = midz + size / 2;
	float ex = midx - size / 2;
	float ey = midy - size / 2;
	float ez = midz - size / 2;
	float fx = midx + size / 2;
	float fy = midy - size / 2;
	float fz = midz - size / 2;
	float gx = midx + size / 2;
	float gy = midy + size / 2;
	float gz = midz - size / 2;
	float hx = midx - size / 2;
	float hy = midy + size / 2;
	float hz = midz - size / 2;

	// Draw 6 faces
	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	glVertex3f(ax, ay, az);
	glVertex3f(bx, by, bz);
	glVertex3f(cx, cy, cz);
	glVertex3f(dx, dy, dz);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(r - .1, g - .1, b - .1);
	glVertex3f(ax, ay, az);
	glVertex3f(dx, dy, dz);
	glVertex3f(hx, hy, hz);
	glVertex3f(ex, ey, ez);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(r - .04, g - .04, b - .04);
	glVertex3f(ax, ay, az);
	glVertex3f(ex, ey, ez);
	glVertex3f(fx, fy, fz);
	glVertex3f(bx, by, bz);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(r + .04, g + .04, b + .04);
	glVertex3f(gx, gy, gz);
	glVertex3f(fx, fy, fz);
	glVertex3f(ex, ey, ez);
	glVertex3f(hx, hy, hz);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(r - .12, g - .12, b - .12);

	glVertex3f(gx, gy, gz);
	glVertex3f(cx, cy, cz);
	glVertex3f(bx, by, bz);
	glVertex3f(fx, fy, fz);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(r - .2, g - .2, b - .2);
	glVertex3f(gx, gy, gz);
	glVertex3f(hx, hy, hz);
	glVertex3f(dx, dy, dz);
	glVertex3f(cx, cy, cz);
	glEnd();
}

float xAngle = 0;
float yAngle = 0;
float zAngle = 0;
// Material properties
float Ka = 0.2;
float Kd = 0.5;
float Ks = 0.7;
float Kp = 0.6;
void init_material(float Ka, float Kd, float Ks, float Kp, float Mr, float Mg, float Mb)
{
	// Material variables
	float ambient[] = {Ka * Mr, Ka * Mg, Ka * Mb, 1.0};
	float diffuse[] = {Kd * Mr, Kd * Mg, Kd * Mb, 1.0};
	float specular[] = {Ks * Mr, Ks * Mg, Ks * Mb, 1.0};

	// Initialize material
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Kp);
}
void init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim)
{
	// Read jpg image
	im_color image;
	image.ReadJpg(name);
	printf("Reading image %s\n", name);
	xdim = 1;
	while (xdim < image.R.Xdim)
		xdim *= 2;
	xdim /= 2;
	ydim = 1;
	while (ydim < image.R.Ydim)
		ydim *= 2;
	ydim /= 2;
	image.Interpolate(xdim, ydim);
	printf("Interpolating to %d by %d\n", xdim, ydim);

	// Copy image into texture array
	texture = (unsigned char *)malloc((unsigned int)(xdim * ydim * 3));
	int index = 0;
	for (int y = 0; y < ydim; y++)
		for (int x = 0; x < xdim; x++)
		{
			texture[index++] = (unsigned char)(image.R.Data2D[y][x]);
			texture[index++] = (unsigned char)(image.G.Data2D[y][x]);
			texture[index++] = (unsigned char)(image.B.Data2D[y][x]);
		}
}
void setTexture(char material)
{
	if (material == ' ')
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, grass);
	}
	else if (material == 'r')
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, rock);
	}
	else if (material == 'b')
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, brick);
	}
	else if (material == 'w')
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, wood);
	}
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();
	glRotatef(xAngle, 1.0, 0.0, 0.0);
	glRotatef(yAngle, 0.0, 1.0, 0.0);
	glRotatef(zAngle, 0.0, 0.0, 1.0);

	//draw floor
	setTexture(' ');
	// init_material(Ka, Kd, Ks, 100 * Kp, 0.8, 0.6, 0.4);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-.8, 0, -.8);
	glTexCoord2f(2.0, 0);
	glVertex3f(-.8, 0, .8);
	glTexCoord2f(2.0, 2.0);
	glVertex3f(.8, 0, .8);
	glTexCoord2f(0, 1.0);
	glVertex3f(.8, 0, -.8);
	glEnd();
	xAngle = 0;
	yAngle = 0;
	zAngle = 0;
	// draw the player
	auto position = player.getPlayerPosition();
	// printf("player position: %f, %f, %f\n", position[0], position[1], position[2]);
	cube(position[0], position[1] + 0.03125/2, position[2], 0.03125, (float)201 / 255, (float)66 / 255, (float)68 / 255);
	// glPushMatrix();
	for (int z = 0; z < maze.getRowCount(); z++)
	{
		for (int x = 0; x < maze.getColumnCount(); x++)
		{
			int height = 3;
			char material = maze.getBlockMaterial(z, x);
			if (material != ' ')
			{
				// printf("%i, %i\n", z, x);
				float xCoord = -.5 + x * maze.getBlockXSize();
				float yCoord = height * maze.getBlockYSize();
				float zCoord = .5 - z * maze.getBlockZSize();
				// printf("%f, %f, %f\n", xCoord, yCoord, zCoord);
				glEnable(GL_TEXTURE_2D);
				setTexture(material);
				block(xCoord, 0, zCoord, xCoord + maze.getBlockXSize(), yCoord, zCoord + maze.getBlockZSize());
			}
		}
	}
	glFlush();
}
void keyboard(unsigned char key, int x, int y)
{
	if (key == 'x')
	{
		xAngle -= 5;
		glutPostRedisplay();
	}
	if (key == 'X')
	{
		xAngle += 5;
		glutPostRedisplay();
	}
	if (key == 'y')
	{
		yAngle -= 5;
		glutPostRedisplay();
	}
	if (key == 'Y')
	{
		yAngle += 5;
		glutPostRedisplay();
	}
	if (key == 'z')
	{
		zAngle -= 5;
		glutPostRedisplay();
	}
	if (key == 'Z')
	{
		zAngle += 5;
		glutPostRedisplay();
	}
	if (key == 'r' || key == 'R')
	{
		xAngle = 0;
		yAngle = 0;
		zAngle = 0;
		glutPostRedisplay();
	}
	if (std::tolower(key) == 'w')
	{
		player.moveForwards();
		glutPostRedisplay();
	}
	if (std::tolower(key) == 's')
	{
		player.moveBackwards();
		glutPostRedisplay();
	}
	if (std::tolower(key) == 'd')
	{
		player.moveRight();
		glutPostRedisplay();
	}
	if (std::tolower(key) == 'a')
	{
		player.moveLeft();
		glutPostRedisplay();
	}
	if (std::tolower(key) == 'l') {
		player.turnLeft();
	}
	if (std::tolower(key) == 'r') {
		player.turnRight();
	}
}
void init_light(int light_source, float Lx, float Ly, float Lz, float Lr, float Lg, float Lb)
{
	// Light variables
	float light_position[] = {Lx, Ly, Lz, 0.0};
	float light_color[] = {Lr, Lg, Lb, 1.0};

	// Initialize light source
	glEnable(GL_LIGHTING);
	glEnable(light_source);
	glLightfv(light_source, GL_POSITION, light_position);
	glLightfv(light_source, GL_AMBIENT, light_color);
	glLightfv(light_source, GL_DIFFUSE, light_color);
	glLightfv(light_source, GL_SPECULAR, light_color);
	glLightf(light_source, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(light_source, GL_LINEAR_ATTENUATION, 0.0);
	glLightf(light_source, GL_QUADRATIC_ATTENUATION, 0.0);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}
void init()
{
	const auto mazeFileName = "maze.txt";
	maze.readMazeFile(mazeFileName);
	// const float playerMargin = .0625;
	const auto ip = maze.getInitialPosition();
	printf("%f, %f, %f\n", ip[0], ip[1], ip[2]);
	player = Player(maze.getInitialPosition(), maze.getBlockXSize(), maze.getBlockXSize(), maze.getBlockXSize(), &maze);
	// yAngle = 90;
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	// glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, -2.0);
	glLoadIdentity();
	init_light(GL_LIGHT0, 0, 1, 1, 0.5, 0.5, 0.5);
	init_light(GL_LIGHT1, 1, 0, 0, 0.5, 0.5, 0.5);
	init_light(GL_LIGHT2, 1, 1, 0, 0.5, 0.5, 0.5);
	init_light(GL_LIGHT3, 1, 0, 1, 0.5, 0.5, 0.5);

	// Init textures
	init_texture((char *)"textures/grass.jpg", grass, xdim, ydim);
	init_texture((char *)"textures/brick.jpg", brick, xdim, ydim);
	init_texture((char *)"textures/rock.jpg", rock, xdim, ydim);
	init_texture((char *)"textures/wood.jpg", wood, xdim, ydim);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(250, 250);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutCreateWindow("Maze");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();
	return 0;
}