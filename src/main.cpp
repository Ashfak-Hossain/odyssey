#include "Game.h"
#include "Platform.h"

Game game;

void display() {
  game.render();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Odyssey");
  game.init();
  glutDisplayFunc(display);
  glutMainLoop();

  return 0;
}