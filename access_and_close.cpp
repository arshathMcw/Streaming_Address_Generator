// access_and_close.cpp
#include <iostream>
#include <c7x.h>
#include <c7x_scalable.h>

using namespace std;
using namespace c7x; 

#define IMAGE_WIDTH  (128)
#define IMAGE_HEIGHT (16)

int main(){
    uint8_t image[IMAGE_HEIGHT][IMAGE_WIDTH] = {0};
    int32_t idx;
    idx = 255;
    for(int32_t rows = 0; rows < IMAGE_HEIGHT; rows++) {
        for(int32_t cols = 0; cols < IMAGE_WIDTH; cols++) {
            image[rows][cols] = (cols & 0x3F)? idx: ++idx;
        }
    }
    uint32_t width  = 256;
    uint32_t height = 128;
    __SA_TEMPLATE_v1 saTemplate = __gen_SA_TEMPLATE_v1();
    saTemplate.VECLEN  = sa_veclen<char_vec>::value; 
    saTemplate.DIMFMT  = __SA_DIMFMT_2D;
    saTemplate.ICNT0 = width;
    saTemplate.ICNT1 = height; 
    saTemplate.DIM1 = width;
    __SA0_OPEN(saTemplate);
    const int vec_len = element_count_of<uchar_vec>::value;
    for(int32_t rows = 0; rows < IMAGE_HEIGHT; rows++) {
        for(int32_t cols = 0; cols < IMAGE_WIDTH; cols+=vec_len) {
            uchar_vec vData = * strm_agen<0, uchar_vec>::get_adv((void *)image);
            cout<<"vData["<<rows<<"]["<<cols<<"] = ";
            vData.print();
        }
    }
    __SA0_CLOSE();
}