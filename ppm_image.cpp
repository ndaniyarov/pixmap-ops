#include "ppm_image.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace agl;
using namespace std;

ppm_image::ppm_image() 
{
   widthVar = 0;
   heightVar = 0;
}

ppm_image::ppm_image(int w, int h)
{
   widthVar = w;
   heightVar = h;
   pixel = new ppm_pixel[h*w];

}

ppm_image::ppm_image(const ppm_image& orig)
{
   widthVar = orig.widthVar;
   heightVar = orig.heightVar;
   
   int size = orig.widthVar*orig.heightVar;
   pixel = new ppm_pixel[size];
   for (int i = 0; i < size; i++){ 
      pixel[i].r = (int)orig.pixel[i].r;
      pixel[i].g = (int)orig.pixel[i].g;
      pixel[i].b = (int)orig.pixel[i].b; 
      
  }
  for (int i = 0; i < size; i++)
  cout << (int)orig.pixel[i].r << (int)orig.pixel[i].g << (int)orig.pixel[i].b << " " <<i << endl;
}

ppm_image& ppm_image::operator=(const ppm_image& orig)
{
   if (&orig == this) // protect against self-assignment
   {
      return *this;
   }
   if (pixel != NULL)
      delete[] pixel; 
   widthVar = orig.widthVar;
   heightVar = orig.heightVar;

   int size = orig.widthVar*orig.heightVar;
   pixel = new ppm_pixel[size];
   for (int i = 0; i < size; i++){ 
      pixel[i].r = orig.pixel[i].r;
      pixel[i].g = orig.pixel[i].g;
      pixel[i].b = orig.pixel[i].b; 
  }
   return *this;
   delete[] pixel;
}

ppm_image::~ppm_image()
{
   delete[] pixel;
}

bool ppm_image::load(const std::string& filename)
{
   ifstream file(filename);
   if (!file){
      return false;
   }
   string line;
   string p3;
   int max;
   pixel = new ppm_pixel[widthVar*heightVar];
   file >> p3 >> widthVar >> heightVar >> max;
   if (!file){
      return false;
   }
      int red, green, blue = 0;
      for (int i = 0; i < widthVar*heightVar; i++){
         file >> red >> green >> blue;
         pixel[i].r = red;
         pixel[i].g = green;
         pixel[i].b = blue; 
         //cout << (int)pixel[i].r << (int)pixel[i].g << (int)pixel[i].b << " ";
      }
   file.close();
   return true;
   
}
   
bool ppm_image::save(const std::string& filename) const
{
   //cout << (int)pixel[i].r << " " << (int)pixel[i].g << " " << (int)pixel[i].b << " ";
   ofstream out;
   out.open(filename.c_str());
   if (!out){
      return false;
   }
   out << "P3" << "\n" << widthVar << " " << heightVar << "\n" << 255 << "\n";
   int red,green,blue;
   for (int i = 0; i < widthVar*heightVar; i++){
      
      red = pixel[i].r;
      green = pixel[i].g;
      blue = pixel[i].b;
      out << (int)red << " "<< (int)green<< " " << (int)blue << " ";
      //cout << (int)red << " "<< (int)green<< " " << (int)blue << " ";
   }
   if (out.fail()){
      return false;
   }
   out.close();
   return true;
}

 ppm_image ppm_image::resize(int w, int h) const
{
   ppm_image result(w,h);
   ppm_pixel* newPixel = new ppm_pixel[w*h];
   double wScale =  (double)w / (double)widthVar;
   double hScale = (double)h / (double)heightVar;
      for(int i = 0; i < h; i++){
         for(int j = 0; j < w; j++){
            int newLoc = i*wScale;
            int oldLoc = (int)(i/hScale)*widthVar + (int)(j/wScale);
                
            newPixel[newLoc].r =  pixel[oldLoc].r;
            newPixel[newLoc].g =  pixel[oldLoc].g;
            newPixel[newLoc].b =  pixel[oldLoc].b;
         }
      }

    return result;
}

ppm_image ppm_image::flip_horizontal() const
{
   ppm_image image(widthVar, heightVar);
   ppm_pixel pix1;
   ppm_pixel pix2;
   int numRows = widthVar-1;
   int numCols = heightVar-1;
   ppm_pixel* pixels= new ppm_pixel[widthVar*heightVar];
   for (int r = 0; r < heightVar; r++){
      for (int c = 0; c < widthVar/2; c++){
         pix1 = get(numRows,numCols);
         pix2 = get(r,c);
         //cout << "hellpppp";
         //cout << (int)pix1.r << (int)pix1.g << (int)pix1.b << " ";
         pixels[r * widthVar + c] = pix1;
         pixels[numRows * widthVar + numCols] = pix2;
         numRows--;
         numCols--;
         
      }
   }
   for (int i = 0; i < widthVar*heightVar; i++){
      /*
         pixel[i].r = (int)pixels[i].r;
         pixel[i].g = (int)pixels[i].g;
         pixel[i].b = (int)pixels[i].b;
      */
         image.pixel[i].r = (int)pixels[i].r;
         image.pixel[i].g = (int)pixels[i].g;
         image.pixel[i].b = (int)pixels[i].b;
         
         //cout << (int)pixel[i].r << (int)pixel[i].g << (int)pixel[i].b << " ";
      }
    return image;
    delete[] pixels;
}

ppm_image ppm_image::subimage(int startx, int starty, int w, int h) const
{
   ppm_image result(w,h);
   ppm_pixel* newPixel = new ppm_pixel[w*h];
   int p = 0;
   int x = startx;
   int y = starty;
   for (int i = startx; i < x + w; i++){
      for (int j = starty; j < y + h; j++){
      int location = i * widthVar + j;
      newPixel[p].r = (int)pixel[location].r;
      newPixel[p].g = (int)pixel[location].g;
      newPixel[p].b = (int)pixel[location].b; 
      p++;
      }
   }
   for (int i = 0; i < w*h; i++){ 
      result.pixel[i].r = (int)newPixel[i].r;
      result.pixel[i].g = (int)newPixel[i].g;
      result.pixel[i].b = (int)newPixel[i].b; 
   }
   //result.widthVar = w;
   //result.heightVar = h;
   delete[] newPixel;
    return result;
}

void ppm_image::replace(const ppm_image& image, int startx, int starty)
{
   if((startx + image.widthVar > widthVar) || (starty + image.heightVar > heightVar))
      cout << "Image is too big";
   int j = 0;
   for (int i = startx; i < startx + image.widthVar; i++){
      pixel[i].r = (int)image.pixel[j].r;
      pixel[i].g = (int)image.pixel[j].g;
      pixel[i].b = (int)image.pixel[j].b; 
      j++;
   }
}

ppm_image ppm_image::alpha_blend(const ppm_image& other, float alpha) const
{
   ppm_image result(widthVar, heightVar);
   for (int i = 0; i < widthVar*heightVar; ++i){ 
      result.pixel[i].r = (float)pixel[i].r * (1-alpha) + (float)other.pixel[i].r*alpha;
      result.pixel[i].g = (float)pixel[i].g * (1-alpha) + (float)other.pixel[i].g*alpha;
      result.pixel[i].b = (float)pixel[i].b * (1-alpha) + (float)other.pixel[i].b*alpha; 

      //pixel[i].r = (int)result.pixel[i].r;
      //pixel[i].g = (int)result.pixel[i].g;
      //pixel[i].b = (int)result.pixel[i].b;
   }
   
   return result;
}

ppm_image ppm_image::gammaCorrect(float gamma) const
{
   //I = pow(I, 1/gamma)
   ppm_image result;
   ppm_pixel* newPixel = new ppm_pixel[heightVar*widthVar];
   for (int i = 0; i < heightVar*widthVar; i++){ 
      newPixel[i].r = pow((int)pixel[i].r, 1/gamma);
      newPixel[i].g = pow((int)pixel[i].g, 1/gamma);
      newPixel[i].b = pow((int)pixel[i].b, 1/gamma);

      result.pixel[i].r = (int)newPixel[i].r;
      result.pixel[i].g = (int)newPixel[i].g;
      result.pixel[i].b = (int)newPixel[i].b;
   }
   return result;
}

ppm_image ppm_image::grayscale() const
{
   ppm_image result;
   ppm_pixel* newPixel = new ppm_pixel[heightVar*widthVar];
   for (int i = 0; i < heightVar*widthVar; i++){ 
      newPixel[i].r = (int)pixel[i].r;
      newPixel[i].g = (int)pixel[i].g;
      newPixel[i].b = (int)pixel[i].b;

      result.pixel[i].r = (int)newPixel[i].r*0.3;
      result.pixel[i].g = (int)newPixel[i].g*0.59;
      result.pixel[i].b = (int)newPixel[i].b*0.11;
   }
   delete[] newPixel;
   return result;
}

ppm_pixel ppm_image::get(int row, int col) const
{
   ppm_pixel resultPixel = pixel[row * widthVar + col];
   return resultPixel;
}

void ppm_image::set(int row, int col, const ppm_pixel& c)
{
   pixel[row * widthVar + col] = c;
}

int ppm_image::height() const
{
   return heightVar;
}

int ppm_image::width() const
{
   return widthVar;
}

//Invert colors: subtract each color channel from the max value, 255.
void ppm_image::invert(){
   ppm_pixel* newPixel = new ppm_pixel[heightVar*widthVar];
   for (int i = 0; i < heightVar*widthVar; i++){ 
      newPixel[i].r = (int)pixel[i].r;
      newPixel[i].g = (int)pixel[i].g;
      newPixel[i].b = (int)pixel[i].b;

      pixel[i].r = 255-newPixel[i].r;
      pixel[i].g = 255-newPixel[i].g;
      pixel[i].b = 255-newPixel[i].b;
   }
   delete[] newPixel;
}

//Swirl colors: rotate the colors of your image such that the red channel becomes the green channel, the green becomes blue, and the blue becomes red.
void ppm_image::swirl(){
   ppm_pixel* newPixel = new ppm_pixel[heightVar*widthVar];
   for (int i = 0; i < heightVar*widthVar; i++){ 
      newPixel[i].r = (int)pixel[i].r;
      newPixel[i].g = (int)pixel[i].g;
      newPixel[i].b = (int)pixel[i].b;

      pixel[i].r = 255-newPixel[i].g;
      pixel[i].g = 255-newPixel[i].b;
      pixel[i].b = 255-newPixel[i].r;
   }
   delete[] newPixel;
}
//Add a border around the edge of your images.
void ppm_image::border(ppm_pixel bord){
   //top
   for (int i = 0; i < widthVar; i++){
      for (int j = 0; j < 3; j++){
         pixel[j*widthVar + i].r = (int)bord.r;
         pixel[j*widthVar + i].g = (int)bord.g;
         pixel[j*widthVar + i].b = (int)bord.b;
      }
   }
   //right side
   for (int i = widthVar-3; i < widthVar; i++){
      for (int j = 0; j < heightVar; j++){
         pixel[j*widthVar + i].r = (int)bord.r;
         pixel[j*widthVar + i].g = (int)bord.g;
         pixel[j*widthVar + i].b = (int)bord.b;
      }
   }
   //bottom
   for (int i = 0; i < widthVar; i++){
      for (int j = heightVar-3; j < heightVar; j++){
         pixel[j*widthVar + i].r = (int)bord.r;
         pixel[j*widthVar + i].g = (int)bord.g;
         pixel[j*widthVar + i].b = (int)bord.b;
      }
   }
   //left side
   for (int i = 0; i < 3; i++){
      for (int j = 0; j < heightVar; j++){
         pixel[j*widthVar + i].r = (int)bord.r;
         pixel[j*widthVar + i].g = (int)bord.g;
         pixel[j*widthVar + i].b = (int)bord.b;
      }
   }
}


//Difference: given a ppm_image, implement this.pixel - other.pixel
void ppm_image::difference(ppm_image img){
   //make sure it is does not go below 0
   ppm_pixel* newPixel = new ppm_pixel[heightVar*widthVar];
   for (int i = 0; i < heightVar*widthVar; i++){ 
      newPixel[i].r = std::max((int)img.pixel[i].r - (int)pixel[i].r, 0);
      newPixel[i].g = std::max((int)img.pixel[i].g - (int)pixel[i].g, 0);
      newPixel[i].b = std::max((int)img.pixel[i].b - (int)pixel[i].b, 0);

      pixel[i].r = newPixel[i].g;
      pixel[i].g = newPixel[i].b;
      pixel[i].b = newPixel[i].r;
   }
   delete[] newPixel;
}

//Sum: given a ppm_image, implement this.pixel + other.pixel
void ppm_image::sum(ppm_image img){
   //make sure it does not go above 255
   ppm_pixel* newPixel = new ppm_pixel[heightVar*widthVar];
   for (int i = 0; i < heightVar*widthVar; i++){ 
      newPixel[i].r = std::min((int)img.pixel[i].r + (int)pixel[i].r, 255);
      newPixel[i].g = std::min((int)img.pixel[i].g + (int)pixel[i].g, 255);
      newPixel[i].b = std::min((int)img.pixel[i].b + (int)pixel[i].b, 255);

      pixel[i].r = newPixel[i].g;
      pixel[i].g = newPixel[i].b;
      pixel[i].b = newPixel[i].r;
   }
   delete[] newPixel;
}

//Lightest
void ppm_image::lightest(ppm_image img){
   ppm_pixel* newPixel = new ppm_pixel[heightVar*widthVar];
   for (int i = 0; i < heightVar*widthVar; i++){ 
      newPixel[i].r = std::max((int)img.pixel[i].r, (int)pixel[i].r);
      newPixel[i].g = std::max((int)img.pixel[i].g, (int)pixel[i].g);
      newPixel[i].b = std::max((int)img.pixel[i].b, (int)pixel[i].b);

      pixel[i].r = newPixel[i].g;
      pixel[i].g = newPixel[i].b;
      pixel[i].b = newPixel[i].r;
   }
   delete[] newPixel;
}
