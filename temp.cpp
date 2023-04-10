// void myKeyboardFunc(unsigned char key, int x, int y)
// {
// }

// void fullScreen(int w, int h)
// {
//     if (h == 0)
//         h = 1;
//     float ratio = (GLfloat)w / (GLfloat)h;
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();

//     glViewport(0, 0, w, h);
//     gluPerspective(60, ratio, 1, 500);
//     glMatrixMode(GL_MODELVIEW);
// }


// int main(int argc, char **argv)
// {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

//     glutInitWindowPosition(100, 100);
//     glutInitWindowSize(800, 600);
//     glutCreateWindow("CS 352 Amusement Park");

//     glShadeModel(GL_SMOOTH);
//     glEnable(GL_DEPTH_TEST);
//     glEnable(GL_NORMALIZE);

//     // ....

//     glutReshapeFunc(fullScreen);
//     glutKeyboardFunc(myKeyboardFunc);
//     glEnable(GL_BLEND);
//     glEnable(GL_DEPTH_TEST);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//     glutDisplayFunc(display);
//     glutMainLoop();

//     return 0;
// }