// access_and_close.cpp
#include <iostream>
#include <c7x.h>
#include <c7x_scalable.h>

using namespace std;
using namespace c7x; 

#define IMAGE_WIDTH  (128)
#define IMAGE_HEIGHT (16)

int main(){
    int32_t image[IMAGE_HEIGHT][IMAGE_WIDTH] = {0};
    int32_t idx;
    for(int32_t rows = 0; rows < IMAGE_HEIGHT; rows++) {
        for(int32_t cols = 0; cols < IMAGE_WIDTH; cols++) {
            image[rows][cols] = rows+cols;
        }
    }
    __SA_TEMPLATE_v1 saTemplate = __gen_SA_TEMPLATE_v1();
    saTemplate.VECLEN  = sa_veclen<int_vec>::value; 
    saTemplate.DIMFMT  = __SA_DIMFMT_2D;
    saTemplate.ICNT0 = IMAGE_WIDTH;
    saTemplate.ICNT1 = IMAGE_HEIGHT; 
    saTemplate.DIM1 = IMAGE_WIDTH;
    __SA0_OPEN(saTemplate);
    const int vec_len = element_count_of<int_vec>::value;
    for(int32_t rows = 0; rows < IMAGE_HEIGHT; rows++) {
        for(int32_t cols = 0; cols < IMAGE_WIDTH; cols+=vec_len) {
            int_vec vData = * strm_agen<0, int_vec>::get_adv((void *)image);
            cout<<"vData["<<rows<<"]["<<cols<<"] = ";
            vData.print();
        }
    }
    __SA0_CLOSE();
}