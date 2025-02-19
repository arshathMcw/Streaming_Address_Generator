// multi_dimension_stores.cpp
#include <c7x.h>
#include <c7x_scalable.h>
#include <iostream>

using namespace c7x;
using namespace std;

#define IMG_WIDTH (32)
#define IMG_HEIGHT (8)
#define IMG_STRIDE (IMG_WIDTH)
#define IMG_CH (3)

int main(){
    int32_t data[IMG_CH][IMG_HEIGHT][IMG_WIDTH],image[IMG_CH][IMG_HEIGHT][IMG_WIDTH];
    for(int ch = 0;ch < IMG_CH;ch++){
        int32_t *ptr = (int32_t *)&image[ch * (IMG_HEIGHT * IMG_WIDTH)];
        int32_t value = 0;
        for(int h = 0;h < IMG_HEIGHT;h++){
            for(int w = 0;w < IMG_WIDTH;w++){
                data[ch][h][w] = value++;
                cout<<data[ch][h][w]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    __SA_TEMPLATE_v1 saTemplate = __gen_SA_TEMPLATE_v1();
    saTemplate.VECLEN = sa_veclen<int_vec>::value;

    saTemplate.DIMFMT = __SA_DIMFMT_3D;
    saTemplate.ICNT0 = IMG_WIDTH;
    saTemplate.ICNT1 = IMG_HEIGHT;  
    saTemplate.DIM1 = IMG_STRIDE;
    saTemplate.ICNT2 = IMG_CH;      
    saTemplate.DIM2 = IMG_STRIDE * IMG_HEIGHT;

    __SA0_OPEN(saTemplate);
    const int vec_len = element_count_of<int_vec>::value;
    for(int32_t ctr = 0; ctr < (NUM_CH * IMG_HEIGHT * IMG_WIDTH); ctr+=vec_len) {
        int_vec vOut = *((int_vec)&data[ctr]);
        __vpred pred = strm_agen<0, int_vec>::get_vpred();
        int_vec * addr = strm_agen<0, int_vec>::get_adv(&image[0][0][0]);
        __vstore_pred(pred, addr, vOut);
        // printf("vOut[%d] = ", ctr);
        // vOut.print();
    }
    __SA0_CLOSE();
}   

