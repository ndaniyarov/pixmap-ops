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
   file >> p3 >> widthVar >> heightVar >> max;
   pixel = new ppm_pixel[widthVar*heightVar];
   
   if (!file){
      return false;
   }
      int red, green, blue = 0;
      for (int i = 0; i < widthVar*heightVar; i++){
         file >> red >> green >> blue;
         pixel[i].r = red;
         pixel[i].g = green;
         pixel[i].b = blue; 
      }
   file.close();
   return true;
   
}
   
bool ppm_image::save(const std::string& filename) const
{
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
      for(int i = 0; i < heightVar; i++){
         for(int j = 0; j < widthVar; j++){
            int newy = floor((float)i * (w-1)/(float)(widthVar-1));
            int newx = floor((float)j * (h-1)/(float)(heightVar-1));
            int newLoc = newx * w + newy;
                
            result.pixel[newLoc].r =  pixel[i * widthVar + j].r;
            result.pixel[newLoc].g =  pixel[i * widthVar + j].g;
            result.pixel[newLoc].b =  pixel[i * widthVar + j].b;
         }
      }
    return result;
}

ppm_image ppm_image::flip_horizontal() const
{
   ppm_image image(widthVar, heightVar);
   int red, green, blue = 0;

   for (int r = 0; r <= heightVar/2; r++){
      for (int c = 0; c < widthVar; c++){
         red = pixel[r * widthVar + c].r;
         green = pixel[r * widthVar + c].g;
         blue = pixel[r * widthVar + c].b;

         image.pixel[r * widthVar + c].r = pixel[((heightVar - r) * widthVar) + c].r;
         image.pixel[r * widthVar + c].g = pixel[((heightVar - r) * widthVar) + c].g;
         image.pixel[r * widthVar + c].b = pixel[((heightVar - r) * widthVar) + c].b;

         image.pixel[((heightVar - r) * widthVar) + c].r = red;
         image.pixel[((heightVar - r) * widthVar) + c].g = green;
         image.pixel[((heightVar - r) * widthVar) + c].b = blue;
      }
   }
    return image;
}

ppm_image ppm_image::subimage(int startx, int starty, int w, int h) const
{
   if (widthVar < w+startx)
      w = widthVar;
   if (heightVar < h+starty)
      h = heightVar;
   ppm_image result(w,h);
   int p = 0;
   for (int i = startx; i < startx + w; i++){
      for (int j = starty; j < starty + h; j++){
      int location = (j * widthVar) + i;
      result.pixel[p].r = (int)pixel[location].r;
      result.pixel[p].g = (int)pixel[location].g;
      result.pixel[p].b = (int)pixel[location].b; 
      p++;
      }
   }
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
   for (int i = 0; i < widthVar*heightVar; i++){ 
      result.pixel[i].r = (float)((pixel[i].r*(1-alpha)) + (float)(other.pixel[i].r*alpha));
      result.pixel[i].g = (float)((pixel[i].g*(1-alpha)) + (float)(other.pixel[i].g*alpha));
      result.pixel[i].b = (float)((pixel[i].b*(1-alpha)) + (float)(other.pixel[i].b*alpha));
   }
   
   return result;
}

ppm_image ppm_image::gammaCorrect(float gamma) const
{
   ppm_image result(widthVar,heightVar);
   for (int i = 0; i < heightVar*widthVar; i++){ 
      result.pixel[i].r  = 255 * pow((float)pixel[i].r/255, (1/gamma));
      result.pixel[i].g  = 255 * pow((float)pixel[i].g/255, (1/gamma));
      result.pixel[i].b  = 255 * pow((float)pixel[i].b/255, (1/gamma));
   }
   return result;
}

ppm_image ppm_image::grayscale() const
{
   ppm_image result(widthVar, heightVar);
   for (int i = 0; i < heightVar*widthVar; i++){ 
      int average = floor((float)pixel[i].r*0.3 + (float)pixel[i].g*0.5 + pixel[i].b*0.11);
      result.pixel[i].r = average;
      result.pixel[i].g = average;
      result.pixel[i].b = average;
   }
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
ppm_image ppm_image::invert(){
   ppm_image img(widthVar, heightVar);
   for (int i = 0; i < heightVar*widthVar; i++){ 
      img.pixel[i].r = 255 - (int)pixel[i].r;
      img.pixel[i].g = 255 - (int)pixel[i].g;
      img.pixel[i].b = 255 - (int)pixel[i].b;
   }
   return img;
}

//Swirl colors: rotate the colors of your image such that the red channel becomes the green channel, the green becomes blue, and the blue becomes red.
ppm_image ppm_image::swirl(){
   ppm_image img(widthVar, heightVar);
   for (int i = 0; i < heightVar*widthVar; i++){ 
      img.pixel[i].r = (int)pixel[i].g;
      img.pixel[i].g = (int)pixel[i].b;
      img.pixel[i].b = (int)pixel[i].r;
   }
   return img;
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
ppm_image ppm_image::difference(ppm_image img){
   ppm_image result(widthVar, heightVar);
   for (int i = 0; i < heightVar*widthVar; i++){ 
      result.pixel[i].r = std::max((int)img.pixel[i].r - (int)pixel[i].r, 0);
      result.pixel[i].g = std::max((int)img.pixel[i].g - (int)pixel[i].g, 0);
      result.pixel[i].b = std::max((int)img.pixel[i].b - (int)pixel[i].b, 0);
   }
   return result;
}

//Sum: given a ppm_image, implement this.pixel + other.pixel
ppm_image ppm_image::sum(ppm_image img){
   ppm_image result(widthVar, heightVar);
   for (int i = 0; i < heightVar*widthVar; i++){ 
      result.pixel[i].r = std::min((int)img.pixel[i].r + (int)pixel[i].r, 255);
      result.pixel[i].g = std::min((int)img.pixel[i].g + (int)pixel[i].g, 255);
      result.pixel[i].b = std::min((int)img.pixel[i].b + (int)pixel[i].b, 255);
   }
   return result;
}

//Lightest
ppm_image ppm_image::lightest(ppm_image img){
   ppm_image result(widthVar, heightVar);
   for (int i = 0; i < heightVar*widthVar; i++){ 
      result.pixel[i].r = std::max((int)img.pixel[i].r, (int)pixel[i].r);
      result.pixel[i].g = std::max((int)img.pixel[i].g, (int)pixel[i].g);
      result.pixel[i].b = std::max((int)img.pixel[i].b, (int)pixel[i].b);
   }
   return result;
}

ppm_image ppm_image::collageVertical(ppm_image img){
   int newSize = widthVar* (heightVar + img.heightVar);
    ppm_image result(widthVar, heightVar + img.heightVar);
   for (int i = 0; i < heightVar*widthVar; i++){ 
      result.pixel[i].r = (int)pixel[i].r;
      result.pixel[i].g = (int)pixel[i].g;
      result.pixel[i].b = (int)pixel[i].b;
   }
   int j = 0;
   for (int i = (heightVar * widthVar); i < newSize; i++){
      result.pixel[i].r = (int)img.pixel[j].r;
      result.pixel[i].g = (int)img.pixel[j].g;
      result.pixel[i].b = (int)img.pixel[j].b;
      j++;
   }
   return result;
}
ppm_image ppm_image::collageHorizontal(ppm_image img){
   
   int newSize = (widthVar + img.widthVar)*heightVar;
    ppm_image result(widthVar + img.widthVar, heightVar);
   for (int i = 0; i < heightVar*widthVar; i++){ 
      result.pixel[i].r = (int)pixel[i].r;
      result.pixel[i].g = (int)pixel[i].g;
      result.pixel[i].b = (int)pixel[i].b;
      
   }
   int j = 0;
   for (int i = (heightVar * widthVar); i < newSize; i++){
      result.pixel[i].r = (int)img.pixel[j].r;
      result.pixel[i].g = (int)img.pixel[j].g;
      result.pixel[i].b = (int)img.pixel[j].b;
      j++;
   }
   return result;
}
