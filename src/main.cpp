#include "head.h"

int main()
{    
    //初始化小波分解所需要的系数，第一个参数为DBn小波，第二个系数是信号的行数，第三个系数是信号的列数
    DWT dwt(4,9,32,7681,0,32,40,32);//参数说明，，第一参数是dbn小波，第二个参数是分解n层，第三个参数是有几个信号，第四个参数是信号长度，第五个参数是读文件模式0读EEG，1读label
    //第六个参数是读那个文件夹，第七个参数是文件夹下那个文件，第八个参数重构是的txt哪一行,第九个参数为频率
    //初始化系数矩阵的信息
    int dec = 0;//分解数据长度
    int decline = dwt.getDWT_data_line();
    int filer =  2 * dwt.getDWT_DBN();
    for(int i = 0; i < dwt.getDWT_DBN_N(); ++i)
    {
        dec = (decline + filer - 1) / 2;
        decline = dec;        
    }
    std::cout << "dec = " << dec << std::endl;
    Matrix max(dwt.getDWT_DBN());
    max.matrix();
    std::cout << "系数矩阵" << std::endl;
    max.Print_matrix();
    //进行读文件操作      
    RWDATE_REF rwref(dwt.getDWT_DBN_N(),1,1,1,dec); 
    rwref.ReadDate_ref();                
    RTF rtf(dwt.getDWT_DBN(),dwt.getDWT_DBN_N(),rwref.getFile_data_line(),rwref.getFile_m_ref(),rwref.getFile_n_ref(),128);                
    rtf.Reverse_transform_init(max.getMatrix(),"All");//初始化重构函数
    rtf.Reverse_transform(rwref.getRaw_Data_ref(),rwref.getFile_txt_ref());    
    

    return 0;
}

