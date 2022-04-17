#include <iostream>
#include <math.h>

#define PI 3.14159265 
#define RADIUS 6378

using namespace std;

double radian(double degree){
  return (degree*PI)/180;
}

double alpha_calculator(double height, double tangent){
  double a = RADIUS/(RADIUS + height);
  double b = cos(tangent);

  return acos(a*b)-tangent;
}

int main(int argc, char *argv[]){

  double height, tangent;
  
  //INPUTS
  cout << "Height of satellite: ";
  cin >> height;

  cout << "Tangent angle of beam: ";
  cin >> tangent;

  //EQUASION
  tangent = radian(tangent);
  double alpha = alpha_calculator(height, tangent);
  double surface = 2*PI*pow(RADIUS,2)*(1-cos(alpha));

  //RATIO
  double ratio = 0.5*(1-cos(alpha))*100;
  cout << "SURFACE: " << surface << "km2" << endl;
  cout << "RATIO: " << ratio << "%" << endl;

  return 0;
}

