#include "head.h"

int main()
{
        
    boost::progress_timer t;  //计算程序运行时间
    pDEC dec;//用于接收分解指针只传递一个数据大小
    
    //初始化小波分解所需要的系数，第一个参数为DBn小波，第二个系数是信号的行数，第三个系数是信号的列数
    DWT dwt(4,9,32,7681,0,32,40,32);//参数说明，，第一参数是dbn小波，第二个参数是分解n层，第三个参数是有几个信号，第四个参数是信号长度，第五个参数是读文件模式0读EEG，1读label
    //第六个参数是读那个文件夹，第七个参数是文件夹下那个文件，第八个参数重构是的txt哪一行,第九个参数为频率
    //初始化系数矩阵的信息
    Matrix max(dwt.getDWT_DBN());
    max.matrix();
    std::cout << "系数矩阵" << std::endl;
    max.Print_matrix();
    //进行读文件操作      
    for(int i = 1; i <=  dwt.getDWT_file_m(); ++i)
    {
        for(int j = 1; j <= dwt.getDWT_file_n(); ++j)
        {
            for(int k = 1; k <= dwt.getDWT_file_txt(); ++k)
            {
                RWDATE_REF rwref(dwt.getDWT_DBN_N(),i,j,k,dec); 
                rwref.ReadDate_ref();
                //rwref.Print_rwDate_ref();
                RTF rtf(dwt.getDWT_DBN(),dwt.getDWT_DBN_N(),rwref.getFile_data_line(),rwref.getFile_m_ref(),rwref.getFile_n_ref(),128);                
                rtf.Reverse_transform_init(max.getMatrix(),"Alpha");//初始化重构函数
                rtf.Reverse_transform(rwref.getRaw_Data_ref(),rwref.getFile_txt_ref());             
            }
        } 
    }
    
    std::cout << t.elapsed() << std::endl; 
    return 0;
}

