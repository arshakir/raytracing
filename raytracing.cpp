#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

struct vec3 {
  double x, y, z;
  vec3(double xd, double yd, double zd) {
    x = xd;
    y = yd;
    z = zd;
  }
};

struct sphere {
  double r, x, y, z;
  sphere(double xd, double yd, double zd, double rd) {
    x = xd;
    y = yd;
    z = zd;
    r = rd;
  }
};

struct color {
  int r, g, b;
  color(int red, int green, int blue) {
    r = red;
    g = green;
    b = blue;
  }
};

double mag(vec3 e) { return sqrt(e.x * e.x + e.y * e.y + e.z * e.z); }

vec3 unit(vec3 e) {
  double m = mag(e);
  e.x = e.x / m;
  e.y = e.y / m;
  e.z = e.z / m;
  return e;
}

double dot(vec3 e1, vec3 e2) { return e1.x * e2.x + e1.y * e2.y + e1.z * e2.z; }

double sol(vec3 e, sphere s) {
  double a, b, c, disc, sol[2] = {-1, -1};

  a = e.x * e.x + e.y * e.y + e.z * e.z;
  b = 2 * (-1 * e.x * s.x + -1 * e.y * s.y + -1 * e.z * s.z);
  c = s.x * s.x + s.y * s.y + s.z * s.z - s.r * s.r;

  disc = b * b - 4 * a * c;

  if (disc >= 0) {
    sol[0] = (-1 * b + sqrt(disc)) / (2 * a);
    sol[1] = (-1 * b - sqrt(disc)) / (2 * a);
  }

  return min(sol[1], sol[0]);
}

color hit(vec3 e, vector<sphere> s, vec3 light) {
  double u;
  int w,b,c;

  for (int i = 0; i < s.size(); i++) {
    u = sol(e, s[i]);
    if (u == -1) {
    } else {
      vec3 p(e.x * u, e.y * u, e.z * u);
      vec3 a(light.x - p.x, light.y - p.y, light.z - p.z);
      if (i==0){
        w=1;
        b=0;
        c=0;
      } else if (i==1){
        w=0;
        b=1;
        c=0;
      } else if (i==2){
        w=0;
        b=0;
        c=1;
      } else {
        w=1;
        b=1;
        c=1;
      }
      return color(200 * (1 + dot(unit(p), unit(a))) * w, 200 * (1 + dot(unit(p), unit(a))) * b, 200 * (1 + dot(unit(p), unit(a))) * c);
    }
  }
  return color(0,0,0);
}

int main() {
  srand(time(0));
  vec3 p(0, 0, 0);
  vector<sphere> s;
  s.push_back(sphere(10, 0, 20, 10));
  s.push_back(sphere(-10, 0, 20, 5));
  s.push_back(sphere(0,-5,10,3));
  s.push_back(sphere(-10,15,25,3));
  vec3 light(5, 50, -5);
  double u;

  cout << "P3\n1000 1000\n255\n";
  for (int y = 500; y > -500; y--) {
    for (int x = -500; x < 500; x++) {
      color c = hit(vec3(x, y, 500), s, light);
      cout << c.r << " " << c.g << " " << c.b << endl;
    }
  }
}
