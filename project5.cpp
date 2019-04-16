#include <string>
#include <iostream>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Maze.h"
#include "libim/im_color.h"

Maze maze = Maze();
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
	// GLubyte myTextels[512][512];
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
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();
	glRotatef(xAngle, 1.0, 0.0, 0.0);
	glRotatef(yAngle, 0.0, 1.0, 0.0);
	glRotatef(zAngle, 0.0, 0.0, 1.0);

	//draw floor
	// init_material(Ka, Kd, Ks, 100 * Kp, 0.8, 0.6, 0.4);
	glBegin(GL_POLYGON);
	glColor3f(0.1, 0.1, 0.1);
	glVertex3f(-.8, 0, -.8);
	glVertex3f(-.8, 0, .8);
	glVertex3f(.8, 0, .8);
	glVertex3f(.8, 0, -.8);
	glEnd();
	xAngle = 0;
	yAngle = 0;
	zAngle = 0;
	// draw the cube
	// glPushMatrix();
	for (int x = 0; x < maze.getColumnCount(); x++)
	{
		for (int z = 0; z < maze.getRowCount(); z++)
		{
			int height = 1;
			char material = maze.getBlockMaterial(x, z);
			if (material != ' ')
			{
				height = 3;
			}
			for (int y = 0; y < height; y++)
			{
				float xCoord = x * maze.getBlockXSize() - .5;
				float yCoord = y * maze.getBlockYSize();
				float zCoord = z * maze.getBlockZSize() - .5;
				printf("%f, %f\n", x, z);
				if (material == ' ')
				{
					glEnable(GL_TEXTURE_2D);
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, grass);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				}
				else if (material == 'r')
				{
					glEnable(GL_TEXTURE_2D);
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, rock);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				}
				else if (material == 'b')
				{
					glEnable(GL_TEXTURE_2D);
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, brick);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				}
				else if (material == 'w') {
					glEnable(GL_TEXTURE_2D);
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, wood);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				}
				block(xCoord, yCoord, zCoord, xCoord + maze.getBlockXSize(), yCoord + maze.getBlockYSize(), zCoord + maze.getBlockZSize());
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
	}
	else if (key == 'X')
	{
		xAngle += 5;
	}
	else if (key == 'y')
	{
		yAngle -= 5;
	}
	else if (key == 'Y')
	{
		yAngle += 5;
	}
	else if (key == 'z')
	{
		zAngle -= 5;
	}
	else if (key == 'Z')
	{
		zAngle += 5;
	}
	else if (key == 'r' || key == 'R')
	{
		xAngle = 0;
		yAngle = 0;
		zAngle = 0;
	}
	glutPostRedisplay();
}
void init_light(int light_source, float Lx, float Ly, float Lz, float Lr, float Lg, float Lb) {
	// Light variables
	float light_position[] = { Lx, Ly, Lz, 0.0 };
	float light_color[] = { Lr, Lg, Lb, 1.0 };

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
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	init_light(GL_LIGHT0, 0, 1, 1, 0.5, 0.5, 0.5);
	init_light(GL_LIGHT1, 1, 0, 0, 0.5, 0.5, 0.5);
	init_light(GL_LIGHT2, 1, 1, 0, 0.5, 0.5, 0.5);
	init_light(GL_LIGHT3, 1, 0, 1, 0.5, 0.5, 0.5);

	// Init grass texture
	init_texture((char *)"textures/grass.jpg", grass, xdim, ydim);
	init_texture((char *)"textures/brick.jpg", brick, xdim, ydim);
	init_texture((char *)"textures/rock.jpg", rock, xdim, ydim);
	init_texture((char *)"textures/wood.jpg", wood, xdim, ydim);
}

int main(int argc, char *argv[])
{
	const auto mazeFileName = "maze.txt";
	maze.readMazeFile(mazeFileName);
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